// The frame buffer passes of pure3d (RTTI names pure3d::FrameBufferPass, ProtoMotherPass, ProtoThermalPass, ToneMapPass,
// ProtoToneMapPass, CopyPass and CapturePass): passes that draw the finished picture again with a pixel shader (post
// processing). Each one that has parameters keeps a ParameterHandler of its own class. Only what the reconstructed
// functions use is declared; names are guesses.
#ifndef PURE3D_FRAMEBUFFERPASS_H
#define PURE3D_FRAMEBUFFERPASS_H

#include "code/pure3d/parameterhandler.h"
#include "code/pure3d/pass.h"

namespace pure3d
{
	class FrameBufferPass : public Pass
	{
	public:
		unsigned char unknownB0[0x38];
	};

	class ProtoMotherPass : public FrameBufferPass
	{
	public:
		// 0x1075DAF0 (another unit): the registered "enable" parameter's setter
		bool SetParameterEnable(bool value);

		unsigned char unknownE8[0x1C];
		ParameterHandler<ProtoMotherPass> parameters; // +0x104
	};

	class ProtoThermalPass : public FrameBufferPass
	{
	public:
		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		unsigned char unknownE8[0x1C];
		ParameterHandler<ProtoThermalPass> parameters; // +0x104
	};

	class ToneMapPass : public FrameBufferPass
	{
	public:
		// 0x1075DAF0 / 0x107AF3A0 (another unit)
		bool SetParameterEnable(bool value);

		unsigned char unknownE8[0x3C];
		ParameterHandler<ToneMapPass> parameters; // +0x130
	};
}

#endif
