// Fight items of the vehicle group: SetPanicStateTrack, PanicTrack, SpawnCopsBesideCarTrack, SpawnCopsOffScreenTrack, TerminateTrack, ReturnToNormalTrack (unit 0x1027BF20 - 0x1027D9F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/vehicle/vehicle_panic.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			fight::Property** gSetPanicStateTrackProperties;  // 0x112561AC

			// FUNCTION: ENGINE 0x1027BF20
			bool SetPanicStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BF40
			bool SetPanicStateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BF60
			bool SetPanicStateTrack::SetPanicType(int newValue)
			{
				panicType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C1B0
			fight::Property* SetPanicStateTrack::GetProperty(int index)
			{
				return gSetPanicStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C1D0
			void SetPanicStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetPanicStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C1E0
			SetPanicStateTrack::SetPanicStateTrack() : timeBegin(0.0f), timeEnd(-1.0f), panicType(0)
			{
			}

			// FUNCTION: ENGINE 0x1027C220
			float SetPanicStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C230
			float SetPanicStateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C240
			SetPanicStateTrack::~SetPanicStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027CD80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetPanicStateTrack::RegisterProperties()
			{
				if (gSetPanicStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetPanicStateTrack>("timeBegin", &SetPanicStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetPanicStateTrack>("timeEnd", &SetPanicStateTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<SetPanicStateTrack>("panicType", gSetPanicStateTrackPanicTypeTable, gSetPanicStateTrackPanicTypeCount, &SetPanicStateTrack::SetPanicType);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSetPanicStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CC60
			fight::TrackFactory* CreateSetPanicStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPanicStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D510
			void RegisterSetPanicStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPanicStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPanicTrackProperties;  // 0x112561B0

			// FUNCTION: ENGINE 0x1027BF70
			bool PanicTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BF90
			bool PanicTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BFB0
			bool PanicTrack::SetMinTimeDelay(float newValue)
			{
				minTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BFD0
			bool PanicTrack::SetMaxTimeDelay(float newValue)
			{
				maxTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027BFF0
			bool PanicTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C010
			bool PanicTrack::SetAccelration(float newValue)
			{
				accelration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C030
			bool PanicTrack::SetBraking(float newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C050
			fight::BranchHolder* PanicTrack::SetMyBranch()
			{
				return &myBranch;
			}

			// FUNCTION: ENGINE 0x1027C250
			fight::Property* PanicTrack::GetProperty(int index)
			{
				return gPanicTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C270
			void PanicTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPanicTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C280
			PanicTrack::PanicTrack() : myBranch(0), accelration(1.0f), braking(1.0f), maxTimeDelay(1.0f), maxVelocity(1.0f), minTimeDelay(0.1f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027C2F0
			float PanicTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C300
			float PanicTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C310
			PanicTrack::~PanicTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027CEB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PanicTrack::RegisterProperties()
			{
				if (gPanicTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PanicTrack>("timeBegin", &PanicTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("timeEnd", &PanicTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("minTimeDelay", &PanicTrack::SetMinTimeDelay);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("maxTimeDelay", &PanicTrack::SetMaxTimeDelay);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("maxVelocity", &PanicTrack::SetMaxVelocity);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("accelration", &PanicTrack::SetAccelration);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PanicTrack>("braking", &PanicTrack::SetBraking);
					properties[6] = property;
					property = new fight::PropertyBranch<PanicTrack>("myBranch", &PanicTrack::SetMyBranch);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gPanicTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CC90
			fight::TrackFactory* CreatePanicTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PanicTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D540
			void RegisterPanicTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PanicTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpawnCopsBesideCarTrackProperties;  // 0x112561B4

			// FUNCTION: ENGINE 0x1027C060
			bool SpawnCopsBesideCarTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C080
			bool SpawnCopsBesideCarTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C0A0
			bool SpawnCopsBesideCarTrack::SetXOffset(float newValue)
			{
				xOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C330
			fight::Property* SpawnCopsBesideCarTrack::GetProperty(int index)
			{
				return gSpawnCopsBesideCarTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C350
			void SpawnCopsBesideCarTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnCopsBesideCarTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C360
			SpawnCopsBesideCarTrack::SpawnCopsBesideCarTrack() : timeBegin(0.0f), timeEnd(-1.0f), xOffset(1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027C3B0
			float SpawnCopsBesideCarTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C3C0
			float SpawnCopsBesideCarTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C3D0
			SpawnCopsBesideCarTrack::~SpawnCopsBesideCarTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027D100
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnCopsBesideCarTrack::RegisterProperties()
			{
				if (gSpawnCopsBesideCarTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpawnCopsBesideCarTrack>("timeBegin", &SpawnCopsBesideCarTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpawnCopsBesideCarTrack>("timeEnd", &SpawnCopsBesideCarTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SpawnCopsBesideCarTrack>("xOffset", &SpawnCopsBesideCarTrack::SetXOffset);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSpawnCopsBesideCarTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CCC0
			fight::TrackFactory* CreateSpawnCopsBesideCarTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnCopsBesideCarTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D570
			void RegisterSpawnCopsBesideCarTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnCopsBesideCarTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpawnCopsOffScreenTrackProperties;  // 0x112561B8

			// FUNCTION: ENGINE 0x1027C0C0
			bool SpawnCopsOffScreenTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C0E0
			bool SpawnCopsOffScreenTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C100
			bool SpawnCopsOffScreenTrack::SetNumCops(int newValue)
			{
				numCops = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C3E0
			fight::Property* SpawnCopsOffScreenTrack::GetProperty(int index)
			{
				return gSpawnCopsOffScreenTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C400
			void SpawnCopsOffScreenTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnCopsOffScreenTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C410
			SpawnCopsOffScreenTrack::SpawnCopsOffScreenTrack() : timeBegin(0.0f), timeEnd(-1.0f), numCops(2)
			{
			}

			// FUNCTION: ENGINE 0x1027C450
			float SpawnCopsOffScreenTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C460
			float SpawnCopsOffScreenTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C470
			SpawnCopsOffScreenTrack::~SpawnCopsOffScreenTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027D210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnCopsOffScreenTrack::RegisterProperties()
			{
				if (gSpawnCopsOffScreenTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpawnCopsOffScreenTrack>("timeBegin", &SpawnCopsOffScreenTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpawnCopsOffScreenTrack>("timeEnd", &SpawnCopsOffScreenTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<SpawnCopsOffScreenTrack>("numCops", &SpawnCopsOffScreenTrack::SetNumCops);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSpawnCopsOffScreenTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CCF0
			fight::TrackFactory* CreateSpawnCopsOffScreenTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnCopsOffScreenTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D5A0
			void RegisterSpawnCopsOffScreenTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnCopsOffScreenTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTerminateTrackProperties;  // 0x112561BC

			// FUNCTION: ENGINE 0x1027C110
			bool TerminateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C130
			bool TerminateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C480
			fight::Property* TerminateTrack::GetProperty(int index)
			{
				return gTerminateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C4A0
			void TerminateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTerminateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C4B0
			TerminateTrack::TerminateTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027C4E0
			float TerminateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C4F0
			float TerminateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C500
			TerminateTrack::~TerminateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027D320
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TerminateTrack::RegisterProperties()
			{
				if (gTerminateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TerminateTrack>("timeBegin", &TerminateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TerminateTrack>("timeEnd", &TerminateTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTerminateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CD20
			fight::TrackFactory* CreateTerminateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TerminateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D5D0
			void RegisterTerminateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TerminateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReturnToNormalTrackProperties;  // 0x112561C0

			// FUNCTION: ENGINE 0x1027C150
			bool ReturnToNormalTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C170
			bool ReturnToNormalTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C190
			bool ReturnToNormalTrack::SetTimeTillReturn(float newValue)
			{
				timeTillReturn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027C510
			fight::Property* ReturnToNormalTrack::GetProperty(int index)
			{
				return gReturnToNormalTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027C530
			void ReturnToNormalTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReturnToNormalTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027C540
			ReturnToNormalTrack::ReturnToNormalTrack() : timeBegin(0.0f), timeEnd(-1.0f), timeTillReturn(1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027C590
			float ReturnToNormalTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C5A0
			float ReturnToNormalTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027C5B0
			ReturnToNormalTrack::~ReturnToNormalTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027D400
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReturnToNormalTrack::RegisterProperties()
			{
				if (gReturnToNormalTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReturnToNormalTrack>("timeBegin", &ReturnToNormalTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReturnToNormalTrack>("timeEnd", &ReturnToNormalTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReturnToNormalTrack>("timeTillReturn", &ReturnToNormalTrack::SetTimeTillReturn);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReturnToNormalTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027CD50
			fight::TrackFactory* CreateReturnToNormalTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReturnToNormalTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027D600
			void RegisterReturnToNormalTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReturnToNormalTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<SetPanicStateTrack>;
			template class fight::PropertyEnumConstList<SetPanicStateTrack>;
			template class fight::TrackFactoryTemplate<SetPanicStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SetPanicStateTrack>;
			template class fight::PropertyFloatConstRange<PanicTrack>;
			template class fight::PropertyBranch<PanicTrack>;
			template class fight::TrackFactoryTemplate<PanicTrack>;
			template class fight::TrackFactoryCasterTemplate<PanicTrack>;
			template class fight::PropertyFloatConstRange<SpawnCopsBesideCarTrack>;
			template class fight::TrackFactoryTemplate<SpawnCopsBesideCarTrack>;
			template class fight::TrackFactoryCasterTemplate<SpawnCopsBesideCarTrack>;
			template class fight::PropertyFloatConstRange<SpawnCopsOffScreenTrack>;
			template class fight::PropertyIntConstRange<SpawnCopsOffScreenTrack>;
			template class fight::TrackFactoryTemplate<SpawnCopsOffScreenTrack>;
			template class fight::TrackFactoryCasterTemplate<SpawnCopsOffScreenTrack>;
			template class fight::PropertyFloatConstRange<TerminateTrack>;
			template class fight::TrackFactoryTemplate<TerminateTrack>;
			template class fight::TrackFactoryCasterTemplate<TerminateTrack>;
			template class fight::PropertyFloatConstRange<ReturnToNormalTrack>;
			template class fight::TrackFactoryTemplate<ReturnToNormalTrack>;
			template class fight::TrackFactoryCasterTemplate<ReturnToNormalTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027C5C0
// FUNCTION: ENGINE 0x1027C5F0
// FUNCTION: ENGINE 0x1027C620
// FUNCTION: ENGINE 0x1027C650
// FUNCTION: ENGINE 0x1027C680
// FUNCTION: ENGINE 0x1027C6B0
// FUNCTION: ENGINE 0x1027C6E0
// FUNCTION: ENGINE 0x1027C6F0
// FUNCTION: ENGINE 0x1027C720
// FUNCTION: ENGINE 0x1027C730
// FUNCTION: ENGINE 0x1027C760
// FUNCTION: ENGINE 0x1027C770
// FUNCTION: ENGINE 0x1027C7A0
// FUNCTION: ENGINE 0x1027C7B0
// FUNCTION: ENGINE 0x1027C7E0
// FUNCTION: ENGINE 0x1027C7F0
// FUNCTION: ENGINE 0x1027C820
// FUNCTION: ENGINE 0x1027C830
// FUNCTION: ENGINE 0x1027C860
// FUNCTION: ENGINE 0x1027C890
// FUNCTION: ENGINE 0x1027C8C0
// FUNCTION: ENGINE 0x1027C8D0
// FUNCTION: ENGINE 0x1027C910
// FUNCTION: ENGINE 0x1027C920
// FUNCTION: ENGINE 0x1027C950
// FUNCTION: ENGINE 0x1027C970
// FUNCTION: ENGINE 0x1027C980
// FUNCTION: ENGINE 0x1027C9B0
// FUNCTION: ENGINE 0x1027C9E0
// FUNCTION: ENGINE 0x1027C9F0
// FUNCTION: ENGINE 0x1027CA20
// FUNCTION: ENGINE 0x1027CA40
// FUNCTION: ENGINE 0x1027CA70
// FUNCTION: ENGINE 0x1027CAA0
// FUNCTION: ENGINE 0x1027CAB0
// FUNCTION: ENGINE 0x1027CAE0
// FUNCTION: ENGINE 0x1027CB10
// FUNCTION: ENGINE 0x1027CB20
// FUNCTION: ENGINE 0x1027CB50
// FUNCTION: ENGINE 0x1027CB70
// FUNCTION: ENGINE 0x1027CB80
// FUNCTION: ENGINE 0x1027CBB0
// FUNCTION: ENGINE 0x1027CBE0
// FUNCTION: ENGINE 0x1027CBF0
// FUNCTION: ENGINE 0x1027CC20
// FUNCTION: ENGINE 0x1027CC50
// FUNCTION: ENGINE 0x1027D630
// FUNCTION: ENGINE 0x1027D660
// FUNCTION: ENGINE 0x1027D680
// FUNCTION: ENGINE 0x1027D6B0
// FUNCTION: ENGINE 0x1027D6D0
// FUNCTION: ENGINE 0x1027D700
// FUNCTION: ENGINE 0x1027D720
// FUNCTION: ENGINE 0x1027D750
// FUNCTION: ENGINE 0x1027D770
// FUNCTION: ENGINE 0x1027D7A0
// FUNCTION: ENGINE 0x1027D7C0
// FUNCTION: ENGINE 0x1027D7F0
// FUNCTION: ENGINE 0x1027D810
// FUNCTION: ENGINE 0x1027D860
// FUNCTION: ENGINE 0x1027D8B0
// FUNCTION: ENGINE 0x1027D900
// FUNCTION: ENGINE 0x1027D950
// FUNCTION: ENGINE 0x1027D9A0
