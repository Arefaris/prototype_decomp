// The update of the particle system states and the generators' attribute values (unit around 0x1079C000 - 0x107A0600,
// the code that the generators' Update functions share; the file name is a guess). Names are guesses.
#include "code/math/aabb.h"
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/pure3d/effects/particles.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1079CE80
	void ParticleAttributes::Apply(ParticleUpdateData* data)
	{
		if (apply)
		{
			values.MultiplyAdd(values, scale, offset);
		}
	}

	// FUNCTION: ENGINE 0x1079F320
	// EQUIVALENT: the same operations in the same order (525 bytes against 577); the engine keeps the box's minimum x in a
	// register through the loop and loads the particle count once
	void ParticleSystemState::UpdateBounds(ParticleUpdateData* data)
	{
		math::Vector* positions = (math::Vector*)(attributes2C0->entries[0].offset + block);
		float* radii = (float*)(attributes2D0->entries[4].offset + block);
		math::AABB box;
		box.Reset();
		bool visible = inheritUnknown4BC ? parent->GetUnknown3F4() : unknown3F4;
		if (visible)
		{
			for (unsigned int i = 0; i < particleCount; i++)
			{
				float radius = radii[i];
				if (!(math::EPSILON_SMALL > radius) && ((float*)(attributes2D0->entries[1].offset + block))[i] != 1e12f)
				{
					float x = positions[i].x;
					float y = positions[i].y;
					float z = positions[i].z;
					float minX = x - radius;
					float minY = y - radius;
					float minZ = z - radius;
					float maxX = x + radius;
					float maxY = y + radius;
					float maxZ = z + radius;
					if (!(minX > box.min.x))
					{
						box.min.x = minX;
					}
					if (!(minY > box.min.y))
					{
						box.min.y = minY;
					}
					if (!(minZ > box.min.z))
					{
						box.min.z = minZ;
					}
					if (maxX > box.max.x)
					{
						box.max.x = maxX;
					}
					if (maxY > box.max.y)
					{
						box.max.y = maxY;
					}
					if (maxZ > box.max.z)
					{
						box.max.z = maxZ;
					}
				}
			}
			if (!box.IsEmpty())
			{
				math::Matrix inverse;
				inverse = transform;
				inverse.Invert();
				box.SetTransformed(inverse, box);
			}
		}
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x1079F570
	// EQUIVALENT: the same calls with the same arguments in the same order; the engine computes the arguments of the
	// kernels into stack slots before the first test, and the compiler orders them differently
	// The pointers below are named by the table of the state that holds the attribute's offset (t: attributes2D0,
	// u: attributes2C0, v: attributes2D8, s1 / s2 / s3: the shared details' tables at +0x1F0 / +0x1E0 / +0x1F8) and the
	// index of the entry (the offset in the table divided by 8)
	void ParticleSystemState::UpdateParticles(ParticleUpdateData* data)
	{
		SharedDetails* details = shared;
		if (unknown3F0 && unknown3F0->channel)
		{
			unknown3F0->channel->GetValue(data->time, &unknown3F4);
		}
		if (override418 == -1.0f && unknown400)
		{
			if (unknown400->channel)
			{
				unknown400->channel->GetValue(data->time, &unknown2E4);
				unknown2E4 = bias410 * unknown2E4;
			}
		}
		else if (override418 != -1.0f)
		{
			unknown2E4 = override418;
		}
		if (override414 == -1.0f && unknown404)
		{
			if (unknown404->channel)
			{
				unknown404->channel->GetValue(data->time, &unknown2E0);
				unknown2E0 = bias40C * unknown2E0;
			}
		}
		else if (override414 != -1.0f)
		{
			unknown2E0 = override414;
		}
		if (unknown408 && unknown408->channel)
		{
			unknown408->channel->mKeys.Evaluate(FrameTime(data->time), &unknown308);
		}
		unknown314 = data->position;
		unknown320.Set(generator->transform.m[3][0], generator->transform.m[3][1], generator->transform.m[3][2]);
		unknown36C = generator->transform;
		generator->Update(data);
		generator->GetUnknown10740E50(&unknown32C);
		generator->Unknown107404B0(1.0f);
		generator->Generate(data, unknownE4);
		unsigned int count = CountParticles();
		unknown4BC = count != 0;
		if (unknown4BC)
		{
			unsigned char* t0 = block + attributes2D0->entries[0].offset;
			unsigned char* t1 = block + attributes2D0->entries[1].offset;
			unsigned char* t2 = block + attributes2D0->entries[2].offset;
			unsigned char* t3 = block + attributes2D0->entries[3].offset;
			unsigned char* t4 = block + attributes2D0->entries[4].offset;
			unsigned char* t5 = block + attributes2D0->entries[5].offset;
			unsigned char* t6 = block + attributes2D0->entries[6].offset;
			unsigned char* t7 = block + attributes2D0->entries[7].offset;
			unsigned char* t9 = block + attributes2D0->entries[9].offset;
			unsigned char* t10 = block + attributes2D0->entries[10].offset;
			unsigned char* t11 = block + attributes2D0->entries[11].offset;
			unsigned char* t13 = block + attributes2D0->entries[13].offset;
			unsigned char* t16 = block + attributes2D0->entries[16].offset;
			unsigned char* t17 = block + attributes2D0->entries[17].offset;
			unsigned char* t19 = block + attributes2D0->entries[19].offset;
			unsigned char* t20 = block + attributes2D0->entries[20].offset;
			unsigned char* t21 = block + attributes2D0->entries[21].offset;
			unsigned char* t22 = block + attributes2D0->entries[22].offset;
			unsigned char* t23 = block + attributes2D0->entries[23].offset;
			unsigned char* t24 = block + attributes2D0->entries[24].offset;
			unsigned char* t25 = block + attributes2D0->entries[25].offset;
			unsigned char* u0 = block + attributes2C0->entries[0].offset;
			unsigned char* u1 = block + attributes2C0->entries[1].offset;
			unsigned char* u2 = block + attributes2C0->entries[2].offset;
			unsigned char* u3 = block + attributes2C0->entries[3].offset;
			unsigned char* u4 = block + attributes2C0->entries[4].offset;
			unsigned char* u6 = block + attributes2C0->entries[6].offset;
			unsigned char* u7 = block + attributes2C0->entries[7].offset;
			unsigned char* u8 = block + attributes2C0->entries[8].offset;
			unsigned char* u9 = block + attributes2C0->entries[9].offset;
			unsigned char* u11 = block + attributes2C0->entries[11].offset;
			unsigned char* u12 = block + attributes2C0->entries[12].offset;
			unsigned char* v0 = block + attributes2D8->entries[0].offset;
			unsigned char* v1 = block + attributes2D8->entries[1].offset;
			unsigned char* v2 = block + attributes2D8->entries[2].offset;
			unsigned char* sharedBlock = details->block;
			unsigned char* s1_2 = sharedBlock + details->attributes1F0->entries[2].offset;
			unsigned char* s1_4 = sharedBlock + details->attributes1F0->entries[4].offset;
			unsigned char* s1_6 = sharedBlock + details->attributes1F0->entries[6].offset;
			unsigned char* s1_7 = sharedBlock + details->attributes1F0->entries[7].offset;
			unsigned char* s1_8 = sharedBlock + details->attributes1F0->entries[8].offset;
			unsigned char* s1_13 = sharedBlock + details->attributes1F0->entries[13].offset;
			unsigned char* s1_16 = sharedBlock + details->attributes1F0->entries[16].offset;
			unsigned char* s1_18 = sharedBlock + details->attributes1F0->entries[18].offset;
			unsigned char* s1_21 = sharedBlock + details->attributes1F0->entries[21].offset;
			unsigned char* s1_22 = sharedBlock + details->attributes1F0->entries[22].offset;
			unsigned char* s1_23 = sharedBlock + details->attributes1F0->entries[23].offset;
			unsigned char* s2_4 = sharedBlock + details->attributes1E0->entries[4].offset;
			unsigned char* s2_8 = sharedBlock + details->attributes1E0->entries[8].offset;
			unsigned char* s3_0 = sharedBlock + details->attributes1F8->entries[0].offset;
			float dt = data->deltaTime;
			if (updateKernels & 0x1)
			{
				UpdateKernel00(dt, count, unknown4B4, t5, t6);
			}
			if (updateKernels & 0x2)
			{
				UpdateKernel01(dt, count, unknown4B4, t0, t1, t5, t6, s1_6);
			}
			if (updateKernels & 0x4)
			{
				UpdateKernel02(dt, count, unknown4B4, u3, u4);
			}
			if (updateKernels & 0x8)
			{
				UpdateKernel03(dt, count, unknown4B4, t0, t1, u3, u4, s2_4);
			}
			if (updateKernels & 0x10)
			{
				UpdateKernel04(dt, count, unknown4B4, u11, u4, u1);
			}
			if (updateKernels & 0x20)
			{
				UpdateKernel05(dt, count, unknown4B4, u9, t0, &unknown2F0, t9, t10);
			}
			if (updateKernels & 0x40)
			{
				UpdateKernel06(dt, count, unknown4B4, u9, t0, t1, &unknown2E8, &unknown2EC, s1_8);
			}
			if (updateKernels & 0x80)
			{
				UpdateFrameBlend(dt, count, unknown4B4, (ParticleFrameBlend*)u9, (const float*)t9, t10, (float*)t11,
					&unknown2F0);
			}
			if (updateKernels & 0x100)
			{
				UpdateKernel08(dt, count, unknown4B4, t0, t1, v0, v1, biasColours, s3_0);
			}
			if (updateKernels & 0x200)
			{
				UpdateKernel09(dt, count, unknown4B4, t0, t1, v0, v1, biasColours, s3_0);
			}
			if (updateKernels & 0x400)
			{
				UpdateKernel10(dt, count, unknown4B4, t0, t1, v0, v1, biasColours, s3_0);
			}
			if (updateKernels & 0x800)
			{
				UpdateKernel11(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, &unknown2E4, s1_2, s1_7);
			}
			if (updateKernels & 0x1000)
			{
				UpdateKernel12(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, t19, t17, s1_2, s1_7,
					s1_18);
			}
			if (updateKernels & 0x2000)
			{
				UpdateKernel13(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, &unknown2E4, t13, u8, s1_2,
					s1_7, s1_13, s2_8);
			}
			if (updateKernels & 0x4000)
			{
				UpdateKernel14(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, &unknown2E4, t13, u8,
					&unknown32C, s1_2, s1_7, s1_13, s2_8);
			}
			if (updateKernels & 0x8000)
			{
				UpdateKernel15(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, &unknown2E4, t13, u8,
					&unknown32C, s1_2, s1_7, s1_13, s2_8);
			}
			if (updateKernels & 0x10000)
			{
				UpdateKernel16(dt, count, unknown4B4, t0, t1, t7, u0, u2, u1, u7, t2, &unknown2E0, &unknown2E4, t13, u8,
					&unknown32C, s1_2, s1_7, s1_13, s2_8);
			}
			if (updateKernels & 0x20000)
			{
				UpdateKernel17(dt, count, unknown4B4, t0, t1, t3, t4, s1_4);
			}
			if (updateKernels & 0x40000)
			{
				UpdateNothing(dt, count, unknown4B4, u0, t3, t4, v0);
			}
			if (updateKernels & 0x80000)
			{
				UpdateKernel19(dt, count, unknown4B4, u0, u2, t0, t1, t20, t21, t22, t23, t24, &unknown2E4, &unknown2E0, t25,
					&unknown320, s1_22, s1_23, s1_21);
			}
			if (updateKernels & 0x100000)
			{
				UpdateKernel20(dt, count, unknown4B4, u2, t0, t1, &unknown314, &unknown320, t5, t6, s1_6);
			}
			if (updateKernels & 0x200000)
			{
				UpdateKernel21(dt, count, unknown4B4, u0, &unknown32C);
			}
			if (updateKernels & 0x400000)
			{
				UpdateKernel22(dt, count, unknown4B4, t0, t1, u0, t13, u8, &unknown2F4, &unknown36C, s1_13, s2_8);
			}
			if (updateKernels & 0x800000)
			{
				UpdateKernel23(dt, count, unknown4B4, u0, u2, u6);
			}
			if (updateKernels & 0x1000000)
			{
				UpdateKernel24(dt, count, unknown4B4, v0, v2);
			}
			if (updateKernels & 0x2000000)
			{
				UpdateKernel25(dt, count, unknown4B4, v0, v2);
			}
			if (updateKernels & 0x4000000)
			{
				UpdateKernel26(dt, count, unknown4B4, t0, t1, u12, u0, t16, s1_16);
			}
		}
		UpdateBounds(data);
	}
}
