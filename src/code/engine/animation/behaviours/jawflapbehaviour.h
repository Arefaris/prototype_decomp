// engine::animation::JawFlapBehaviour (RTTI and reflection names; base engine::Behaviour): opens and closes the jaw of
// a character while it talks. The value a message carries (the loudness of the voice) is mapped from the reflected
// thresholds to an angle, which turns the "Jaw" joint around the reflected axis through a joint driver of the object's
// puppet. Unit 0x10919F50 - 0x1091B180 (no assert path; the directory and file names are guesses). The reflected
// member names are original; the rest is guessed.
#ifndef ENGINE_ANIMATION_BEHAVIOURS_JAWFLAPBEHAVIOUR_H
#define ENGINE_ANIMATION_BEHAVIOURS_JAWFLAPBEHAVIOUR_H

#include "code/choreo/drivers.h"
#include "code/choreo/puppet.h"
#include "code/content/metatype.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace engine
{
	namespace animation
	{
		// The message (type 0x15, id 2) that carries how loud the character speaks
		struct VoiceMessage : public Message
		{
			int unknownC;
			int unknown10;
			int unknown14;
			float loudness;  // +0x18
		};

		class JawFlapBehaviour : public Behaviour
		{
		public:
			// 0x1091A290
			explicit JawFlapBehaviour(GameObject* newOwner);
			// 0x1091A380 (deleting destructor 0x1091A5E0)
			virtual ~JawFlapBehaviour();

			// vftable slot 1 (0x1091B0A0): while the behaviour is active, finds the puppet and makes the driver
			virtual void Slot1();
			// vftable slot 3 (0x1091B0C0)
			virtual void OnActiveChanged(bool active);
			// vftable slot 4 (0x1091A720): turns the jaw
			virtual void Update(float dt, unsigned short mask);
			// vftable slot 5 (0x10919F90)
			virtual void OnPostedMessage(Message* message);
			// vftable slot 6 (0x1091AAC0): the drawable and puppet attributes and the voice message
			virtual void OnMessage(Message* message);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The reflected accessors (0x10919FA0 - 0x1091A090)
			float GetThresholdMin() const;
			void SetThresholdMin(float value);
			float GetThresholdMax() const;
			void SetThresholdMax(float value);
			float GetAngleMin() const;
			void SetAngleMin(float value);
			float GetAngleMax() const;
			void SetAngleMax(float value);
			int GetPriority() const;
			void SetPriority(int value);
			float GetBlendInTime() const;
			void SetBlendInTime(float value);
			float GetBlendOutTime() const;
			void SetBlendOutTime(float value);
			const math::Vector* GetAxis() const;
			void SetAxis(const math::Vector* value);

			// 0x1091A3D0: takes the puppet of the owner
			void FindPuppet();
			// 0x1091A410: lets go of the puppet, the parts and the driver
			void ReleaseAll();
			// 0x1091B090: finds the jaw and the puppet
			void Setup();
			// 0x1091A600: finds the jaw joint of the owner's drawable and makes the joint driver
			void FindJaw();

			core::RefPtr<choreo::Driver> driver;  // +0xC
			core::RefPtr<choreo::Puppet> puppet;  // +0x10
			core::RefPtr<core::IRefCount> parts;  // +0x14
			float loudness;  // +0x18
			unsigned int jaw;  // +0x1C
			float thresholdMin;  // +0x20
			float thresholdMax;  // +0x24
			float angleMin;  // +0x28
			float angleMax;  // +0x2C
			int priority;  // +0x30
			float blendInTime;  // +0x34
			float blendOutTime;  // +0x38
			math::Vector axis;  // +0x3C
		};
	}
}

#endif
