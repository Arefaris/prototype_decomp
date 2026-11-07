// proto::SensesInfoBehaviour (RTTI and reflection names; base engine::Behaviour): what an object senses of the others
// by its kind (proto::SensesType). Reflected: the kind. Unit 0x10075AC0 - 0x10076370 (no assert path; the file name is
// a guess). The reflected name is original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_SENSESINFOBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SENSESINFOBEHAVIOUR_H

#include "code/content/enummetatype.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/render/async/drawable.h"
#include "code/proto/render/deformshaderbehaviour.h"

namespace proto
{
	// The kinds of object the senses distinguish (reflected as proto::SensesType)
	enum SensesType
	{
		SENSES_NONE = 0,
		SENSES_PROTOTYPE = 1,
		SENSES_INFECTED0 = 2,
		SENSES_INFECTED1 = 3,
		SENSES_INFECTED2 = 4,
		SENSES_BRAWLER = 5,
		SENSES_STEALTH = 6,
		SENSES_LEADER = 7,
		SENSES_HYDRA = 8,
		SENSES_SOLDIER = 9,
		SENSES_TANK = 10,
		SENSES_HELICOPTER = 11,
		SENSES_UAV = 12,
		SENSES_GENERIC_MILITARY = 13,
		SENSES_HIVE_PROP = 14,
		SENSES_INFECTED_BOSS = 15,
		SENSES_PEDESTRIAN = 16
	};

	// RTTI: proto::ConfigureSensesInfoMessage (message type 0x3D, id 0xE): sets the values; a negative value leaves the
	// old one (the member names are guesses)
	struct ConfigureSensesInfoMessage : public ProtoRenderMsg
	{
		ConfigureSensesInfoMessage(engine::render::Drawable newDrawable, float newNear, float newFar, bool newFade) :
			ProtoRenderMsg(0xe), drawable(newDrawable), nearValue(newNear), farValue(newFar), fade(newFade)
		{
		}
		virtual ~ConfigureSensesInfoMessage()
		{
		}

		engine::render::Drawable drawable;  // +0xC
		float nearValue;  // +0x10
		float farValue;  // +0x14
		bool fade;  // +0x18
	};

	// RTTI: proto::GetSensesInfoMessage (id 0xF): answers the values
	struct GetSensesInfoMessage : public ProtoRenderMsg
	{
		explicit GetSensesInfoMessage(bool newScaled) : ProtoRenderMsg(0xf), nearValue(0.0f), farValue(0.0f), scaled(newScaled)
		{
		}
		virtual ~GetSensesInfoMessage()
		{
		}

		float nearValue;  // +0xC
		float farValue;  // +0x10
		bool scaled;  // +0x14
	};

	// RTTI: proto::ResetSensesInfoMessage (id 0x10): back to the values of the kind
	struct ResetSensesInfoMessage : public ProtoRenderMsg
	{
		ResetSensesInfoMessage() : ProtoRenderMsg(0x10)
		{
		}
		virtual ~ResetSensesInfoMessage()
		{
		}
	};

	// The values of every kind of object: how near and how far it is seen at the start (17 entries each; 0x10FED1F8 and
	// 0x10FED240) and the scale they are applied with (0x10FED1F4)
	extern float gSensesScale;
	extern float gSensesNearValues[17];
	extern float gSensesFarValues[17];

	class SensesInfoBehaviour : public engine::Behaviour
	{
	public:
		// 0x10075B00
		explicit SensesInfoBehaviour(engine::GameObject* newOwner);
		// 0x10075CE0 (deleting destructor)
		virtual ~SensesInfoBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x10075F70), 3 (0x10075F30), 4 (0x10075FB0) and 6 (0x100760B0)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x10075B90: the scale every object's senses are seen with (names guessed)
		static void SetGlobalScale(float scale);
		// 0x10075D10: hands the drawable a modifier with the values
		void ApplyVision(engine::render::Drawable drawable);
		// 0x10075E60: asks the object for its drawable and applies the values
		void Refresh();
		// 0x10075EF0 / 0x10075F10
		void SetNear(float value);
		void SetFar(float value);

		float nearValue;  // +0xC
		float farValue;  // +0x10
		float scale;  // +0x14
		SensesType sensesType;  // +0x18
		bool active;  // +0x1C
		bool fading;  // +0x1D
	};
}

#endif
