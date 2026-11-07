// The branches of the fight tree that run a non-interactive sequence (RTTI: engine::NISNode and engine::NISRootNode, each
// with the 18 vftable slots of a fight::Branch and the 2 of its fight::Param): the node plays the sequence of the
// stream package named like itself; the root adds the sound track, the ease branches, the post NIS branch and the
// flags. Unit 0x108A71B0 - 0x108A8420 (no assert path; the file name is a guess); the member names are guesses.
#ifndef ENGINE_NIS_NISNODES_H
#define ENGINE_NIS_NISNODES_H

#include "code/engine/fight/chunk.h"
#include "code/engine/fight/trackfactory.h"

namespace engine
{
	class StreamPackage;

	// RTTI: engine::NISNode (0x40 bytes)
	class NISNode : public fight::Node
	{
	public:
		// 0x108A7310
		NISNode();
		// vftable slot 2 (0x108A7210 is the deleting destructor)
		virtual ~NISNode()
		{
		}

		// vftable slot 0 of the Param part (0x108A72D0)
		virtual fight::Property* GetProperty(int index);

		// 0x108A71E0 / 0x108A71D0: the time the sequence starts at
		bool SetStartTime(float value);
		float GetStartTime() const;

		// 0x108A7920 / 0x108A72E0: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		StreamPackage* package;  // +0x38: the package of the sequence, found by the name of the node the first time it is asked for
		float startTime;  // +0x3C
	};

	// RTTI: engine::NISRootNode (0xC0 bytes)
	class NISRootNode : public NISNode
	{
	public:
		// 0x108A7340
		NISRootNode();
		// vftable slot 2 (0x108A74A0 is the deleting destructor, 0x108A73C0 the body)
		virtual ~NISRootNode();

		// vftable slot 11 (0x108A7430): puts the node on the sequencer as its pending track
		virtual bool Slot11(fight::Sequencer* sequencer, void* params, int a);
		// vftable slot 12 (0x108A7E50, left to the engine)
		virtual void Slot12(int a, core::IRefCount* b, fight::Sequencer* sequencer);
		// vftable slot 0 of the Param part (0x108A72F0)
		virtual fight::Property* GetProperty(int index);

		// The members the properties hand out
		bool SetSoundTrack(const char* value);
		fight::BranchHolder* GetEaseIn();
		fight::BranchHolder* GetEaseOut();
		bool SetEaseOutBegin(float value);
		bool SetEaseOutOffset(float value);
		bool SetDisableSimulation(bool value);
		fight::BranchHolder* GetPostNIS();
		bool SetAutoUnload(bool value);

		// 0x108A7A10 / 0x108A7300: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		char* soundTrack;  // +0x40
		fight::BranchHolder easeIn;  // +0x44
		fight::BranchHolder easeOut;  // +0x68
		float easeOutBegin;  // +0x8C
		float easeOutOffset;  // +0x90
		fight::BranchHolder postNIS;  // +0x94
		int unknownB8;
		bool disableSimulation;  // +0xBC
		bool autoUnload;  // +0xBD
	};

	// The properties of the two classes (0x11318138 / 0x1131813C)
	extern fight::Property** gNISNodeProperties;
	extern fight::Property** gNISRootNodeProperties;
}

#endif
