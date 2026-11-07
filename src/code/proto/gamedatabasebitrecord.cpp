#include "code/proto/gamedatabasebitrecord.h"

namespace proto
{
	// FUNCTION: ENGINE 0x104DF2D0
	void GameDatabaseBitRecord::OnDBSlot0(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104DF2E0
	void GameDatabaseBitRecord::OnDBSlot1(int a, int b)
	{
		subject = 0;
	}

	// FUNCTION: ENGINE 0x104DF2F0
	bool GameDatabaseBitRecord::Test(int index)
	{
		unsigned int value = subject->GetInt(0, index >> 5);
		unsigned int mask = 1 << (index & 0x1f);
		if (mask & value)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104DF330
	void GameDatabaseBitRecord::Set(int index)
	{
		unsigned int value = subject->GetInt(0, index >> 5);
		unsigned int mask = 1 << (index & 0x1f);
		value |= mask;
		engine::gGameDatabase->SetInt(subjectName, 0, value, index >> 5);
	}

	// FUNCTION: ENGINE 0x104DF380
	void GameDatabaseBitRecord::SetAll()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		for (int i = 0; i < count + 0x1f >> 5; i++)
		{
			database->SetInt(subjectName, 0, -1, i);
		}
	}

	// FUNCTION: ENGINE 0x104DF3E0
	void GameDatabaseBitRecord::Clear(int index)
	{
		unsigned int value = subject->GetInt(0, index >> 5);
		unsigned int mask = 1 << (index & 0x1f);
		value &= ~mask;
		engine::gGameDatabase->SetInt(subjectName, 0, value, index >> 5);
	}

	// FUNCTION: ENGINE 0x104DF440
	void GameDatabaseBitRecord::ClearAll()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		for (int i = 0; i < count + 0x1f >> 5; i++)
		{
			database->SetInt(subjectName, 0, 0, i);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
