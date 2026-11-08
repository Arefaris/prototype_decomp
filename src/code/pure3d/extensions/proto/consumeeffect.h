// pure3d::extensions::proto::ConsumeEffect and ConsumeEffect2 (RTTI names; vftables 0x10E5C06C and 0x10E5C0D4, 25 slots,
// bases SimpleFrameController, AnimationFrameController, FrameController): the controllers a drawable that is being
// consumed carries (the shader parameters "isConsumeActive", "consume_colour", "consume_normal" and "consume_refl" belong
// to them). Only the slots that are not tied to their members are here so far; the class is not laid out yet.
#ifndef PURE3D_EXTENSIONS_PROTO_CONSUMEEFFECT_H
#define PURE3D_EXTENSIONS_PROTO_CONSUMEEFFECT_H

#include "code/pure3d/framecontroller.h"

namespace pure3d
{
	namespace extensions
	{
		namespace proto
		{
			class ConsumeEffect : public SimpleFrameController
			{
			public:
				// RTTI: pure3d::extensions::proto::ConsumeEffect::SharedData (a struct; base RefCounted, vftable 0x10E5C054, 0x14
				// bytes): the buffer the effect's copies share
				struct SharedData : public RefCounted
				{
					// 0x10724AF0; the destructor (implicit) is 0x10724B10 and the scalar deleting destructor 0x107251A0
					SharedData();

					// A growing array of bytes: begin, end and the end of the storage
					struct ByteArray
					{
						ByteArray() : mBegin(0), mEnd(0), mCapacity(0)
						{
						}
						~ByteArray()
						{
							mEnd = mBegin;
							if (mBegin != 0)
							{
								delete[] mBegin;
							}
						}
						char* mBegin;
						char* mEnd;
						char* mCapacity;
					} mBytes;
				};

				// Slot 3 (0x10725180): nothing; slot 4 (0x10724CD0, not reconstructed); slot 5 (0x10725190): nothing;
				// slot 24 (0x10721490): no animation is supported
				virtual void SetTarget(Entity* target);
				virtual void Advance(float dt, bool update);
				virtual void Unknown5();
				virtual bool IsSupported(Animation* animation);
			};

			class ConsumeEffect2 : public SimpleFrameController
			{
			public:
				// Slot 3 (0x10726270), slot 4 (0x10724E90, not reconstructed), slot 5 (0x10726280) and slot 24 (0x10721360),
				// as those of ConsumeEffect
				virtual void SetTarget(Entity* target);
				virtual void Advance(float dt, bool update);
				virtual void Unknown5();
				virtual bool IsSupported(Animation* animation);
			};
		}
	}
}

#endif
