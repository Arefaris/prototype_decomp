// The fight tracks that drive a light, teleport an object and spawn an object (unit 0x108B52D0 - 0x108B6C40; no assert path, file name guessed).
#include "code/engine/fight/spawntracks.h"
#include <new>

namespace engine
{
	extern const int gLightTrackColourMembers[];
	extern const int gLightTrackIntensityMembers[];
	extern const int gLightTrackShadowCasterMembers[];
	extern const int gLightTrackUmbraMembers[];
	extern const int gLightTrackDecayMembers[];

	fight::Property** gLightTrackProperties;  // 0x113183D0

	// FUNCTION: ENGINE 0x108B51E0
	bool LightTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B51F0
	bool LightTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5200
	bool LightTrack::SetColourColour(const math::Colour128& newValue)
	{
		colourColour = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5220
	bool LightTrack::SetIntensityIntensity(float newValue)
	{
		intensityIntensity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5230
	bool LightTrack::SetShadowCasterShadowOffset(float newValue)
	{
		shadowCasterShadowOffset = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5240
	bool LightTrack::SetShadowCasterRangeMultiplier(float newValue)
	{
		shadowCasterRangeMultiplier = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5250
	bool LightTrack::SetShadowCasterRadiusMultiplier(float newValue)
	{
		shadowCasterRadiusMultiplier = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5260
	bool LightTrack::SetShadowCasterMaxRadius(float newValue)
	{
		shadowCasterMaxRadius = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5270
	bool LightTrack::SetUmbraUmbra(float newValue)
	{
		umbraUmbra = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5290
	bool LightTrack::SetUmbraPenumbra(float newValue)
	{
		umbraPenumbra = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x108B52B0
	bool LightTrack::SetDecayInner(float newValue)
	{
		decayInner = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B52C0
	bool LightTrack::SetDecayOuter(float newValue)
	{
		decayOuter = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5400
	bool LightTrack::SetLightName(const fight::Name& newValue)
	{
		lightName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5530
	bool LightTrack::SetColour(bool newValue)
	{
		colour = newValue;
		ApplyGroup(0, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B5550
	bool LightTrack::SetIntensity(bool newValue)
	{
		intensity = newValue;
		ApplyGroup(1, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B5570
	bool LightTrack::SetShadowCaster(bool newValue)
	{
		shadowCaster = newValue;
		ApplyGroup(2, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B5590
	bool LightTrack::SetUmbra(bool newValue)
	{
		umbra = newValue;
		ApplyGroup(3, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B55B0
	bool LightTrack::SetDecay(bool newValue)
	{
		decay = newValue;
		ApplyGroup(4, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B52D0
	fight::Property* LightTrack::GetProperty(int index)
	{
		return gLightTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B52E0
	void LightTrack::ClearProperties()
	{
		fight::FreePropertyList(&gLightTrackProperties);
	}

	extern const int gLightTrackColourMembers[];
	extern const int gLightTrackIntensityMembers[];
	extern const int gLightTrackShadowCasterMembers[];
	extern const int gLightTrackUmbraMembers[];
	extern const int gLightTrackDecayMembers[];

	// FUNCTION: ENGINE 0x108B52F0
	void LightTrack::ApplyGroup(int group, bool value)
	{
		const int* members;
		switch (group)
		{
		case 0:
			members = gLightTrackColourMembers;
			value = value && colour;
			break;
		case 1:
			members = gLightTrackIntensityMembers;
			value = value && intensity;
			break;
		case 2:
			members = gLightTrackShadowCasterMembers;
			value = value && shadowCaster;
			break;
		case 3:
			members = gLightTrackUmbraMembers;
			value = value && umbra;
			break;
		case 4:
			members = gLightTrackDecayMembers;
			value = value && decay;
			break;
		default:
			return;
		}
		for (int i = 0; members[i] != -1; i++)
		{
			const int* member = &members[i];
			unsigned __int64 bit = 1ui64 << *member;
			if (value)
			{
				overrideMask |= bit;
			}
			else
			{
				overrideMask &= ~bit;
			}
			ApplyGroup(*member, value);
		}
	}

	// FUNCTION: ENGINE 0x108B54E0
	bool LightTrack::Slot16(int index)
	{
		return (overrideMask & (1ui64 << index)) != 0;
	}

	// FUNCTION: ENGINE 0x108B5420
	// ctor stores: [('mov', 'dword', 0, '0x10e7c144'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '1.0f'), ('movss', 'dword', 40, '1.0f'), ('movss', 'dword', 44, '1.0f'), ('movss', 'dword', 48, '5.0f'), ('movss', 'dword', 64, '1.0f'), ('movss', 'dword', 68, '1.0f'), ('movss', 'dword', 52, '25.0f'), ('movss', 'dword', 72, '0.0010000000474974513f'), ('mov', 'byte', 92, '0'), ('mov', 'byte', 93, '0'), ('mov', 'byte', 94, '0'), ('mov', 'byte', 95, '0'), ('mov', 'byte', 96, '0'), ('movss', 'dword', 56, '0.0f'), ('movss', 'dword', 60, '200.0f'), ('movss', 'dword', 76, '0.0f'), ('movss', 'dword', 80, '0.0f'), ('movss', 'dword', 84, '0.0f'), ('movss', 'dword', 88, '1.5707963705062866f')]
	LightTrack::LightTrack() : colourColour(1.0f, 1.0f, 1.0f, 1.0f), decayInner(5.0f), decayOuter(25.0f), intensityIntensity(0.0f), shadowCasterMaxRadius(200.0f), shadowCasterRadiusMultiplier(1.0f), shadowCasterRangeMultiplier(1.0f), shadowCasterShadowOffset(0.0010000000474974513f), timeBegin(0.0f), timeEnd(0.0f), umbraPenumbra(0.0f), umbraUmbra(1.5707963705062866f), colour(0), decay(0), intensity(0), shadowCaster(0), umbra(0)
	{
	}

	// FUNCTION: ENGINE 0x108B54D0
	float LightTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B5510
	float LightTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B5520
	LightTrack::~LightTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B57E0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void LightTrack::RegisterProperties()
	{
		if (gLightTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<LightTrack>("timeBegin", &LightTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("timeEnd", &LightTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<LightTrack>("lightName", &LightTrack::SetLightName);
			properties[2] = property;
			property = new fight::PropertyGroup<LightTrack>("colour", &LightTrack::SetColour, gLightTrackColourMembers);
			properties[3] = property;
			property = new fight::PropertyColour<LightTrack>("colourColour", &LightTrack::SetColourColour);
			properties[4] = property;
			property = new fight::PropertyGroup<LightTrack>("intensity", &LightTrack::SetIntensity, gLightTrackIntensityMembers);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("intensityIntensity", &LightTrack::SetIntensityIntensity);
			properties[6] = property;
			property = new fight::PropertyGroup<LightTrack>("shadowCaster", &LightTrack::SetShadowCaster, gLightTrackShadowCasterMembers);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("shadowCasterShadowOffset", &LightTrack::SetShadowCasterShadowOffset);
			properties[8] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("shadowCasterRangeMultiplier", &LightTrack::SetShadowCasterRangeMultiplier);
			properties[9] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("shadowCasterRadiusMultiplier", &LightTrack::SetShadowCasterRadiusMultiplier);
			properties[10] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("shadowCasterMaxRadius", &LightTrack::SetShadowCasterMaxRadius);
			properties[11] = property;
			property = new fight::PropertyGroup<LightTrack>("umbra", &LightTrack::SetUmbra, gLightTrackUmbraMembers);
			properties[12] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("umbraUmbra", &LightTrack::SetUmbraUmbra);
			properties[13] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("umbraPenumbra", &LightTrack::SetUmbraPenumbra);
			properties[14] = property;
			property = new fight::PropertyGroup<LightTrack>("decay", &LightTrack::SetDecay, gLightTrackDecayMembers);
			properties[15] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("decayInner", &LightTrack::SetDecayInner);
			properties[16] = property;
			property = new fight::PropertyFloatConstRange<LightTrack>("decayOuter", &LightTrack::SetDecayOuter);
			properties[17] = property;
			fight::RegisterPropertyList(properties, &gLightTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B5740
	fight::TrackFactory* CreateLightTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<LightTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B5760
	void RegisterLightTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<LightTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyColour<LightTrack>;
	template class fight::PropertyFloatConstRange<LightTrack>;
	template class fight::PropertyGroup<LightTrack>;
	template class fight::PropertyNameList<LightTrack>;
	template class fight::TrackFactoryTemplate<LightTrack>;
	template class fight::TrackFactoryCasterTemplate<LightTrack>;

	extern fight::EnumEntry gTeleportTrackSpaceTable[];
	extern const int gTeleportTrackSpaceCount;

	fight::Property** gTeleportTrackProperties;  // 0x113183D4

	// FUNCTION: ENGINE 0x108B5C50
	bool TeleportTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5C60
	bool TeleportTrack::SetRestorePosition(bool newValue)
	{
		restorePosition = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5C70
	bool TeleportTrack::SetSpace(int newValue)
	{
		space = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5C80
	bool TeleportTrack::SetOffset(const math::Vector& newValue)
	{
		offset.x = newValue.x;
		offset.y = newValue.y;
		offset.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5CA0
	bool TeleportTrack::SetOrientation(const math::Vector& newValue)
	{
		// Degrees in the property, radians in the track
		math::Vector v(newValue.x, newValue.y, newValue.z);
		v.Scale(0.01745329238474369f);
		orientation.x = v.x;
		orientation.y = v.y;
		orientation.z = v.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5D00
	bool TeleportTrack::SetObject(const fight::Name& newValue)
	{
		object = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5D20
	bool TeleportTrack::SetSpaceJoint(const fight::Name& newValue)
	{
		spaceJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B5CE0
	fight::Property* TeleportTrack::GetProperty(int index)
	{
		return gTeleportTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B5CF0
	void TeleportTrack::ClearProperties()
	{
		fight::FreePropertyList(&gTeleportTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B5D40
	// ctor stores: [('mov', 'dword', 0, '0x10e7c31c'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '0.0f'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '0.0f'), ('mov', 'dword', 60, '0'), ('mov', 'byte', 64, '0'), ('movss', 'dword', 56, '0.0f'), ('mov', 'dword', 12, '1')]
	TeleportTrack::TeleportTrack() : offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), timeBegin(0.0f), space(0), restorePosition(false)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B5DA0
	float TeleportTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B5DB0
	float TeleportTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x108B5DC0
	TeleportTrack::~TeleportTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B6090
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void TeleportTrack::RegisterProperties()
	{
		if (gTeleportTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<TeleportTrack>("timeBegin", &TeleportTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<TeleportTrack>("restorePosition", &TeleportTrack::SetRestorePosition);
			properties[1] = property;
			property = new fight::PropertyName<TeleportTrack>("object", &TeleportTrack::SetObject);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<TeleportTrack>("space", gTeleportTrackSpaceTable, gTeleportTrackSpaceCount, &TeleportTrack::SetSpace);
			properties[3] = property;
			property = new fight::PropertyNameList<TeleportTrack>("spaceJoint", &TeleportTrack::SetSpaceJoint);
			properties[4] = property;
			property = new fight::PropertyVector<TeleportTrack>("offset", &TeleportTrack::SetOffset);
			properties[5] = property;
			property = new fight::PropertyVector<TeleportTrack>("orientation", &TeleportTrack::SetOrientation);
			properties[6] = property;
			fight::RegisterPropertyList(properties, &gTeleportTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B5FB0
	fight::TrackFactory* CreateTeleportTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<TeleportTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B5FD0
	void RegisterTeleportTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<TeleportTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<TeleportTrack>;
	template class fight::PropertyEnumConstList<TeleportTrack>;
	template class fight::PropertyFloatConstRange<TeleportTrack>;
	template class fight::PropertyName<TeleportTrack>;
	template class fight::PropertyNameList<TeleportTrack>;
	template class fight::PropertyVector<TeleportTrack>;
	template class fight::TrackFactoryTemplate<TeleportTrack>;
	template class fight::TrackFactoryCasterTemplate<TeleportTrack>;

	extern fight::EnumEntry gSpawnObjectTrackSpawnSpaceTable[];
	extern const int gSpawnObjectTrackSpawnSpaceCount;

	fight::Property** gSpawnObjectTrackProperties;  // 0x113183D8

	// FUNCTION: ENGINE 0x108B62D0
	bool SpawnObjectTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B62E0
	bool SpawnObjectTrack::SetAddSuffix(bool newValue)
	{
		addSuffix = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B62F0
	bool SpawnObjectTrack::SetSpawnSpace(int newValue)
	{
		spawnSpace = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6300
	bool SpawnObjectTrack::SetOffset(const math::Vector& newValue)
	{
		offset.x = newValue.x;
		offset.y = newValue.y;
		offset.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6320
	bool SpawnObjectTrack::SetOrientation(const math::Vector& newValue)
	{
		// Degrees in the property, radians in the track
		math::Vector v(newValue.x, newValue.y, newValue.z);
		v.Scale(0.01745329238474369f);
		orientation.x = v.x;
		orientation.y = v.y;
		orientation.z = v.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6360
	bool SpawnObjectTrack::SetLinearVelocity(const math::Vector& newValue)
	{
		linearVelocity.x = newValue.x;
		linearVelocity.y = newValue.y;
		linearVelocity.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6380
	bool SpawnObjectTrack::SetAngularVelocity(const math::Vector& newValue)
	{
		angularVelocity.x = newValue.x;
		angularVelocity.y = newValue.y;
		angularVelocity.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108B63A0
	bool SpawnObjectTrack::SetCollideWithSpawnerDelay(float newValue)
	{
		collideWithSpawnerDelay = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B63B0
	bool SpawnObjectTrack::SetDeleteOnExit(bool newValue)
	{
		deleteOnExit = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B63E0
	bool SpawnObjectTrack::SetInitialState(const char* newValue)
	{
		initialState = fight::ReplaceString(initialState, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B6400
	bool SpawnObjectTrack::SetTemplateName(const fight::Name& newValue)
	{
		templateName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6420
	bool SpawnObjectTrack::SetObjectName(const fight::Name& newValue)
	{
		objectName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6440
	bool SpawnObjectTrack::SetSpecificPlaybackSet(const fight::Name& newValue)
	{
		specificPlaybackSet = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6460
	bool SpawnObjectTrack::SetSpawnJoint(const fight::Name& newValue)
	{
		spawnJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B63C0
	fight::Property* SpawnObjectTrack::GetProperty(int index)
	{
		return gSpawnObjectTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B63D0
	void SpawnObjectTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSpawnObjectTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B6480
	// ctor stores: [('mov', 'dword', 0, '0x10e7c49c'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '0.0f'), ('movss', 'dword', 56, '0.0f'), ('movss', 'dword', 60, '0.0f'), ('movss', 'dword', 64, '0.0f'), ('movss', 'dword', 68, '0.0f'), ('movss', 'dword', 72, '0.0f'), ('movss', 'dword', 76, '0.0f'), ('movss', 'dword', 80, '0.0f'), ('movss', 'dword', 84, '0.0f'), ('movss', 'dword', 88, '0.0f'), ('movss', 'dword', 92, '0.0f'), ('mov', 'dword', 108, '1'), ('mov', 'byte', 112, '1'), ('mov', 'dword', 12, '1'), ('mov', 'dword', 96, '0'), ('movss', 'dword', 100, '0.5f'), ('movss', 'dword', 104, '0.0f'), ('mov', 'byte', 113, '0')]
	SpawnObjectTrack::SpawnObjectTrack() : angularVelocity(0.0f, 0.0f, 0.0f), linearVelocity(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), initialState(0), collideWithSpawnerDelay(0.5f), timeBegin(0.0f), spawnSpace(1), addSuffix(1), deleteOnExit(false)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B6520
	float SpawnObjectTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B6530
	float SpawnObjectTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x108B6540
	SpawnObjectTrack::~SpawnObjectTrack()
	{
		delete[] initialState;
	}

	// FUNCTION: ENGINE 0x108B6870
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SpawnObjectTrack::RegisterProperties()
	{
		if (gSpawnObjectTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SpawnObjectTrack>("timeBegin", &SpawnObjectTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<SpawnObjectTrack>("templateName", &SpawnObjectTrack::SetTemplateName);
			properties[1] = property;
			property = new fight::PropertyName<SpawnObjectTrack>("objectName", &SpawnObjectTrack::SetObjectName);
			properties[2] = property;
			property = new fight::PropertyBool<SpawnObjectTrack>("addSuffix", &SpawnObjectTrack::SetAddSuffix);
			properties[3] = property;
			property = new fight::PropertyString<SpawnObjectTrack>("initialState", &SpawnObjectTrack::SetInitialState);
			properties[4] = property;
			property = new fight::PropertyName<SpawnObjectTrack>("specificPlaybackSet", &SpawnObjectTrack::SetSpecificPlaybackSet);
			properties[5] = property;
			property = new fight::PropertyEnumConstList<SpawnObjectTrack>("spawnSpace", gSpawnObjectTrackSpawnSpaceTable, gSpawnObjectTrackSpawnSpaceCount, &SpawnObjectTrack::SetSpawnSpace);
			properties[6] = property;
			property = new fight::PropertyNameList<SpawnObjectTrack>("spawnJoint", &SpawnObjectTrack::SetSpawnJoint);
			properties[7] = property;
			property = new fight::PropertyVector<SpawnObjectTrack>("offset", &SpawnObjectTrack::SetOffset);
			properties[8] = property;
			property = new fight::PropertyVector<SpawnObjectTrack>("orientation", &SpawnObjectTrack::SetOrientation);
			properties[9] = property;
			property = new fight::PropertyVector<SpawnObjectTrack>("linearVelocity", &SpawnObjectTrack::SetLinearVelocity);
			properties[10] = property;
			property = new fight::PropertyVector<SpawnObjectTrack>("angularVelocity", &SpawnObjectTrack::SetAngularVelocity);
			properties[11] = property;
			property = new fight::PropertyFloatConstRange<SpawnObjectTrack>("collideWithSpawnerDelay", &SpawnObjectTrack::SetCollideWithSpawnerDelay);
			properties[12] = property;
			property = new fight::PropertyBool<SpawnObjectTrack>("deleteOnExit", &SpawnObjectTrack::SetDeleteOnExit);
			properties[13] = property;
			fight::RegisterPropertyList(properties, &gSpawnObjectTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B6790
	fight::TrackFactory* CreateSpawnObjectTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SpawnObjectTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B67B0
	void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SpawnObjectTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<SpawnObjectTrack>;
	template class fight::PropertyEnumConstList<SpawnObjectTrack>;
	template class fight::PropertyFloatConstRange<SpawnObjectTrack>;
	template class fight::PropertyName<SpawnObjectTrack>;
	template class fight::PropertyNameList<SpawnObjectTrack>;
	template class fight::PropertyString<SpawnObjectTrack>;
	template class fight::PropertyVector<SpawnObjectTrack>;
	template class fight::TrackFactoryTemplate<SpawnObjectTrack>;
	template class fight::TrackFactoryCasterTemplate<SpawnObjectTrack>;

}
