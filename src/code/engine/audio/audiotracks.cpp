// The fight tracks of the audio system (see the header): the members their properties write, the constructors, the
// property lists and the property classes their lists instantiate. No assert path names the unit; the file name is a
// guess. The CreateAction bodies are the audio systems' (not reconstructed).
#include "code/engine/audio/audiotracks.h"

namespace fight
{
	// FUNCTION: ENGINE 0x105A7A60
	TrackChildren::TrackChildren() :
		head(0)
	{
	}

	// FUNCTION: ENGINE 0x105A7B20
	TrackChildren::~TrackChildren()
	{
		for (Track* node = head; node != 0;)
		{
			Track* current = node;
			node = current->next;
			current->next = 0;
			delete current;
		}
		head = 0;
	}
}

namespace engine
{
	// GLOBAL: ENGINE 0x11316B70
	fight::Property** gSoundTrackProperties;

	fight::EnumEntry gSoundTrackTriggerTypeTable[4] =
		{
			{ fight::Name("Retrigger", 0) },
			{ fight::Name("Overlap", 0) },
			{ fight::Name("StopExisting", 0) },
			{ fight::Name("IgnoreIfPlaying", 0) }
		};
	extern fight::Name gMixerDefaultCategory;

	// GLOBAL: ENGINE 0x11316B74
	fight::Property** gSoundBoolValueTrackProperties;
	// GLOBAL: ENGINE 0x11316B78
	fight::Property** gMixerTrackProperties;
	// GLOBAL: ENGINE 0x11316B7C
	fight::Property** gMusicTrackProperties;
	extern fight::EnumEntry gMusicTrackPriorityTable[];
	// GLOBAL: ENGINE 0x11316B80
	fight::Property** gReverbTrackProperties;
	// GLOBAL: ENGINE 0x11316B84
	fight::Property** gSoundZoneTrackProperties;
	fight::EnumEntry gSoundZoneTrackBoundaryActionTable[2] =
		{
			{ fight::Name("ZoneEnter", 0) },
			{ fight::Name("ZoneExit", 0) }
		};

	// FUNCTION: ENGINE 0x1087A9F0
	fight::Property* SoundTrack::GetProperty(int index)
	{
		return gSoundTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087AA00
	void SoundTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSoundTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087A900
	bool SoundTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AE30
	bool SoundTrack::SetPatch(const fight::Name& value)
	{
		patch = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AE50
	bool SoundTrack::SetTrigger(const fight::Name& value)
	{
		trigger = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A970
	bool SoundTrack::SetVolumeFactor(float value)
	{
		volumeFactor = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A910
	bool SoundTrack::SetMinDistance(float value)
	{
		minDistance = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A920
	bool SoundTrack::SetMaxDistance(float value)
	{
		maxDistance = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A930
	bool SoundTrack::SetMinPitch(float value)
	{
		minPitch = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A940
	bool SoundTrack::SetMaxPitch(float value)
	{
		maxPitch = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A950
	bool SoundTrack::SetCyclicPhase(float value)
	{
		cyclicPhase = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AE70
	bool SoundTrack::SetInstanceName(const fight::Name& value)
	{
		instanceName = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A980
	bool SoundTrack::SetFrequency(float value)
	{
		frequency = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A9A0
	bool SoundTrack::SetPolledLifetime(bool value)
	{
		polledLifetime = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A9B0
	bool SoundTrack::SetTriggerType(int value)
	{
		triggerType = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AF40
	// The compiler's destructor of SoundTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087AE90
	SoundTrack::SoundTrack() :
		timeBegin(0.0f),
		unknown14(-1.0f),
		volumeFactor(1.0f),
		minDistance(0.0f),
		maxDistance(0.0f),
		minPitch(1.0f),
		maxPitch(1.0f),
		cyclicPhase(0.0f),
		frequency(1.0f),
		polledLifetime(false),
		triggerType(0)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1087AF20
	float SoundTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1087AF30
	float SoundTrack::Slot10() const
	{
		return unknown14 - timeBegin;
	}

	// FUNCTION: ENGINE 0x1087C6B0
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch, 99.2 %
	void SoundTrack::RegisterProperties()
	{
		if (gSoundTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SoundTrack>("timeBegin", &SoundTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<SoundTrack>("Patch", &SoundTrack::SetPatch);
			properties[1] = property;
			property = new fight::PropertyName<SoundTrack>("Trigger", &SoundTrack::SetTrigger);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("VolumeFactor", &SoundTrack::SetVolumeFactor);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("MinDistance", &SoundTrack::SetMinDistance);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("MaxDistance", &SoundTrack::SetMaxDistance);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("MinPitch", &SoundTrack::SetMinPitch);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("MaxPitch", &SoundTrack::SetMaxPitch);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("CyclicPhase", &SoundTrack::SetCyclicPhase);
			properties[8] = property;
			property = new fight::PropertyName<SoundTrack>("InstanceName", &SoundTrack::SetInstanceName);
			properties[9] = property;
			property = new fight::PropertyFloatConstRange<SoundTrack>("Frequency", &SoundTrack::SetFrequency);
			properties[10] = property;
			property = new fight::PropertyBool<SoundTrack>("polledLifetime", &SoundTrack::SetPolledLifetime);
			properties[11] = property;
			property = new fight::PropertyEnumConstList<SoundTrack>("TriggerType", gSoundTrackTriggerTypeTable, 4,
				&SoundTrack::SetTriggerType);
			properties[12] = property;
			fight::RegisterPropertyList(properties, &gSoundTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1087BD80
	// FUNCTION: ENGINE 0x1087BDA0
	// FUNCTION: ENGINE 0x1087BDC0
	template class fight::PropertyFloatConstRange<SoundTrack>;
	// FUNCTION: ENGINE 0x1087BDD0
	// FUNCTION: ENGINE 0x1087BDF0
	// FUNCTION: ENGINE 0x1087BE10
	template class fight::PropertyBool<SoundTrack>;
	// FUNCTION: ENGINE 0x1087BE20
	// FUNCTION: ENGINE 0x1087BE50
	// FUNCTION: ENGINE 0x1087BE60
	// FUNCTION: ENGINE 0x1087BE80
	// FUNCTION: ENGINE 0x1087BEA0
	template class fight::PropertyEnumConstList<SoundTrack>;
	// FUNCTION: ENGINE 0x1087C470
	// FUNCTION: ENGINE 0x1087C490
	template class fight::PropertyName<SoundTrack>;

	// ---- SoundBoolValueTrack ----

	// FUNCTION: ENGINE 0x1087AA30
	fight::Property* SoundBoolValueTrack::GetProperty(int index)
	{
		return gSoundBoolValueTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087AA40
	void SoundBoolValueTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSoundBoolValueTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087A730
	bool SoundBoolValueTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ACB0
	bool SoundBoolValueTrack::SetPatch(const fight::Name& value)
	{
		patch = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ACD0
	bool SoundBoolValueTrack::SetControl(const fight::Name& value)
	{
		control = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A740
	bool SoundBoolValueTrack::SetValue(bool value)
	{
		this->value = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AFB0
	// The compiler's destructor of SoundBoolValueTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087AF60
	SoundBoolValueTrack::SoundBoolValueTrack() :
		value(true),
		timeBegin(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x1087AF90
	float SoundBoolValueTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1087AFA0
	float SoundBoolValueTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1087C990
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch
	void SoundBoolValueTrack::RegisterProperties()
	{
		if (gSoundBoolValueTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SoundBoolValueTrack>("timeBegin", &SoundBoolValueTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<SoundBoolValueTrack>("Patch", &SoundBoolValueTrack::SetPatch);
			properties[1] = property;
			property = new fight::PropertyName<SoundBoolValueTrack>("Control", &SoundBoolValueTrack::SetControl);
			properties[2] = property;
			property = new fight::PropertyBool<SoundBoolValueTrack>("Value", &SoundBoolValueTrack::SetValue);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gSoundBoolValueTrackProperties);
		}
	}

	// ---- MixerTrack ----

	// FUNCTION: ENGINE 0x1087AA50
	fight::Property* MixerTrack::GetProperty(int index)
	{
		return gMixerTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087AA60
	void MixerTrack::ClearProperties()
	{
		fight::FreePropertyList(&gMixerTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087A8C0
	bool MixerTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A8D0
	bool MixerTrack::SetFadeTime(float value)
	{
		fadeTime = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ADF0
	bool MixerTrack::SetMixer(const fight::Name& value)
	{
		mixer = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AE10
	bool MixerTrack::SetCategory(const fight::Name& value)
	{
		category = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A8E0
	bool MixerTrack::SetFadeIn(bool value)
	{
		fadeIn = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A8F0
	bool MixerTrack::SetUninstallOnExit(bool value)
	{
		uninstallOnExit = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087B030
	// The compiler's destructor of MixerTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087AFD0
	MixerTrack::MixerTrack() :
		timeBegin(0.0f),
		unknown14(-1.0f),
		category(gMixerDefaultCategory),
		fadeIn(true),
		fadeTime(-1.0f),
		uninstallOnExit(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1087AAF0
	float MixerTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1087AAE0
	float MixerTrack::Slot10() const
	{
		return unknown14 - timeBegin;
	}

	// FUNCTION: ENGINE 0x1087CAA0
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch
	void MixerTrack::RegisterProperties()
	{
		if (gMixerTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<MixerTrack>("timeBegin", &MixerTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<MixerTrack>("fadeTime", &MixerTrack::SetFadeTime);
			properties[1] = property;
			property = new fight::PropertyName<MixerTrack>("Mixer", &MixerTrack::SetMixer);
			properties[2] = property;
			property = new fight::PropertyName<MixerTrack>("Category", &MixerTrack::SetCategory);
			properties[3] = property;
			property = new fight::PropertyBool<MixerTrack>("FadeIn", &MixerTrack::SetFadeIn);
			properties[4] = property;
			property = new fight::PropertyBool<MixerTrack>("UninstallOnExit", &MixerTrack::SetUninstallOnExit);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gMixerTrackProperties);
		}
	}

	// ---- MusicTrack ----

	// FUNCTION: ENGINE 0x1087AB00
	fight::Property* MusicTrack::GetProperty(int index)
	{
		return gMusicTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087AB10
	void MusicTrack::ClearProperties()
	{
		fight::FreePropertyList(&gMusicTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087A750
	bool MusicTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ACF0
	bool MusicTrack::SetGroup(const fight::Name& value)
	{
		group = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AD10
	bool MusicTrack::SetCue(const fight::Name& value)
	{
		cue = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AD30
	bool MusicTrack::SetPart(const fight::Name& value)
	{
		part = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A760
	bool MusicTrack::SetPriority(int value)
	{
		priority = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A770
	bool MusicTrack::SetResetPriority(bool value)
	{
		resetPriority = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A780
	bool MusicTrack::SetOverrideFadeOut(bool value)
	{
		overrideFadeOut = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A790
	bool MusicTrack::SetFadeoutStartBar(int value)
	{
		fadeoutStartBar = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7A0
	bool MusicTrack::SetFadeoutStartBeat(int value)
	{
		fadeoutStartBeat = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7B0
	bool MusicTrack::SetFadeoutStartNote(int value)
	{
		fadeoutStartNote = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7C0
	bool MusicTrack::SetFadeoutLengthBar(int value)
	{
		fadeoutLengthBar = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7D0
	bool MusicTrack::SetFadeoutLengthBeat(int value)
	{
		fadeoutLengthBeat = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7E0
	bool MusicTrack::SetFadeoutLengthNote(int value)
	{
		fadeoutLengthNote = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A7F0
	bool MusicTrack::SetOverrideFadeIn(bool value)
	{
		overrideFadeIn = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A800
	bool MusicTrack::SetFadeinStartBar(int value)
	{
		fadeinStartBar = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A810
	bool MusicTrack::SetFadeinStartBeat(int value)
	{
		fadeinStartBeat = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A820
	bool MusicTrack::SetFadeinStartNote(int value)
	{
		fadeinStartNote = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A830
	bool MusicTrack::SetFadeinLengthBar(int value)
	{
		fadeinLengthBar = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A840
	bool MusicTrack::SetFadeinLengthBeat(int value)
	{
		fadeinLengthBeat = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A850
	bool MusicTrack::SetFadeinLengthNote(int value)
	{
		fadeinLengthNote = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087B130
	// The compiler's destructor of MusicTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087B050
	MusicTrack::MusicTrack() :
		timeBegin(0.0f),
		unknown14(-1.0f),
		group("", 1),
		priority(0),
		resetPriority(false),
		overrideFadeOut(false),
		fadeoutStartNote(0),
		fadeoutStartBeat(0),
		fadeoutStartBar(0),
		unknown50(0),
		unknown54(false),
		fadeoutLengthNote(0),
		fadeoutLengthBeat(0),
		fadeoutLengthBar(0),
		unknown64(0),
		unknown68(false),
		overrideFadeIn(false),
		fadeinStartNote(0),
		fadeinStartBeat(0),
		fadeinStartBar(0),
		unknown7C(0),
		unknown80(false),
		fadeinLengthNote(0),
		fadeinLengthBeat(0),
		fadeinLengthBar(0),
		unknown90(0),
		unknown94(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1087B110
	float MusicTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1087B120
	float MusicTrack::Slot10() const
	{
		return unknown14 - timeBegin;
	}

	// FUNCTION: ENGINE 0x1087CC10
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch
	void MusicTrack::RegisterProperties()
	{
		if (gMusicTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<MusicTrack>("timeBegin", &MusicTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<MusicTrack>("Group", &MusicTrack::SetGroup);
			properties[1] = property;
			property = new fight::PropertyName<MusicTrack>("Cue", &MusicTrack::SetCue);
			properties[2] = property;
			property = new fight::PropertyName<MusicTrack>("Part", &MusicTrack::SetPart);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<MusicTrack>("Priority", gMusicTrackPriorityTable, 2,
				&MusicTrack::SetPriority);
			properties[4] = property;
			property = new fight::PropertyBool<MusicTrack>("ResetPriority", &MusicTrack::SetResetPriority);
			properties[5] = property;
			property = new fight::PropertyBool<MusicTrack>("OverrideFadeOut", &MusicTrack::SetOverrideFadeOut);
			properties[6] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutStartBar", &MusicTrack::SetFadeoutStartBar);
			properties[7] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutStartBeat", &MusicTrack::SetFadeoutStartBeat);
			properties[8] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutStartNote", &MusicTrack::SetFadeoutStartNote);
			properties[9] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutLengthBar", &MusicTrack::SetFadeoutLengthBar);
			properties[10] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutLengthBeat", &MusicTrack::SetFadeoutLengthBeat);
			properties[11] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeoutLengthNote", &MusicTrack::SetFadeoutLengthNote);
			properties[12] = property;
			property = new fight::PropertyBool<MusicTrack>("OverrideFadeIn", &MusicTrack::SetOverrideFadeIn);
			properties[13] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinStartBar", &MusicTrack::SetFadeinStartBar);
			properties[14] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinStartBeat", &MusicTrack::SetFadeinStartBeat);
			properties[15] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinStartNote", &MusicTrack::SetFadeinStartNote);
			properties[16] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinLengthBar", &MusicTrack::SetFadeinLengthBar);
			properties[17] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinLengthBeat", &MusicTrack::SetFadeinLengthBeat);
			properties[18] = property;
			property = new fight::PropertyIntConstRange<MusicTrack>("FadeinLengthNote", &MusicTrack::SetFadeinLengthNote);
			properties[19] = property;
			fight::RegisterPropertyList(properties, &gMusicTrackProperties);
		}
	}

	// ---- ReverbTrack ----

	// FUNCTION: ENGINE 0x1087AB60
	fight::Property* ReverbTrack::GetProperty(int index)
	{
		return gReverbTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087AB70
	void ReverbTrack::ClearProperties()
	{
		fight::FreePropertyList(&gReverbTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087A890
	bool ReverbTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AD50
	bool ReverbTrack::SetPreset(const fight::Name& value)
	{
		preset = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A8A0
	bool ReverbTrack::SetGain(float value)
	{
		gain = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087B1C0
	// The compiler's destructor of ReverbTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087B150
	ReverbTrack::ReverbTrack() :
		timeBegin(0.0f),
		unknown14(-1.0f),
		gain(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1087B1A0
	float ReverbTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1087B1B0
	float ReverbTrack::Slot10() const
	{
		return unknown14 - timeBegin;
	}

	// FUNCTION: ENGINE 0x1087D040
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch
	void ReverbTrack::RegisterProperties()
	{
		if (gReverbTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<ReverbTrack>("timeBegin", &ReverbTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<ReverbTrack>("preset", &ReverbTrack::SetPreset);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<ReverbTrack>("gain", &ReverbTrack::SetGain);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gReverbTrackProperties);
		}
	}

	// ---- SoundZoneTrack ----

	// FUNCTION: ENGINE 0x1087ABC0
	fight::Property* SoundZoneTrack::GetProperty(int index)
	{
		return gSoundZoneTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1087ABD0
	void SoundZoneTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSoundZoneTrackProperties);
	}

	// FUNCTION: ENGINE 0x1087AD70
	bool SoundZoneTrack::SetZoneName(const fight::Name& value)
	{
		zoneName = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087AD90
	bool SoundZoneTrack::SetReverb(const fight::Name& value)
	{
		reverb = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ADB0
	bool SoundZoneTrack::SetAmbience(const fight::Name& value)
	{
		ambience = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087ADD0
	bool SoundZoneTrack::SetMix(const fight::Name& value)
	{
		mix = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087A8B0
	bool SoundZoneTrack::SetBoundaryAction(int value)
	{
		boundaryAction = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1087B250
	// The compiler's destructor of SoundZoneTrack (the class declares none)
	// FUNCTION: ENGINE 0x1087B1E0
	SoundZoneTrack::SoundZoneTrack() :
		boundaryAction(0)
	{
	}

	// FUNCTION: ENGINE 0x1087B230
	float SoundZoneTrack::GetTimeBegin() const
	{
		return unknown10;
	}

	// FUNCTION: ENGINE 0x1087B240
	float SoundZoneTrack::Slot10() const
	{
		return unknown14 - unknown10;
	}

	// FUNCTION: ENGINE 0x1087D120
	// EQUIVALENT: shrink-wrap, the engine saves esi in the entry block before the guard's branch
	void SoundZoneTrack::RegisterProperties()
	{
		if (gSoundZoneTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<SoundZoneTrack>("ZoneName", &SoundZoneTrack::SetZoneName);
			properties[0] = property;
			property = new fight::PropertyName<SoundZoneTrack>("reverb", &SoundZoneTrack::SetReverb);
			properties[1] = property;
			property = new fight::PropertyName<SoundZoneTrack>("ambience", &SoundZoneTrack::SetAmbience);
			properties[2] = property;
			property = new fight::PropertyName<SoundZoneTrack>("mix", &SoundZoneTrack::SetMix);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<SoundZoneTrack>("BoundaryAction", gSoundZoneTrackBoundaryActionTable, 2,
				&SoundZoneTrack::SetBoundaryAction);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gSoundZoneTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1087BEB0
	// FUNCTION: ENGINE 0x1087BED0
	// FUNCTION: ENGINE 0x1087BEF0
	template class fight::PropertyFloatConstRange<SoundBoolValueTrack>;
	// FUNCTION: ENGINE 0x1087BF00
	// FUNCTION: ENGINE 0x1087BF20
	// FUNCTION: ENGINE 0x1087BF40
	template class fight::PropertyBool<SoundBoolValueTrack>;
	// FUNCTION: ENGINE 0x1087C4B0
	// FUNCTION: ENGINE 0x1087C4D0
	template class fight::PropertyName<SoundBoolValueTrack>;
	// FUNCTION: ENGINE 0x1087BF50
	// FUNCTION: ENGINE 0x1087BF70
	// FUNCTION: ENGINE 0x1087BF90
	template class fight::PropertyFloatConstRange<MixerTrack>;
	// FUNCTION: ENGINE 0x1087BFA0
	// FUNCTION: ENGINE 0x1087BFC0
	// FUNCTION: ENGINE 0x1087BFE0
	template class fight::PropertyBool<MixerTrack>;
	// FUNCTION: ENGINE 0x1087C4F0
	// FUNCTION: ENGINE 0x1087C510
	template class fight::PropertyName<MixerTrack>;
	// FUNCTION: ENGINE 0x1087BFF0
	// FUNCTION: ENGINE 0x1087C010
	// FUNCTION: ENGINE 0x1087C030
	template class fight::PropertyFloatConstRange<MusicTrack>;
	// FUNCTION: ENGINE 0x1087C040
	// FUNCTION: ENGINE 0x1087C070
	// FUNCTION: ENGINE 0x1087C080
	// FUNCTION: ENGINE 0x1087C0A0
	// FUNCTION: ENGINE 0x1087C0C0
	template class fight::PropertyEnumConstList<MusicTrack>;
	// FUNCTION: ENGINE 0x1087C0D0
	// FUNCTION: ENGINE 0x1087C0F0
	// FUNCTION: ENGINE 0x1087C110
	template class fight::PropertyBool<MusicTrack>;
	// FUNCTION: ENGINE 0x1087C120
	// FUNCTION: ENGINE 0x1087C140
	// FUNCTION: ENGINE 0x1087C160
	template class fight::PropertyIntConstRange<MusicTrack>;
	// FUNCTION: ENGINE 0x1087C530
	// FUNCTION: ENGINE 0x1087C550
	template class fight::PropertyName<MusicTrack>;
	// FUNCTION: ENGINE 0x1087C170
	// FUNCTION: ENGINE 0x1087C190
	// FUNCTION: ENGINE 0x1087C1B0
	template class fight::PropertyFloatConstRange<ReverbTrack>;
	// FUNCTION: ENGINE 0x1087C570
	// FUNCTION: ENGINE 0x1087C590
	template class fight::PropertyName<ReverbTrack>;
	// FUNCTION: ENGINE 0x1087C1C0
	// FUNCTION: ENGINE 0x1087C1F0
	// FUNCTION: ENGINE 0x1087C200
	// FUNCTION: ENGINE 0x1087C220
	// FUNCTION: ENGINE 0x1087C240
	template class fight::PropertyEnumConstList<SoundZoneTrack>;
	// FUNCTION: ENGINE 0x1087C5B0
	// FUNCTION: ENGINE 0x1087C5D0
	template class fight::PropertyName<SoundZoneTrack>;
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gMixerDefaultCategory("default", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D76560
// FUNCTION: ENGINE 0x10D765E0
// FUNCTION: ENGINE 0x10D8A820
// FUNCTION: ENGINE 0x10D8A840


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D741D0
// FUNCTION: ENGINE 0x10D89DF0
