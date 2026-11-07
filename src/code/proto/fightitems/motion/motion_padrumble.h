// Fight items of the motion group: PadRumbleSetTrack, PadRumbleRefTrack, PadRumbleClearTrack (unit 0x101998F0 - 0x1019A8A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PADRUMBLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PADRUMBLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				int GetMotor() const;
				float GetScale() const;
				float GetFadeInTime() const;
				float GetHoldTime() const;
				float GetFadeOutTime() const;
				bool GetUseObjectPos() const;
				float GetFullIntensityRadius() const;
				float GetFallOffRadius() const;
				bool GetCancelOnTrackEnd() const;

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

			// 0x10FF83F4: the controller motor the track's motor property picks (name guess)
			extern const int gPadRumbleSetTrackMotorIndex[];

			// ---- actions begin
			// 0x101001B0: stops the vibration of both motors of the first active controller (name guess)
			void StopPadRumble();

			// What a track owner of kind 0x40000 holds: a position
			struct PadRumbleOwnerPoint : TrackOwner
			{
				unsigned char unknown10[0x30];
				math::Vector position;  // +0x40
			};

			// RTTI: proto::fightitems::motion::PadRumbleSetAction (9 vftable slots, 0x38 bytes): vibrates the pad for as long as the track runs
			class PadRumbleSetAction : public fight::Action
			{
			public:
				// 0x10100660
				PadRumbleSetAction(PadRumbleSetTrack* newTrack);
				// 0x101003F0
				virtual ~PadRumbleSetAction();

				// vftable slot 5 (0x10100710)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101008B0)
				virtual void Slot6();
				// vftable slot 7 (0x10100140)
				virtual bool Slot7(int arg, float value);

				// 0x10100110: the world position the rumble comes from
				void SetPosition(const math::Vector& newPosition);

				core::Link<PadRumbleSetTrack> link;  // +0x1C
				math::Vector position;  // +0x28
				bool usePosition;  // +0x34
			};

			// RTTI: proto::fightitems::motion::PadRumbleRefAction (9 vftable slots, 0x78 bytes): runs the track's branch in its own sequencer
			class PadRumbleRefAction : public fight::Action
			{
			public:
				// 0x101008D0
				PadRumbleRefAction(fight::Track* listener, PadRumbleRefTrack* newTrack, int newEffect, core::IRefCount* newOwner);
				// 0x10100440
				virtual ~PadRumbleRefAction();

				// vftable slot 3 (0x10100150)
				virtual fight::Sequencer* GetChild();
				// vftable slot 5 (0x101009A0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10100160)
				virtual void Slot6();

				core::Link<PadRumbleRefTrack> link;  // +0x1C
				int effect;  // +0x28
				core::IRefCount* owner;  // +0x2C
				fight::Sequencer sequencer;  // +0x30
			};

			// RTTI: proto::fightitems::motion::PadRumbleClearAction (9 vftable slots, 0x2C bytes)
			class PadRumbleClearAction : public fight::Action
			{
			public:
				// 0x101005B0
				PadRumbleClearAction(PadRumbleClearTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101003A0
				virtual ~PadRumbleClearAction();

				// vftable slot 5 (0x10100200)
				virtual bool Slot5(int arg, float value);

				core::Link<PadRumbleClearTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// 0x101000D0
			void RegisterPadRumbleClearFactories(fight::TrackRegistry* registry);

			// ---- actions end
		}
	}
}

#endif
