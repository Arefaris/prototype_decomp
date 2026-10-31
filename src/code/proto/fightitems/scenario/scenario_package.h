// Fight items of the scenario group: PackageReadyCondition, PackageLoadTrack, PackageUnloadTrack (unit 0x101D9540 - 0x101D9FB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_PACKAGE_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_PACKAGE_H

#include "code/engine/system/streampackage.h"
#include "code/core/linklist.h"
#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	// 0x104887E0 (another unit, name unknown): tells the game that a package is being let go
	void Unknown104887E0(const core::Name<core::CaseSensitiveKey>& packageName);
}

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::PackageReadyCondition (10 vftable slots, 0x10 bytes)
			class PackageReadyCondition : public fight::Condition
			{
			public:
				// 0x101D9580
				PackageReadyCondition();
				virtual ~PackageReadyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D6060, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPackageName(const char* newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* packageName;  // +0xC
			};

			extern fight::Property** gPackageReadyConditionProperties;
			fight::ConditionFactory* CreatePackageReadyConditionFactory(const char* name);
			void RegisterPackageReadyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::PackageLoadTrack (16 vftable slots, 0x18 bytes)
			class PackageLoadTrack : public fight::Track
			{
			public:
				// 0x101D9640
				PackageLoadTrack();
				virtual ~PackageLoadTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D6580, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetPackageName(const char* newValue);
				bool SetAsync(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* packageName;  // +0x10
					bool async;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gPackageLoadTrackProperties;
			fight::TrackFactory* CreatePackageLoadTrackFactory(const char* name);
			void RegisterPackageLoadTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::PackageUnloadTrack (16 vftable slots, 0x14 bytes)
			class PackageUnloadTrack : public fight::Track
			{
			public:
				// 0x101D9720
				PackageUnloadTrack();
				virtual ~PackageUnloadTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D65B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetPackageName(const char* newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* packageName;  // +0x10
			};

			extern fight::Property** gPackageUnloadTrackProperties;
			fight::TrackFactory* CreatePackageUnloadTrackFactory(const char* name);
			void RegisterPackageUnloadTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::PackageLoadAction (9 vftable slots, size 0x28): asks for the track's package
			class PackageLoadAction : public fight::Action
			{
			public:
				// 0x101D6340 (the destructor is 0x101D61E0, the deleting destructor 0x101D63B0)
				PackageLoadAction(PackageLoadTrack* newTrack);
				virtual ~PackageLoadAction();

				// vftable slot 5 (0x101D63E0) and slot 6 (0x101D6020)
				virtual bool Slot5(int arg, float value);
				virtual void Slot6();

				core::Link<PackageLoadTrack> link;  // +0x1C
			};

			// RTTI: proto::fightitems::scenario::PackageUnloadAction (9 vftable slots, size 0x28): lets the track's package go
			class PackageUnloadAction : public fight::Action
			{
			public:
				// 0x101D6450 (the destructor is 0x101D6230, the deleting destructor 0x101D64C0)
				PackageUnloadAction(PackageUnloadTrack* newTrack);
				virtual ~PackageUnloadAction();

				// vftable slot 5 (0x101D64F0) and slot 6 (0x101D6030)
				virtual bool Slot5(int arg, float value);
				virtual void Slot6();

				core::Link<PackageUnloadTrack> link;  // +0x1C
			};

			// 0x11254CF8: the slot group name the package is loaded under (name guess)
			extern const content::ObjectName gPackageLoadSlotGroup;
		}
	}
}

#endif
