// Fight items of the motion group: DecalTrack (unit 0x10153160 - 0x10153950; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DECAL_H
#define PROTO_FIGHTITEMS_MOTION_DECAL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DecalTrack (16 vftable slots, 0x48 bytes)
			class DecalTrack : public fight::Track
			{
			public:
				// 0x101532D0
				DecalTrack();
				virtual ~DecalTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B1030, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetShaderName(const fight::Name& newValue);
				bool SetOrientation(float newValue);
				bool SetScaleX(float newValue);
				bool SetScaleY(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetPositionOffset(const math::Vector& newValue);
				bool SetMaxDistance(float newValue);
				bool SetMinNormalArc(float newValue);
				bool SetFadeOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					fight::Name shaderName;  // +0x18
					math::Vector positionOffset;  // +0x20
					float fadeOutTime;  // +0x2C
					float maxDistance;  // +0x30
					float minNormalArc;  // +0x34
					float orientation;  // +0x38
					float scaleX;  // +0x3C
					float scaleY;  // +0x40
					float timeBegin;  // +0x44
			};

			extern fight::Property** gDecalTrackProperties;
			fight::TrackFactory* CreateDecalTrackFactory(const char* name);
			void RegisterDecalTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
