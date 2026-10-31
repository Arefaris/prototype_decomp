// Fight items of the motion group: ReactionHitApplyImpulseTrack (unit 0x101A9F10 - 0x101AA2B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONHITAPPLYIMPULSE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONHITAPPLYIMPULSE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionHitApplyImpulseTrack (16 vftable slots, 0x18 bytes)
			class ReactionHitApplyImpulseTrack : public fight::Track
			{
			public:
				// 0x101A9F80
				ReactionHitApplyImpulseTrack();
				virtual ~ReactionHitApplyImpulseTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010D950, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetImpulseScale(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float impulseScale;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gReactionHitApplyImpulseTrackProperties;
			fight::TrackFactory* CreateReactionHitApplyImpulseTrackFactory(const char* name);
			void RegisterReactionHitApplyImpulseTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
