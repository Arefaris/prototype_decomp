// engine::OLSProfile: see olsprofile.h. Unit 0x10888D20 - 0x10889D80 (no assert path; the file name is a guess).
#include "code/engine/online/olsfriend.h"
#include "code/engine/online/ols.h"

namespace engine
{
	// Set while a profile is being picked (0x11316E4D; name guessed)
	extern bool gSelectingProfile;

	// FUNCTION: ENGINE 0x10888D20
	void OLSProfile::Slot4(int a, int b, int c, int d, int e)
	{
	}

	// FUNCTION: ENGINE 0x10888DF0
	void OLSProfile::Slot5(int a, int b, int c, int d, int e)
	{
	}

	// FUNCTION: ENGINE 0x10888E00
	void OLSProfile::Slot6(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10888E10
	// EQUIVALENT: scheduling (the engine reads the user back from the message after the call that gets the services, ours
	// passes the register; 65 %)
	void OLSProfile::SelectProfile(int index)
	{
		gSelectingProfile = true;
		OLSProfileMessage message(6);
		int user;
		if (index < 0)
		{
			user = -1;
			currentProfile = -1;
		}
		else
		{
			user = entries[index].user;
			currentProfile = index;
		}
		message.unknown10 = user;
		message.user = currentProfile;
		message.unknownC = 0;
		OLS::Get()->userList->SetCurrentUser(message.unknown10);
		if (OLS::Get()->friends != 0)
		{
			OLS::Get()->friends->OnProfileSelected(index);
		}
		OLS::Get()->SendMessage(&message);
		gSelectingProfile = false;
	}

	// FUNCTION: ENGINE 0x10888EC0
	OLSUser* OLSProfile::GetUser(unsigned int index)
	{
		int user = entries[index].user;
		if (user != -1)
		{
			return (OLSUser*)&OLS::Get()->userList->records[user];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10888F00
	bool OLSProfile::Slot12()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10889D50
	void OLSProfile::Slot14(int a)
	{
	}

	// FUNCTION: ENGINE 0x10889D60
	void OLSProfile::Slot15(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10889D70
	void OLSProfile::Slot16(int a)
	{
	}
}
