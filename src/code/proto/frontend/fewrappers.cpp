// The script method wrappers of the front end and head-up display classes of proto (GameFEManager, GameFEControllerManager,
// FrontEndState, the marker and mission objective managers, the head-up display elements ...): the units that register
// methods of these classes with the script context instantiate engine::Function's Method and Closure templates for their
// signatures. The classes themselves are other files'; they are declared here as far as the signatures need them (the
// enumerations the arguments name are nested in classes, which the mangled names of the instances spell). The classes with
// several bases have method pointers of two words, which the declarations below ask for.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/vector.h"

namespace proto
{
	enum KBActionController
	{
		KBActionControllerFirst
	};
	enum KBControlScheme
	{
		KBControlSchemeFirst
	};
	class FEBlackFade
	{
	};
	class FECellManager
	{
	};
	class FECredits
	{
	};
	class FEHUDTypewriter
	{
	};
	class FEHudCombatConclusion
	{
	};
	class FEHudEventPopup
	{
	};
	class FEHudKeyCard
	{
	};
	class FEHudMeterBase0
	{
	};
	class FEHudMeterBase1
	{
	};
	class FEHudMeter : public FEHudMeterBase0, public FEHudMeterBase1
	{
	public:
		enum EBarColors
		{
			EBarColorsFirst
		};
		enum EIcons
		{
			EIconsFirst
		};
		enum EPositions
		{
			EPositionsFirst
		};
	};
	class FEHudMiniMap;
	class FEHudMissionPopup
	{
	};
	class FEHudOpportunityEventPopup
	{
	};
	class FEHudPopup
	{
	};
	class FEHudPowers;
	class FEHudScreen
	{
	};
	class FEHudTextLog
	{
	};
	class FEMarker
	{
	public:
		enum DisplayLayer
		{
			DisplayLayerFirst
		};
		enum DisplayType
		{
			DisplayTypeFirst
		};
		enum IconType
		{
			IconTypeFirst
		};
		enum MarkerCallerType
		{
			MarkerCallerTypeFirst
		};
		enum MarkerColour
		{
			MarkerColourFirst
		};
	};
	class FrontEndState;
	class GameFEControllerManager;
	class GameFEManager
	{
	};
	class HUDState
	{
	public:
		enum EAnimType
		{
			EAnimTypeFirst
		};
	};
	class MarkerManager
	{
	};
	class MissionObjectivesManager
	{
	public:
		enum MissionObjectivesStatus
		{
			MissionObjectivesStatusFirst
		};
	};
	class StaticMarkerFilter
	{
	};
}

template class Method0<proto::FEBlackFade, void>;
template class Closure0<proto::FEBlackFade, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEBlackFade, void>(const char*,
	proto::FEBlackFade*, void (proto::FEBlackFade::*)());

template class Method1<proto::FEBlackFade, void, bool>;
template class Closure1<proto::FEBlackFade, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEBlackFade, void, bool>(const char*,
	proto::FEBlackFade*, void (proto::FEBlackFade::*)(bool));

template class Method0<proto::FEBlackFade, bool>;
template class Closure0<proto::FEBlackFade, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEBlackFade, bool>(const char*,
	proto::FEBlackFade*, bool (proto::FEBlackFade::*)());

template class Method1<proto::FEBlackFade, bool, bool>;
template class Closure1<proto::FEBlackFade, bool, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEBlackFade, bool, bool>(const char*,
	proto::FEBlackFade*, bool (proto::FEBlackFade::*)(bool));

template class Method0<proto::FECellManager, unsigned int>;
template class Closure0<proto::FECellManager, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FECellManager, unsigned int>(const char*,
	proto::FECellManager*, unsigned int (proto::FECellManager::*)());

template class Method0<proto::FECredits, void>;
template class Closure0<proto::FECredits, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FECredits, void>(const char*,
	proto::FECredits*, void (proto::FECredits::*)());

template class Method1<proto::FECredits, bool, bool>;
template class Closure1<proto::FECredits, bool, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FECredits, bool, bool>(const char*,
	proto::FECredits*, bool (proto::FECredits::*)(bool));

template class Method1<proto::FECredits, const char*, int>;
template class Closure1<proto::FECredits, const char*, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FECredits, const char*, int>(const char*,
	proto::FECredits*, const char* (proto::FECredits::*)(int));

template class Method0<proto::GameFEManager, void>;
template class Closure0<proto::GameFEManager, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)());

template class Method1<proto::GameFEManager, void, bool>;
template class Closure1<proto::GameFEManager, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, bool>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(bool));

template class Method0<proto::GameFEManager, bool>;
template class Closure0<proto::GameFEManager, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, bool>(const char*,
	proto::GameFEManager*, bool (proto::GameFEManager::*)());

template class Method1<proto::GameFEManager, const char*, const char*>;
template class Closure1<proto::GameFEManager, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, const char*, const char*>(const char*,
	proto::GameFEManager*, const char* (proto::GameFEManager::*)(const char*));

template class Method1<proto::GameFEManager, bool, const char*>;
template class Closure1<proto::GameFEManager, bool, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, bool, const char*>(const char*,
	proto::GameFEManager*, bool (proto::GameFEManager::*)(const char*));

template class Method2<proto::GameFEManager, void, const char*, const char*>;
template class Closure2<proto::GameFEManager, void, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, const char*, const char*>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(const char*, const char*));

template class Method1<proto::GameFEManager, void, const char*>;
template class Closure1<proto::GameFEManager, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, const char*>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(const char*));

template class Method4<proto::GameFEManager, void, const char*, const char*, const char*, const char*>;
template class Closure4<proto::GameFEManager, void, const char*, const char*, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, const char*, const char*, const char*, const char*>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(const char*, const char*, const char*, const char*));

template class Method6<proto::GameFEManager, void, const char*, const char*, const char*, const char*, const char*, const char*>;
template class Closure6<proto::GameFEManager, void, const char*, const char*, const char*, const char*, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, const char*, const char*, const char*, const char*, const char*, const char*>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(const char*, const char*, const char*, const char*, const char*, const char*));

template class Method1<proto::GameFEManager, void, unsigned int>;
template class Closure1<proto::GameFEManager, void, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, unsigned int>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(unsigned int));

template class Method3<proto::GameFEManager, void, int, int, const char*>;
template class Closure3<proto::GameFEManager, void, int, int, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, int, int, const char*>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(int, int, const char*));

template class Method3<proto::GameFEManager, bool, const char*, const char*, const char*>;
template class Closure3<proto::GameFEManager, bool, const char*, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, bool, const char*, const char*, const char*>(const char*,
	proto::GameFEManager*, bool (proto::GameFEManager::*)(const char*, const char*, const char*));

template class Method4<proto::GameFEManager, void, float, float, float, float>;
template class Closure4<proto::GameFEManager, void, float, float, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, float, float, float, float>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(float, float, float, float));

template class Method2<proto::GameFEManager, void, float, float>;
template class Closure2<proto::GameFEManager, void, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, void, float, float>(const char*,
	proto::GameFEManager*, void (proto::GameFEManager::*)(float, float));

template class Method1<proto::GameFEManager, bool, bool>;
template class Closure1<proto::GameFEManager, bool, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, bool, bool>(const char*,
	proto::GameFEManager*, bool (proto::GameFEManager::*)(bool));

template class Method0<proto::GameFEManager, unsigned int>;
template class Closure0<proto::GameFEManager, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, unsigned int>(const char*,
	proto::GameFEManager*, unsigned int (proto::GameFEManager::*)());

template class Method0<proto::GameFEManager, const char*>;
template class Closure0<proto::GameFEManager, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEManager, const char*>(const char*,
	proto::GameFEManager*, const char* (proto::GameFEManager::*)());

template class Method0<proto::MarkerManager, void>;
template class Closure0<proto::MarkerManager, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)());

template class Method5<proto::MarkerManager, bool, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::DisplayType, proto::FEMarker::MarkerCallerType, const char*>;
template class Closure5<proto::MarkerManager, bool, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::DisplayType, proto::FEMarker::MarkerCallerType, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, bool, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::DisplayType, proto::FEMarker::MarkerCallerType, const char*>(const char*,
	proto::MarkerManager*, bool (proto::MarkerManager::*)(engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::DisplayType, proto::FEMarker::MarkerCallerType, const char*));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::IconType>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::IconType>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::IconType>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, proto::FEMarker::IconType));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerCallerType>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerCallerType>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerCallerType>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, proto::FEMarker::MarkerCallerType));

template class Method1<proto::MarkerManager, void, proto::FEMarker::MarkerCallerType>;
template class Closure1<proto::MarkerManager, void, proto::FEMarker::MarkerCallerType>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, proto::FEMarker::MarkerCallerType>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(proto::FEMarker::MarkerCallerType));

template class Method3<proto::MarkerManager, void, engine::LuaGOH, float, float>;
template class Closure3<proto::MarkerManager, void, engine::LuaGOH, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, float, float>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, float, float));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerColour>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerColour>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::MarkerColour>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, proto::FEMarker::MarkerColour));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, proto::HUDState::EAnimType>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, proto::HUDState::EAnimType>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, proto::HUDState::EAnimType>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, proto::HUDState::EAnimType));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, float>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, float>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, float));

template class Method2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::DisplayLayer>;
template class Closure2<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::DisplayLayer>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, engine::LuaGOH, proto::FEMarker::DisplayLayer>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(engine::LuaGOH, proto::FEMarker::DisplayLayer));

template class Method2<proto::MarkerManager, void, bool, math::Vector>;
template class Closure2<proto::MarkerManager, void, bool, math::Vector>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, bool, math::Vector>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(bool, math::Vector));

template class Method1<proto::MarkerManager, void, float>;
template class Closure1<proto::MarkerManager, void, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, void, float>(const char*,
	proto::MarkerManager*, void (proto::MarkerManager::*)(float));

template class Method1<proto::MarkerManager, const char*, int>;
template class Closure1<proto::MarkerManager, const char*, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, const char*, int>(const char*,
	proto::MarkerManager*, const char* (proto::MarkerManager::*)(int));

template class Method4<proto::MarkerManager, int, float, float, bool, bool>;
template class Closure4<proto::MarkerManager, int, float, float, bool, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, int, float, float, bool, bool>(const char*,
	proto::MarkerManager*, int (proto::MarkerManager::*)(float, float, bool, bool));

template class Method1<proto::MarkerManager, float, int>;
template class Closure1<proto::MarkerManager, float, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, float, int>(const char*,
	proto::MarkerManager*, float (proto::MarkerManager::*)(int));

template class Method1<proto::MarkerManager, proto::FEMarker::MarkerCallerType, engine::LuaGOH>;
template class Closure1<proto::MarkerManager, proto::FEMarker::MarkerCallerType, engine::LuaGOH>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, proto::FEMarker::MarkerCallerType, engine::LuaGOH>(const char*,
	proto::MarkerManager*, proto::FEMarker::MarkerCallerType (proto::MarkerManager::*)(engine::LuaGOH));

template class Method0<proto::MarkerManager, unsigned int>;
template class Closure0<proto::MarkerManager, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, unsigned int>(const char*,
	proto::MarkerManager*, unsigned int (proto::MarkerManager::*)());

template class Method1<proto::MarkerManager, proto::FEMarker::IconType, int>;
template class Closure1<proto::MarkerManager, proto::FEMarker::IconType, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, proto::FEMarker::IconType, int>(const char*,
	proto::MarkerManager*, proto::FEMarker::IconType (proto::MarkerManager::*)(int));

template class Method2<proto::MarkerManager, unsigned int, int, bool>;
template class Closure2<proto::MarkerManager, unsigned int, int, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::MarkerManager, unsigned int, int, bool>(const char*,
	proto::MarkerManager*, unsigned int (proto::MarkerManager::*)(int, bool));

template class Method0<proto::MissionObjectivesManager, void>;
template class Closure0<proto::MissionObjectivesManager, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)());

template class Method2<proto::MissionObjectivesManager, void, const char*, const char*>;
template class Closure2<proto::MissionObjectivesManager, void, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*, const char*>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*, const char*));

template class Method3<proto::MissionObjectivesManager, void, const char*, const char*, unsigned int>;
template class Closure3<proto::MissionObjectivesManager, void, const char*, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*, const char*, unsigned int>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*, const char*, unsigned int));

template class Method1<proto::MissionObjectivesManager, void, const char*>;
template class Closure1<proto::MissionObjectivesManager, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*));

template class Method2<proto::MissionObjectivesManager, void, const char*, proto::FEMarker::IconType>;
template class Closure2<proto::MissionObjectivesManager, void, const char*, proto::FEMarker::IconType>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*, proto::FEMarker::IconType>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*, proto::FEMarker::IconType));

template class Method2<proto::MissionObjectivesManager, void, const char*, unsigned int>;
template class Closure2<proto::MissionObjectivesManager, void, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*, unsigned int>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*, unsigned int));

template class Method2<proto::MissionObjectivesManager, void, const char*, proto::MissionObjectivesManager::MissionObjectivesStatus>;
template class Closure2<proto::MissionObjectivesManager, void, const char*, proto::MissionObjectivesManager::MissionObjectivesStatus>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, void, const char*, proto::MissionObjectivesManager::MissionObjectivesStatus>(const char*,
	proto::MissionObjectivesManager*, void (proto::MissionObjectivesManager::*)(const char*, proto::MissionObjectivesManager::MissionObjectivesStatus));

template class Method1<proto::MissionObjectivesManager, const char*, bool>;
template class Closure1<proto::MissionObjectivesManager, const char*, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::MissionObjectivesManager, const char*, bool>(const char*,
	proto::MissionObjectivesManager*, const char* (proto::MissionObjectivesManager::*)(bool));

template class Method0<proto::StaticMarkerFilter, void>;
template class Closure0<proto::StaticMarkerFilter, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::StaticMarkerFilter, void>(const char*,
	proto::StaticMarkerFilter*, void (proto::StaticMarkerFilter::*)());

template class Method8<proto::StaticMarkerFilter, unsigned int, math::Vector, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, proto::FEMarker::MarkerColour, float, float, float, const char*>;
template class Closure8<proto::StaticMarkerFilter, unsigned int, math::Vector, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, proto::FEMarker::MarkerColour, float, float, float, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::StaticMarkerFilter, unsigned int, math::Vector, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, proto::FEMarker::MarkerColour, float, float, float, const char*>(const char*,
	proto::StaticMarkerFilter*, unsigned int (proto::StaticMarkerFilter::*)(math::Vector, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, proto::FEMarker::MarkerColour, float, float, float, const char*));

template class Method5<proto::StaticMarkerFilter, unsigned int, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, float, const char*>;
template class Closure5<proto::StaticMarkerFilter, unsigned int, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, float, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::StaticMarkerFilter, unsigned int, engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, float, const char*>(const char*,
	proto::StaticMarkerFilter*, unsigned int (proto::StaticMarkerFilter::*)(engine::LuaGOH, proto::FEMarker::IconType, proto::FEMarker::MarkerCallerType, float, const char*));

template class Method1<proto::StaticMarkerFilter, void, unsigned int>;
template class Closure1<proto::StaticMarkerFilter, void, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::StaticMarkerFilter, void, unsigned int>(const char*,
	proto::StaticMarkerFilter*, void (proto::StaticMarkerFilter::*)(unsigned int));

template class Method0<proto::FEHudScreen, void>;
template class Closure0<proto::FEHudScreen, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudScreen, void>(const char*,
	proto::FEHudScreen*, void (proto::FEHudScreen::*)());

template class Method0<proto::FEHudScreen, int>;
template class Closure0<proto::FEHudScreen, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudScreen, int>(const char*,
	proto::FEHudScreen*, int (proto::FEHudScreen::*)());

template class Method1<proto::FEHudScreen, int, unsigned int>;
template class Closure1<proto::FEHudScreen, int, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudScreen, int, unsigned int>(const char*,
	proto::FEHudScreen*, int (proto::FEHudScreen::*)(unsigned int));

template class Method2<proto::FEHudScreen, void, unsigned int, unsigned int>;
template class Closure2<proto::FEHudScreen, void, unsigned int, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudScreen, void, unsigned int, unsigned int>(const char*,
	proto::FEHudScreen*, void (proto::FEHudScreen::*)(unsigned int, unsigned int));

template class Method0<proto::FEHudCombatConclusion, void>;
template class Closure0<proto::FEHudCombatConclusion, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudCombatConclusion, void>(const char*,
	proto::FEHudCombatConclusion*, void (proto::FEHudCombatConclusion::*)());

template class Method0<proto::FEHudEventPopup, bool>;
template class Closure0<proto::FEHudEventPopup, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudEventPopup, bool>(const char*,
	proto::FEHudEventPopup*, bool (proto::FEHudEventPopup::*)());

template class Method0<proto::FEHudKeyCard, void>;
template class Closure0<proto::FEHudKeyCard, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudKeyCard, void>(const char*,
	proto::FEHudKeyCard*, void (proto::FEHudKeyCard::*)());

template class Method0<proto::FEHudMissionPopup, void>;
template class Closure0<proto::FEHudMissionPopup, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMissionPopup, void>(const char*,
	proto::FEHudMissionPopup*, void (proto::FEHudMissionPopup::*)());

template class Method0<proto::FEHudOpportunityEventPopup, void>;
template class Closure0<proto::FEHudOpportunityEventPopup, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudOpportunityEventPopup, void>(const char*,
	proto::FEHudOpportunityEventPopup*, void (proto::FEHudOpportunityEventPopup::*)());

template class Method0<proto::FEHudPopup, void>;
template class Closure0<proto::FEHudPopup, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, void>(const char*,
	proto::FEHudPopup*, void (proto::FEHudPopup::*)());

template class Method2<proto::FEHudPopup, void, bool, const char*>;
template class Closure2<proto::FEHudPopup, void, bool, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, void, bool, const char*>(const char*,
	proto::FEHudPopup*, void (proto::FEHudPopup::*)(bool, const char*));

template class Method6<proto::FEHudPopup, void, bool, bool, const char*, const char*, const char*, const char*>;
template class Closure6<proto::FEHudPopup, void, bool, bool, const char*, const char*, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, void, bool, bool, const char*, const char*, const char*, const char*>(const char*,
	proto::FEHudPopup*, void (proto::FEHudPopup::*)(bool, bool, const char*, const char*, const char*, const char*));

template class Method2<proto::FEHudPopup, void, const char*, const char*>;
template class Closure2<proto::FEHudPopup, void, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, void, const char*, const char*>(const char*,
	proto::FEHudPopup*, void (proto::FEHudPopup::*)(const char*, const char*));

template class Method0<proto::FEHudPopup, bool>;
template class Closure0<proto::FEHudPopup, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, bool>(const char*,
	proto::FEHudPopup*, bool (proto::FEHudPopup::*)());

template class Method1<proto::FEHudPopup, void, bool>;
template class Closure1<proto::FEHudPopup, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPopup, void, bool>(const char*,
	proto::FEHudPopup*, void (proto::FEHudPopup::*)(bool));

template class Method0<proto::FEHudTextLog, void>;
template class Closure0<proto::FEHudTextLog, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudTextLog, void>(const char*,
	proto::FEHudTextLog*, void (proto::FEHudTextLog::*)());

template class Method1<proto::FEHudTextLog, void, const char*>;
template class Closure1<proto::FEHudTextLog, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudTextLog, void, const char*>(const char*,
	proto::FEHudTextLog*, void (proto::FEHudTextLog::*)(const char*));

template class Method2<proto::FEHudTextLog, void, const char*, bool>;
template class Closure2<proto::FEHudTextLog, void, const char*, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudTextLog, void, const char*, bool>(const char*,
	proto::FEHudTextLog*, void (proto::FEHudTextLog::*)(const char*, bool));

template class Method2<proto::FEHudTextLog, void, char*, char*>;
template class Closure2<proto::FEHudTextLog, void, char*, char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudTextLog, void, char*, char*>(const char*,
	proto::FEHudTextLog*, void (proto::FEHudTextLog::*)(char*, char*));

template class Method0<proto::FEHUDTypewriter, void>;
template class Closure0<proto::FEHUDTypewriter, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHUDTypewriter, void>(const char*,
	proto::FEHUDTypewriter*, void (proto::FEHUDTypewriter::*)());

template class Method7<proto::FEHUDTypewriter, void, const char*, float, float, float, const char*, float, const char*>;
template class Closure7<proto::FEHUDTypewriter, void, const char*, float, float, float, const char*, float, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHUDTypewriter, void, const char*, float, float, float, const char*, float, const char*>(const char*,
	proto::FEHUDTypewriter*, void (proto::FEHUDTypewriter::*)(const char*, float, float, float, const char*, float, const char*));

template class Method2<proto::FEHUDTypewriter, void, float, float>;
template class Closure2<proto::FEHUDTypewriter, void, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHUDTypewriter, void, float, float>(const char*,
	proto::FEHUDTypewriter*, void (proto::FEHUDTypewriter::*)(float, float));

template class Method0<proto::FEHUDTypewriter, bool>;
template class Closure0<proto::FEHUDTypewriter, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHUDTypewriter, bool>(const char*,
	proto::FEHUDTypewriter*, bool (proto::FEHUDTypewriter::*)());

#pragma pointers_to_members(full_generality, multiple_inheritance)

template class Method0<proto::GameFEControllerManager, void>;
template class Closure0<proto::GameFEControllerManager, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, void>(const char*,
	proto::GameFEControllerManager*, void (proto::GameFEControllerManager::*)());

template class Method2<proto::GameFEControllerManager, const char*, unsigned int, proto::KBActionController>;
template class Closure2<proto::GameFEControllerManager, const char*, unsigned int, proto::KBActionController>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, const char*, unsigned int, proto::KBActionController>(const char*,
	proto::GameFEControllerManager*, const char* (proto::GameFEControllerManager::*)(unsigned int, proto::KBActionController));

template class Method1<proto::GameFEControllerManager, int, bool>;
template class Closure1<proto::GameFEControllerManager, int, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, int, bool>(const char*,
	proto::GameFEControllerManager*, int (proto::GameFEControllerManager::*)(bool));

template class Method1<proto::GameFEControllerManager, int, int>;
template class Closure1<proto::GameFEControllerManager, int, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, int, int>(const char*,
	proto::GameFEControllerManager*, int (proto::GameFEControllerManager::*)(int));

template class Method1<proto::GameFEControllerManager, const char*, int>;
template class Closure1<proto::GameFEControllerManager, const char*, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, const char*, int>(const char*,
	proto::GameFEControllerManager*, const char* (proto::GameFEControllerManager::*)(int));

template class Method1<proto::GameFEControllerManager, bool, int>;
template class Closure1<proto::GameFEControllerManager, bool, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, bool, int>(const char*,
	proto::GameFEControllerManager*, bool (proto::GameFEControllerManager::*)(int));

template class Method0<proto::GameFEControllerManager, proto::KBControlScheme>;
template class Closure0<proto::GameFEControllerManager, proto::KBControlScheme>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, proto::KBControlScheme>(const char*,
	proto::GameFEControllerManager*, proto::KBControlScheme (proto::GameFEControllerManager::*)());

template class Method0<proto::GameFEControllerManager, bool>;
template class Closure0<proto::GameFEControllerManager, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, bool>(const char*,
	proto::GameFEControllerManager*, bool (proto::GameFEControllerManager::*)());

template class Method1<proto::GameFEControllerManager, void, int>;
template class Closure1<proto::GameFEControllerManager, void, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameFEControllerManager, void, int>(const char*,
	proto::GameFEControllerManager*, void (proto::GameFEControllerManager::*)(int));

template class Method0<proto::FEHudMiniMap, void>;
template class Closure0<proto::FEHudMiniMap, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMiniMap, void>(const char*,
	proto::FEHudMiniMap*, void (proto::FEHudMiniMap::*)());

template class Method0<proto::FEHudMiniMap, int>;
template class Closure0<proto::FEHudMiniMap, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMiniMap, int>(const char*,
	proto::FEHudMiniMap*, int (proto::FEHudMiniMap::*)());

template class Method1<proto::FEHudMiniMap, void, bool>;
template class Closure1<proto::FEHudMiniMap, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMiniMap, void, bool>(const char*,
	proto::FEHudMiniMap*, void (proto::FEHudMiniMap::*)(bool));

template class Method0<proto::FEHudPowers, bool>;
template class Closure0<proto::FEHudPowers, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudPowers, bool>(const char*,
	proto::FEHudPowers*, bool (proto::FEHudPowers::*)());

template class Method0<proto::FEHudMeter, void>;
template class Closure0<proto::FEHudMeter, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)());

template class Method8<proto::FEHudMeter, void, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, const char*, const char*, float, proto::FEHudMeter::EBarColors, proto::FEHudMeter::EBarColors>;
template class Closure8<proto::FEHudMeter, void, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, const char*, const char*, float, proto::FEHudMeter::EBarColors, proto::FEHudMeter::EBarColors>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, const char*, const char*, float, proto::FEHudMeter::EBarColors, proto::FEHudMeter::EBarColors>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, proto::FEHudMeter::EIcons, const char*, const char*, float, proto::FEHudMeter::EBarColors, proto::FEHudMeter::EBarColors));

template class Method2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EIcons>;
template class Closure2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EIcons>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EIcons>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EPositions, proto::FEHudMeter::EIcons));

template class Method2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, const char*>;
template class Closure2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, const char*>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EPositions, const char*));

template class Method1<proto::FEHudMeter, void, float>;
template class Closure1<proto::FEHudMeter, void, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, float>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(float));

template class Method2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, bool>;
template class Closure2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, bool>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EPositions, bool));

template class Method2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EBarColors>;
template class Closure2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EBarColors>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, proto::FEHudMeter::EBarColors>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EPositions, proto::FEHudMeter::EBarColors));

template class Method1<proto::FEHudMeter, void, bool>;
template class Closure1<proto::FEHudMeter, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, bool>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(bool));

template class Method2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, float>;
template class Closure2<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::FEHudMeter, void, proto::FEHudMeter::EPositions, float>(const char*,
	proto::FEHudMeter*, void (proto::FEHudMeter::*)(proto::FEHudMeter::EPositions, float));

template class Method0<proto::FrontEndState, void>;
template class Closure0<proto::FrontEndState, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, void>(const char*,
	proto::FrontEndState*, void (proto::FrontEndState::*)());

template class Method1<proto::FrontEndState, void, bool>;
template class Closure1<proto::FrontEndState, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, void, bool>(const char*,
	proto::FrontEndState*, void (proto::FrontEndState::*)(bool));

template class Method0<proto::FrontEndState, unsigned int>;
template class Closure0<proto::FrontEndState, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, unsigned int>(const char*,
	proto::FrontEndState*, unsigned int (proto::FrontEndState::*)());

template class Method1<proto::FrontEndState, const char*, unsigned int>;
template class Closure1<proto::FrontEndState, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, const char*, unsigned int>(const char*,
	proto::FrontEndState*, const char* (proto::FrontEndState::*)(unsigned int));

template class Method0<proto::FrontEndState, const char*>;
template class Closure0<proto::FrontEndState, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, const char*>(const char*,
	proto::FrontEndState*, const char* (proto::FrontEndState::*)());

template class Method0<proto::FrontEndState, bool>;
template class Closure0<proto::FrontEndState, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, bool>(const char*,
	proto::FrontEndState*, bool (proto::FrontEndState::*)());

template class Method1<proto::FrontEndState, void, const char*>;
template class Closure1<proto::FrontEndState, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FrontEndState, void, const char*>(const char*,
	proto::FrontEndState*, void (proto::FrontEndState::*)(const char*));


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104AA980
// FUNCTION: ENGINE 0x104AA9D0
// FUNCTION: ENGINE 0x104AABB0
// FUNCTION: ENGINE 0x104AAC10
// FUNCTION: ENGINE 0x104AAC30
// FUNCTION: ENGINE 0x104AAC90
// FUNCTION: ENGINE 0x104AACB0
// FUNCTION: ENGINE 0x104AACD0
// FUNCTION: ENGINE 0x104AAD20
// FUNCTION: ENGINE 0x104AAD40
// FUNCTION: ENGINE 0x104AAD60
// FUNCTION: ENGINE 0x104AADC0
// FUNCTION: ENGINE 0x104AADF0
// FUNCTION: ENGINE 0x104AB2F0
// FUNCTION: ENGINE 0x104AB380
// FUNCTION: ENGINE 0x104AB3F0
// FUNCTION: ENGINE 0x104AB410
// FUNCTION: ENGINE 0x104AB420
// FUNCTION: ENGINE 0x104AB480
// FUNCTION: ENGINE 0x104AB4A0
// FUNCTION: ENGINE 0x104AB510
// FUNCTION: ENGINE 0x104ABB10
// FUNCTION: ENGINE 0x104ABB70
// FUNCTION: ENGINE 0x104ABC00
// FUNCTION: ENGINE 0x104AC790
// FUNCTION: ENGINE 0x104AC7E0
// FUNCTION: ENGINE 0x104AC800
// FUNCTION: ENGINE 0x104AC8C0
// FUNCTION: ENGINE 0x104AC920
// FUNCTION: ENGINE 0x104AC980
// FUNCTION: ENGINE 0x104AD540
// FUNCTION: ENGINE 0x104AD590
// FUNCTION: ENGINE 0x104AED10
// FUNCTION: ENGINE 0x104AED70
// FUNCTION: ENGINE 0x104AED90
// FUNCTION: ENGINE 0x104AEE00
// FUNCTION: ENGINE 0x104AEE30
// FUNCTION: ENGINE 0x104AEE70
// FUNCTION: ENGINE 0x104AEED0
// FUNCTION: ENGINE 0x104AEF10
// FUNCTION: ENGINE 0x104AEF50
// FUNCTION: ENGINE 0x104AEFB0
// FUNCTION: ENGINE 0x104AEFE0
// FUNCTION: ENGINE 0x104AF010
// FUNCTION: ENGINE 0x104AF070
// FUNCTION: ENGINE 0x104AF0A0
// FUNCTION: ENGINE 0x104AF0D0
// FUNCTION: ENGINE 0x104AF130
// FUNCTION: ENGINE 0x104AF160
// FUNCTION: ENGINE 0x104AF190
// FUNCTION: ENGINE 0x104AF1E0
// FUNCTION: ENGINE 0x104AF200
// FUNCTION: ENGINE 0x104AF230
// FUNCTION: ENGINE 0x104AF280
// FUNCTION: ENGINE 0x104AF2A0
// FUNCTION: ENGINE 0x104AF2D0
// FUNCTION: ENGINE 0x104AF330
// FUNCTION: ENGINE 0x104AF350
// FUNCTION: ENGINE 0x104AF3A0
// FUNCTION: ENGINE 0x104AF440
// FUNCTION: ENGINE 0x104AF480
// FUNCTION: ENGINE 0x104AF4C0
// FUNCTION: ENGINE 0x104AF4E0
// FUNCTION: ENGINE 0x104AF550
// FUNCTION: ENGINE 0x104AF590
// FUNCTION: ENGINE 0x104AF600
// FUNCTION: ENGINE 0x104AF630
// FUNCTION: ENGINE 0x104AF6A0
// FUNCTION: ENGINE 0x104AF6D0
// FUNCTION: ENGINE 0x104AF740
// FUNCTION: ENGINE 0x104AF770
// FUNCTION: ENGINE 0x104AF7D0
// FUNCTION: ENGINE 0x104AF7F0
// FUNCTION: ENGINE 0x104AF850
// FUNCTION: ENGINE 0x104AF870
// FUNCTION: ENGINE 0x104AF8E0
// FUNCTION: ENGINE 0x104AF900
// FUNCTION: ENGINE 0x104AF970
// FUNCTION: ENGINE 0x104AF9D0
// FUNCTION: ENGINE 0x104AFA30
// FUNCTION: ENGINE 0x104AFA90
// FUNCTION: ENGINE 0x104AFAF0
// FUNCTION: ENGINE 0x104AFB90
// FUNCTION: ENGINE 0x104AFC30
// FUNCTION: ENGINE 0x104B0230
// FUNCTION: ENGINE 0x104B0280
// FUNCTION: ENGINE 0x104B0320
// FUNCTION: ENGINE 0x104B0380
// FUNCTION: ENGINE 0x104B03A0
// FUNCTION: ENGINE 0x104B0400
// FUNCTION: ENGINE 0x104B0430
// FUNCTION: ENGINE 0x104B0460
// FUNCTION: ENGINE 0x104B04C0
// FUNCTION: ENGINE 0x104B04E0
// FUNCTION: ENGINE 0x104B0510
// FUNCTION: ENGINE 0x104B05A0
// FUNCTION: ENGINE 0x104B05B0
// FUNCTION: ENGINE 0x104B0620
// FUNCTION: ENGINE 0x104B0650
// FUNCTION: ENGINE 0x104B06C0
// FUNCTION: ENGINE 0x104B06F0
// FUNCTION: ENGINE 0x104B0750
// FUNCTION: ENGINE 0x104B1800
// FUNCTION: ENGINE 0x104B1850
// FUNCTION: ENGINE 0x104B2580
// FUNCTION: ENGINE 0x104B25E0
// FUNCTION: ENGINE 0x104B2600
// FUNCTION: ENGINE 0x104B2660
// FUNCTION: ENGINE 0x104B2680
// FUNCTION: ENGINE 0x104B26A0
// FUNCTION: ENGINE 0x104B26F0
// FUNCTION: ENGINE 0x104B2710
// FUNCTION: ENGINE 0x104B2730
// FUNCTION: ENGINE 0x104B2790
// FUNCTION: ENGINE 0x104B27B0
// FUNCTION: ENGINE 0x104B27E0
// FUNCTION: ENGINE 0x104B2840
// FUNCTION: ENGINE 0x104B2860
// FUNCTION: ENGINE 0x104B2890
// FUNCTION: ENGINE 0x104B2900
// FUNCTION: ENGINE 0x104B2920
// FUNCTION: ENGINE 0x104B2940
// FUNCTION: ENGINE 0x104B29A0
// FUNCTION: ENGINE 0x104B29C0
// FUNCTION: ENGINE 0x104B29E0
// FUNCTION: ENGINE 0x104B2A70
// FUNCTION: ENGINE 0x104B2AA0
// FUNCTION: ENGINE 0x104B2AE0
// FUNCTION: ENGINE 0x104B2BA0
// FUNCTION: ENGINE 0x104B2BF0
// FUNCTION: ENGINE 0x104B2C40
// FUNCTION: ENGINE 0x104B2CA0
// FUNCTION: ENGINE 0x104B2CC0
// FUNCTION: ENGINE 0x104B2CE0
// FUNCTION: ENGINE 0x104B2D60
// FUNCTION: ENGINE 0x104B2D80
// FUNCTION: ENGINE 0x104B2DB0
// FUNCTION: ENGINE 0x104B2E30
// FUNCTION: ENGINE 0x104B2E60
// FUNCTION: ENGINE 0x104B2E90
// FUNCTION: ENGINE 0x104B2F20
// FUNCTION: ENGINE 0x104B2F60
// FUNCTION: ENGINE 0x104B2FA0
// FUNCTION: ENGINE 0x104B3010
// FUNCTION: ENGINE 0x104B3040
// FUNCTION: ENGINE 0x104B3070
// FUNCTION: ENGINE 0x104B30D0
// FUNCTION: ENGINE 0x104B3100
// FUNCTION: ENGINE 0x104B3130
// FUNCTION: ENGINE 0x104B3180
// FUNCTION: ENGINE 0x104B31A0
// FUNCTION: ENGINE 0x104B31C0
// FUNCTION: ENGINE 0x104B3210
// FUNCTION: ENGINE 0x104B3230
// FUNCTION: ENGINE 0x104B3290
// FUNCTION: ENGINE 0x104B3320
// FUNCTION: ENGINE 0x104B3390
// FUNCTION: ENGINE 0x104B33B0
// FUNCTION: ENGINE 0x104B3410
// FUNCTION: ENGINE 0x104B3430
// FUNCTION: ENGINE 0x104B34A0
// FUNCTION: ENGINE 0x104B34D0
// FUNCTION: ENGINE 0x104B3540
// FUNCTION: ENGINE 0x104B3570
// FUNCTION: ENGINE 0x104B35A0
// FUNCTION: ENGINE 0x104B35C0
// FUNCTION: ENGINE 0x104B3630
// FUNCTION: ENGINE 0x104B3650
// FUNCTION: ENGINE 0x104B3680
// FUNCTION: ENGINE 0x104B36C0
// FUNCTION: ENGINE 0x104B36D0
// FUNCTION: ENGINE 0x104B3700
// FUNCTION: ENGINE 0x104B3750
// FUNCTION: ENGINE 0x104B37C0
// FUNCTION: ENGINE 0x104B37E0
// FUNCTION: ENGINE 0x104B3810
// FUNCTION: ENGINE 0x104B3840
// FUNCTION: ENGINE 0x104B3870
// FUNCTION: ENGINE 0x104B38B0
// FUNCTION: ENGINE 0x104B38E0
// FUNCTION: ENGINE 0x104B3920
// FUNCTION: ENGINE 0x104B3950
// FUNCTION: ENGINE 0x104B3980
// FUNCTION: ENGINE 0x104B39F0
// FUNCTION: ENGINE 0x104B3A20
// FUNCTION: ENGINE 0x104B3A80
// FUNCTION: ENGINE 0x104B3AA0
// FUNCTION: ENGINE 0x104B3B00
// FUNCTION: ENGINE 0x104B3B20
// FUNCTION: ENGINE 0x104B3B80
// FUNCTION: ENGINE 0x104B3C10
// FUNCTION: ENGINE 0x104B3C70
// FUNCTION: ENGINE 0x104B3CD0
// FUNCTION: ENGINE 0x104B3D40
// FUNCTION: ENGINE 0x104B3DA0
// FUNCTION: ENGINE 0x104B3E10
// FUNCTION: ENGINE 0x104B3E80
// FUNCTION: ENGINE 0x104B3EE0
// FUNCTION: ENGINE 0x104B3F50
// FUNCTION: ENGINE 0x104B3FC0
// FUNCTION: ENGINE 0x104B4030
// FUNCTION: ENGINE 0x104B40A0
// FUNCTION: ENGINE 0x104B4100
// FUNCTION: ENGINE 0x104B4190
// FUNCTION: ENGINE 0x104B5A90
// FUNCTION: ENGINE 0x104B5AE0
// FUNCTION: ENGINE 0x104B6A10
// FUNCTION: ENGINE 0x104B6A70
// FUNCTION: ENGINE 0x104B6A90
// FUNCTION: ENGINE 0x104B6B30
// FUNCTION: ENGINE 0x104B6B80
// FUNCTION: ENGINE 0x104B6BD0
// FUNCTION: ENGINE 0x104B6C40
// FUNCTION: ENGINE 0x104B6C60
// FUNCTION: ENGINE 0x104B6C80
// FUNCTION: ENGINE 0x104B6CF0
// FUNCTION: ENGINE 0x104B6D10
// FUNCTION: ENGINE 0x104B6D30
// FUNCTION: ENGINE 0x104B6D90
// FUNCTION: ENGINE 0x104B6DB0
// FUNCTION: ENGINE 0x104B6DD0
// FUNCTION: ENGINE 0x104B6E50
// FUNCTION: ENGINE 0x104B6E80
// FUNCTION: ENGINE 0x104B6EB0
// FUNCTION: ENGINE 0x104B6F20
// FUNCTION: ENGINE 0x104B6F40
// FUNCTION: ENGINE 0x104B6F60
// FUNCTION: ENGINE 0x104B6FD0
// FUNCTION: ENGINE 0x104B6FF0
// FUNCTION: ENGINE 0x104B7010
// FUNCTION: ENGINE 0x104B7080
// FUNCTION: ENGINE 0x104B70A0
// FUNCTION: ENGINE 0x104B70D0
// FUNCTION: ENGINE 0x104B7140
// FUNCTION: ENGINE 0x104B7160
// FUNCTION: ENGINE 0x104B7180
// FUNCTION: ENGINE 0x104B71F0
// FUNCTION: ENGINE 0x104B7240
// FUNCTION: ENGINE 0x104B7290
// FUNCTION: ENGINE 0x104B72F0
// FUNCTION: ENGINE 0x104B7310
// FUNCTION: ENGINE 0x104B7330
// FUNCTION: ENGINE 0x104B7390
// FUNCTION: ENGINE 0x104B73B0
// FUNCTION: ENGINE 0x104B73E0
// FUNCTION: ENGINE 0x104B7470
// FUNCTION: ENGINE 0x104B74D0
// FUNCTION: ENGINE 0x104B7530
// FUNCTION: ENGINE 0x104B7590
// FUNCTION: ENGINE 0x104B75C0
// FUNCTION: ENGINE 0x104B7600
// FUNCTION: ENGINE 0x104B7660
// FUNCTION: ENGINE 0x104B7680
// FUNCTION: ENGINE 0x104B76B0
// FUNCTION: ENGINE 0x104B7700
// FUNCTION: ENGINE 0x104B7720
// FUNCTION: ENGINE 0x104B7740
// FUNCTION: ENGINE 0x104B77A0
// FUNCTION: ENGINE 0x104B77C0
// FUNCTION: ENGINE 0x104B77F0
// FUNCTION: ENGINE 0x104B7860
// FUNCTION: ENGINE 0x104B7890
// FUNCTION: ENGINE 0x104B8AB0
// FUNCTION: ENGINE 0x104B8B70
// FUNCTION: ENGINE 0x104B8BA0
// FUNCTION: ENGINE 0x104B8BF0
// FUNCTION: ENGINE 0x104B8C00
// FUNCTION: ENGINE 0x104B8C30
// FUNCTION: ENGINE 0x104B8C50
// FUNCTION: ENGINE 0x104B8C80
// FUNCTION: ENGINE 0x104B8CA0
// FUNCTION: ENGINE 0x104B8D10
// FUNCTION: ENGINE 0x104B8D30
// FUNCTION: ENGINE 0x104B8D60
// FUNCTION: ENGINE 0x104B8D90
// FUNCTION: ENGINE 0x104B8DC0
// FUNCTION: ENGINE 0x104B8DE0
// FUNCTION: ENGINE 0x104B8E10
// FUNCTION: ENGINE 0x104B8E30
// FUNCTION: ENGINE 0x104B8E60
// FUNCTION: ENGINE 0x104B8E90
// FUNCTION: ENGINE 0x104B8EC0
// FUNCTION: ENGINE 0x104B8EE0
// FUNCTION: ENGINE 0x104B8F10
// FUNCTION: ENGINE 0x104B8F60
// FUNCTION: ENGINE 0x104B8FD0
// FUNCTION: ENGINE 0x104B8FF0
// FUNCTION: ENGINE 0x104B9060
// FUNCTION: ENGINE 0x104B9090
// FUNCTION: ENGINE 0x104B90C0
// FUNCTION: ENGINE 0x104B9120
// FUNCTION: ENGINE 0x104B9190
// FUNCTION: ENGINE 0x104B91D0
// FUNCTION: ENGINE 0x104B9240
// FUNCTION: ENGINE 0x104B9270
// FUNCTION: ENGINE 0x104B92D0
// FUNCTION: ENGINE 0x104B92F0
// FUNCTION: ENGINE 0x104B9360
// FUNCTION: ENGINE 0x104B9390
// FUNCTION: ENGINE 0x104B93C0
// FUNCTION: ENGINE 0x104B9B50
// FUNCTION: ENGINE 0x104B9BC0
// FUNCTION: ENGINE 0x104B9C30
// FUNCTION: ENGINE 0x104B9CA0
// FUNCTION: ENGINE 0x104B9D00
// FUNCTION: ENGINE 0x104B9D70
// FUNCTION: ENGINE 0x104B9DE0
// FUNCTION: ENGINE 0x104B9E50
// FUNCTION: ENGINE 0x104B9EC0
// FUNCTION: ENGINE 0x104B9F30
// FUNCTION: ENGINE 0x104B9FA0
// FUNCTION: ENGINE 0x104BA000
// FUNCTION: ENGINE 0x104BA060
// FUNCTION: ENGINE 0x104BA0D0
// FUNCTION: ENGINE 0x104BA130
// FUNCTION: ENGINE 0x104BA190
// FUNCTION: ENGINE 0x104BA220
// FUNCTION: ENGINE 0x104BA280
// FUNCTION: ENGINE 0x104BB840
// FUNCTION: ENGINE 0x104BB890
// FUNCTION: ENGINE 0x104BBEE0
// FUNCTION: ENGINE 0x104BBF40
// FUNCTION: ENGINE 0x104BBF60
// FUNCTION: ENGINE 0x104BBFD0
// FUNCTION: ENGINE 0x104BBFF0
// FUNCTION: ENGINE 0x104BC010
// FUNCTION: ENGINE 0x104BC090
// FUNCTION: ENGINE 0x104BC0B0
// FUNCTION: ENGINE 0x104BC0E0
// FUNCTION: ENGINE 0x104BC140
// FUNCTION: ENGINE 0x104BC160
// FUNCTION: ENGINE 0x104BC180
// FUNCTION: ENGINE 0x104BC1F0
// FUNCTION: ENGINE 0x104BC210
// FUNCTION: ENGINE 0x104BC230
// FUNCTION: ENGINE 0x104BC2A0
// FUNCTION: ENGINE 0x104BC2C0
// FUNCTION: ENGINE 0x104BC2E0
// FUNCTION: ENGINE 0x104BC350
// FUNCTION: ENGINE 0x104BC370
// FUNCTION: ENGINE 0x104BC390
// FUNCTION: ENGINE 0x104BC3F0
// FUNCTION: ENGINE 0x104BC420
// FUNCTION: ENGINE 0x104BC7F0
// FUNCTION: ENGINE 0x104BC880
// FUNCTION: ENGINE 0x104BC8B0
// FUNCTION: ENGINE 0x104BC8D0
// FUNCTION: ENGINE 0x104BC900
// FUNCTION: ENGINE 0x104BC930
// FUNCTION: ENGINE 0x104BC9A0
// FUNCTION: ENGINE 0x104BC9C0
// FUNCTION: ENGINE 0x104BC9F0
// FUNCTION: ENGINE 0x104BCA10
// FUNCTION: ENGINE 0x104BCA40
// FUNCTION: ENGINE 0x104BCA60
// FUNCTION: ENGINE 0x104BCA90
// FUNCTION: ENGINE 0x104BCAB0
// FUNCTION: ENGINE 0x104BCAC0
// FUNCTION: ENGINE 0x104BCB30
// FUNCTION: ENGINE 0x104BCDE0
// FUNCTION: ENGINE 0x104BCE50
// FUNCTION: ENGINE 0x104BCEC0
// FUNCTION: ENGINE 0x104BCF20
// FUNCTION: ENGINE 0x104BCF90
// FUNCTION: ENGINE 0x104BD000
// FUNCTION: ENGINE 0x104BD070
// FUNCTION: ENGINE 0x104BDCB0
// FUNCTION: ENGINE 0x104BDD00
// FUNCTION: ENGINE 0x104BDD60
// FUNCTION: ENGINE 0x104BDDC0
// FUNCTION: ENGINE 0x104BDDE0
// FUNCTION: ENGINE 0x104BDEC0
// FUNCTION: ENGINE 0x104BDF60
// FUNCTION: ENGINE 0x104BDF90
// FUNCTION: ENGINE 0x104BE030
// FUNCTION: ENGINE 0x104BE080
// FUNCTION: ENGINE 0x104BE0D0
// FUNCTION: ENGINE 0x104BE130
// FUNCTION: ENGINE 0x104BE150
// FUNCTION: ENGINE 0x104BE560
// FUNCTION: ENGINE 0x104BE5F0
// FUNCTION: ENGINE 0x104BE620
// FUNCTION: ENGINE 0x104BE650
// FUNCTION: ENGINE 0x104BE680
// FUNCTION: ENGINE 0x104BE6D0
// FUNCTION: ENGINE 0x104BE740
// FUNCTION: ENGINE 0x104BE760
// FUNCTION: ENGINE 0x104BE9E0
// FUNCTION: ENGINE 0x104BEA50
// FUNCTION: ENGINE 0x104BEAC0
// FUNCTION: ENGINE 0x104C0EA0
// FUNCTION: ENGINE 0x104C0EF0
// FUNCTION: ENGINE 0x104C1190
// FUNCTION: ENGINE 0x104C11F0
// FUNCTION: ENGINE 0x104C1210
// FUNCTION: ENGINE 0x104C1260
// FUNCTION: ENGINE 0x104C1280
// FUNCTION: ENGINE 0x104C12A0
// FUNCTION: ENGINE 0x104C1300
// FUNCTION: ENGINE 0x104C1320
// FUNCTION: ENGINE 0x104C1350
// FUNCTION: ENGINE 0x104C13C0
// FUNCTION: ENGINE 0x104C13E0
// FUNCTION: ENGINE 0x104C1800
// FUNCTION: ENGINE 0x104C1890
// FUNCTION: ENGINE 0x104C18F0
// FUNCTION: ENGINE 0x104C1910
// FUNCTION: ENGINE 0x104C1920
// FUNCTION: ENGINE 0x104C1990
// FUNCTION: ENGINE 0x104C19C0
// FUNCTION: ENGINE 0x104C19F0
// FUNCTION: ENGINE 0x104C1AE0
// FUNCTION: ENGINE 0x104C1B70
// FUNCTION: ENGINE 0x104C1BD0
// FUNCTION: ENGINE 0x104C3810
// FUNCTION: ENGINE 0x104C3860
// FUNCTION: ENGINE 0x104C3D90
// FUNCTION: ENGINE 0x104C3DF0
// FUNCTION: ENGINE 0x104C3E10
// FUNCTION: ENGINE 0x104C3E60
// FUNCTION: ENGINE 0x104C3E80
// FUNCTION: ENGINE 0x104C3EB0
// FUNCTION: ENGINE 0x104C3F10
// FUNCTION: ENGINE 0x104C3F30
// FUNCTION: ENGINE 0x104C4460
// FUNCTION: ENGINE 0x104C4500
// FUNCTION: ENGINE 0x104C4560
// FUNCTION: ENGINE 0x104C4580
// FUNCTION: ENGINE 0x104C45A0
// FUNCTION: ENGINE 0x104C4610
// FUNCTION: ENGINE 0x104C4700
// FUNCTION: ENGINE 0x104C47A0
// FUNCTION: ENGINE 0x104C5E10
// FUNCTION: ENGINE 0x104C5E60
// FUNCTION: ENGINE 0x104C5E80
// FUNCTION: ENGINE 0x104C6610
// FUNCTION: ENGINE 0x104C6670
// FUNCTION: ENGINE 0x104C6E70
// FUNCTION: ENGINE 0x104CC8C0
// FUNCTION: ENGINE 0x104CC910
// FUNCTION: ENGINE 0x104CCC10
// FUNCTION: ENGINE 0x104CCC70
// FUNCTION: ENGINE 0x104CCC90
// FUNCTION: ENGINE 0x104CCD80
// FUNCTION: ENGINE 0x104CCDF0
// FUNCTION: ENGINE 0x104CCE70
// FUNCTION: ENGINE 0x104CCEE0
// FUNCTION: ENGINE 0x104CCF00
// FUNCTION: ENGINE 0x104CCF30
// FUNCTION: ENGINE 0x104CCFA0
// FUNCTION: ENGINE 0x104CCFC0
// FUNCTION: ENGINE 0x104CCFF0
// FUNCTION: ENGINE 0x104CD050
// FUNCTION: ENGINE 0x104CD070
// FUNCTION: ENGINE 0x104CD0A0
// FUNCTION: ENGINE 0x104CD110
// FUNCTION: ENGINE 0x104CD140
// FUNCTION: ENGINE 0x104CD170
// FUNCTION: ENGINE 0x104CD1E0
// FUNCTION: ENGINE 0x104CD200
// FUNCTION: ENGINE 0x104CD230
// FUNCTION: ENGINE 0x104CD290
// FUNCTION: ENGINE 0x104CD2B0
// FUNCTION: ENGINE 0x104CD2D0
// FUNCTION: ENGINE 0x104CD340
// FUNCTION: ENGINE 0x104CD370
// FUNCTION: ENGINE 0x104CD660
// FUNCTION: ENGINE 0x104CD700
// FUNCTION: ENGINE 0x104CD740
// FUNCTION: ENGINE 0x104CD750
// FUNCTION: ENGINE 0x104CD770
// FUNCTION: ENGINE 0x104CD7B0
// FUNCTION: ENGINE 0x104CD7E0
// FUNCTION: ENGINE 0x104CD820
// FUNCTION: ENGINE 0x104CD850
// FUNCTION: ENGINE 0x104CD8C0
// FUNCTION: ENGINE 0x104CD8F0
// FUNCTION: ENGINE 0x104CD930
// FUNCTION: ENGINE 0x104CD960
// FUNCTION: ENGINE 0x104CD9A0
// FUNCTION: ENGINE 0x104CD9D0
// FUNCTION: ENGINE 0x104CDA40
// FUNCTION: ENGINE 0x104CDA60
// FUNCTION: ENGINE 0x104CDAA0
// FUNCTION: ENGINE 0x104CDB00
// FUNCTION: ENGINE 0x104CDB70
// FUNCTION: ENGINE 0x104CDBE0
// FUNCTION: ENGINE 0x104CDC50
// FUNCTION: ENGINE 0x104CDCB0
// FUNCTION: ENGINE 0x104CDD20
// FUNCTION: ENGINE 0x104CDD90
// FUNCTION: ENGINE 0x104CDDF0
// FUNCTION: ENGINE 0x104CF4C0
// FUNCTION: ENGINE 0x104CF510
// FUNCTION: ENGINE 0x104CF560
// FUNCTION: ENGINE 0x104CF5C0
// FUNCTION: ENGINE 0x104CF5E0
// FUNCTION: ENGINE 0x104CF670
// FUNCTION: ENGINE 0x104CFBD0
// FUNCTION: ENGINE 0x104CFC20
// FUNCTION: ENGINE 0x104CFC40
// FUNCTION: ENGINE 0x104CFC60
// FUNCTION: ENGINE 0x104CFCC0
// FUNCTION: ENGINE 0x104CFCE0
// FUNCTION: ENGINE 0x104D0C10
// FUNCTION: ENGINE 0x104D0C60
// FUNCTION: ENGINE 0x104D0CD0
// FUNCTION: ENGINE 0x104D0D30
// FUNCTION: ENGINE 0x104D0D50
// FUNCTION: ENGINE 0x104D0DE0
// FUNCTION: ENGINE 0x104D0FB0
// FUNCTION: ENGINE 0x104D1000
// FUNCTION: ENGINE 0x104D1010
// FUNCTION: ENGINE 0x104D1070
// FUNCTION: ENGINE 0x104D1090
// FUNCTION: ENGINE 0x104D1120
// FUNCTION: ENGINE 0x104D1220
// FUNCTION: ENGINE 0x104D1270
// FUNCTION: ENGINE 0x104D1280
// FUNCTION: ENGINE 0x104D12E0
// FUNCTION: ENGINE 0x104D1300
// FUNCTION: ENGINE 0x104D1390
// FUNCTION: ENGINE 0x104D1600
// FUNCTION: ENGINE 0x104D1650
// FUNCTION: ENGINE 0x104D1B90
// FUNCTION: ENGINE 0x104D1BF0
// FUNCTION: ENGINE 0x104D1C10
// FUNCTION: ENGINE 0x104D1C80
// FUNCTION: ENGINE 0x104D1CA0
// FUNCTION: ENGINE 0x104D1CC0
// FUNCTION: ENGINE 0x104D1D80
// FUNCTION: ENGINE 0x104D1DD0
// FUNCTION: ENGINE 0x104D1E30
// FUNCTION: ENGINE 0x104D1EA0
// FUNCTION: ENGINE 0x104D1EC0
// FUNCTION: ENGINE 0x104D1EE0
// FUNCTION: ENGINE 0x104D1F30
// FUNCTION: ENGINE 0x104D1F50
// FUNCTION: ENGINE 0x104D1F70
// FUNCTION: ENGINE 0x104D1FD0
// FUNCTION: ENGINE 0x104D1FF0
// FUNCTION: ENGINE 0x104D20D0
// FUNCTION: ENGINE 0x104D2160
// FUNCTION: ENGINE 0x104D2190
// FUNCTION: ENGINE 0x104D21B0
// FUNCTION: ENGINE 0x104D21E0
// FUNCTION: ENGINE 0x104D2240
// FUNCTION: ENGINE 0x104D2270
// FUNCTION: ENGINE 0x104D2290
// FUNCTION: ENGINE 0x104D22F0
// FUNCTION: ENGINE 0x104D2310
// FUNCTION: ENGINE 0x104D2320
// FUNCTION: ENGINE 0x104D2390
// FUNCTION: ENGINE 0x104D23B0
// FUNCTION: ENGINE 0x104D2420
// FUNCTION: ENGINE 0x104D2490
// FUNCTION: ENGINE 0x104D2500
// FUNCTION: ENGINE 0x104D2590
// FUNCTION: ENGINE 0x104D2EE0
// FUNCTION: ENGINE 0x104D2F30
// FUNCTION: ENGINE 0x104D3360
// FUNCTION: ENGINE 0x104D33C0
// FUNCTION: ENGINE 0x104D33E0
// FUNCTION: ENGINE 0x104D3440
// FUNCTION: ENGINE 0x104D3460
// FUNCTION: ENGINE 0x104D3480
// FUNCTION: ENGINE 0x104D34F0
// FUNCTION: ENGINE 0x104D3510
// FUNCTION: ENGINE 0x104D3530
// FUNCTION: ENGINE 0x104D35A0
// FUNCTION: ENGINE 0x104D35C0
// FUNCTION: ENGINE 0x104D35E0
// FUNCTION: ENGINE 0x104D3670
// FUNCTION: ENGINE 0x104D36E0
// FUNCTION: ENGINE 0x104D3700
// FUNCTION: ENGINE 0x104D3710
// FUNCTION: ENGINE 0x104D3740
// FUNCTION: ENGINE 0x104D3760
// FUNCTION: ENGINE 0x104D3790
// FUNCTION: ENGINE 0x104D37B0
// FUNCTION: ENGINE 0x104D3810
// FUNCTION: ENGINE 0x104D3880
// FUNCTION: ENGINE 0x104D9A20
// FUNCTION: ENGINE 0x104D9A70
// FUNCTION: ENGINE 0x104D9DC0
// FUNCTION: ENGINE 0x104D9E20
// FUNCTION: ENGINE 0x104D9E40
// FUNCTION: ENGINE 0x104D9F10
// FUNCTION: ENGINE 0x104D9F70
// FUNCTION: ENGINE 0x104D9FE0
// FUNCTION: ENGINE 0x104DA050
// FUNCTION: ENGINE 0x104DA080
// FUNCTION: ENGINE 0x104DA0B0
// FUNCTION: ENGINE 0x104DA100
// FUNCTION: ENGINE 0x104DA120
// FUNCTION: ENGINE 0x104DA280
// FUNCTION: ENGINE 0x104DA310
// FUNCTION: ENGINE 0x104DA340
// FUNCTION: ENGINE 0x104DA3B0
// FUNCTION: ENGINE 0x104DA3E0
// FUNCTION: ENGINE 0x104DA410
// FUNCTION: ENGINE 0x104DA420
// FUNCTION: ENGINE 0x104DA480
// FUNCTION: ENGINE 0x104DA5F0
// FUNCTION: ENGINE 0x104DA660
// FUNCTION: ENGINE 0x104DA6D0
// FUNCTION: ENGINE 0x104DD9B0
// FUNCTION: ENGINE 0x104DDA00
// FUNCTION: ENGINE 0x104DDE10
// FUNCTION: ENGINE 0x104DDE70
// FUNCTION: ENGINE 0x104DDE90
// FUNCTION: ENGINE 0x104DDEF0
// FUNCTION: ENGINE 0x104DDF10
// FUNCTION: ENGINE 0x104DDF30
// FUNCTION: ENGINE 0x104DDF80
// FUNCTION: ENGINE 0x104DDFA0
// FUNCTION: ENGINE 0x104DDFD0
// FUNCTION: ENGINE 0x104DE030
// FUNCTION: ENGINE 0x104DE060
// FUNCTION: ENGINE 0x104DE090
// FUNCTION: ENGINE 0x104DE0E0
// FUNCTION: ENGINE 0x104DE100
// FUNCTION: ENGINE 0x104DE130
// FUNCTION: ENGINE 0x104DE180
// FUNCTION: ENGINE 0x104DE1A0
// FUNCTION: ENGINE 0x104DE1D0
// FUNCTION: ENGINE 0x104DE230
// FUNCTION: ENGINE 0x104DE250
// FUNCTION: ENGINE 0x104DE270
// FUNCTION: ENGINE 0x104DE310
// FUNCTION: ENGINE 0x104DE330
// FUNCTION: ENGINE 0x104DE3A0
// FUNCTION: ENGINE 0x104DE3C0
// FUNCTION: ENGINE 0x104DE420
// FUNCTION: ENGINE 0x104DE440
// FUNCTION: ENGINE 0x104DE4B0
// FUNCTION: ENGINE 0x104DE4E0
// FUNCTION: ENGINE 0x104DE540
// FUNCTION: ENGINE 0x104DE560
// FUNCTION: ENGINE 0x104DE5C0
// FUNCTION: ENGINE 0x104DE5E0
// FUNCTION: ENGINE 0x104DE650
// FUNCTION: ENGINE 0x104DE670
// FUNCTION: ENGINE 0x104DE6D0
// FUNCTION: ENGINE 0x104DE770
// FUNCTION: ENGINE 0x104DE7D0
// FUNCTION: ENGINE 0x104DE870
// FUNCTION: ENGINE 0x104DE910
