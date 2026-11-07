#include "code/proto/webofintrigue/webofintriguemanager.h"
#include "code/engine/camera/director.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/nis/nis.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/content/enummetatype.h"
#include "code/content/arraycmetatype.h"
#include "code/container/arrayc.h"
#include "code/proto/scenariomessages.h"

namespace proto
{
	// 0x10D977EC
	extern const float gTen;
}

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gMale;
	extern core::Name<core::CaseSensitiveKey> gFemale;
	extern core::Name<core::CaseSensitiveKey> gWoi;
	extern MessageListeners gScenario6;
}

namespace proto
{
	// A node of the web of intrigue (RTTI proto::WebOfIntrigueManager::Node, a load object of 0xF0 bytes; the members
	// are named by what the manager reads from them, the names are guesses)
	class WebOfIntrigueManager::Node : public content::MetaLoadObject
	{
	public:
		// proto::WebOfIntrigueManager::Node::Type and AmbientType (the reflected enumerations)
		enum Type
		{
			TYPE_AMBIENT,
			TYPE_CHARACTER,
			TYPE_MILITARY
		};
		enum AmbientType
		{
			AMBIENT_HUMAN_MALE,
			AMBIENT_HUMAN_FEMALE,
			AMBIENT_COP_MALE
		};

		// 0x1055C810
		Node();
		// 0x1055C8E0 (the deleting destructor is 0x1055DFF0)
		virtual ~Node();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 3 (0x105613F0, another unit) and 4 (0x1055B770)
		virtual void Slot3(int unused);
		virtual bool IsReady();

		int id;  // +8
		int links[6];  // +0xC ("strands")
		Type kinds;  // +0x24 (the reflected "type")
		int episode;  // +0x28
		float x;  // +0x2C
		float y;  // +0x30
		int unknown34;
		core::Name<core::CaseSensitiveKey> unknown38;
		core::Name<core::CaseSensitiveKey> name;  // +0x40
		AmbientType type;  // +0x48 (the reflected "ambientType")
		int flags;  // +0x4C
		float unknown50;
		float unknown54;
		engine::NISTransform transformA;  // +0x58
		bool unknown98;
		unsigned char unknown99;
		engine::GameObjectHandle target;  // +0x9A
		engine::NISTransform transformB;  // +0xA0
		bool useTransformB;  // +0xE0
		unsigned char unknownE1[3];
		float unknownE4;
		float unknownE8;
		int unknownEC;

		// 0x1055B780: stores the state of the node in the database and tells the scenario
		void SetState(unsigned int state, bool notify);
		// 0x1055B800: the state of the node in the database (1 without the subject)
		int GetState();
		// 0x1055B830
		bool IsType2();
		// 0x1055B840: the transform of the node
		engine::NISTransform* GetTransform();
		// 0x1055C8F0: the name of the node's gender (names guessed)
		core::Name<core::CaseSensitiveKey> GetGenderName();
		// 0x1055C940 / 0x1055C990 / 0x1055C9E0: the flag of the link at a place in the state / of the link to a node
		// 0x1055B5B0 / 0x1055B5C0: the first flag (the reflected "autoplay")
		bool GetAutoplay() const;
		void SetAutoplay(bool on);
		bool GetLinkFlag(unsigned int place);
		void SetLinkFlag(unsigned int place, bool on);
		void MarkLink(int linkID);
		// The place of the link to a node, -1 for none
		int IndexOfLink(int linkID)
		{
			for (int i = 0; i < 6; i++)
			{
				if (links[i] == -1)
				{
					return -1;
				}
				if (links[i] == linkID)
				{
					return i;
				}
			}
			return -1;
		}
	};

	// FUNCTION: ENGINE 0x1055C810
	// NONMATCHING: the engine's scheduling of the member stores and of the constants differs (54 %)
#ifdef NONMATCHING
	WebOfIntrigueManager::Node::Node() : id(-1), kinds(TYPE_AMBIENT), episode(0), x(0.0f), y(0.0f), unknown38(), name(),
		type(AMBIENT_HUMAN_MALE), flags(0), unknown50(20.0f), unknown54(gTen), unknown98(false), target(),
		useTransformB(false), unknownE4(0.0f), unknownE8(0.0f)
	{
		links[0] = -1;
		links[1] = -1;
		links[2] = -1;
		links[3] = -1;
		links[4] = -1;
		links[5] = -1;
	}
#endif

	// FUNCTION: ENGINE 0x1055C8E0
	WebOfIntrigueManager::Node::~Node()
	{
	}

	// FUNCTION: ENGINE 0x1055B770
	bool WebOfIntrigueManager::Node::IsReady()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1055B5B0
	bool WebOfIntrigueManager::Node::GetAutoplay() const
	{
		return (flags & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1055B5C0
	void WebOfIntrigueManager::Node::SetAutoplay(bool on)
	{
		int bits = flags;
		if (on)
		{
			flags = bits | 1;
			return;
		}
		flags = bits & 0xfffffffe;
	}

	// FUNCTION: ENGINE 0x1055B780
	void WebOfIntrigueManager::Node::SetState(unsigned int state, bool notify)
	{
		engine::gGameDatabase->SetInt(engine::gWoi, 0, state, id);
		if (notify)
		{
			int nodeID = id;
			WOINodeStateScenarioMessage message;
			message.nodeID = nodeID;
			message.state = state & 0xffff;
			engine::SendMessage(&message, &engine::gScenario6);
		}
	}

	// FUNCTION: ENGINE 0x1055C940
	bool WebOfIntrigueManager::Node::GetLinkFlag(unsigned int place)
	{
		if (place > 5 || links[place] == -1)
		{
			return false;
		}
		int state = GetState();
		return (int)((1 << (0x1e - place)) & state) > 0;
	}

	// FUNCTION: ENGINE 0x1055C990
	void WebOfIntrigueManager::Node::SetLinkFlag(unsigned int place, bool on)
	{
		if (place > 5 || links[place] == -1)
		{
			return;
		}
		unsigned int state = GetState();
		state |= (unsigned int)on << (0x1e - place);
		SetState(state, false);
	}

	// FUNCTION: ENGINE 0x1055C9E0
	void WebOfIntrigueManager::Node::MarkLink(int linkID)
	{
		int place = IndexOfLink(linkID);
		if (place != -1)
		{
			SetLinkFlag(place, true);
		}
	}

	// FUNCTION: ENGINE 0x1055B800
	int WebOfIntrigueManager::Node::GetState()
	{
		engine::DBSubject* subject = gWebOfIntrigueManager->subject;
		if (subject != 0)
		{
			return subject->GetInt(0, id);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1055B830
	bool WebOfIntrigueManager::Node::IsType2()
	{
		return type == 2;
	}

	// FUNCTION: ENGINE 0x1055B840
	engine::NISTransform* WebOfIntrigueManager::Node::GetTransform()
	{
		if (useTransformB)
		{
			return &transformB;
		}
		return &transformA;
	}

	// FUNCTION: ENGINE 0x1055C8F0
	core::Name<core::CaseSensitiveKey> WebOfIntrigueManager::Node::GetGenderName()
	{
		switch (type)
		{
		case 0:
			return engine::gMale;
		case 1:
			return engine::gFemale;
		case 2:
			return engine::gMale;
		}
		return engine::gMale;
	}

	// FUNCTION: ENGINE 0x1055BCD0
	int WebOfIntrigueManager::GetNodeState(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->GetState() & 0xffff;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1055BD00
	int WebOfIntrigueManager::GetNodeStateByID(int nodeID)
	{
		return GetNodeState(FindNodeIndex(nodeID));
	}

	// FUNCTION: ENGINE 0x1055BD20
	bool WebOfIntrigueManager::AreAllEpisodesDone()
	{
		int count = visibleCount;
		for (int i = 0; i < count; i++)
		{
			if (GetVisibleProgress(i) < 1.0f)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1055BD70
	bool WebOfIntrigueManager::GetNodeFirstFlag(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return (node->flags & 1) != 0;
		}
		return false;
	}

	namespace
	{
		const content::EnumValue sNodeTypeValues[] =
		{
			{ "Ambient", 0 },
			{ "Character", 1 },
			{ "Military", 2 }
		};

		const content::EnumValue sNodeAmbientTypeValues[] =
		{
			{ "human_male", 0 },
			{ "human_female", 1 },
			{ "cop_male", 2 }
		};
	}
}

namespace content
{
	// FUNCTION: ENGINE 0x1055B6B0
	template<> void EnumInfo<proto::WebOfIntrigueManager::Node::Type>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::WebOfIntrigueManager::Node::Type";
		*code = "p";
		*values = proto::sNodeTypeValues;
		*count = 3;
	}

	// FUNCTION: ENGINE 0x1055B6F0
	template<> void EnumInfo<proto::WebOfIntrigueManager::Node::AmbientType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "proto::WebOfIntrigueManager::Node::AmbientType";
		*code = "p";
		*values = proto::sNodeAmbientTypeValues;
		*count = 3;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1055B730
	content::ClassInfo* WebOfIntrigueManager::Node::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WebOfIntrigueManager::Node";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1055FCD0
	content::MemberList* WebOfIntrigueManager::Node::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Node, int, 0>("p"), PROTO_OFFSET(Node, id), "id" },
			{ content::GetArrayCMetaType<Node, container::ArrayC<int, 6> >(6, 4,
				content::GetMemberPrimitiveMetaType<Node, int, 1>("p"), "p"), PROTO_OFFSET(Node, links), "strands" },
			{ content::GetEnumMetaType<Type>(), 0x24, "type" },
			{ content::GetMemberMetaType<Node, bool, 0>(&Node::GetAutoplay, &Node::SetAutoplay, "p"), 0, "autoplay" },
			{ content::GetMemberPrimitiveMetaType<Node, int, 2>("p"), PROTO_OFFSET(Node, episode), "episodeID" },
			{ content::GetMemberPrimitiveMetaType<Node, float, 0>("p"), PROTO_OFFSET(Node, x), "feX" },
			{ content::GetMemberPrimitiveMetaType<Node, float, 1>("p"), PROTO_OFFSET(Node, y), "feY" },
			{ content::GetEnumMetaType<AmbientType>(), 0x48, "ambientType" },
			{ content::GetMemberNameMetaType<Node, 0>(true, true, "p"), PROTO_OFFSET(Node, unknown38), "objectName" },
			{ content::GetMemberNameMetaType<Node, 1>(true, true, "p"), PROTO_OFFSET(Node, name), "objectTemplate" },
			{ content::GetMemberPrimitiveMetaType<Node, float, 2>("p"), PROTO_OFFSET(Node, unknown50), "reopenTime" },
			{ content::GetMemberPrimitiveMetaType<Node, float, 3>("p"), PROTO_OFFSET(Node, unknown54), "reactionTime" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1055B860
	void AddWebOfIntrigueSubject()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		engine::DBSubjectInfo info(true, 0xff, -1);
		database->AddIntSubject(engine::gWoi, 0, 0x81, info);
	}

	// FUNCTION: ENGINE 0x1055B8C0
	void ReleaseWebOfIntrigueSubject()
	{
		engine::gGameDatabase->ReleaseSubject(engine::gWoi);
	}

	// FUNCTION: ENGINE 0x1055B8F0
	void WebOfIntrigueManager::ClearSubject(int unused, int unused2)
	{
		subject = 0;
	}

	// FUNCTION: ENGINE 0x1055B9C0
	void WebOfIntrigueManager::UnregisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x1055B520
	int WOIEpisode::GetDone()
	{
		return done;
	}

	// FUNCTION: ENGINE 0x1055B530
	int WOIEpisode::GetTotal()
	{
		return total;
	}

	// FUNCTION: ENGINE 0x1055B540
	void WOIEpisode::IncrementDone()
	{
		done++;
	}

	// FUNCTION: ENGINE 0x1055B550
	int WebOfIntrigueManager::GetUnknown420()
	{
		return unknown420;
	}

	// FUNCTION: ENGINE 0x1055B560
	float WebOfIntrigueManager::GetUnknown454()
	{
		return unknown454;
	}

	// FUNCTION: ENGINE 0x1055B570
	int WebOfIntrigueManager::IsUnknown458Clear()
	{
		if (unknown458 <= 0.0f)
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055B590
	int WebOfIntrigueManager::GetSelectedIndex()
	{
		return selectedIndex;
	}

	// FUNCTION: ENGINE 0x1055B5A0
	int WebOfIntrigueManager::GetSelectedEpisode()
	{
		return selectedEpisode;
	}

	// FUNCTION: ENGINE 0x1055CA30
	void WebOfIntrigueManager::SetNodeTransform(int nodeID, const math::Matrix* transform)
	{
		Node* node = GetNode(FindNodeIndex(nodeID));
		if (node != 0)
		{
			node->transformA = *reinterpret_cast<const engine::NISTransform*>(transform);
			node->unknown98 = true;
		}
	}

	// FUNCTION: ENGINE 0x1055CA70
	void WebOfIntrigueManager::NodeLocatorLoaded(int nodeID)
	{
		Node* node = GetNode(FindNodeIndex(nodeID));
		if (node != 0)
		{
			node->unknown98 = false;
		}
	}

	// FUNCTION: ENGINE 0x1055CC40
	WebOfIntrigueManager::Node* WebOfIntrigueManager::FindNode(engine::GameObjectHandle handle)
	{
		Node** at = nodeListBegin;
		while (at != nodeListEnd)
		{
			Node* node = *at;
			if (node != 0 && *(int*)&node->target == *(int*)&handle)
			{
				return node;
			}
			at++;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055B9E0
	WebOfIntrigueManager::Node* WebOfIntrigueManager::GetNode(int index)
	{
		if (index >= 0 && index < nodeCount)
		{
			return nodes[index];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055BA10
	WOIEpisode* WebOfIntrigueManager::GetVisibleNode(int index)
	{
		if (index >= 0 && index < visibleCount)
		{
			return visible[index];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055BA40
	int WebOfIntrigueManager::GetVisibleCount()
	{
		return visibleCount;
	}

	// FUNCTION: ENGINE 0x1055BA50
	int WebOfIntrigueManager::GetNodeCount()
	{
		return nodeCount;
	}

	// FUNCTION: ENGINE 0x1055BA60
	int WebOfIntrigueManager::FindNodeIndex(int nodeID)
	{
		if (nodeID != -1)
		{
			for (int i = 0; i < nodeCount; i++)
			{
				if (nodes[i]->id == nodeID)
				{
					return i;
				}
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1055BAB0
	float WebOfIntrigueManager::GetVisibleProgress(int index)
	{
		if (index >= 0 && index < visibleCount)
		{
			WOIEpisode* episode = visible[index];
			return (float)(episode->done / episode->total);
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1055BAF0
	int WebOfIntrigueManager::GetVisibleNodeID(int index)
	{
		if (index >= 0 && index < visibleCount)
		{
			return visible[index]->done;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055BB20
	int WebOfIntrigueManager::GetVisibleNodeTotal(int index)
	{
		if (index >= 0 && index < visibleCount)
		{
			return visible[index]->total;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1055BB50
	int WebOfIntrigueManager::GetNodeEpisode(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->episode;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1055BC40
	int WebOfIntrigueManager::GetNodeID(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->id;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1055BC60
	int WebOfIntrigueManager::GetNodeKinds(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->kinds;
		}
		return 3;
	}

	// FUNCTION: ENGINE 0x1055BC90
	float WebOfIntrigueManager::GetNodeX(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->x;
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1055BCB0
	float WebOfIntrigueManager::GetNodeY(int index)
	{
		Node* node = GetNode(index);
		if (node != 0)
		{
			return node->y;
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1055B900
	void WebOfIntrigueManager::AddVisible(WOIEpisode* episode)
	{
		if (visibleCount < 10)
		{
			visible[visibleCount] = episode;
			visibleCount++;
		}
		if (visibleCount == 1)
		{
			selectedEpisode = 0;
		}
	}

	// FUNCTION: ENGINE 0x1055BB70
	void WebOfIntrigueManager::SelectNode(Node* node)
	{
		selectedIndex = FindNodeIndex(node->id);
		selectedEpisode = node->episode;
	}

	// FUNCTION: ENGINE 0x1055BE90
	void WebOfIntrigueManager::SetUnknown46C()
	{
		unknown46C = true;
	}

	// FUNCTION: ENGINE 0x1055BEA0
	void WebOfIntrigueManager::SetUnknown458(float value, bool force)
	{
		if (unknown458 <= 0.0f || force)
		{
			unknown458 = value;
		}
	}

	// FUNCTION: ENGINE 0x1055BED0
	void WebOfIntrigueManager::SetUnknown454(float value)
	{
		unknown454 = value;
	}

	// FUNCTION: ENGINE 0x1055BEF0
	void WebOfIntrigueManager::ClearUnknown458()
	{
		unknown458 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1055C010
	bool WebOfIntrigueManager::GetUnknown45C()
	{
		return unknown45C;
	}

	// FUNCTION: ENGINE 0x1055CAD0
	int WebOfIntrigueManager::CountNodeLinks(int index)
	{
		Node* node = GetNode(index);
		unsigned int count = 0;
		if (node != 0)
		{
			const int* link = node->links;
			do
			{
				if (*link == -1)
				{
					return count;
				}
				count++;
				link++;
			}
			while (count < 6);
			count = 6;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1055CB10
	int WebOfIntrigueManager::GetNodeLink(int index, unsigned int place)
	{
		Node* node = GetNode(index);
		if (node == 0 || place > 5)
		{
			return -1;
		}
		int link = node->links[place];
		if (link == -1)
		{
			return -1;
		}
		return link;
	}

	// FUNCTION: ENGINE 0x1055B950
	void WebOfIntrigueManager::ResetEpisodeStates(int episode)
	{
		Node** at = nodes;
		int count = 0xff;
		do
		{
			if (*at != 0 && (*at)->episode == episode)
			{
				unsigned int state = (*at)->GetState() & 0xffffff7f;
				(*at)->SetState(state, false);
			}
			at++;
			count--;
		}
		while (count != 0);
		if (episode > unknown464)
		{
			unknown464 = episode;
		}
	}

	// FUNCTION: ENGINE 0x1055BDA0
	void WebOfIntrigueManager::StartNodeState(int nodeID)
	{
		Node* node = GetNode(FindNodeIndex(nodeID));
		if (node != 0)
		{
			unsigned int state = node->GetState();
			if ((state & 1) != 0)
			{
				node->SetState((state & 0x7e000080) | 0x42, false);
			}
		}
	}

	// FUNCTION: ENGINE 0x1055BDF0
	void WebOfIntrigueManager::ClearNodeFlag40(int nodeID)
	{
		Node* node = GetNode(FindNodeIndex(nodeID));
		if (node != 0)
		{
			unsigned int state = node->GetState();
			if ((state & 0x40) != 0)
			{
				node->SetState(state & 0xffffffbf, false);
			}
		}
	}

	// FUNCTION: ENGINE 0x1055BE40
	void WebOfIntrigueManager::ClearNodeFlag20(int nodeID)
	{
		Node* node = GetNode(FindNodeIndex(nodeID));
		if (node != 0)
		{
			unsigned int state = node->GetState();
			if ((state & 0x20) != 0)
			{
				node->SetState((state & 0x7e000000) | 0x10, false);
			}
		}
	}

	// FUNCTION: ENGINE 0x1055CAA0
	void WebOfIntrigueManager::SelectNodeByID(int nodeID)
	{
		SelectNode(GetNode(FindNodeIndex(nodeID)));
	}

	// FUNCTION: ENGINE 0x1055CB40
	bool WebOfIntrigueManager::GetNodeLinkFlag(int index, unsigned int place)
	{
		Node* node = GetNode(index);
		bool result = false;
		if (node != 0)
		{
			result = node->GetLinkFlag(place);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1055CB70
	void WebOfIntrigueManager::LinkNodes(int firstID, int secondID)
	{
		Node* first = GetNode(FindNodeIndex(firstID));
		Node* second = GetNode(FindNodeIndex(secondID));
		if (first != 0 && second != 0)
		{
			first->MarkLink(secondID);
			second->MarkLink(firstID);
		}
	}

	// FUNCTION: ENGINE 0x1055BF00
	void WebOfIntrigueManager::OnNodeTargeted(Node* node)
	{
		bool done = GetVisibleProgress(node->episode) >= 1.0f;
		unknown468 = 1;
		if (done)
		{
			unknown468 = 2;
		}
		SelectNode(node);
	}

	// FUNCTION: ENGINE 0x1055BF60
	void WebOfIntrigueManager::SendTargetConsumed()
	{
		int nodeEpisode = 0;
		int episode = 0;
		switch (unknown468)
		{
		case 2:
			nodeEpisode = GetNode(FindNodeIndex(unknown460))->episode + 1;
		case 1:
			episode = unknown464 + 1;
			break;
		}
		bool allDone = AreAllEpisodesDone();
		WOITargetConsumedScenarioMessage message;
		message.NodeCompletedInEpisode = episode;
		message.EpisodeComplete = nodeEpisode;
		message.WOIComplete = allDone;
		engine::SendMessage(&message, &engine::gScenario6);
		unknown468 = 0;
	}

	// FUNCTION: ENGINE 0x1055C020
	bool WebOfIntrigueManager::HasOpenNode()
	{
		if (AreAllEpisodesDone())
		{
			return false;
		}
		for (int i = 0; i < nodeCount; i++)
		{
			if (nodes[i] != 0)
			{
				int state = nodes[i]->GetState();
				if (nodes[i]->kinds != 1 && (state & 2) > 0 && !((state & 0x80) != 0))
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1055C090
	int WebOfIntrigueManager::FindOpenNodeID(unsigned int kinds)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			unsigned int state = nodes[i]->GetState();
			if ((state & 0x91) == 0 && (nodes[i]->flags & 0x100) == 0 && (nodes[i]->kinds & kinds) != 0)
			{
				return nodes[i]->id;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1055C260
	void WebOfIntrigueManager::CountFinishedNodes()
	{
		int highest = -1;
		Node** at = nodes;
		int count = 0xff;
		do
		{
			if (*at != 0)
			{
				int state = (*at)->GetState();
				if ((state & 0x10) != 0)
				{
					WOIEpisode* episode = GetVisibleNode((*at)->episode);
					if (episode != 0)
					{
						episode->done++;
					}
				}
				if (!((state & 0x80) != 0) && (*at)->episode > highest)
				{
					highest = (*at)->episode;
				}
			}
			at++;
			count--;
		}
		while (count != 0);
		if (highest > unknown464)
		{
			unknown464 = highest;
		}
	}

	// FUNCTION: ENGINE 0x1055C2E0
	void WebOfIntrigueManager::ResetAllNodes()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			if (nodes[i] != 0)
			{
				nodes[i]->SetState(0x10, false);
			}
		}
		for (int i = 0; i < visibleCount; i++)
		{
			if (visible[i] != 0)
			{
				visible[i]->ResetDone();
			}
		}
		CountFinishedNodes();
	}

	// FUNCTION: ENGINE 0x1055C360
	void WebOfIntrigueManager::SetAllNodesOpen(int unused)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			if (nodes[i] != 0)
			{
				nodes[i]->SetState(2, false);
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1055C4F0
// FUNCTION: ENGINE 0x1055C570
// FUNCTION: ENGINE 0x1055C670
// FUNCTION: ENGINE 0x1055C6A0
// FUNCTION: ENGINE 0x1055C6E0
// FUNCTION: ENGINE 0x1055CD80
// FUNCTION: ENGINE 0x1055CDC0
// FUNCTION: ENGINE 0x1055CE00
// FUNCTION: ENGINE 0x1055CE40
// FUNCTION: ENGINE 0x1055CE80
// FUNCTION: ENGINE 0x1055CEC0
// FUNCTION: ENGINE 0x1055CF00
// FUNCTION: ENGINE 0x1055CF40
// FUNCTION: ENGINE 0x1055CF50
// FUNCTION: ENGINE 0x1055CF70
// FUNCTION: ENGINE 0x1055CF90
// FUNCTION: ENGINE 0x1055CFB0
// FUNCTION: ENGINE 0x1055CFD0
