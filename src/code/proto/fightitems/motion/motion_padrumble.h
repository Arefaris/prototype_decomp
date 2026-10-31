// Fight items of the motion group: PadRumbleSetTrack, PadRumbleRefTrack, PadRumbleClearTrack (unit 0x101998F0 - 0x1019A8A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PADRUMBLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PADRUMBLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::PadRumbleSetTrack (16 vftable slots, 0x38 bytes)
			class PadRumbleSetTrack : public fight::Track
			{
			public:
				// 0x10199AC0
				PadRumbleSetTrack();
				virtual ~PadRumbleSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10100A40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMotor(int newValue);
				bool SetScale(float newValue);
				bool SetFadeInTime(float newValue);
				bool SetHoldTime(float newValue);
				bool SetFadeOutTime(float newValue);
				bool SetUseObjectPos(bool newValue);
				bool SetFullIntensityRadius(float newValue);
				bool SetFallOffRadius(float newValue);
				bool SetCancelOnTrackEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fadeInTime;  // +0x10
					float fadeOutTime;  // +0x14
					float fallOffRadius;  // +0x18
					float fullIntensityRadius;  // +0x1C
					float holdTime;  // +0x20
					float scale;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					int motor;  // +0x30
					bool cancelOnTrackEnd;  // +0x34
					bool useObjectPos;  // +0x35
					unsigned char unknown36[0x2];
			};

			extern fight::Property** gPadRumbleSetTrackProperties;
			fight::TrackFactory* CreatePadRumbleSetTrackFactory(const char* name);
			void RegisterPadRumbleSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PadRumbleRefTrack (16 vftable slots, 0x3C bytes)
			class PadRumbleRefTrack : public fight::Track
			{
			public:
				// 0x10199BB0
				PadRumbleRefTrack();
				virtual ~PadRumbleRefTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10100B40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				fight::BranchHolder* SetBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
			};

			extern fight::Property** gPadRumbleRefTrackProperties;
			fight::TrackFactory* CreatePadRumbleRefTrackFactory(const char* name);
			void RegisterPadRumbleRefTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PadRumbleClearTrack (16 vftable slots, 0x14 bytes)
			class PadRumbleClearTrack : public fight::Track
			{
			public:
				// 0x10199C70
				PadRumbleClearTrack();
				virtual ~PadRumbleClearTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101009F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gPadRumbleClearTrackProperties;
			fight::TrackFactory* CreatePadRumbleClearTrackFactory(const char* name);
			void RegisterPadRumbleClearTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
