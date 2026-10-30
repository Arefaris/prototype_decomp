// The fight track of the non-interactive sequences that hides and blocks what is inside up to three volumes while a
// sequence plays (RTTI proto::NISExcludeVolumeTrack and proto::NISExcludeVolumeAction). Unit 0x10576000 - 0x10578740
// (no assert path; the file name is a guess). The class names are original, the members are guessed.
#ifndef PROTO_NIS_NISEXCLUDEVOLUME_H
#define PROTO_NIS_NISEXCLUDEVOLUME_H

#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/trackfactory.h"

namespace proto
{
	class NISExcludeVolumeTrack : public fight::Track
	{
	public:
		// 0x10577E50
		NISExcludeVolumeTrack();
		virtual ~NISExcludeVolumeTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10577520)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetVolumeName1(const fight::Name& value);
		bool SetVolumeName2(const fight::Name& value);
		bool SetVolumeName3(const fight::Name& value);
		bool SetActionOnProps(int value);
		bool SetHideAndBlockAmbients(bool value);
		bool SetHideAndBlockDrivables(bool value);
		bool SetHideAndBlockWalkers(bool value);
		bool SetHideAndBlockHunters(bool value);
		bool SetDeleteDeadBodies(bool value);
		bool SetMaxHiddenObjects(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name volumeName1;  // +0x10
		fight::Name volumeName2;  // +0x18
		fight::Name volumeName3;  // +0x20
		float timeBegin;  // +0x28
		float timeEnd;  // +0x2C
		int actionOnProps;  // +0x30
		int maxHiddenObjects;  // +0x34
		bool deleteDeadBodies;  // +0x38
		bool hideAndBlockAmbients;  // +0x39
		bool hideAndBlockDrivables;  // +0x3A
		bool hideAndBlockHunters;  // +0x3B
		bool hideAndBlockWalkers;  // +0x3C
	};

	extern fight::Property** gNISExcludeVolumeTrackProperties;
	fight::TrackFactory* CreateNISExcludeVolumeTrackFactory(const char* name);
	void RegisterNISExcludeVolumeTrackFactory(fight::TrackRegistry* registry, const char* name);
}

#endif
