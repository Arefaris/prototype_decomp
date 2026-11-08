// Fight items of the ai group: FleeTrack (unit 0x10231FB0 - 0x10232390; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_FLEE_H
#define PROTO_FIGHTITEMS_AI_AI_FLEE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::FleeTrack (16 vftable slots, 0x1C bytes)
			class FleeTrack : public fight::Track
			{
			public:
				// 0x10232040
				FleeTrack();
				virtual ~FleeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F3470, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFleeDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fleeDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gFleeTrackProperties;
			fight::TrackFactory* CreateFleeTrackFactory(const char* name);
			void RegisterFleeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::ai::FleeAction (9 vftable slots, 0x40 bytes)
			class FleeAction : public fight::Action
			{
			public:
				// 0x101F3270
				FleeAction(FleeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F3100
				virtual ~FleeAction();

				// vftable slot 5 (0x101F3020)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F3040)
				virtual void Slot6();
				// vftable slot 7 (0x101F3680)
				virtual bool Slot7(int arg, float value);

				// 0x101F3320: runs along a direction away from the threat and enters the state of fleeing (name guess)
				void Flee(const math::Vector* direction);
				// 0x101F33A0: runs directly away from the threat (name guess)
				void FleeFromThreat();
				// 0x101F3130: keeps the object running directly away from the threat (name guess)
				bool KeepFleeing(engine::GameObject* object, float time);
				// 0x101F34C0: picks the object's target as the threat and starts to flee from it (name guess)
				bool StartFleeing(engine::GameObject* object, float time);

				int unknown1C;  // +0x1C
				engine::GameObjectHandle unknown20;  // +0x20
				math::Vector direction;  // +0x24
				core::Link<FleeTrack> link;  // +0x30
				engine::GameObjectHandle target;  // +0x3C
			};
			// ---- actions end
		}
	}
}

#endif
