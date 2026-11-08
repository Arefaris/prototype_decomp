// The branches of the fight tree that run a non-interactive sequence (engine::NISNode, engine::NISRootNode; code/engine/nis/
// nisnodes.cpp; the file name is a guess, the unit starts at 0x108A71B0 and has no assert path). Names are guesses unless the
// RTTI gives them.
#include "code/engine/nis/nisnodes.h"
#include "code/engine/fight/nisspawnaction.h"
#include "code/engine/system/streampackage.h"

namespace engine
{
	// The texts the two branch kinds register their factories under (0x111D5044 / 0x111D5048)
	extern const char* const gNISNodeText;
	extern const char* const gNISRootNodeText;

	// GLOBAL: ENGINE 0x11318138
	fight::Property** gNISNodeProperties;
	// GLOBAL: ENGINE 0x1131813C
	fight::Property** gNISRootNodeProperties;

	// ---- engine::NISNode ---------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108A71E0
	bool NISNode::SetStartTime(float value)
	{
		startTime = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108A71D0
	float NISNode::GetStartTime() const
	{
		return startTime;
	}

	// FUNCTION: ENGINE 0x108A72D0
	fight::Property* NISNode::GetProperty(int index)
	{
		return gNISNodeProperties[index];
	}

	// FUNCTION: ENGINE 0x108A72E0
	void NISNode::ClearProperties()
	{
		fight::FreePropertyList(&gNISNodeProperties);
	}

	// FUNCTION: ENGINE 0x108A7310
	NISNode::NISNode()
		: package(0), startTime(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108A7920
	// NONMATCHING: shrink-wrap
#ifdef NONMATCHING
	void NISNode::RegisterProperties()
	{
		if (gNISNodeProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloat<NISNode>("startTime", &NISNode::SetStartTime);
			properties[0] = property;
			property = new fight::PropertyConditionGroup<NISNode>("conditions", &NISNode::GetConditions);
			properties[1] = property;
			property = new fight::PropertyTrackGroup<NISNode>("tracks", &NISNode::GetTracks);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gNISNodeProperties);
		}
	}
#endif

	// FUNCTION: ENGINE 0x108A7CA0
	StreamPackage* __fastcall GetNISNodeStreamPackage(fight::Branch* node)
	{
		NISNode* nisNode = (NISNode*)node;
		if (nisNode->package == 0)
		{
			nisNode->package = content::gRootInventory->Find<StreamPackage>(nisNode->name);
		}
		return nisNode->package;
	}

	// ---- engine::NISRootNode -----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108A7240
	bool NISRootNode::SetDisableSimulation(bool value)
	{
		disableSimulation = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108A7250
	bool NISRootNode::SetAutoUnload(bool value)
	{
		autoUnload = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108A7260
	fight::BranchHolder* NISRootNode::GetEaseIn()
	{
		return &easeIn;
	}

	// FUNCTION: ENGINE 0x108A7270
	fight::BranchHolder* NISRootNode::GetEaseOut()
	{
		return &easeOut;
	}

	// FUNCTION: ENGINE 0x108A7280
	fight::BranchHolder* NISRootNode::GetPostNIS()
	{
		return &postNIS;
	}

	// FUNCTION: ENGINE 0x108A7290
	bool NISRootNode::SetEaseOutBegin(float value)
	{
		easeOutBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108A72B0
	bool NISRootNode::SetEaseOutOffset(float value)
	{
		easeOutOffset = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108A72F0
	fight::Property* NISRootNode::GetProperty(int index)
	{
		return gNISRootNodeProperties[index];
	}

	// FUNCTION: ENGINE 0x108A7300
	void NISRootNode::ClearProperties()
	{
		fight::FreePropertyList(&gNISRootNodeProperties);
	}

	// FUNCTION: ENGINE 0x108A7340
	NISRootNode::NISRootNode()
		: soundTrack(0), easeIn(0), easeOut(0), easeOutBegin(0.0f), easeOutOffset(-0.6667f), postNIS(0), unknownB8(0),
		disableSimulation(true), autoUnload(true)
	{
	}

	// FUNCTION: ENGINE 0x108A73C0
	NISRootNode::~NISRootNode()
	{
		if (soundTrack != 0)
		{
			delete[] soundTrack;
		}
	}

	// FUNCTION: ENGINE 0x108A7410
	bool NISRootNode::SetSoundTrack(const char* value)
	{
		soundTrack = fight::ReplaceString(soundTrack, value);
		return true;
	}

	// FUNCTION: ENGINE 0x108A7430
	bool NISRootNode::Slot11(fight::Sequencer* sequencer, void* params, int a)
	{
		return sequencer->SetPending(this, (int)sequencer, (core::IRefCount*)params, a);
	}

	// FUNCTION: ENGINE 0x108A7A10
	// NONMATCHING: shrink-wrap
#ifdef NONMATCHING
	void NISRootNode::RegisterProperties()
	{
		if (gNISRootNodeProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyString<NISRootNode>("soundTrack", &NISRootNode::SetSoundTrack);
			properties[0] = property;
			property = new fight::PropertyBranch<NISRootNode>("easeIn", &NISRootNode::GetEaseIn);
			properties[1] = property;
			property = new fight::PropertyBranch<NISRootNode>("easeOut", &NISRootNode::GetEaseOut);
			properties[2] = property;
			property = new fight::PropertyFloat<NISRootNode>("easeOutBegin", &NISRootNode::SetEaseOutBegin);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<NISRootNode>("easeOutOffset", &NISRootNode::SetEaseOutOffset);
			properties[4] = property;
			property = new fight::PropertyBool<NISRootNode>("disableSimulation", &NISRootNode::SetDisableSimulation);
			properties[5] = property;
			property = new fight::PropertyBranch<NISRootNode>("postNIS", &NISRootNode::GetPostNIS);
			properties[6] = property;
			property = new fight::PropertyBool<NISRootNode>("autoUnload", &NISRootNode::SetAutoUnload);
			properties[7] = property;
			property = new fight::PropertyConditionGroup<NISNode>("conditions", &NISNode::GetConditions);
			properties[8] = property;
			property = new fight::PropertyTrackGroup<NISNode>("tracks", &NISNode::GetTracks);
			properties[9] = property;
			fight::RegisterPropertyList(properties, &gNISRootNodeProperties);
		}
	}
#endif

	// ---- the properties and factories ---------------------------------------------------------------------------------

	template class fight::PropertyFloat<NISNode>;
	template class fight::PropertyConditionGroup<NISNode>;
	template class fight::PropertyTrackGroup<NISNode>;
	template class fight::PropertyString<NISRootNode>;
	template class fight::PropertyBranch<NISRootNode>;
	template class fight::PropertyFloat<NISRootNode>;
	template class fight::PropertyFloatConstRange<NISRootNode>;
	template class fight::PropertyBool<NISRootNode>;
	template class fight::BranchFactoryTemplate<NISNode>;
	template class fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISNode> >;
	template class fight::BranchFactoryTemplate<NISRootNode>;
	template class fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISRootNode> >;

	// FUNCTION: ENGINE 0x108A78E0
	fight::BranchFactory* CreateNISNodeBranchFactory(const char* name)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISNode> > caster;
		return fight::FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108A7900
	fight::BranchFactory* CreateNISRootNodeBranchFactory(const char* name)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISRootNode> > caster;
		return fight::FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108A7C70
	void RegisterNISNodeBranchFactory(fight::TrackRegistry* registry)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISNode> > caster;
		registry->AddFactory(fight::FindBranchFactory(gNISNodeText, &caster));
	}

	// FUNCTION: ENGINE 0x108A7DA0
	void RegisterNISRootNodeBranchFactory(fight::TrackRegistry* registry)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<NISRootNode> > caster;
		registry->AddFactory(fight::FindBranchFactory(gNISRootNodeText, &caster));
	}
}

// Kept copies (template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108A74C0
// FUNCTION: ENGINE 0x108A74D0
// FUNCTION: ENGINE 0x108A7500
// FUNCTION: ENGINE 0x108A7510
// FUNCTION: ENGINE 0x108A7540
// FUNCTION: ENGINE 0x108A7570
// FUNCTION: ENGINE 0x108A75B0
// FUNCTION: ENGINE 0x108A75C0
// FUNCTION: ENGINE 0x108A75F0
// FUNCTION: ENGINE 0x108A7620
// FUNCTION: ENGINE 0x108A7650
// FUNCTION: ENGINE 0x108A7680
// FUNCTION: ENGINE 0x108A76B0
// FUNCTION: ENGINE 0x108A76F0
// FUNCTION: ENGINE 0x108A7700
// FUNCTION: ENGINE 0x108A7730
// FUNCTION: ENGINE 0x108A7760
// FUNCTION: ENGINE 0x108A7790
// FUNCTION: ENGINE 0x108A77D0
// FUNCTION: ENGINE 0x108A77E0
// FUNCTION: ENGINE 0x108A7810
// FUNCTION: ENGINE 0x108A7850
// FUNCTION: ENGINE 0x108A7860
// FUNCTION: ENGINE 0x108A7890
// FUNCTION: ENGINE 0x108A78D0
// FUNCTION: ENGINE 0x108A7FD0
// FUNCTION: ENGINE 0x108A8010
// FUNCTION: ENGINE 0x108A8030
// FUNCTION: ENGINE 0x108A8080
// FUNCTION: ENGINE 0x108A80C0
// FUNCTION: ENGINE 0x108A80E0
// FUNCTION: ENGINE 0x108A8130
// FUNCTION: ENGINE 0x108A8180
