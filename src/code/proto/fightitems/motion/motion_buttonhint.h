// Fight items of the motion group: ButtonHintShowingCondition, EnableButtonHintsTrack, ButtonHintShowTrack (unit 0x10146A60 - 0x101479B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_BUTTONHINT_H
#define PROTO_FIGHTITEMS_MOTION_BUTTONHINT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ButtonHintShowingCondition (10 vftable slots, 0x18 bytes)
			class ButtonHintShowingCondition : public fight::Condition
			{
			public:
				// 0x10146C80
				ButtonHintShowingCondition();
				virtual ~ButtonHintShowingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100A03A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetButtonHint(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name buttonHint;  // +0x10
			};

			extern fight::Property** gButtonHintShowingConditionProperties;
			fight::ConditionFactory* CreateButtonHintShowingConditionFactory(const char* name);
			void RegisterButtonHintShowingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::EnableButtonHintsTrack (16 vftable slots, 0x18 bytes)
			class EnableButtonHintsTrack : public fight::Track
			{
			public:
				// 0x10146B80
				EnableButtonHintsTrack();
				virtual ~EnableButtonHintsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A0A50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gEnableButtonHintsTrackProperties;
			fight::TrackFactory* CreateEnableButtonHintsTrackFactory(const char* name);
			void RegisterEnableButtonHintsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ButtonHintShowTrack (16 vftable slots, 0x38 bytes)
			class ButtonHintShowTrack : public fight::Track
			{
			public:
				// 0x10146CF0
				ButtonHintShowTrack();
				virtual ~ButtonHintShowTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A0A00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetButton(int newValue);
				bool SetPressType(int newValue);
				bool SetDisplayMessage(const char* newValue);
				bool SetScenarioMessage(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetPersistent(bool newValue);
				// 0x1009FF10 (another unit)
				const fight::EnumEntry* GetButtonEntry(int index);
				// 0x1009FF30 (another unit)
				int GetButtonCount();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name scenarioMessage;  // +0x10
					char* displayMessage;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					int button;  // +0x24
					int pressType;  // +0x28
					int priority;  // +0x2C
					bool persistent;  // +0x30
					unsigned char unknown31[0x7];
			};

			extern fight::Property** gButtonHintShowTrackProperties;
			fight::TrackFactory* CreateButtonHintShowTrackFactory(const char* name);
			void RegisterButtonHintShowTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
