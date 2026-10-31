// Fight items of the ai group: ZiplineLandTrack, ZiplineTakeOffTrack (unit 0x10256A40 - 0x102573D0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_zipline.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gZiplineLandTrackProperties;  // 0x11255C60

			// FUNCTION: ENGINE 0x10256A40
			bool ZiplineLandTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256A60
			bool ZiplineLandTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256A80
			bool ZiplineLandTrack::SetSpeed(const math::Vector& newValue)
			{
				speed.x = newValue.x;
				speed.y = newValue.y;
				speed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B40
			fight::Property* ZiplineLandTrack::GetProperty(int index)
			{
				return gZiplineLandTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10256B60
			void ZiplineLandTrack::ClearProperties()
			{
				fight::FreePropertyList(&gZiplineLandTrackProperties);
			}

			// FUNCTION: ENGINE 0x10256B70
			ZiplineLandTrack::ZiplineLandTrack() : speed(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10256BC0
			float ZiplineLandTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10256BD0
			float ZiplineLandTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10256BE0
			ZiplineLandTrack::~ZiplineLandTrack()
			{
			}

			// FUNCTION: ENGINE 0x10256F90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ZiplineLandTrack::RegisterProperties()
			{
				if (gZiplineLandTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ZiplineLandTrack>("timeBegin", &ZiplineLandTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ZiplineLandTrack>("timeEnd", &ZiplineLandTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ZiplineLandTrack>("speed", &ZiplineLandTrack::SetSpeed);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gZiplineLandTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256F30
			fight::TrackFactory* CreateZiplineLandTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineLandTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10257230
			void RegisterZiplineLandTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineLandTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gZiplineTakeOffTrackProperties;  // 0x11255C64

			// FUNCTION: ENGINE 0x10256AA0
			bool ZiplineTakeOffTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256AC0
			bool ZiplineTakeOffTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256AE0
			bool ZiplineTakeOffTrack::SetZiplineSpeed(const math::Vector& newValue)
			{
				ziplineSpeed.x = newValue.x;
				ziplineSpeed.y = newValue.y;
				ziplineSpeed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B00
			bool ZiplineTakeOffTrack::SetZiplineTime(float newValue)
			{
				ziplineTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B20
			bool ZiplineTakeOffTrack::SetCharacterSpeed(const math::Vector& newValue)
			{
				characterSpeed.x = newValue.x;
				characterSpeed.y = newValue.y;
				characterSpeed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256BF0
			fight::Property* ZiplineTakeOffTrack::GetProperty(int index)
			{
				return gZiplineTakeOffTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10256C10
			void ZiplineTakeOffTrack::ClearProperties()
			{
				fight::FreePropertyList(&gZiplineTakeOffTrackProperties);
			}

			// FUNCTION: ENGINE 0x10256C20
			ZiplineTakeOffTrack::ZiplineTakeOffTrack() : characterSpeed(0.0f, 0.0f, 0.0f), ziplineSpeed(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f), ziplineTime(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10256C80
			float ZiplineTakeOffTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10256C90
			float ZiplineTakeOffTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10256CA0
			ZiplineTakeOffTrack::~ZiplineTakeOffTrack()
			{
			}

			// FUNCTION: ENGINE 0x102570A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ZiplineTakeOffTrack::RegisterProperties()
			{
				if (gZiplineTakeOffTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("timeBegin", &ZiplineTakeOffTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("timeEnd", &ZiplineTakeOffTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ZiplineTakeOffTrack>("ziplineSpeed", &ZiplineTakeOffTrack::SetZiplineSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("ziplineTime", &ZiplineTakeOffTrack::SetZiplineTime);
					properties[3] = property;
					property = new fight::PropertyVector<ZiplineTakeOffTrack>("characterSpeed", &ZiplineTakeOffTrack::SetCharacterSpeed);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gZiplineTakeOffTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256F60
			fight::TrackFactory* CreateZiplineTakeOffTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10257260
			void RegisterZiplineTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x1021A910
			ZiplineLandAction::ZiplineLandAction(ZiplineLandTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
				position.x = 0.0f;
				position.y = 0.0f;
				position.z = 0.0f;
			}

			// FUNCTION: ENGINE 0x1021A5A0
			ZiplineLandAction::~ZiplineLandAction()
			{
			}

			// FUNCTION: ENGINE 0x1021A5D0
			// NONMATCHING: the translation copy goes through x87 for the first component, best 55%
#ifdef NONMATCHING
			bool ZiplineLandAction::Slot5(int arg, float value)
			{
				math::Matrix& matrix = target.Get()->transform->value;
				float x = matrix.m[3][0];
				float y = matrix.m[3][1];
				float z = matrix.m[3][2];
				position.x = x;
				position.y = y;
				position.z = z;
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x1021A400
			void ZiplineLandAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x1021A9C0
			bool ZiplineLandAction::Slot7(int arg, float value)
			{
				return link.Get() ? true : false;
			}

			// FUNCTION: ENGINE 0x1021AA20
			fight::Action* ZiplineLandTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ZiplineLandAction(this, handle);
			}

			// FUNCTION: ENGINE 0x1021A710
			// EQUIVALENT: scheduling; the integer store of the state sits behind the vector's stores in the engine, ours hoists it; the same stores
			ZiplineTakeOffAction::ZiplineTakeOffAction(ZiplineTakeOffTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
				position.x = 0.0f;
				position.y = 0.0f;
				position.z = 0.0f;
				state = 0;
				elapsed = 0.0f;
			}

			// FUNCTION: ENGINE 0x1021A550
			ZiplineTakeOffAction::~ZiplineTakeOffAction()
			{
			}

			// FUNCTION: ENGINE 0x1021A7C0
			// NONMATCHING: the translation copy goes through x87 for the first component, best 56%
#ifdef NONMATCHING
			bool ZiplineTakeOffAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				math::Matrix& matrix = target.Get()->transform->value;
				float x = matrix.m[3][0];
				float y = matrix.m[3][1];
				float z = matrix.m[3][2];
				position.x = x;
				position.y = y;
				position.z = z;
				elapsed = 0.0f;
				state = 1;
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x1021A850
			void ZiplineTakeOffAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x1021A860
			// NONMATCHING: float order and block layout, best 25%
#ifdef NONMATCHING
			bool ZiplineTakeOffAction::Slot7(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				if (state == 1)
				{
					float stepX = link.Get()->ziplineSpeed.x * value;
					float stepY = link.Get()->ziplineSpeed.y * value;
					float stepZ = link.Get()->ziplineSpeed.z * value;
					position.x = position.x + stepX;
					position.y = position.y + stepY;
					position.z = position.z + stepZ;
					elapsed += value;
					if (elapsed > link.Get()->ziplineTime)
					{
						state = 2;
					}
				}
				else if (state != 2)
				{
					return false;
				}
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x1021A9D0
			fight::Action* ZiplineTakeOffTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ZiplineTakeOffAction(this, handle);
			}


			// ---- actions end
			template class fight::PropertyFloatConstRange<ZiplineLandTrack>;
			template class fight::PropertyVector<ZiplineLandTrack>;
			template class fight::TrackFactoryTemplate<ZiplineLandTrack>;
			template class fight::TrackFactoryCasterTemplate<ZiplineLandTrack>;
			template class fight::PropertyFloatConstRange<ZiplineTakeOffTrack>;
			template class fight::PropertyVector<ZiplineTakeOffTrack>;
			template class fight::TrackFactoryTemplate<ZiplineTakeOffTrack>;
			template class fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1021A410
// FUNCTION: ENGINE 0x1021A430
// FUNCTION: ENGINE 0x1021A450
// FUNCTION: ENGINE 0x1021A480
// FUNCTION: ENGINE 0x1021A4E0
// FUNCTION: ENGINE 0x1021A790
// FUNCTION: ENGINE 0x1021A990
// FUNCTION: ENGINE 0x10256CB0
// FUNCTION: ENGINE 0x10256CE0
// FUNCTION: ENGINE 0x10256D10
// FUNCTION: ENGINE 0x10256D20
// FUNCTION: ENGINE 0x10256D50
// FUNCTION: ENGINE 0x10256D60
// FUNCTION: ENGINE 0x10256D90
// FUNCTION: ENGINE 0x10256DC0
// FUNCTION: ENGINE 0x10256DF0
// FUNCTION: ENGINE 0x10256E00
// FUNCTION: ENGINE 0x10256E30
// FUNCTION: ENGINE 0x10256E50
// FUNCTION: ENGINE 0x10256E60
// FUNCTION: ENGINE 0x10256E90
// FUNCTION: ENGINE 0x10256EC0
// FUNCTION: ENGINE 0x10256ED0
// FUNCTION: ENGINE 0x10256F00
// FUNCTION: ENGINE 0x10256F20
// FUNCTION: ENGINE 0x10257290
// FUNCTION: ENGINE 0x102572C0
// FUNCTION: ENGINE 0x102572E0
// FUNCTION: ENGINE 0x10257310
// FUNCTION: ENGINE 0x10257330
// FUNCTION: ENGINE 0x10257380
