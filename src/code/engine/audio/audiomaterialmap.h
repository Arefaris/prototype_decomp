// The audio library's material map (RTTI: engine::AudioMaterialMap, an om entity named "MaterialMap") and its om
// reflection (audiomaterialmap.cpp): a dictionary from the names of materials to the names of sounds, reflected as
// "Map".
#ifndef ENGINE_AUDIOMATERIALMAP_H
#define ENGINE_AUDIOMATERIALMAP_H

#include "code/om/dictionary.h"
#include "code/om/entity.h"

namespace engine
{
	typedef om::Dictionary<om::ClassName, om::ClassName, om::Comparer<om::ClassName> > MaterialDictionary;

	// The map entity (0x38 bytes)
	class AudioMaterialMap : public om::Entity
	{
	public:
		explicit AudioMaterialMap(const om::ClassName& newName);
		virtual ~AudioMaterialMap();
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(AudioMaterialMap);

		const MaterialDictionary& GetMap() const;
		void SetMap(const MaterialDictionary& newMap);

		char unknown10[0x10];
		MaterialDictionary map;  // 0x20
	};
}

#endif
