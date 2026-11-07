// proto::BulletTracer (RTTI name; a pure3d primitive that draws a bullet's tracer as two ribbons, a bright head and a
// trail), its per-shot state proto::BulletTracerState and the parameters of a ribbon, proto::BulletTracerParams::Data (a
// reflected type; its fields' names are the engine's own, from the reflection strings). Layouts partial; the names of
// the state's runtime members and of the methods are guesses.
#ifndef PROTO_RENDER_BULLETTRACER_H
#define PROTO_RENDER_BULLETTRACER_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	class Shader;
}

namespace proto
{
	struct BulletTracerParams
	{
		// The parameters of one ribbon (0x58 bytes)
		struct Data
		{
			// 0x102CCC70 / 0x102CE670
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float fadeInTime;
			float fadeOutTime;
			float startFadeDistance;
			float endFadeDistance;
			float generateTime;
			float fadeInTrailTime;
			float fadeOutTrailTime;
			float shrinkInTime;
			float shrinkOutTime;
			float thickness;
			float textureLength;
			float textureScrollRate;
			unsigned char unknown30[8];
			math::Vector4 startColour;
			math::Vector4 endColour;
		};
	};

	// The profile of a tracer (RTTI proto::BulletTracerProfile; reflected: head, tail, wait, offset, headShaderName,
	// tailShaderName): the parameters of the two ribbons and their shaders
	struct BulletTracerProfile
	{
		// 0x102CCCB0 / 0x102CF0F0
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[8];
		BulletTracerParams::Data head;  // +8
		BulletTracerParams::Data tail;  // +0x60
		core::Name<core::CaseSensitiveKey> headShaderName;  // +0xB8
		core::Name<core::CaseSensitiveKey> tailShaderName;  // +0xC0
		float wait;  // +0xC8
		math::Vector offset;  // +0xCC
	};

	// What a tracer is started with (0xE4 bytes, copied by the code that starts it, 0x102CCD90): the parameters of the two
	// ribbons, the delay, the object it follows and where on it the muzzle is (names guessed)
	struct BulletTracerSetup
	{
		BulletTracerParams::Data head;  // +0
		BulletTracerParams::Data tail;  // +0x58
		float wait;  // +0xB0
		int jointIndex;  // +0xB4
		unsigned int owner;  // +0xB8
		float unknownBC;
		float unknownC0;
		float unknownC4;
		float unknownC8;
		float unknownCC;
		float unknownD0;
		float unknownD4;
		float localX;  // +0xD8
		float localY;  // +0xDC
		float localZ;  // +0xE0
	};

	// The state of a tracer in flight: a copy of the profile (the ribbons and the delay), the head's position and
	// direction, and the clocks of the ribbons
	class BulletTracerState : public pure3d::PrimitiveState
	{
	public:
		// 0x102CF450: a tracer of a primitive started with the setup; 0x102CF600: a copy of a tracer
		BulletTracerState(pure3d::Primitive* newPrimitive, const BulletTracerSetup* setup);
		BulletTracerState(const BulletTracerState& other);
		// slot 3 (0x102CF780): a copy; slot 4 (0x102CDAE0): the clocks and the head advance; slot 5 (0x102CCE90): nothing;
		// slot 6 (0x102CDE60): the tracer has run out; slot 7 (0x102CD220): the primitive's box
		virtual pure3d::PrimitiveState* Unknown3();
		virtual void Update(float dt);
		virtual void Unknown5();
		virtual bool Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		// 0x102CDE00: the time from the start to the end of the longer ribbon, after the delay
		float GetDuration();
		// 0x102CE990: the muzzle's place in the world, from the object the tracer follows (name guess)
		void UpdateMuzzle();
		// 0x102CCEB0 / 0x102CCEF0 / 0x102CCF30 / 0x102CCF70: one over the fade out trail / fade in trail / shrink out /
		// shrink in time, zero when it is zero
		float GetInverseFadeOutTrailTime(const BulletTracerParams::Data* data);
		float GetInverseFadeInTrailTime(const BulletTracerParams::Data* data);
		float GetInverseShrinkOutTime(const BulletTracerParams::Data* data);
		float GetInverseShrinkInTime(const BulletTracerParams::Data* data);
		// 0x102CCFB0: the opacity of the trail at a distance along it, from its age and the distance
		float GetTrailFade(const BulletTracerParams::Data* data, float time, float distance);
		// 0x102CD130: the fade of the ribbon's width towards its end, from the position along it
		float GetWidthFade(const BulletTracerParams::Data* data, float position);
		// 0x102CDE90: the opacity of a ribbon: it fades in, holds for the generate time and fades out
		float GetFade(const BulletTracerParams::Data* data);
		// 0x102CDFB0: how far the point a is behind the head, as a fade (1 at the head) scaled by the age
		float GetDistanceFade(const math::Vector* a, const math::Vector* b);

		unsigned char unknown10[0xC];
		unsigned int owner;  // +0x1C
		BulletTracerParams::Data head;
		BulletTracerParams::Data tail;
		float wait;
		math::Vector offset;
		math::Vector position;
		math::Vector direction;
		math::Vector local;  // +0xF8
		int jointIndex;  // +0x104
		float age;
		float headScroll;
		float tailScroll;
		float unknown114;
		float unknown118;
		float unknown11C;
		float unknown120;
		float unknown124;
		float unknown128;
		float unknown12C;
		float speed;
		float unknown134;
		float unknown138;
		float length;
		float unknown140;
		int unknown144;
	};

	// The two ribbons share one primitive: the shaders of the head and the trail
	class BulletTracer : public pure3d::Primitive
	{
	public:
		// 0x102CEC70
		BulletTracer(pure3d::Shader* head, pure3d::Shader* tail);
		// 0x102CE070 (the deleting destructor is 0x102CECF0)
		virtual ~BulletTracer();
		// 0x102D2000: draws the trail's ribbon and then the head's with the cull mode off
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, pure3d::PrimitiveState* state,
			const math::Matrix* world, const pure3d::PrimStreamParameters* parameters, pure3d::PartBinding* binding);
		// slot 5 (0x102CD250): everything, slot 6 (0x102CD2A0): a sphere around the origin, slot 7 (0x102CD230): nothing
		// to batch, slot 8 (0x102CE0A0)
		virtual void GetBoundingBox(math::AABB* box);
		virtual void GetCentre(math::Vector* centre);
		virtual bool FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown);
		virtual int Unknown8();

		// The engine's form of DrawLayer takes the name as a pointer to characters (0x102CFF50)
		void DrawLayer(int layer, const char* name, BulletTracerState* state, const BulletTracerParams::Data* data,
			pure3d::Shader* shader);
		// 0x102CFF50: builds the triangles of one ribbon (layer 0: the head, 1: the trail) and draws them
		void DrawLayer(int layer, const core::Name<core::CaseInsensitiveKey32>& name, BulletTracerState* state,
			const BulletTracerParams::Data* data, pure3d::Shader* shader);

		pure3d::Shader* headShader;
		pure3d::Shader* tailShader;
	};
}

#endif
