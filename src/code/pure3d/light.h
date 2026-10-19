// pure3d::Light (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the user data the engine
// hangs on it (pure3d::LightUserData and its subclass pure3d::ProtoLightUserData). Only what the render passes read;
// the accessors are small functions of the light unit (0x10758300 - 0x10758B50) that the passes call. Member and
// method names are guesses.
#ifndef PURE3D_LIGHT_H
#define PURE3D_LIGHT_H

#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	class LightUserData : public RefCounted
	{
	};

	// The engine's own light user data: two intensity scales (the lit pass picks one by mode), a range scale and a
	// flag (1: the light is a cheap, per-vertex light)
	class ProtoLightUserData : public LightUserData
	{
	public:
		float unknown8;
		float unknownC;
		float unknown10;
		unsigned char unknown14[4];
		int cheap;
	};

	// How far a light reaches (RTTI name pure3d::DecayRange, from the render events that carry its shape): kind 0 means
	// without limit, otherwise the range is at +8. The constructor sets the defaults (shape 1, 5, 25, 0.5, 0)
	class DecayRange
	{
	public:
		enum DecayShape
		{
			SHAPE_NONE = 0,
			SHAPE_RANGE = 1
		};

		// 0x10758AC0 / 0x1075A7E0
		DecayRange();
		~DecayRange();
		// 0x10758B10 / 0x10758B50 / 0x10758B20 (the second range: 0 without a limit)
		int GetKind();
		float GetRange();
		float GetUnknown10758B20();
		// 0x10758B00 / 0x1075A7F0 / 0x1075A810 (the two ranges are capped at 10000)
		void SetKind(int newKind);
		void SetUnknown1075A7F0(float value);
		void SetUnknown1075A810(float value);

		int kind;
		float unknown4;
		float range;
		float unknownC;
		int unknown10;
	};

	class RenderParams;

	class Light : public Entity
	{
	public:
		enum LightType
		{
			TYPE_AMBIENT = 1,
			TYPE_DIRECTIONAL = 2,
			TYPE_POINT = 3,
			TYPE_SPOT = 4
		};

		// 0x1075AFB0: a light of the type with the defaults (the render thread's light API makes them)
		explicit Light(LightType newType);

		// 0x10758300: the colour (red, green, blue, intensity)
		const math::Vector4* GetColour();
		// 0x10758340 / 0x10758380
		const math::Vector* GetPosition();
		const math::Vector* GetDirection();
		// 0x107584D0
		DecayRange* GetDecay();
		// 0x10758550: the shadow parameters (null until the shadow is enabled)
		RenderParams* GetShadow();
		// 0x10758560
		bool IsEnabled();
		// 0x107582A0
		LightUserData* GetUserData();
		// 0x10758760: how much of the light's colour goes to the second colour constant
		float GetUnknown10758760();

		// The setters and getters of the render thread's light API (the render light API calls them); the names say the
		// offset of the field they work on, the types follow the calls
		// 0x107582B0 / 0x107582D0 / 0x10758310 / 0x10758350 / 0x10758390 / 0x10758490 / 0x10758CB0
		void SetUnknown158(bool value);
		void SetColour(const math::Vector4* newColour);
		void SetPosition(const math::Vector* newPosition);
		void SetDirection(const math::Vector* newDirection);
		void SetUnknownF0(const math::Vector* value);
		void SetDecay(const DecayRange* newDecay);
		void SetUserData(LightUserData* newData);
		// 0x107583C0 / 0x10758410 / 0x10758450 / 0x107584F0 / 0x10758570 / 0x10758590 / 0x107585C0 / 0x10758720
		void SetUnknown120(float value);
		void SetUnknown124(float value);
		void SetUnknown130(bool value);
		void SetUnknown194(float a, float b, float c);
		void SetUnknown164(int value);
		void SetUnknown168(float value);
		void SetUnknown16C(float value);
		void SetUnknown128(float value);
		// 0x107587A0 / 0x107587C0 / 0x107587F0 / 0x10758810 / 0x10758830 / 0x10758EF0 / 0x10758F70 / 0x10758FA0 /
		// 0x10758FD0
		void SetUnknown188(bool value);
		void SetUnknown107587C0(float value);
		void SetUnknown190(bool value);
		void SetUnknown216(bool value);
		void SetUnknown20C(int value);
		void SetShadowEnabled(bool value);
		void SetUnknown17C(float value);
		void SetUnknown180(float value);
		void SetUnknown184(float value);
		// 0x1075C500: takes three light bit sets of nine words (the unit of the light bit sets)
		void Unknown1075C500(const unsigned int* a, const unsigned int* b, const unsigned int* c);
		// 0x10758400 / 0x10758460 / 0x10758520 / 0x10758580 / 0x107585B0 / 0x107585E0 / 0x10758770 / 0x10758780 /
		// 0x10758790 / 0x107587D0 / 0x107587E0 / 0x10758820 / 0x10758E50
		float GetUnknown120();
		bool GetUnknown130();
		void GetUnknown194(float* a, float* b, float* c);
		int GetUnknown164();
		float GetUnknown168();
		float GetUnknown16C();
		float GetUnknown17C();
		float GetUnknown180();
		float GetUnknown184();
		float GetUnknown107587D0();
		bool GetUnknown190();
		int GetUnknown20C();
		float GetUnknown10758E50();
		// 0x1072D4F0 is Entity's name assignment (the setter of mName)

		unsigned char unknown10[0xB8];
		math::Vector4 colour;
		math::Vector position;
		math::Vector direction;
		unsigned char unknownF0[0x18];
		DecayRange decay;
		unsigned char unknown11C[0x44];
		bool enabled;
		unsigned char unknown161[0x2B];
		int type;
		unsigned char unknown190[0x80];
		LightUserData* userData;
		unsigned char unknown214[0x14];
	};
}

#endif
