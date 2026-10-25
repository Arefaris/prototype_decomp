// engine::RenderBehaviour (RTTI and reflection name "RenderBehaviour", vftable 0x10E730C8, 8 slots, base
// engine::Behaviour): the behaviour that draws a game object. It owns a render::Drawable made from a drawable archetype
// (the reflected members are "drawableSource", the archetype's name, and "sourcePackage", the stream package the
// archetype comes from), puts the object's transform (and scale) on it every update, hands it the pose the object's
// "pose" attribute holds and forwards the drawable messages (message types 7 - 10) to the drawable. Unit 0x10862350 -
// 0x10863850 (no assert path; the directory and file name are guesses). The reflected names are original, the rest is
// guessed.
#ifndef ENGINE_RENDER_RENDERBEHAVIOUR_H
#define ENGINE_RENDER_RENDERBEHAVIOUR_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/drawablearchetype.h"

namespace pure3d
{
	class Pose;
}

namespace engine
{
	// The scale the drawable is drawn at: the one it has, the one it moves to and the factor on top of both
	struct ScaleState
	{
		explicit ScaleState(float one)
		{
			current = one;
			target = one;
			factor = one;
		}

		float current;  // +0x20
		float target;  // +0x24
		float factor;  // +0x28
	};

	class RenderBehaviour : public Behaviour
	{
	public:
		// 0x108636B0
		explicit RenderBehaviour(GameObject* newOwner);
		// 0x10862C10 (deleting destructor 0x10863040)
		virtual ~RenderBehaviour();

		// 0x10862350 / 0x10862F60
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108623B0): from now on the update runs every frame
		virtual void Slot1();
		// slot 3 (0x10862420)
		virtual void OnActiveChanged(bool active);
		// slot 4 (0x108627B0): puts the object's transform, scaled, and the pose on the drawable
		virtual void Update(float dt, unsigned short mask);
		// slot 6 (0x10863060)
		virtual void OnMessage(Message* message);

		// 0x10862390 / 0x108623A0: whether the drawables are made when their package has loaded, not at once
		static void SetSourcesDeferred(bool deferred);
		static bool GetSourcesDeferred();

		// 0x10862440 / 0x10862450 / 0x10862D60: the reflected "drawableSource" (the archetype is not kept: the getter
		// answers nothing)
		render::DrawableArchetype* GetSource() const;
		const core::Name<core::CaseSensitiveKey>* GetSourceName() const;
		void SetSource(render::DrawableArchetype* archetype, const core::Name<core::CaseSensitiveKey>& name);

		// 0x108623C0: whether the scale is moving towards its target
		bool IsScaleChanging() const;
		// 0x108623F0: makes sure the update runs
		void WakeUpdate();
		// 0x10862460: the scale the drawable is drawn at
		float GetEffectiveScale() const;
		// 0x10862570: moves the scale towards its target
		void UpdateScale(float dt);
		// 0x10862600: hands the drawable's pose to the object's "pose" attribute and tells the object
		void SetPose(pure3d::Pose* pose);
		// 0x10862A60: drops the pose and the drawable and the archetype
		void ReleaseDrawable();
		// 0x10862C30: takes a drawable that was made elsewhere and publishes its handle
		void SetDrawable(render::Drawable newDrawable, const core::Name<core::CaseSensitiveKey>& name);

		Attribute<pure3d::Pose*>* poseAttribute;  // +0xC
		Attribute<math::Vector>* scaleAttribute;  // +0x10, null while the scale is the identity
		render::Drawable drawable;  // +0x14
		core::Name<core::CaseSensitiveKey> sourceName;  // +0x18
		ScaleState scaleState;  // +0x20
		render::DrawableArchetype* source;  // +0x2C (holds a reference)
		core::Name<core::CaseSensitiveKey> sourcePackage;  // +0x30
		int heap;  // +0x38
		// +0x3C: the pose is the drawable's own (bit 0), the pose is updated here (bit 1), the drawable is made later
		// (bit 2)
		unsigned char poseIsDrawables : 1;
		unsigned char updatesPose : 1;
		unsigned char sourceDeferred : 1;
	};
}

#endif
