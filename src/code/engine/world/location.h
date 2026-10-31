// engine::world::Location (RTTI and reflection name; a library object of the world; base content::MetaLoadObject). The
// layout is not recovered: the class is its size, its constructor, the two functions of its reflection and the two
// functions the world stream manager calls. Names other than the RTTI one are guesses.
#ifndef ENGINE_WORLD_LOCATION_H
#define ENGINE_WORLD_LOCATION_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace engine
{
	class StreamPackageInstance;

	namespace world
	{
		class Location : public content::MetaLoadObject
		{
		public:
			// 0x108D6580; the reflection is 0x108D5F50 / 0x108D64A0
			Location();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();
			// 0x108D6170 / 0x108D61E0: what the world stream manager hands a loading / unloading package instance to (names
			// unknown)
			void Unknown108D6170(StreamPackageInstance* instance);
			void Unknown108D61E0(StreamPackageInstance* instance);

			unsigned char unknown8[0x3C];
		};
	}
}

#endif
