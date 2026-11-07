#include "code/engine/surfacedefinition.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/driving/wheelcollectiondata.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x10937570
		content::ClassInfo* WheelData::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::WheelData";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x109375F0
		// NONMATCHING: the engine stores 0xffff between the name's vftable and its first byte, ours puts the zero first (80.0 %)
#ifdef NONMATCHING
		WheelData::WheelData() : unknown44(0xffff)
		{
			unknown48 = 0;
			unknown4C = 0.0f;
			unknown50 = 0.0f;
			unknown54 = 0.0f;
			unknown58 = 0.0f;
			unknown5C = 0.0f;
			unknown60 = 0.0f;
			unknown64 = gHalf;
		}
#endif

		// FUNCTION: ENGINE 0x10937640
		content::MemberList* WheelData::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberStringMetaType<0>(&((WheelData*)content::gStringMemberBase)->name, "p"),
					content::StringBufferOffset(&((WheelData*)content::gStringMemberBase)->name)
					+ (int)&((WheelData*)0)->name, "jointName" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}
