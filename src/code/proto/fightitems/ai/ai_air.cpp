// Fight items of the ai group: AirHoverTrack, AirDodgeTrack (unit 0x1021BA30 - 0x1021C6F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_air.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gAirHoverTrackProperties;  // 0x1125581C

			// FUNCTION: ENGINE 0x1021BA30
			bool AirHoverTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BA50
			bool AirHoverTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BA70
			bool AirHoverTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BA90
			bool AirHoverTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BAB0
			bool AirHoverTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BAD0
			bool AirHoverTrack::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BAF0
			bool AirHoverTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BB10
			bool AirHoverTrack::SetShootingDistance(float newValue)
			{
				shootingDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BB30
			bool AirHoverTrack::SetUseMissiles(bool newValue)
			{
				useMissiles = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BB40
			bool AirHoverTrack::SetMinFireTime(float newValue)
			{
				minFireTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BB60
			bool AirHoverTrack::SetMaxFireTime(float newValue)
			{
				maxFireTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BB80
			bool AirHoverTrack::SetMinWaitTime(float newValue)
			{
				minWaitTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BBA0
			bool AirHoverTrack::SetMaxWaitTime(float newValue)
			{
				maxWaitTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BC10
			fight::Property* AirHoverTrack::GetProperty(int index)
			{
				return gAirHoverTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021BC30
			void AirHoverTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAirHoverTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021BC40
			AirHoverTrack::AirHoverTrack() : distanceMax(2e+01f), distanceMin(1e+01f), heightMax(15.0f), heightMin(1e+01f), maxFireTime(6.0f), maxWaitTime(3.0f), minFireTime(5.0f), minWaitTime(2.0f), shootingDistance(2e+01f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), useMissiles(false)
			{
			}

			// FUNCTION: ENGINE 0x1021BD10
			float AirHoverTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021BD20
			float AirHoverTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021BD30
			AirHoverTrack::~AirHoverTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021C0C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AirHoverTrack::RegisterProperties()
			{
				if (gAirHoverTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("timeBegin", &AirHoverTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("timeEnd", &AirHoverTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("distanceMin", &AirHoverTrack::SetDistanceMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("distanceMax", &AirHoverTrack::SetDistanceMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("heightMin", &AirHoverTrack::SetHeightMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("heightMax", &AirHoverTrack::SetHeightMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("speed", &AirHoverTrack::SetSpeed);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("shootingDistance", &AirHoverTrack::SetShootingDistance);
					properties[7] = property;
					property = new fight::PropertyBool<AirHoverTrack>("useMissiles", &AirHoverTrack::SetUseMissiles);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("minFireTime", &AirHoverTrack::SetMinFireTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("maxFireTime", &AirHoverTrack::SetMaxFireTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("minWaitTime", &AirHoverTrack::SetMinWaitTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<AirHoverTrack>("maxWaitTime", &AirHoverTrack::SetMaxWaitTime);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gAirHoverTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021C060
			fight::TrackFactory* CreateAirHoverTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AirHoverTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021C550
			void RegisterAirHoverTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AirHoverTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAirDodgeTrackProperties;  // 0x11255820

			// FUNCTION: ENGINE 0x1021BBC0
			bool AirDodgeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BBE0
			bool AirDodgeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BC00
			bool AirDodgeTrack::SetUseDirection(bool newValue)
			{
				useDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021BD40
			fight::Property* AirDodgeTrack::GetProperty(int index)
			{
				return gAirDodgeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021BD60
			void AirDodgeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAirDodgeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021BD70
			AirDodgeTrack::AirDodgeTrack() : timeBegin(0.0f), timeEnd(-1.0f), useDirection(false)
			{
			}

			// FUNCTION: ENGINE 0x1021BDB0
			float AirDodgeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021BDC0
			float AirDodgeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021BDD0
			AirDodgeTrack::~AirDodgeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021C440
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AirDodgeTrack::RegisterProperties()
			{
				if (gAirDodgeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AirDodgeTrack>("timeBegin", &AirDodgeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AirDodgeTrack>("timeEnd", &AirDodgeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<AirDodgeTrack>("useDirection", &AirDodgeTrack::SetUseDirection);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAirDodgeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021C090
			fight::TrackFactory* CreateAirDodgeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AirDodgeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021C580
			void RegisterAirDodgeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AirDodgeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101DEBA0
			AirHoverAction::AirHoverAction(AirHoverTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown38(false), unknown39(false), unknown3C(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101DE980
			AirHoverAction::~AirHoverAction()
			{
			}

			// FUNCTION: ENGINE 0x101DE520
			bool AirHoverAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101DE530
			void AirHoverAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101DF5F0
			fight::Action* AirHoverTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AirHoverAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101DF040
			AirDodgeAction::AirDodgeAction(AirDodgeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101DEA90
			AirDodgeAction::~AirDodgeAction()
			{
			}

			// FUNCTION: ENGINE 0x101DE540
			void AirDodgeAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101DF760
			fight::Action* AirDodgeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AirDodgeAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<AirHoverTrack>;
			template class fight::PropertyBool<AirHoverTrack>;
			template class fight::TrackFactoryTemplate<AirHoverTrack>;
			template class fight::TrackFactoryCasterTemplate<AirHoverTrack>;
			template class fight::PropertyFloatConstRange<AirDodgeTrack>;
			template class fight::PropertyBool<AirDodgeTrack>;
			template class fight::TrackFactoryTemplate<AirDodgeTrack>;
			template class fight::TrackFactoryCasterTemplate<AirDodgeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DD9E0
// FUNCTION: ENGINE 0x101DDAA0
// FUNCTION: ENGINE 0x101DE010
// FUNCTION: ENGINE 0x101DE030
// FUNCTION: ENGINE 0x101DEC20
// FUNCTION: ENGINE 0x101DF0C0
// FUNCTION: ENGINE 0x1021BDE0
// FUNCTION: ENGINE 0x1021BE10
// FUNCTION: ENGINE 0x1021BE40
// FUNCTION: ENGINE 0x1021BE50
// FUNCTION: ENGINE 0x1021BE80
// FUNCTION: ENGINE 0x1021BE90
// FUNCTION: ENGINE 0x1021BEC0
// FUNCTION: ENGINE 0x1021BEF0
// FUNCTION: ENGINE 0x1021BF20
// FUNCTION: ENGINE 0x1021BF30
// FUNCTION: ENGINE 0x1021BF60
// FUNCTION: ENGINE 0x1021BF80
// FUNCTION: ENGINE 0x1021BF90
// FUNCTION: ENGINE 0x1021BFC0
// FUNCTION: ENGINE 0x1021BFF0
// FUNCTION: ENGINE 0x1021C000
// FUNCTION: ENGINE 0x1021C030
// FUNCTION: ENGINE 0x1021C050
// FUNCTION: ENGINE 0x1021C5B0
// FUNCTION: ENGINE 0x1021C5E0
// FUNCTION: ENGINE 0x1021C600
// FUNCTION: ENGINE 0x1021C630
// FUNCTION: ENGINE 0x1021C650
// FUNCTION: ENGINE 0x1021C6A0
