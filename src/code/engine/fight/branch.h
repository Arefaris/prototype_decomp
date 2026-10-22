// fight::Entity and fight::Branch (RTTI names; Branch has 18 vftable slots at +0 and 2 at +0x10, bases fight::Entity,
// content::LoadObject, core::IRefCount and fight::Param): the branch of a fight tree a behaviour runs. A branch has a
// parent, a list of children and the list of the nodes that watch it (a behaviour keeps the branch as the node of that
// list: the node's payload at +0, its links behind, which is why Register / Unregister take its address).
// Unit 0x105A2440 - 0x105A5F00 (no assert path; the file name is a guess). Names are guesses.
#ifndef ENGINE_FIGHT_BRANCH_H
#define ENGINE_FIGHT_BRANCH_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/engine/fight/sequencer.h"

namespace core
{
	struct IRefCount;
	struct CaseSensitiveKey;
}

namespace engine
{
	class GameObject;
}

namespace fight
{
	class Sequencer;
	class TrackRegistry;
	class Reader;
	class BranchWatch;
	class Branch;
	class Chunk;

	// The head of the list of the nodes that watch a branch (the nodes link through their own words)
	struct WatcherList
	{
		// 0x105A30D0 / 0x105A3150: puts a node at the head of the list / replaces the head
		void Add(BranchWatch* node);
		void SetHead(BranchWatch* node);
		// 0x105A30F0: takes a node out of the list and clears it
		void Remove(BranchWatch* node);
		// 0x105A3AF0: points every node at another branch and hands the list over to it; the first argument is not
		// read
		void Retarget(Branch* unused, Branch* newBranch);

		BranchWatch* head;
	};

	// RTTI: fight::Entity (5 vftable slots, base content::LoadObject): a load object with a name
	class __declspec(align(8)) Entity : public content::LoadObject
	{
	public:
		// 0x105A5120
		Entity();
		// vftable slot 2 (0x105A5170 is the deleting destructor; 0x105A5150 the body)
		virtual ~Entity();

		// 0x105A5160: replaces the name
		void SetName(const core::Name<core::CaseSensitiveKey>& newName);
		// 0x105A3160: the hash of the name
		unsigned __int64 GetNameHash() const;
		// 0x105AA1E0: the name
		const core::Name<core::CaseSensitiveKey>& GetName() const;

		core::Name<core::CaseSensitiveKey> name;  // +8
	};

	class Branch : public Entity, public Param
	{
	public:
		// 0x105A3D30
		Branch();
		// vftable slot 2 (0x105A3DD0 is the deleting destructor; 0x105A3D80 the body)
		virtual ~Branch();

		// vftable slot 5 (0x100166F8 for the branches that are no chunk): whether the branch is the root of a chunk
		virtual bool IsChunkRoot() const
		{
			return false;
		}
		// vftable slot 6 (0x105A27B0): the context the branch's tree belongs to (null without load listeners)
		virtual TrackRegistry* Slot6();
		// vftable slot 7 (0x105A2CA0) / 8 (0x105A2D00) / 9 (0x105A2C90): hand the branch to its properties and to the
		// branches below it
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		// 0x10863FB0: runs the branch on a sequencer with parameters, answering the track it started (or null)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, bool b);
		// 0x10863FB0: starts that track, answering whether it began
		virtual bool Slot11(Sequencer* sequencer, void* params, int a);
		// 0x105A4780 (the sequencer's unit) starts a pending track through it
		virtual void Slot12(int a, core::IRefCount* b, Sequencer* sequencer);
		// vftable slot 13 (0x105A3BE0): reads the branch stored under a key from a reader (the key, the context, the
		// reader, the position)
		virtual bool Slot13(const core::Name<core::CaseSensitiveKey>* key, Chunk* owner, Reader* reader, int position);
		// vftable slot 14 (0x105A26D0): makes another branch the parent
		virtual void Slot14(Branch* newParent);
		// vftable slot 15 (0x105A2960): puts the branch in front of what a link points to and makes a branch its parent
		virtual void Slot15(Branch* newParent, Branch** link);
		// vftable slot 16 (0x105A2980): takes the branch out of the chain the link was in, answering the following one
		virtual void Slot16(Branch** following);
		// vftable slot 17 (0x105A3C60): merges another branch's properties and children into this one
		virtual void Slot17(Branch* other, int argument);

		// vftable slot 0 of the Param part (0x105A3D70)
		virtual Property* GetProperty(int index);

		// 0x105A2F60: hands every property of the nodes below the branch's own to the reader
		bool ReadProperties(Reader* reader);
		// 0x105A2FC0: reads the branches stored below the node (the chunk, the reader, the position of the first)
		bool LoadChildren(Chunk* owner, Reader* reader, int position);
		// 0x105A3860: reads the branch's name, finds its parent and puts it there
		bool ReadHeader(Chunk* owner, Reader* reader, int position);
		// 0x105A3A40 / 0x105A3A90 (under the load listeners' lock): enters the branch's listener list / leaves it
		void Register(void* entry);
		void Unregister(void* entry);
		// 0x105A3AC0: replaces the head of the list of watchers
		void SetWatchers(BranchWatch* head);
		// 0x105A30A0: has the chunk root tell an item when the chunk is loaded (the item hears of this branch)
		void ListChild(Item* child);

		// 0x105A3690: the branch of the tree below this root that a path from the root names
		Branch* FindInTree(const char* path);
		// 0x105A3530: the length the branch's path needs (the hashes of the names written out)
		int GetPathLength(int flag);
		// 0x105A3590: writes the path of the node into a buffer (the same code as Track::GetPath)
		bool GetPath(char* buffer, int size, int flag);
		// 0x105A3740: the branch below this one that a path names (names guessed for these three)
		Branch* FindByPath(const char* path);
		// 0x105A2760 / 0x105A2710: the chunk root this branch is in
		Branch* GetFirstOfTree();
		const Branch* GetFirstOfTree() const;
		// 0x105A2840: the next branch in the tree's order (first child, else the next one up)
		Branch* GetNextOfTree();
		// 0x105A2820: the next branch of the tree after this one and its children
		Branch* GetNextAfterChildren();
		// 0x105A3290 / 0x105A32E0 / 0x105A3350: the last branch of the tree below this one / the previous sibling (the
		// parent for the first one) / the previous branch in the tree's order
		Branch* GetLastOfTree();
		Branch* GetPreviousSiblingOrParent();
		Branch* GetPreviousOfTree();
		// 0x105A33C0 / 0x105A3480 / 0x105A34D0: the index of a child by name / the child of that name in this branch
		// or the ones above it / the child of that name
		int IndexOfChildNamed(const core::Name<core::CaseSensitiveKey>& childName);
		Branch* FindNamedAbove(const core::Name<core::CaseSensitiveKey>& childName);
		Branch* FindChildNamed(const core::Name<core::CaseSensitiveKey>& childName);
		// 0x105A2D60: picks one of the children to run, by weights and a random number
		Branch* PickChild(Sequencer* sequencer, void* params);
		// 0x105A2850: the topmost parent
		Branch* GetRoot();
		// 0x105A2870: the number of parents above this branch
		int GetDepth();
		// 0x105A2890: the number of children
		int GetChildCount();
		// 0x105A28B0 / 0x105A28E0: the child at an index (null past the end)
		Branch* GetChild(int index);
		const Branch* GetChild(int index) const;
		// 0x105A2910: the index of a child (-1 when it is none of them)
		int IndexOfChild(const Branch* child);
		// 0x105A2940: whether this branch is above another
		bool IsAncestorOf(const Branch* other);
		// 0x105A26E0: whether another branch is above this one
		bool IsBelow(const Branch* other) const;
		// 0x105A29A0 / 0x105A2A00: adds a child at an index (-1 for the end), answering the index (-1 for none)
		int AddChild(int index, Branch* child);
		int AddChild(Branch* child);
		// 0x105A2A50 / 0x105A2AB0: takes a child away by index / by address
		bool RemoveChild(int index);
		bool RemoveChild(Branch* child);
		// 0x105A2B10 / 0x105A2C00: moves a child below another parent at an index / at the end
		bool MoveChild(Branch* child, Branch* newParent, int index);
		// 0x105A2C00: puts another branch in the place of a child
		void ReplaceChild(Branch* oldChild, Branch* newChild);
		// 0x105A3430 / 0x105A3460: moves a child to another index of this branch
		bool MoveChildToIndex(int fromIndex, int toIndex);
		bool MoveChild(Branch* child, int toIndex);
		// 0x105A3400: whether this branch's name sorts before another's
		bool IsNameBefore(const Branch* other) const;
		// 0x105A3B30: sorts the children by name (and theirs when asked)
		void SortChildren(bool deep);
		// 0x105A2E50: runs the following branches until one starts (the sequencer, the parameters, the branch to stop at)
		Branch* RunNext(Sequencer* sequencer, void* params, Branch* stop);
		// 0x105A2A10: lets go of every child
		void ReleaseChildren();
		// 0x105A25F0 / 0x105A2600 / 0x105A2610 / 0x105A2620
		int GetIndex() const;
		void SetIndex(int newIndex);
		Branch* GetParent() const;
		Branch* GetNextSibling() const;

		// The position of the branch among its siblings
		int index;  // +0x14
		Branch* parent;  // +0x18
		Branch* firstChild;  // +0x1C
		Branch* nextSibling;  // +0x20
		// The nodes that watch the branch
		WatcherList watchers;  // +0x24
	};

	// The node something registers on a branch it watches (the same 12-byte node as engine::TrackWatch; the branch
	// keeps the list of such nodes)
	class BranchWatch
	{
	public:
		BranchWatch(Branch* newBranch)
		{
			branch = newBranch;
			next = 0;
			prev = 0;
			if (newBranch != 0)
			{
				newBranch->Register(this);
			}
		}
		~BranchWatch()
		{
			if (branch != 0)
			{
				branch->Unregister(this);
			}
		}

		// 0x1007E9C0 (the engine's shared copy): watches another branch
		void Assign(Branch* newBranch);

		Branch* branch;
		BranchWatch* next;
		BranchWatch* prev;
	};
}

#endif
