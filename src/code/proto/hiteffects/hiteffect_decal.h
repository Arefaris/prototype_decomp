// Fight items of the hit effects: DecalTrack (unit 0x105049C0 - 0x10505220; no assert path, the file name is a guess).
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECT_DECAL_H
#define PROTO_HITEFFECTMANAGER_HITEFFECT_DECAL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/hiteffects/hiteffectdata.h"

namespace proto
{
	namespace HitEffectManager
	{
		// RTTI: proto::HitEffectManager::DecalTrack (16 vftable slots, 0x38 bytes)
		class DecalTrack : public fight::Track
		{
		public:
			// 0x10504AE0
			DecalTrack();
			virtual ~DecalTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x104FBEA0, another unit)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetShaderName(const fight::Name& newValue);
			bool SetRandomSelect(int newValue);
			bool SetRandomOrientation(float newValue);
			bool SetScaleByDamage(bool newValue);
			bool SetScaleX(float newValue);
			bool SetScaleY(float newValue);
			bool SetPatch(const char* newValue);
			bool SetDecalStore(int newValue);
			bool SetCullOffscreen(bool newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name shaderName;  // +0x10
			char* patch;  // +0x18
			float randomOrientation;  // +0x1C
			float scaleX;  // +0x20
			float scaleY;  // +0x24
			int decalStore;  // +0x28
			int randomSelect;  // +0x2C
			bool cullOffscreen;  // +0x30
			bool scaleByDamage;  // +0x31
			unsigned char unknown32[0x6];
		};

		extern fight::Property** gDecalTrackProperties;
		fight::TrackFactory* CreateDecalTrackFactory(const char* name);
		void RegisterDecalTrackFactory(fight::TrackRegistry* registry, const char* name);

	}
}

#endif
