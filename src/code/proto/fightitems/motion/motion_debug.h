// Fight items of the motion group: DebugLayerCondition, DebugSphereTrack, DebugAxisTrack (unit 0x101521B0 - 0x10153160; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DEBUG_H
#define PROTO_FIGHTITEMS_MOTION_DEBUG_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DebugLayerCondition (10 vftable slots, 0x14 bytes)
			class DebugLayerCondition : public fight::Condition
			{
			public:
				// 0x10152360
				DebugLayerCondition();
				virtual ~DebugLayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B0700, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDebugLayer(const char* newValue);
				bool SetEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* debugLayer;  // +0xC
					bool enabled;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gDebugLayerConditionProperties;
			fight::ConditionFactory* CreateDebugLayerConditionFactory(const char* name);
			void RegisterDebugLayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DebugSphereTrack (16 vftable slots, 0x40 bytes)
			class DebugSphereTrack : public fight::Track
			{
			public:
				// 0x101524C0
				DebugSphereTrack();
				virtual ~DebugSphereTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B0710, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetColour(const math::Colour128& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Colour128 colour;  // +0x18
					math::Vector offset;  // +0x28
					float radius;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
			};

			extern fight::Property** gDebugSphereTrackProperties;
			fight::TrackFactory* CreateDebugSphereTrackFactory(const char* name);
			void RegisterDebugSphereTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DebugAxisTrack (16 vftable slots, 0x28 bytes)
			class DebugAxisTrack : public fight::Track
			{
			public:
				// 0x10152570
				DebugAxisTrack();
				virtual ~DebugAxisTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B0720, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetScale(float newValue);
				bool SetJoint(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					float scale;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gDebugAxisTrackProperties;
			fight::TrackFactory* CreateDebugAxisTrackFactory(const char* name);
			void RegisterDebugAxisTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
