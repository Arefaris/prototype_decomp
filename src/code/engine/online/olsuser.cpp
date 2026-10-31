// engine::OLSUserList (the RTTI name is engine::OLSUser; see olsfriend.h). Unit 0x10886A70 - 0x108879EA.
#include "code/engine/online/olsfriend.h"
#include <string.h>

namespace engine
{
	// FUNCTION: ENGINE 0x10886BB0
	// EQUIVALENT: scheduling and register allocation (the engine keeps minus one in ecx and loads the memset arguments after
	// the stores of minus one; 67 %)
	void OLSUserRecord::Reset()
	{
		controller = 0xffffffff;
		id = -1;
		unknown2C = -1;
		unknown14 = 0;
		unknown18 = 0;
		invite = 0;
		flags = 0;
		memset(values, 0, valueCount << 4);
		name.Set("");
	}

	// FUNCTION: ENGINE 0x10886C40
	void OLSUserList::ResetRecord(int index)
	{
		records[index].Reset();
	}

	// FUNCTION: ENGINE 0x10886C60
	void OLSUserList::Reset()
	{
		activeCount = 0;
		currentUser = -1;
		for (int i = 0; i < recordCount; i++)
		{
			ResetRecord(i);
		}
	}

	// FUNCTION: ENGINE 0x10886C90
	int OLSUserList::FindIndexById(int userId)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (userId == records[i].id)
			{
				return records[i].index;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10886CD0
	// EQUIVALENT: register allocation (the engine keeps the records in edi and the controller in esi; 92 %)
	int OLSUserList::FindIndexByController(unsigned int controllerId)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (controllerId == records[i].controller)
			{
				return records[i].index;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10886F50
	void OLSUserList::SetCurrentUser(int id)
	{
		currentUser = id;
	}
}
