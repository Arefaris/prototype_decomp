// engine::NIS (RTTI and reflection names; "non-interactive sequence"): a content library object that describes a
// scripted scene. It lists the objects the scene inserts (by template and transform), places, animates, attaches
// to each other, shows and hides (visibility keys), the light groups it uses, its subtitles, the time slices and
// shot boundaries (times) and the radius of the area it excludes. Unit 0x1088B6E0 - 0x10890900 (no assert path; the
// directory and file name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_NIS_NIS_H
#define ENGINE_NIS_NIS_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/math/matrix.h"

namespace container
{
	// The float arrays' assignment is small enough for the compiler to expand in place where it likes
	template<> inline float* AssignRange<float>(const float* first, const float* last, float* dest)
	{
		for (; first != last; dest++, first++)
		{
			*dest = *first;
		}
		return dest;
	}
}

namespace engine
{
	// A transform as the scene structs hold it: four rows of four floats whose copy the engine runs row by row
	// (the row's copy constructor, 0x10070B20, is out of line), and which it assigns element by element. The
	// layout of math::Matrix.
	struct NISRow
	{
		NISRow()
		{
		}
		NISRow(const NISRow& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}
		NISRow& operator=(const NISRow& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			return *this;
		}

		float x;
		float y;
		float z;
		float w;
	};

	// The word behind an array that the structs' copies leave alone
	struct NISSpareWord
	{
		NISSpareWord()
		{
		}
		NISSpareWord(const NISSpareWord& other)
		{
		}
		NISSpareWord& operator=(const NISSpareWord& other)
		{
			return *this;
		}

		int value;
	};

	struct NISTransform
	{
		// Sets the identity element by element
		__forceinline void SetIdentity()
		{
			const math::Matrix& identity = math::Matrix::IDENTITY;
			rows[0].x = identity.m[0][0];
			rows[0].y = identity.m[0][1];
			rows[0].z = identity.m[0][2];
			rows[0].w = identity.m[0][3];
			rows[1].x = identity.m[1][0];
			rows[1].y = identity.m[1][1];
			rows[1].z = identity.m[1][2];
			rows[1].w = identity.m[1][3];
			rows[2].x = identity.m[2][0];
			rows[2].y = identity.m[2][1];
			rows[2].z = identity.m[2][2];
			rows[2].w = identity.m[2][3];
			rows[3].x = identity.m[3][0];
			rows[3].y = identity.m[3][1];
			rows[3].z = identity.m[3][2];
			rows[3].w = identity.m[3][3];
		}

		NISRow rows[4];
	};

	struct NIS : public content::MetaLoadObject
	{
		// An object the scene inserts, made from a template
		struct Insertion
		{
			Insertion();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> object;  // +0
			core::Name<core::CaseSensitiveKey> objectTemplate;  // +8
			NISTransform transform;  // +0x10
		};

		// Where an object is put
		struct Placement
		{
			Placement();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> object;  // +0
			NISTransform transform;  // +8
		};

		// An animation an object plays
		struct Animation
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> animation;  // +0
			core::Name<core::CaseSensitiveKey> object;  // +8
		};

		// An object attached to a joint of another
		struct Attachment
		{
			Attachment();
			__forceinline Attachment(const Attachment& other) : parent(other.parent), parentJoint(other.parentJoint),
				child(other.child), childTransform(other.childTransform)
			{
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> parent;  // +0
			core::Name<core::CaseSensitiveKey> parentJoint;  // +8
			core::Name<core::CaseSensitiveKey> child;  // +0x10
			NISTransform childTransform;  // +0x18
		};

		typedef container::ArrayDynamic<float, container::AllocatorNew> FloatArray;

		// The times an object is shown or hidden at
		struct Visibility
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> object;  // +0
			bool startVisibility;  // +8
			FloatArray keys;  // +0xC
			// The word behind the array (the arrays of this kind are followed by one; never touched here)
			NISSpareWord unknown18;  // +0x18
		};

		// A light group an object belongs to
		struct LightGroup
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> lightGroupName;  // +0
			core::Name<core::CaseSensitiveKey> object;  // +8
		};

		// A subtitle and the time span it is shown for
		struct SubTitle
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> subTitleId;  // +0
			float timeBegin;  // +8
			float timeEnd;  // +0xC
		};

		typedef container::ArrayDynamic<Insertion, container::AllocatorNew> InsertionArray;
		typedef container::ArrayDynamic<Placement, container::AllocatorNew> PlacementArray;
		typedef container::ArrayDynamic<Animation, container::AllocatorNew> AnimationArray;
		typedef container::ArrayDynamic<Attachment, container::AllocatorNew> AttachmentArray;
		typedef container::ArrayDynamic<Visibility, container::AllocatorNew> VisibilityArray;
		typedef container::ArrayDynamic<LightGroup, container::AllocatorNew> LightGroupArray;
		typedef container::ArrayDynamic<SubTitle, container::AllocatorNew> SubTitleArray;

		// 0x108E0F90 (the unit's tail, where the factory makes the object)
		NIS();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Every array is followed by a word that nobody touches
		InsertionArray insertions;  // +8
		int unknown14;
		PlacementArray placements;  // +0x18
		int unknown24;
		AnimationArray animations;  // +0x28
		int unknown34;
		AttachmentArray attachments;  // +0x38
		int unknown44;
		VisibilityArray visibilities;  // +0x48
		int unknown54;
		LightGroupArray lightGroups;  // +0x58
		int unknown64;
		SubTitleArray subTitles;  // +0x68
		int unknown74;
		FloatArray timeSlices;  // +0x78
		int unknown84;
		FloatArray shotBoundaries;  // +0x88
		int unknown94;
		float exclusionRadius;  // +0x98
	};
}

namespace container
{
	// The scene structs are too large for the compiler to inline the assignment of their elements
	template<> struct ArrayEraseInline<engine::NIS::Insertion>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::Placement>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::Animation>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::Attachment>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::Visibility>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::LightGroup>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::NIS::SubTitle>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The element access of the scene arrays for their meta types. Where the elements' copy is too large for the
	// compiler to expand in place, the engine's Insert fills the gap with the array's fill (one copy); the arrays
	// of subtitles use the generic helper.
#define ENGINE_NIS_FILL_HELPER(Element) 	template<> class ArrayDynamicHelper<container::ArrayDynamic<engine::NIS::Element, container::AllocatorNew> > 		: public ArrayDynamicHelperBase 	{ 	public: 		typedef container::ArrayDynamic<engine::NIS::Element, container::AllocatorNew> A; 		typedef engine::NIS::Element T;  		virtual int Size(void* array) 		{ 			return ((A*)array)->Size(); 		} 		virtual void* Get(void* array, int index) 		{ 			return ((A*)array)->begin + index; 		} 		virtual void* GetConst(void* array, int index) 		{ 			return ((A*)array)->begin + index; 		} 		virtual void Insert(void* array, int index, int unused) 		{ 			A* a = (A*)array; 			if (a->Size() >= a->Capacity()) 			{ 				a->Reserve(a->Size() + 1); 			} 			T* position = a->begin + index; 			static T sDefault; 			a->Insert(position, 1, sDefault); 		} 		virtual void Erase(void* array, int index, int unused) 		{ 			A* a = (A*)array; 			a->Erase(a->begin + index); 		} 		virtual int Capacity(void* array) 		{ 			return ((A*)array)->Capacity(); 		} 		virtual void Expand(void* array, unsigned int count) 		{ 			A* a = (A*)array; 			if (a->Capacity() == 0) 			{ 				a->Allocate(count); 			} 			else if (count + a->Size() > a->Capacity()) 			{ 				a->Reserve(count + a->Size()); 			} 		} 	};

	ENGINE_NIS_FILL_HELPER(Insertion)
	ENGINE_NIS_FILL_HELPER(Placement)
	ENGINE_NIS_FILL_HELPER(Animation)
	ENGINE_NIS_FILL_HELPER(Attachment)
	ENGINE_NIS_FILL_HELPER(Visibility)
	ENGINE_NIS_FILL_HELPER(LightGroup)
#undef ENGINE_NIS_FILL_HELPER

	// The same for an array of floats (the engine expands the removal and the insertion with loops of their own
	// here too, and shares the default element, a float, with the other users of the template)
	template<> class ArrayDynamicHelper<container::ArrayDynamic<float, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<float, container::AllocatorNew> A;
		typedef float T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			T* from = a->end;
			if (from + 1 <= a->capacity)
			{
				T* to = from + 1;
				a->end = to;
				while (from != position)
				{
					from--;
					to--;
					if (to != 0)
					{
						*to = *from;
					}
				}
				if (position != 0)
				{
					*position = Default();
				}
			}
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			T* position = a->begin + index;
			T* last = a->end;
			T* destination = position;
			for (T* source = position + 1; source != last; source++, destination++)
			{
				*destination = *source;
			}
			a->end--;
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
