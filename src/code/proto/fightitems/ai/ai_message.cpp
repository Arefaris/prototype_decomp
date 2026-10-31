// Fight items of the ai group: PeriodicMessageTrack, MessageTrack, BlindTrack (unit 0x1023A830 - 0x1023BC30; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_message.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gPeriodicMessageTrackProperties;  // 0x11255A80

			// FUNCTION: ENGINE 0x1023A830
			bool PeriodicMessageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A850
			bool PeriodicMessageTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A870
			bool PeriodicMessageTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A880
			bool PeriodicMessageTrack::SetIntensity(float newValue)
			{
				intensity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A8A0
			bool PeriodicMessageTrack::SetTaker(int newValue)
			{
				taker = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A8B0
			bool PeriodicMessageTrack::SetGiver(int newValue)
			{
				giver = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A8C0
			bool PeriodicMessageTrack::SetUseOriginator(bool newValue)
			{
				useOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A8D0
			bool PeriodicMessageTrack::SetPeriod(float newValue)
			{
				period = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A9D0
			fight::Property* PeriodicMessageTrack::GetProperty(int index)
			{
				return gPeriodicMessageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023A9F0
			void PeriodicMessageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPeriodicMessageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023AA00
			PeriodicMessageTrack::PeriodicMessageTrack() : intensity(1.0f), period(0.0f), timeBegin(0.0f), timeEnd(-1.0f), giver(0), taker(0), type(0), useOriginator(false)
			{
			}

			// FUNCTION: ENGINE 0x1023AA60
			float PeriodicMessageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023AA70
			float PeriodicMessageTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023AA80
			PeriodicMessageTrack::~PeriodicMessageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1023B290
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PeriodicMessageTrack::RegisterProperties()
			{
				if (gPeriodicMessageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PeriodicMessageTrack>("timeBegin", &PeriodicMessageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PeriodicMessageTrack>("timeEnd", &PeriodicMessageTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<PeriodicMessageTrack>("type", motion::gPedestrianAlertStateConditionStateTable, motion::gPedestrianAlertStateConditionStateCount, &PeriodicMessageTrack::SetType);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PeriodicMessageTrack>("intensity", &PeriodicMessageTrack::SetIntensity);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<PeriodicMessageTrack>("taker", gPeriodicMessageTrackTakerTable, gPeriodicMessageTrackTakerCount, &PeriodicMessageTrack::SetTaker);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<PeriodicMessageTrack>("giver", gPeriodicMessageTrackTakerTable, gPeriodicMessageTrackTakerCount, &PeriodicMessageTrack::SetGiver);
					properties[5] = property;
					property = new fight::PropertyBool<PeriodicMessageTrack>("useOriginator", &PeriodicMessageTrack::SetUseOriginator);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<PeriodicMessageTrack>("period", &PeriodicMessageTrack::SetPeriod);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gPeriodicMessageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023B200
			fight::TrackFactory* CreatePeriodicMessageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PeriodicMessageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023B520
			void RegisterPeriodicMessageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PeriodicMessageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMessageTrackProperties;  // 0x11255A84

			// FUNCTION: ENGINE 0x1023A8F0
			bool MessageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A910
			bool MessageTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A920
			bool MessageTrack::SetIntensity(float newValue)
			{
				intensity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A940
			bool MessageTrack::SetTaker(int newValue)
			{
				taker = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A950
			bool MessageTrack::SetUseOriginator(bool newValue)
			{
				useOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023AAF0
			bool MessageTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023AA90
			fight::Property* MessageTrack::GetProperty(int index)
			{
				return gMessageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023AAB0
			void MessageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMessageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023AB60
			MessageTrack::MessageTrack() : intensity(1.0f), timeBegin(0.0f), taker(0), type(0), useOriginator(false)
			{
			}

			// FUNCTION: ENGINE 0x1023ABB0
			float MessageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023ABC0
			float MessageTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1023ABD0
			MessageTrack::~MessageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1023B6C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MessageTrack::RegisterProperties()
			{
				if (gMessageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MessageTrack>("timeBegin", &MessageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<MessageTrack>("type", motion::gPedestrianAlertStateConditionStateTable, motion::gPedestrianAlertStateConditionStateCount, &MessageTrack::SetType);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MessageTrack>("intensity", &MessageTrack::SetIntensity);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<MessageTrack>("taker", gPeriodicMessageTrackTakerTable, gPeriodicMessageTrackTakerCount, &MessageTrack::SetTaker);
					properties[3] = property;
					property = new fight::PropertyBool<MessageTrack>("useOriginator", &MessageTrack::SetUseOriginator);
					properties[4] = property;
					property = new fight::PropertyNameList<MessageTrack>("grabSlot", &MessageTrack::SetGrabSlot);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gMessageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023B230
			fight::TrackFactory* CreateMessageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MessageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023B550
			void RegisterMessageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MessageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gBlindTrackProperties;  // 0x11255A88

			// FUNCTION: ENGINE 0x1023A960
			bool BlindTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A980
			bool BlindTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A9A0
			bool BlindTrack::SetTaker(int newValue)
			{
				taker = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A9B0
			bool BlindTrack::SetBlind(bool newValue)
			{
				blind = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023AB10
			bool BlindTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A9C0
			bool BlindTrack::SetUndoOnEnd(bool newValue)
			{
				undoOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023AAC0
			fight::Property* BlindTrack::GetProperty(int index)
			{
				return gBlindTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023AAE0
			void BlindTrack::ClearProperties()
			{
				fight::FreePropertyList(&gBlindTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023ABE0
			BlindTrack::BlindTrack() : timeBegin(0.0f), timeEnd(-1.0f), taker(0), blind(true), undoOnEnd(false)
			{
			}

			// FUNCTION: ENGINE 0x1023AC30
			float BlindTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023AC40
			float BlindTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023AC50
			BlindTrack::~BlindTrack()
			{
			}

			// FUNCTION: ENGINE 0x1023B8C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void BlindTrack::RegisterProperties()
			{
				if (gBlindTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<BlindTrack>("timeBegin", &BlindTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<BlindTrack>("timeEnd", &BlindTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<BlindTrack>("taker", gPeriodicMessageTrackTakerTable, gPeriodicMessageTrackTakerCount, &BlindTrack::SetTaker);
					properties[2] = property;
					property = new fight::PropertyBool<BlindTrack>("blind", &BlindTrack::SetBlind);
					properties[3] = property;
					property = new fight::PropertyNameList<BlindTrack>("grabSlot", &BlindTrack::SetGrabSlot);
					properties[4] = property;
					property = new fight::PropertyBool<BlindTrack>("undoOnEnd", &BlindTrack::SetUndoOnEnd);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gBlindTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023B260
			fight::TrackFactory* CreateBlindTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlindTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023B580
			void RegisterBlindTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlindTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101FDF90
			BlindAction::BlindAction(BlindTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FD800
			BlindAction::~BlindAction()
			{
			}

			// FUNCTION: ENGINE 0x101FE350
			fight::Action* BlindTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new BlindAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<PeriodicMessageTrack>;
			template class fight::PropertyEnumConstList<PeriodicMessageTrack>;
			template class fight::PropertyBool<PeriodicMessageTrack>;
			template class fight::TrackFactoryTemplate<PeriodicMessageTrack>;
			template class fight::TrackFactoryCasterTemplate<PeriodicMessageTrack>;
			template class fight::PropertyFloatConstRange<MessageTrack>;
			template class fight::PropertyEnumConstList<MessageTrack>;
			template class fight::PropertyBool<MessageTrack>;
			template class fight::PropertyNameList<MessageTrack>;
			template class fight::TrackFactoryTemplate<MessageTrack>;
			template class fight::TrackFactoryCasterTemplate<MessageTrack>;
			template class fight::PropertyFloatConstRange<BlindTrack>;
			template class fight::PropertyEnumConstList<BlindTrack>;
			template class fight::PropertyBool<BlindTrack>;
			template class fight::PropertyNameList<BlindTrack>;
			template class fight::TrackFactoryTemplate<BlindTrack>;
			template class fight::TrackFactoryCasterTemplate<BlindTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1023AB30
// FUNCTION: ENGINE 0x1023AC60
// FUNCTION: ENGINE 0x1023AC70
// FUNCTION: ENGINE 0x1023ACA0
// FUNCTION: ENGINE 0x1023ACB0
// FUNCTION: ENGINE 0x1023ACE0
// FUNCTION: ENGINE 0x1023ACF0
// FUNCTION: ENGINE 0x1023AD20
// FUNCTION: ENGINE 0x1023AD50
// FUNCTION: ENGINE 0x1023AD80
// FUNCTION: ENGINE 0x1023ADB0
// FUNCTION: ENGINE 0x1023ADE0
// FUNCTION: ENGINE 0x1023ADF0
// FUNCTION: ENGINE 0x1023AE30
// FUNCTION: ENGINE 0x1023AE40
// FUNCTION: ENGINE 0x1023AE70
// FUNCTION: ENGINE 0x1023AE90
// FUNCTION: ENGINE 0x1023AEA0
// FUNCTION: ENGINE 0x1023AED0
// FUNCTION: ENGINE 0x1023AEF0
// FUNCTION: ENGINE 0x1023AF00
// FUNCTION: ENGINE 0x1023AF30
// FUNCTION: ENGINE 0x1023AF60
// FUNCTION: ENGINE 0x1023AF70
// FUNCTION: ENGINE 0x1023AFB0
// FUNCTION: ENGINE 0x1023AFC0
// FUNCTION: ENGINE 0x1023AFF0
// FUNCTION: ENGINE 0x1023B010
// FUNCTION: ENGINE 0x1023B020
// FUNCTION: ENGINE 0x1023B050
// FUNCTION: ENGINE 0x1023B070
// FUNCTION: ENGINE 0x1023B080
// FUNCTION: ENGINE 0x1023B0B0
// FUNCTION: ENGINE 0x1023B0E0
// FUNCTION: ENGINE 0x1023B0F0
// FUNCTION: ENGINE 0x1023B130
// FUNCTION: ENGINE 0x1023B140
// FUNCTION: ENGINE 0x1023B170
// FUNCTION: ENGINE 0x1023B190
// FUNCTION: ENGINE 0x1023B1A0
// FUNCTION: ENGINE 0x1023B1D0
// FUNCTION: ENGINE 0x1023B1F0
// FUNCTION: ENGINE 0x1023B5B0
// FUNCTION: ENGINE 0x1023B5E0
// FUNCTION: ENGINE 0x1023B600
// FUNCTION: ENGINE 0x1023B610
// FUNCTION: ENGINE 0x1023B640
// FUNCTION: ENGINE 0x1023B660
// FUNCTION: ENGINE 0x1023B670
// FUNCTION: ENGINE 0x1023B6A0
// FUNCTION: ENGINE 0x1023BAA0
// FUNCTION: ENGINE 0x1023BAF0
// FUNCTION: ENGINE 0x1023BB20
// FUNCTION: ENGINE 0x1023BB40
// FUNCTION: ENGINE 0x1023BB70
// FUNCTION: ENGINE 0x1023BB90
// FUNCTION: ENGINE 0x1023BBE0
