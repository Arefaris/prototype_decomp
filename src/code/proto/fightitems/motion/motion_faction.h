// Fight items of the motion group: FactionTypeCondition, FactionCondition, FactionSetTrack, FactionDefaultTrack (unit 0x1015D620 - 0x1015E4B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_FACTION_H
#define PROTO_FIGHTITEMS_MOTION_FACTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FactionTypeCondition (10 vftable slots, 0x14 bytes)
			class FactionTypeCondition : public fight::Condition
			{
			public:
				// 0x1015D6B0
				FactionTypeCondition();
				virtual ~FactionTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100BB8E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetFactionType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int factionType;  // +0x10
			};

			extern fight::Property** gFactionTypeConditionProperties;
			fight::ConditionFactory* CreateFactionTypeConditionFactory(const char* name);
			void RegisterFactionTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::FactionCondition (10 vftable slots, 0x20 bytes)
			class FactionCondition : public fight::Condition
			{
			public:
				// 0x1015D8A0
				FactionCondition();
				virtual ~FactionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100BB820, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetFaction(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name faction;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gFactionConditionProperties;
			fight::ConditionFactory* CreateFactionConditionFactory(const char* name);
			void RegisterFactionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::FactionSetTrack (16 vftable slots, 0x20 bytes)
			class FactionSetTrack : public fight::Track
			{
			public:
				// 0x1015D8E0
				FactionSetTrack();
				virtual ~FactionSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BBE10, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetFaction(const fight::Name& newValue);
				bool SetNotifyAI(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name faction;  // +0x10
					float timeBegin;  // +0x18
					bool notifyAI;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gFactionSetTrackProperties;
			fight::TrackFactory* CreateFactionSetTrackFactory(const char* name);
			void RegisterFactionSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::FactionDefaultTrack (16 vftable slots, 0x10 bytes)
			class FactionDefaultTrack : public fight::Track
			{
			public:
				// 0x1015D7E0
				FactionDefaultTrack();
				virtual ~FactionDefaultTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BBE60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gFactionDefaultTrackProperties;
			fight::TrackFactory* CreateFactionDefaultTrackFactory(const char* name);
			void RegisterFactionDefaultTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::FactionDefaultAction (9 vftable slots, 0x2C bytes)
			class FactionDefaultAction : public fight::Action
			{
			public:
				// 0x100BBC80
				FactionDefaultAction(FactionDefaultTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BB7F0
				virtual ~FactionDefaultAction();

				// vftable slot 5 (0x100BBD30)
				virtual bool Slot5(int arg, float value);

				core::Link<FactionDefaultTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::FactionSetAction (9 vftable slots, 0x2C bytes)
			class FactionSetAction : public fight::Action
			{
			public:
				// 0x100BBA90
				FactionSetAction(FactionSetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BB7A0
				virtual ~FactionSetAction();

				// vftable slot 5 (0x100BBB40)
				virtual bool Slot5(int arg, float value);

				core::Link<FactionSetTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
