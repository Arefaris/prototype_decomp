// Fight items of the ai group: AbsoluteHeightCondition, AreDisguiseActionsEnabledCondition, IsDisguiseActionEnabledCondition, DisguiseActionUsedTrack, ClearMarkersTrack, DumpAlertCharactersTrack, PlayDebugDialogTrack, DrawObjectDebugTrack, HelicopterStrafeModeTrack, ShowDisguiseActionHUDTrack, AddMarkerByKeyTrack, AddDiversionTrack, SetUserTooltipTrack, AdjustHydraMovementTrack (unit 0x102272B0 - 0x1022AC60; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_disguise.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gAbsoluteHeightConditionProperties;  // 0x112558F4

			// FUNCTION: ENGINE 0x102272B0
			bool AbsoluteHeightCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102272C0
			bool AbsoluteHeightCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227650
			fight::Property* AbsoluteHeightCondition::GetProperty(int index)
			{
				return gAbsoluteHeightConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10227670
			void AbsoluteHeightCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAbsoluteHeightConditionProperties);
			}

			// FUNCTION: ENGINE 0x10227680
			AbsoluteHeightCondition::AbsoluteHeightCondition() : fight::Condition(0), distance(0.0f), compare(4)
			{
			}

			// FUNCTION: ENGINE 0x102276B0
			AbsoluteHeightCondition::~AbsoluteHeightCondition()
			{
			}

			// FUNCTION: ENGINE 0x102294C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AbsoluteHeightCondition::RegisterProperties()
			{
				if (gAbsoluteHeightConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AbsoluteHeightCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AbsoluteHeightCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AbsoluteHeightCondition>("distance", &AbsoluteHeightCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gAbsoluteHeightConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229220
			fight::ConditionFactory* CreateAbsoluteHeightConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AbsoluteHeightCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A0B0
			void RegisterAbsoluteHeightConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AbsoluteHeightCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAreDisguiseActionsEnabledConditionProperties;  // 0x112558F8

			// FUNCTION: ENGINE 0x10227720
			fight::Property* AreDisguiseActionsEnabledCondition::GetProperty(int index)
			{
				return gAreDisguiseActionsEnabledConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10227740
			void AreDisguiseActionsEnabledCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAreDisguiseActionsEnabledConditionProperties);
			}

			// FUNCTION: ENGINE 0x10227750
			AreDisguiseActionsEnabledCondition::AreDisguiseActionsEnabledCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10227770
			AreDisguiseActionsEnabledCondition::~AreDisguiseActionsEnabledCondition()
			{
			}

			// FUNCTION: ENGINE 0x102276C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AreDisguiseActionsEnabledCondition::RegisterProperties()
			{
				if (gAreDisguiseActionsEnabledConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gAreDisguiseActionsEnabledConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229250
			fight::ConditionFactory* CreateAreDisguiseActionsEnabledConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AreDisguiseActionsEnabledCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A0E0
			void RegisterAreDisguiseActionsEnabledConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AreDisguiseActionsEnabledCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsDisguiseActionEnabledConditionProperties;  // 0x112558FC

			// FUNCTION: ENGINE 0x102272E0
			bool IsDisguiseActionEnabledCondition::SetAction(int newValue)
			{
				action = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227780
			fight::Property* IsDisguiseActionEnabledCondition::GetProperty(int index)
			{
				return gIsDisguiseActionEnabledConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102277A0
			void IsDisguiseActionEnabledCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsDisguiseActionEnabledConditionProperties);
			}

			// FUNCTION: ENGINE 0x102277B0
			IsDisguiseActionEnabledCondition::IsDisguiseActionEnabledCondition() : fight::Condition(0), action(0)
			{
			}

			// FUNCTION: ENGINE 0x102277E0
			IsDisguiseActionEnabledCondition::~IsDisguiseActionEnabledCondition()
			{
			}

			// FUNCTION: ENGINE 0x102295B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsDisguiseActionEnabledCondition::RegisterProperties()
			{
				if (gIsDisguiseActionEnabledConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<IsDisguiseActionEnabledCondition>("action", gIsDisguiseActionEnabledConditionActionTable, gIsDisguiseActionEnabledConditionActionCount, &IsDisguiseActionEnabledCondition::SetAction);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsDisguiseActionEnabledConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229280
			fight::ConditionFactory* CreateIsDisguiseActionEnabledConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsDisguiseActionEnabledCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A110
			void RegisterIsDisguiseActionEnabledConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsDisguiseActionEnabledCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDisguiseActionUsedTrackProperties;  // 0x11255900

			// FUNCTION: ENGINE 0x102272F0
			bool DisguiseActionUsedTrack::SetAction(int newValue)
			{
				action = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102277F0
			fight::Property* DisguiseActionUsedTrack::GetProperty(int index)
			{
				return gDisguiseActionUsedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227810
			void DisguiseActionUsedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDisguiseActionUsedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227820
			DisguiseActionUsedTrack::DisguiseActionUsedTrack() : action(0)
			{
			}

			// FUNCTION: ENGINE 0x10227840
			float DisguiseActionUsedTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227850
			float DisguiseActionUsedTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227860
			DisguiseActionUsedTrack::~DisguiseActionUsedTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229660
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisguiseActionUsedTrack::RegisterProperties()
			{
				if (gDisguiseActionUsedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DisguiseActionUsedTrack>("action", gIsDisguiseActionEnabledConditionActionTable, gIsDisguiseActionEnabledConditionActionCount, &DisguiseActionUsedTrack::SetAction);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDisguiseActionUsedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102292B0
			fight::TrackFactory* CreateDisguiseActionUsedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisguiseActionUsedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A140
			void RegisterDisguiseActionUsedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisguiseActionUsedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gClearMarkersTrackProperties;  // 0x11255904

			// FUNCTION: ENGINE 0x102278D0
			fight::Property* ClearMarkersTrack::GetProperty(int index)
			{
				return gClearMarkersTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102278F0
			void ClearMarkersTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearMarkersTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227900
			ClearMarkersTrack::ClearMarkersTrack()
			{
			}

			// FUNCTION: ENGINE 0x10227920
			float ClearMarkersTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227930
			float ClearMarkersTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227940
			ClearMarkersTrack::~ClearMarkersTrack()
			{
			}

			// FUNCTION: ENGINE 0x10227870
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearMarkersTrack::RegisterProperties()
			{
				if (gClearMarkersTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gClearMarkersTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102292E0
			fight::TrackFactory* CreateClearMarkersTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearMarkersTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A170
			void RegisterClearMarkersTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearMarkersTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDumpAlertCharactersTrackProperties;  // 0x11255908

			// FUNCTION: ENGINE 0x102279B0
			fight::Property* DumpAlertCharactersTrack::GetProperty(int index)
			{
				return gDumpAlertCharactersTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102279D0
			void DumpAlertCharactersTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDumpAlertCharactersTrackProperties);
			}

			// FUNCTION: ENGINE 0x102279E0
			DumpAlertCharactersTrack::DumpAlertCharactersTrack()
			{
			}

			// FUNCTION: ENGINE 0x10227A00
			float DumpAlertCharactersTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227A10
			float DumpAlertCharactersTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227A20
			DumpAlertCharactersTrack::~DumpAlertCharactersTrack()
			{
			}

			// FUNCTION: ENGINE 0x10227950
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DumpAlertCharactersTrack::RegisterProperties()
			{
				if (gDumpAlertCharactersTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gDumpAlertCharactersTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229310
			fight::TrackFactory* CreateDumpAlertCharactersTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumpAlertCharactersTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A1A0
			void RegisterDumpAlertCharactersTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumpAlertCharactersTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPlayDebugDialogTrackProperties;  // 0x1125590C

			// FUNCTION: ENGINE 0x10227300
			bool PlayDebugDialogTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227320
			bool PlayDebugDialogTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227AF0
			bool PlayDebugDialogTrack::SetText(const char* newValue)
			{
				text = fight::ReplaceString(text, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10227A30
			fight::Property* PlayDebugDialogTrack::GetProperty(int index)
			{
				return gPlayDebugDialogTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227A50
			void PlayDebugDialogTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPlayDebugDialogTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227A60
			PlayDebugDialogTrack::PlayDebugDialogTrack() : text(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10227AA0
			float PlayDebugDialogTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227AB0
			float PlayDebugDialogTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227AC0
			PlayDebugDialogTrack::~PlayDebugDialogTrack()
			{
				delete[] text;
			}

			// FUNCTION: ENGINE 0x10229710
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PlayDebugDialogTrack::RegisterProperties()
			{
				if (gPlayDebugDialogTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PlayDebugDialogTrack>("timeBegin", &PlayDebugDialogTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PlayDebugDialogTrack>("timeEnd", &PlayDebugDialogTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyString<PlayDebugDialogTrack>("text", &PlayDebugDialogTrack::SetText);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gPlayDebugDialogTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229340
			fight::TrackFactory* CreatePlayDebugDialogTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayDebugDialogTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A1D0
			void RegisterPlayDebugDialogTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayDebugDialogTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDrawObjectDebugTrackProperties;  // 0x11255910

			// FUNCTION: ENGINE 0x10227340
			bool DrawObjectDebugTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227360
			bool DrawObjectDebugTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227380
			bool DrawObjectDebugTrack::SetColour(const math::Colour128& newValue)
			{
				colour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102273B0
			bool DrawObjectDebugTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10227F80
			bool DrawObjectDebugTrack::SetAttachJoint(const fight::Name& newValue)
			{
				attachJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102273D0
			bool DrawObjectDebugTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227B20
			fight::Property* DrawObjectDebugTrack::GetProperty(int index)
			{
				return gDrawObjectDebugTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227B40
			void DrawObjectDebugTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDrawObjectDebugTrackProperties);
			}

			// FUNCTION: ENGINE 0x102280F0
			DrawObjectDebugTrack::DrawObjectDebugTrack() : colour(1.0f, 1.0f, 1.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), radius(-1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10228170
			float DrawObjectDebugTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10228180
			float DrawObjectDebugTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10228190
			DrawObjectDebugTrack::~DrawObjectDebugTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022A6D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DrawObjectDebugTrack::RegisterProperties()
			{
				if (gDrawObjectDebugTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DrawObjectDebugTrack>("timeBegin", &DrawObjectDebugTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DrawObjectDebugTrack>("timeEnd", &DrawObjectDebugTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyColour<DrawObjectDebugTrack>("colour", &DrawObjectDebugTrack::SetColour);
					properties[2] = property;
					property = new fight::PropertyVector<DrawObjectDebugTrack>("offset", &DrawObjectDebugTrack::SetOffset);
					properties[3] = property;
					property = new fight::PropertyNameList<DrawObjectDebugTrack>("attachJoint", &DrawObjectDebugTrack::SetAttachJoint);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<DrawObjectDebugTrack>("radius", &DrawObjectDebugTrack::SetRadius);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDrawObjectDebugTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229370
			fight::TrackFactory* CreateDrawObjectDebugTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DrawObjectDebugTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A200
			void RegisterDrawObjectDebugTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DrawObjectDebugTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHelicopterStrafeModeTrackProperties;  // 0x11255914

			// FUNCTION: ENGINE 0x102273F0
			bool HelicopterStrafeModeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227410
			bool HelicopterStrafeModeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227B50
			fight::Property* HelicopterStrafeModeTrack::GetProperty(int index)
			{
				return gHelicopterStrafeModeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227B70
			void HelicopterStrafeModeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHelicopterStrafeModeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227B80
			HelicopterStrafeModeTrack::HelicopterStrafeModeTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10227BB0
			float HelicopterStrafeModeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227BC0
			float HelicopterStrafeModeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227BD0
			HelicopterStrafeModeTrack::~HelicopterStrafeModeTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229820
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HelicopterStrafeModeTrack::RegisterProperties()
			{
				if (gHelicopterStrafeModeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HelicopterStrafeModeTrack>("timeBegin", &HelicopterStrafeModeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HelicopterStrafeModeTrack>("timeEnd", &HelicopterStrafeModeTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHelicopterStrafeModeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102293A0
			fight::TrackFactory* CreateHelicopterStrafeModeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HelicopterStrafeModeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A230
			void RegisterHelicopterStrafeModeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HelicopterStrafeModeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShowDisguiseActionHUDTrackProperties;  // 0x11255918

			// FUNCTION: ENGINE 0x10227430
			bool ShowDisguiseActionHUDTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227450
			bool ShowDisguiseActionHUDTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227470
			bool ShowDisguiseActionHUDTrack::SetShowAndHideOnly(bool newValue)
			{
				showAndHideOnly = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227480
			bool ShowDisguiseActionHUDTrack::SetStealthConsumeInRange(bool newValue)
			{
				stealthConsumeInRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227490
			bool ShowDisguiseActionHUDTrack::SetStealthConsumeUsable(bool newValue)
			{
				stealthConsumeUsable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102274A0
			bool ShowDisguiseActionHUDTrack::SetPatsyUsable(bool newValue)
			{
				patsyUsable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102274B0
			bool ShowDisguiseActionHUDTrack::SetAirStrikeUsable(bool newValue)
			{
				airStrikeUsable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227BE0
			fight::Property* ShowDisguiseActionHUDTrack::GetProperty(int index)
			{
				return gShowDisguiseActionHUDTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227C00
			void ShowDisguiseActionHUDTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShowDisguiseActionHUDTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227C10
			ShowDisguiseActionHUDTrack::ShowDisguiseActionHUDTrack() : timeBegin(0.0f), timeEnd(-1.0f), airStrikeUsable(false), patsyUsable(false), showAndHideOnly(true), stealthConsumeInRange(false), stealthConsumeUsable(false)
			{
			}

			// FUNCTION: ENGINE 0x10227C60
			float ShowDisguiseActionHUDTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227C70
			float ShowDisguiseActionHUDTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227C80
			ShowDisguiseActionHUDTrack::~ShowDisguiseActionHUDTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShowDisguiseActionHUDTrack::RegisterProperties()
			{
				if (gShowDisguiseActionHUDTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShowDisguiseActionHUDTrack>("timeBegin", &ShowDisguiseActionHUDTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShowDisguiseActionHUDTrack>("timeEnd", &ShowDisguiseActionHUDTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ShowDisguiseActionHUDTrack>("showAndHideOnly", &ShowDisguiseActionHUDTrack::SetShowAndHideOnly);
					properties[2] = property;
					property = new fight::PropertyBool<ShowDisguiseActionHUDTrack>("stealthConsumeInRange", &ShowDisguiseActionHUDTrack::SetStealthConsumeInRange);
					properties[3] = property;
					property = new fight::PropertyBool<ShowDisguiseActionHUDTrack>("stealthConsumeUsable", &ShowDisguiseActionHUDTrack::SetStealthConsumeUsable);
					properties[4] = property;
					property = new fight::PropertyBool<ShowDisguiseActionHUDTrack>("patsyUsable", &ShowDisguiseActionHUDTrack::SetPatsyUsable);
					properties[5] = property;
					property = new fight::PropertyBool<ShowDisguiseActionHUDTrack>("airStrikeUsable", &ShowDisguiseActionHUDTrack::SetAirStrikeUsable);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gShowDisguiseActionHUDTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102293D0
			fight::TrackFactory* CreateShowDisguiseActionHUDTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShowDisguiseActionHUDTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A260
			void RegisterShowDisguiseActionHUDTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShowDisguiseActionHUDTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAddMarkerByKeyTrackProperties;  // 0x1125591C

			// FUNCTION: ENGINE 0x102274C0
			bool AddMarkerByKeyTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102274E0
			bool AddMarkerByKeyTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227500
			bool AddMarkerByKeyTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227510
			bool AddMarkerByKeyTrack::SetDisplayType(int newValue)
			{
				displayType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227520
			bool AddMarkerByKeyTrack::SetAnimType(int newValue)
			{
				animType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227530
			bool AddMarkerByKeyTrack::SetColor(int newValue)
			{
				color = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227C90
			fight::Property* AddMarkerByKeyTrack::GetProperty(int index)
			{
				return gAddMarkerByKeyTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227CB0
			void AddMarkerByKeyTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAddMarkerByKeyTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227CC0
			AddMarkerByKeyTrack::AddMarkerByKeyTrack() : timeBegin(0.0f), timeEnd(-1.0f), animType(0), color(0), type(0), displayType(0)
			{
			}

			// FUNCTION: ENGINE 0x10227D10
			float AddMarkerByKeyTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227D20
			float AddMarkerByKeyTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227D30
			AddMarkerByKeyTrack::~AddMarkerByKeyTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229B10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AddMarkerByKeyTrack::RegisterProperties()
			{
				if (gAddMarkerByKeyTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AddMarkerByKeyTrack>("timeBegin", &AddMarkerByKeyTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AddMarkerByKeyTrack>("timeEnd", &AddMarkerByKeyTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<AddMarkerByKeyTrack>("type", motion::gHaveIconTypeConditionTypeTable, motion::gHaveIconTypeConditionTypeCount, &AddMarkerByKeyTrack::SetType);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<AddMarkerByKeyTrack>("displayType", motion::gHUDMarkerTrackDisplayTypeTable, motion::gHUDMarkerTrackDisplayTypeCount, &AddMarkerByKeyTrack::SetDisplayType);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<AddMarkerByKeyTrack>("animType", motion::gHUDMarkerTrackAnimTypeTable, motion::gHUDMarkerTrackAnimTypeCount, &AddMarkerByKeyTrack::SetAnimType);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<AddMarkerByKeyTrack>("color", motion::gHUDMarkerTrackColorTable, motion::gHUDMarkerTrackColorCount, &AddMarkerByKeyTrack::SetColor);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gAddMarkerByKeyTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229400
			fight::TrackFactory* CreateAddMarkerByKeyTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AddMarkerByKeyTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A290
			void RegisterAddMarkerByKeyTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AddMarkerByKeyTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAddDiversionTrackProperties;  // 0x11255920

			// FUNCTION: ENGINE 0x10227540
			bool AddDiversionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227560
			bool AddDiversionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227580
			bool AddDiversionTrack::SetIntensity(float newValue)
			{
				intensity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102275A0
			bool AddDiversionTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102275C0
			bool AddDiversionTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227D40
			fight::Property* AddDiversionTrack::GetProperty(int index)
			{
				return gAddDiversionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227D60
			void AddDiversionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAddDiversionTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227D70
			AddDiversionTrack::AddDiversionTrack() : intensity(1.0f), maxDistance(2.0f), minDistance(2.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10227DD0
			float AddDiversionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227DE0
			float AddDiversionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227DF0
			AddDiversionTrack::~AddDiversionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229D30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AddDiversionTrack::RegisterProperties()
			{
				if (gAddDiversionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AddDiversionTrack>("timeBegin", &AddDiversionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AddDiversionTrack>("timeEnd", &AddDiversionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AddDiversionTrack>("intensity", &AddDiversionTrack::SetIntensity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AddDiversionTrack>("minDistance", &AddDiversionTrack::SetMinDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AddDiversionTrack>("maxDistance", &AddDiversionTrack::SetMaxDistance);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gAddDiversionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229430
			fight::TrackFactory* CreateAddDiversionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AddDiversionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A2C0
			void RegisterAddDiversionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AddDiversionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetUserTooltipTrackProperties;  // 0x11255924

			// FUNCTION: ENGINE 0x102275E0
			bool SetUserTooltipTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227EB0
			bool SetUserTooltipTrack::SetTooltip(const char* newValue)
			{
				tooltip = fight::ReplaceString(tooltip, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10227E00
			fight::Property* SetUserTooltipTrack::GetProperty(int index)
			{
				return gSetUserTooltipTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227E20
			void SetUserTooltipTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetUserTooltipTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227E30
			SetUserTooltipTrack::SetUserTooltipTrack() : tooltip(0), timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10227E60
			float SetUserTooltipTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227E70
			float SetUserTooltipTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10227E80
			SetUserTooltipTrack::~SetUserTooltipTrack()
			{
				delete[] tooltip;
			}

			// FUNCTION: ENGINE 0x10229EC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetUserTooltipTrack::RegisterProperties()
			{
				if (gSetUserTooltipTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetUserTooltipTrack>("timeBegin", &SetUserTooltipTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyString<SetUserTooltipTrack>("tooltip", &SetUserTooltipTrack::SetTooltip);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetUserTooltipTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229460
			fight::TrackFactory* CreateSetUserTooltipTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetUserTooltipTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A2F0
			void RegisterSetUserTooltipTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetUserTooltipTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAdjustHydraMovementTrackProperties;  // 0x11255928

			// FUNCTION: ENGINE 0x10227600
			bool AdjustHydraMovementTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227620
			bool AdjustHydraMovementTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227640
			bool AdjustHydraMovementTrack::SetAboveGround(bool newValue)
			{
				aboveGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10227EE0
			fight::Property* AdjustHydraMovementTrack::GetProperty(int index)
			{
				return gAdjustHydraMovementTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10227F00
			void AdjustHydraMovementTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAdjustHydraMovementTrackProperties);
			}

			// FUNCTION: ENGINE 0x10227F10
			AdjustHydraMovementTrack::AdjustHydraMovementTrack() : timeBegin(0.0f), timeEnd(-1.0f), aboveGround(true)
			{
			}

			// FUNCTION: ENGINE 0x10227F50
			float AdjustHydraMovementTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10227F60
			float AdjustHydraMovementTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10227F70
			AdjustHydraMovementTrack::~AdjustHydraMovementTrack()
			{
			}

			// FUNCTION: ENGINE 0x10229FA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AdjustHydraMovementTrack::RegisterProperties()
			{
				if (gAdjustHydraMovementTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AdjustHydraMovementTrack>("timeBegin", &AdjustHydraMovementTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AdjustHydraMovementTrack>("timeEnd", &AdjustHydraMovementTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<AdjustHydraMovementTrack>("aboveGround", &AdjustHydraMovementTrack::SetAboveGround);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAdjustHydraMovementTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10229490
			fight::TrackFactory* CreateAdjustHydraMovementTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AdjustHydraMovementTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022A320
			void RegisterAdjustHydraMovementTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AdjustHydraMovementTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101EA690
			// EQUIVALENT: instruction selection (ours clears eax before the compare); the same result (best 0.0 %)
			bool AddMarkerByKeyAction::Slot7(int arg, float value)
			{
				return link.object != 0;
			}

			// FUNCTION: ENGINE 0x101EA190
			// EQUIVALENT: instruction selection (ours clears eax before the compare); the same result (best 0.0 %)
			bool PlayDebugDialogAction::Slot7(int arg, float value)
			{
				return link.object != 0;
			}

			// FUNCTION: ENGINE 0x101EB900
			// EQUIVALENT: block order and constant selection (the engine puts the failure exit first and returns the constants in al, ours in eax); the same tests (best 17.9 %)
			bool AdjustHydraMovementAction::Slot5(int arg, float value)
			{
				return link.object != 0 && target.IsValid();
			}

			// FUNCTION: ENGINE 0x101E9A60
			// EQUIVALENT: block order and constant selection (the engine returns the failure first and the constants in al, ours in eax); the same tests (best 68.0 %)
			bool HelicopterStrafeModeAction::Slot5(int arg, float value)
			{
				return target.IsValid();
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101EA6A0
			ClearMarkersAction::ClearMarkersAction(ClearMarkersTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E9590
			ClearMarkersAction::~ClearMarkersAction()
			{
			}

			// FUNCTION: ENGINE 0x101E8CC0
			void ClearMarkersAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101EBB70
			fight::Action* ClearMarkersTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ClearMarkersAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EA0E0
			PlayDebugDialogAction::PlayDebugDialogAction(PlayDebugDialogTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E94A0
			PlayDebugDialogAction::~PlayDebugDialogAction()
			{
			}

			// FUNCTION: ENGINE 0x101E8C30
			bool PlayDebugDialogAction::Slot5(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101E8C40
			void PlayDebugDialogAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101EBA50
			fight::Action* PlayDebugDialogTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new PlayDebugDialogAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EB7A0
			HelicopterStrafeModeAction::HelicopterStrafeModeAction(HelicopterStrafeModeTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E9A30
			HelicopterStrafeModeAction::~HelicopterStrafeModeAction()
			{
			}

			// FUNCTION: ENGINE 0x101E9B20
			void HelicopterStrafeModeAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101EBD60
			fight::Action* HelicopterStrafeModeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new HelicopterStrafeModeAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EB3B0
			ShowDisguiseActionHUDAction::ShowDisguiseActionHUDAction(ShowDisguiseActionHUDTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E96F0
			ShowDisguiseActionHUDAction::~ShowDisguiseActionHUDAction()
			{
			}

			// FUNCTION: ENGINE 0x101EBBD0
			fight::Action* ShowDisguiseActionHUDTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ShowDisguiseActionHUDAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EA4B0
			AddMarkerByKeyAction::AddMarkerByKeyAction(AddMarkerByKeyTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E9540
			AddMarkerByKeyAction::~AddMarkerByKeyAction()
			{
			}

			// FUNCTION: ENGINE 0x101EBB10
			fight::Action* AddMarkerByKeyTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AddMarkerByKeyAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101E9FC0
			SetUserTooltipAction::SetUserTooltipAction(SetUserTooltipTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E9450
			SetUserTooltipAction::~SetUserTooltipAction()
			{
			}

			// FUNCTION: ENGINE 0x101E8C10
			bool SetUserTooltipAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101E8C20
			void SetUserTooltipAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101EB9F0
			fight::Action* SetUserTooltipTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SetUserTooltipAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EB850
			AdjustHydraMovementAction::AdjustHydraMovementAction(AdjustHydraMovementTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E9B50
			AdjustHydraMovementAction::~AdjustHydraMovementAction()
			{
			}

			// FUNCTION: ENGINE 0x101EBDC0
			fight::Action* AdjustHydraMovementTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AdjustHydraMovementAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101EA1A0
			DrawObjectDebugAction::DrawObjectDebugAction(DrawObjectDebugTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E94F0
			DrawObjectDebugAction::~DrawObjectDebugAction()
			{
			}

			// FUNCTION: ENGINE 0x101E8C50
			bool DrawObjectDebugAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101E8C60
			void DrawObjectDebugAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101EBAB0
			fight::Action* DrawObjectDebugTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DrawObjectDebugAction(this, handle, effect, listener);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<AbsoluteHeightCondition>;
			template class fight::PropertyFloatConstRange<AbsoluteHeightCondition>;
			template class fight::ConditionFactoryTemplate<AbsoluteHeightCondition>;
			template class fight::ConditionFactoryCasterTemplate<AbsoluteHeightCondition>;
			template class fight::ConditionFactoryTemplate<AreDisguiseActionsEnabledCondition>;
			template class fight::ConditionFactoryCasterTemplate<AreDisguiseActionsEnabledCondition>;
			template class fight::PropertyEnumConstList<IsDisguiseActionEnabledCondition>;
			template class fight::ConditionFactoryTemplate<IsDisguiseActionEnabledCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsDisguiseActionEnabledCondition>;
			template class fight::PropertyEnumConstList<DisguiseActionUsedTrack>;
			template class fight::TrackFactoryTemplate<DisguiseActionUsedTrack>;
			template class fight::TrackFactoryCasterTemplate<DisguiseActionUsedTrack>;
			template class fight::TrackFactoryTemplate<ClearMarkersTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearMarkersTrack>;
			template class fight::TrackFactoryTemplate<DumpAlertCharactersTrack>;
			template class fight::TrackFactoryCasterTemplate<DumpAlertCharactersTrack>;
			template class fight::PropertyFloatConstRange<PlayDebugDialogTrack>;
			template class fight::PropertyString<PlayDebugDialogTrack>;
			template class fight::TrackFactoryTemplate<PlayDebugDialogTrack>;
			template class fight::TrackFactoryCasterTemplate<PlayDebugDialogTrack>;
			template class fight::PropertyFloatConstRange<DrawObjectDebugTrack>;
			template class fight::PropertyColour<DrawObjectDebugTrack>;
			template class fight::PropertyVector<DrawObjectDebugTrack>;
			template class fight::PropertyNameList<DrawObjectDebugTrack>;
			template class fight::TrackFactoryTemplate<DrawObjectDebugTrack>;
			template class fight::TrackFactoryCasterTemplate<DrawObjectDebugTrack>;
			template class fight::PropertyFloatConstRange<HelicopterStrafeModeTrack>;
			template class fight::TrackFactoryTemplate<HelicopterStrafeModeTrack>;
			template class fight::TrackFactoryCasterTemplate<HelicopterStrafeModeTrack>;
			template class fight::PropertyFloatConstRange<ShowDisguiseActionHUDTrack>;
			template class fight::PropertyBool<ShowDisguiseActionHUDTrack>;
			template class fight::TrackFactoryTemplate<ShowDisguiseActionHUDTrack>;
			template class fight::TrackFactoryCasterTemplate<ShowDisguiseActionHUDTrack>;
			template class fight::PropertyFloatConstRange<AddMarkerByKeyTrack>;
			template class fight::PropertyEnumConstList<AddMarkerByKeyTrack>;
			template class fight::PropertyBitfieldConstList<AddMarkerByKeyTrack>;
			template class fight::TrackFactoryTemplate<AddMarkerByKeyTrack>;
			template class fight::TrackFactoryCasterTemplate<AddMarkerByKeyTrack>;
			template class fight::PropertyFloatConstRange<AddDiversionTrack>;
			template class fight::TrackFactoryTemplate<AddDiversionTrack>;
			template class fight::TrackFactoryCasterTemplate<AddDiversionTrack>;
			template class fight::PropertyFloatConstRange<SetUserTooltipTrack>;
			template class fight::PropertyString<SetUserTooltipTrack>;
			template class fight::TrackFactoryTemplate<SetUserTooltipTrack>;
			template class fight::TrackFactoryCasterTemplate<SetUserTooltipTrack>;
			template class fight::PropertyFloatConstRange<AdjustHydraMovementTrack>;
			template class fight::PropertyBool<AdjustHydraMovementTrack>;
			template class fight::TrackFactoryTemplate<AdjustHydraMovementTrack>;
			template class fight::TrackFactoryCasterTemplate<AdjustHydraMovementTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101EA040
// FUNCTION: ENGINE 0x101EA160
// FUNCTION: ENGINE 0x101EA220
// FUNCTION: ENGINE 0x101EA530
// FUNCTION: ENGINE 0x101EA720
// FUNCTION: ENGINE 0x101EB430
// FUNCTION: ENGINE 0x101EB820
// FUNCTION: ENGINE 0x101EB8D0
// FUNCTION: ENGINE 0x10227FA0
// FUNCTION: ENGINE 0x10227FD0
// FUNCTION: ENGINE 0x10228000
// FUNCTION: ENGINE 0x10228030
// FUNCTION: ENGINE 0x10228060
// FUNCTION: ENGINE 0x10228090
// FUNCTION: ENGINE 0x102280C0
// FUNCTION: ENGINE 0x102281A0
// FUNCTION: ENGINE 0x102281D0
// FUNCTION: ENGINE 0x10228200
// FUNCTION: ENGINE 0x10228230
// FUNCTION: ENGINE 0x10228260
// FUNCTION: ENGINE 0x10228290
// FUNCTION: ENGINE 0x102282C0
// FUNCTION: ENGINE 0x102282D0
// FUNCTION: ENGINE 0x10228300
// FUNCTION: ENGINE 0x10228310
// FUNCTION: ENGINE 0x10228340
// FUNCTION: ENGINE 0x10228370
// FUNCTION: ENGINE 0x10228390
// FUNCTION: ENGINE 0x102283E0
// FUNCTION: ENGINE 0x102283F0
// FUNCTION: ENGINE 0x10228420
// FUNCTION: ENGINE 0x10228430
// FUNCTION: ENGINE 0x10228460
// FUNCTION: ENGINE 0x10228470
// FUNCTION: ENGINE 0x102284A0
// FUNCTION: ENGINE 0x102284D0
// FUNCTION: ENGINE 0x102284F0
// FUNCTION: ENGINE 0x10228540
// FUNCTION: ENGINE 0x10228550
// FUNCTION: ENGINE 0x10228580
// FUNCTION: ENGINE 0x102285B0
// FUNCTION: ENGINE 0x102285D0
// FUNCTION: ENGINE 0x10228620
// FUNCTION: ENGINE 0x10228630
// FUNCTION: ENGINE 0x10228660
// FUNCTION: ENGINE 0x10228670
// FUNCTION: ENGINE 0x102286A0
// FUNCTION: ENGINE 0x102286B0
// FUNCTION: ENGINE 0x102286E0
// FUNCTION: ENGINE 0x102286F0
// FUNCTION: ENGINE 0x10228720
// FUNCTION: ENGINE 0x10228730
// FUNCTION: ENGINE 0x10228760
// FUNCTION: ENGINE 0x10228770
// FUNCTION: ENGINE 0x102287A0
// FUNCTION: ENGINE 0x102287B0
// FUNCTION: ENGINE 0x102287E0
// FUNCTION: ENGINE 0x102287F0
// FUNCTION: ENGINE 0x10228820
// FUNCTION: ENGINE 0x10228850
// FUNCTION: ENGINE 0x10228890
// FUNCTION: ENGINE 0x102288A0
// FUNCTION: ENGINE 0x102288D0
// FUNCTION: ENGINE 0x102288F0
// FUNCTION: ENGINE 0x10228900
// FUNCTION: ENGINE 0x10228930
// FUNCTION: ENGINE 0x10228960
// FUNCTION: ENGINE 0x10228970
// FUNCTION: ENGINE 0x102289B0
// FUNCTION: ENGINE 0x102289C0
// FUNCTION: ENGINE 0x102289F0
// FUNCTION: ENGINE 0x10228A10
// FUNCTION: ENGINE 0x10228A20
// FUNCTION: ENGINE 0x10228A60
// FUNCTION: ENGINE 0x10228A70
// FUNCTION: ENGINE 0x10228AA0
// FUNCTION: ENGINE 0x10228AC0
// FUNCTION: ENGINE 0x10228AD0
// FUNCTION: ENGINE 0x10228B00
// FUNCTION: ENGINE 0x10228B30
// FUNCTION: ENGINE 0x10228B40
// FUNCTION: ENGINE 0x10228B70
// FUNCTION: ENGINE 0x10228B90
// FUNCTION: ENGINE 0x10228BA0
// FUNCTION: ENGINE 0x10228BD0
// FUNCTION: ENGINE 0x10228C00
// FUNCTION: ENGINE 0x10228C10
// FUNCTION: ENGINE 0x10228C40
// FUNCTION: ENGINE 0x10228C60
// FUNCTION: ENGINE 0x10228C70
// FUNCTION: ENGINE 0x10228CA0
// FUNCTION: ENGINE 0x10228CC0
// FUNCTION: ENGINE 0x10228CD0
// FUNCTION: ENGINE 0x10228D00
// FUNCTION: ENGINE 0x10228D30
// FUNCTION: ENGINE 0x10228D40
// FUNCTION: ENGINE 0x10228D70
// FUNCTION: ENGINE 0x10228DA0
// FUNCTION: ENGINE 0x10228DB0
// FUNCTION: ENGINE 0x10228DE0
// FUNCTION: ENGINE 0x10228E00
// FUNCTION: ENGINE 0x10228E10
// FUNCTION: ENGINE 0x10228E40
// FUNCTION: ENGINE 0x10228E70
// FUNCTION: ENGINE 0x10228E80
// FUNCTION: ENGINE 0x10228EC0
// FUNCTION: ENGINE 0x10228ED0
// FUNCTION: ENGINE 0x10228F00
// FUNCTION: ENGINE 0x10228F20
// FUNCTION: ENGINE 0x10228F30
// FUNCTION: ENGINE 0x10228F70
// FUNCTION: ENGINE 0x10228F80
// FUNCTION: ENGINE 0x10228FA0
// FUNCTION: ENGINE 0x10228FB0
// FUNCTION: ENGINE 0x10229010
// FUNCTION: ENGINE 0x10229040
// FUNCTION: ENGINE 0x10229070
// FUNCTION: ENGINE 0x10229080
// FUNCTION: ENGINE 0x102290B0
// FUNCTION: ENGINE 0x102290E0
// FUNCTION: ENGINE 0x102290F0
// FUNCTION: ENGINE 0x10229120
// FUNCTION: ENGINE 0x10229140
// FUNCTION: ENGINE 0x10229150
// FUNCTION: ENGINE 0x10229180
// FUNCTION: ENGINE 0x102291B0
// FUNCTION: ENGINE 0x102291C0
// FUNCTION: ENGINE 0x102291F0
// FUNCTION: ENGINE 0x10229210
// FUNCTION: ENGINE 0x1022A350
// FUNCTION: ENGINE 0x1022A380
// FUNCTION: ENGINE 0x1022A3A0
// FUNCTION: ENGINE 0x1022A3B0
// FUNCTION: ENGINE 0x1022A3E0
// FUNCTION: ENGINE 0x1022A400
// FUNCTION: ENGINE 0x1022A430
// FUNCTION: ENGINE 0x1022A450
// FUNCTION: ENGINE 0x1022A480
// FUNCTION: ENGINE 0x1022A4A0
// FUNCTION: ENGINE 0x1022A4D0
// FUNCTION: ENGINE 0x1022A4F0
// FUNCTION: ENGINE 0x1022A520
// FUNCTION: ENGINE 0x1022A540
// FUNCTION: ENGINE 0x1022A570
// FUNCTION: ENGINE 0x1022A590
// FUNCTION: ENGINE 0x1022A5C0
// FUNCTION: ENGINE 0x1022A5E0
// FUNCTION: ENGINE 0x1022A610
// FUNCTION: ENGINE 0x1022A630
// FUNCTION: ENGINE 0x1022A660
// FUNCTION: ENGINE 0x1022A680
// FUNCTION: ENGINE 0x1022A6B0
// FUNCTION: ENGINE 0x1022A8A0
// FUNCTION: ENGINE 0x1022A8F0
// FUNCTION: ENGINE 0x1022A940
// FUNCTION: ENGINE 0x1022A990
// FUNCTION: ENGINE 0x1022A9E0
// FUNCTION: ENGINE 0x1022AA30
// FUNCTION: ENGINE 0x1022AA80
// FUNCTION: ENGINE 0x1022AAD0
// FUNCTION: ENGINE 0x1022AB20
// FUNCTION: ENGINE 0x1022AB70
// FUNCTION: ENGINE 0x1022ABC0
// FUNCTION: ENGINE 0x1022ABF0
// FUNCTION: ENGINE 0x1022AC10
