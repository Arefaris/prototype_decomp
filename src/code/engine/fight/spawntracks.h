// The fight tracks that drive a light, teleport an object and spawn an object (unit 0x108B52D0 - 0x108B6C40; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_SPAWNTRACKS_H
#define ENGINE_FIGHT_SPAWNTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::LightTrack (17 vftable slots, 0x68 bytes)
	class LightTrack : public fight::Track
	{
	public:
		// 0x108B5420
		LightTrack();
		virtual ~LightTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F3260)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);
		// vftable slot 16 (0x108B54E0)
		virtual bool Slot16(int index);

		// The members the properties write
		// 0x108B52F0: sets or clears the override bits of a group's properties
		void ApplyGroup(int group, bool value);
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetLightName(const fight::Name& value);
		bool SetColour(bool value);
		bool SetColourColour(const math::Colour128& value);
		bool SetIntensity(bool value);
		bool SetIntensityIntensity(float value);
		bool SetShadowCaster(bool value);
		bool SetShadowCasterShadowOffset(float value);
		bool SetShadowCasterRangeMultiplier(float value);
		bool SetShadowCasterRadiusMultiplier(float value);
		bool SetShadowCasterMaxRadius(float value);
		bool SetUmbra(bool value);
		bool SetUmbraUmbra(float value);
		bool SetUmbraPenumbra(float value);
		bool SetDecay(bool value);
		bool SetDecayInner(float value);
		bool SetDecayOuter(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		// The bits of the properties the track overrides (Slot16 tests one, ApplyGroup sets a group's)
		unsigned __int64 overrideMask;  // +0x10
		fight::Name lightName;  // +0x18
		math::Colour128 colourColour;  // +0x20
		float decayInner;  // +0x30
		float decayOuter;  // +0x34
		float intensityIntensity;  // +0x38
		float shadowCasterMaxRadius;  // +0x3C
		float shadowCasterRadiusMultiplier;  // +0x40
		float shadowCasterRangeMultiplier;  // +0x44
		float shadowCasterShadowOffset;  // +0x48
		float timeBegin;  // +0x4C
		float timeEnd;  // +0x50
		float umbraPenumbra;  // +0x54
		float umbraUmbra;  // +0x58
		bool colour;  // +0x5C
		bool decay;  // +0x5D
		bool intensity;  // +0x5E
		bool shadowCaster;  // +0x5F
		bool umbra;  // +0x60
		int unknown64;
	};

	extern fight::Property** gLightTrackProperties;
	// 0x108B5740
	// 0x108B5760
	fight::TrackFactory* CreateLightTrackFactory(const char* name);
	void RegisterLightTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::TeleportTrack (16 vftable slots, 0x48 bytes)
	class TeleportTrack : public fight::Track
	{
	public:
		// 0x108B5D40
		TeleportTrack();
		virtual ~TeleportTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F3780)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetRestorePosition(bool value);
		bool SetObject(const fight::Name& value);
		bool SetSpace(int value);
		bool SetSpaceJoint(const fight::Name& value);
		bool SetOffset(const math::Vector& value);
		bool SetOrientation(const math::Vector& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name object;  // +0x10
		fight::Name spaceJoint;  // +0x18
		math::Vector offset;  // +0x20
		math::Vector orientation;  // +0x2C
		float timeBegin;  // +0x38
		int space;  // +0x3C
		bool restorePosition;  // +0x40
		int unknown44;
	};

	extern fight::Property** gTeleportTrackProperties;
	// 0x108B5FB0
	// 0x108B5FD0
	fight::TrackFactory* CreateTeleportTrackFactory(const char* name);
	void RegisterTeleportTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SpawnObjectTrack (16 vftable slots, 0x78 bytes)
	class SpawnObjectTrack : public fight::Track
	{
	public:
		// 0x108B6480
		SpawnObjectTrack();
		virtual ~SpawnObjectTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F43D0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTemplateName(const fight::Name& value);
		bool SetObjectName(const fight::Name& value);
		bool SetAddSuffix(bool value);
		bool SetInitialState(const char* value);
		bool SetSpecificPlaybackSet(const fight::Name& value);
		bool SetSpawnSpace(int value);
		bool SetSpawnJoint(const fight::Name& value);
		bool SetOffset(const math::Vector& value);
		bool SetOrientation(const math::Vector& value);
		bool SetLinearVelocity(const math::Vector& value);
		bool SetAngularVelocity(const math::Vector& value);
		bool SetCollideWithSpawnerDelay(float value);
		bool SetDeleteOnExit(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name objectName;  // +0x10
		fight::Name spawnJoint;  // +0x18
		fight::Name specificPlaybackSet;  // +0x20
		fight::Name templateName;  // +0x28
		math::Vector angularVelocity;  // +0x30
		math::Vector linearVelocity;  // +0x3C
		math::Vector offset;  // +0x48
		math::Vector orientation;  // +0x54
		char* initialState;  // +0x60
		float collideWithSpawnerDelay;  // +0x64
		float timeBegin;  // +0x68
		int spawnSpace;  // +0x6C
		bool addSuffix;  // +0x70
		bool deleteOnExit;  // +0x71
		int unknown74;
	};

	extern fight::Property** gSpawnObjectTrackProperties;
	// 0x108B6790
	// 0x108B67B0
	fight::TrackFactory* CreateSpawnObjectTrackFactory(const char* name);
	void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
