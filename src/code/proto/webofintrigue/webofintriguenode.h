// A node of the web of intrigue (RTTI proto::WebOfIntrigueManager::Node); the manager's unit and the fight actions that
// look a node up read it.
#ifndef PROTO_WEBOFINTRIGUE_WEBOFINTRIGUENODE_H
#define PROTO_WEBOFINTRIGUE_WEBOFINTRIGUENODE_H

#include "code/proto/webofintrigue/webofintriguemanager.h"
#include "code/engine/nis/nis.h"

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
}

#endif
