// A set of up to 16 named shader parameters (0x118 bytes; copied by 0x10707B00). No name survives; the layout
// follows the copy, the meanings of the fields are unknown.
#ifndef PURE3D_SHADERPARAMETERS_H
#define PURE3D_SHADERPARAMETERS_H

#include "code/core/name.h"

namespace pure3d
{
	struct ShaderParameter
	{
		core::Name<core::CaseInsensitiveKey32> name;
		int value;
		unsigned int unknown8 : 8;
		unsigned int unknown9 : 8;
		unsigned int unknownA : 3;
		unsigned int unknownA3 : 4;
		unsigned char unknownC : 1;
	};

	class ShaderParameters
	{
	public:
		ShaderParameters& operator=(const ShaderParameters& other);

		int unknown0[4];
		ShaderParameter parameters[16];
		bool unknown110;
		int unknown114;
	};
}

#endif
