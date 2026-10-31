// Fight items of the motion group: GrabSlotUpdateAttachmentWithRestoreTrack, GrabSlotDetachThrowTrack, GrabSlotDetachTrack, GrabSetGrabbingTimerTrack, GrabSlotSwapTrack, GrabSlotReverseAttachmentTrack, GrabbedExecuteUsingParentTrack, GrabbedSwapGrabberSlotsTrack, GrabButtonStruggleTrack, GrabbedDetachTrack, GrabObjectFromChildGrabSlotTrack, GrabSlotExecuteTrack, GrabTargetClearTrack, GrabSlotDeathTrack, ReactionHitGrabTrack, SetGrabIntersectionPropertiesTrack, GrabbedPlaybackTrack, AllowGrabbingTrack, DelayCollisionWithGrabbedTrack, GrabObjectFromParentGrabSlotTrack, GrabSlotExecuteUsingChildTrack, GrabbedUpdateAttachmentTrack, GrabGrabTargetTrack, GrabSlotUpdateAttachmentTrack, GrabPlayerTrack, GrabbedExecuteOnParentTrack, GrabSlotEnableStuckTestTrack (unit 0x10169790 - 0x10173B80; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_grabtrack.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGrabSlotUpdateAttachmentWithRestoreTrackProperties;  // 0x112545F0

			// FUNCTION: ENGINE 0x10169790
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101697B0
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AF30
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AF50
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101697D0
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101697F0
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AF70
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169840
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169860
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101698B0
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101698D0
			bool GrabSlotUpdateAttachmentWithRestoreTrack::SetPhysicsMode(int newValue)
			{
				physicsMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A710
			fight::Property* GrabSlotUpdateAttachmentWithRestoreTrack::GetProperty(int index)
			{
				return gGrabSlotUpdateAttachmentWithRestoreTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A730
			void GrabSlotUpdateAttachmentWithRestoreTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotUpdateAttachmentWithRestoreTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B490
			GrabSlotUpdateAttachmentWithRestoreTrack::GrabSlotUpdateAttachmentWithRestoreTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), physicsMode(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016B550
			float GrabSlotUpdateAttachmentWithRestoreTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B560
			float GrabSlotUpdateAttachmentWithRestoreTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B570
			GrabSlotUpdateAttachmentWithRestoreTrack::~GrabSlotUpdateAttachmentWithRestoreTrack()
			{
			}

			// FUNCTION: ENGINE 0x101702E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotUpdateAttachmentWithRestoreTrack::RegisterProperties()
			{
				if (gGrabSlotUpdateAttachmentWithRestoreTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentWithRestoreTrack>("timeBegin", &GrabSlotUpdateAttachmentWithRestoreTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentWithRestoreTrack>("timeEnd", &GrabSlotUpdateAttachmentWithRestoreTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentWithRestoreTrack>("grabSlot", &GrabSlotUpdateAttachmentWithRestoreTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentWithRestoreTrack>("parentJoint", &GrabSlotUpdateAttachmentWithRestoreTrack::SetParentJoint);
					properties[3] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentWithRestoreTrack>("parentPositionOffset", &GrabSlotUpdateAttachmentWithRestoreTrack::SetParentPositionOffset);
					properties[4] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentWithRestoreTrack>("parentRotationOffset", &GrabSlotUpdateAttachmentWithRestoreTrack::SetParentRotationOffset);
					properties[5] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentWithRestoreTrack>("childJoint", &GrabSlotUpdateAttachmentWithRestoreTrack::SetChildJoint);
					properties[6] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentWithRestoreTrack>("childPositionOffset", &GrabSlotUpdateAttachmentWithRestoreTrack::SetChildPositionOffset);
					properties[7] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentWithRestoreTrack>("childRotationOffset", &GrabSlotUpdateAttachmentWithRestoreTrack::SetChildRotationOffset);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentWithRestoreTrack>("blendTime", &GrabSlotUpdateAttachmentWithRestoreTrack::SetBlendTime);
					properties[9] = property;
					property = new fight::PropertyEnumConstList<GrabSlotUpdateAttachmentWithRestoreTrack>("physicsMode", gCollisionGrabTrackPhysicsModeTable, gCollisionGrabTrackPhysicsModeCount, &GrabSlotUpdateAttachmentWithRestoreTrack::SetPhysicsMode);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotUpdateAttachmentWithRestoreTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E830
			fight::TrackFactory* CreateGrabSlotUpdateAttachmentWithRestoreTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentWithRestoreTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F3E0
			void RegisterGrabSlotUpdateAttachmentWithRestoreTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentWithRestoreTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotDetachThrowTrackProperties;  // 0x112545F4

			// FUNCTION: ENGINE 0x101698E0
			bool GrabSlotDetachThrowTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169900
			bool GrabSlotDetachThrowTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169920
			bool GrabSlotDetachThrowTrack::SetLatestDetachTime(float newValue)
			{
				latestDetachTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AF90
			bool GrabSlotDetachThrowTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169940
			bool GrabSlotDetachThrowTrack::SetLinearVelocityReference(int newValue)
			{
				linearVelocityReference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169950
			bool GrabSlotDetachThrowTrack::SetAddedLinearVelocity(const math::Vector& newValue)
			{
				addedLinearVelocity.x = newValue.x;
				addedLinearVelocity.y = newValue.y;
				addedLinearVelocity.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169970
			bool GrabSlotDetachThrowTrack::SetAngularVelocityReference(int newValue)
			{
				angularVelocityReference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169980
			bool GrabSlotDetachThrowTrack::SetAddedAngularVelocity(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				addedAngularVelocity.x = scaled.x;
				addedAngularVelocity.y = scaled.y;
				addedAngularVelocity.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A740
			fight::Property* GrabSlotDetachThrowTrack::GetProperty(int index)
			{
				return gGrabSlotDetachThrowTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A760
			void GrabSlotDetachThrowTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotDetachThrowTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B580
			GrabSlotDetachThrowTrack::GrabSlotDetachThrowTrack() : addedAngularVelocity(0.0f, 0.0f, 0.0f), addedLinearVelocity(0.0f, 0.0f, 0.0f), latestDetachTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), angularVelocityReference(0), linearVelocityReference(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016B600
			float GrabSlotDetachThrowTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B610
			float GrabSlotDetachThrowTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B620
			GrabSlotDetachThrowTrack::~GrabSlotDetachThrowTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170600
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotDetachThrowTrack::RegisterProperties()
			{
				if (gGrabSlotDetachThrowTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotDetachThrowTrack>("timeBegin", &GrabSlotDetachThrowTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotDetachThrowTrack>("timeEnd", &GrabSlotDetachThrowTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotDetachThrowTrack>("latestDetachTime", &GrabSlotDetachThrowTrack::SetLatestDetachTime);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabSlotDetachThrowTrack>("grabSlot", &GrabSlotDetachThrowTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<GrabSlotDetachThrowTrack>("linearVelocityReference", gGrabSlotDetachThrowTrackLinearVelocityReferenceTable, gGrabSlotDetachThrowTrackLinearVelocityReferenceCount, &GrabSlotDetachThrowTrack::SetLinearVelocityReference);
					properties[4] = property;
					property = new fight::PropertyVector<GrabSlotDetachThrowTrack>("addedLinearVelocity", &GrabSlotDetachThrowTrack::SetAddedLinearVelocity);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<GrabSlotDetachThrowTrack>("angularVelocityReference", gGrabSlotDetachThrowTrackLinearVelocityReferenceTable, gGrabSlotDetachThrowTrackLinearVelocityReferenceCount, &GrabSlotDetachThrowTrack::SetAngularVelocityReference);
					properties[6] = property;
					property = new fight::PropertyVector<GrabSlotDetachThrowTrack>("addedAngularVelocity", &GrabSlotDetachThrowTrack::SetAddedAngularVelocity);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotDetachThrowTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E860
			fight::TrackFactory* CreateGrabSlotDetachThrowTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDetachThrowTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F410
			void RegisterGrabSlotDetachThrowTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDetachThrowTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotDetachTrackProperties;  // 0x112545F8

			// FUNCTION: ENGINE 0x101699D0
			bool GrabSlotDetachTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AFB0
			bool GrabSlotDetachTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A770
			fight::Property* GrabSlotDetachTrack::GetProperty(int index)
			{
				return gGrabSlotDetachTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A790
			void GrabSlotDetachTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotDetachTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B630
			GrabSlotDetachTrack::GrabSlotDetachTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016B670
			float GrabSlotDetachTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B680
			float GrabSlotDetachTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016B690
			GrabSlotDetachTrack::~GrabSlotDetachTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170870
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotDetachTrack::RegisterProperties()
			{
				if (gGrabSlotDetachTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotDetachTrack>("timeBegin", &GrabSlotDetachTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotDetachTrack>("grabSlot", &GrabSlotDetachTrack::SetGrabSlot);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotDetachTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E890
			fight::TrackFactory* CreateGrabSlotDetachTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDetachTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F440
			void RegisterGrabSlotDetachTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDetachTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSetGrabbingTimerTrackProperties;  // 0x112545FC

			// FUNCTION: ENGINE 0x101699F0
			bool GrabSetGrabbingTimerTrack::SetDuration(float newValue)
			{
				duration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169A10
			bool GrabSetGrabbingTimerTrack::SetIsGrabAttack(bool newValue)
			{
				isGrabAttack = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A7A0
			fight::Property* GrabSetGrabbingTimerTrack::GetProperty(int index)
			{
				return gGrabSetGrabbingTimerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A7C0
			void GrabSetGrabbingTimerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSetGrabbingTimerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016A7D0
			GrabSetGrabbingTimerTrack::GrabSetGrabbingTimerTrack() : duration(0.5f), isGrabAttack(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016A810
			float GrabSetGrabbingTimerTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016A820
			float GrabSetGrabbingTimerTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016A830
			GrabSetGrabbingTimerTrack::~GrabSetGrabbingTimerTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016ED40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSetGrabbingTimerTrack::RegisterProperties()
			{
				if (gGrabSetGrabbingTimerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSetGrabbingTimerTrack>("duration", &GrabSetGrabbingTimerTrack::SetDuration);
					properties[0] = property;
					property = new fight::PropertyBool<GrabSetGrabbingTimerTrack>("isGrabAttack", &GrabSetGrabbingTimerTrack::SetIsGrabAttack);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSetGrabbingTimerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E8C0
			fight::TrackFactory* CreateGrabSetGrabbingTimerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSetGrabbingTimerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F470
			void RegisterGrabSetGrabbingTimerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSetGrabbingTimerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotSwapTrackProperties;  // 0x11254600

			// FUNCTION: ENGINE 0x10169A20
			bool GrabSlotSwapTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AFD0
			bool GrabSlotSwapTrack::SetSlotA(const fight::Name& newValue)
			{
				slotA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AFF0
			bool GrabSlotSwapTrack::SetSlotB(const fight::Name& newValue)
			{
				slotB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A840
			fight::Property* GrabSlotSwapTrack::GetProperty(int index)
			{
				return gGrabSlotSwapTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A860
			void GrabSlotSwapTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotSwapTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B6D0
			GrabSlotSwapTrack::GrabSlotSwapTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x1016B710
			float GrabSlotSwapTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B720
			float GrabSlotSwapTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016B730
			GrabSlotSwapTrack::~GrabSlotSwapTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170950
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotSwapTrack::RegisterProperties()
			{
				if (gGrabSlotSwapTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotSwapTrack>("timeBegin", &GrabSlotSwapTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotSwapTrack>("slotA", &GrabSlotSwapTrack::SetSlotA);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabSlotSwapTrack>("slotB", &GrabSlotSwapTrack::SetSlotB);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotSwapTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E8F0
			fight::TrackFactory* CreateGrabSlotSwapTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotSwapTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F4A0
			void RegisterGrabSlotSwapTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotSwapTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotReverseAttachmentTrackProperties;  // 0x11254604

			// FUNCTION: ENGINE 0x10169A40
			bool GrabSlotReverseAttachmentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B010
			bool GrabSlotReverseAttachmentTrack::SetGiverGrabSlot(const fight::Name& newValue)
			{
				giverGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B030
			bool GrabSlotReverseAttachmentTrack::SetReceiverGrabSlot(const fight::Name& newValue)
			{
				receiverGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B050
			bool GrabSlotReverseAttachmentTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169A60
			bool GrabSlotReverseAttachmentTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169A80
			bool GrabSlotReverseAttachmentTrack::SetUpdateRotationOffset(bool newValue)
			{
				updateRotationOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169A90
			bool GrabSlotReverseAttachmentTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B070
			bool GrabSlotReverseAttachmentTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169AE0
			bool GrabSlotReverseAttachmentTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169B00
			bool GrabSlotReverseAttachmentTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169B50
			bool GrabSlotReverseAttachmentTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169B70
			bool GrabSlotReverseAttachmentTrack::SetPhysicsMode(int newValue)
			{
				physicsMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A870
			fight::Property* GrabSlotReverseAttachmentTrack::GetProperty(int index)
			{
				return gGrabSlotReverseAttachmentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A890
			void GrabSlotReverseAttachmentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotReverseAttachmentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B740
			GrabSlotReverseAttachmentTrack::GrabSlotReverseAttachmentTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), physicsMode(0), updateRotationOffset(true)
			{
			}

			// FUNCTION: ENGINE 0x1016B7F0
			float GrabSlotReverseAttachmentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B800
			float GrabSlotReverseAttachmentTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016B810
			GrabSlotReverseAttachmentTrack::~GrabSlotReverseAttachmentTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170A60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotReverseAttachmentTrack::RegisterProperties()
			{
				if (gGrabSlotReverseAttachmentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotReverseAttachmentTrack>("timeBegin", &GrabSlotReverseAttachmentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotReverseAttachmentTrack>("giverGrabSlot", &GrabSlotReverseAttachmentTrack::SetGiverGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabSlotReverseAttachmentTrack>("receiverGrabSlot", &GrabSlotReverseAttachmentTrack::SetReceiverGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabSlotReverseAttachmentTrack>("parentJoint", &GrabSlotReverseAttachmentTrack::SetParentJoint);
					properties[3] = property;
					property = new fight::PropertyVector<GrabSlotReverseAttachmentTrack>("parentPositionOffset", &GrabSlotReverseAttachmentTrack::SetParentPositionOffset);
					properties[4] = property;
					property = new fight::PropertyBool<GrabSlotReverseAttachmentTrack>("updateRotationOffset", &GrabSlotReverseAttachmentTrack::SetUpdateRotationOffset);
					properties[5] = property;
					property = new fight::PropertyVector<GrabSlotReverseAttachmentTrack>("parentRotationOffset", &GrabSlotReverseAttachmentTrack::SetParentRotationOffset);
					properties[6] = property;
					property = new fight::PropertyNameList<GrabSlotReverseAttachmentTrack>("childJoint", &GrabSlotReverseAttachmentTrack::SetChildJoint);
					properties[7] = property;
					property = new fight::PropertyVector<GrabSlotReverseAttachmentTrack>("childPositionOffset", &GrabSlotReverseAttachmentTrack::SetChildPositionOffset);
					properties[8] = property;
					property = new fight::PropertyVector<GrabSlotReverseAttachmentTrack>("childRotationOffset", &GrabSlotReverseAttachmentTrack::SetChildRotationOffset);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotReverseAttachmentTrack>("blendTime", &GrabSlotReverseAttachmentTrack::SetBlendTime);
					properties[10] = property;
					property = new fight::PropertyEnumConstList<GrabSlotReverseAttachmentTrack>("physicsMode", gGrabSlotReverseAttachmentTrackPhysicsModeTable, 2, &GrabSlotReverseAttachmentTrack::SetPhysicsMode);
					properties[11] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotReverseAttachmentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E920
			fight::TrackFactory* CreateGrabSlotReverseAttachmentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotReverseAttachmentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F4D0
			void RegisterGrabSlotReverseAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotReverseAttachmentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedExecuteUsingParentTrackProperties;  // 0x11254608

			// FUNCTION: ENGINE 0x10169B80
			bool GrabbedExecuteUsingParentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169BA0
			bool GrabbedExecuteUsingParentTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169BC0
			fight::BranchHolder* GrabbedExecuteUsingParentTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1016A8A0
			fight::Property* GrabbedExecuteUsingParentTrack::GetProperty(int index)
			{
				return gGrabbedExecuteUsingParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A8C0
			void GrabbedExecuteUsingParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedExecuteUsingParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016A8D0
			GrabbedExecuteUsingParentTrack::GrabbedExecuteUsingParentTrack() : branch(0), timeBegin(0.0f), timeEnd(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016A910
			float GrabbedExecuteUsingParentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016A920
			float GrabbedExecuteUsingParentTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016A930
			GrabbedExecuteUsingParentTrack::~GrabbedExecuteUsingParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016EE20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedExecuteUsingParentTrack::RegisterProperties()
			{
				if (gGrabbedExecuteUsingParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedExecuteUsingParentTrack>("timeBegin", &GrabbedExecuteUsingParentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabbedExecuteUsingParentTrack>("timeEnd", &GrabbedExecuteUsingParentTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBranch<GrabbedExecuteUsingParentTrack>("branch", &GrabbedExecuteUsingParentTrack::SetBranch);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabbedExecuteUsingParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E950
			fight::TrackFactory* CreateGrabbedExecuteUsingParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedExecuteUsingParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F500
			void RegisterGrabbedExecuteUsingParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedExecuteUsingParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedSwapGrabberSlotsTrackProperties;  // 0x1125460C

			// FUNCTION: ENGINE 0x10169BD0
			bool GrabbedSwapGrabberSlotsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B090
			bool GrabbedSwapGrabberSlotsTrack::SetSlotA(const fight::Name& newValue)
			{
				slotA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B0B0
			bool GrabbedSwapGrabberSlotsTrack::SetSlotB(const fight::Name& newValue)
			{
				slotB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A950
			fight::Property* GrabbedSwapGrabberSlotsTrack::GetProperty(int index)
			{
				return gGrabbedSwapGrabberSlotsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A970
			void GrabbedSwapGrabberSlotsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedSwapGrabberSlotsTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B850
			GrabbedSwapGrabberSlotsTrack::GrabbedSwapGrabberSlotsTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x1016B890
			float GrabbedSwapGrabberSlotsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B8A0
			float GrabbedSwapGrabberSlotsTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016B8B0
			GrabbedSwapGrabberSlotsTrack::~GrabbedSwapGrabberSlotsTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170DB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedSwapGrabberSlotsTrack::RegisterProperties()
			{
				if (gGrabbedSwapGrabberSlotsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedSwapGrabberSlotsTrack>("timeBegin", &GrabbedSwapGrabberSlotsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabbedSwapGrabberSlotsTrack>("slotA", &GrabbedSwapGrabberSlotsTrack::SetSlotA);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabbedSwapGrabberSlotsTrack>("slotB", &GrabbedSwapGrabberSlotsTrack::SetSlotB);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabbedSwapGrabberSlotsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E980
			fight::TrackFactory* CreateGrabbedSwapGrabberSlotsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedSwapGrabberSlotsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F530
			void RegisterGrabbedSwapGrabberSlotsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedSwapGrabberSlotsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabButtonStruggleTrackProperties;  // 0x11254610

			// FUNCTION: ENGINE 0x10169BF0
			bool GrabButtonStruggleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169C10
			bool GrabButtonStruggleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169C30
			bool GrabButtonStruggleTrack::SetTimeInput(float newValue)
			{
				timeInput = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B0D0
			bool GrabButtonStruggleTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169C50
			bool GrabButtonStruggleTrack::SetInitialCharge(float newValue)
			{
				initialCharge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169C70
			bool GrabButtonStruggleTrack::SetAutoChargeRateMin(float newValue)
			{
				autoChargeRateMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169C90
			bool GrabButtonStruggleTrack::SetAutoChargeRateMax(float newValue)
			{
				autoChargeRateMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169CB0
			bool GrabButtonStruggleTrack::SetButtonChargeRate(float newValue)
			{
				buttonChargeRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A980
			fight::Property* GrabButtonStruggleTrack::GetProperty(int index)
			{
				return gGrabButtonStruggleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A9A0
			void GrabButtonStruggleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabButtonStruggleTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B8C0
			GrabButtonStruggleTrack::GrabButtonStruggleTrack() : autoChargeRateMax(0.0f), autoChargeRateMin(0.0f), buttonChargeRate(0.0f), initialCharge(0.5f), timeBegin(0.0f), timeEnd(-1.0f), timeInput(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016B930
			float GrabButtonStruggleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B940
			float GrabButtonStruggleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B950
			GrabButtonStruggleTrack::~GrabButtonStruggleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10170EC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabButtonStruggleTrack::RegisterProperties()
			{
				if (gGrabButtonStruggleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("timeBegin", &GrabButtonStruggleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("timeEnd", &GrabButtonStruggleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("timeInput", &GrabButtonStruggleTrack::SetTimeInput);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabButtonStruggleTrack>("grabSlot", &GrabButtonStruggleTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("initialCharge", &GrabButtonStruggleTrack::SetInitialCharge);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("autoChargeRateMin", &GrabButtonStruggleTrack::SetAutoChargeRateMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("autoChargeRateMax", &GrabButtonStruggleTrack::SetAutoChargeRateMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<GrabButtonStruggleTrack>("buttonChargeRate", &GrabButtonStruggleTrack::SetButtonChargeRate);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gGrabButtonStruggleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E9B0
			fight::TrackFactory* CreateGrabButtonStruggleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabButtonStruggleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F560
			void RegisterGrabButtonStruggleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabButtonStruggleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedDetachTrackProperties;  // 0x11254614

			// FUNCTION: ENGINE 0x10169CD0
			bool GrabbedDetachTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A9B0
			fight::Property* GrabbedDetachTrack::GetProperty(int index)
			{
				return gGrabbedDetachTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016A9D0
			void GrabbedDetachTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedDetachTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016A9E0
			GrabbedDetachTrack::GrabbedDetachTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x1016AA00
			float GrabbedDetachTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AA10
			float GrabbedDetachTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016AA20
			GrabbedDetachTrack::~GrabbedDetachTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016EF30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedDetachTrack::RegisterProperties()
			{
				if (gGrabbedDetachTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedDetachTrack>("timeBegin", &GrabbedDetachTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabbedDetachTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016E9E0
			fight::TrackFactory* CreateGrabbedDetachTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedDetachTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F590
			void RegisterGrabbedDetachTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedDetachTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabObjectFromChildGrabSlotTrackProperties;  // 0x11254618

			// FUNCTION: ENGINE 0x10169CF0
			bool GrabObjectFromChildGrabSlotTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B0F0
			bool GrabObjectFromChildGrabSlotTrack::SetChild(const fight::Name& newValue)
			{
				child = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B110
			bool GrabObjectFromChildGrabSlotTrack::SetChildGrabSlot(const fight::Name& newValue)
			{
				childGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B130
			bool GrabObjectFromChildGrabSlotTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AA30
			fight::Property* GrabObjectFromChildGrabSlotTrack::GetProperty(int index)
			{
				return gGrabObjectFromChildGrabSlotTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AA50
			void GrabObjectFromChildGrabSlotTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabObjectFromChildGrabSlotTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016B990
			GrabObjectFromChildGrabSlotTrack::GrabObjectFromChildGrabSlotTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016B9E0
			float GrabObjectFromChildGrabSlotTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016B9F0
			float GrabObjectFromChildGrabSlotTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BA00
			GrabObjectFromChildGrabSlotTrack::~GrabObjectFromChildGrabSlotTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171110
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabObjectFromChildGrabSlotTrack::RegisterProperties()
			{
				if (gGrabObjectFromChildGrabSlotTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabObjectFromChildGrabSlotTrack>("timeBegin", &GrabObjectFromChildGrabSlotTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabObjectFromChildGrabSlotTrack>("child", &GrabObjectFromChildGrabSlotTrack::SetChild);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabObjectFromChildGrabSlotTrack>("childGrabSlot", &GrabObjectFromChildGrabSlotTrack::SetChildGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabObjectFromChildGrabSlotTrack>("grabSlot", &GrabObjectFromChildGrabSlotTrack::SetGrabSlot);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGrabObjectFromChildGrabSlotTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EA10
			fight::TrackFactory* CreateGrabObjectFromChildGrabSlotTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabObjectFromChildGrabSlotTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F5C0
			void RegisterGrabObjectFromChildGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabObjectFromChildGrabSlotTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotExecuteTrackProperties;  // 0x1125461C

			// FUNCTION: ENGINE 0x10169D10
			bool GrabSlotExecuteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B150
			bool GrabSlotExecuteTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169D30
			fight::BranchHolder* GrabSlotExecuteTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x10169D40
			bool GrabSlotExecuteTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AA60
			fight::Property* GrabSlotExecuteTrack::GetProperty(int index)
			{
				return gGrabSlotExecuteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AA80
			void GrabSlotExecuteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotExecuteTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BA10
			GrabSlotExecuteTrack::GrabSlotExecuteTrack() : receiverBranch(0), timeBegin(0.0f), interruptPriority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BA60
			float GrabSlotExecuteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BA70
			float GrabSlotExecuteTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BA80
			GrabSlotExecuteTrack::~GrabSlotExecuteTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171260
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotExecuteTrack::RegisterProperties()
			{
				if (gGrabSlotExecuteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotExecuteTrack>("timeBegin", &GrabSlotExecuteTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotExecuteTrack>("grabSlot", &GrabSlotExecuteTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyBranch<GrabSlotExecuteTrack>("receiverBranch", &GrabSlotExecuteTrack::SetReceiverBranch);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<GrabSlotExecuteTrack>("interruptPriority", &GrabSlotExecuteTrack::SetInterruptPriority);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotExecuteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EA40
			fight::TrackFactory* CreateGrabSlotExecuteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotExecuteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F5F0
			void RegisterGrabSlotExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotExecuteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabTargetClearTrackProperties;  // 0x11254620

			// FUNCTION: ENGINE 0x10169D50
			bool GrabTargetClearTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AA90
			fight::Property* GrabTargetClearTrack::GetProperty(int index)
			{
				return gGrabTargetClearTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AAB0
			void GrabTargetClearTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabTargetClearTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016AAC0
			GrabTargetClearTrack::GrabTargetClearTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016AAF0
			float GrabTargetClearTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AB00
			float GrabTargetClearTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016AB10
			GrabTargetClearTrack::~GrabTargetClearTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016EFD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabTargetClearTrack::RegisterProperties()
			{
				if (gGrabTargetClearTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabTargetClearTrack>("timeBegin", &GrabTargetClearTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabTargetClearTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EA70
			fight::TrackFactory* CreateGrabTargetClearTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabTargetClearTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F620
			void RegisterGrabTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabTargetClearTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotDeathTrackProperties;  // 0x11254624

			// FUNCTION: ENGINE 0x10169D70
			bool GrabSlotDeathTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B170
			bool GrabSlotDeathTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AB20
			fight::Property* GrabSlotDeathTrack::GetProperty(int index)
			{
				return gGrabSlotDeathTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AB40
			void GrabSlotDeathTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotDeathTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BAD0
			GrabSlotDeathTrack::GrabSlotDeathTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BB10
			float GrabSlotDeathTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BB20
			float GrabSlotDeathTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BB30
			GrabSlotDeathTrack::~GrabSlotDeathTrack()
			{
			}

			// FUNCTION: ENGINE 0x101713B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotDeathTrack::RegisterProperties()
			{
				if (gGrabSlotDeathTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotDeathTrack>("timeBegin", &GrabSlotDeathTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotDeathTrack>("grabSlot", &GrabSlotDeathTrack::SetGrabSlot);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotDeathTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EAA0
			fight::TrackFactory* CreateGrabSlotDeathTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDeathTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F650
			void RegisterGrabSlotDeathTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotDeathTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReactionHitGrabTrackProperties;  // 0x11254628

			// FUNCTION: ENGINE 0x10169D90
			bool ReactionHitGrabTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169DB0
			bool ReactionHitGrabTrack::SetObject(int newValue)
			{
				object = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169DC0
			bool ReactionHitGrabTrack::SetReverseAttachment(bool newValue)
			{
				reverseAttachment = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B190
			bool ReactionHitGrabTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B1B0
			bool ReactionHitGrabTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169DD0
			bool ReactionHitGrabTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169DF0
			bool ReactionHitGrabTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B1D0
			bool ReactionHitGrabTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169E40
			bool ReactionHitGrabTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169E60
			bool ReactionHitGrabTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10169EB0
			bool ReactionHitGrabTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AB50
			fight::Property* ReactionHitGrabTrack::GetProperty(int index)
			{
				return gReactionHitGrabTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AB70
			void ReactionHitGrabTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitGrabTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BB40
			ReactionHitGrabTrack::ReactionHitGrabTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), object(0), reverseAttachment(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BBF0
			float ReactionHitGrabTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BC00
			float ReactionHitGrabTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BC10
			ReactionHitGrabTrack::~ReactionHitGrabTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171490
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitGrabTrack::RegisterProperties()
			{
				if (gReactionHitGrabTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitGrabTrack>("timeBegin", &ReactionHitGrabTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitGrabTrack>("object", gReactionHitGrabTrackObjectTable, gReactionHitGrabTrackObjectCount, &ReactionHitGrabTrack::SetObject);
					properties[1] = property;
					property = new fight::PropertyBool<ReactionHitGrabTrack>("reverseAttachment", &ReactionHitGrabTrack::SetReverseAttachment);
					properties[2] = property;
					property = new fight::PropertyNameList<ReactionHitGrabTrack>("grabSlot", &ReactionHitGrabTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyNameList<ReactionHitGrabTrack>("parentJoint", &ReactionHitGrabTrack::SetParentJoint);
					properties[4] = property;
					property = new fight::PropertyVector<ReactionHitGrabTrack>("parentPositionOffset", &ReactionHitGrabTrack::SetParentPositionOffset);
					properties[5] = property;
					property = new fight::PropertyVector<ReactionHitGrabTrack>("parentRotationOffset", &ReactionHitGrabTrack::SetParentRotationOffset);
					properties[6] = property;
					property = new fight::PropertyNameList<ReactionHitGrabTrack>("childJoint", &ReactionHitGrabTrack::SetChildJoint);
					properties[7] = property;
					property = new fight::PropertyVector<ReactionHitGrabTrack>("childPositionOffset", &ReactionHitGrabTrack::SetChildPositionOffset);
					properties[8] = property;
					property = new fight::PropertyVector<ReactionHitGrabTrack>("childRotationOffset", &ReactionHitGrabTrack::SetChildRotationOffset);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitGrabTrack>("blendTime", &ReactionHitGrabTrack::SetBlendTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gReactionHitGrabTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EAD0
			fight::TrackFactory* CreateReactionHitGrabTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitGrabTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F680
			void RegisterReactionHitGrabTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitGrabTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetGrabIntersectionPropertiesTrackProperties;  // 0x1125462C

			// FUNCTION: ENGINE 0x10169ED0
			bool SetGrabIntersectionPropertiesTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169EF0
			bool SetGrabIntersectionPropertiesTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B1F0
			bool SetGrabIntersectionPropertiesTrack::SetIntersectionProperties(const fight::Name& newValue)
			{
				intersectionProperties = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169F10
			bool SetGrabIntersectionPropertiesTrack::SetTemporary(bool newValue)
			{
				temporary = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AB80
			fight::Property* SetGrabIntersectionPropertiesTrack::GetProperty(int index)
			{
				return gSetGrabIntersectionPropertiesTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016ABA0
			void SetGrabIntersectionPropertiesTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetGrabIntersectionPropertiesTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BC20
			SetGrabIntersectionPropertiesTrack::SetGrabIntersectionPropertiesTrack() : timeBegin(0.0f), timeEnd(-1.0f), temporary(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BC70
			float SetGrabIntersectionPropertiesTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BC80
			float SetGrabIntersectionPropertiesTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BC90
			SetGrabIntersectionPropertiesTrack::~SetGrabIntersectionPropertiesTrack()
			{
			}

			// FUNCTION: ENGINE 0x101717B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetGrabIntersectionPropertiesTrack::RegisterProperties()
			{
				if (gSetGrabIntersectionPropertiesTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetGrabIntersectionPropertiesTrack>("timeBegin", &SetGrabIntersectionPropertiesTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetGrabIntersectionPropertiesTrack>("timeEnd", &SetGrabIntersectionPropertiesTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SetGrabIntersectionPropertiesTrack>("intersectionProperties", &SetGrabIntersectionPropertiesTrack::SetIntersectionProperties);
					properties[2] = property;
					property = new fight::PropertyBool<SetGrabIntersectionPropertiesTrack>("temporary", &SetGrabIntersectionPropertiesTrack::SetTemporary);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gSetGrabIntersectionPropertiesTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EB00
			fight::TrackFactory* CreateSetGrabIntersectionPropertiesTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetGrabIntersectionPropertiesTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F6B0
			void RegisterSetGrabIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetGrabIntersectionPropertiesTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedPlaybackTrackProperties;  // 0x11254630

			// FUNCTION: ENGINE 0x10169F20
			bool GrabbedPlaybackTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B210
			bool GrabbedPlaybackTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B230
			bool GrabbedPlaybackTrack::SetState(const fight::Name& newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B250
			bool GrabbedPlaybackTrack::SetSpecificPlaybackSet(const fight::Name& newValue)
			{
				specificPlaybackSet = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169F40
			bool GrabbedPlaybackTrack::SetNotifyOnPlaybackFinished(bool newValue)
			{
				notifyOnPlaybackFinished = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016ABB0
			fight::Property* GrabbedPlaybackTrack::GetProperty(int index)
			{
				return gGrabbedPlaybackTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016ABD0
			void GrabbedPlaybackTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedPlaybackTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BCA0
			GrabbedPlaybackTrack::GrabbedPlaybackTrack() : timeBegin(0.0f), notifyOnPlaybackFinished(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BCF0
			float GrabbedPlaybackTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BD00
			float GrabbedPlaybackTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BD10
			GrabbedPlaybackTrack::~GrabbedPlaybackTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedPlaybackTrack::RegisterProperties()
			{
				if (gGrabbedPlaybackTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedPlaybackTrack>("timeBegin", &GrabbedPlaybackTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabbedPlaybackTrack>("grabSlot", &GrabbedPlaybackTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyName<GrabbedPlaybackTrack>("state", &GrabbedPlaybackTrack::SetState);
					properties[2] = property;
					property = new fight::PropertyName<GrabbedPlaybackTrack>("specificPlaybackSet", &GrabbedPlaybackTrack::SetSpecificPlaybackSet);
					properties[3] = property;
					property = new fight::PropertyBool<GrabbedPlaybackTrack>("notifyOnPlaybackFinished", &GrabbedPlaybackTrack::SetNotifyOnPlaybackFinished);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gGrabbedPlaybackTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EB30
			fight::TrackFactory* CreateGrabbedPlaybackTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedPlaybackTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F6E0
			void RegisterGrabbedPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedPlaybackTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAllowGrabbingTrackProperties;  // 0x11254634

			// FUNCTION: ENGINE 0x10169F50
			bool AllowGrabbingTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169F70
			bool AllowGrabbingTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169F90
			bool AllowGrabbingTrack::SetOnBegin(int newValue)
			{
				onBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169FA0
			bool AllowGrabbingTrack::SetOnEnd(int newValue)
			{
				onEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016ABE0
			fight::Property* AllowGrabbingTrack::GetProperty(int index)
			{
				return gAllowGrabbingTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AC00
			void AllowGrabbingTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAllowGrabbingTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016AC10
			AllowGrabbingTrack::AllowGrabbingTrack() : timeBegin(0.0f), timeEnd(-1.0f), onBegin(0), onEnd(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016AC60
			float AllowGrabbingTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AC70
			float AllowGrabbingTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AC80
			AllowGrabbingTrack::~AllowGrabbingTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016F070
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AllowGrabbingTrack::RegisterProperties()
			{
				if (gAllowGrabbingTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AllowGrabbingTrack>("timeBegin", &AllowGrabbingTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AllowGrabbingTrack>("timeEnd", &AllowGrabbingTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<AllowGrabbingTrack>("onBegin", gAllowGrabbingTrackOnBeginTable, gAllowGrabbingTrackOnBeginCount, &AllowGrabbingTrack::SetOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<AllowGrabbingTrack>("onEnd", gAllowGrabbingTrackOnEndTable, gAllowGrabbingTrackOnEndCount, &AllowGrabbingTrack::SetOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gAllowGrabbingTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EB60
			fight::TrackFactory* CreateAllowGrabbingTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AllowGrabbingTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F710
			void RegisterAllowGrabbingTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AllowGrabbingTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDelayCollisionWithGrabbedTrackProperties;  // 0x11254638

			// FUNCTION: ENGINE 0x10169FB0
			bool DelayCollisionWithGrabbedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10169FD0
			bool DelayCollisionWithGrabbedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AC90
			fight::Property* DelayCollisionWithGrabbedTrack::GetProperty(int index)
			{
				return gDelayCollisionWithGrabbedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016ACB0
			void DelayCollisionWithGrabbedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDelayCollisionWithGrabbedTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016ACC0
			DelayCollisionWithGrabbedTrack::DelayCollisionWithGrabbedTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016AD00
			float DelayCollisionWithGrabbedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AD10
			float DelayCollisionWithGrabbedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AD20
			DelayCollisionWithGrabbedTrack::~DelayCollisionWithGrabbedTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016F1F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DelayCollisionWithGrabbedTrack::RegisterProperties()
			{
				if (gDelayCollisionWithGrabbedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DelayCollisionWithGrabbedTrack>("timeBegin", &DelayCollisionWithGrabbedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DelayCollisionWithGrabbedTrack>("timeEnd", &DelayCollisionWithGrabbedTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDelayCollisionWithGrabbedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EB90
			fight::TrackFactory* CreateDelayCollisionWithGrabbedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DelayCollisionWithGrabbedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F740
			void RegisterDelayCollisionWithGrabbedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DelayCollisionWithGrabbedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabObjectFromParentGrabSlotTrackProperties;  // 0x1125463C

			// FUNCTION: ENGINE 0x10169FF0
			bool GrabObjectFromParentGrabSlotTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B270
			bool GrabObjectFromParentGrabSlotTrack::SetParentSlot(const fight::Name& newValue)
			{
				parentSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B290
			bool GrabObjectFromParentGrabSlotTrack::SetChildSlot(const fight::Name& newValue)
			{
				childSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A010
			bool GrabObjectFromParentGrabSlotTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AD30
			fight::Property* GrabObjectFromParentGrabSlotTrack::GetProperty(int index)
			{
				return gGrabObjectFromParentGrabSlotTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AD50
			void GrabObjectFromParentGrabSlotTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabObjectFromParentGrabSlotTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BD80
			GrabObjectFromParentGrabSlotTrack::GrabObjectFromParentGrabSlotTrack() : timeBegin(0.0f), interruptPriority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BDD0
			float GrabObjectFromParentGrabSlotTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BDE0
			float GrabObjectFromParentGrabSlotTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BDF0
			GrabObjectFromParentGrabSlotTrack::~GrabObjectFromParentGrabSlotTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171A90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabObjectFromParentGrabSlotTrack::RegisterProperties()
			{
				if (gGrabObjectFromParentGrabSlotTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabObjectFromParentGrabSlotTrack>("timeBegin", &GrabObjectFromParentGrabSlotTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabObjectFromParentGrabSlotTrack>("parentSlot", &GrabObjectFromParentGrabSlotTrack::SetParentSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabObjectFromParentGrabSlotTrack>("childSlot", &GrabObjectFromParentGrabSlotTrack::SetChildSlot);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<GrabObjectFromParentGrabSlotTrack>("interruptPriority", &GrabObjectFromParentGrabSlotTrack::SetInterruptPriority);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGrabObjectFromParentGrabSlotTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EBC0
			fight::TrackFactory* CreateGrabObjectFromParentGrabSlotTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabObjectFromParentGrabSlotTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F770
			void RegisterGrabObjectFromParentGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabObjectFromParentGrabSlotTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotExecuteUsingChildTrackProperties;  // 0x11254640

			// FUNCTION: ENGINE 0x1016A020
			bool GrabSlotExecuteUsingChildTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A040
			bool GrabSlotExecuteUsingChildTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B2B0
			bool GrabSlotExecuteUsingChildTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A060
			fight::BranchHolder* GrabSlotExecuteUsingChildTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1016AD60
			fight::Property* GrabSlotExecuteUsingChildTrack::GetProperty(int index)
			{
				return gGrabSlotExecuteUsingChildTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AD80
			void GrabSlotExecuteUsingChildTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotExecuteUsingChildTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BE00
			GrabSlotExecuteUsingChildTrack::GrabSlotExecuteUsingChildTrack() : branch(0), timeBegin(0.0f), timeEnd(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BE50
			float GrabSlotExecuteUsingChildTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BE60
			float GrabSlotExecuteUsingChildTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BE70
			GrabSlotExecuteUsingChildTrack::~GrabSlotExecuteUsingChildTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171BE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotExecuteUsingChildTrack::RegisterProperties()
			{
				if (gGrabSlotExecuteUsingChildTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotExecuteUsingChildTrack>("timeBegin", &GrabSlotExecuteUsingChildTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotExecuteUsingChildTrack>("timeEnd", &GrabSlotExecuteUsingChildTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabSlotExecuteUsingChildTrack>("grabSlot", &GrabSlotExecuteUsingChildTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyBranch<GrabSlotExecuteUsingChildTrack>("branch", &GrabSlotExecuteUsingChildTrack::SetBranch);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotExecuteUsingChildTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EBF0
			fight::TrackFactory* CreateGrabSlotExecuteUsingChildTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotExecuteUsingChildTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F7A0
			void RegisterGrabSlotExecuteUsingChildTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotExecuteUsingChildTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedUpdateAttachmentTrackProperties;  // 0x11254644

			// FUNCTION: ENGINE 0x1016A070
			bool GrabbedUpdateAttachmentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B2D0
			bool GrabbedUpdateAttachmentTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A090
			bool GrabbedUpdateAttachmentTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A0B0
			bool GrabbedUpdateAttachmentTrack::SetUpdateRotationOffset(bool newValue)
			{
				updateRotationOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A0C0
			bool GrabbedUpdateAttachmentTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B2F0
			bool GrabbedUpdateAttachmentTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A110
			bool GrabbedUpdateAttachmentTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A130
			bool GrabbedUpdateAttachmentTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A180
			bool GrabbedUpdateAttachmentTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A1A0
			bool GrabbedUpdateAttachmentTrack::SetPhysicsMode(int newValue)
			{
				physicsMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AD90
			fight::Property* GrabbedUpdateAttachmentTrack::GetProperty(int index)
			{
				return gGrabbedUpdateAttachmentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016ADB0
			void GrabbedUpdateAttachmentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedUpdateAttachmentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BE90
			GrabbedUpdateAttachmentTrack::GrabbedUpdateAttachmentTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), physicsMode(0), updateRotationOffset(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016BF30
			float GrabbedUpdateAttachmentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016BF40
			float GrabbedUpdateAttachmentTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016BF50
			GrabbedUpdateAttachmentTrack::~GrabbedUpdateAttachmentTrack()
			{
			}

			// FUNCTION: ENGINE 0x10171D30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedUpdateAttachmentTrack::RegisterProperties()
			{
				if (gGrabbedUpdateAttachmentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedUpdateAttachmentTrack>("timeBegin", &GrabbedUpdateAttachmentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabbedUpdateAttachmentTrack>("parentJoint", &GrabbedUpdateAttachmentTrack::SetParentJoint);
					properties[1] = property;
					property = new fight::PropertyVector<GrabbedUpdateAttachmentTrack>("parentPositionOffset", &GrabbedUpdateAttachmentTrack::SetParentPositionOffset);
					properties[2] = property;
					property = new fight::PropertyBool<GrabbedUpdateAttachmentTrack>("updateRotationOffset", &GrabbedUpdateAttachmentTrack::SetUpdateRotationOffset);
					properties[3] = property;
					property = new fight::PropertyVector<GrabbedUpdateAttachmentTrack>("parentRotationOffset", &GrabbedUpdateAttachmentTrack::SetParentRotationOffset);
					properties[4] = property;
					property = new fight::PropertyNameList<GrabbedUpdateAttachmentTrack>("childJoint", &GrabbedUpdateAttachmentTrack::SetChildJoint);
					properties[5] = property;
					property = new fight::PropertyVector<GrabbedUpdateAttachmentTrack>("childPositionOffset", &GrabbedUpdateAttachmentTrack::SetChildPositionOffset);
					properties[6] = property;
					property = new fight::PropertyVector<GrabbedUpdateAttachmentTrack>("childRotationOffset", &GrabbedUpdateAttachmentTrack::SetChildRotationOffset);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GrabbedUpdateAttachmentTrack>("blendTime", &GrabbedUpdateAttachmentTrack::SetBlendTime);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<GrabbedUpdateAttachmentTrack>("physicsMode", gCollisionGrabTrackPhysicsModeTable, gCollisionGrabTrackPhysicsModeCount, &GrabbedUpdateAttachmentTrack::SetPhysicsMode);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gGrabbedUpdateAttachmentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EC20
			fight::TrackFactory* CreateGrabbedUpdateAttachmentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedUpdateAttachmentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F7D0
			void RegisterGrabbedUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedUpdateAttachmentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabGrabTargetTrackProperties;  // 0x11254648

			// FUNCTION: ENGINE 0x1016A1B0
			bool GrabGrabTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A1D0
			bool GrabGrabTargetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B310
			bool GrabGrabTargetTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B330
			bool GrabGrabTargetTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A1F0
			bool GrabGrabTargetTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A220
			bool GrabGrabTargetTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B350
			bool GrabGrabTargetTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A280
			bool GrabGrabTargetTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A2A0
			bool GrabGrabTargetTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A2F0
			bool GrabGrabTargetTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A310
			fight::BranchHolder* GrabGrabTargetTrack::SetGiverBranch()
			{
				return &giverBranch;
			}

			// FUNCTION: ENGINE 0x1016A320
			fight::BranchHolder* GrabGrabTargetTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x1016A330
			bool GrabGrabTargetTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016ADC0
			fight::Property* GrabGrabTargetTrack::GetProperty(int index)
			{
				return gGrabGrabTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016ADE0
			void GrabGrabTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabGrabTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016BF60
			GrabGrabTargetTrack::GrabGrabTargetTrack() : giverBranch(0), receiverBranch(0), childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), interruptPriority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016C060
			float GrabGrabTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C070
			float GrabGrabTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C080
			GrabGrabTargetTrack::~GrabGrabTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x10172010
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabGrabTargetTrack::RegisterProperties()
			{
				if (gGrabGrabTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabGrabTargetTrack>("timeBegin", &GrabGrabTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabGrabTargetTrack>("timeEnd", &GrabGrabTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabGrabTargetTrack>("grabSlot", &GrabGrabTargetTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<GrabGrabTargetTrack>("parentJoint", &GrabGrabTargetTrack::SetParentJoint);
					properties[3] = property;
					property = new fight::PropertyVector<GrabGrabTargetTrack>("parentPositionOffset", &GrabGrabTargetTrack::SetParentPositionOffset);
					properties[4] = property;
					property = new fight::PropertyVector<GrabGrabTargetTrack>("parentRotationOffset", &GrabGrabTargetTrack::SetParentRotationOffset);
					properties[5] = property;
					property = new fight::PropertyNameList<GrabGrabTargetTrack>("childJoint", &GrabGrabTargetTrack::SetChildJoint);
					properties[6] = property;
					property = new fight::PropertyVector<GrabGrabTargetTrack>("childPositionOffset", &GrabGrabTargetTrack::SetChildPositionOffset);
					properties[7] = property;
					property = new fight::PropertyVector<GrabGrabTargetTrack>("childRotationOffset", &GrabGrabTargetTrack::SetChildRotationOffset);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<GrabGrabTargetTrack>("blendTime", &GrabGrabTargetTrack::SetBlendTime);
					properties[9] = property;
					property = new fight::PropertyBranch<GrabGrabTargetTrack>("giverBranch", &GrabGrabTargetTrack::SetGiverBranch);
					properties[10] = property;
					property = new fight::PropertyBranch<GrabGrabTargetTrack>("receiverBranch", &GrabGrabTargetTrack::SetReceiverBranch);
					properties[11] = property;
					property = new fight::PropertyIntConstRange<GrabGrabTargetTrack>("interruptPriority", &GrabGrabTargetTrack::SetInterruptPriority);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gGrabGrabTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EC50
			fight::TrackFactory* CreateGrabGrabTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabGrabTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F800
			void RegisterGrabGrabTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabGrabTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotUpdateAttachmentTrackProperties;  // 0x1125464C

			// FUNCTION: ENGINE 0x1016A350
			bool GrabSlotUpdateAttachmentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B370
			bool GrabSlotUpdateAttachmentTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B390
			bool GrabSlotUpdateAttachmentTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A370
			bool GrabSlotUpdateAttachmentTrack::SetOverrideParentTranslationJoint(bool newValue)
			{
				overrideParentTranslationJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B3B0
			bool GrabSlotUpdateAttachmentTrack::SetParentTranslationJoint(const fight::Name& newValue)
			{
				parentTranslationJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A390
			bool GrabSlotUpdateAttachmentTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A3B0
			bool GrabSlotUpdateAttachmentTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B3D0
			bool GrabSlotUpdateAttachmentTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A400
			bool GrabSlotUpdateAttachmentTrack::SetOverrideChildTranslationJoint(bool newValue)
			{
				overrideChildTranslationJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B3F0
			bool GrabSlotUpdateAttachmentTrack::SetChildTranslationJoint(const fight::Name& newValue)
			{
				childTranslationJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A420
			bool GrabSlotUpdateAttachmentTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A440
			bool GrabSlotUpdateAttachmentTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A490
			bool GrabSlotUpdateAttachmentTrack::SetConsiderChildAlternateRotation(bool newValue)
			{
				considerChildAlternateRotation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A4B0
			bool GrabSlotUpdateAttachmentTrack::SetChildAlternateRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childAlternateRotationOffset.x = scaled.x;
				childAlternateRotationOffset.y = scaled.y;
				childAlternateRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A500
			bool GrabSlotUpdateAttachmentTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A520
			bool GrabSlotUpdateAttachmentTrack::SetPhysicsMode(int newValue)
			{
				physicsMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016ADF0
			fight::Property* GrabSlotUpdateAttachmentTrack::GetProperty(int index)
			{
				return gGrabSlotUpdateAttachmentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AE10
			void GrabSlotUpdateAttachmentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotUpdateAttachmentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016C0B0
			GrabSlotUpdateAttachmentTrack::GrabSlotUpdateAttachmentTrack() : childAlternateRotationOffset(0.0f, 0.0f, 0.0f), childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), physicsMode(0), considerChildAlternateRotation(false), overrideChildTranslationJoint(false), overrideParentTranslationJoint(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016C190
			float GrabSlotUpdateAttachmentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C1A0
			float GrabSlotUpdateAttachmentTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016C1B0
			GrabSlotUpdateAttachmentTrack::~GrabSlotUpdateAttachmentTrack()
			{
			}

			// FUNCTION: ENGINE 0x10172390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotUpdateAttachmentTrack::RegisterProperties()
			{
				if (gGrabSlotUpdateAttachmentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentTrack>("timeBegin", &GrabSlotUpdateAttachmentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>("grabSlot", &GrabSlotUpdateAttachmentTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>("parentJoint", &GrabSlotUpdateAttachmentTrack::SetParentJoint);
					properties[2] = property;
					property = new fight::PropertyBool<GrabSlotUpdateAttachmentTrack>("overrideParentTranslationJoint", &GrabSlotUpdateAttachmentTrack::SetOverrideParentTranslationJoint);
					properties[3] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>("parentTranslationJoint", &GrabSlotUpdateAttachmentTrack::SetParentTranslationJoint);
					properties[4] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentTrack>("parentPositionOffset", &GrabSlotUpdateAttachmentTrack::SetParentPositionOffset);
					properties[5] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentTrack>("parentRotationOffset", &GrabSlotUpdateAttachmentTrack::SetParentRotationOffset);
					properties[6] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>("childJoint", &GrabSlotUpdateAttachmentTrack::SetChildJoint);
					properties[7] = property;
					property = new fight::PropertyBool<GrabSlotUpdateAttachmentTrack>("overrideChildTranslationJoint", &GrabSlotUpdateAttachmentTrack::SetOverrideChildTranslationJoint);
					properties[8] = property;
					property = new fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>("childTranslationJoint", &GrabSlotUpdateAttachmentTrack::SetChildTranslationJoint);
					properties[9] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentTrack>("childPositionOffset", &GrabSlotUpdateAttachmentTrack::SetChildPositionOffset);
					properties[10] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentTrack>("childRotationOffset", &GrabSlotUpdateAttachmentTrack::SetChildRotationOffset);
					properties[11] = property;
					property = new fight::PropertyBool<GrabSlotUpdateAttachmentTrack>("considerChildAlternateRotation", &GrabSlotUpdateAttachmentTrack::SetConsiderChildAlternateRotation);
					properties[12] = property;
					property = new fight::PropertyVector<GrabSlotUpdateAttachmentTrack>("childAlternateRotationOffset", &GrabSlotUpdateAttachmentTrack::SetChildAlternateRotationOffset);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentTrack>("blendTime", &GrabSlotUpdateAttachmentTrack::SetBlendTime);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<GrabSlotUpdateAttachmentTrack>("physicsMode", gCollisionGrabTrackPhysicsModeTable, gCollisionGrabTrackPhysicsModeCount, &GrabSlotUpdateAttachmentTrack::SetPhysicsMode);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotUpdateAttachmentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016EC80
			fight::TrackFactory* CreateGrabSlotUpdateAttachmentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F830
			void RegisterGrabSlotUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabPlayerTrackProperties;  // 0x11254650

			// FUNCTION: ENGINE 0x1016A530
			bool GrabPlayerTrack::SetUseLocalSpace(bool newValue)
			{
				useLocalSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A540
			bool GrabPlayerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A560
			bool GrabPlayerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A580
			bool GrabPlayerTrack::SetGrabbingPlayer(int newValue)
			{
				grabbingPlayer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A590
			bool GrabPlayerTrack::SetGrabbedPlayer(int newValue)
			{
				grabbedPlayer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A5A0
			bool GrabPlayerTrack::SetActionOnEnd(int newValue)
			{
				actionOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B410
			bool GrabPlayerTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B430
			bool GrabPlayerTrack::SetParentJoint(const fight::Name& newValue)
			{
				parentJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A5B0
			bool GrabPlayerTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A5D0
			bool GrabPlayerTrack::SetParentRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				parentRotationOffset.x = scaled.x;
				parentRotationOffset.y = scaled.y;
				parentRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B450
			bool GrabPlayerTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A620
			bool GrabPlayerTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A640
			bool GrabPlayerTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A690
			bool GrabPlayerTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AE20
			fight::Property* GrabPlayerTrack::GetProperty(int index)
			{
				return gGrabPlayerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AE40
			void GrabPlayerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabPlayerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016C1C0
			GrabPlayerTrack::GrabPlayerTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), parentPositionOffset(0.0f, 0.0f, 0.0f), parentRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), actionOnEnd(0), grabbedPlayer(0), grabbingPlayer(0), useLocalSpace(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016C280
			float GrabPlayerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C290
			float GrabPlayerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C2A0
			GrabPlayerTrack::~GrabPlayerTrack()
			{
			}

			// FUNCTION: ENGINE 0x101727E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabPlayerTrack::RegisterProperties()
			{
				if (gGrabPlayerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<GrabPlayerTrack>("useLocalSpace", &GrabPlayerTrack::SetUseLocalSpace);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabPlayerTrack>("timeBegin", &GrabPlayerTrack::SetTimeBegin);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GrabPlayerTrack>("timeEnd", &GrabPlayerTrack::SetTimeEnd);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<GrabPlayerTrack>("grabbingPlayer", gGrabPlayerTrackGrabbingPlayerTable, gGrabPlayerTrackGrabbingPlayerCount, &GrabPlayerTrack::SetGrabbingPlayer);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<GrabPlayerTrack>("grabbedPlayer", gGrabPlayerTrackGrabbingPlayerTable, gGrabPlayerTrackGrabbingPlayerCount, &GrabPlayerTrack::SetGrabbedPlayer);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<GrabPlayerTrack>("actionOnEnd", gGrabPlayerTrackActionOnEndTable, gGrabPlayerTrackActionOnEndCount, &GrabPlayerTrack::SetActionOnEnd);
					properties[5] = property;
					property = new fight::PropertyNameList<GrabPlayerTrack>("grabSlot", &GrabPlayerTrack::SetGrabSlot);
					properties[6] = property;
					property = new fight::PropertyNameList<GrabPlayerTrack>("parentJoint", &GrabPlayerTrack::SetParentJoint);
					properties[7] = property;
					property = new fight::PropertyVector<GrabPlayerTrack>("parentPositionOffset", &GrabPlayerTrack::SetParentPositionOffset);
					properties[8] = property;
					property = new fight::PropertyVector<GrabPlayerTrack>("parentRotationOffset", &GrabPlayerTrack::SetParentRotationOffset);
					properties[9] = property;
					property = new fight::PropertyNameList<GrabPlayerTrack>("childJoint", &GrabPlayerTrack::SetChildJoint);
					properties[10] = property;
					property = new fight::PropertyVector<GrabPlayerTrack>("childPositionOffset", &GrabPlayerTrack::SetChildPositionOffset);
					properties[11] = property;
					property = new fight::PropertyVector<GrabPlayerTrack>("childRotationOffset", &GrabPlayerTrack::SetChildRotationOffset);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<GrabPlayerTrack>("blendTime", &GrabPlayerTrack::SetBlendTime);
					properties[13] = property;
					fight::RegisterPropertyList(properties, &gGrabPlayerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016ECB0
			fight::TrackFactory* CreateGrabPlayerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabPlayerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F860
			void RegisterGrabPlayerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabPlayerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabbedExecuteOnParentTrackProperties;  // 0x11254654

			// FUNCTION: ENGINE 0x1016A6B0
			bool GrabbedExecuteOnParentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016A6D0
			fight::BranchHolder* GrabbedExecuteOnParentTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x1016A6E0
			bool GrabbedExecuteOnParentTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AE50
			fight::Property* GrabbedExecuteOnParentTrack::GetProperty(int index)
			{
				return gGrabbedExecuteOnParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AE70
			void GrabbedExecuteOnParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedExecuteOnParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016AE80
			GrabbedExecuteOnParentTrack::GrabbedExecuteOnParentTrack() : receiverBranch(0), timeBegin(0.0f), interruptPriority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016AEC0
			float GrabbedExecuteOnParentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016AED0
			float GrabbedExecuteOnParentTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016AEE0
			GrabbedExecuteOnParentTrack::~GrabbedExecuteOnParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x1016F2D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedExecuteOnParentTrack::RegisterProperties()
			{
				if (gGrabbedExecuteOnParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabbedExecuteOnParentTrack>("timeBegin", &GrabbedExecuteOnParentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBranch<GrabbedExecuteOnParentTrack>("receiverBranch", &GrabbedExecuteOnParentTrack::SetReceiverBranch);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<GrabbedExecuteOnParentTrack>("interruptPriority", &GrabbedExecuteOnParentTrack::SetInterruptPriority);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabbedExecuteOnParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016ECE0
			fight::TrackFactory* CreateGrabbedExecuteOnParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedExecuteOnParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F890
			void RegisterGrabbedExecuteOnParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabbedExecuteOnParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrabSlotEnableStuckTestTrackProperties;  // 0x11254658

			// FUNCTION: ENGINE 0x1016A6F0
			bool GrabSlotEnableStuckTestTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016B470
			bool GrabSlotEnableStuckTestTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1016AF00
			fight::Property* GrabSlotEnableStuckTestTrack::GetProperty(int index)
			{
				return gGrabSlotEnableStuckTestTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1016AF20
			void GrabSlotEnableStuckTestTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotEnableStuckTestTrackProperties);
			}

			// FUNCTION: ENGINE 0x1016C2E0
			GrabSlotEnableStuckTestTrack::GrabSlotEnableStuckTestTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1016C320
			float GrabSlotEnableStuckTestTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1016C330
			float GrabSlotEnableStuckTestTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1016C340
			GrabSlotEnableStuckTestTrack::~GrabSlotEnableStuckTestTrack()
			{
			}

			// FUNCTION: ENGINE 0x10172BD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotEnableStuckTestTrack::RegisterProperties()
			{
				if (gGrabSlotEnableStuckTestTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrabSlotEnableStuckTestTrack>("timeBegin", &GrabSlotEnableStuckTestTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabSlotEnableStuckTestTrack>("grabSlot", &GrabSlotEnableStuckTestTrack::SetGrabSlot);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotEnableStuckTestTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1016ED10
			fight::TrackFactory* CreateGrabSlotEnableStuckTestTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotEnableStuckTestTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1016F8C0
			void RegisterGrabSlotEnableStuckTestTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrabSlotEnableStuckTestTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::PropertyNameList<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::PropertyVector<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::PropertyEnumConstList<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentWithRestoreTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotDetachThrowTrack>;
			template class fight::PropertyNameList<GrabSlotDetachThrowTrack>;
			template class fight::PropertyEnumConstList<GrabSlotDetachThrowTrack>;
			template class fight::PropertyVector<GrabSlotDetachThrowTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotDetachThrowTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotDetachThrowTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotDetachTrack>;
			template class fight::PropertyNameList<GrabSlotDetachTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotDetachTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotDetachTrack>;
			template class fight::PropertyFloatConstRange<GrabSetGrabbingTimerTrack>;
			template class fight::PropertyBool<GrabSetGrabbingTimerTrack>;
			template class fight::TrackFactoryTemplate<GrabSetGrabbingTimerTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSetGrabbingTimerTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotSwapTrack>;
			template class fight::PropertyNameList<GrabSlotSwapTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotSwapTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotSwapTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotReverseAttachmentTrack>;
			template class fight::PropertyNameList<GrabSlotReverseAttachmentTrack>;
			template class fight::PropertyVector<GrabSlotReverseAttachmentTrack>;
			template class fight::PropertyBool<GrabSlotReverseAttachmentTrack>;
			template class fight::PropertyEnumConstList<GrabSlotReverseAttachmentTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotReverseAttachmentTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotReverseAttachmentTrack>;
			template class fight::PropertyFloatConstRange<GrabbedExecuteUsingParentTrack>;
			template class fight::PropertyBranch<GrabbedExecuteUsingParentTrack>;
			template class fight::TrackFactoryTemplate<GrabbedExecuteUsingParentTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedExecuteUsingParentTrack>;
			template class fight::PropertyFloatConstRange<GrabbedSwapGrabberSlotsTrack>;
			template class fight::PropertyNameList<GrabbedSwapGrabberSlotsTrack>;
			template class fight::TrackFactoryTemplate<GrabbedSwapGrabberSlotsTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedSwapGrabberSlotsTrack>;
			template class fight::PropertyFloatConstRange<GrabButtonStruggleTrack>;
			template class fight::PropertyNameList<GrabButtonStruggleTrack>;
			template class fight::TrackFactoryTemplate<GrabButtonStruggleTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabButtonStruggleTrack>;
			template class fight::PropertyFloatConstRange<GrabbedDetachTrack>;
			template class fight::TrackFactoryTemplate<GrabbedDetachTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedDetachTrack>;
			template class fight::PropertyFloatConstRange<GrabObjectFromChildGrabSlotTrack>;
			template class fight::PropertyNameList<GrabObjectFromChildGrabSlotTrack>;
			template class fight::TrackFactoryTemplate<GrabObjectFromChildGrabSlotTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabObjectFromChildGrabSlotTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotExecuteTrack>;
			template class fight::PropertyNameList<GrabSlotExecuteTrack>;
			template class fight::PropertyBranch<GrabSlotExecuteTrack>;
			template class fight::PropertyIntConstRange<GrabSlotExecuteTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotExecuteTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotExecuteTrack>;
			template class fight::PropertyFloatConstRange<GrabTargetClearTrack>;
			template class fight::TrackFactoryTemplate<GrabTargetClearTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabTargetClearTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotDeathTrack>;
			template class fight::PropertyNameList<GrabSlotDeathTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotDeathTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotDeathTrack>;
			template class fight::PropertyFloatConstRange<ReactionHitGrabTrack>;
			template class fight::PropertyEnumConstList<ReactionHitGrabTrack>;
			template class fight::PropertyBool<ReactionHitGrabTrack>;
			template class fight::PropertyNameList<ReactionHitGrabTrack>;
			template class fight::PropertyVector<ReactionHitGrabTrack>;
			template class fight::TrackFactoryTemplate<ReactionHitGrabTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionHitGrabTrack>;
			template class fight::PropertyFloatConstRange<SetGrabIntersectionPropertiesTrack>;
			template class fight::PropertyName<SetGrabIntersectionPropertiesTrack>;
			template class fight::PropertyBool<SetGrabIntersectionPropertiesTrack>;
			template class fight::TrackFactoryTemplate<SetGrabIntersectionPropertiesTrack>;
			template class fight::TrackFactoryCasterTemplate<SetGrabIntersectionPropertiesTrack>;
			template class fight::PropertyFloatConstRange<GrabbedPlaybackTrack>;
			template class fight::PropertyNameList<GrabbedPlaybackTrack>;
			template class fight::PropertyName<GrabbedPlaybackTrack>;
			template class fight::PropertyBool<GrabbedPlaybackTrack>;
			template class fight::TrackFactoryTemplate<GrabbedPlaybackTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedPlaybackTrack>;
			template class fight::PropertyFloatConstRange<AllowGrabbingTrack>;
			template class fight::PropertyEnumConstList<AllowGrabbingTrack>;
			template class fight::TrackFactoryTemplate<AllowGrabbingTrack>;
			template class fight::TrackFactoryCasterTemplate<AllowGrabbingTrack>;
			template class fight::PropertyFloatConstRange<DelayCollisionWithGrabbedTrack>;
			template class fight::TrackFactoryTemplate<DelayCollisionWithGrabbedTrack>;
			template class fight::TrackFactoryCasterTemplate<DelayCollisionWithGrabbedTrack>;
			template class fight::PropertyFloatConstRange<GrabObjectFromParentGrabSlotTrack>;
			template class fight::PropertyNameList<GrabObjectFromParentGrabSlotTrack>;
			template class fight::PropertyIntConstRange<GrabObjectFromParentGrabSlotTrack>;
			template class fight::TrackFactoryTemplate<GrabObjectFromParentGrabSlotTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabObjectFromParentGrabSlotTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotExecuteUsingChildTrack>;
			template class fight::PropertyNameList<GrabSlotExecuteUsingChildTrack>;
			template class fight::PropertyBranch<GrabSlotExecuteUsingChildTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotExecuteUsingChildTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotExecuteUsingChildTrack>;
			template class fight::PropertyFloatConstRange<GrabbedUpdateAttachmentTrack>;
			template class fight::PropertyNameList<GrabbedUpdateAttachmentTrack>;
			template class fight::PropertyVector<GrabbedUpdateAttachmentTrack>;
			template class fight::PropertyBool<GrabbedUpdateAttachmentTrack>;
			template class fight::PropertyEnumConstList<GrabbedUpdateAttachmentTrack>;
			template class fight::TrackFactoryTemplate<GrabbedUpdateAttachmentTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedUpdateAttachmentTrack>;
			template class fight::PropertyFloatConstRange<GrabGrabTargetTrack>;
			template class fight::PropertyNameList<GrabGrabTargetTrack>;
			template class fight::PropertyVector<GrabGrabTargetTrack>;
			template class fight::PropertyBranch<GrabGrabTargetTrack>;
			template class fight::PropertyIntConstRange<GrabGrabTargetTrack>;
			template class fight::TrackFactoryTemplate<GrabGrabTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabGrabTargetTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotUpdateAttachmentTrack>;
			template class fight::PropertyNameList<GrabSlotUpdateAttachmentTrack>;
			template class fight::PropertyBool<GrabSlotUpdateAttachmentTrack>;
			template class fight::PropertyVector<GrabSlotUpdateAttachmentTrack>;
			template class fight::PropertyEnumConstList<GrabSlotUpdateAttachmentTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotUpdateAttachmentTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotUpdateAttachmentTrack>;
			template class fight::PropertyBool<GrabPlayerTrack>;
			template class fight::PropertyFloatConstRange<GrabPlayerTrack>;
			template class fight::PropertyEnumConstList<GrabPlayerTrack>;
			template class fight::PropertyNameList<GrabPlayerTrack>;
			template class fight::PropertyVector<GrabPlayerTrack>;
			template class fight::TrackFactoryTemplate<GrabPlayerTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabPlayerTrack>;
			template class fight::PropertyFloatConstRange<GrabbedExecuteOnParentTrack>;
			template class fight::PropertyBranch<GrabbedExecuteOnParentTrack>;
			template class fight::PropertyIntConstRange<GrabbedExecuteOnParentTrack>;
			template class fight::TrackFactoryTemplate<GrabbedExecuteOnParentTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabbedExecuteOnParentTrack>;
			template class fight::PropertyFloatConstRange<GrabSlotEnableStuckTestTrack>;
			template class fight::PropertyNameList<GrabSlotEnableStuckTestTrack>;
			template class fight::TrackFactoryTemplate<GrabSlotEnableStuckTestTrack>;
			template class fight::TrackFactoryCasterTemplate<GrabSlotEnableStuckTestTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1016B6A0
// FUNCTION: ENGINE 0x1016B820
// FUNCTION: ENGINE 0x1016B960
// FUNCTION: ENGINE 0x1016BAA0
// FUNCTION: ENGINE 0x1016BD20
// FUNCTION: ENGINE 0x1016BD50
// FUNCTION: ENGINE 0x1016C2B0
// FUNCTION: ENGINE 0x1016C350
// FUNCTION: ENGINE 0x1016C360
// FUNCTION: ENGINE 0x1016C390
// FUNCTION: ENGINE 0x1016C3A0
// FUNCTION: ENGINE 0x1016C3D0
// FUNCTION: ENGINE 0x1016C3E0
// FUNCTION: ENGINE 0x1016C410
// FUNCTION: ENGINE 0x1016C420
// FUNCTION: ENGINE 0x1016C450
// FUNCTION: ENGINE 0x1016C460
// FUNCTION: ENGINE 0x1016C490
// FUNCTION: ENGINE 0x1016C4A0
// FUNCTION: ENGINE 0x1016C4D0
// FUNCTION: ENGINE 0x1016C4E0
// FUNCTION: ENGINE 0x1016C510
// FUNCTION: ENGINE 0x1016C520
// FUNCTION: ENGINE 0x1016C550
// FUNCTION: ENGINE 0x1016C560
// FUNCTION: ENGINE 0x1016C590
// FUNCTION: ENGINE 0x1016C5A0
// FUNCTION: ENGINE 0x1016C5D0
// FUNCTION: ENGINE 0x1016C5E0
// FUNCTION: ENGINE 0x1016C610
// FUNCTION: ENGINE 0x1016C620
// FUNCTION: ENGINE 0x1016C650
// FUNCTION: ENGINE 0x1016C660
// FUNCTION: ENGINE 0x1016C690
// FUNCTION: ENGINE 0x1016C6A0
// FUNCTION: ENGINE 0x1016C6D0
// FUNCTION: ENGINE 0x1016C6E0
// FUNCTION: ENGINE 0x1016C710
// FUNCTION: ENGINE 0x1016C720
// FUNCTION: ENGINE 0x1016C750
// FUNCTION: ENGINE 0x1016C760
// FUNCTION: ENGINE 0x1016C790
// FUNCTION: ENGINE 0x1016C7A0
// FUNCTION: ENGINE 0x1016C7D0
// FUNCTION: ENGINE 0x1016C7E0
// FUNCTION: ENGINE 0x1016C810
// FUNCTION: ENGINE 0x1016C820
// FUNCTION: ENGINE 0x1016C850
// FUNCTION: ENGINE 0x1016C860
// FUNCTION: ENGINE 0x1016C890
// FUNCTION: ENGINE 0x1016C8A0
// FUNCTION: ENGINE 0x1016C8D0
// FUNCTION: ENGINE 0x1016C8E0
// FUNCTION: ENGINE 0x1016C910
// FUNCTION: ENGINE 0x1016C920
// FUNCTION: ENGINE 0x1016C950
// FUNCTION: ENGINE 0x1016C960
// FUNCTION: ENGINE 0x1016C990
// FUNCTION: ENGINE 0x1016C9A0
// FUNCTION: ENGINE 0x1016C9D0
// FUNCTION: ENGINE 0x1016C9E0
// FUNCTION: ENGINE 0x1016CA10
// FUNCTION: ENGINE 0x1016CA40
// FUNCTION: ENGINE 0x1016CA70
// FUNCTION: ENGINE 0x1016CAA0
// FUNCTION: ENGINE 0x1016CAD0
// FUNCTION: ENGINE 0x1016CB00
// FUNCTION: ENGINE 0x1016CB30
// FUNCTION: ENGINE 0x1016CB60
// FUNCTION: ENGINE 0x1016CB90
// FUNCTION: ENGINE 0x1016CBC0
// FUNCTION: ENGINE 0x1016CBF0
// FUNCTION: ENGINE 0x1016CC20
// FUNCTION: ENGINE 0x1016CC50
// FUNCTION: ENGINE 0x1016CC80
// FUNCTION: ENGINE 0x1016CCB0
// FUNCTION: ENGINE 0x1016CCE0
// FUNCTION: ENGINE 0x1016CD10
// FUNCTION: ENGINE 0x1016CD40
// FUNCTION: ENGINE 0x1016CD70
// FUNCTION: ENGINE 0x1016CDA0
// FUNCTION: ENGINE 0x1016CDD0
// FUNCTION: ENGINE 0x1016CE00
// FUNCTION: ENGINE 0x1016CE30
// FUNCTION: ENGINE 0x1016CE40
// FUNCTION: ENGINE 0x1016CE70
// FUNCTION: ENGINE 0x1016CE90
// FUNCTION: ENGINE 0x1016CEA0
// FUNCTION: ENGINE 0x1016CEE0
// FUNCTION: ENGINE 0x1016CEF0
// FUNCTION: ENGINE 0x1016CF20
// FUNCTION: ENGINE 0x1016CF40
// FUNCTION: ENGINE 0x1016CF50
// FUNCTION: ENGINE 0x1016CF80
// FUNCTION: ENGINE 0x1016CFB0
// FUNCTION: ENGINE 0x1016CFC0
// FUNCTION: ENGINE 0x1016D000
// FUNCTION: ENGINE 0x1016D010
// FUNCTION: ENGINE 0x1016D040
// FUNCTION: ENGINE 0x1016D060
// FUNCTION: ENGINE 0x1016D070
// FUNCTION: ENGINE 0x1016D0A0
// FUNCTION: ENGINE 0x1016D0C0
// FUNCTION: ENGINE 0x1016D0D0
// FUNCTION: ENGINE 0x1016D100
// FUNCTION: ENGINE 0x1016D130
// FUNCTION: ENGINE 0x1016D140
// FUNCTION: ENGINE 0x1016D170
// FUNCTION: ENGINE 0x1016D1A0
// FUNCTION: ENGINE 0x1016D1B0
// FUNCTION: ENGINE 0x1016D1E0
// FUNCTION: ENGINE 0x1016D200
// FUNCTION: ENGINE 0x1016D210
// FUNCTION: ENGINE 0x1016D240
// FUNCTION: ENGINE 0x1016D270
// FUNCTION: ENGINE 0x1016D280
// FUNCTION: ENGINE 0x1016D2B0
// FUNCTION: ENGINE 0x1016D2E0
// FUNCTION: ENGINE 0x1016D2F0
// FUNCTION: ENGINE 0x1016D320
// FUNCTION: ENGINE 0x1016D340
// FUNCTION: ENGINE 0x1016D350
// FUNCTION: ENGINE 0x1016D380
// FUNCTION: ENGINE 0x1016D3A0
// FUNCTION: ENGINE 0x1016D3B0
// FUNCTION: ENGINE 0x1016D3F0
// FUNCTION: ENGINE 0x1016D400
// FUNCTION: ENGINE 0x1016D430
// FUNCTION: ENGINE 0x1016D450
// FUNCTION: ENGINE 0x1016D460
// FUNCTION: ENGINE 0x1016D490
// FUNCTION: ENGINE 0x1016D4C0
// FUNCTION: ENGINE 0x1016D4D0
// FUNCTION: ENGINE 0x1016D500
// FUNCTION: ENGINE 0x1016D520
// FUNCTION: ENGINE 0x1016D550
// FUNCTION: ENGINE 0x1016D580
// FUNCTION: ENGINE 0x1016D590
// FUNCTION: ENGINE 0x1016D5C0
// FUNCTION: ENGINE 0x1016D5F0
// FUNCTION: ENGINE 0x1016D600
// FUNCTION: ENGINE 0x1016D630
// FUNCTION: ENGINE 0x1016D660
// FUNCTION: ENGINE 0x1016D670
// FUNCTION: ENGINE 0x1016D6A0
// FUNCTION: ENGINE 0x1016D6D0
// FUNCTION: ENGINE 0x1016D6E0
// FUNCTION: ENGINE 0x1016D710
// FUNCTION: ENGINE 0x1016D740
// FUNCTION: ENGINE 0x1016D750
// FUNCTION: ENGINE 0x1016D780
// FUNCTION: ENGINE 0x1016D7A0
// FUNCTION: ENGINE 0x1016D7D0
// FUNCTION: ENGINE 0x1016D7F0
// FUNCTION: ENGINE 0x1016D800
// FUNCTION: ENGINE 0x1016D830
// FUNCTION: ENGINE 0x1016D860
// FUNCTION: ENGINE 0x1016D870
// FUNCTION: ENGINE 0x1016D8A0
// FUNCTION: ENGINE 0x1016D8D0
// FUNCTION: ENGINE 0x1016D8E0
// FUNCTION: ENGINE 0x1016D910
// FUNCTION: ENGINE 0x1016D940
// FUNCTION: ENGINE 0x1016D950
// FUNCTION: ENGINE 0x1016D990
// FUNCTION: ENGINE 0x1016D9A0
// FUNCTION: ENGINE 0x1016D9D0
// FUNCTION: ENGINE 0x1016D9F0
// FUNCTION: ENGINE 0x1016DA00
// FUNCTION: ENGINE 0x1016DA30
// FUNCTION: ENGINE 0x1016DA50
// FUNCTION: ENGINE 0x1016DA60
// FUNCTION: ENGINE 0x1016DA90
// FUNCTION: ENGINE 0x1016DAB0
// FUNCTION: ENGINE 0x1016DAC0
// FUNCTION: ENGINE 0x1016DAF0
// FUNCTION: ENGINE 0x1016DB20
// FUNCTION: ENGINE 0x1016DB30
// FUNCTION: ENGINE 0x1016DB60
// FUNCTION: ENGINE 0x1016DB80
// FUNCTION: ENGINE 0x1016DB90
// FUNCTION: ENGINE 0x1016DBC0
// FUNCTION: ENGINE 0x1016DBF0
// FUNCTION: ENGINE 0x1016DC00
// FUNCTION: ENGINE 0x1016DC30
// FUNCTION: ENGINE 0x1016DC50
// FUNCTION: ENGINE 0x1016DC60
// FUNCTION: ENGINE 0x1016DC90
// FUNCTION: ENGINE 0x1016DCC0
// FUNCTION: ENGINE 0x1016DCD0
// FUNCTION: ENGINE 0x1016DD10
// FUNCTION: ENGINE 0x1016DD20
// FUNCTION: ENGINE 0x1016DD50
// FUNCTION: ENGINE 0x1016DD70
// FUNCTION: ENGINE 0x1016DD80
// FUNCTION: ENGINE 0x1016DDB0
// FUNCTION: ENGINE 0x1016DDE0
// FUNCTION: ENGINE 0x1016DDF0
// FUNCTION: ENGINE 0x1016DE20
// FUNCTION: ENGINE 0x1016DE50
// FUNCTION: ENGINE 0x1016DE60
// FUNCTION: ENGINE 0x1016DE90
// FUNCTION: ENGINE 0x1016DEB0
// FUNCTION: ENGINE 0x1016DEC0
// FUNCTION: ENGINE 0x1016DEF0
// FUNCTION: ENGINE 0x1016DF20
// FUNCTION: ENGINE 0x1016DF30
// FUNCTION: ENGINE 0x1016DF60
// FUNCTION: ENGINE 0x1016DF80
// FUNCTION: ENGINE 0x1016DFB0
// FUNCTION: ENGINE 0x1016DFE0
// FUNCTION: ENGINE 0x1016DFF0
// FUNCTION: ENGINE 0x1016E020
// FUNCTION: ENGINE 0x1016E040
// FUNCTION: ENGINE 0x1016E050
// FUNCTION: ENGINE 0x1016E080
// FUNCTION: ENGINE 0x1016E0A0
// FUNCTION: ENGINE 0x1016E0B0
// FUNCTION: ENGINE 0x1016E0F0
// FUNCTION: ENGINE 0x1016E100
// FUNCTION: ENGINE 0x1016E130
// FUNCTION: ENGINE 0x1016E150
// FUNCTION: ENGINE 0x1016E160
// FUNCTION: ENGINE 0x1016E190
// FUNCTION: ENGINE 0x1016E1C0
// FUNCTION: ENGINE 0x1016E1D0
// FUNCTION: ENGINE 0x1016E200
// FUNCTION: ENGINE 0x1016E220
// FUNCTION: ENGINE 0x1016E230
// FUNCTION: ENGINE 0x1016E260
// FUNCTION: ENGINE 0x1016E280
// FUNCTION: ENGINE 0x1016E2B0
// FUNCTION: ENGINE 0x1016E2D0
// FUNCTION: ENGINE 0x1016E2E0
// FUNCTION: ENGINE 0x1016E310
// FUNCTION: ENGINE 0x1016E340
// FUNCTION: ENGINE 0x1016E350
// FUNCTION: ENGINE 0x1016E380
// FUNCTION: ENGINE 0x1016E3A0
// FUNCTION: ENGINE 0x1016E3B0
// FUNCTION: ENGINE 0x1016E3E0
// FUNCTION: ENGINE 0x1016E400
// FUNCTION: ENGINE 0x1016E410
// FUNCTION: ENGINE 0x1016E450
// FUNCTION: ENGINE 0x1016E460
// FUNCTION: ENGINE 0x1016E490
// FUNCTION: ENGINE 0x1016E4B0
// FUNCTION: ENGINE 0x1016E4C0
// FUNCTION: ENGINE 0x1016E4F0
// FUNCTION: ENGINE 0x1016E510
// FUNCTION: ENGINE 0x1016E520
// FUNCTION: ENGINE 0x1016E550
// FUNCTION: ENGINE 0x1016E580
// FUNCTION: ENGINE 0x1016E590
// FUNCTION: ENGINE 0x1016E5D0
// FUNCTION: ENGINE 0x1016E5E0
// FUNCTION: ENGINE 0x1016E610
// FUNCTION: ENGINE 0x1016E630
// FUNCTION: ENGINE 0x1016E640
// FUNCTION: ENGINE 0x1016E670
// FUNCTION: ENGINE 0x1016E690
// FUNCTION: ENGINE 0x1016E6A0
// FUNCTION: ENGINE 0x1016E6D0
// FUNCTION: ENGINE 0x1016E700
// FUNCTION: ENGINE 0x1016E710
// FUNCTION: ENGINE 0x1016E740
// FUNCTION: ENGINE 0x1016E760
// FUNCTION: ENGINE 0x1016E790
// FUNCTION: ENGINE 0x1016E7B0
// FUNCTION: ENGINE 0x1016E7C0
// FUNCTION: ENGINE 0x1016E7F0
// FUNCTION: ENGINE 0x1016E820
// FUNCTION: ENGINE 0x1016F8F0
// FUNCTION: ENGINE 0x1016F920
// FUNCTION: ENGINE 0x1016F940
// FUNCTION: ENGINE 0x1016F950
// FUNCTION: ENGINE 0x1016F980
// FUNCTION: ENGINE 0x1016F9A0
// FUNCTION: ENGINE 0x1016F9B0
// FUNCTION: ENGINE 0x1016F9E0
// FUNCTION: ENGINE 0x1016FA00
// FUNCTION: ENGINE 0x1016FA10
// FUNCTION: ENGINE 0x1016FA40
// FUNCTION: ENGINE 0x1016FA60
// FUNCTION: ENGINE 0x1016FA70
// FUNCTION: ENGINE 0x1016FAA0
// FUNCTION: ENGINE 0x1016FAC0
// FUNCTION: ENGINE 0x1016FAD0
// FUNCTION: ENGINE 0x1016FB00
// FUNCTION: ENGINE 0x1016FB20
// FUNCTION: ENGINE 0x1016FB30
// FUNCTION: ENGINE 0x1016FB60
// FUNCTION: ENGINE 0x1016FB80
// FUNCTION: ENGINE 0x1016FB90
// FUNCTION: ENGINE 0x1016FBC0
// FUNCTION: ENGINE 0x1016FBE0
// FUNCTION: ENGINE 0x1016FBF0
// FUNCTION: ENGINE 0x1016FC20
// FUNCTION: ENGINE 0x1016FC40
// FUNCTION: ENGINE 0x1016FC50
// FUNCTION: ENGINE 0x1016FC80
// FUNCTION: ENGINE 0x1016FCA0
// FUNCTION: ENGINE 0x1016FCB0
// FUNCTION: ENGINE 0x1016FCE0
// FUNCTION: ENGINE 0x1016FD00
// FUNCTION: ENGINE 0x1016FD10
// FUNCTION: ENGINE 0x1016FD40
// FUNCTION: ENGINE 0x1016FD60
// FUNCTION: ENGINE 0x1016FD90
// FUNCTION: ENGINE 0x1016FDB0
// FUNCTION: ENGINE 0x1016FDC0
// FUNCTION: ENGINE 0x1016FDF0
// FUNCTION: ENGINE 0x1016FE10
// FUNCTION: ENGINE 0x1016FE40
// FUNCTION: ENGINE 0x1016FE60
// FUNCTION: ENGINE 0x1016FE70
// FUNCTION: ENGINE 0x1016FEA0
// FUNCTION: ENGINE 0x1016FEC0
// FUNCTION: ENGINE 0x1016FED0
// FUNCTION: ENGINE 0x1016FF00
// FUNCTION: ENGINE 0x1016FF20
// FUNCTION: ENGINE 0x1016FF30
// FUNCTION: ENGINE 0x1016FF60
// FUNCTION: ENGINE 0x1016FF80
// FUNCTION: ENGINE 0x1016FF90
// FUNCTION: ENGINE 0x1016FFC0
// FUNCTION: ENGINE 0x1016FFE0
// FUNCTION: ENGINE 0x1016FFF0
// FUNCTION: ENGINE 0x10170020
// FUNCTION: ENGINE 0x10170040
// FUNCTION: ENGINE 0x10170050
// FUNCTION: ENGINE 0x10170080
// FUNCTION: ENGINE 0x101700A0
// FUNCTION: ENGINE 0x101700B0
// FUNCTION: ENGINE 0x101700E0
// FUNCTION: ENGINE 0x10170100
// FUNCTION: ENGINE 0x10170130
// FUNCTION: ENGINE 0x10170150
// FUNCTION: ENGINE 0x10170180
// FUNCTION: ENGINE 0x101701A0
// FUNCTION: ENGINE 0x101701D0
// FUNCTION: ENGINE 0x101701F0
// FUNCTION: ENGINE 0x10170220
// FUNCTION: ENGINE 0x10170240
// FUNCTION: ENGINE 0x10170270
// FUNCTION: ENGINE 0x10170290
// FUNCTION: ENGINE 0x101702C0
// FUNCTION: ENGINE 0x10172CB0
// FUNCTION: ENGINE 0x10172D00
// FUNCTION: ENGINE 0x10172D50
// FUNCTION: ENGINE 0x10172DA0
// FUNCTION: ENGINE 0x10172DF0
// FUNCTION: ENGINE 0x10172E40
// FUNCTION: ENGINE 0x10172E90
// FUNCTION: ENGINE 0x10172EE0
// FUNCTION: ENGINE 0x10172F10
// FUNCTION: ENGINE 0x10172F30
// FUNCTION: ENGINE 0x10172F60
// FUNCTION: ENGINE 0x10172F80
// FUNCTION: ENGINE 0x10172FB0
// FUNCTION: ENGINE 0x10172FD0
// FUNCTION: ENGINE 0x10173000
// FUNCTION: ENGINE 0x10173020
// FUNCTION: ENGINE 0x10173050
// FUNCTION: ENGINE 0x10173070
// FUNCTION: ENGINE 0x101730A0
// FUNCTION: ENGINE 0x101730C0
// FUNCTION: ENGINE 0x101730F0
// FUNCTION: ENGINE 0x10173110
// FUNCTION: ENGINE 0x10173140
// FUNCTION: ENGINE 0x10173160
// FUNCTION: ENGINE 0x10173190
// FUNCTION: ENGINE 0x101731B0
// FUNCTION: ENGINE 0x101731E0
// FUNCTION: ENGINE 0x10173200
// FUNCTION: ENGINE 0x10173230
// FUNCTION: ENGINE 0x10173250
// FUNCTION: ENGINE 0x10173280
// FUNCTION: ENGINE 0x101732A0
// FUNCTION: ENGINE 0x101732D0
// FUNCTION: ENGINE 0x101732F0
// FUNCTION: ENGINE 0x10173320
// FUNCTION: ENGINE 0x10173340
// FUNCTION: ENGINE 0x10173370
// FUNCTION: ENGINE 0x10173390
// FUNCTION: ENGINE 0x101733C0
// FUNCTION: ENGINE 0x101733E0
// FUNCTION: ENGINE 0x10173410
// FUNCTION: ENGINE 0x10173440
// FUNCTION: ENGINE 0x10173470
// FUNCTION: ENGINE 0x101734A0
// FUNCTION: ENGINE 0x101734D0
// FUNCTION: ENGINE 0x101734F0
// FUNCTION: ENGINE 0x10173520
// FUNCTION: ENGINE 0x10173540
// FUNCTION: ENGINE 0x10173590
// FUNCTION: ENGINE 0x101735E0
// FUNCTION: ENGINE 0x10173630
// FUNCTION: ENGINE 0x10173680
// FUNCTION: ENGINE 0x101736D0
// FUNCTION: ENGINE 0x10173720
// FUNCTION: ENGINE 0x10173770
// FUNCTION: ENGINE 0x101737C0
// FUNCTION: ENGINE 0x10173810
// FUNCTION: ENGINE 0x10173860
// FUNCTION: ENGINE 0x101738B0
// FUNCTION: ENGINE 0x10173900
// FUNCTION: ENGINE 0x10173950
// FUNCTION: ENGINE 0x101739A0
// FUNCTION: ENGINE 0x101739F0
// FUNCTION: ENGINE 0x10173A40
// FUNCTION: ENGINE 0x10173A90
// FUNCTION: ENGINE 0x10173AE0
// FUNCTION: ENGINE 0x10173B30
