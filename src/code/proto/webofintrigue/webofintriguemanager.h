// The web of intrigue manager (RTTI proto::WebOfIntrigueManager, base engine::DBObserver): the mission-like web of
// targets the player works through. It keeps the nodes of the web and the list of the visible ones. Only what the
// units around it use is declared; the members are named after what they answer, the names are guesses.
#ifndef PROTO_WEBOFINTRIGUE_WEBOFINTRIGUEMANAGER_H
#define PROTO_WEBOFINTRIGUE_WEBOFINTRIGUEMANAGER_H

#include "code/core/name.h"
#include "code/math/matrix.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/dbobserver.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// An episode of the web (RTTI proto::WOIEpisode, a load object; only what the manager reads is recovered)
	class WOIEpisode : public content::MetaLoadObject
	{
	public:
		// 0x10563080
		static content::ClassInfo* GetClassInfo();

		int done;  // +8
		int total;  // +0xC

		// 0x1055B520 / 0x1055B530 / 0x1055B540 (names guessed)
		int GetDone();
		int GetTotal();
		void IncrementDone();
		// 0x105630F0 (another unit)
		void ResetDone();
	};

	// RTTI: proto::WebOfIntrigueManager
	class WebOfIntrigueManager : public engine::DBObserver
	{
	public:
		// RTTI: proto::WebOfIntrigueManager::Node (a node of the web: its index is at +8)
		class Node;

		// 0x1055CC40: the node of the web an object is the target of (null when it is none; name guess)
		Node* FindNode(engine::GameObjectHandle handle);
		// 0x1055CA30: gives a node the transform of its locator (name guess)
		void SetNodeTransform(int nodeID, const math::Matrix* transform);
		// 0x1055CA70: tells the manager that the locator of a node has loaded (name guess)
		void NodeLocatorLoaded(int nodeID);

		// 0x1055B9E0 / 0x1055BA10: the node at an index of the web / the episode at an index of the visible list,
		// null outside
		Node* GetNode(int index);
		WOIEpisode* GetVisibleNode(int index);
		// 0x1055BA40 / 0x1055BA50
		int GetVisibleCount();
		int GetNodeCount();
		// 0x1055BA60: the index of the node with that id, -1 for none
		int FindNodeIndex(int nodeID);
		// 0x1055BAB0: how far a visible episode is (a whole division of its two counts)
		float GetVisibleProgress(int index);
		// 0x1055BAF0 / 0x1055BB20: the two counts of a visible episode
		int GetVisibleNodeID(int index);
		int GetVisibleNodeTotal(int index);
		// 0x1055BB50, 0x1055BC40, 0x1055BC60, 0x1055BC90, 0x1055BCB0: members of the node at an index (defaults for none)
		int GetNodeEpisode(int index);
		int GetNodeID(int index);
		int GetNodeKinds(int index);
		float GetNodeX(int index);
		float GetNodeY(int index);
		// 0x1055B900: appends an episode to the visible list (ten at most)
		void AddVisible(WOIEpisode* episode);
		// 0x1055BB70: selects a node
		void SelectNode(Node* node);
		// 0x1055B550 / 0x1055B560 / 0x1055B570 / 0x1055B590 / 0x1055B5A0 (names guessed)
		int GetUnknown420();
		float GetUnknown454();
		int IsUnknown458Clear();
		int GetSelectedIndex();
		int GetSelectedEpisode();
		// 0x1055BE90 / 0x1055BEA0 / 0x1055BED0 / 0x1055BEF0 / 0x1055C010
		void SetUnknown46C();
		void SetUnknown458(float value, bool force);
		void SetUnknown454(float value);
		void ClearUnknown458();
		bool GetUnknown45C();
		// 0x1055BCD0 / 0x1055BD00: the state of the node at an index / with an id
		int GetNodeState(int index);
		int GetNodeStateByID(int nodeID);
		// 0x1055BD20: whether every visible episode is done
		bool AreAllEpisodesDone();
		// 0x1055BD70: the first flag of the node at an index
		bool GetNodeFirstFlag(int index);
		// 0x1055B950: puts the nodes of an episode back (clears their flag 0x80) and counts the episodes opened
		void ResetEpisodeStates(int episode);
		// 0x1055BDA0 / 0x1055BDF0 / 0x1055BE40: move the node with an id along its states (names guessed)
		void StartNodeState(int nodeID);
		void ClearNodeFlag40(int nodeID);
		void ClearNodeFlag20(int nodeID);
		// 0x1055CAA0: selects the node with an id
		void SelectNodeByID(int nodeID);
		// 0x1055CB40: whether the node at an index has the link flag set
		bool GetNodeLinkFlag(int index, unsigned int place);
		// 0x1055CB70: links two nodes with each other by their ids
		void LinkNodes(int firstID, int secondID);
		// 0x1055C260: counts the finished nodes in their episodes and remembers the highest episode in use
		void CountFinishedNodes();
		// 0x1055C2E0: sets every node to its first state, clears the episodes' counts and counts again
		void ResetAllNodes();
		// 0x1055C360: sets every node to the state 2
		void SetAllNodesOpen(int unused);
		// 0x1055BF00: remembers that a node was targeted (the state 2 when its episode is done, else 1)
		void OnNodeTargeted(Node* node);
		// 0x1055BF60: tells the scenario that a target was consumed and forgets the targeting
		void SendTargetConsumed();
		// 0x1055C020: whether some node is open to be worked on
		bool HasOpenNode();
		// 0x1055C090: the id of the first available node with one of the kinds, -1 for none
		int FindOpenNodeID(unsigned int kinds);
		// 0x1055CAD0 / 0x1055CB10: how many links the node at an index has / the link at a place
		int CountNodeLinks(int index);
		int GetNodeLink(int index, unsigned int place);

		Node* nodes[0xff];  // +4
		Node** nodeListBegin;  // +0x400 (a second list of the nodes)
		Node** nodeListEnd;  // +0x404
		Node** nodeListCapacity;  // +0x408
		int unknown40C;
		int nodeCount;  // +0x410
		int unknown414;
		int selectedIndex;  // +0x418
		int selectedEpisode;  // +0x41C
		int unknown420;
		engine::DBSubject* subject;  // +0x424
		int visibleCount;  // +0x428
		WOIEpisode* visible[10];  // +0x42C
		float unknown454;
		float unknown458;
		bool unknown45C;
		unsigned char unknown45D[3];
		int unknown460;
		int unknown464;
		int unknown468;
		bool unknown46C;
	};

	// 0x11272D48: the one manager (null: none)
	extern WebOfIntrigueManager* gWebOfIntrigueManager;
}

#endif
