// Fight items of the motion group: GrabSlotUpdateAttachmentWithRestoreTrack, GrabSlotDetachThrowTrack, GrabSlotDetachTrack, GrabSetGrabbingTimerTrack, GrabSlotSwapTrack, GrabSlotReverseAttachmentTrack, GrabbedExecuteUsingParentTrack, GrabbedSwapGrabberSlotsTrack, GrabButtonStruggleTrack, GrabbedDetachTrack, GrabObjectFromChildGrabSlotTrack, GrabSlotExecuteTrack, GrabTargetClearTrack, GrabSlotDeathTrack, ReactionHitGrabTrack, SetGrabIntersectionPropertiesTrack, GrabbedPlaybackTrack, AllowGrabbingTrack, DelayCollisionWithGrabbedTrack, GrabObjectFromParentGrabSlotTrack, GrabSlotExecuteUsingChildTrack, GrabbedUpdateAttachmentTrack, GrabGrabTargetTrack, GrabSlotUpdateAttachmentTrack, GrabPlayerTrack, GrabbedExecuteOnParentTrack, GrabSlotEnableStuckTestTrack (unit 0x10169790 - 0x10173B80; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GRABTRACK_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GRABTRACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GrabSlotUpdateAttachmentWithRestoreTrack (16 vftable slots, 0x68 bytes)
			class GrabSlotUpdateAttachmentWithRestoreTrack : public fight::Track
			{
			public:
				// 0x1016B490
				GrabSlotUpdateAttachmentWithRestoreTrack();
				virtual ~GrabSlotUpdateAttachmentWithRestoreTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC1C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);
				bool SetPhysicsMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name parentJoint;  // +0x20
					math::Vector childPositionOffset;  // +0x28
					math::Vector childRotationOffset;  // +0x34
					math::Vector parentPositionOffset;  // +0x40
					math::Vector parentRotationOffset;  // +0x4C
					float blendTime;  // +0x58
					float timeBegin;  // +0x5C
					float timeEnd;  // +0x60
					int physicsMode;  // +0x64
			};

			extern fight::Property** gGrabSlotUpdateAttachmentWithRestoreTrackProperties;
			fight::TrackFactory* CreateGrabSlotUpdateAttachmentWithRestoreTrackFactory(const char* name);
			void RegisterGrabSlotUpdateAttachmentWithRestoreTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotDetachThrowTrack (16 vftable slots, 0x48 bytes)
			class GrabSlotDetachThrowTrack : public fight::Track
			{
			public:
				// 0x1016B580
				GrabSlotDetachThrowTrack();
				virtual ~GrabSlotDetachThrowTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC3A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetLatestDetachTime(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetLinearVelocityReference(int newValue);
				bool SetAddedLinearVelocity(const math::Vector& newValue);
				bool SetAngularVelocityReference(int newValue);
				bool SetAddedAngularVelocity(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					math::Vector addedAngularVelocity;  // +0x18
					math::Vector addedLinearVelocity;  // +0x24
					float latestDetachTime;  // +0x30
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					int angularVelocityReference;  // +0x3C
					int linearVelocityReference;  // +0x40
					unsigned char unknown44[0x4];
			};

			extern fight::Property** gGrabSlotDetachThrowTrackProperties;
			fight::TrackFactory* CreateGrabSlotDetachThrowTrackFactory(const char* name);
			void RegisterGrabSlotDetachThrowTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotDetachTrack (16 vftable slots, 0x20 bytes)
			class GrabSlotDetachTrack : public fight::Track
			{
			public:
				// 0x1016B630
				GrabSlotDetachTrack();
				virtual ~GrabSlotDetachTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC350, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabSlotDetachTrackProperties;
			fight::TrackFactory* CreateGrabSlotDetachTrackFactory(const char* name);
			void RegisterGrabSlotDetachTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSetGrabbingTimerTrack (16 vftable slots, 0x18 bytes)
			class GrabSetGrabbingTimerTrack : public fight::Track
			{
			public:
				// 0x1016A7D0
				GrabSetGrabbingTimerTrack();
				virtual ~GrabSetGrabbingTimerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCB70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetDuration(float newValue);
				bool SetIsGrabAttack(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float duration;  // +0x10
					bool isGrabAttack;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gGrabSetGrabbingTimerTrackProperties;
			fight::TrackFactory* CreateGrabSetGrabbingTimerTrackFactory(const char* name);
			void RegisterGrabSetGrabbingTimerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotSwapTrack (16 vftable slots, 0x28 bytes)
			class GrabSlotSwapTrack : public fight::Track
			{
			public:
				// 0x1016B6D0
				GrabSlotSwapTrack();
				virtual ~GrabSlotSwapTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC490, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSlotA(const fight::Name& newValue);
				bool SetSlotB(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name slotA;  // +0x10
					fight::Name slotB;  // +0x18
					float timeBegin;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabSlotSwapTrackProperties;
			fight::TrackFactory* CreateGrabSlotSwapTrackFactory(const char* name);
			void RegisterGrabSlotSwapTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotReverseAttachmentTrack (16 vftable slots, 0x70 bytes)
			class GrabSlotReverseAttachmentTrack : public fight::Track
			{
			public:
				// 0x1016B740
				GrabSlotReverseAttachmentTrack();
				virtual ~GrabSlotReverseAttachmentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC440, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGiverGrabSlot(const fight::Name& newValue);
				bool SetReceiverGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetUpdateRotationOffset(bool newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);
				bool SetPhysicsMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name giverGrabSlot;  // +0x18
					fight::Name parentJoint;  // +0x20
					fight::Name receiverGrabSlot;  // +0x28
					math::Vector childPositionOffset;  // +0x30
					math::Vector childRotationOffset;  // +0x3C
					math::Vector parentPositionOffset;  // +0x48
					math::Vector parentRotationOffset;  // +0x54
					float blendTime;  // +0x60
					float timeBegin;  // +0x64
					int physicsMode;  // +0x68
					bool updateRotationOffset;  // +0x6C
					unsigned char unknown6D[0x3];
			};

			extern fight::Property** gGrabSlotReverseAttachmentTrackProperties;
			fight::TrackFactory* CreateGrabSlotReverseAttachmentTrackFactory(const char* name);
			void RegisterGrabSlotReverseAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedExecuteUsingParentTrack (16 vftable slots, 0x3C bytes)
			class GrabbedExecuteUsingParentTrack : public fight::Track
			{
			public:
				// 0x1016A8D0
				GrabbedExecuteUsingParentTrack();
				virtual ~GrabbedExecuteUsingParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC940, another unit)
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

			extern fight::Property** gGrabbedExecuteUsingParentTrackProperties;
			fight::TrackFactory* CreateGrabbedExecuteUsingParentTrackFactory(const char* name);
			void RegisterGrabbedExecuteUsingParentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedSwapGrabberSlotsTrack (16 vftable slots, 0x28 bytes)
			class GrabbedSwapGrabberSlotsTrack : public fight::Track
			{
			public:
				// 0x1016B850
				GrabbedSwapGrabberSlotsTrack();
				virtual ~GrabbedSwapGrabberSlotsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC4E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSlotA(const fight::Name& newValue);
				bool SetSlotB(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name slotA;  // +0x10
					fight::Name slotB;  // +0x18
					float timeBegin;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabbedSwapGrabberSlotsTrackProperties;
			fight::TrackFactory* CreateGrabbedSwapGrabberSlotsTrackFactory(const char* name);
			void RegisterGrabbedSwapGrabberSlotsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabButtonStruggleTrack (16 vftable slots, 0x38 bytes)
			class GrabButtonStruggleTrack : public fight::Track
			{
			public:
				// 0x1016B8C0
				GrabButtonStruggleTrack();
				virtual ~GrabButtonStruggleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC580, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimeInput(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetInitialCharge(float newValue);
				bool SetAutoChargeRateMin(float newValue);
				bool SetAutoChargeRateMax(float newValue);
				bool SetButtonChargeRate(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float autoChargeRateMax;  // +0x18
					float autoChargeRateMin;  // +0x1C
					float buttonChargeRate;  // +0x20
					float initialCharge;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float timeInput;  // +0x30
					unsigned char unknown34[0x4];
			};

			extern fight::Property** gGrabButtonStruggleTrackProperties;
			fight::TrackFactory* CreateGrabButtonStruggleTrackFactory(const char* name);
			void RegisterGrabButtonStruggleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedDetachTrack (16 vftable slots, 0x14 bytes)
			class GrabbedDetachTrack : public fight::Track
			{
			public:
				// 0x1016A9E0
				GrabbedDetachTrack();
				virtual ~GrabbedDetachTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC530, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gGrabbedDetachTrackProperties;
			fight::TrackFactory* CreateGrabbedDetachTrackFactory(const char* name);
			void RegisterGrabbedDetachTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabObjectFromChildGrabSlotTrack (16 vftable slots, 0x30 bytes)
			class GrabObjectFromChildGrabSlotTrack : public fight::Track
			{
			public:
				// 0x1016B990
				GrabObjectFromChildGrabSlotTrack();
				virtual ~GrabObjectFromChildGrabSlotTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCA30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetChild(const fight::Name& newValue);
				bool SetChildGrabSlot(const fight::Name& newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name child;  // +0x10
					fight::Name childGrabSlot;  // +0x18
					fight::Name grabSlot;  // +0x20
					float timeBegin;  // +0x28
					unsigned char unknown2C[0x4];
			};

			extern fight::Property** gGrabObjectFromChildGrabSlotTrackProperties;
			fight::TrackFactory* CreateGrabObjectFromChildGrabSlotTrackFactory(const char* name);
			void RegisterGrabObjectFromChildGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotExecuteTrack (16 vftable slots, 0x48 bytes)
			class GrabSlotExecuteTrack : public fight::Track
			{
			public:
				// 0x1016BA10
				GrabSlotExecuteTrack();
				virtual ~GrabSlotExecuteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC3F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				fight::BranchHolder* SetReceiverBranch();
				bool SetInterruptPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder receiverBranch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name grabSlot;  // +0x38
					float timeBegin;  // +0x40
					int interruptPriority;  // +0x44
			};

			extern fight::Property** gGrabSlotExecuteTrackProperties;
			fight::TrackFactory* CreateGrabSlotExecuteTrackFactory(const char* name);
			void RegisterGrabSlotExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabTargetClearTrack (16 vftable slots, 0x14 bytes)
			class GrabTargetClearTrack : public fight::Track
			{
			public:
				// 0x1016AAC0
				GrabTargetClearTrack();
				virtual ~GrabTargetClearTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100C51D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gGrabTargetClearTrackProperties;
			fight::TrackFactory* CreateGrabTargetClearTrackFactory(const char* name);
			void RegisterGrabTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotDeathTrack (16 vftable slots, 0x20 bytes)
			class GrabSlotDeathTrack : public fight::Track
			{
			public:
				// 0x1016BAD0
				GrabSlotDeathTrack();
				virtual ~GrabSlotDeathTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC300, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabSlotDeathTrackProperties;
			fight::TrackFactory* CreateGrabSlotDeathTrackFactory(const char* name);
			void RegisterGrabSlotDeathTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitGrabTrack (16 vftable slots, 0x68 bytes)
			class ReactionHitGrabTrack : public fight::Track
			{
			public:
				// 0x1016BB40
				ReactionHitGrabTrack();
				virtual ~ReactionHitGrabTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCBC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetObject(int newValue);
				bool SetReverseAttachment(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name parentJoint;  // +0x20
					math::Vector childPositionOffset;  // +0x28
					math::Vector childRotationOffset;  // +0x34
					math::Vector parentPositionOffset;  // +0x40
					math::Vector parentRotationOffset;  // +0x4C
					float blendTime;  // +0x58
					float timeBegin;  // +0x5C
					int object;  // +0x60
					bool reverseAttachment;  // +0x64
					unsigned char unknown65[0x3];
			};

			extern fight::Property** gReactionHitGrabTrackProperties;
			fight::TrackFactory* CreateReactionHitGrabTrackFactory(const char* name);
			void RegisterReactionHitGrabTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetGrabIntersectionPropertiesTrack (16 vftable slots, 0x28 bytes)
			class SetGrabIntersectionPropertiesTrack : public fight::Track
			{
			public:
				// 0x1016BC20
				SetGrabIntersectionPropertiesTrack();
				virtual ~SetGrabIntersectionPropertiesTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCC00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIntersectionProperties(const fight::Name& newValue);
				bool SetTemporary(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name intersectionProperties;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					bool temporary;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gSetGrabIntersectionPropertiesTrackProperties;
			fight::TrackFactory* CreateSetGrabIntersectionPropertiesTrackFactory(const char* name);
			void RegisterSetGrabIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedPlaybackTrack (16 vftable slots, 0x30 bytes)
			class GrabbedPlaybackTrack : public fight::Track
			{
			public:
				// 0x1016BCA0
				GrabbedPlaybackTrack();
				virtual ~GrabbedPlaybackTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCB20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetState(const fight::Name& newValue);
				bool SetSpecificPlaybackSet(const fight::Name& newValue);
				bool SetNotifyOnPlaybackFinished(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					fight::Name specificPlaybackSet;  // +0x18
					fight::Name state;  // +0x20
					float timeBegin;  // +0x28
					bool notifyOnPlaybackFinished;  // +0x2C
					unsigned char unknown2D[0x3];
			};

			extern fight::Property** gGrabbedPlaybackTrackProperties;
			fight::TrackFactory* CreateGrabbedPlaybackTrackFactory(const char* name);
			void RegisterGrabbedPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AllowGrabbingTrack (16 vftable slots, 0x20 bytes)
			class AllowGrabbingTrack : public fight::Track
			{
			public:
				// 0x1016AC10
				AllowGrabbingTrack();
				virtual ~AllowGrabbingTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCAD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOnBegin(int newValue);
				bool SetOnEnd(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int onBegin;  // +0x18
					int onEnd;  // +0x1C
			};

			extern fight::Property** gAllowGrabbingTrackProperties;
			fight::TrackFactory* CreateAllowGrabbingTrackFactory(const char* name);
			void RegisterAllowGrabbingTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DelayCollisionWithGrabbedTrack (16 vftable slots, 0x18 bytes)
			class DelayCollisionWithGrabbedTrack : public fight::Track
			{
			public:
				// 0x1016ACC0
				DelayCollisionWithGrabbedTrack();
				virtual ~DelayCollisionWithGrabbedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCA80, another unit)
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

			extern fight::Property** gDelayCollisionWithGrabbedTrackProperties;
			fight::TrackFactory* CreateDelayCollisionWithGrabbedTrackFactory(const char* name);
			void RegisterDelayCollisionWithGrabbedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabObjectFromParentGrabSlotTrack (16 vftable slots, 0x28 bytes)
			class GrabObjectFromParentGrabSlotTrack : public fight::Track
			{
			public:
				// 0x1016BD80
				GrabObjectFromParentGrabSlotTrack();
				virtual ~GrabObjectFromParentGrabSlotTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC9E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetParentSlot(const fight::Name& newValue);
				bool SetChildSlot(const fight::Name& newValue);
				bool SetInterruptPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childSlot;  // +0x10
					fight::Name parentSlot;  // +0x18
					float timeBegin;  // +0x20
					int interruptPriority;  // +0x24
			};

			extern fight::Property** gGrabObjectFromParentGrabSlotTrackProperties;
			fight::TrackFactory* CreateGrabObjectFromParentGrabSlotTrackFactory(const char* name);
			void RegisterGrabObjectFromParentGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotExecuteUsingChildTrack (16 vftable slots, 0x48 bytes)
			class GrabSlotExecuteUsingChildTrack : public fight::Track
			{
			public:
				// 0x1016BE00
				GrabSlotExecuteUsingChildTrack();
				virtual ~GrabSlotExecuteUsingChildTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC990, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				fight::BranchHolder* SetBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name grabSlot;  // +0x38
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
			};

			extern fight::Property** gGrabSlotExecuteUsingChildTrackProperties;
			fight::TrackFactory* CreateGrabSlotExecuteUsingChildTrackFactory(const char* name);
			void RegisterGrabSlotExecuteUsingChildTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedUpdateAttachmentTrack (16 vftable slots, 0x60 bytes)
			class GrabbedUpdateAttachmentTrack : public fight::Track
			{
			public:
				// 0x1016BE90
				GrabbedUpdateAttachmentTrack();
				virtual ~GrabbedUpdateAttachmentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC210, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetUpdateRotationOffset(bool newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);
				bool SetPhysicsMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name parentJoint;  // +0x18
					math::Vector childPositionOffset;  // +0x20
					math::Vector childRotationOffset;  // +0x2C
					math::Vector parentPositionOffset;  // +0x38
					math::Vector parentRotationOffset;  // +0x44
					float blendTime;  // +0x50
					float timeBegin;  // +0x54
					int physicsMode;  // +0x58
					bool updateRotationOffset;  // +0x5C
					unsigned char unknown5D[0x3];
			};

			extern fight::Property** gGrabbedUpdateAttachmentTrackProperties;
			fight::TrackFactory* CreateGrabbedUpdateAttachmentTrackFactory(const char* name);
			void RegisterGrabbedUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabGrabTargetTrack (16 vftable slots, 0xB0 bytes)
			class GrabGrabTargetTrack : public fight::Track
			{
			public:
				// 0x1016BF60
				GrabGrabTargetTrack();
				virtual ~GrabGrabTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC2B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);
				fight::BranchHolder* SetGiverBranch();
				fight::BranchHolder* SetReceiverBranch();
				bool SetInterruptPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder giverBranch;  // +0x10
					fight::BranchHolder receiverBranch;  // +0x34
					fight::Name childJoint;  // +0x58
					fight::Name grabSlot;  // +0x60
					fight::Name parentJoint;  // +0x68
					math::Vector childPositionOffset;  // +0x70
					math::Vector childRotationOffset;  // +0x7C
					math::Vector parentPositionOffset;  // +0x88
					math::Vector parentRotationOffset;  // +0x94
					float blendTime;  // +0xA0
					float timeBegin;  // +0xA4
					float timeEnd;  // +0xA8
					int interruptPriority;  // +0xAC
			};

			extern fight::Property** gGrabGrabTargetTrackProperties;
			fight::TrackFactory* CreateGrabGrabTargetTrackFactory(const char* name);
			void RegisterGrabGrabTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotUpdateAttachmentTrack (16 vftable slots, 0x88 bytes)
			class GrabSlotUpdateAttachmentTrack : public fight::Track
			{
			public:
				// 0x1016C0B0
				GrabSlotUpdateAttachmentTrack();
				virtual ~GrabSlotUpdateAttachmentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC170, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetOverrideParentTranslationJoint(bool newValue);
				bool SetParentTranslationJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetOverrideChildTranslationJoint(bool newValue);
				bool SetChildTranslationJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetConsiderChildAlternateRotation(bool newValue);
				bool SetChildAlternateRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);
				bool SetPhysicsMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name childTranslationJoint;  // +0x18
					fight::Name grabSlot;  // +0x20
					fight::Name parentJoint;  // +0x28
					fight::Name parentTranslationJoint;  // +0x30
					math::Vector childAlternateRotationOffset;  // +0x38
					math::Vector childPositionOffset;  // +0x44
					math::Vector childRotationOffset;  // +0x50
					math::Vector parentPositionOffset;  // +0x5C
					math::Vector parentRotationOffset;  // +0x68
					float blendTime;  // +0x74
					float timeBegin;  // +0x78
					int physicsMode;  // +0x7C
					bool considerChildAlternateRotation;  // +0x80
					bool overrideChildTranslationJoint;  // +0x81
					bool overrideParentTranslationJoint;  // +0x82
					unsigned char unknown83[0x5];
			};

			extern fight::Property** gGrabSlotUpdateAttachmentTrackProperties;
			fight::TrackFactory* CreateGrabSlotUpdateAttachmentTrackFactory(const char* name);
			void RegisterGrabSlotUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabPlayerTrack (16 vftable slots, 0x78 bytes)
			class GrabPlayerTrack : public fight::Track
			{
			public:
				// 0x1016C1C0
				GrabPlayerTrack();
				virtual ~GrabPlayerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC260, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetUseLocalSpace(bool newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabbingPlayer(int newValue);
				bool SetGrabbedPlayer(int newValue);
				bool SetActionOnEnd(int newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetParentJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetParentRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name parentJoint;  // +0x20
					math::Vector childPositionOffset;  // +0x28
					math::Vector childRotationOffset;  // +0x34
					math::Vector parentPositionOffset;  // +0x40
					math::Vector parentRotationOffset;  // +0x4C
					float blendTime;  // +0x58
					float timeBegin;  // +0x5C
					float timeEnd;  // +0x60
					int actionOnEnd;  // +0x64
					int grabbedPlayer;  // +0x68
					int grabbingPlayer;  // +0x6C
					bool useLocalSpace;  // +0x70
					unsigned char unknown71[0x7];
			};

			extern fight::Property** gGrabPlayerTrackProperties;
			fight::TrackFactory* CreateGrabPlayerTrackFactory(const char* name);
			void RegisterGrabPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedExecuteOnParentTrack (16 vftable slots, 0x3C bytes)
			class GrabbedExecuteOnParentTrack : public fight::Track
			{
			public:
				// 0x1016AE80
				GrabbedExecuteOnParentTrack();
				virtual ~GrabbedExecuteOnParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CC8F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				fight::BranchHolder* SetReceiverBranch();
				bool SetInterruptPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder receiverBranch;  // +0x10
					float timeBegin;  // +0x34
					int interruptPriority;  // +0x38
			};

			extern fight::Property** gGrabbedExecuteOnParentTrackProperties;
			fight::TrackFactory* CreateGrabbedExecuteOnParentTrackFactory(const char* name);
			void RegisterGrabbedExecuteOnParentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotEnableStuckTestTrack (16 vftable slots, 0x20 bytes)
			class GrabSlotEnableStuckTestTrack : public fight::Track
			{
			public:
				// 0x1016C2E0
				GrabSlotEnableStuckTestTrack();
				virtual ~GrabSlotEnableStuckTestTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CCC50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabSlotEnableStuckTestTrackProperties;
			fight::TrackFactory* CreateGrabSlotEnableStuckTestTrackFactory(const char* name);
			void RegisterGrabSlotEnableStuckTestTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
