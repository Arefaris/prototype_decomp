// The fight tracks the engine registers with the fight system and the factory machinery that builds them: a
// reflected property per track member (fight::Property and its type classes), the factory the game looks a track up
// with (fight::TrackFactory / fight::TrackFactoryCaster and their per-class templates) and the tracks themselves.
// Unit 0x108078E0 - 0x10809000 and on (no assert path; the file name is a guess). Class and member names are guesses
// until the binary tells the real ones; the layouts, the vftable slots and the property names come from the code.
#ifndef ENGINE_FIGHT_TRACKFACTORY_H
#define ENGINE_FIGHT_TRACKFACTORY_H

#include "code/core/name.h"
#include "code/engine/fight/sequencer.h"

namespace fight
{
	class TrackFactory;

	// The engine's names are case sensitive
	typedef core::Name<core::CaseSensitiveKey> Name;

	// A reflected property of a fight node's class (RTTI: fight::Property, 7 vftable slots, 0x10 bytes): the
	// property's name and, in the derived classes, the accessor that reads or writes the member it stands for.
	class Property
	{
	public:
		Property(const char* name);

		// vftable slot 0: the kind of value the property carries (every type class returns its own id)
		virtual int GetType() const = 0;
		// vftable slot 1: nothing is attached to the property
		virtual bool IsNull() const;
		virtual void Slot2(int arg);
		virtual void Slot3(int arg);
		virtual void Slot4(int a, int b, int c, int d);
		virtual void Slot5(int a, int b);
		// vftable slot 6: reads the value off an object and hands it to the property's own setter below
		virtual bool Slot6(int a, int b, void* object) = 0;

		// The word between the vftable and the name (the engine's own constructor leaves it alone)
		unsigned int unknown4;
		Name name;
	};

	// The property classes per value kind: each returns its own type id and reads its value off an object
	class PropertyTypeFloat : public Property
	{
	public:
		PropertyTypeFloat(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int a, int b, void* object);
		// vftable slot 7: writes a value into the member the property stands for
		virtual bool Set(void* object, float value) = 0;
	};

	class PropertyTypeBool : public Property
	{
	public:
		PropertyTypeBool(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int a, int b, void* object);
		// vftable slot 7
		virtual bool Set(void* object, bool value) = 0;
	};

	class PropertyTypeString : public Property
	{
	public:
		PropertyTypeString(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int a, int b, void* object);
		// vftable slot 7: the value came in as text
		virtual bool Set(void* object, const char* text) = 0;
	};

	class PropertyTypeName : public PropertyTypeString
	{
	public:
		PropertyTypeName(const char* name);

		// vftable slot 6
		virtual bool Slot6(int a, int b, void* object);
		// vftable slot 7: turns the text into a name and hands it to slot 8
		virtual bool Set(void* object, const char* text);
		// vftable slot 8
		virtual bool Set(void* object, const Name& value) = 0;
	};

	// The property of a float member with an optional range, and of a bool or a name member: the setter is the
	// track's own member function, stored as a member pointer in the property (the classes are 0x18 bytes)
	template<class T> class PropertyFloatConstRange : public PropertyTypeFloat
	{
	public:
		typedef bool (T::*Setter)(float);

		PropertyFloatConstRange(const char* name, Setter setter)
			: PropertyTypeFloat(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, float value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyBool : public PropertyTypeBool
	{
	public:
		typedef bool (T::*Setter)(bool);

		PropertyBool(const char* name, Setter setter)
			: PropertyTypeBool(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, bool value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyName : public PropertyTypeName
	{
	public:
		typedef bool (T::*Setter)(const Name&);

		PropertyName(const char* name, Setter setter)
			: PropertyTypeName(name), m_setter(setter)
		{
		}

		// vftable slot 8
		virtual bool Set(void* object, const Name& value)
		{
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	// The list of a track class's properties, built once from a null-terminated array of them (0x105A8420)
	void RegisterPropertyList(Property** properties, Property*** list);
	// Frees a property list and clears it (0x105A9650, used as a track class's clear function)
	void FreePropertyList(Property*** list);

	// The factory of one track class (RTTI: fight::TrackFactory, 2 vftable slots, 0x18 bytes). Its constructor
	// registers the class's properties the first time one of them is asked for.
	class TrackFactory
	{
	public:
		TrackFactory(const char* name, void (*registerProperties)(), void (*clearProperties)());

		// vftable slot 0 (0x105A9CF0, inherited from every factory)
		virtual void Slot0();
		// vftable slot 1: makes a track of this factory's class
		virtual void* CreateTrack() = 0;

		unsigned int unknown4;
		Name name;
		int unknown10;
		void (*clearProperties)();
	};

	// What the game casts a factory to before asking it for a track (RTTI: fight::TrackFactoryCaster, 2 vftable
	// slots): the vtable alone, the object has no data
	class TrackFactoryCaster
	{
	public:
		// vftable slot 0: whether a factory is of the class this caster knows
		virtual bool IsType(TrackFactory* factory) = 0;
		// vftable slot 1: makes the factory of that class
		virtual TrackFactory* CreateFactory(const char* name) = 0;
	};

	// 0x105A9E90 (another unit): the factory of a track class, the one the list of load listeners holds already or a
	// new one made through the caster
	TrackFactory* FindTrackFactory(const char* name, TrackFactoryCaster* caster);

	// The list of track factories the fight system knows (another unit's class; only the one member this unit calls
	// is laid out here)
	class TrackRegistry
	{
	public:
		// 0x105A5D10
		void AddFactory(TrackFactory* factory);
	};

	template<class T> class TrackFactoryTemplate : public TrackFactory
	{
	public:
		TrackFactoryTemplate(const char* name)
			: TrackFactory(name, T::RegisterProperties, T::ClearProperties)
		{
		}

		// vftable slot 1
		virtual void* CreateTrack()
		{
			return new T();
		}
	};

	template<class T> class TrackFactoryCasterTemplate : public TrackFactoryCaster
	{
	public:
		// 0x108079C0 (out of line, in the .cpp of the fight track unit): sets the vftable
		TrackFactoryCasterTemplate();

		// vftable slot 0
		virtual bool IsType(TrackFactory* factory)
		{
			return dynamic_cast<TrackFactoryTemplate<T>*>(factory) != 0;
		}

		// vftable slot 1
		virtual TrackFactory* CreateFactory(const char* name)
		{
			return new TrackFactoryTemplate<T>(name);
		}
	};
}

namespace engine
{
	using fight::Property;
	using fight::PropertyBool;
	using fight::PropertyFloatConstRange;
	using fight::PropertyName;
	using fight::TrackFactory;
	using fight::TrackFactoryCasterTemplate;
	using fight::TrackFactoryTemplate;

	// engine::PlaybackTrack (RTTI: engine::PlaybackTrack, 16 vftable slots, 0x28 bytes): plays a playback set
	class PlaybackTrack : public fight::Track
	{
	public:
		PlaybackTrack();
		virtual ~PlaybackTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (another unit)
		virtual void Slot15();

		// 0x108078E0 / 0x108078F0 / 0x10807920 / 0x10807940: the members the properties write
		bool SetTimeBegin(float value);
		bool SetNotifyOnPlaybackFinished(bool value);
		bool SetState(const fight::Name& value);
		bool SetSpecificPlaybackSet(const fight::Name& value);

		// 0x10807B50 / 0x10807910: the property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		// The two names the properties write: "specificPlaybackSet" at +0x10, "state" at +0x18
		fight::Name specificPlaybackSet;
		fight::Name state;
		float timeBegin;
		bool notifyOnPlaybackFinished;
	};

	// The properties of the track classes, one list per class (0x11284B50 for the playback track)
	extern fight::Property** gPlaybackTrackProperties;

	// The per-class list accessors the properties and the factory use
	fight::Property* GetPlaybackTrackProperty(int index);
}

#endif
