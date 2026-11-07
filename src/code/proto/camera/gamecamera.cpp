// proto::GameCamera (RTTI name; base engine::camera::Camera): the base of the game's cameras. Its own vftable slots are
// small (0x10351120 - 0x10351790; no assert path, the file name is a guess).
#include "code/proto/camera/vehiclecamera.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10351130
	void GameCamera::Slot15(engine::GameObjectHandle object, int hint)
	{
	}

	// FUNCTION: ENGINE 0x10351140
	int GameCamera::GetType()
	{
		return 7;
	}

	// FUNCTION: ENGINE 0x10351150
	void GameCamera::Slot11()
	{
		unknown48 = true;
	}

	// FUNCTION: ENGINE 0x10351160
	void GameCamera::Slot12()
	{
		unknown48 = false;
	}

	// FUNCTION: ENGINE 0x10324C30
	void GameCamera::Slot13(int first, int second)
	{
	}

	// FUNCTION: ENGINE 0x10351190
	bool GameCamera::Slot14(int value)
	{
		return false;
	}
}
