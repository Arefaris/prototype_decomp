// The objects the Director registers as controllers: by the RTTI the namespace has an engine::camera::Cinematographer,
// and this class fits what the Director does with them (slot 0x3c, id 0x40, a type from a virtual, an owner at 0x10,
// an enable byte at 0x2c, Update and Reset virtuals). The vftable slot names other than Update / GetType / Reset and
// all member names are guesses.
#ifndef ENGINE_CAMERA_CINEMATOGRAPHER_H
#define ENGINE_CAMERA_CINEMATOGRAPHER_H

#include "code/core/name.h"

namespace engine
{
	namespace camera
	{
		class Cinematographer
		{
		public:
			virtual ~Cinematographer()
			{
			}
			virtual void Slot1() = 0;
			virtual void Slot2() = 0;
			// vftable slot 3
			virtual void Update(float delta, float time, int flags) = 0;
			virtual void Slot4() = 0;
			// vftable slot 5
			virtual int GetType() = 0;
			virtual void Slot6() = 0;
			// vftable slot 7, called by the Director for every controller of an owner
			virtual void OnEvent(int param) = 0;
			virtual void Slot8() = 0;
			// vftable slot 9, called by the Director for controllers of a kind unless bit 1 of flags is set
			virtual void OnKindEvent(float param) = 0;
			// vftable slot 10
			virtual void Reset() = 0;

			int unknown4;
			core::Name<core::CaseSensitiveKey> name;
			// Compared with a player index by the Director
			int owner;
			int unknown14;
			int unknown18;
			int kind;
			int unknown20;
			unsigned int flags;
			int unknown28;
			bool enabled;
			int unknown30[3];
			// Index in the Director's controller table and the serial number given when registered
			int slot;
			int id;

			core::Name<core::CaseSensitiveKey> GetName() const
			{
				return name;
			}
			// Bit 1 of flags clear
			bool IsRunning() const
			{
				return !((flags >> 1) & 1);
			}
			void SetSlot(int value);
			void SetId(int value);
			int GetId() const;
		};
	}
}

#endif
