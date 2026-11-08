// proto::GlobalFBEffectsRig (reflection names): the framebuffer effects of the time of day, each a channel of keys over
// the day: the bloom, the tone mapping, the colour matrix and the depth of field with the parameter structs
// proto::GlobalFBEffectsRig::BloomParameters, TonemapParameters, ColourMatrixParameters and DOFParameters, and the
// channel class proto::GlobalFBEffectsRigChannel<T> (RTTI) that adds the "enable" flag. Unit 0x1052E0F0 - 0x1053D870
// (no assert path; the file name is a guess). The reflected names are original, the defaults are the ones the engine's
// key constructors store.
#ifndef PROTO_TIMEOFDAY_GLOBALFBEFFECTSRIG_H
#define PROTO_TIMEOFDAY_GLOBALFBEFFECTSRIG_H

#include "code/proto/timeofday/timeofdayvarchannel.h"

namespace engine
{
	namespace driving
	{
		// 0x10D946E0, 0x10D94CC4, 0x10D95578, 0x10D95E48: 1, 0.5, 2 and 30 in the pooled constants
		extern const float gOne;
		extern const float gHalf;
		extern const float gTwo;
		extern const float gThirty;
	}
}

namespace proto
{
	// 0x10D977EC: 10.0f in the pooled constants
	extern const float gTen;

	// A channel of the framebuffer effects rig (RTTI proto::GlobalFBEffectsRigChannel<T>; 24 bytes): the channel and the
	// flag that switches the effect
	template<class T> class GlobalFBEffectsRigChannel : public TimeOfDayVarChannel<T>
	{
	public:
		GlobalFBEffectsRigChannel()
		{
		}
		virtual ~GlobalFBEffectsRigChannel()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool enable;  // +0x14
	};

	// The rig (reflection name proto::GlobalFBEffectsRig; 0x60 bytes): the four effects' channels
	struct GlobalFBEffectsRig
	{
		// The colour matrix pass (72 bytes)
		struct ColourMatrixParameters
		{
			__forceinline ColourMatrixParameters()
			{
				brightness = 0.0f;
				contrast = engine::driving::gOne;
				midpoint = engine::driving::gHalf;
				saturation = engine::driving::gOne;
				hue = 0.0f;
				tint.r = engine::driving::gOne;
				tint.g = engine::driving::gOne;
				tint.b = engine::driving::gOne;
				tint.a = engine::driving::gOne;
				cmyk.x = 0.0f;
				cmyk.y = 0.0f;
				cmyk.z = 0.0f;
				cmykScale = 0.0f;
				cmykBias = 0.0f;
				grainSpeed = 0.0f;
				grainIntensity = 0.0f;
				overlayOpacity = engine::driving::gOne;
				overlaySaturation = engine::driving::gOne;
			}
			// The member-wise copy is the engine's function (0x10514960, in the unit of the time of day manager)
			ColourMatrixParameters& operator=(const ColourMatrixParameters& other);
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float brightness;
			float contrast;
			float midpoint;
			float saturation;
			float hue;
			math::Colour128 tint;  // +0x14
			math::Vector cmyk;  // +0x24
			float cmykScale;  // +0x30
			float cmykBias;
			float grainSpeed;
			float grainIntensity;
			float overlayOpacity;
			float overlaySaturation;
		};

		// The tone mapping (20 bytes)
		struct TonemapParameters
		{
			__forceinline TonemapParameters()
			{
				avgLum = 0.7f;
				adaptRate = engine::driving::gThirty;
				rangeLower = engine::driving::gOne;
				rangeUpper = 2.5f;
				exposurePower = engine::driving::gOne;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float avgLum;
			float adaptRate;
			float rangeLower;
			float rangeUpper;
			float exposurePower;
		};

		// The bloom (60 bytes)
		struct BloomParameters
		{
			__forceinline BloomParameters()
			{
				bloom = 0.0f;
				backbuffer = engine::driving::gOne;
				radiusX = gTen;
				radiusY = gTen;
				cutoff = engine::driving::gOne;
				falloff = engine::driving::gTwo;
				brightness = 0.0f;
				contrast = 0.0f;
				hue = 0.0f;
				midpoint = engine::driving::gHalf;
				saturation = engine::driving::gOne;
				tint.r = engine::driving::gOne;
				tint.g = engine::driving::gOne;
				tint.b = engine::driving::gOne;
				tint.a = engine::driving::gOne;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float bloom;
			float backbuffer;
			float radiusX;
			float radiusY;
			float cutoff;
			float falloff;
			float brightness;
			float contrast;
			float hue;
			float midpoint;
			float saturation;
			math::Colour128 tint;  // +0x2C
		};

		// The depth of field (16 bytes)
		struct DOFParameters
		{
			__forceinline DOFParameters()
			{
				nearDepth = 0.0f;
				farDepth = 0.0f;
				range = engine::driving::gOne;
				aperture = 0.0f;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float nearDepth;
			float farDepth;
			float range;
			float aperture;
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The channels of the effects (the engine keeps a copy for const rigs)
		GlobalFBEffectsRigChannel<BloomParameters>* GetBloomKeys();
		GlobalFBEffectsRigChannel<TonemapParameters>* GetTonemapKeys();
		GlobalFBEffectsRigChannel<ColourMatrixParameters>* GetColourMatrixKeys();
		GlobalFBEffectsRigChannel<DOFParameters>* GetDofKeys();
		const GlobalFBEffectsRigChannel<BloomParameters>* GetBloomKeys() const;
		const GlobalFBEffectsRigChannel<TonemapParameters>* GetTonemapKeys() const;
		const GlobalFBEffectsRigChannel<ColourMatrixParameters>* GetColourMatrixKeys() const;
		const GlobalFBEffectsRigChannel<DOFParameters>* GetDofKeys() const;

		GlobalFBEffectsRigChannel<BloomParameters> bloomKeys;  // +0
		GlobalFBEffectsRigChannel<TonemapParameters> tonemapKeys;  // +0x18
		GlobalFBEffectsRigChannel<ColourMatrixParameters> colourMatrixKeys;  // +0x30
		GlobalFBEffectsRigChannel<DOFParameters> dofKeys;  // +0x48
	};

}

namespace proto
{
	// Left to the engine (declared and mapped in symbols.txt, not defined): the compile of these keys' operations schedules
	// the loads, the constants and the copies of the struct differently
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::AddKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::TonemapParameters>::AddKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::AddKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::DOFParameters>::AddKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::RemoveKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::ResetKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::TonemapParameters>::ResetKey(float time);
	template<> void TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::ResetKey(float time);
}

namespace proto
{
	// The framebuffer effects' RemoveKey reaches the array through a reference
	template<> struct KeyOrder<GlobalFBEffectsRig::ColourMatrixParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<GlobalFBEffectsRig::TonemapParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<GlobalFBEffectsRig::BloomParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 1
		};
	};
	template<> struct KeyOrder<GlobalFBEffectsRig::DOFParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
}

namespace container
{
	// Reserve of the colour matrix keys stores the begin pointer first
	template<> struct ArrayReserveBeginFirst<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::Key>
	{
		enum
		{
			value = 1
		};
	};
	// The keys of the effects are moved down by the out-of-line AssignRange
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::TonemapParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::DOFParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::Key)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT_DECL
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::TonemapParameters>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, sDefault);)
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::Key)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_ERASE_DECL
	PROTO_KEY_ARRAY_HELPER_TAIL

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::DOFParameters>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, sDefault);)
	PROTO_KEY_ARRAY_HELPER_END
}

#endif
