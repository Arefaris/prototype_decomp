// pure3d::RenderScheme (RTTI name, vftable 0x10E5E1EC, seven slots): a named way of drawing the scene, which runs one
// pass tree. Member and slot names are guesses.
#ifndef PURE3D_RENDERSCHEME_H
#define PURE3D_RENDERSCHEME_H

#include "code/pure3d/pass.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/framebufferpass.h"

namespace pure3d
{
	// What a pass is made from (RTTI name pure3d::PassDesc, a struct, 0x18 bytes, one slot: the deleting destructor; the classes
	// derived from it add the settings of their pass). The constructor takes the name of the pass and a flag.
	struct PassDesc
	{
	public:
		// 0x10754A40
		PassDesc(const void* name, int flag);
		virtual ~PassDesc()
		{
		}

		unsigned char unknown4[0x10];
		// The Z pass's description keeps a number here
		unsigned int unknown14;
	};

	// RTTI name pure3d::Debug2DPassDesc (vftable 0x10E638B8)
	struct Debug2DPassDesc : public PassDesc
	{
	public:
		// 0x107A0740
		explicit Debug2DPassDesc(const void* name);

		bool unknown18;
		bool unknown19;
	};

	// 0x111BBA3C: the colour the debug descriptions start with (name guessed)
	extern const PassColour gDebugColour;

	// RTTI name pure3d::Debug3DPassDesc (vftable 0x10E638C0)
	struct Debug3DPassDesc : public PassDesc
	{
		// 0x107A0780
		explicit Debug3DPassDesc(const void* name);

		unsigned int colour18;
		unsigned int colour1C;
		float size;
		unsigned int colour24;
		PassColour colour28;
		int count;
		bool flags[6];
	};

	// RTTI name pure3d::DebugPassDesc (vftable 0x10E638FC)
	struct DebugPassDesc : public PassDesc
	{
		// 0x107A0DF0
		DebugPassDesc(const void* name, bool newFlag);

		unsigned int colour18;
		unsigned int colour1C;
		float size;
		unsigned int colour24;
		PassColour colour28;
		bool unknown2C;
		bool flag;
	};

	class RenderScheme
	{
	public:
		// Slot 0 (0x1074DCF0 is the scalar deleting destructor, its body 0x1074DC80)
		virtual ~RenderScheme();
		// Slots 1 / 2 (0x1074D860 / 0x1074D870): start / stop the pass tree
		virtual void Begin();
		virtual void End();
		// Slot 3 (0x1074D960): gives a copy of the scheme's default name
		virtual core::Name<core::CaseSensitiveKey>* Unknown3(core::Name<core::CaseSensitiveKey>* out);
		// Slots 4 / 5 (0x1074DC60 / 0x1074DC70): do nothing
		virtual void Unknown4(int a);
		virtual void Unknown5(int a, int b, int c, int d);
		// Slot 6 (0x1074D920)
		virtual void Unknown6();

		unsigned char unknown4[0x30];
		Pass* pass;
	};

	// The schemes (RTTI names; the vftables are those of the base class with the destructor and a few slots replaced).
	// Each destructor sets its vftable and runs the base destructor 0x1074DC80
	class SelectionRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A05F0, the deleting destructor 0x107A0610
		virtual ~SelectionRenderScheme();
		// Slot 6 (0x107A0600): hands on to 0x107BFEC0 with the scheme's pass
		virtual void Unknown6();
	};

	// Begin / End also switch the device's slot 8 on and off
	class ShadowDebugRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A06F0, the deleting destructor 0x107A0820
		virtual ~ShadowDebugRenderScheme();
		// Slots 1 / 2 (0x107A0700 / 0x107A0720)
		virtual void Begin();
		virtual void End();
	};

	class PrimColourRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A0DE0, the deleting destructor 0x107A0E80
		virtual ~PrimColourRenderScheme();
	};

	class OrthoNormalRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A1170, the deleting destructor 0x107A1180
		virtual ~OrthoNormalRenderScheme();
	};

	class StandardRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A1350, the deleting destructor 0x107A13A0
		virtual ~StandardRenderScheme();
		// Slots 1 / 2 (0x107A1360 / 0x107A1380)
		virtual void Begin();
		virtual void End();
	};

	class BasicRenderScheme : public RenderScheme
	{
	public:
		// Slot 0: the body is 0x107A1900, the deleting destructor 0x107A1910
		virtual ~BasicRenderScheme();
	};
}

#endif
