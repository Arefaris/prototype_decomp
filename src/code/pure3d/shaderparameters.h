// A set of up to 16 named shader parameters (0x118 bytes; copied by 0x10707B00). No name survives; the layout
// follows the copy, the meanings of the fields are unknown.
#ifndef PURE3D_SHADERPARAMETERS_H
#define PURE3D_SHADERPARAMETERS_H

#include "code/core/name.h"

namespace pure3d
{
	struct ShaderParameter
	{
		ShaderParameter() : name()
		{
			unknownC = 0;
			unknown8 = 0;
			unknown9 = 0;
			value = 0;
			unknownA = 4;
			unknownA3 = 0;
		}

		core::Name<core::CaseInsensitiveKey32> name;
		int value;
		int unknown8 : 8;
		unsigned int unknown9 : 8;
		unsigned int unknownA : 3;
		unsigned int unknownA3 : 4;
		unsigned char unknownC : 1;
	};

	class ShaderParameters
	{
	public:
		// 0x102E8BB0
		ShaderParameters();
		ShaderParameters& operator=(const ShaderParameters& other);

		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		ShaderParameter parameters[16];
		bool unknown110;
		int unknown114;
	};
}

#endif
