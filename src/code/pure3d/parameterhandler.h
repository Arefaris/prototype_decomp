// pure3d::ParameterHandlerTypeless (RTTI name; vftable 0x10E639B4, one slot): the named parameters of a render pass -- a
// tree of name -> typed value. A parameter is either a variable of the owner (a pointer the handler stores through) or
// a pair of functions the owner supplied (called with the owner, the name and the value). The classes
// ParameterHandler<T> derive from it and register the parameters of a pass of type T. Names and the layout of the
// nodes are guesses; the kind numbers are the engine's.
#ifndef PURE3D_PARAMETERHANDLER_H
#define PURE3D_PARAMETERHANDLER_H

#include "code/container/map.h"
#include "code/core/name.h"
#include "code/math/colour128.h"
#include "code/math/pddicolour.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"

namespace pure3d
{
	// The kinds of a parameter: 1 - 11 point at a variable (float, int, unsigned int, bool, Vector, Vector2, Vector4,
	// pddiColour, packed unsigned int colour, four-float colour, reference), 12 - 21 are the functions of the same
	// kinds without the reference and 22 sets a reference through a function
	class ParameterValue
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> ParameterName;

		int kind;
		void* setter;
		void* getter;
	};

	// 0x1074E220 (another unit): orders a name against the name of a parameter node
	int CompareParameter(const void* key, const container::TreeBase::Node* node);

	// The engine's pddiColour as this unit copies it (a copy that is not inlined: 0x107A1E20; the name is a guess)
	struct Colour32
	{
		Colour32()
		{
		}
		Colour32(const Colour32& other);

		union
		{
			unsigned int bits;
			struct
			{
				unsigned int b : 8;
				unsigned int g : 8;
				unsigned int r : 8;
				unsigned int a : 8;
			};
		};
	};

	class ParameterHandlerTypeless
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> ParameterName;
		typedef bool (*SetIntFunction)(void* owner, const ParameterName* name, int value);

		// One parameter (the node's key is the name)
		struct Node : public container::TreeBase::Node
		{
			ParameterName name;
			ParameterValue value;
		};

		// 0x107A2C90
		ParameterHandlerTypeless();
		// Slot 0 (0x107A2CB0 is the body, 0x107A2CD0 the scalar deleting destructor)
		virtual ~ParameterHandlerTypeless();

		// 0x107A1F80 / 0x107A1FE0 / 0x107A2040 / 0x107A20B0 / 0x107A2110 / 0x107A2180 / 0x107A21F0: set the parameter
		// of that name to the value; false when there is none of that kind
		bool SetInt(const ParameterName* name, int value);
		bool SetUnknown1FE0(const ParameterName* name, unsigned int value);
		bool SetFloat(const ParameterName* name, float value);
		bool SetBool(const ParameterName* name, bool value);
		bool SetVector(const ParameterName* name, const math::Vector* value);
		bool SetVector2(const ParameterName* name, const math::Vector2* value);
		bool SetVector4(const ParameterName* name, const math::Vector4* value);
		// 0x107A27C0 / 0x107A2270 / 0x107A2910: a colour as a pddiColour, as a packed word, as four floats
		bool SetColour(const ParameterName* name, const math::pddiColour* value);
		bool SetColourWord(const ParameterName* name, const unsigned int* value);
		bool SetColourFloats(const ParameterName* name, const math::Colour128* value);

		// 0x107A2430 / 0x107A2490 / 0x107A24F0 / 0x107A2550 / 0x107A25B0 / 0x107A2620 / 0x107A2A20
		bool GetInt(const ParameterName* name, int* value);
		bool GetUnknown2490(const ParameterName* name, unsigned int* value);
		bool GetFloat(const ParameterName* name, float* value);
		bool GetBool(const ParameterName* name, bool* value);
		bool GetVector(const ParameterName* name, math::Vector* value);
		bool GetVector4(const ParameterName* name, math::Vector4* value);
		bool GetColour(const ParameterName* name, math::pddiColour* value);
		bool GetColourWord(const ParameterName* name, unsigned int* value);
		bool GetColourFloats(const ParameterName* name, math::Colour128* value);

		void* owner;
		container::TreeBase parameters;
	};
}

#endif
