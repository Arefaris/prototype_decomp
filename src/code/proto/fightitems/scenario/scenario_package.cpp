// Fight items of the scenario group: PackageReadyCondition, PackageLoadTrack, PackageUnloadTrack (unit 0x101D9540 - 0x101D9FB0; no assert path, the file name is a guess).
#include "code/core/linklist.h"
#include "code/proto/fightitems/scenario/scenario_package.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gPackageReadyConditionProperties;  // 0x11254DB0

			// FUNCTION: ENGINE 0x101D95E0
			bool PackageReadyCondition::SetPackageName(const char* newValue)
			{
				packageName = fight::ReplaceString(packageName, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101D9550
			fight::Property* PackageReadyCondition::GetProperty(int index)
			{
				return gPackageReadyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101D9570
			void PackageReadyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPackageReadyConditionProperties);
			}

			// FUNCTION: ENGINE 0x101D9580
			PackageReadyCondition::PackageReadyCondition() : fight::Condition(0), packageName(0)
			{
			}

			// FUNCTION: ENGINE 0x101D95B0
			PackageReadyCondition::~PackageReadyCondition()
			{
				delete[] packageName;
			}

			// FUNCTION: ENGINE 0x101D9B20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PackageReadyCondition::RegisterProperties()
			{
				if (gPackageReadyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyString<PackageReadyCondition>("packageName", &PackageReadyCondition::SetPackageName);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPackageReadyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D9A90
			fight::ConditionFactory* CreatePackageReadyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PackageReadyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D9D40
			void RegisterPackageReadyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PackageReadyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPackageLoadTrackProperties;  // 0x11254DB4

			// FUNCTION: ENGINE 0x101D96C0
			bool PackageLoadTrack::SetPackageName(const char* newValue)
			{
				packageName = fight::ReplaceString(packageName, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101D9540
			bool PackageLoadTrack::SetAsync(bool newValue)
			{
				async = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D9610
			fight::Property* PackageLoadTrack::GetProperty(int index)
			{
				return gPackageLoadTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D9630
			void PackageLoadTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPackageLoadTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D9640
			PackageLoadTrack::PackageLoadTrack() : packageName(0), async(true)
			{
			}

			// FUNCTION: ENGINE 0x101D9670
			float PackageLoadTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101D9680
			float PackageLoadTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101D9690
			PackageLoadTrack::~PackageLoadTrack()
			{
				delete[] packageName;
			}

			// FUNCTION: ENGINE 0x101D9BC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PackageLoadTrack::RegisterProperties()
			{
				if (gPackageLoadTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyString<PackageLoadTrack>("packageName", &PackageLoadTrack::SetPackageName);
					properties[0] = property;
					property = new fight::PropertyBool<PackageLoadTrack>("async", &PackageLoadTrack::SetAsync);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPackageLoadTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D9AC0
			fight::TrackFactory* CreatePackageLoadTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PackageLoadTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D9D70
			void RegisterPackageLoadTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PackageLoadTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPackageUnloadTrackProperties;  // 0x11254DB8

			// FUNCTION: ENGINE 0x101D9790
			bool PackageUnloadTrack::SetPackageName(const char* newValue)
			{
				packageName = fight::ReplaceString(packageName, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101D96F0
			fight::Property* PackageUnloadTrack::GetProperty(int index)
			{
				return gPackageUnloadTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D9710
			void PackageUnloadTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPackageUnloadTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D9720
			PackageUnloadTrack::PackageUnloadTrack() : packageName(0)
			{
			}

			// FUNCTION: ENGINE 0x101D9740
			float PackageUnloadTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101D9750
			float PackageUnloadTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101D9760
			PackageUnloadTrack::~PackageUnloadTrack()
			{
				delete[] packageName;
			}

			// FUNCTION: ENGINE 0x101D9CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PackageUnloadTrack::RegisterProperties()
			{
				if (gPackageUnloadTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyString<PackageUnloadTrack>("packageName", &PackageUnloadTrack::SetPackageName);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPackageUnloadTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D9AF0
			fight::TrackFactory* CreatePackageUnloadTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PackageUnloadTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D9DA0
			void RegisterPackageUnloadTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PackageUnloadTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyString<PackageReadyCondition>;
			template class fight::ConditionFactoryTemplate<PackageReadyCondition>;
			template class fight::ConditionFactoryCasterTemplate<PackageReadyCondition>;
			template class fight::PropertyString<PackageLoadTrack>;
			template class fight::PropertyBool<PackageLoadTrack>;
			template class fight::TrackFactoryTemplate<PackageLoadTrack>;
			template class fight::TrackFactoryCasterTemplate<PackageLoadTrack>;
			template class fight::PropertyString<PackageUnloadTrack>;
			template class fight::TrackFactoryTemplate<PackageUnloadTrack>;
			template class fight::TrackFactoryCasterTemplate<PackageUnloadTrack>;

			// FUNCTION: ENGINE 0x101D6060
			bool PackageReadyCondition::Evaluate(int a, int b, int c, int d)
			{
				if (packageName != 0)
				{
					core::Name<core::CaseSensitiveKey> name(packageName, 1);
					engine::StreamPackage* package = engine::FindStreamPackage(name);
					if (package != 0 && package->instance != 0 && package->instance->state == engine::StreamPackageInstance::STATE_LOADED)
					{
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x101D6340
			PackageLoadAction::PackageLoadAction(PackageLoadTrack* newTrack) : fight::Action(0xE00), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x101D61E0
			PackageLoadAction::~PackageLoadAction()
			{
			}

			// FUNCTION: ENGINE 0x101D63E0
			bool PackageLoadAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				core::Name<core::CaseSensitiveKey> name(link.object->packageName, 1);
				engine::StreamPackage* package = engine::FindStreamPackage(name);
				if (package != 0)
				{
					package->Load(0, 0xFFFF, gPackageLoadSlotGroup, true);
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101D6020
			void PackageLoadAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101D6450
			PackageUnloadAction::PackageUnloadAction(PackageUnloadTrack* newTrack) : fight::Action(0xE00), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x101D6230
			PackageUnloadAction::~PackageUnloadAction()
			{
			}

			// FUNCTION: ENGINE 0x101D64F0
			bool PackageUnloadAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				core::Name<core::CaseSensitiveKey> name(link.object->packageName, 1);
				engine::StreamPackage* package = engine::FindStreamPackage(name);
				if (package != 0)
				{
					core::Name<core::CaseSensitiveKey> again(link.object->packageName, 1);
					Unknown104887E0(again);
					package->Unload(0, true);
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101D6030
			void PackageUnloadAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101D6580
			fight::Action* PackageLoadTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new PackageLoadAction(this);
			}

			// FUNCTION: ENGINE 0x101D65B0
			fight::Action* PackageUnloadTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new PackageUnloadAction(this);
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101D60C0
// FUNCTION: ENGINE 0x101D60E0
// FUNCTION: ENGINE 0x101D6110
// FUNCTION: ENGINE 0x101D6170
// FUNCTION: ENGINE 0x101D63B0
// FUNCTION: ENGINE 0x101D64C0
// FUNCTION: ENGINE 0x101D97C0
// FUNCTION: ENGINE 0x101D97F0
// FUNCTION: ENGINE 0x101D9820
// FUNCTION: ENGINE 0x101D9850
// FUNCTION: ENGINE 0x101D9860
// FUNCTION: ENGINE 0x101D9890
// FUNCTION: ENGINE 0x101D98A0
// FUNCTION: ENGINE 0x101D98D0
// FUNCTION: ENGINE 0x101D98E0
// FUNCTION: ENGINE 0x101D9910
// FUNCTION: ENGINE 0x101D9940
// FUNCTION: ENGINE 0x101D9960
// FUNCTION: ENGINE 0x101D9970
// FUNCTION: ENGINE 0x101D99A0
// FUNCTION: ENGINE 0x101D99C0
// FUNCTION: ENGINE 0x101D99D0
// FUNCTION: ENGINE 0x101D9A00
// FUNCTION: ENGINE 0x101D9A20
// FUNCTION: ENGINE 0x101D9A30
// FUNCTION: ENGINE 0x101D9A60
// FUNCTION: ENGINE 0x101D9A80
// FUNCTION: ENGINE 0x101D9DD0
// FUNCTION: ENGINE 0x101D9E00
// FUNCTION: ENGINE 0x101D9E20
// FUNCTION: ENGINE 0x101D9E50
// FUNCTION: ENGINE 0x101D9E70
// FUNCTION: ENGINE 0x101D9EA0
// FUNCTION: ENGINE 0x101D9EC0
// FUNCTION: ENGINE 0x101D9F10
// FUNCTION: ENGINE 0x101D9F60
