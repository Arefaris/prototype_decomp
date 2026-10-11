// code/engine/system/poimanager.hpp (path from the header's own asserts): per-player points of interest. Each
// player has a POIManager (0xE0 bytes, an array of sMaxPlayers of them): a stack of the game objects the player
// controls and a stack of world streamer points of interest (positions or objects the streamer follows). Member
// names with the m prefix, the stack sizes and sMaxPlayers / sRegisteredPlayers come from assert strings; the
// class name follows the file, everything else is guessed.
#ifndef ENGINE_SYSTEM_POIMANAGER_HPP
#define ENGINE_SYSTEM_POIMANAGER_HPP

#include "code/core/debug.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

#define POI_HPP_FILE "c:\\workspace\\outrun\\proto\\atg\\engine\\code\\engine/system/poimanager.hpp"

namespace math
{
	// 0x11283234: the zero vector the engine copies (name guessed)
	extern const Vector kZeroVector;
}

namespace engine
{
	// The payload of PlayerControlChangedMessage (another unit: constructor 0x10862340, Reset 0x108622E0): the index
	// of the player that now controls the object, -1 when none
	class PlayerControlInfo
	{
	public:
		PlayerControlInfo();
		void Reset();

		int playerIndex;
		int unknown4;
	};

	// engine::PlayerControlChangedMessage (RTTI name): sent to a game object when a player takes or loses control
	// of it; message type 14
	class PlayerControlChangedMessage : public IntrusiveMessage
	{
	public:
		PlayerControlChangedMessage();
		virtual ~PlayerControlChangedMessage();

		PlayerControlInfo info;
	};

	class POIManager
	{
	public:
		enum
		{
			CONTROLLED_OBJECT_STACK_SIZE = 4,
			WORLD_STREAM_POI_STACK_SIZE = 8
		};

		enum
		{
			POI_NONE,
			POI_OBJECT,
			POI_POSITION
		};

		// A point of interest: an object (whose position is followed while it is valid) or a fixed position, with
		// a serial number from a global counter
		class WorldStreamerPOI
		{
		public:
			WorldStreamerPOI();
			explicit WorldStreamerPOI(math::Vector point);
			explicit WorldStreamerPOI(GameObjectHandle object);

			math::Vector GetPosition() const;

			GameObjectHandle handle;
			math::Vector position;
			int type;
			int serial;
		};

		POIManager();
		~POIManager()
		{
		}

		// Back to empty stacks
		void Reset();
		// Inline (poimanager.hpp); 0x10825B00 is the kept copy
		int GetPlayerIndex() const
		{
			unsigned int index = this - sManagers;
			OLD_ASSERT_AT(POI_HPP_FILE, 0xdd, index < (unsigned)sMaxPlayers, "index < ( unsigned )sMaxPlayers", "");
			return index;
		}
		// Pushes a point of interest and returns its serial; Pop drops the top one
		int PushPOI(float x, float y, float z);
		int PushPOI(GameObjectHandle object);
		void PopPOI(GameObjectHandle object);
		void PopPOI(int serial);
		// The controlled object stack: the top entry is the object the player controls
		void PushControlled(GameObjectHandle object);
		void PopControlled(GameObjectHandle object);
		// Both stacks at once
		void Push(GameObjectHandle object);
		void Pop(GameObjectHandle object);
		void Replace(GameObjectHandle object);
		GameObjectHandle GetControlled() const
		{
			return mControlledObjectStackIndex != 0 ? mControlledObjectStack[mControlledObjectStackIndex - 1]
				: GameObjectHandle();
		}

		static POIManager* sManagers;
		static int sMaxPlayers;
		static int sRegisteredPlayers;
		static int sNextSerial;
		// Called with the player index when the point of interest stack, the registered player or the controlled
		// object changes
		static void (*sPOIChanged)(int playerIndex);
		static void (*sPlayerRegistered)(int playerIndex);
		static void (*sControlChanged)(int playerIndex);

		static POIManager& Get(int playerIndex)
		{
			OLD_ASSERT_AT(POI_HPP_FILE, 0xd4, playerIndex < sMaxPlayers, "playerIndex < sMaxPlayers", "");
			return sManagers[playerIndex];
		}
		static void CreateAll();
		static void DestroyAll();
		static void ResetAll();
		static bool IsFirstPlayerActive();
		static int GetRegisteredPlayers();
		static GameObjectHandle GetPlayerObject(int playerIndex);
		static void RegisterPlayer(int playerIndex, GameObjectHandle playerPositionHandle, bool active);
		// Tells the object that lost control and the one that gained it (PlayerControlChangedMessage)
		void ChangeControl(GameObjectHandle previous, GameObjectHandle next);

		GameObjectHandle mControlledObjectStack[CONTROLLED_OBJECT_STACK_SIZE];
		int mControlledObjectStackIndex;
		WorldStreamerPOI mWorldStreamerPOIStack[WORLD_STREAM_POI_STACK_SIZE];
		int mWorldStreamerPOIStackIndex;
		GameObjectHandle mPlayer;
		bool mInactive;
	};
}

#endif
