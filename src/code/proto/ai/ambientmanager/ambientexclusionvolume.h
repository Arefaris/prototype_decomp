// proto::AmbientExclusionVolume (RTTI and reflection names; a reflected load object): a box in the world that keeps
// ambient pedestrians and / or traffic vehicles out. Reflected: transform, extents, excludePedestrians,
// excludeTrafficVehicles, decayState. Unit 0x10409900 - 0x10409940, with its members spread over the ambient manager's
// range (no assert path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTEXCLUSIONVOLUME_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTEXCLUSIONVOLUME_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/proto/ai/ambientmanager/ambientenums.h"
#include "code/proto/citymanager.h"
#include "code/ravenphysics/context.h"

namespace proto
{
	class AmbientExclusionVolume : public content::MetaLoadObject
	{
	public:
		// The kinds of ambient object the volume excludes, one bit each (the bit of an AmbientExcludeType)
		struct ExcludeFlags
		{
			// 0x1040BBE0
			ExcludeFlags();
			// 0x1040BC00
			void Clear();
			// 0x1040BC20
			bool Test(unsigned char bit) const;
			// 0x1040BC40
			void ClearBit(unsigned char bit);
			// 0x1040C220
			void SetBit(unsigned char bit);
			// 0x10411740: sets or clears the bit
			void Assign(unsigned char bit, bool value);

			unsigned char bits;
		};

		// 0x1040C8B0
		AmbientExclusionVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x1041C820): makes the physics object of the volume
		virtual void Slot3(int unused);
		// vftable slot 4 (0x1041C9E0): takes it out of the world again
		virtual bool IsReady();

		// 0x1040BCE0 / 0x10415680, 0x1040BCF0 / 0x10415720: the reflected flags
		bool GetExcludePedestrians() const;
		void SetExcludePedestrians(bool exclude);
		bool GetExcludeTrafficVehicles() const;
		void SetExcludeTrafficVehicles(bool exclude);

		math::Matrix transform;  // +8
		math::Vector extents;  // +0x48
		ExcludeFlags flags;  // +0x54
		int decayState;  // +0x58
		ravenphysics::ObjectHandle physicsObject;  // +0x5C
	};
}

namespace content
{
	// 0x104F05D0 (another unit): the values of the decay state
	template<> void EnumInfo<proto::CityManager::DecayState>::Get(const char** name, const EnumValue** values, int* count,
		const char** code);
}

#endif
