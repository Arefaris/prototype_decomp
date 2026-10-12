// engine::StreamTrigger (RTTI and reflection names): a volume of the world (a bounding box, refined by convex hulls of
// planes) that makes the stream manager load packages; it names its neighbouring triggers and its packages as
// ';'-separated lists that are resolved after loading. engine::StreamTriggerHull and engine::StreamPackage are other
// units' classes. Unit 0x108352B0 - 0x10836640 (no assert path; the directory and file name are guesses). The
// reflected member names are original; others are guesses.
#ifndef ENGINE_SYSTEM_STREAMTRIGGER_H
#define ENGINE_SYSTEM_STREAMTRIGGER_H

#include "code/container/arraydynamicstatic.h"
#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/system/tagset.h"
#include "code/math/aabb.h"
#include "code/math/plane.h"

namespace engine
{
	class StreamTrigger;
	class StreamPackage;

	// One convex hull of a trigger: the point is inside when it is behind every plane (unit 0x108C6xxx)
	class StreamTriggerHull
	{
	public:
		// 0x108C7030
		StreamTriggerHull();

		// 0x108C6960 / 0x108C6F00
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x108C6A10
		bool Contains(const math::Vector& point) const;

		container::ArrayDynamic<math::Plane, container::AllocatorCoreStatic<12, 16> > planes;
	};

	// A package of the stream manager (another unit); only its tags are used here
	class StreamPackage
	{
	public:
		unsigned char unknown0[0x30];
		TagSet tags;
	};

	// The stream manager's registry (another unit, 0x1082xxxx; names guessed)
	void RegisterStreamTrigger(StreamTrigger* trigger);
	void UnregisterStreamTrigger(StreamTrigger* trigger);
	StreamTrigger* FindStreamTrigger(const core::Name<core::CaseSensitiveKey>& name);
	StreamPackage* FindStreamPackage(const core::Name<core::CaseSensitiveKey>& name);

	class StreamTrigger : public content::MetaLoadObject
	{
	public:
		typedef container::AllocatorCoreStatic<12, 16> Allocator;
		typedef container::StringDynamic<Allocator> String;

		StreamTrigger();
		explicit StreamTrigger(const content::ObjectName& newName);
		virtual ~StreamTrigger();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Slot 3: keeps the value in a static (meaning unknown)
		virtual void Slot3(int value);
		// Slot 4: leaves the stream manager and drops the resolved lists
		virtual bool IsReady();
		// Slot 5: joins the stream manager
		virtual bool Slot5();
		virtual void SetName(const content::ObjectName& newName);

		// The reflected accessors of neighbours, packages and tags
		const char* GetNeighbours();
		void SetNeighbours(const char* text);
		const char* GetPackages();
		void SetPackages(const char* text);
		const char* GetTags();
		void SetTags(const char* text);

		// Resolves the neighbour and package names into the triggers and packages they name
		void ResolveLinks();
		// Replaces the neighbours with the count triggers of list
		void SetNeighbourTriggers(StreamTrigger** list, unsigned int count);
		// True when point lies in the bounding box grown by margin, or (with hulls) in one of the hulls
		bool Contains(const math::Vector& point, float margin);
		// The first package whose tags intersect tags
		StreamPackage* FindPackage(const TagSet& tags);

		static int sUnknown;

		content::ObjectName name;
		String* neighbours;
		container::ArrayDynamic<StreamTrigger*, Allocator>* neighbourTriggers;
		String* packages;
		container::ArrayDynamic<StreamPackage*, Allocator>* packageList;
		container::ArrayDynamic<StreamTriggerHull, Allocator> hulls;
		TagSet tags;
		math::AABB boundingBox;
	};
}

#endif
