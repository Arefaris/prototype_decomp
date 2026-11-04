// proto::GlobalShaderRig (reflection names): the shader parameters of the time of day, as named channels of one, two,
// three or four floats (proto::GlobalShaderRig::Param<T>, T a float, a vector or a colour): the name of the shader
// parameter and the channel of its values over the day. Unit 0x1054D580 - 0x10550600 (no assert path; the file name is
// a guess). The reflected names are original.
#ifndef PROTO_TIMEOFDAY_GLOBALSHADERRIG_H
#define PROTO_TIMEOFDAY_GLOBALSHADERRIG_H

#include "code/core/name.h"
#include "code/proto/timeofday/timeofdayvarchannel.h"

namespace proto
{
	struct GlobalShaderRig
	{
		// One named parameter (RTTI proto::GlobalShaderRig::Param<T>; 0x20 bytes)
		template<class T> class Param
		{
		public:
			Param()
			{
			}
			Param(const Param& other) : name(other.name), values(other.values)
			{
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> name;
			int unknown8;
			TimeOfDayVarChannel<T> values;  // +0xC
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		container::ArrayDynamic<Param<float>, container::AllocatorNew> float1s;
		int unknownC;
		container::ArrayDynamic<Param<math::Vector2>, container::AllocatorNew> float2s;  // +0x10
		int unknown1C;
		container::ArrayDynamic<Param<math::Vector>, container::AllocatorNew> float3s;  // +0x20
		int unknown2C;
		container::ArrayDynamic<Param<math::Colour128>, container::AllocatorNew> float4s;  // +0x30
		int unknown3C;
	};
}

namespace container
{
	// The parameters are moved down by the out-of-line AssignRange
	template<> struct ArrayEraseInline<proto::GlobalShaderRig::Param<float> >
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::GlobalShaderRig::Param<math::Vector2> >
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::GlobalShaderRig::Param<math::Vector> >
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::GlobalShaderRig::Param<math::Colour128> >
	{
		enum
		{
			value = 0
		};
	};
}


namespace content
{
	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::GlobalShaderRig::Param<float>)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_ERASE_DECL
	PROTO_KEY_ARRAY_HELPER_TAIL

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::GlobalShaderRig::Param<math::Vector>)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_ERASE_DECL
	PROTO_KEY_ARRAY_HELPER_TAIL

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::GlobalShaderRig::Param<math::Colour128>)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_ERASE_DECL
	PROTO_KEY_ARRAY_HELPER_TAIL
}

#endif
