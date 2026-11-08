#include "code/proto/npcanimation.h"
#include "code/choreo/puppet.h"
#include "code/core/refptr.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/animation.h"

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x104769C0
	content::ClassInfo* NPCAnimation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCAnimation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10476A00
	content::ClassInfo* NPCAnimationList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCAnimationList";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10478E90
	content::ClassInfo* NPCDrawable::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCDrawable";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10476A40
	bool NPCAnimation::Slot5()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10476A80
	pure3d::Pose* NPCAnimation::GetPuppetPose() const
	{
		return puppet->mPoseObject;
	}

	// FUNCTION: ENGINE 0x10476A90
	pure3d::Pose* NPCAnimation::GetPose() const
	{
		return pose;
	}

	// FUNCTION: ENGINE 0x10476AA0
	choreo::Puppet* NPCAnimation::GetPuppet() const
	{
		return puppet;
	}

	// FUNCTION: ENGINE 0x10476AB0
	float NPCAnimation::GetLocomotionSpeed() const
	{
		return locomotionSpeed;
	}

	// FUNCTION: ENGINE 0x10476A50
	void NPCAnimation::UpdatePose(float dt)
	{
		pure3d::Pose* source = puppet->mPoseObject;
		pure3d::Pose* destination = pose;
		if (source != 0 && destination != 0)
		{
			destination->CopyStateFrom(source);
		}
	}

	// FUNCTION: ENGINE 0x104770B0
	// NONMATCHING: the engine computes the address of the puppet handle after the store of the reference count (91.7 %)
#ifdef NONMATCHING
	NPCAnimation::NPCAnimation() : animation(0), puppet(0), puppetHandle(), driver(0), skeleton(0), startFrame(0.0f),
		locomotionSpeed(0.0f), animationSpeed(1.0f)
	{
	}
#endif

	// FUNCTION: ENGINE 0x10476CB0
	NPCAnimation::~NPCAnimation()
	{
		core::SafeRelease(animation);
		core::SafeRelease(skeleton);
	}

	// FUNCTION: ENGINE 0x10478E20
	// NONMATCHING: the engine computes the address of the animations after the store of the reference count (80.9 %)
#ifdef NONMATCHING
	NPCAnimationList::NPCAnimationList()
	{
	}
#endif

	// FUNCTION: ENGINE 0x10478D80
	NPCAnimationList::~NPCAnimationList()
	{
		int count = animations.Size();
		for (int i = 0; i < count; i++)
		{
			core::SafeRelease(animations[i]);
		}
	}

	// FUNCTION: ENGINE 0x10478F20
	NPCDrawable::NPCDrawable() : drawable(0), animationList(0)
	{
	}

	// FUNCTION: ENGINE 0x10478F40
	NPCDrawable::~NPCDrawable()
	{
		core::SafeRelease((core::IRefCount*&)drawable);
		core::SafeRelease(animationList);
	}

	// FUNCTION: ENGINE 0x10478F70
	int NPCDrawable::PickAnimationIndex(int state, unsigned int seed) const
	{
		if (animationList->states[state].IsEmpty())
		{
			return -1;
		}
		return (seed / 7) % animationList->states[state].Size();
	}

	// FUNCTION: ENGINE 0x10479040
	// NONMATCHING: the engine places the return of the animation of the entry behind the return of the first animation (71.9 %)
#ifdef NONMATCHING
	NPCAnimation* NPCDrawable::GetAnimation(int state, unsigned int seed) const
	{
		int pick = PickAnimationIndex(state, seed);
		if (pick >= 0)
		{
			int entry = animationList->states[state][pick];
			if (entry >= 0)
			{
				return animationList->animations[entry];
			}
		}
		return animationList->animations[0];
	}
#endif

	// FUNCTION: ENGINE 0x10478530
	content::MemberList* NPCAnimation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<NPCAnimation, pure3d::Animation>("p"),
				PROTO_OFFSET(NPCAnimation, animation), "animation" },
			{ content::GetReferenceMetaType<NPCAnimation, pure3d::Skeleton>("p"),
				PROTO_OFFSET(NPCAnimation, skeleton), "skeleton" },
			{ content::GetMemberPrimitiveMetaType<NPCAnimation, float, 0>("p"),
				PROTO_OFFSET(NPCAnimation, startFrame), "startFrame" },
			{ content::GetMemberPrimitiveMetaType<NPCAnimation, float, 1>("p"),
				PROTO_OFFSET(NPCAnimation, locomotionSpeed), "locomotionSpeed" },
			{ content::GetMemberPrimitiveMetaType<NPCAnimation, float, 2>("p"),
				PROTO_OFFSET(NPCAnimation, animationSpeed), "animationSpeed" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104786A0
	content::MemberList* NPCAnimationList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 0>(&NPCAnimationList::GetStateWalking,
				&NPCAnimationList::SetStateWalking, "p"), 0, "state_Walking" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 1>(&NPCAnimationList::GetStateWalking1,
				&NPCAnimationList::SetStateWalking1, "p"), 0, "state_Walking1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 2>(&NPCAnimationList::GetStateWalking2,
				&NPCAnimationList::SetStateWalking2, "p"), 0, "state_Walking2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 3>(&NPCAnimationList::GetStateStanding,
				&NPCAnimationList::SetStateStanding, "p"), 0, "state_Standing" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 4>(&NPCAnimationList::GetStateStanding1,
				&NPCAnimationList::SetStateStanding1, "p"), 0, "state_Standing1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 5>(&NPCAnimationList::GetStateStanding2,
				&NPCAnimationList::SetStateStanding2, "p"), 0, "state_Standing2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 6>(&NPCAnimationList::GetStateRunning,
				&NPCAnimationList::SetStateRunning, "p"), 0, "state_Running" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 7>(&NPCAnimationList::GetStateRunning1,
				&NPCAnimationList::SetStateRunning1, "p"), 0, "state_Running1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 8>(&NPCAnimationList::GetStateRunning2,
				&NPCAnimationList::SetStateRunning2, "p"), 0, "state_Running2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 9>(&NPCAnimationList::GetStateFloat,
				&NPCAnimationList::SetStateFloat, "p"), 0, "state_Float" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 10>(&NPCAnimationList::GetStateFloat1,
				&NPCAnimationList::SetStateFloat1, "p"), 0, "state_Float1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 11>(&NPCAnimationList::GetStateFloat2,
				&NPCAnimationList::SetStateFloat2, "p"), 0, "state_Float2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 12>(&NPCAnimationList::GetStateDead,
				&NPCAnimationList::SetStateDead, "p"), 0, "state_Dead" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 13>(&NPCAnimationList::GetStateDead1,
				&NPCAnimationList::SetStateDead1, "p"), 0, "state_Dead1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 14>(&NPCAnimationList::GetStateDead2,
				&NPCAnimationList::SetStateDead2, "p"), 0, "state_Dead2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 15>(&NPCAnimationList::GetStateCower,
				&NPCAnimationList::SetStateCower, "p"), 0, "state_Cower" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 16>(&NPCAnimationList::GetStateCower1,
				&NPCAnimationList::SetStateCower1, "p"), 0, "state_Cower1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 17>(&NPCAnimationList::GetStateCower2,
				&NPCAnimationList::SetStateCower2, "p"), 0, "state_Cower2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 18>(&NPCAnimationList::GetStateLowMoraleWalking,
				&NPCAnimationList::SetStateLowMoraleWalking, "p"), 0, "state_LowMoraleWalking" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 19>(&NPCAnimationList::GetStateLowMoraleWalking1,
				&NPCAnimationList::SetStateLowMoraleWalking1, "p"), 0, "state_LowMoraleWalking1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 20>(&NPCAnimationList::GetStateLowMoraleWalking2,
				&NPCAnimationList::SetStateLowMoraleWalking2, "p"), 0, "state_LowMoraleWalking2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 21>(&NPCAnimationList::GetStateLowMoraleStanding,
				&NPCAnimationList::SetStateLowMoraleStanding, "p"), 0, "state_LowMoraleStanding" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 22>(&NPCAnimationList::GetStateLowMoraleStanding1,
				&NPCAnimationList::SetStateLowMoraleStanding1, "p"), 0, "state_LowMoraleStanding1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 23>(&NPCAnimationList::GetStateLowMoraleStanding2,
				&NPCAnimationList::SetStateLowMoraleStanding2, "p"), 0, "state_LowMoraleStanding2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 24>(&NPCAnimationList::GetStateSpawnDead,
				&NPCAnimationList::SetStateSpawnDead, "p"), 0, "state_SpawnDead" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 25>(&NPCAnimationList::GetStateSpawnDead1,
				&NPCAnimationList::SetStateSpawnDead1, "p"), 0, "state_SpawnDead1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 26>(&NPCAnimationList::GetStateSpawnDead2,
				&NPCAnimationList::SetStateSpawnDead2, "p"), 0, "state_SpawnDead2" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 27>(&NPCAnimationList::GetStateRubbernecking,
				&NPCAnimationList::SetStateRubbernecking, "p"), 0, "state_Rubbernecking" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 28>(&NPCAnimationList::GetStateRubbernecking1,
				&NPCAnimationList::SetStateRubbernecking1, "p"), 0, "state_Rubbernecking1" },
			{ content::GetReferenceMemberMetaType<NPCAnimationList, NPCAnimation, 29>(&NPCAnimationList::GetStateRubbernecking2,
				&NPCAnimationList::SetStateRubbernecking2, "p"), 0, "state_Rubbernecking2" }
		};
		sList.members = sMembers;
		sList.count = 30;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10479150
	content::MemberList* NPCDrawable::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<NPCDrawable, NPCAnimationList>("p"),
				PROTO_OFFSET(NPCDrawable, animationList), "animationList" },
			{ content::GetReferenceMetaType<NPCDrawable, engine::render::DrawableArchetype>("p"),
				PROTO_OFFSET(NPCDrawable, drawable), "drawable" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// The place of an animation in the list (the end of the list when it is not there)
	static inline NPCAnimation** FindAnimation(container::ArrayFixed<NPCAnimation*, 12>& list, NPCAnimation* wanted)
	{
		NPCAnimation** position = list.Begin();
		NPCAnimation** end = list.End();
		while (position != end && *position != wanted)
		{
			position++;
		}
		return position;
	}

	// FUNCTION: ENGINE 0x10477140
	void NPCAnimationList::AddAnimation(int state, NPCAnimation* newAnimation)
	{
		if (newAnimation != 0)
		{
			NPCAnimation** position = FindAnimation(animations, newAnimation);
			if (position != animations.End())
			{
				states[state].PushBack(position - animations.Begin());
				return;
			}
			animations.PushBack(newAnimation);
			states[state].PushBack(animations.Size() - 1);
			newAnimation->AddRef();
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104769A0
// FUNCTION: ENGINE 0x10476AD0
// FUNCTION: ENGINE 0x10476AE0
// FUNCTION: ENGINE 0x10476AF0
// FUNCTION: ENGINE 0x10476B60
// FUNCTION: ENGINE 0x10476B70
// FUNCTION: ENGINE 0x10476C30
// FUNCTION: ENGINE 0x10476EB0
// FUNCTION: ENGINE 0x10476EF0
// FUNCTION: ENGINE 0x10476F30
// FUNCTION: ENGINE 0x10476F70
// FUNCTION: ENGINE 0x10476FB0
// FUNCTION: ENGINE 0x10477010
// FUNCTION: ENGINE 0x10477020
// FUNCTION: ENGINE 0x10477050
// FUNCTION: ENGINE 0x10477070
// FUNCTION: ENGINE 0x10477090
// FUNCTION: ENGINE 0x10477110
// FUNCTION: ENGINE 0x10477250
// FUNCTION: ENGINE 0x104772B0
// FUNCTION: ENGINE 0x10477310
// FUNCTION: ENGINE 0x10477330
// FUNCTION: ENGINE 0x104773C0
// FUNCTION: ENGINE 0x10477450
// FUNCTION: ENGINE 0x104774E0
// FUNCTION: ENGINE 0x10477500
// FUNCTION: ENGINE 0x10477590
// FUNCTION: ENGINE 0x10477620
// FUNCTION: ENGINE 0x104776B0
// FUNCTION: ENGINE 0x104776D0
// FUNCTION: ENGINE 0x10477760
// FUNCTION: ENGINE 0x104777F0
// FUNCTION: ENGINE 0x10477880
// FUNCTION: ENGINE 0x104778A0
// FUNCTION: ENGINE 0x10477930
// FUNCTION: ENGINE 0x104779C0
// FUNCTION: ENGINE 0x10477A50
// FUNCTION: ENGINE 0x10477A70
// FUNCTION: ENGINE 0x10477B00
// FUNCTION: ENGINE 0x10477B90
// FUNCTION: ENGINE 0x10477C20
// FUNCTION: ENGINE 0x10477C40
// FUNCTION: ENGINE 0x10477CD0
// FUNCTION: ENGINE 0x10477D60
// FUNCTION: ENGINE 0x10477DF0
// FUNCTION: ENGINE 0x10477E10
// FUNCTION: ENGINE 0x10477EA0
// FUNCTION: ENGINE 0x10477F30
// FUNCTION: ENGINE 0x10477FC0
// FUNCTION: ENGINE 0x10477FE0
// FUNCTION: ENGINE 0x10478070
// FUNCTION: ENGINE 0x10478100
// FUNCTION: ENGINE 0x10478190
// FUNCTION: ENGINE 0x104781B0
// FUNCTION: ENGINE 0x10478240
// FUNCTION: ENGINE 0x104782D0
// FUNCTION: ENGINE 0x10478360
// FUNCTION: ENGINE 0x10478380
// FUNCTION: ENGINE 0x10478410
// FUNCTION: ENGINE 0x104784A0
// FUNCTION: ENGINE 0x10478E60
// FUNCTION: ENGINE 0x10478EF0
// FUNCTION: ENGINE 0x10478FD0
// FUNCTION: ENGINE 0x10478FE0
// FUNCTION: ENGINE 0x10479090
// FUNCTION: ENGINE 0x104790F0
// FUNCTION: ENGINE 0x10478ED0
// FUNCTION: ENGINE 0x10478F00
// FUNCTION: ENGINE 0x10479010
