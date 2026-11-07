// proto::FramerCam (RTTI name; 4 vftable slots in the camera range): the framer, which frames the fight around the player.
// Only what the other units call is declared; the names are guesses.
#ifndef PROTO_CAMERA_FRAMERCAM_H
#define PROTO_CAMERA_FRAMERCAM_H

namespace proto
{
	// proto::FramerCam (RTTI name): the camera of the framer
	class FramerCam
	{
	public:
		// 0x10347A90 / 0x10347AA0: counts the blocks that keep the framer from moving the camera
		void AddBlock();
		void RemoveBlock();
	};
}

#endif
