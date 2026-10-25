// om::Bool32 (RTTI om::Bool32): a boolean that is stored as a 32-bit integer and reflected under its own description.
#ifndef OM_BOOL32_H
#define OM_BOOL32_H

namespace om
{
	class Bool32
	{
	public:
		Bool32()
		{
		}
		Bool32(bool newValue) :
			value(newValue)
		{
		}

		int value;
	};
}

#endif
