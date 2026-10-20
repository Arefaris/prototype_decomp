// The editor's lists of the scenario system (code/engine/scenario/scenariolisters.cpp): the names of the scenario
// message kinds and the names of the handles those messages carry. Both are fight::ListObjects over fixed arrays of
// names with a number (RTTI: engine::scenario::ScenarioMessageLister, engine::scenario::AffiliateLister); the engine
// keeps one of each (0x111C4280, 0x111C4888). Names of the members are guesses.
#ifndef ENGINE_SCENARIO_SCENARIOLISTERS_H
#define ENGINE_SCENARIO_SCENARIOLISTERS_H

#include "code/container/arrayfixed.h"
#include "code/core/name.h"
#include "code/engine/fight/listobject.h"

namespace engine
{
	namespace scenario
	{
		// A name and the number it stands for (16 bytes: the last word is only there for the size). The two lists keep
		// entries of their own types. The ordering is by the name's hash
		struct MessageEntry
		{
			MessageEntry(const core::Name<core::CaseSensitiveKey>& newName, int newValue) : name(newName)
			{
				value = newValue;
			}
			MessageEntry(const MessageEntry& other) : name(other.name)
			{
				value = other.value;
			}
			MessageEntry& operator=(const MessageEntry& other)
			{
				name = other.name;
				value = other.value;
				return *this;
			}
			bool operator<(const MessageEntry& other) const;

			core::Name<core::CaseSensitiveKey> name;
			int value;
			int padding;
		};

		struct AffiliateEntry
		{
			AffiliateEntry(const core::Name<core::CaseSensitiveKey>& newName, int newValue) : name(newName)
			{
				value = newValue;
			}
			AffiliateEntry(const AffiliateEntry& other) : name(other.name)
			{
				value = other.value;
			}
			AffiliateEntry& operator=(const AffiliateEntry& other)
			{
				name = other.name;
				value = other.value;
				return *this;
			}
			bool operator<(const AffiliateEntry& other) const;

			core::Name<core::CaseSensitiveKey> name;
			int value;
			int padding;
		};

		// What the lists answer with for a number they do not have (0x11276210)
		extern core::Name<core::CaseSensitiveKey> gEmptyListName;

		// The scenario message kinds by name: the number is the message's event
		class ScenarioMessageLister : public fight::ListObject
		{
		public:
			enum
			{
				CAPACITY = 96
			};

			// 0x10830390 / 0x108303A0 / 0x108303D0
			virtual int GetCount() const;
			virtual const core::Name<core::CaseSensitiveKey>* GetName(int index);
			virtual void Slot2();
			// 0x10830410: adds the name of text; nothing when the list is full
			void Add(const char* text, int value);
			// 0x10830470
			int GetValue(int index) const;

			// 0x108322D0: puts the entries in order of their names
			void Sort();
			// 0x10831E90
			void Reset();

			container::ArrayFixed<MessageEntry, CAPACITY> entries;
		};

		// The names of the handles of the messages: the number is the handle's index in its message
		class AffiliateLister : public fight::ListObject
		{
		public:
			enum
			{
				CAPACITY = 384
			};

			// 0x10830490 / 0x108304A0 / 0x108304D0
			virtual int GetCount() const;
			virtual const core::Name<core::CaseSensitiveKey>* GetName(int index);
			virtual void Slot2();
			// 0x10830510
			void Add(const char* text, int value);
			// 0x10830570
			int GetValue(int index) const;

			// 0x108322F0
			void Sort();
			// 0x10831EA0
			void Reset();

			container::ArrayFixed<AffiliateEntry, CAPACITY> entries;
		};

		// 0x10832310 / 0x10832070: sort both lists / empty both lists
		void SortListers();
		void ResetListers();

		extern ScenarioMessageLister gScenarioMessageLister;
		extern AffiliateLister gAffiliateLister;

		// 0x10830580 - 0x108309E0: adds a message kind (the event number and the name the editor shows) to the first
		// list and the names of its handles to the second
		template<class Message> void RegisterMessageKind(int event, const char* name);
	}
}

#endif
