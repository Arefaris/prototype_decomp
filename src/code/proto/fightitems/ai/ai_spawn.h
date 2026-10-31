// Fight items of the ai group: SpawnTemplateCondition, ShouldSpawnCondition, ObjectSpawnedTrack (unit 0x10249C30 - 0x1024A810; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_SPAWN_H
#define PROTO_FIGHTITEMS_AI_AI_SPAWN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::SpawnTemplateCondition (10 vftable slots, 0x20 bytes)
			class SpawnTemplateCondition : public fight::Condition
			{
			public:
				// 0x10249DA0
				SpawnTemplateCondition();
				virtual ~SpawnTemplateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1020AF10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTemplateName(const fight::Name& newValue);
				bool SetCompare(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name templateName;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gSpawnTemplateConditionProperties;
			fight::ConditionFactory* CreateSpawnTemplateConditionFactory(const char* name);
			void RegisterSpawnTemplateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ShouldSpawnCondition (10 vftable slots, 0x10 bytes)
			class ShouldSpawnCondition : public fight::Condition
			{
			public:
				// 0x10249D00
				ShouldSpawnCondition();
				virtual ~ShouldSpawnCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1020AE60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetShould(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool should;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gShouldSpawnConditionProperties;
			fight::ConditionFactory* CreateShouldSpawnConditionFactory(const char* name);
			void RegisterShouldSpawnConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ObjectSpawnedTrack (16 vftable slots, 0x28 bytes)
			class ObjectSpawnedTrack : public fight::Track
			{
			public:
				// 0x10249E10
				ObjectSpawnedTrack();
				virtual ~ObjectSpawnedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020B220, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetLastGuy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					bool lastGuy;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gObjectSpawnedTrackProperties;
			fight::TrackFactory* CreateObjectSpawnedTrackFactory(const char* name);
			void RegisterObjectSpawnedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ObjectSpawnedAction (9 vftable slots, 0x2C bytes)
			class ObjectSpawnedAction : public fight::Action
			{
			public:
				// 0x1020B040
				ObjectSpawnedAction(ObjectSpawnedTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1020AE30
				virtual ~ObjectSpawnedAction();

				// vftable slot 5 (0x1020B0F0)
				virtual bool Slot5(int arg, float value);

				core::Link<ObjectSpawnedTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
