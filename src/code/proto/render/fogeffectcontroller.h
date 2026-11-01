// proto::FogEffectController (RTTI proto::FogEffectController, base engine::EffectController): the controller of the fog
// effects of a fog track: it sizes every effect it holds (the generator width and height), puts it at the fog's position
// and gives it its fade. Unit 0x102E9DA0 - 0x102E9F70 (no assert path; the file name is a guess). The member names are
// guesses.
#ifndef PROTO_RENDER_FOGEFFECTCONTROLLER_H
#define PROTO_RENDER_FOGEFFECTCONTROLLER_H

#include "code/engine/render/effectcontroller.h"
#include "code/math/vector.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// The values the controller applies to every effect (0x18 bytes)
	struct FogParams
	{
		float width;
		float height;
		math::Vector position;
		float fade;
	};

	class FogEffectController : public engine::EffectController
	{
	public:
		// 0x102E9DA0
		FogEffectController(const int* newOwner, const core::Name<core::CaseSensitiveKey>& newName);
		// 0x102E9DF0 (the deleting destructor is 0x102E9E50)
		virtual ~FogEffectController();

		// vftable slot 3 (0x102E9E80): keeps the effect and gives it the fog's values
		virtual bool AddEffect(const int* effect);
		// vftable slot 4 (0x102E9F70): gives every effect the fog's values again
		virtual void Slot4();

		// vftable slot 5 (0x102E9E40): a jump to the base class's
		virtual void StopAll();

		// 0x102E9F30
		void SetParams(const FogParams* params);

		unsigned char unknown24[4];
		float width;  // +0x28
		float height;  // +0x2C
		math::Vector position;  // +0x30
		float fade;  // +0x3C
	};
}

#endif
