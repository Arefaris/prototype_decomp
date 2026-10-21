// engine::TrackedMotionToExpressionMap (RTTI and reflection names): a content library object that drives the
// expressions of an expression group (blend shapes) from the motion of tracked joints. Per joint it holds an offset, a
// motion filter (the transform of the joint is tracked through it) and a list of mappings; a mapping reads one feature
// off the tracked motion (displacement, speed or acceleration along or around an axis), looks it up on a curve and
// combines the result into one expression by add, min, max or override. Unit 0x10911880 - 0x10914850 (no assert path;
// the directory and file name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_TRACKEDMOTIONTOEXPRESSIONMAP_H
#define ENGINE_TRACKEDMOTIONTOEXPRESSIONMAP_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/vectormetatype.h"
#include "code/core/name.h"
#include "code/engine/motionfeatureextractor.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/pure3d/expressiongroup.h"
#include "code/pure3d/pose.h"

namespace engine
{
	class TrackedMotionToExpressionMap : public content::MetaLoadObject
	{
	public:
		// One point of a mapping curve
		struct PropertyMappingKeyValuePair
		{
			// 0x109119B0
			PropertyMappingKeyValuePair()
			{
				key = 0.0f;
				value = 0.0f;
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float key;  // +0
			float value;  // +4
		};

		typedef container::ArrayDynamic<PropertyMappingKeyValuePair, container::AllocatorNew> CurveArray;

		// One feature of the tracked motion that drives one expression
		struct PropertyMapping
		{
			// How the mapped value combines with the expression's value so far
			enum BlendType
			{
				BLEND_ADD = 0,
				BLEND_MIN = 1,
				BLEND_MAX = 2,
				BLEND_OVERRIDE = 3
			};

			// 0x109135F0
			PropertyMapping();
			// 0x10913470 / 0x109131A0 (the copies share the extractor)
			PropertyMapping(const PropertyMapping& other) : featureExtractor(other.featureExtractor),
				expressionName(other.expressionName), expressionIndex(other.expressionIndex), weight(other.weight),
				blendType(other.blendType), mappingCurve(other.mappingCurve), debugDisable(other.debugDisable)
			{
			}
			PropertyMapping& operator=(const PropertyMapping& other)
			{
				featureExtractor = other.featureExtractor;
				expressionName = other.expressionName;
				expressionIndex = other.expressionIndex;
				weight = other.weight;
				blendType = other.blendType;
				mappingCurve = other.mappingCurve;
				debugDisable = other.debugDisable;
				return *this;
			}
			// 0x10913630 (the extractor belongs to the mapping)
			~PropertyMapping();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x109119C0: finds the expression of expressionName
			void ResolveExpression(const pure3d::ExpressionGroup* group);
			// 0x10911E30: whether the keys of the curve increase
			bool IsCurveSorted() const;
			// 0x10911E60: the curve's value at x (the ends are held)
			float EvaluateCurve(float x) const;

			MotionFeatureExtractor* featureExtractor;  // +0
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> expressionName;  // +8
			int expressionIndex;  // +0x10
			float weight;  // +0x14
			BlendType blendType;  // +0x18
			CurveArray mappingCurve;  // +0x1C
			bool debugDisable;  // +0x2C
		};

		typedef container::ArrayDynamic<PropertyMapping, container::AllocatorNew> PropertyArray;

		// The tracking of one joint
		struct JointData
		{
			// What the joint's offset transform is attached to (0x4C bytes: a transform, two handles and a flag; the
			// constructor, 0x107F6990, is in another unit)
			struct Offset
			{
				Offset();
				Offset(const Offset& other) : transform(other.transform), handle(other.handle), flag(other.flag),
					unknown48(other.unknown48)
				{
				}
				Offset& operator=(const Offset& other)
				{
					transform = other.transform;
					handle = other.handle;
					flag = other.flag;
					unknown48 = other.unknown48;
					return *this;
				}

				math::Matrix transform;  // +0
				int handle;  // +0x40
				bool flag;  // +0x44
				int unknown48;  // +0x48
			};

			// 0x10914180
			JointData();
			// 0x10914110 / 0x10913EE0 (the copies share the filter)
			JointData(const JointData& other) : jointName(other.jointName), offset(other.offset),
				offsetTranslation(other.offsetTranslation), motionFilter(other.motionFilter),
				trackedProperties(other.trackedProperties), debugDisable(other.debugDisable)
			{
			}
			JointData& operator=(const JointData& other)
			{
				jointName = other.jointName;
				offset = other.offset;
				offsetTranslation = other.offsetTranslation;
				motionFilter = other.motionFilter;
				trackedProperties = other.trackedProperties;
				debugDisable = other.debugDisable;
				return *this;
			}
			// 0x109141B0 (deletes the filter)
			~JointData();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x109119E0 / 0x10911A10: the offset's translation (kept apart for the reflection)
			const math::Vector* GetOffset() const;
			void SetOffset(const math::Vector* value);
			// 0x10911EE0: finds the joint of jointName in the skeleton and resolves the mappings' expressions
			void Resolve(const pure3d::Skeleton* skeleton, const pure3d::ExpressionGroup* group);

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> jointName;  // +0
			Offset offset;  // +8
			mutable math::Vector offsetTranslation;  // +0x54
			MotionTrackingFilter* motionFilter;  // +0x60
			PropertyArray trackedProperties;  // +0x64
			bool debugDisable;  // +0x74
		};

		typedef container::ArrayDynamic<JointData, container::AllocatorNew> JointArray;

		// 0x109146F0
		TrackedMotionToExpressionMap();
		// 0x10914720 (deleting destructor 0x10914830)
		virtual ~TrackedMotionToExpressionMap();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10911F50: resolves every joint against the skeleton and the expression group
		void ResolveAll();
		// vftable slot 5 (0x10912AD0)
		virtual bool Slot5();

		pure3d::Skeleton* skeleton;  // +8
		pure3d::ExpressionGroup* expressionGroup;  // +0xC
		JointArray jointData;  // +0x10
	};
}

namespace container
{
	// The mappings and the joints are too large for the compiler to inline the assignment of their elements
	template<> struct ArrayEraseInline<engine::TrackedMotionToExpressionMap::PropertyMapping>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::TrackedMotionToExpressionMap::JointData>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
