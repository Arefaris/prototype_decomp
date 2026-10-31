// Fight items of the ai group: ConfigureScaryMonsterBehaviourTrack, ActivateScaryMonsterBehaviourTrack (unit 0x1021AB50 - 0x1021B3C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_SCARYMONSTER_H
#define PROTO_FIGHTITEMS_AI_AI_SCARYMONSTER_H

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
			// RTTI: proto::fightitems::ai::ConfigureScaryMonsterBehaviourTrack (16 vftable slots, 0x24 bytes)
			class ConfigureScaryMonsterBehaviourTrack : public fight::Track
			{
			public:
				// 0x1021AB80
				ConfigureScaryMonsterBehaviourTrack();
				virtual ~ConfigureScaryMonsterBehaviourTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101DDEC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIntensity(float newValue);
				bool SetVelocityOffset(float newValue);
				bool SetFrequency(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float intensity;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					float velocityOffset;  // +0x1C
					int frequency;  // +0x20
			};

			extern fight::Property** gConfigureScaryMonsterBehaviourTrackProperties;
			fight::TrackFactory* CreateConfigureScaryMonsterBehaviourTrackFactory(const char* name);
			void RegisterConfigureScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ActivateScaryMonsterBehaviourTrack (16 vftable slots, 0x1C bytes)
			class ActivateScaryMonsterBehaviourTrack : public fight::Track
			{
			public:
				// 0x1021AC30
				ActivateScaryMonsterBehaviourTrack();
				virtual ~ActivateScaryMonsterBehaviourTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101DDE70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetActivate(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool activate;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gActivateScaryMonsterBehaviourTrackProperties;
			fight::TrackFactory* CreateActivateScaryMonsterBehaviourTrackFactory(const char* name);
			void RegisterActivateScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ConfigureScaryMonsterBehaviourAction (9 vftable slots, 0x2C bytes)
			class ConfigureScaryMonsterBehaviourAction : public fight::Action
			{
			public:
				// 0x101DDD20
				ConfigureScaryMonsterBehaviourAction(ConfigureScaryMonsterBehaviourTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DDA00
				virtual ~ConfigureScaryMonsterBehaviourAction();

				// vftable slot 5 (0x101DDDD0)
				virtual bool Slot5(int arg, float value);

				core::Link<ConfigureScaryMonsterBehaviourTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ActivateScaryMonsterBehaviourAction (9 vftable slots, 0x2C bytes)
			class ActivateScaryMonsterBehaviourAction : public fight::Action
			{
			public:
				// 0x101DDB00
				ActivateScaryMonsterBehaviourAction(ActivateScaryMonsterBehaviourTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DD9B0
				virtual ~ActivateScaryMonsterBehaviourAction();

				// vftable slot 5 (0x101DDBB0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101DDC70)
				virtual void Slot6();
				// vftable slot 7 (0x101DD800)
				virtual bool Slot7(int arg, float value);

				core::Link<ActivateScaryMonsterBehaviourTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
