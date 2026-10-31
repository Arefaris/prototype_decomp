// Fight items of the ai group: PeriodicMessageTrack, MessageTrack, BlindTrack (unit 0x1023A830 - 0x1023BC30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_MESSAGE_H
#define PROTO_FIGHTITEMS_AI_AI_MESSAGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::PeriodicMessageTrack (16 vftable slots, 0x30 bytes)
			class PeriodicMessageTrack : public fight::Track
			{
			public:
				// 0x1023AA00
				PeriodicMessageTrack();
				virtual ~PeriodicMessageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FE2C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetType(int newValue);
				bool SetIntensity(float newValue);
				bool SetTaker(int newValue);
				bool SetGiver(int newValue);
				bool SetUseOriginator(bool newValue);
				bool SetPeriod(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float intensity;  // +0x10
					float period;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					int giver;  // +0x20
					int taker;  // +0x24
					int type;  // +0x28
					bool useOriginator;  // +0x2C
					unsigned char unknown2D[0x3];
			};

			extern fight::Property** gPeriodicMessageTrackProperties;
			fight::TrackFactory* CreatePeriodicMessageTrackFactory(const char* name);
			void RegisterPeriodicMessageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::MessageTrack (16 vftable slots, 0x30 bytes)
			class MessageTrack : public fight::Track
			{
			public:
				// 0x1023AB60
				MessageTrack();
				virtual ~MessageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FE230, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetType(int newValue);
				bool SetIntensity(float newValue);
				bool SetTaker(int newValue);
				bool SetUseOriginator(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float intensity;  // +0x18
					float timeBegin;  // +0x1C
					int taker;  // +0x20
					int type;  // +0x24
					bool useOriginator;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gMessageTrackProperties;
			fight::TrackFactory* CreateMessageTrackFactory(const char* name);
			void RegisterMessageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::BlindTrack (16 vftable slots, 0x28 bytes)
			class BlindTrack : public fight::Track
			{
			public:
				// 0x1023ABE0
				BlindTrack();
				virtual ~BlindTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FE350, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTaker(int newValue);
				bool SetBlind(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetUndoOnEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					int taker;  // +0x20
					bool blind;  // +0x24
					bool undoOnEnd;  // +0x25
					unsigned char unknown26[0x2];
			};

			extern fight::Property** gBlindTrackProperties;
			fight::TrackFactory* CreateBlindTrackFactory(const char* name);
			void RegisterBlindTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
