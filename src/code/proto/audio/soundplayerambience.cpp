// proto::SoundPlayerAmbience: the property setters, the tables that bind them to the names of the properties, the
// application of the properties of a settings object, the destructor (see soundplayerambience.h). The file name is a guess.
#include "code/proto/audio/soundplayerambience.h"
#include "code/core/hash.h"
#include "code/om/dynamicproperty.h"
#include "code/om/name.h"

namespace proto
{
	using namespace om;

	SpeakerGains::SpeakerGains()
	{
		lf = rf = ls = rs;
	}

	SoundPlayerAmbience::~SoundPlayerAmbience()
	{
		audio::gRemotePlayers->Release(player);
	}

	void SoundPlayerAmbience::SetLoop(bool value)
	{
	}

	void SoundPlayerAmbience::SetSmallSphereMult(float value)
	{
	}

	void SoundPlayerAmbience::SetMedSphereMult(float value)
	{
	}

	void SoundPlayerAmbience::SetMinRadius(float value)
	{
	}

	void SoundPlayerAmbience::SetListenerYOffsetMax(float value)
	{
	}

	void SoundPlayerAmbience::SetListenerMoveConst(float value)
	{
	}

	void SoundPlayerAmbience::SetWorldPointDistance(float value)
	{
	}

	void SoundPlayerAmbience::SetWorldPointRadius(float value)
	{
	}

	void SoundPlayerAmbience::SetRooftopOffset(float value)
	{
	}

	void SoundPlayerAmbience::SetCrowdUp(float value)
	{
	}

	void SoundPlayerAmbience::SetCrowdDown(float value)
	{
	}

	void SoundPlayerAmbience::SetCrowdUpChannel(float value)
	{
	}

	void SoundPlayerAmbience::SetCrowdDownChannel(float value)
	{
	}

	void SoundPlayerAmbience::SetInfUp(float value)
	{
	}

	void SoundPlayerAmbience::SetInfDown(float value)
	{
	}

	void SoundPlayerAmbience::SetInfUpChannel(float value)
	{
	}

	void SoundPlayerAmbience::SetInfDownChannel(float value)
	{
	}

	void SoundPlayerAmbience::SetInfectedZoneMinVolume(float value)
	{
	}

	void SoundPlayerAmbience::SetGroup(const String& value)
	{
	}

	void SoundPlayerAmbience::SetInfLocalLfMult(float value)
	{
		infLocal.lf = value;
	}

	void SoundPlayerAmbience::SetInfLocalLsMult(float value)
	{
		infLocal.ls = value;
	}

	void SoundPlayerAmbience::SetInfLocalRsMult(float value)
	{
		infLocal.rs = value;
	}

	void SoundPlayerAmbience::SetInfLocalRfMult(float value)
	{
		infLocal.rf = value;
	}

	void SoundPlayerAmbience::SetInfLfMult(float value)
	{
		inf.lf = value;
	}

	void SoundPlayerAmbience::SetInfLsMult(float value)
	{
		inf.ls = value;
	}

	void SoundPlayerAmbience::SetInfRsMult(float value)
	{
		inf.rs = value;
	}

	void SoundPlayerAmbience::SetInfRfMult(float value)
	{
		inf.rf = value;
	}

	void SoundPlayerAmbience::SetCrowdLocalLfMult(float value)
	{
		crowdLocal.lf = value;
	}

	void SoundPlayerAmbience::SetCrowdLocalLsMult(float value)
	{
		crowdLocal.ls = value;
	}

	void SoundPlayerAmbience::SetCrowdLocalRsMult(float value)
	{
		crowdLocal.rs = value;
	}

	void SoundPlayerAmbience::SetCrowdLocalRfMult(float value)
	{
		crowdLocal.rf = value;
	}

	void SoundPlayerAmbience::SetCrowdLfMult(float value)
	{
		crowd.lf = value;
	}

	void SoundPlayerAmbience::SetCrowdLsMult(float value)
	{
		crowd.ls = value;
	}

	void SoundPlayerAmbience::SetCrowdRsMult(float value)
	{
		crowd.rs = value;
	}

	void SoundPlayerAmbience::SetCrowdRfMult(float value)
	{
		crowd.rf = value;
	}

	void SoundPlayerAmbience::SetIdleLfMult(float value)
	{
		idle.lf = value;
	}

	void SoundPlayerAmbience::SetIdleLsMult(float value)
	{
		idle.ls = value;
	}

	void SoundPlayerAmbience::SetIdleRsMult(float value)
	{
		idle.rs = value;
	}

	void SoundPlayerAmbience::SetIdleRfMult(float value)
	{
		idle.rf = value;
	}

	void SoundPlayerAmbience::SetReverbSend(float value)
	{
		reverbSend = value;
	}

	void SoundPlayerAmbience::SetDistanceFilter(float value)
	{
		distanceFilter = value;
	}

	void SoundPlayerAmbience::SetVolume(float value)
	{
		volume = value;
	}

	void SoundPlayerAmbience::SetCityVol(float value)
	{
		cityVol = value;
	}

	void SoundPlayerAmbience::SetCrowdPanicVol(float value)
	{
		crowdPanicVol = value;
	}

	void SoundPlayerAmbience::SetTrafficIdleVol(float value)
	{
		trafficIdleVol = value;
	}

	void SoundPlayerAmbience::SetTrafficPanicVol(float value)
	{
		trafficPanicVol = value;
	}

	void SoundPlayerAmbience::SetRooftopVolume(float value)
	{
		rooftopVolume = value;
	}

	void SoundPlayerAmbience::SetInfectedVol(float value)
	{
		infectedVol = value;
	}

	void SoundPlayerAmbience::SetInfectedLocalVol(float value)
	{
		infectedLocalVol = value;
	}

	void SoundPlayerAmbience::SetParkVol(float value)
	{
		parkVol = value;
	}

	void SoundPlayerAmbience::SetCrowdLocalVol(float value)
	{
		crowdLocalVol = value;
	}

	// The tables that map the names of the properties to the setters, one per type of value; each ends with an entry named
	// by the empty text (the engine fills them in at start-up)
	template<class Setter> struct PropertyEntry
	{
		ClassName name;
		Setter setter;
	};

	extern PropertyEntry<void (SoundPlayerAmbience::*)(bool)> ambienceBoolProperties[];
	extern PropertyEntry<void (SoundPlayerAmbience::*)(float)> ambienceFloatProperties[];
	extern PropertyEntry<void (SoundPlayerAmbience::*)(const String&)> ambienceStringProperties[];
	extern PropertyEntry<void (SoundPlayerAmbience::*)(const DynamicArray<String, unsigned short>&)> ambienceArrayProperties[];
	extern PropertyEntry<void (SoundPlayerAmbience::*)(const mgraph::EnvelopeData&)> ambienceEnvelopeProperties[];

#ifdef NONMATCHING
	// NONMATCHING: the dynamic initializers of the tables (0x10D5C400, 0x10D5C4D0, 0x10D5D750, 0x10D5D870, 0x10D5D940) are 93 - 99 %: the engine zeroes the
	// two words of the closing entry with xor and two stores, ours stores two immediate zeros
	// A property name: the hash of the text
	static inline ClassName NameOf(const String& name)
	{
		return ClassName(core::Hash64(name.GetText(), 0));
	}

	static inline ClassName NameOf(const char* text)
	{
		String name(text, 0);
		return ClassName(core::Hash64(name.GetText(), 0));
	}


	PropertyEntry<void (SoundPlayerAmbience::*)(bool)> ambienceBoolProperties[] =
	{
		{ NameOf("loop"), &SoundPlayerAmbience::SetLoop },
		{ NameOf(""), 0 }
	};

	PropertyEntry<void (SoundPlayerAmbience::*)(float)> ambienceFloatProperties[] =
	{
		{ NameOf("city_vol"), &SoundPlayerAmbience::SetCityVol },
		{ NameOf("crowd_panic_vol"), &SoundPlayerAmbience::SetCrowdPanicVol },
		{ NameOf("traffic_idle_vol"), &SoundPlayerAmbience::SetTrafficIdleVol },
		{ NameOf("traffic_panic_vol"), &SoundPlayerAmbience::SetTrafficPanicVol },
		{ NameOf("rooftop_volume"), &SoundPlayerAmbience::SetRooftopVolume },
		{ NameOf("infected_vol"), &SoundPlayerAmbience::SetInfectedVol },
		{ NameOf("infected_local_vol"), &SoundPlayerAmbience::SetInfectedLocalVol },
		{ NameOf("park_vol"), &SoundPlayerAmbience::SetParkVol },
		{ NameOf("crowd_local_vol"), &SoundPlayerAmbience::SetCrowdLocalVol },
		{ NameOf("volume"), &SoundPlayerAmbience::SetVolume },
		{ NameOf("med_sphere_mult"), &SoundPlayerAmbience::SetMedSphereMult },
		{ NameOf("small_sphere_mult"), &SoundPlayerAmbience::SetSmallSphereMult },
		{ NameOf("min_radius"), &SoundPlayerAmbience::SetMinRadius },
		{ NameOf("distance_filter"), &SoundPlayerAmbience::SetDistanceFilter },
		{ NameOf("reverb_send"), &SoundPlayerAmbience::SetReverbSend },
		{ NameOf("listener_y_offset_max"), &SoundPlayerAmbience::SetListenerYOffsetMax },
		{ NameOf("listener_move_const"), &SoundPlayerAmbience::SetListenerMoveConst },
		{ NameOf("world_point_distance"), &SoundPlayerAmbience::SetWorldPointDistance },
		{ NameOf("world_point_radius"), &SoundPlayerAmbience::SetWorldPointRadius },
		{ NameOf("multichan_volume_leak"), &SoundPlayerAmbience::SetWorldPointRadius },
		{ NameOf("rooftop_offset"), &SoundPlayerAmbience::SetRooftopOffset },
		{ NameOf("crowd_up"), &SoundPlayerAmbience::SetCrowdUp },
		{ NameOf("crowd_down"), &SoundPlayerAmbience::SetCrowdDown },
		{ NameOf("crowd_up_channel"), &SoundPlayerAmbience::SetCrowdUpChannel },
		{ NameOf("crowd_down_channel"), &SoundPlayerAmbience::SetCrowdDownChannel },
		{ NameOf("inf_up"), &SoundPlayerAmbience::SetInfUp },
		{ NameOf("inf_down"), &SoundPlayerAmbience::SetInfDown },
		{ NameOf("inf_up_channel"), &SoundPlayerAmbience::SetInfUpChannel },
		{ NameOf("inf_down_channel"), &SoundPlayerAmbience::SetInfDownChannel },
		{ NameOf("infected_zone_min_volume"), &SoundPlayerAmbience::SetInfectedZoneMinVolume },
		{ NameOf("idle_lf_mult"), &SoundPlayerAmbience::SetIdleLfMult },
		{ NameOf("idle_ls_mult"), &SoundPlayerAmbience::SetIdleLsMult },
		{ NameOf("idle_rs_mult"), &SoundPlayerAmbience::SetIdleRsMult },
		{ NameOf("idle_rf_mult"), &SoundPlayerAmbience::SetIdleRfMult },
		{ NameOf("crowd_lf_mult"), &SoundPlayerAmbience::SetCrowdLfMult },
		{ NameOf("crowd_ls_mult"), &SoundPlayerAmbience::SetCrowdLsMult },
		{ NameOf("crowd_rs_mult"), &SoundPlayerAmbience::SetCrowdRsMult },
		{ NameOf("crowd_rf_mult"), &SoundPlayerAmbience::SetCrowdRfMult },
		{ NameOf("crowd_local_lf_mult"), &SoundPlayerAmbience::SetCrowdLocalLfMult },
		{ NameOf("crowd_local_ls_mult"), &SoundPlayerAmbience::SetCrowdLocalLsMult },
		{ NameOf("crowd_local_rs_mult"), &SoundPlayerAmbience::SetCrowdLocalRsMult },
		{ NameOf("crowd_local_rf_mult"), &SoundPlayerAmbience::SetCrowdLocalRfMult },
		{ NameOf("inf_lf_mult"), &SoundPlayerAmbience::SetInfLfMult },
		{ NameOf("inf_ls_mult"), &SoundPlayerAmbience::SetInfLsMult },
		{ NameOf("inf_rs_mult"), &SoundPlayerAmbience::SetInfRsMult },
		{ NameOf("inf_rf_mult"), &SoundPlayerAmbience::SetInfRfMult },
		{ NameOf("inf_local_lf_mult"), &SoundPlayerAmbience::SetInfLocalLfMult },
		{ NameOf("inf_local_ls_mult"), &SoundPlayerAmbience::SetInfLocalLsMult },
		{ NameOf("inf_local_rs_mult"), &SoundPlayerAmbience::SetInfLocalRsMult },
		{ NameOf("inf_local_rf_mult"), &SoundPlayerAmbience::SetInfLocalRfMult },
		{ NameOf(""), 0 }
	};

	PropertyEntry<void (SoundPlayerAmbience::*)(const String&)> ambienceStringProperties[] =
	{
		{ NameOf("filename"), &SoundPlayerAmbience::SetFilename },
		{ NameOf("group"), &SoundPlayerAmbience::SetGroup },
		{ NameOf(""), 0 }
	};

	PropertyEntry<void (SoundPlayerAmbience::*)(const DynamicArray<String, unsigned short>&)> ambienceArrayProperties[] =
	{
		{ NameOf("mixbus"), &SoundPlayerAmbience::SetMixbus },
		{ NameOf(""), 0 }
	};

	PropertyEntry<void (SoundPlayerAmbience::*)(const mgraph::EnvelopeData&)> ambienceEnvelopeProperties[] =
	{
		{ NameOf("traffic_idle_env"), &SoundPlayerAmbience::SetTrafficIdleEnv },
		{ NameOf("traffic_panic_env"), &SoundPlayerAmbience::SetTrafficPanicEnv },
		{ NameOf("crowd_panic_env"), &SoundPlayerAmbience::SetCrowdPanicEnv },
		{ NameOf("infected_env"), &SoundPlayerAmbience::SetInfectedEnv },
		{ NameOf("rofftop_env"), &SoundPlayerAmbience::SetRofftopEnv },
		{ NameOf(""), 0 }
	};
#endif

	// Takes the value of a property of the type into the setter the table names for the property (the table ends with
	// the entry named by the empty text); false when the property is of another type or has no entry
	template<class T, class Setter> bool ApplyProperty(SoundPlayerAmbience* player, DynamicPropertyBase* property, const PropertyEntry<Setter>* entry);

#ifdef NONMATCHING
	template<class T, class Setter> bool ApplyProperty(SoundPlayerAmbience* player, DynamicPropertyBase* property, const PropertyEntry<Setter>* entry)
	{
		MetaTypeBase*& cache = MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(T));
		}
		MetaTypeBase* type = cache;
		if (property->GetMetaType() == type)
		{
			for (;;)
			{
				bool more;
				{
					String empty("", 0);
					more = entry->name.key != NameOf(empty).key;
				}
				if (!more)
				{
					break;
				}
				if (entry->name.key == property->GetName().key)
				{
					DynamicProperty<T>* typed = static_cast<DynamicProperty<T>*>(property);
					(player->*entry->setter)(*static_cast<const T*>(typed->DynamicProperty<T>::GetValuePointer()));
					return true;
				}
				entry++;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104A4F10
	// NONMATCHING: 99.5 %, the engine's call of GetValuePointer leads to the copy of its own unit (0x104A3B40 and the like), the symbol of the instance maps to the copy of another unit
	template bool ApplyProperty<bool>(SoundPlayerAmbience*, DynamicPropertyBase*, const PropertyEntry<void (SoundPlayerAmbience::*)(bool)>*);
	// FUNCTION: ENGINE 0x104A5020
	// NONMATCHING: 99.5 %, the call of GetValuePointer (see above)
	template bool ApplyProperty<float>(SoundPlayerAmbience*, DynamicPropertyBase*, const PropertyEntry<void (SoundPlayerAmbience::*)(float)>*);
	// FUNCTION: ENGINE 0x104A5130
	// NONMATCHING: 99.5 %, the call of GetValuePointer (see above)
	template bool ApplyProperty<String>(SoundPlayerAmbience*, DynamicPropertyBase*, const PropertyEntry<void (SoundPlayerAmbience::*)(const String&)>*);
	// FUNCTION: ENGINE 0x104A5240
	// NONMATCHING: 99.5 %, the call of GetValuePointer (see above)
	template bool ApplyProperty<DynamicArray<String, unsigned short> >(SoundPlayerAmbience*, DynamicPropertyBase*, const PropertyEntry<void (SoundPlayerAmbience::*)(const DynamicArray<String, unsigned short>&)>*);
	// FUNCTION: ENGINE 0x104A5350
	// NONMATCHING: 99.5 %, the call of GetValuePointer (see above)
	template bool ApplyProperty<mgraph::EnvelopeData>(SoundPlayerAmbience*, DynamicPropertyBase*, const PropertyEntry<void (SoundPlayerAmbience::*)(const mgraph::EnvelopeData&)>*);
#endif

	// Takes one property of the settings into the member the table of its type names
	void ApplySetting(SoundPlayerAmbience* player, DynamicPropertyBase* property)
	{
		if (!ApplyProperty<bool>(player, property, ambienceBoolProperties))
		{
			if (!ApplyProperty<float>(player, property, ambienceFloatProperties))
			{
				if (!ApplyProperty<String>(player, property, ambienceStringProperties))
				{
					if (!ApplyProperty<DynamicArray<String, unsigned short> >(player, property, ambienceArrayProperties))
					{
						ApplyProperty<mgraph::EnvelopeData>(player, property, ambienceEnvelopeProperties);
					}
				}
			}
		}
	}

	void SoundPlayerAmbience::Slot2(DynamicObject* properties)
	{
		for (DynamicPropertyBase* property = properties->GetFirstProperty(); property != 0; property = properties->GetNextProperty(property))
		{
			ApplySetting(this, property);
		}
	}

	void SoundPlayerAmbience::SetTrafficIdleEnv(const mgraph::EnvelopeData& value)
	{
		trafficIdleEnv = value;
	}

	void SoundPlayerAmbience::SetRofftopEnv(const mgraph::EnvelopeData& value)
	{
		rooftopEnv = value;
	}

	void SoundPlayerAmbience::SetTrafficPanicEnv(const mgraph::EnvelopeData& value)
	{
		trafficPanicEnv = value;
	}

	void SoundPlayerAmbience::SetCrowdPanicEnv(const mgraph::EnvelopeData& value)
	{
		crowdPanicEnv = value;
	}

	void SoundPlayerAmbience::SetInfectedEnv(const mgraph::EnvelopeData& value)
	{
		infectedEnv = value;
	}

	void SoundPlayerAmbience::SetFilename(const String& value)
	{
		new audio::RemotePlayerEvent_Param1<const String&>(player, &audio::RemotePlayer::SetFilename, value);
	}

	void SoundPlayerAmbience::SetMixbus(const DynamicArray<String, unsigned short>& value)
	{
		audio::gRemotePlayers->SetMixBuses(player, value);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A2ED0
// FUNCTION: ENGINE 0x104A2EE0
// FUNCTION: ENGINE 0x104A2EF0
// FUNCTION: ENGINE 0x104A2F00
// FUNCTION: ENGINE 0x104A2F10
// FUNCTION: ENGINE 0x104A2F20
// FUNCTION: ENGINE 0x104A2F30
// FUNCTION: ENGINE 0x104A2F40
// FUNCTION: ENGINE 0x104A2F50
// FUNCTION: ENGINE 0x104A2F60
// FUNCTION: ENGINE 0x104A2F70
// FUNCTION: ENGINE 0x104A2F80
// FUNCTION: ENGINE 0x104A2F90
// FUNCTION: ENGINE 0x104A2FA0
// FUNCTION: ENGINE 0x104A2FB0
// FUNCTION: ENGINE 0x104A2FC0
// FUNCTION: ENGINE 0x104A2FD0
// FUNCTION: ENGINE 0x104A2FE0
// FUNCTION: ENGINE 0x104A2FF0
// FUNCTION: ENGINE 0x104A3000
// FUNCTION: ENGINE 0x104A3020
// FUNCTION: ENGINE 0x104A3040
// FUNCTION: ENGINE 0x104A3060
// FUNCTION: ENGINE 0x104A3080
// FUNCTION: ENGINE 0x104A30A0
// FUNCTION: ENGINE 0x104A30C0
// FUNCTION: ENGINE 0x104A30E0
// FUNCTION: ENGINE 0x104A3100
// FUNCTION: ENGINE 0x104A3120
// FUNCTION: ENGINE 0x104A3140
// FUNCTION: ENGINE 0x104A3160
// FUNCTION: ENGINE 0x104A3180
// FUNCTION: ENGINE 0x104A31A0
// FUNCTION: ENGINE 0x104A31C0
// FUNCTION: ENGINE 0x104A31E0
// FUNCTION: ENGINE 0x104A3200
// FUNCTION: ENGINE 0x104A3220
// FUNCTION: ENGINE 0x104A3240
// FUNCTION: ENGINE 0x104A3260
// FUNCTION: ENGINE 0x104A3280
// FUNCTION: ENGINE 0x104A32A0
// FUNCTION: ENGINE 0x104A32C0
// FUNCTION: ENGINE 0x104A32E0
// FUNCTION: ENGINE 0x104A3300
// FUNCTION: ENGINE 0x104A3320
// FUNCTION: ENGINE 0x104A3340
// FUNCTION: ENGINE 0x104A3360
// FUNCTION: ENGINE 0x104A3380
// FUNCTION: ENGINE 0x104A33A0
// FUNCTION: ENGINE 0x104A33C0
// FUNCTION: ENGINE 0x104A33E0
// FUNCTION: ENGINE 0x104A3400
// FUNCTION: ENGINE 0x104A3E10
// FUNCTION: ENGINE 0x104A47C0
// FUNCTION: ENGINE 0x104A4930
// FUNCTION: ENGINE 0x104A5470
// FUNCTION: ENGINE 0x104A55D0
// FUNCTION: ENGINE 0x104A5600
// FUNCTION: ENGINE 0x104A5630
// FUNCTION: ENGINE 0x104A5660
// FUNCTION: ENGINE 0x104A5690
// FUNCTION: ENGINE 0x104A56C0
// FUNCTION: ENGINE 0x104A5840
// FUNCTION: ENGINE 0x104A5A90
// FUNCTION: ENGINE 0x104A5DA0
