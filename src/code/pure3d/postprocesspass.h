// The post processing passes that run on the finished picture and own the passes of their parts (RTTI names
// pure3d::ProtoFBPass, ProtoBloomPass, ProtoBloomColourAdjustPass, ProtoBloomCompositePass, ProtoColourMatrixPass,
// ProtoFogPass, ProtoRadialBlurPass and DepthOfFieldPass; BlurPass and ProtoToneMapPass are declared only as far as
// the passes that make them need). Only what the reconstructed functions use is declared; names are guesses.
#ifndef PURE3D_POSTPROCESSPASS_H
#define PURE3D_POSTPROCESSPASS_H

#include "code/math/colour128.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"
#include "code/core/refptr.h"
#include "code/pure3d/framebufferpass.h"
#include "code/pure3d/passnames.h"
#include "code/pure3d/renderscheme.h"

namespace pure3d
{
	// The names of the shaders of the bloom passes (0x111B9350 / 0x111B9354; names guessed)
	extern const char* gShaderBloom;
	extern const char* gShaderBloomAdd;

	// 0x111B935C / 0x111BBED0: the weights of the colour channels in the brightness (0.2127, 0.7152, 0.0722), as a vector and
	// as the vector with w 1 the colour matrix functions take
	extern const math::Vector gLuminanceWeights;
	extern const math::Vector4 gLuminanceWeights4;

	// The tone map pass the frame buffer pass makes (vftable 0x10E5EBD8; the constructor is 0x1075F4E0, the destructor
	// 0x1075F500)
	class ProtoToneMapPass : public ToneMapPass
	{
	public:
		explicit ProtoToneMapPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1075F500, the deleting destructor 0x1075FC60)
		virtual ~ProtoToneMapPass();
		// Slot 4 (0x1075FC80) and 5 (0x1075F510)
		virtual void Render(PassContext* context);
		virtual void Begin();

		int unknown174; // the engine allocates 0x178 bytes
	};

	// The pass that blurs the picture (vftable 0x10E5EB68; 0x540 bytes, the constructor is 0x1075F090)
	class BlurPass : public FrameBufferPass
	{
	public:
		explicit BlurPass(const PassDesc* desc);
		virtual ~BlurPass();
		virtual void Render(PassContext* context);

		// 0x1075DB10 / 0x1075D6E0 (another unit): the two settings of the blur the bloom makes from its sizes
		void SetBlurSize(float value);
		void SetBlurRatio(float value);

		char unknownE8[0x540 - 0xE8];
	};

	class ProtoBloomPass;

	// Four floats copied as a block (the tint of the colour adjust pass)
	struct PassColour4
	{
		float r;
		float g;
		float b;
		float a;
	};

	// Applies the bloom colour adjustment to the picture (vftable 0x10E5ED5C): a colour matrix made from the settings
	// (brightness, contrast, saturation, hue, a tint) and the threshold of the bright parts
	class ProtoBloomColourAdjustPass : public FrameBufferPass
	{
	public:
		// 0x10761EA0
		explicit ProtoBloomColourAdjustPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10761220, the deleting destructor 0x10761B90)
		virtual ~ProtoBloomColourAdjustPass();
		// Slot 4 (0x10762000), 5 (0x107612C0, a jump to slot 7) and 7 (0x10761230)
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual bool IsVisible();

		// 0x107612D0 / 0x107612F0, 0x10761300 / 0x10761390, 0x107613A0 / 0x107613C0, 0x107613D0, 0x10761400,
		// 0x10761480 / 0x107614B0 and the matching getters: the settings; each one makes the matrix stale
		void SetBrightness(float value);
		float GetBrightness();
		void SetContrast(float value);
		float GetContrast();
		void SetMidpoint(float value);
		float GetMidpoint();
		void SetSaturation(float value);
		float GetSaturation();
		void SetHue(float value);
		float GetHue();
		void SetCutoff(float value);
		float GetCutoff();
		void SetPower(float value);
		float GetPower();
		// 0x10761430 / 0x10761470: the tint, 0x107614E0 / 0x10761510: the luminance weights (kept normalised)
		void SetTint(const math::Colour128* value);
		const math::Colour128& GetTint();
		void SetWeights(const math::Vector* value);
		const math::Vector& GetWeights();
		// 0x10761BB0: puts the matrix and the other inputs on the shader (when stale)
		void UpdateShader();

		float brightness;        // +0xE8
		float contrastScale;     // +0xEC
		float contrast;          // +0xF0
		float midpoint;          // +0xF4
		float saturation;        // +0xF8
		float hue;               // +0xFC
		float cutoff;            // +0x100
		float power;             // +0x104
		PassColour4 tint;        // +0x108
		math::Vector weights;    // +0x118
		math::Matrix matrix;     // +0x124
		bool matrixValid;        // +0x164
	};

	// Adds the bloom to the picture (vftable 0x10E5EF18)
	class ProtoBloomCompositePass : public FrameBufferPass
	{
	public:
		// 0x10761520
		explicit ProtoBloomCompositePass(const PassDesc* desc);
		// Slot 0 (the body is 0x10761560, the deleting destructor 0x10761DF0)
		virtual ~ProtoBloomCompositePass();
		// Slot 4 (0x10762410), 5 (0x10761660, a jump to slot 7) and 7 (0x10761570)
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual bool IsVisible();

		// 0x10761600 / 0x10761620, 0x10761630 / 0x10761650
		void SetBloomStrength(float value);
		float GetBloomStrength();
		void SetBackBufferStrength(float value);
		float GetBackBufferStrength();
		// 0x107621E0: puts the strengths and the textures on the shader
		void UpdateShader();

		float bloomStrength;      // +0xE8
		float backBufferStrength; // +0xEC
		bool shaderValid;         // +0xF0
	};

	// The bloom (vftable 0x10E5EF98): finds the bright parts with a colour adjust pass, blurs them and adds them with a
	// composite pass; the parameters it registers are those of its two passes
	class ProtoBloomPass : public FrameBufferPass
	{
	public:
		// 0x10762D90
		explicit ProtoBloomPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10762CE0, the deleting destructor 0x10763390)
		virtual ~ProtoBloomPass();
		// Slot 2 (0x10761200), 4 (0x107619C0), 5 (0x10761100), 6 (0x10761B50) and 7 (0x10760FF0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);
		// 0x10760FE0: the pass that blurs the bright parts (made by the frame buffer pass)
		void SetBlurPass(BlurPass* pass);
		// 0x10761070 / 0x10761090, 0x107610A0 / 0x107610C0: the two sizes the blur is made at
		void SetSize(float value);
		float GetSize() const;
		void SetBlur(float value);
		float GetBlur() const;
		// 0x107610D0: the two textures the bloom draws into
		void SetTextures(Texture* first, Texture* second);
		// 0x10761150: the sizes of the blur from the two settings
		void UpdateBlur();
		// 0x10761210
		ProtoBloomCompositePass* GetComposite();

		// 0x10761990 / 0x107619B0, 0x10761960 / 0x10761980, 0x107617D0 / 0x107617F0, 0x10761800 / 0x10761820,
		// 0x10761890 / 0x107618B0, 0x107618E0 / 0x10761900, 0x10761910 / 0x10761930, 0x10761830 / 0x10761850,
		// 0x10761860 / 0x10761880, 0x107618C0 / 0x107618D0, 0x10761940 / 0x10761950: the settings of its two passes
		void SetBackBufferStrength(float value);
		float GetBackBufferStrength() const;
		void SetBloomStrength(float value);
		float GetBloomStrength() const;
		void SetBrightness(float value);
		float GetBrightness() const;
		void SetContrast(float value);
		float GetContrast() const;
		void SetHue(float value);
		float GetHue() const;
		void SetCutoff(float value);
		float GetCutoff() const;
		void SetPower(float value);
		float GetPower() const;
		void SetMidpoint(float value);
		float GetMidpoint() const;
		void SetSaturation(float value);
		float GetSaturation() const;
		void SetTint(const math::Colour128* value);
		const math::Colour128& GetTint();
		void SetWeights(const math::Vector* value);
		const math::Vector& GetWeights();

		Texture* textureE8;
		Texture* textureEC;
		ProtoBloomColourAdjustPass* colourAdjust; // +0xF0
		ProtoBloomCompositePass* composite;       // +0xF4
		BlurPass* blurPass;                        // +0xF8
		float size;                                // +0xFC
		float blur;                                // +0x100
		ParameterHandler<ProtoBloomPass> parameters; // +0x104
		bool blurValid;                            // +0x148
		int unknown14C;                            // the engine allocates 0x150 bytes
	};

	// The names of the shaders of the colour matrix pass (0x111B9434; name guessed)
	extern const char* gShaderColourMatrix;

	// 0x10E5F244 / 0x10E5F248 / 0x10E5F240: the start values of the colour matrix pass's grain speed, overlay opacity and
	// overlay saturation (names guessed)
	extern const float gColourMatrixGrainSpeed;
	extern const float gColourMatrixOverlayOpacity;
	extern const float gColourMatrixOverlaySaturation;

	// Grades the colours of the picture with a colour matrix (vftable 0x10E5F21C): brightness, contrast, saturation, hue
	// and a tint, plus a CMY shift, an overlay, the grain and the distortion textures
	class ProtoColourMatrixPass : public FrameBufferPass
	{
	public:
		// 0x10764910
		explicit ProtoColourMatrixPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10764880, the deleting destructor 0x10764D00)
		virtual ~ProtoColourMatrixPass();
		// Slot 2 (0x10763710), 4 (0x10764270), 5 (0x107636F0), 6 (0x10763F30) and 7 (0x10763460)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);
		// 0x107634E0 - 0x10763520, 0x10763530: the settings
		float GetBrightness();
		float GetContrast();
		float GetMidpoint();
		float GetSaturation();
		float GetHue();
		void GetTint(unsigned int* value);
		// 0x10763540: takes the settings (the contrast scale follows the contrast)
		void SetValues(float newBrightness, float newContrast, float newMidpoint, float newSaturation, float newHue,
			unsigned int newTint);
		// 0x10763600: the CMY shift in hundredths; 0x10763670: the scale and bias of the shift
		void SetCMY(const math::Vector* value);
		void SetCMYScaleBias(const math::Vector2* value);
		// 0x107636B0: the opacity and the saturation of the overlay
		void SetOverlayValues(float opacity, float newSaturation);
		// 0x107636D0, 0x107638A0, 0x107638E0: the textures
		void SetDistortion(Texture* texture);
		void SetOverlay(Texture* texture);
		void SetGrain(Texture* texture);
		// 0x10763920: puts the matrix and the other inputs on the shader
		void UpdateShader();
		// 0x107640F0: draws the parts that distort the picture
		void DrawDistortion(PassContext* context);

		core::RefPtr<Texture> overlay;               // +0xE8
		core::RefPtr<Texture> grain;                 // +0xEC
		Texture* distortion;                         // +0xF0
		float brightness;                            // +0xF4
		float contrastScale;                         // +0xF8
		float contrast;                              // +0xFC
		float midpoint;                              // +0x100
		float saturation;                            // +0x104
		float hue;                                   // +0x108
		math::pddiColour tint;                       // +0x10C
		math::Vector cmy;                            // +0x110
		math::Vector2 cmyScaleBias;                  // +0x11C
		float grainSpeed;                            // +0x124
		float grainIntensity;                        // +0x128
		float overlayOpacity;                        // +0x12C
		float overlaySaturation;                     // +0x130
		bool distortionEnabled;                      // +0x134
		ParameterHandler<ProtoColourMatrixPass> parameters; // +0x138
		int unknown17C;                              // the engine allocates 0x180 bytes
	};

	// Draws fog over the picture (vftable 0x10E5F714)
	class ProtoFogPass : public FrameBufferPass
	{
	public:
		// 0x1076A550
		explicit ProtoFogPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076A4B0, the deleting destructor 0x1076A6A0)
		virtual ~ProtoFogPass();
		// Slot 2 (0x10769900), 4 (0x1076A880) and 5 (0x107698F0, the base class's)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual void Begin();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		math::Vector2 tiling;   // +0xE8
		float variation;        // +0xF0
		float speed;            // +0xF4
		RefCounted* object;     // +0xF8
		ParameterHandler<ProtoFogPass> parameters; // +0xFC
	};

	// The names of the shaders of the radial blur and depth of field passes (0x111B9C7C / 0x111B9D08 / 0x111B9D04; names guessed)
	extern const char* gShaderRadialBlur;

	// Blurs the picture away from a centre (vftable 0x10E5FC00)
	class ProtoRadialBlurPass : public FrameBufferPass
	{
	public:
		// 0x107732E0
		explicit ProtoRadialBlurPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10773280, the deleting destructor 0x10773510)
		virtual ~ProtoRadialBlurPass();
		// Slot 2 (0x10772500), 4 (0x10772E80) and 7 (0x10772150)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual bool IsVisible();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);
		// 0x107721C0: the settings
		void SetValues(float x, float y, float z, float newRadius, float newIntensity, float newSize, float newFalloff);

		float radius;           // +0xE8
		float unknownEC;
		float unknownF0;
		float unknownF4;
		float unknownF8;
		math::Vector source;    // +0xFC
		float intensity;        // +0x108
		float size;             // +0x10C
		float falloff;          // +0x110
		float sampleScale;      // +0x114
		unsigned char unknown118[0x500 - 0x118];
		ParameterHandler<ProtoRadialBlurPass> parameters; // +0x500
	};

	// Blurs the parts of the picture that are out of focus (vftable 0x10E5FCD0)
	class DepthOfFieldPass : public FrameBufferPass
	{
	public:
		// 0x107743D0
		explicit DepthOfFieldPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10774310, the deleting destructor 0x10774550)
		virtual ~DepthOfFieldPass();
		// Slot 2 (0x10773540), 4 (0x10773870), 5 (0x10773810) and 7 (0x10773620)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual bool IsVisible();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		Shader* shaderE8;
		Shader* shaderEC;
		Shader* shaderF0;
		Shader* shaderF4;
		Shader* shaderF8;
		Texture* textureFC;
		Texture* texture100;
		float nearDepth;        // +0x104
		float farDepth;         // +0x108
		float range;            // +0x10C
		float aperture;         // +0x110
		ParameterHandler<DepthOfFieldPass> parameters; // +0x114
	};

	// Draws the picture through all the post processing passes (vftable 0x10E5ED00): makes the tone map, bloom, colour
	// matrix, thermal, mother, copy and blur passes itself
	class ProtoFBPass : public FrameBufferPass
	{
	public:
		// 0x10760BE0
		explicit ProtoFBPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10760AB0, the deleting destructor 0x10760FC0)
		virtual ~ProtoFBPass();
		// Slot 2 (0x1075F4D0), 4 (0x1075F670), 5 (0x1075F200), 6 (0x1075F620) and 7 (0x1075F2A0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);
		// 0x1075F460, 0x1075F470, 0x1075F450, 0x1075F480, 0x1075F490, 0x1075F4C0: the passes it made
		ProtoToneMapPass* GetToneMapPass();
		ProtoBloomPass* GetBloomPass();
		ProtoColourMatrixPass* GetColourMatrixPass();
		ProtoThermalPass* GetThermalPass();
		ProtoMotherPass* GetMotherPass();
		BlurPass* GetBlurPass();
		// 0x1075F4A0 / 0x1075F4B0: the pass kept at +0xFC
		void SetPassFC(Pass* pass);
		Pass* GetPassFC();

		ProtoToneMapPass* toneMapPass;               // +0xE8
		ProtoBloomPass* bloomPass;                   // +0xEC
		ProtoColourMatrixPass* colourMatrixPass;     // +0xF0
		ProtoThermalPass* thermalPass;               // +0xF4
		ProtoMotherPass* motherPass;                 // +0xF8
		Pass* unknownFC;
		CopyPass* copyPass;                          // +0x100
		BlurPass* blurPass;                          // +0x104
		Texture* texture108;
		Shader* shader10C;
		Shader* shader110;
		int visionMode;                              // +0x114
		float visionStrength;                        // +0x118
		int unknown11C;
		float mixAmount;                             // +0x120
		math::Vector colourMix;                      // +0x124
		math::Vector alexColour;                     // +0x130
		Texture* texture13C;
		Texture* texture140;
		Texture* texture144;
		unsigned int unknown148;
		ParameterHandler<ProtoFBPass> parameters;    // +0x14C
	};
}

#endif
