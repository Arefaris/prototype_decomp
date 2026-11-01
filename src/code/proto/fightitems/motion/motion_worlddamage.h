// Fight items of the motion group: WorldDamageTrack, ExplicitWorldDamageTrack, WorldConeDamageTrack, ExplicitWorldConeDamageTrack (unit 0x1050DEE0 - 0x10510A30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WORLDDAMAGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WORLDDAMAGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/worlddamagedata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WorldDamageTrack (16 vftable slots, 0x70 bytes)
			class WorldDamageTrack : public fight::Track
			{
			public:
				// 0x1050E3C0
				WorldDamageTrack();
				virtual ~WorldDamageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10502D00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetPosition(const math::Vector& newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetUseSupportingLimb(bool newValue);
				bool SetDistance(float newValue);
				bool SetDamageType(int newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetEffectType(const fight::Name& newValue);
				bool SetScaleX(float newValue);
				bool SetScaleY(float newValue);
				bool SetEffectScale(float newValue);
				bool SetPropAreaEmissionScale(float newValue);
				bool SetPropAreaEmissionScaleFunction(int newValue);
				bool SetPropAreaSizeScale(float newValue);
				bool SetPropAreaSizeScaleFunction(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				fight::Name effectType;  // +0x10
				fight::Name hitType;  // +0x18
				fight::Name joint;  // +0x20
				math::Vector direction;  // +0x28
				math::Vector position;  // +0x34
				float distance;  // +0x40
				float effectScale;  // +0x44
				float propAreaEmissionScale;  // +0x48
				float propAreaSizeScale;  // +0x4C
				float scaleX;  // +0x50
				float scaleY;  // +0x54
				float timeBegin;  // +0x58
				int attackType;  // +0x5C
				int damageType;  // +0x60
				int propAreaEmissionScaleFunction;  // +0x64
				int propAreaSizeScaleFunction;  // +0x68
				bool useSupportingLimb;  // +0x6C
				unsigned char unknown6D[0x3];
			};

			extern fight::Property** gWorldDamageTrackProperties;
			fight::TrackFactory* CreateWorldDamageTrackFactory(const char* name);
			void RegisterWorldDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ExplicitWorldDamageTrack (16 vftable slots, 0x80 bytes)
			class ExplicitWorldDamageTrack : public WorldDamageTrack
			{
			public:
				// 0x1050E4B0
				ExplicitWorldDamageTrack();
				virtual ~ExplicitWorldDamageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 15 (0x10502D50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetObject(const fight::Name& newValue);
				bool SetToBeContinued(bool newValue);
				// TODO SetTimeBegin
				// TODO SetJoint
				// TODO SetPosition
				// TODO SetDirection
				// TODO SetUseSupportingLimb
				// TODO SetDistance
				// TODO SetDamageType
				// TODO SetAttackType
				// TODO SetHitType
				// TODO SetEffectType
				// TODO SetScaleX
				// TODO SetScaleY
				// TODO SetEffectScale
				// TODO SetPropAreaEmissionScale
				// TODO SetPropAreaEmissionScaleFunction
				// TODO SetPropAreaSizeScale
				// TODO SetPropAreaSizeScaleFunction

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				fight::Name object;  // +0x70
				bool toBeContinued;  // +0x78
				unsigned char unknown79[0x7];
			};

			extern fight::Property** gExplicitWorldDamageTrackProperties;
			fight::TrackFactory* CreateExplicitWorldDamageTrackFactory(const char* name);
			void RegisterExplicitWorldDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WorldConeDamageTrack (16 vftable slots, 0x70 bytes)
			class WorldConeDamageTrack : public fight::Track
			{
			public:
				// 0x1050E4F0
				WorldConeDamageTrack();
				virtual ~WorldConeDamageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x105035F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetPosition(const math::Vector& newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetUp(const math::Vector& newValue);
				bool SetMinAngle(float newValue);
				bool SetMaxAngle(float newValue);
				bool SetStartDistance(float newValue);
				bool SetLength(float newValue);
				bool SetMinDecals(int newValue);
				bool SetMaxDecals(int newValue);
				bool SetMinDecalScale(float newValue);
				bool SetMaxDecalScale(float newValue);
				bool SetDamageType(int newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetEffectType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				fight::Name effectType;  // +0x10
				fight::Name hitType;  // +0x18
				math::Vector direction;  // +0x20
				math::Vector position;  // +0x2C
				math::Vector up;  // +0x38
				float length;  // +0x44
				float maxAngle;  // +0x48
				float maxDecalScale;  // +0x4C
				float minAngle;  // +0x50
				float minDecalScale;  // +0x54
				float startDistance;  // +0x58
				float timeBegin;  // +0x5C
				int attackType;  // +0x60
				int damageType;  // +0x64
				int maxDecals;  // +0x68
				int minDecals;  // +0x6C
			};

			extern fight::Property** gWorldConeDamageTrackProperties;
			fight::TrackFactory* CreateWorldConeDamageTrackFactory(const char* name);
			void RegisterWorldConeDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ExplicitWorldConeDamageTrack (16 vftable slots, 0x80 bytes)
			class ExplicitWorldConeDamageTrack : public WorldConeDamageTrack
			{
			public:
				// 0x1050E600
				ExplicitWorldConeDamageTrack();
				virtual ~ExplicitWorldConeDamageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 15 (0x10503640, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetObject(const fight::Name& newValue);
				bool SetToBeContinued(bool newValue);
				// TODO SetTimeBegin
				// TODO SetPosition
				// TODO SetDirection
				// TODO SetUp
				// TODO SetMinAngle
				// TODO SetMaxAngle
				// TODO SetStartDistance
				// TODO SetLength
				// TODO SetMinDecals
				// TODO SetMaxDecals
				// TODO SetMinDecalScale
				// TODO SetMaxDecalScale
				// TODO SetDamageType
				// TODO SetAttackType
				// TODO SetHitType
				// TODO SetEffectType

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				fight::Name object;  // +0x70
				bool toBeContinued;  // +0x78
				unsigned char unknown79[0x7];
			};

			extern fight::Property** gExplicitWorldConeDamageTrackProperties;
			fight::TrackFactory* CreateExplicitWorldConeDamageTrackFactory(const char* name);
			void RegisterExplicitWorldConeDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
