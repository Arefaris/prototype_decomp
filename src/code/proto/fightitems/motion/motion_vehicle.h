// Fight items of the motion group: HelicopterHeightAboveGroundCondition, HelicopterRotorCollisionCondition, SecondaryWeaponTypeCondition, VehiclePowerOnOffCondition, HelicopterOnGroundCondition, SetVehicleAnimatedTrack, HelicopterSpawnBloodtoxTrack, VehiclePlayAnimationTrack, SetVehicleHeadlightTrack, VehiclePowerOnOffTrack, SetSecondaryWeaponTypeTrack, SetVehicleSolverEnabledTrack (unit 0x101C8410 - 0x101CAFF0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_VEHICLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_VEHICLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HelicopterHeightAboveGroundCondition (10 vftable slots, 0x14 bytes)
			class HelicopterHeightAboveGroundCondition : public fight::Condition
			{
			public:
				// 0x101C8620
				HelicopterHeightAboveGroundCondition();
				virtual ~HelicopterHeightAboveGroundCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012A5C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float height;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gHelicopterHeightAboveGroundConditionProperties;
			fight::ConditionFactory* CreateHelicopterHeightAboveGroundConditionFactory(const char* name);
			void RegisterHelicopterHeightAboveGroundConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HelicopterRotorCollisionCondition (10 vftable slots, 0x14 bytes)
			class HelicopterRotorCollisionCondition : public fight::Condition
			{
			public:
				// 0x101C8690
				HelicopterRotorCollisionCondition();
				virtual ~HelicopterRotorCollisionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012A410, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gHelicopterRotorCollisionConditionProperties;
			fight::ConditionFactory* CreateHelicopterRotorCollisionConditionFactory(const char* name);
			void RegisterHelicopterRotorCollisionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SecondaryWeaponTypeCondition (10 vftable slots, 0x14 bytes)
			class SecondaryWeaponTypeCondition : public fight::Condition
			{
			public:
				// 0x101C8700
				SecondaryWeaponTypeCondition();
				virtual ~SecondaryWeaponTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012AA00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int type;  // +0x10
			};

			extern fight::Property** gSecondaryWeaponTypeConditionProperties;
			fight::ConditionFactory* CreateSecondaryWeaponTypeConditionFactory(const char* name);
			void RegisterSecondaryWeaponTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VehiclePowerOnOffCondition (10 vftable slots, 0x10 bytes)
			class VehiclePowerOnOffCondition : public fight::Condition
			{
			public:
				// 0x101C8770
				VehiclePowerOnOffCondition();
				virtual ~VehiclePowerOnOffCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012A690, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPowerOn(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool powerOn;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gVehiclePowerOnOffConditionProperties;
			fight::ConditionFactory* CreateVehiclePowerOnOffConditionFactory(const char* name);
			void RegisterVehiclePowerOnOffConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HelicopterOnGroundCondition (10 vftable slots, 0x14 bytes)
			class HelicopterOnGroundCondition : public fight::Condition
			{
			public:
				// 0x101C87D0
				HelicopterOnGroundCondition();
				virtual ~HelicopterOnGroundCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012A4F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gHelicopterOnGroundConditionProperties;
			fight::ConditionFactory* CreateHelicopterOnGroundConditionFactory(const char* name);
			void RegisterHelicopterOnGroundConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetVehicleAnimatedTrack (16 vftable slots, 0x14 bytes)
			class SetVehicleAnimatedTrack : public fight::Track
			{
			public:
				// 0x101C8840
				SetVehicleAnimatedTrack();
				virtual ~SetVehicleAnimatedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B7B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetAnimated(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool animated;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gSetVehicleAnimatedTrackProperties;
			fight::TrackFactory* CreateSetVehicleAnimatedTrackFactory(const char* name);
			void RegisterSetVehicleAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HelicopterSpawnBloodtoxTrack (16 vftable slots, 0x18 bytes)
			class HelicopterSpawnBloodtoxTrack : public fight::Track
			{
			public:
				// 0x101C88D0
				HelicopterSpawnBloodtoxTrack();
				virtual ~HelicopterSpawnBloodtoxTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B690, another unit)
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

			extern fight::Property** gHelicopterSpawnBloodtoxTrackProperties;
			fight::TrackFactory* CreateHelicopterSpawnBloodtoxTrackFactory(const char* name);
			void RegisterHelicopterSpawnBloodtoxTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VehiclePlayAnimationTrack (16 vftable slots, 0x18 bytes)
			class VehiclePlayAnimationTrack : public fight::Track
			{
			public:
				// 0x101C8970
				VehiclePlayAnimationTrack();
				virtual ~VehiclePlayAnimationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B5D0, another unit)
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

			extern fight::Property** gVehiclePlayAnimationTrackProperties;
			fight::TrackFactory* CreateVehiclePlayAnimationTrackFactory(const char* name);
			void RegisterVehiclePlayAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetVehicleHeadlightTrack (16 vftable slots, 0x14 bytes)
			class SetVehicleHeadlightTrack : public fight::Track
			{
			public:
				// 0x101C8A10
				SetVehicleHeadlightTrack();
				virtual ~SetVehicleHeadlightTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B810, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool enabled;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gSetVehicleHeadlightTrackProperties;
			fight::TrackFactory* CreateSetVehicleHeadlightTrackFactory(const char* name);
			void RegisterSetVehicleHeadlightTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VehiclePowerOnOffTrack (16 vftable slots, 0x18 bytes)
			class VehiclePowerOnOffTrack : public fight::Track
			{
			public:
				// 0x101C8AA0
				VehiclePowerOnOffTrack();
				virtual ~VehiclePowerOnOffTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B630, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetPowerOn(bool newValue);
				bool SetUseSpinup(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool powerOn;  // +0x14
					bool useSpinup;  // +0x15
					unsigned char unknown16[0x2];
			};

			extern fight::Property** gVehiclePowerOnOffTrackProperties;
			fight::TrackFactory* CreateVehiclePowerOnOffTrackFactory(const char* name);
			void RegisterVehiclePowerOnOffTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetSecondaryWeaponTypeTrack (16 vftable slots, 0x18 bytes)
			class SetSecondaryWeaponTypeTrack : public fight::Track
			{
			public:
				// 0x101C8B40
				SetSecondaryWeaponTypeTrack();
				virtual ~SetSecondaryWeaponTypeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B6F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int type;  // +0x14
			};

			extern fight::Property** gSetSecondaryWeaponTypeTrackProperties;
			fight::TrackFactory* CreateSetSecondaryWeaponTypeTrackFactory(const char* name);
			void RegisterSetSecondaryWeaponTypeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetVehicleSolverEnabledTrack (16 vftable slots, 0x14 bytes)
			class SetVehicleSolverEnabledTrack : public fight::Track
			{
			public:
				// 0x101C8BE0
				SetVehicleSolverEnabledTrack();
				virtual ~SetVehicleSolverEnabledTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012B750, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool enabled;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gSetVehicleSolverEnabledTrackProperties;
			fight::TrackFactory* CreateSetVehicleSolverEnabledTrackFactory(const char* name);
			void RegisterSetVehicleSolverEnabledTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
