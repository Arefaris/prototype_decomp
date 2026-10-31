// Fight items of the proplogic group: OnCollisionTrack, WaitOnCollisionTrack (unit 0x1025EFA0 - 0x1025FC60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PROPLOGIC_PROPLOGIC_ONCOLLISION_H
#define PROTO_FIGHTITEMS_PROPLOGIC_PROPLOGIC_ONCOLLISION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/proplogic/proplogicdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace proplogic
		{
			// RTTI: proto::fightitems::proplogic::OnCollisionTrack (16 vftable slots, 0x4C bytes)
			class OnCollisionTrack : public fight::Track
			{
			public:
				// 0x1025F0E0
				OnCollisionTrack();
				virtual ~OnCollisionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1025EBA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetCollideWith(int newValue);
				bool SetImpulseThreshold(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float impulseThreshold;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					int priority;  // +0x44
					int collideWith;  // +0x48
			};

			extern fight::Property** gOnCollisionTrackProperties;
			fight::TrackFactory* CreateOnCollisionTrackFactory(const char* name);
			void RegisterOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::proplogic::WaitOnCollisionTrack (16 vftable slots, 0x20 bytes)
			class WaitOnCollisionTrack : public fight::Track
			{
			public:
				// 0x1025F1D0
				WaitOnCollisionTrack();
				virtual ~WaitOnCollisionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1025EB00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetCollideWith(int newValue);
				bool SetImpulseThreshold(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float impulseThreshold;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					int collideWith;  // +0x1C
			};

			extern fight::Property** gWaitOnCollisionTrackProperties;
			fight::TrackFactory* CreateWaitOnCollisionTrackFactory(const char* name);
			void RegisterWaitOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
