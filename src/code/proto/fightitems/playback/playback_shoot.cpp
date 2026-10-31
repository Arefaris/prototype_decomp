// Fight items of the playback group: WasShotByPlayerCondition, ShootTrack (unit 0x1025BC30 - 0x1025C660; no assert path, the file name is a guess).
#include "code/proto/fightitems/playback/playback_shoot.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			fight::Property** gWasShotByPlayerConditionProperties;  // 0x11255CF0

			// FUNCTION: ENGINE 0x1025BC30
			bool WasShotByPlayerCondition::SetShotByPlayer(bool newValue)
			{
				shotByPlayer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BD10
			fight::Property* WasShotByPlayerCondition::GetProperty(int index)
			{
				return gWasShotByPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1025BD30
			void WasShotByPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gWasShotByPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x1025BD40
			WasShotByPlayerCondition::WasShotByPlayerCondition() : fight::Condition(0), shotByPlayer(true)
			{
			}

			// FUNCTION: ENGINE 0x1025BD60
			WasShotByPlayerCondition::~WasShotByPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x1025C1C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WasShotByPlayerCondition::RegisterProperties()
			{
				if (gWasShotByPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<WasShotByPlayerCondition>("shotByPlayer", &WasShotByPlayerCondition::SetShotByPlayer);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gWasShotByPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025C160
			fight::ConditionFactory* CreateWasShotByPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WasShotByPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025C4C0
			void RegisterWasShotByPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WasShotByPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShootTrackProperties;  // 0x11255CF4

			// FUNCTION: ENGINE 0x1025BC40
			bool ShootTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BC60
			bool ShootTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BC80
			bool ShootTrack::SetDirectionSpace(int newValue)
			{
				directionSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BC90
			bool ShootTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BCB0
			bool ShootTrack::SetSingleShot(bool newValue)
			{
				singleShot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BCC0
			bool ShootTrack::SetShooterIsOriginator(bool newValue)
			{
				shooterIsOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BCD0
			bool ShootTrack::SetWeaponSpaceOffset(const math::Vector& newValue)
			{
				weaponSpaceOffset.x = newValue.x;
				weaponSpaceOffset.y = newValue.y;
				weaponSpaceOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BCF0
			bool ShootTrack::SetWeaponSpaceRotationOffset(const math::Vector& newValue)
			{
				weaponSpaceRotationOffset.x = newValue.x;
				weaponSpaceRotationOffset.y = newValue.y;
				weaponSpaceRotationOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025BD70
			fight::Property* ShootTrack::GetProperty(int index)
			{
				return gShootTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025BD90
			void ShootTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025BDA0
			ShootTrack::ShootTrack() : direction(0.0f, 0.0f, 0.0f), weaponSpaceOffset(0.0f, 0.0f, 0.0f), weaponSpaceRotationOffset(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(0.0f), directionSpace(0), shooterIsOriginator(false), singleShot(false)
			{
			}

			// FUNCTION: ENGINE 0x1025BE10
			float ShootTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025BE20
			float ShootTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1025BE30
			ShootTrack::~ShootTrack()
			{
			}

			// FUNCTION: ENGINE 0x1025C260
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootTrack::RegisterProperties()
			{
				if (gShootTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootTrack>("timeBegin", &ShootTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShootTrack>("timeEnd", &ShootTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<ShootTrack>("directionSpace", motion::gShootTrackFixedDirectionSpaceTable, motion::gShootTrackFixedDirectionSpaceCount, &ShootTrack::SetDirectionSpace);
					properties[2] = property;
					property = new fight::PropertyVector<ShootTrack>("direction", &ShootTrack::SetDirection);
					properties[3] = property;
					property = new fight::PropertyBool<ShootTrack>("singleShot", &ShootTrack::SetSingleShot);
					properties[4] = property;
					property = new fight::PropertyBool<ShootTrack>("shooterIsOriginator", &ShootTrack::SetShooterIsOriginator);
					properties[5] = property;
					property = new fight::PropertyVector<ShootTrack>("weaponSpaceOffset", &ShootTrack::SetWeaponSpaceOffset);
					properties[6] = property;
					property = new fight::PropertyVector<ShootTrack>("weaponSpaceRotationOffset", &ShootTrack::SetWeaponSpaceRotationOffset);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gShootTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025C190
			fight::TrackFactory* CreateShootTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025C4F0
			void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyBool<WasShotByPlayerCondition>;
			template class fight::ConditionFactoryTemplate<WasShotByPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<WasShotByPlayerCondition>;
			template class fight::PropertyFloatConstRange<ShootTrack>;
			template class fight::PropertyEnumConstList<ShootTrack>;
			template class fight::PropertyVector<ShootTrack>;
			template class fight::PropertyBool<ShootTrack>;
			template class fight::TrackFactoryTemplate<ShootTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1025BE40
// FUNCTION: ENGINE 0x1025BE70
// FUNCTION: ENGINE 0x1025BEA0
// FUNCTION: ENGINE 0x1025BEB0
// FUNCTION: ENGINE 0x1025BEE0
// FUNCTION: ENGINE 0x1025BEF0
// FUNCTION: ENGINE 0x1025BF20
// FUNCTION: ENGINE 0x1025BF50
// FUNCTION: ENGINE 0x1025BF70
// FUNCTION: ENGINE 0x1025BF80
// FUNCTION: ENGINE 0x1025BFB0
// FUNCTION: ENGINE 0x1025BFE0
// FUNCTION: ENGINE 0x1025BFF0
// FUNCTION: ENGINE 0x1025C030
// FUNCTION: ENGINE 0x1025C040
// FUNCTION: ENGINE 0x1025C070
// FUNCTION: ENGINE 0x1025C090
// FUNCTION: ENGINE 0x1025C0A0
// FUNCTION: ENGINE 0x1025C0D0
// FUNCTION: ENGINE 0x1025C0F0
// FUNCTION: ENGINE 0x1025C100
// FUNCTION: ENGINE 0x1025C130
// FUNCTION: ENGINE 0x1025C150
// FUNCTION: ENGINE 0x1025C520
// FUNCTION: ENGINE 0x1025C550
// FUNCTION: ENGINE 0x1025C570
// FUNCTION: ENGINE 0x1025C5A0
// FUNCTION: ENGINE 0x1025C5C0
// FUNCTION: ENGINE 0x1025C610
