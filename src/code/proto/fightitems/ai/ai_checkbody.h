// Fight items of the ai group: CheckBodyTrack (unit 0x1021C920 - 0x1021CD90; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_CHECKBODY_H
#define PROTO_FIGHTITEMS_AI_AI_CHECKBODY_H

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
			// RTTI: proto::fightitems::ai::CheckBodyTrack (16 vftable slots, 0x20 bytes)
			class CheckBodyTrack : public fight::Track
			{
			public:
				// 0x1021C9D0
				CheckBodyTrack();
				virtual ~CheckBodyTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E0030, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetStopDistance(float newValue);
				bool SetTimeCheckingBody(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float stopDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeCheckingBody;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gCheckBodyTrackProperties;
			fight::TrackFactory* CreateCheckBodyTrackFactory(const char* name);
			void RegisterCheckBodyTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::CheckBodyAction (9 vftable slots, 0x2C bytes)
			class CheckBodyAction : public fight::Action
			{
			public:
				// 0x101DFB80
				CheckBodyAction(CheckBodyTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DFAA0
				virtual ~CheckBodyAction();

				// vftable slot 5 (0x101DFC20)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101DFAD0)
				virtual void Slot6();
				// vftable slot 7 (0x101DFD50)
				virtual bool Slot7(int arg, float value);

				core::Link<CheckBodyTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0xC];
				bool unknown38;  // +0x38
				unsigned char unknown39[0x3];
				float unknown3C;  // +0x3C
			};

			// ---- actions end
		}
	}
}

#endif
