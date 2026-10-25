// engine::RenderBehaviour: see the header.
#include "code/engine/render/renderbehaviour.h"

#include "code/core/heap.h"
#include "code/content/namedreference.h"
#include "code/core/refptr.h"
#include "code/engine/attributemessage.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/matrix.h"
#include "code/pure3d/pose.h"
#include <math.h>

namespace pure3d
{
	class PoseAnimationController;

	// 0x1005E540 / 0x1007F230 (the core region's copies): take a reference / let go of one and clear the pointer
	void AssignCoreRef(core::IRefCount*& pointer, core::IRefCount* object);
	void ReleaseCoreRef(core::IRefCount*& pointer);
}

namespace proto
{
	// 0x112834C8 ("pose") and 0x112834D0 ("drawableObject")
	extern content::ObjectName gDrawableAttributeName;
	extern content::ObjectName gDrawableHandleAttributeName;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}

	namespace camera
	{
		float MinOf(float a, float b);
	}

	namespace render
	{
		// A source the drawables are made from (the archetype is one); 0x10825960 makes a pose of its drawable
		class SourceDrawable
		{
		public:
			pure3d::Pose* CreatePoseInstance();
		};
	}

	// The names of the attributes the behaviour reads (0x112834A0, 0x112834D8, 0x11283548; "drawableName", "asleep",
	// "poseAwake") and the ones it publishes (0x112834C8 "pose", 0x112834D0 "drawableObject")
	extern content::ObjectName gDrawableNameName;
	extern content::ObjectName gAsleepName;
	extern content::ObjectName gPoseAwakeName;
	extern content::ObjectName gPoseAnimationControllerName;
	extern content::ObjectName gScaleName;
	extern content::ObjectName gTransformName;
	// 0x102D9810 (another unit): whether every component of a vector is within a hair of the other's
	bool IsVectorNear(const math::Vector& a, const math::Vector& b);
	// Whether the drawables are made when their package has loaded, not at once (0x11315B60; name guessed)
	extern bool gRenderSourcesDeferred;
	extern int gAttributeHeap;

	// The messages the behaviour is told, as the code reads them (names guessed)
	struct DrawableMessage : public Message
	{
		render::Drawable drawable;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	struct FloatMessage : public Message
	{
		float value;  // +0xC
	};

	struct BoolMessage : public Message
	{
		bool value;  // +0xC
	};

	struct SegmentMessage : public Message
	{
		unsigned char unknownC[4];
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		bool visible;  // +0x18
	};

	struct SegmentsMessage : public Message
	{
		const DrawableSegmentVisibility* visibilities;  // +0xC
		unsigned int count;  // +0x10
	};

	struct NameMessage : public Message
	{
		unsigned char unknownC[4];
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	struct PlayAnimationMessage : public Message
	{
		pure3d::Animation* animation;  // +0xC
		float speed;  // +0x10
		float frame;  // +0x14
		float start;  // +0x18
		float end;  // +0x1C
		pure3d::Animation::CycleMode mode;  // +0x20
	};

	struct PlayMessage : public Message
	{
		float start;  // +0xC
		float end;  // +0x10
		float speed;  // +0x14
		pure3d::Animation::CycleMode mode;  // +0x18
		unsigned int cycles;  // +0x1C
	};

	struct DeformRegionMessage : public Message
	{
		pure3d::VertexDeformRegion* region;  // +0xC
	};

	// FUNCTION: ENGINE 0x10862350
	content::ClassInfo* RenderBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "RenderBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10862390
	void RenderBehaviour::SetSourcesDeferred(bool deferred)
	{
		gRenderSourcesDeferred = deferred;
	}

	// FUNCTION: ENGINE 0x108623A0
	bool RenderBehaviour::GetSourcesDeferred()
	{
		return gRenderSourcesDeferred;
	}

	// FUNCTION: ENGINE 0x108623B0
	void RenderBehaviour::Slot1()
	{
		Listen2(0x200, true);
	}

	// FUNCTION: ENGINE 0x108623C0
	bool RenderBehaviour::IsScaleChanging() const
	{
		return driving::gOne != scaleState.current || driving::gOne != scaleState.target;
	}

	// FUNCTION: ENGINE 0x108623F0
	void RenderBehaviour::WakeUpdate()
	{
		if (!Query2(0x200))
		{
			Listen2(0x200, true);
		}
	}

	// FUNCTION: ENGINE 0x10862420
	void RenderBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		drawable.SetRegistered(active);
	}

	// FUNCTION: ENGINE 0x10862440
	render::DrawableArchetype* RenderBehaviour::GetSource() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10862450
	const core::Name<core::CaseSensitiveKey>* RenderBehaviour::GetSourceName() const
	{
		return &sourceName;
	}

	// FUNCTION: ENGINE 0x10862460
	float RenderBehaviour::GetEffectiveScale() const
	{
		return scaleState.factor * scaleState.current;
	}

	// FUNCTION: ENGINE 0x10862570
	void RenderBehaviour::UpdateScale(float dt)
	{
		if (IsScaleChanging() == true)
		{
			float old = scaleState.current;
			float target = scaleState.target;
			if (scaleState.current > target)
			{
				float moved = scaleState.current - dt * 4.0f;
				if (moved < target)
				{
					moved = target;
				}
				scaleState.current = moved;
			}
			else if (scaleState.current < target)
			{
				float moved = dt * 4.0f + scaleState.current;
				if (!(target > moved))
				{
					moved = target;
				}
				scaleState.current = moved;
			}
			scaleState.target = driving::gOne;
			if (old != scaleState.current)
			{
				drawable.SetUnknownBC(GetEffectiveScale());
			}
		}
	}

	// FUNCTION: ENGINE 0x10862600
	void RenderBehaviour::SetPose(pure3d::Pose* pose)
	{
		if (pose != 0)
		{
			pose->AddRef();
		}
		if (poseAttribute != 0)
		{
			pure3d::AssignCoreRef((core::IRefCount*&)poseAttribute->value, pose);
			if (pose != 0)
			{
				pure3d::PoseData* data = &poseAttribute->value->mData;
				data->mFlags &= 0xfb;
				AttributeUpdatedMessage message(proto::gDrawableAttributeName);
				owner->SendMessage(&message);
			}
		}
		if (pose != 0)
		{
			pose->Release();
		}
	}

	// FUNCTION: ENGINE 0x10862A60
	void RenderBehaviour::ReleaseDrawable()
	{
		BaseAttribute* attribute = owner->FindAttribute(proto::gDrawableAttributeName);
		if (attribute != 0)
		{
			pure3d::ReleaseCoreRef((core::IRefCount*&)static_cast<Attribute<pure3d::Pose*>*>(attribute)->value);
		}
		render::Drawable::Destroy(&drawable, 0);
		core::SafeRelease(source);
	}

	// The writers of the two attribute types the behaviour reads and writes are expanded where they are used
	template<> inline AttributeWriter<render::Drawable> GameObject::GetAttributeWriter<render::Drawable>(
		const content::ObjectName& name)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			render::Drawable* value = &static_cast<Attribute<render::Drawable>*>(attribute)->Get();
			return AttributeWriter<render::Drawable>(value, name, this);
		}
		return AttributeWriter<render::Drawable>();
	}

	template<> inline AttributeWriter<core::Name<core::CaseSensitiveKey> >
		GameObject::GetAttributeWriter<core::Name<core::CaseSensitiveKey> >(const content::ObjectName& name)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			core::Name<core::CaseSensitiveKey>* value =
				&static_cast<Attribute<core::Name<core::CaseSensitiveKey> >*>(attribute)->Get();
			return AttributeWriter<core::Name<core::CaseSensitiveKey> >(value, name, this);
		}
		return AttributeWriter<core::Name<core::CaseSensitiveKey> >();
	}

	// The handle an attribute of drawables starts with: no drawable (a function-local static, 0x11315B98)
	static inline const render::Drawable& GetNoDrawable()
	{
		static render::Drawable sNone;
		return sNone;
	}

	// 0x10862BA0 (the engine keeps this instance in the unit): the handle is the empty one
	template<> Attribute<render::Drawable>::Attribute() : ConstAttribute<render::Drawable>(GetNoDrawable())
	{
	}

	// FUNCTION: ENGINE 0x10862BD0
	template<> render::Drawable& Attribute<render::Drawable>::Get()
	{
		return value;
	}

	// The drawable handle attribute the behaviour publishes, made when the object has none: while the object is being
	// constructed it goes into the static list, else into the dynamic one (the engine keeps this instance in the unit)
	// FUNCTION: ENGINE 0x10862E40
	template<> Attribute<render::Drawable>* GameObject::SetAttributeAndGet<render::Drawable>(
		const content::ObjectName& name, const render::Drawable& value, bool overwrite)
	{
		Attribute<render::Drawable>* attribute = (Attribute<render::Drawable>*)FindAttribute(name);
		if (attribute == 0)
		{
			if (this == GetConstructingObject())
			{
				core::HeapScope scope(GetConstructionHeap());
				attribute = new Attribute<render::Drawable>();
				attribute->Get() = value;
				AddAttribute(name, attribute);
			}
			else
			{
				core::HeapScope scope(gAttributeHeap);
				attribute = new Attribute<render::Drawable>();
				attribute->Get() = value;
				if (!AddDynamicAttribute(name, attribute))
				{
					delete attribute;
					return 0;
				}
			}
		}
		else if (overwrite)
		{
			attribute->Get() = value;
		}
		return attribute;
	}

	// FUNCTION: ENGINE 0x10862C10
	RenderBehaviour::~RenderBehaviour()
	{
		ReleaseDrawable();
	}

	// FUNCTION: ENGINE 0x10862C30
	void RenderBehaviour::SetDrawable(render::Drawable newDrawable, const core::Name<core::CaseSensitiveKey>& name)
	{
		if (drawable.IsValid())
		{
			ReleaseDrawable();
		}
		AttributeWriter<render::Drawable> handleWriter =
			owner->GetAttributeWriter<render::Drawable>(proto::gDrawableHandleAttributeName);
		AttributeWriter<core::Name<core::CaseSensitiveKey> > nameWriter =
			owner->GetAttributeWriter<core::Name<core::CaseSensitiveKey> >(gDrawableNameName);
		*handleWriter.value = newDrawable;
		*nameWriter.value = name;
		drawable = newDrawable;
		sourceName = name;
		drawable.SetUnknownCC(4);
		drawable.SetRegistered(requested.Test(7));
	}

	// FUNCTION: ENGINE 0x10862D60
	void RenderBehaviour::SetSource(render::DrawableArchetype* archetype, const core::Name<core::CaseSensitiveKey>& name)
	{
		sourceName = name;
		core::RefAssign(source, archetype);
		heap = core::GetCurrentHeap();
		unsigned int value;
		if (core::GetHeapAllocator(heap)->GetStat(0xb, (int*)&value))
		{
			heap = GetGameObjectHeap();
		}
		sourceDeferred = archetype == 0 || gRenderSourcesDeferred;
		if (!sourceDeferred)
		{
			if (source != 0)
			{
				SetDrawable(render::Drawable::CreateInstance((render::SourceDrawable*)source, true, poseAttribute != 0),
					sourceName);
				if (poseAttribute != 0)
				{
					SetPose(((render::SourceDrawable*)source)->CreatePoseInstance());
				}
			}
		}
		else if (poseAttribute != 0 && source != 0)
		{
			SetPose(((render::SourceDrawable*)source)->CreatePoseInstance());
		}
	}

	// FUNCTION: ENGINE 0x108636B0
	// EQUIVALENT: the engine computes the address of the package name before the stores of the three scales, ours
	// right before the call that needs it, 93.2 %
	RenderBehaviour::RenderBehaviour(GameObject* newOwner)
		: Behaviour(newOwner), drawable(), sourceName(), scaleState(driving::gOne), source(0), sourcePackage()
	{
		poseIsDrawables = true;
		updatesPose = true;
		sourceDeferred = false;
		heap = 0;
		Listen(1, true);
		Listen(0x1a, true);
		Listen(2, true);
		Listen(7, true);
		Listen(8, true);
		Listen(9, true);
		Listen(10, true);
		Listen(0x17, true);
		owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
		render::Drawable invalid;
		owner->SetAttributeAndGet<render::Drawable>(proto::gDrawableHandleAttributeName, invalid, false);
		owner->SetAttribute<core::Name<core::CaseSensitiveKey> >(gDrawableNameName, core::Name<core::CaseSensitiveKey>(), false);
		poseAttribute = static_cast<Attribute<pure3d::Pose*>*>(owner->FindAttribute(proto::gDrawableAttributeName));
		if (poseAttribute != 0 && poseAttribute->value != 0)
		{
			poseAttribute->value->AddRef();
		}
		scaleAttribute = static_cast<Attribute<math::Vector>*>(owner->FindAttribute(gScaleName));
		if (scaleAttribute != 0 && fabsf(scaleAttribute->value.x - 1.0f) <= 0.00001f
			&& fabsf(scaleAttribute->value.y - 1.0f) <= 0.00001f && fabsf(scaleAttribute->value.z - 1.0f) <= 0.00001f)
		{
			scaleAttribute = 0;
		}
	}

	// FUNCTION: ENGINE 0x108627B0
	void RenderBehaviour::Update(float dt, unsigned short mask)
	{
		if (drawable.IsValid())
		{
			UpdateScale(dt);
			pure3d::Pose* pose = 0;
			if (poseAttribute != 0 && poseIsDrawables)
			{
				pose = poseAttribute->value;
			}
			math::Matrix matrix = owner->transform->value;
			if (scaleAttribute != 0)
			{
				Attribute<math::Vector>* scaler = scaleAttribute;
				math::Matrix scaling = math::Matrix::IDENTITY;
				scaling.Scale(scaler->value.x, scaler->value.y, scaler->value.z);
				matrix.Multiply(scaling, matrix);
			}
			drawable.SetTransform(matrix);
			if (pose != 0)
			{
				if (updatesPose)
				{
					pose->Update();
				}
				drawable.CopyPoseStateFrom(pose);
			}
			if (!IsScaleChanging())
			{
				BaseAttribute* asleepAttribute = owner->FindAttribute(gAsleepName);
				bool asleep = asleepAttribute != 0 && static_cast<Attribute<bool>*>(asleepAttribute)->value;
				BaseAttribute* awakeAttribute = owner->FindAttribute(gPoseAwakeName);
				bool poseAwake = awakeAttribute != 0 && static_cast<Attribute<bool>*>(awakeAttribute)->value;
				if (asleep && !poseAwake)
				{
					Listen2(0x200, false);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10862F60
	content::MemberList* RenderBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, RenderBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNamedReferenceMemberMetaType<RenderBehaviour, render::DrawableArchetype>(
				&RenderBehaviour::GetSource, &RenderBehaviour::GetSourceName, &RenderBehaviour::SetSource, "p"),
				0, "drawableSource" },
			{ content::GetNameMetaType<RenderBehaviour>(true, true, "pn"),
				content::MemberOffset(&((RenderBehaviour*)0)->sourcePackage, (int)&((RenderBehaviour*)0)->sourcePackage),
				"sourcePackage" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10863060
	// EQUIVALENT: shrink-wrap (the engine saves the four registers in the entry block, ours the last two behind the
	// table jump), the temporaries of the cases get 8 bytes more frame than the engine's and the registers differ, 55.8 %
	void RenderBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 2:
			drawable.Method106E02C0();
			break;
		case 0x1a:
			if (!Query2(0x200))
			{
				Listen2(0x200, true);
			}
			break;
		case 1:
			{
				const core::Name<core::CaseSensitiveKey>& name = ((NameMessage*)message)->name;
				if (name == gScaleName)
				{
					if (scaleAttribute == 0)
					{
						scaleAttribute = static_cast<Attribute<math::Vector>*>(owner->FindAttribute(gScaleName));
					}
					math::Vector one(driving::gOne, driving::gOne, driving::gOne);
					if (IsVectorNear(scaleAttribute->value, one))
					{
						scaleAttribute = 0;
					}
				}
				else if (name == gAsleepName)
				{
					BaseAttribute* attribute = owner->FindAttribute(gAsleepName);
					if (attribute == 0 || !static_cast<Attribute<bool>*>(attribute)->value)
					{
						Listen2(0x200, true);
					}
				}
				else if (name == gPoseAwakeName)
				{
					BaseAttribute* attribute = owner->FindAttribute(gPoseAwakeName);
					if (attribute != 0 && static_cast<Attribute<bool>*>(attribute)->value)
					{
						Listen2(0x200, true);
					}
				}
			}
			break;
		case 8:
			switch ((unsigned short)message->id)
			{
			case 0:
				drawable.SetSegmentVisible(((SegmentMessage*)message)->name, ((SegmentMessage*)message)->visible);
				break;
			case 1:
				drawable.SetSegmentVisibilities(((SegmentsMessage*)message)->visibilities,
					((SegmentsMessage*)message)->count);
				break;
			case 3:
				drawable.SetPartsUnknown(true);
				break;
			case 2:
				drawable.SetPartsUnknown(((BoolMessage*)message)->value);
				break;
			}
			break;
		case 7:
			switch ((unsigned short)message->id)
			{
			case 7:
				scaleState.target = camera::MinOf(scaleState.target, ((FloatMessage*)message)->value);
				WakeUpdate();
				break;
			case 9:
				if (sourceDeferred)
				{
					if (source == 0)
					{
						StreamPackage* package = FindStreamPackage(sourcePackage);
						if (package != 0)
						{
							StreamPackageInstance* instance = package->instance;
							if (instance != 0
								&& (instance->IsLoaded() || instance->state == StreamPackageInstance::STATE_CLIENT_LOADING))
							{
								core::RefAssign(source, instance->inventory->Find<render::DrawableArchetype>(sourceName));
							}
						}
						if (source == 0)
						{
							break;
						}
					}
					core::HeapScope scope(heap);
					SetDrawable(render::Drawable::CreateInstance((render::SourceDrawable*)source, true, poseAttribute != 0),
						sourceName);
					if (poseAttribute != 0 && poseAttribute->value == 0)
					{
						SetPose(drawable.CreatePoseInstance());
					}
					sourceDeferred = false;
				}
				break;
			case 10:
				if (sourcePackage == core::Name<core::CaseSensitiveKey>("", 1))
				{
					render::Drawable::Destroy(&drawable, 0);
					sourceDeferred = true;
				}
				else
				{
					ReleaseDrawable();
					sourceDeferred = true;
				}
				break;
			case 2:
				((GetCurrentDrawable*)message)->drawable = drawable;
				break;
			case 3:
				{
					SetDrawable(render::Drawable(((DrawableMessage*)message)->drawable.mHandle),
						((DrawableMessage*)message)->name);
					if (poseAttribute != 0)
					{
						render::Drawable handle = ((DrawableMessage*)message)->drawable;
						SetPose(handle.CreatePoseInstance());
					}
				}
				break;
			case 4:
				ReleaseDrawable();
				break;
			case 5:
				drawable.mHandle = 0xffffffff;
				break;
			case 6:
				{
					float old = scaleState.factor;
					scaleState.factor = ((FloatMessage*)message)->value;
					if (old != scaleState.factor)
					{
						drawable.SetUnknownBC(GetEffectiveScale());
					}
				}
				break;
			case 8:
				updatesPose = ((BoolMessage*)message)->value;
				break;
			case 0xb:
				Listen2(0x200, ((BoolMessage*)message)->value);
				drawable.SetRegistered(((BoolMessage*)message)->value);
				break;
			}
			break;
		case 9:
			if (message->id == 5)
			{
				drawable.Method106E1250(((NameMessage*)message)->name);
			}
			break;
		case 10:
			switch ((unsigned short)message->id)
			{
			case 4:
				drawable.SetVertexDeformRegion(((DeformRegionMessage*)message)->region);
				break;
			case 2:
				drawable.ClearFlag10();
				break;
			case 3:
				drawable.SetFlag10();
				break;
			case 0:
				{
					PlayAnimationMessage* play = (PlayAnimationMessage*)message;
					if (owner->GetAttributePtr<pure3d::PoseAnimationController*>(gPoseAnimationControllerName).value == 0
						&& poseAttribute == 0)
					{
						if (requested.Test(7))
						{
							drawable.SetRegistered(false);
						}
						drawable.PlayAnimation(play->animation, play->speed, play->frame, play->start, play->end,
							play->mode);
						if (requested.Test(7))
						{
							drawable.SetRegistered(true);
						}
						if (play->animation == 0)
						{
							poseIsDrawables = true;
						}
						else
						{
							poseIsDrawables = drawable.IsUnknown8();
						}
					}
				}
				break;
			case 1:
				{
					PlayMessage* play = (PlayMessage*)message;
					drawable.Play(play->start, play->end, play->speed, play->mode, play->cycles);
				}
				break;
			case 7:
				drawable.Method106E0490();
				break;
			case 8:
				drawable.Method106E03E0();
				break;
			}
			break;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10862490
// FUNCTION: ENGINE 0x108624D0
// FUNCTION: ENGINE 0x10862530
// FUNCTION: ENGINE 0x10862540
// FUNCTION: ENGINE 0x108626A0
// FUNCTION: ENGINE 0x108626C0
// FUNCTION: ENGINE 0x108626E0
// FUNCTION: ENGINE 0x10862710
// FUNCTION: ENGINE 0x10862730
// FUNCTION: ENGINE 0x10862740
// FUNCTION: ENGINE 0x10862750
// FUNCTION: ENGINE 0x10862AC0
// FUNCTION: ENGINE 0x10862B40
// FUNCTION: ENGINE 0x10863040

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108624F0
// FUNCTION: ENGINE 0x10862790
// FUNCTION: ENGINE 0x10862BE0
// FUNCTION: ENGINE 0x10862BF0
