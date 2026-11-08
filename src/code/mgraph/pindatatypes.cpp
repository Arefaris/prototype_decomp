// The registry of the pin data types of the mgraph library (0x10AD2F00).
#include "code/mgraph/pins.h"

namespace engine
{
	// 0x11327754: the registry of the pin data types (another unit defines it)
	extern om::TreeHead gTreeHeadObject11;
}

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AD2ED0
	void UnregisterPinDataType(PinDataTypeBase* dataType)
	{
		om::TreeNode* node;
		if (dataType != 0)
		{
			node = &dataType->treeNode;
		}
		else
		{
			node = 0;
		}
		engine::gTreeHeadObject11.Erase(node);
	}

	// FUNCTION: ENGINE 0x10AD2F00
	// NONMATCHING: shrink-wrap: the engine saves ebx, esi and edi before the first lookup, ours behind the first test (63.3 %)
#ifdef NONMATCHING
	// The pin data type a node of the registry's tree belongs to, null for no node
	static __forceinline PinDataTypeBase* DataTypeOfNode(om::TreeNode* node)
	{
		PinDataTypeBase* dataType;
		if (node != 0)
		{
			dataType = reinterpret_cast<PinDataTypeBase*>(reinterpret_cast<char*>(node) - 0x10);
		}
		else
		{
			dataType = 0;
		}
		return dataType;
	}

	om::MetaTypeBase* FindGraphMetaType(const type_info& type)
	{
		PinDataTypeBase* dataType = DataTypeOfNode(engine::gTreeHeadObject11.First());
		while (dataType != 0)
		{
			const type_info* dataTypeInfo = dataType->GetPacketType()->type;
			if (*dataTypeInfo == type)
			{
				break;
			}
			dataType = DataTypeOfNode(engine::gTreeHeadObject11.Next(&dataType->treeNode));
		}
		return reinterpret_cast<om::MetaTypeBase*>(dataType);
	}
#endif
}
