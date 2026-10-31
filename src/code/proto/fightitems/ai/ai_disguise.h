// Fight items of the ai group: AbsoluteHeightCondition, AreDisguiseActionsEnabledCondition, IsDisguiseActionEnabledCondition, DisguiseActionUsedTrack, ClearMarkersTrack, DumpAlertCharactersTrack, PlayDebugDialogTrack, DrawObjectDebugTrack, HelicopterStrafeModeTrack, ShowDisguiseActionHUDTrack, AddMarkerByKeyTrack, AddDiversionTrack, SetUserTooltipTrack, AdjustHydraMovementTrack (unit 0x102272B0 - 0x1022AC60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_DISGUISE_H
#define PROTO_FIGHTITEMS_AI_AI_DISGUISE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::AbsoluteHeightCondition (10 vftable slots, 0x14 bytes)
			class AbsoluteHeightCondition : public fight::Condition
			{
			public:
				// 0x10227680
				AbsoluteHeightCondition();
				virtual ~AbsoluteHeightCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E9950, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gAbsoluteHeightConditionProperties;
			fight::ConditionFactory* CreateAbsoluteHeightConditionFactory(const char* name);
			void RegisterAbsoluteHeightConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AreDisguiseActionsEnabledCondition (10 vftable slots, 0xC bytes)
			class AreDisguiseActionsEnabledCondition : public fight::Condition
			{
			public:
				// 0x10227750
				AreDisguiseActionsEnabledCondition();
				virtual ~AreDisguiseActionsEnabledCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E98C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gAreDisguiseActionsEnabledConditionProperties;
			fight::ConditionFactory* CreateAreDisguiseActionsEnabledConditionFactory(const char* name);
			void RegisterAreDisguiseActionsEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::IsDisguiseActionEnabledCondition (10 vftable slots, 0x10 bytes)
			class IsDisguiseActionEnabledCondition : public fight::Condition
			{
			public:
				// 0x102277B0
				IsDisguiseActionEnabledCondition();
				virtual ~IsDisguiseActionEnabledCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E9770, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAction(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int action;  // +0xC
			};

			extern fight::Property** gIsDisguiseActionEnabledConditionProperties;
			fight::ConditionFactory* CreateIsDisguiseActionEnabledConditionFactory(const char* name);
			void RegisterIsDisguiseActionEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DisguiseActionUsedTrack (16 vftable slots, 0x14 bytes)
			class DisguiseActionUsedTrack : public fight::Track
			{
			public:
				// 0x10227820
				DisguiseActionUsedTrack();
				virtual ~DisguiseActionUsedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E8D00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetAction(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int action;  // +0x10
			};

			extern fight::Property** gDisguiseActionUsedTrackProperties;
			fight::TrackFactory* CreateDisguiseActionUsedTrackFactory(const char* name);
			void RegisterDisguiseActionUsedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ClearMarkersTrack (16 vftable slots, 0x10 bytes)
			class ClearMarkersTrack : public fight::Track
			{
			public:
				// 0x10227900
				ClearMarkersTrack();
				virtual ~ClearMarkersTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBB70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gClearMarkersTrackProperties;
			fight::TrackFactory* CreateClearMarkersTrackFactory(const char* name);
			void RegisterClearMarkersTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DumpAlertCharactersTrack (16 vftable slots, 0x10 bytes)
			class DumpAlertCharactersTrack : public fight::Track
			{
			public:
				// 0x102279E0
				DumpAlertCharactersTrack();
				virtual ~DumpAlertCharactersTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E8CD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gDumpAlertCharactersTrackProperties;
			fight::TrackFactory* CreateDumpAlertCharactersTrackFactory(const char* name);
			void RegisterDumpAlertCharactersTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PlayDebugDialogTrack (16 vftable slots, 0x1C bytes)
			class PlayDebugDialogTrack : public fight::Track
			{
			public:
				// 0x10227A60
				PlayDebugDialogTrack();
				virtual ~PlayDebugDialogTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBA50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetText(const char* newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* text;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gPlayDebugDialogTrackProperties;
			fight::TrackFactory* CreatePlayDebugDialogTrackFactory(const char* name);
			void RegisterPlayDebugDialogTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DrawObjectDebugTrack (16 vftable slots, 0x40 bytes)
			class DrawObjectDebugTrack : public fight::Track
			{
			public:
				// 0x102280F0
				DrawObjectDebugTrack();
				virtual ~DrawObjectDebugTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBAB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetColour(const math::Colour128& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetAttachJoint(const fight::Name& newValue);
				bool SetRadius(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name attachJoint;  // +0x10
					math::Colour128 colour;  // +0x18
					math::Vector offset;  // +0x28
					float radius;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
			};

			extern fight::Property** gDrawObjectDebugTrackProperties;
			fight::TrackFactory* CreateDrawObjectDebugTrackFactory(const char* name);
			void RegisterDrawObjectDebugTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HelicopterStrafeModeTrack (16 vftable slots, 0x18 bytes)
			class HelicopterStrafeModeTrack : public fight::Track
			{
			public:
				// 0x10227B80
				HelicopterStrafeModeTrack();
				virtual ~HelicopterStrafeModeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBD60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gHelicopterStrafeModeTrackProperties;
			fight::TrackFactory* CreateHelicopterStrafeModeTrackFactory(const char* name);
			void RegisterHelicopterStrafeModeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ShowDisguiseActionHUDTrack (16 vftable slots, 0x20 bytes)
			class ShowDisguiseActionHUDTrack : public fight::Track
			{
			public:
				// 0x10227C10
				ShowDisguiseActionHUDTrack();
				virtual ~ShowDisguiseActionHUDTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBBD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetShowAndHideOnly(bool newValue);
				bool SetStealthConsumeInRange(bool newValue);
				bool SetStealthConsumeUsable(bool newValue);
				bool SetPatsyUsable(bool newValue);
				bool SetAirStrikeUsable(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool airStrikeUsable;  // +0x18
					bool patsyUsable;  // +0x19
					bool showAndHideOnly;  // +0x1A
					bool stealthConsumeInRange;  // +0x1B
					bool stealthConsumeUsable;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gShowDisguiseActionHUDTrackProperties;
			fight::TrackFactory* CreateShowDisguiseActionHUDTrackFactory(const char* name);
			void RegisterShowDisguiseActionHUDTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AddMarkerByKeyTrack (16 vftable slots, 0x28 bytes)
			class AddMarkerByKeyTrack : public fight::Track
			{
			public:
				// 0x10227CC0
				AddMarkerByKeyTrack();
				virtual ~AddMarkerByKeyTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBB10, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetType(int newValue);
				bool SetDisplayType(int newValue);
				bool SetAnimType(int newValue);
				bool SetColor(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int animType;  // +0x18
					int color;  // +0x1C
					int type;  // +0x20
					int displayType;  // +0x24
			};

			extern fight::Property** gAddMarkerByKeyTrackProperties;
			fight::TrackFactory* CreateAddMarkerByKeyTrackFactory(const char* name);
			void RegisterAddMarkerByKeyTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AddDiversionTrack (16 vftable slots, 0x24 bytes)
			class AddDiversionTrack : public fight::Track
			{
			public:
				// 0x10227D70
				AddDiversionTrack();
				virtual ~AddDiversionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E8CF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIntensity(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMaxDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float intensity;  // +0x10
					float maxDistance;  // +0x14
					float minDistance;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
			};

			extern fight::Property** gAddDiversionTrackProperties;
			fight::TrackFactory* CreateAddDiversionTrackFactory(const char* name);
			void RegisterAddDiversionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetUserTooltipTrack (16 vftable slots, 0x18 bytes)
			class SetUserTooltipTrack : public fight::Track
			{
			public:
				// 0x10227E30
				SetUserTooltipTrack();
				virtual ~SetUserTooltipTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EB9F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTooltip(const char* newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* tooltip;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gSetUserTooltipTrackProperties;
			fight::TrackFactory* CreateSetUserTooltipTrackFactory(const char* name);
			void RegisterSetUserTooltipTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AdjustHydraMovementTrack (16 vftable slots, 0x1C bytes)
			class AdjustHydraMovementTrack : public fight::Track
			{
			public:
				// 0x10227F10
				AdjustHydraMovementTrack();
				virtual ~AdjustHydraMovementTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EBDC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAboveGround(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool aboveGround;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gAdjustHydraMovementTrackProperties;
			fight::TrackFactory* CreateAdjustHydraMovementTrackFactory(const char* name);
			void RegisterAdjustHydraMovementTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ClearMarkersAction (9 vftable slots, 0x2C bytes)
			class ClearMarkersAction : public fight::Action
			{
			public:
				// 0x101EA6A0
				ClearMarkersAction(ClearMarkersTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E9590
				virtual ~ClearMarkersAction();

				// vftable slot 5 (0x101E8C70)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E8CC0)
				virtual void Slot6();

				core::Link<ClearMarkersTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::PlayDebugDialogAction (9 vftable slots, 0x2C bytes)
			class PlayDebugDialogAction : public fight::Action
			{
			public:
				// 0x101EA0E0
				PlayDebugDialogAction(PlayDebugDialogTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E94A0
				virtual ~PlayDebugDialogAction();

				// vftable slot 5 (0x101E8C30)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E8C40)
				virtual void Slot6();
				// vftable slot 7 (0x101EA190)
				virtual bool Slot7(int arg, float value);

				core::Link<PlayDebugDialogTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::HelicopterStrafeModeAction (9 vftable slots, 0x2C bytes)
			class HelicopterStrafeModeAction : public fight::Action
			{
			public:
				// 0x101EB7A0
				HelicopterStrafeModeAction(HelicopterStrafeModeTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E9A30
				virtual ~HelicopterStrafeModeAction();

				// vftable slot 5 (0x101E9A60)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E9B20)
				virtual void Slot6();
				// vftable slot 7 (0x101E9AA0)
				virtual bool Slot7(int arg, float value);

				core::Link<HelicopterStrafeModeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ShowDisguiseActionHUDAction (9 vftable slots, 0x2C bytes)
			class ShowDisguiseActionHUDAction : public fight::Action
			{
			public:
				// 0x101EB3B0
				ShowDisguiseActionHUDAction(ShowDisguiseActionHUDTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E96F0
				virtual ~ShowDisguiseActionHUDAction();

				// vftable slot 5 (0x101EBC30)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101EB460)
				virtual void Slot6();
				// vftable slot 7 (0x101EBCE0)
				virtual bool Slot7(int arg, float value);

				core::Link<ShowDisguiseActionHUDTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::AddMarkerByKeyAction (9 vftable slots, 0x2C bytes)
			class AddMarkerByKeyAction : public fight::Action
			{
			public:
				// 0x101EA4B0
				AddMarkerByKeyAction(AddMarkerByKeyTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E9540
				virtual ~AddMarkerByKeyAction();

				// vftable slot 5 (0x101EA560)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101EA610)
				virtual void Slot6();
				// vftable slot 7 (0x101EA690)
				virtual bool Slot7(int arg, float value);

				core::Link<AddMarkerByKeyTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::SetUserTooltipAction (9 vftable slots, 0x2C bytes)
			class SetUserTooltipAction : public fight::Action
			{
			public:
				// 0x101E9FC0
				SetUserTooltipAction(SetUserTooltipTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E9450
				virtual ~SetUserTooltipAction();

				// vftable slot 5 (0x101E8C10)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E8C20)
				virtual void Slot6();
				// vftable slot 7 (0x101EA070)
				virtual bool Slot7(int arg, float value);

				core::Link<SetUserTooltipTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::AdjustHydraMovementAction (9 vftable slots, 0x2C bytes)
			class AdjustHydraMovementAction : public fight::Action
			{
			public:
				// 0x101EB850
				AdjustHydraMovementAction(AdjustHydraMovementTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E9B50
				virtual ~AdjustHydraMovementAction();

				// vftable slot 5 (0x101EB900)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101EB950)
				virtual void Slot6();

				core::Link<AdjustHydraMovementTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::DrawObjectDebugAction (9 vftable slots, 0x2C bytes)
			class DrawObjectDebugAction : public fight::Action
			{
			public:
				// 0x101EA1A0
				DrawObjectDebugAction(DrawObjectDebugTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101E94F0
				virtual ~DrawObjectDebugAction();

				// vftable slot 5 (0x101E8C50)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E8C60)
				virtual void Slot6();
				// vftable slot 7 (0x101EA250)
				virtual bool Slot7(int arg, float value);

				core::Link<DrawObjectDebugTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
