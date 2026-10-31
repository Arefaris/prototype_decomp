// Fight items of the motion group: ConsumeGrabberTrack, ConsumeByParentTrack, NISConsumeByParentTrack, ScaleJointForConsumeTrack, ConsumeMeTrack, ConsumeTrack (unit 0x1014D220 - 0x1014F4D0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CONSUME_H
#define PROTO_FIGHTITEMS_MOTION_CONSUME_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ConsumeGrabberTrack (16 vftable slots, 0x18 bytes)
			class ConsumeGrabberTrack : public fight::Track
			{
			public:
				// 0x1014D450
				ConsumeGrabberTrack();
				virtual ~ConsumeGrabberTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AD390, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetStealthy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool stealthy;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gConsumeGrabberTrackProperties;
			fight::TrackFactory* CreateConsumeGrabberTrackFactory(const char* name);
			void RegisterConsumeGrabberTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ConsumeByParentTrack (16 vftable slots, 0x50 bytes)
			class ConsumeByParentTrack : public fight::Track
			{
			public:
				// 0x1014D710
				ConsumeByParentTrack();
				virtual ~ConsumeByParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AD430, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRagdollIfNeeded(const fight::Name& newValue);
				bool SetSwitchToRagdollMode(bool newValue);
				bool SetParentObjectName(const fight::Name& newValue);
				bool SetParentDestinationJoint(const fight::Name& newValue);
				bool SetParentPositionOffset(const math::Vector& newValue);
				bool SetConsumeUpwards(bool newValue);
				bool SetBoneSweepConstant(float newValue);
				bool SetTransformationConsume(bool newValue);
				bool SetTransformationConsumeTime(float newValue);
				bool SetStealthy(bool newValue);
				bool SetConsumableProperties(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name consumableProperties;  // +0x10
					fight::Name parentDestinationJoint;  // +0x18
					fight::Name parentObjectName;  // +0x20
					fight::Name ragdollIfNeeded;  // +0x28
					math::Vector parentPositionOffset;  // +0x30
					float boneSweepConstant;  // +0x3C
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					float transformationConsumeTime;  // +0x48
					bool consumeUpwards;  // +0x4C
					bool stealthy;  // +0x4D
					bool switchToRagdollMode;  // +0x4E
					bool transformationConsume;  // +0x4F
			};

			extern fight::Property** gConsumeByParentTrackProperties;
			fight::TrackFactory* CreateConsumeByParentTrackFactory(const char* name);
			void RegisterConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::NISConsumeByParentTrack (16 vftable slots, 0x60 bytes)
			class NISConsumeByParentTrack : public ConsumeByParentTrack
			{
			public:
				// 0x1014D7E0
				NISConsumeByParentTrack();
				virtual ~NISConsumeByParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 15 (0x100AD3E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetObject(const fight::Name& newValue);
				bool SetToBeContinued(bool newValue);
				// TODO SetTimeBegin
				// TODO SetTimeEnd
				// TODO SetRagdollIfNeeded
				// TODO SetSwitchToRagdollMode
				// TODO SetParentObjectName
				// TODO SetParentDestinationJoint
				// TODO SetParentPositionOffset
				// TODO SetConsumeUpwards
				// TODO SetBoneSweepConstant
				// TODO SetTransformationConsume
				// TODO SetTransformationConsumeTime
				// TODO SetStealthy
				// TODO SetConsumableProperties

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name object;  // +0x50
					bool toBeContinued;  // +0x58
					unsigned char unknown59[0x7];
			};

			extern fight::Property** gNISConsumeByParentTrackProperties;
			fight::TrackFactory* CreateNISConsumeByParentTrackFactory(const char* name);
			void RegisterNISConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ScaleJointForConsumeTrack (16 vftable slots, 0x28 bytes)
			class ScaleJointForConsumeTrack : public fight::Track
			{
			public:
				// 0x1014D820
				ScaleJointForConsumeTrack();
				virtual ~ScaleJointForConsumeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AD480, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJointToScale(const fight::Name& newValue);
				bool SetDesiredScale(float newValue);
				bool SetScaleRate(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name jointToScale;  // +0x10
					float desiredScale;  // +0x18
					float scaleRate;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
			};

			extern fight::Property** gScaleJointForConsumeTrackProperties;
			fight::TrackFactory* CreateScaleJointForConsumeTrackFactory(const char* name);
			void RegisterScaleJointForConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ConsumeMeTrack (16 vftable slots, 0x18 bytes)
			class ConsumeMeTrack : public fight::Track
			{
			public:
				// 0x1014D570
				ConsumeMeTrack();
				virtual ~ConsumeMeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AD340, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetStealthy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool stealthy;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gConsumeMeTrackProperties;
			fight::TrackFactory* CreateConsumeMeTrackFactory(const char* name);
			void RegisterConsumeMeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ConsumeTrack (16 vftable slots, 0x20 bytes)
			class ConsumeTrack : public fight::Track
			{
			public:
				// 0x1014D8F0
				ConsumeTrack();
				virtual ~ConsumeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AD2F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetStealthy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					bool stealthy;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gConsumeTrackProperties;
			fight::TrackFactory* CreateConsumeTrackFactory(const char* name);
			void RegisterConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::ConsumeGrabberAction (9 vftable slots, 0x2C bytes)
			class ConsumeGrabberAction : public fight::Action
			{
			public:
				// 0x100AC7D0
				ConsumeGrabberAction(ConsumeGrabberTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100ABB00
				virtual ~ConsumeGrabberAction();

				// vftable slot 5 (0x100AC870)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ConsumeGrabberTrack> link;  // +0x20
			};

			// RTTI: proto::fightitems::motion::ConsumeMeAction (9 vftable slots, 0x2C bytes)
			class ConsumeMeAction : public fight::Action
			{
			public:
				// 0x100AC610
				ConsumeMeAction(ConsumeMeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100ABAB0
				virtual ~ConsumeMeAction();

				// vftable slot 5 (0x100AC6B0)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ConsumeMeTrack> link;  // +0x20
			};

			// RTTI: proto::fightitems::motion::ConsumeByParentAction (9 vftable slots, 0x2C bytes)
			class ConsumeByParentAction : public fight::Action
			{
			public:
				// 0x100AC920
				ConsumeByParentAction(ConsumeByParentTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100ABB50
				virtual ~ConsumeByParentAction();

				// vftable slot 5 (0x100ACA90)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100ACF60)
				virtual void Slot6();
				// vftable slot 7 (0x100ACE20)
				virtual bool Slot7(int arg, float value);

				core::Link<ConsumeByParentTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				engine::HandleBase unknown2C;  // +0x2C
				engine::HandleBase unknown30;  // +0x30
				float unknown34;  // +0x34
				bool unknown38;  // +0x38
				unsigned char unknown39[0x3];
			};

			// RTTI: proto::fightitems::motion::ScaleJointForConsumeAction (9 vftable slots, 0x2C bytes)
			class ScaleJointForConsumeAction : public fight::Action
			{
			public:
				// 0x100AD090
				ScaleJointForConsumeAction(ScaleJointForConsumeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100ABBA0
				virtual ~ScaleJointForConsumeAction();

				// vftable slot 5 (0x100AD140)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100AD240)
				virtual void Slot6();

				core::Link<ScaleJointForConsumeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0x4];
			};

			// RTTI: proto::fightitems::motion::ConsumeAction (9 vftable slots, 0x2C bytes)
			class ConsumeAction : public fight::Action
			{
			public:
				// 0x100ABE20
				ConsumeAction(ConsumeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100ABA60
				virtual ~ConsumeAction();

				// vftable slot 5 (0x100AC540)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ConsumeTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
