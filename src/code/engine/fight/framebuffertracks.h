// The fight tracks that drive the frame buffer effects: tone mapping, fades, depth of field, colour matrices, scatter, letterbox and bloom (unit 0x10815900 - 0x10817A00).
#ifndef ENGINE_FIGHT_FRAMEBUFFERTRACKS_H
#define ENGINE_FIGHT_FRAMEBUFFERTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ToneMapTrack (16 vftable slots, 0x20 bytes)
		class ToneMapTrack : public fight::Track
		{
		public:
			// 0x10815900
			ToneMapTrack();
			virtual ~ToneMapTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC130)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetEnable(bool value);
			bool SetBlendFromPreviousState(bool value);
			bool SetAdaptRate(float value);
			bool SetAverageLuminanceTarget(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float adaptRate;  // +0x10
			float averageLuminanceTarget;  // +0x14
			float timeBegin;  // +0x18
			bool blendFromPreviousState;  // +0x1C
			bool enable;  // +0x1D
		};

		extern fight::Property** gToneMapTrackProperties;
		// 0x108165A0
		// 0x108173F0
		fight::TrackFactory* CreateToneMapTrackFactory(const char* name);
		void RegisterToneMapTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::FadeTrack (16 vftable slots, 0x1C bytes)
		class FadeTrack : public fight::Track
		{
		public:
			// 0x10815980
			FadeTrack();
			virtual ~FadeTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC1F0)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetType(int value);
			// 0x108BAE20 / 0x108BAE30 (another unit): the entries of the "type" enum
			const fight::EnumEntry* GetTypeEntry(int index);
			int GetTypeCount();

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float timeBegin;  // +0x10
			float timeEnd;  // +0x14
			int type;  // +0x18
		};

		extern fight::Property** gFadeTrackProperties;
		// 0x108165C0
		// 0x10817420
		fight::TrackFactory* CreateFadeTrackFactory(const char* name);
		void RegisterFadeTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::DepthOfFieldTrack (16 vftable slots, 0x28 bytes)
		class DepthOfFieldTrack : public fight::Track
		{
		public:
			// 0x10815A10
			DepthOfFieldTrack();
			virtual ~DepthOfFieldTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC190)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetEnable(bool value);
			bool SetBlendFromPreviousState(bool value);
			bool SetNearDepth(float value);
			bool SetFarDepth(float value);
			bool SetRange(float value);
			bool SetAperture(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float aperture;  // +0x10
			float farDepth;  // +0x14
			float nearDepth;  // +0x18
			float range;  // +0x1C
			float timeBegin;  // +0x20
			bool blendFromPreviousState;  // +0x24
			bool enable;  // +0x25
		};

		extern fight::Property** gDepthOfFieldTrackProperties;
		// 0x108165E0
		// 0x10817450
		fight::TrackFactory* CreateDepthOfFieldTrackFactory(const char* name);
		void RegisterDepthOfFieldTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ColourMatrixTrack (16 vftable slots, 0x3C bytes)
		class ColourMatrixTrack : public fight::Track
		{
		public:
			// 0x10815AB0
			ColourMatrixTrack();
			virtual ~ColourMatrixTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC1C0)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetEnable(bool value);
			bool SetBlendFromPreviousState(bool value);
			bool SetBrightness(float value);
			bool SetContrast(float value);
			bool SetMidpoint(float value);
			bool SetSaturate(float value);
			bool SetHue(float value);
			bool SetTint(const math::Colour128& value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			math::Colour128 tint;  // +0x10
			float brightness;  // +0x20
			float contrast;  // +0x24
			float hue;  // +0x28
			float midpoint;  // +0x2C
			float saturate;  // +0x30
			float timeBegin;  // +0x34
			bool blendFromPreviousState;  // +0x38
			bool enable;  // +0x39
		};

		extern fight::Property** gColourMatrixTrackProperties;
		// 0x10816600
		// 0x10817480
		fight::TrackFactory* CreateColourMatrixTrackFactory(const char* name);
		void RegisterColourMatrixTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ScatterTrack (16 vftable slots, 0x50 bytes)
		class ScatterTrack : public fight::Track
		{
		public:
			// 0x10815B60
			ScatterTrack();
			virtual ~ScatterTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC160)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetEnable(bool value);
			bool SetBlendFromPreviousState(bool value);
			bool SetScatterColour(const math::Colour128& value);
			bool SetSaturationMin(float value);
			bool SetSaturationMax(float value);
			bool SetContrastMin(float value);
			bool SetContrastMax(float value);
			bool SetBrightnessMin(float value);
			bool SetBrightnessMax(float value);
			bool SetTintMin(float value);
			bool SetTintMax(float value);
			bool SetDistanceBrightening(float value);
			bool SetContrastDropoff(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			math::Colour128 scatterColour;  // +0x10
			float brightnessMax;  // +0x20
			float brightnessMin;  // +0x24
			float contrastDropoff;  // +0x28
			float contrastMax;  // +0x2C
			float contrastMin;  // +0x30
			float distanceBrightening;  // +0x34
			float saturationMax;  // +0x38
			float saturationMin;  // +0x3C
			float timeBegin;  // +0x40
			float tintMax;  // +0x44
			float tintMin;  // +0x48
			bool blendFromPreviousState;  // +0x4C
			bool enable;  // +0x4D
		};

		extern fight::Property** gScatterTrackProperties;
		// 0x10816620
		// 0x108174B0
		fight::TrackFactory* CreateScatterTrackFactory(const char* name);
		void RegisterScatterTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::LetterboxTrack (16 vftable slots, 0x1C bytes)
		class LetterboxTrack : public fight::Track
		{
		public:
			// 0x10815C30
			LetterboxTrack();
			virtual ~LetterboxTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC220)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetAspectRatio(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float aspectRatio;  // +0x10
			float timeBegin;  // +0x14
			float timeEnd;  // +0x18
		};

		extern fight::Property** gLetterboxTrackProperties;
		// 0x10816640
		// 0x108174E0
		fight::TrackFactory* CreateLetterboxTrackFactory(const char* name);
		void RegisterLetterboxTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::BloomTrack (16 vftable slots, 0x68 bytes)
		class BloomTrack : public fight::Track
		{
		public:
			// 0x10815CC0
			BloomTrack();
			virtual ~BloomTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108BC100)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetEnable(bool value);
			bool SetDisableOnFinish(bool value);
			bool SetBlendFromPreviousState(bool value);
			bool SetBrightness(float value);
			bool SetContrast(float value);
			bool SetMidpoint(float value);
			bool SetSaturate(float value);
			bool SetHue(float value);
			bool SetTint(const math::Colour128& value);
			bool SetBloom(float value);
			bool SetBackbuffer(float value);
			bool SetRadiusX(float value);
			bool SetRadiusY(float value);
			bool SetColour(const math::Colour128& value);
			bool SetLuminanceCutoff(float value);
			bool SetFalloff(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			math::Colour128 colour;  // +0x10
			math::Colour128 tint;  // +0x20
			float backbuffer;  // +0x30
			float bloom;  // +0x34
			float brightness;  // +0x38
			float contrast;  // +0x3C
			float falloff;  // +0x40
			float hue;  // +0x44
			float luminanceCutoff;  // +0x48
			float midpoint;  // +0x4C
			float radiusX;  // +0x50
			float radiusY;  // +0x54
			float saturate;  // +0x58
			float timeBegin;  // +0x5C
			float timeEnd;  // +0x60
			bool blendFromPreviousState;  // +0x64
			bool disableOnFinish;  // +0x65
			bool enable;  // +0x66
		};

		extern fight::Property** gBloomTrackProperties;
		// 0x10816660
		// 0x10817510
		fight::TrackFactory* CreateBloomTrackFactory(const char* name);
		void RegisterBloomTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

}

#endif
