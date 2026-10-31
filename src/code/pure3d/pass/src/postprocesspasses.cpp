// The post processing passes (units around 0x1075D590 - 0x10775000 and the ones of their children; the file name is
// a guess): the frame buffer pass that makes the others, the bloom with its colour adjust and composite passes and the
// colour matrix pass. Names are guesses.
#include "code/core/refptr.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/math/pddicolour.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/pass/rendertargetmanager.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/postprocesspass.h"

#include <intrin.h>
#include <new>

namespace pure3d
{
	const char* gShaderBloom = "pp_bloom";
	const char* gShaderBloomAdd = "pp_bloom_add";
	const char* gShaderColourMatrix = "pp_colourmatrix";
	const char* gShaderRadialBlur = "pp_radialblur";
}

namespace pure3d
{
	// The tables of the contrast setting (0x10E5ED80: the scale for a contrast from 0 to 100)
	extern const float gContrastTable[101];

	// FUNCTION: ENGINE 0x10761070
	void ProtoBloomPass::SetSize(float value)
	{
		size = value;
		blurValid = false;
	}

	// FUNCTION: ENGINE 0x10761090
	float ProtoBloomPass::GetSize() const
	{
		return size;
	}

	// FUNCTION: ENGINE 0x107610A0
	void ProtoBloomPass::SetBlur(float value)
	{
		blur = value;
		blurValid = false;
	}

	// FUNCTION: ENGINE 0x107610C0
	float ProtoBloomPass::GetBlur() const
	{
		return blur;
	}

	// FUNCTION: ENGINE 0x10761210
	ProtoBloomCompositePass* ProtoBloomPass::GetComposite()
	{
		return composite;
	}

	// FUNCTION: ENGINE 0x107612D0
	void ProtoBloomColourAdjustPass::SetBrightness(float value)
	{
		brightness = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x107612F0
	float ProtoBloomColourAdjustPass::GetBrightness()
	{
		return brightness;
	}

	// FUNCTION: ENGINE 0x10761300
	// EQUIVALENT: the table value is copied through the x87 unit and the sum is formed in a second register; the same operations in the same order (92.2 %)
	void ProtoBloomColourAdjustPass::SetContrast(float value)
	{
		float low = -100.0f;
		float difference = value - low;
		contrast = value;
		if (!(difference >= 0.0f))
		{
			value = low;
		}
		float high = 100.0f;
		if (value - high >= 0.0f)
		{
			value = high;
		}
		if (value < 0.0f)
		{
			contrastScale = value * 0.01f + engine::driving::gOne;
			matrixValid = false;
			return;
		}
		contrastScale = gContrastTable[(int)(value + engine::driving::gHalf)];
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x10761390
	float ProtoBloomColourAdjustPass::GetContrast()
	{
		return contrast;
	}

	// FUNCTION: ENGINE 0x107613A0
	void ProtoBloomColourAdjustPass::SetMidpoint(float value)
	{
		midpoint = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x107613C0
	float ProtoBloomColourAdjustPass::GetMidpoint()
	{
		return midpoint;
	}

	// FUNCTION: ENGINE 0x107613D0
	void ProtoBloomColourAdjustPass::SetSaturation(float value)
	{
		saturation = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x107613F0
	float ProtoBloomColourAdjustPass::GetSaturation()
	{
		return saturation;
	}

	// FUNCTION: ENGINE 0x10761400
	void ProtoBloomColourAdjustPass::SetHue(float value)
	{
		hue = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x10761420
	float ProtoBloomColourAdjustPass::GetHue()
	{
		return hue;
	}

	// FUNCTION: ENGINE 0x10761430
	void ProtoBloomColourAdjustPass::SetTint(const math::Colour128* value)
	{
		tint = *(const PassColour4*)value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x10761470
	const math::Colour128& ProtoBloomColourAdjustPass::GetTint()
	{
		return *(const math::Colour128*)&tint;
	}

	// FUNCTION: ENGINE 0x10761480
	void ProtoBloomColourAdjustPass::SetCutoff(float value)
	{
		cutoff = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x107614A0
	float ProtoBloomColourAdjustPass::GetCutoff()
	{
		return cutoff;
	}

	// FUNCTION: ENGINE 0x107614B0
	void ProtoBloomColourAdjustPass::SetPower(float value)
	{
		power = value;
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x107614D0
	float ProtoBloomColourAdjustPass::GetPower()
	{
		return power;
	}

	// FUNCTION: ENGINE 0x107614E0
	void ProtoBloomColourAdjustPass::SetWeights(const math::Vector* value)
	{
		math::Vector& target = weights;
		target.x = value->x;
		target.y = value->y;
		target.z = value->z;
		target.Normalize();
		matrixValid = false;
	}

	// FUNCTION: ENGINE 0x10761510
	const math::Vector& ProtoBloomColourAdjustPass::GetWeights()
	{
		return weights;
	}

	// FUNCTION: ENGINE 0x10761520
	// EQUIVALENT: the engine loads the constant before it stores the vftable pointer (89.3 %)
	ProtoBloomCompositePass::ProtoBloomCompositePass(const PassDesc* desc) : FrameBufferPass(desc)
	{
		float one = engine::driving::gOne;
		bloomStrength = one;
		backBufferStrength = one;
		shaderValid = false;
	}

	// FUNCTION: ENGINE 0x10761560
	ProtoBloomCompositePass::~ProtoBloomCompositePass()
	{
	}

	// FUNCTION: ENGINE 0x10761570
	bool ProtoBloomCompositePass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		unknown24Bit1 = 1;
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderBloomAdd))
			{
				shader = new Shader(gShaderBloomAdd);
				shader->AddRef();
				return unknown24Bit1;
			}
			unknown24Bit1 = 0;
		}
		return unknown24Bit1;
	}

	// FUNCTION: ENGINE 0x10761600
	void ProtoBloomCompositePass::SetBloomStrength(float value)
	{
		bloomStrength = value;
		shaderValid = false;
	}

	// FUNCTION: ENGINE 0x10761620
	float ProtoBloomCompositePass::GetBloomStrength()
	{
		return bloomStrength;
	}

	// FUNCTION: ENGINE 0x10761630
	void ProtoBloomCompositePass::SetBackBufferStrength(float value)
	{
		backBufferStrength = value;
		shaderValid = false;
	}

	// FUNCTION: ENGINE 0x10761650
	float ProtoBloomCompositePass::GetBackBufferStrength()
	{
		return backBufferStrength;
	}

	// FUNCTION: ENGINE 0x107612C0
	void ProtoBloomColourAdjustPass::Begin()
	{
		CallIsVisible();
	}

	// FUNCTION: ENGINE 0x10761660
	void ProtoBloomCompositePass::Begin()
	{
		CallIsVisible();
	}

	// FUNCTION: ENGINE 0x10761220
	ProtoBloomColourAdjustPass::~ProtoBloomColourAdjustPass()
	{
	}

	// FUNCTION: ENGINE 0x10761230
	bool ProtoBloomColourAdjustPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		unknown24Bit1 = 1;
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderBloom))
			{
				shader = new Shader(gShaderBloom);
				shader->AddRef();
				return unknown24Bit1;
			}
			unknown24Bit1 = 0;
		}
		return unknown24Bit1;
	}

	// FUNCTION: ENGINE 0x10761EA0
	// EQUIVALENT: scheduling of the member stores and register allocation; the same stores of the same values and the same calls (71.2 %)
	ProtoBloomColourAdjustPass::ProtoBloomColourAdjustPass(const PassDesc* desc) : FrameBufferPass(desc)
	{
		const unsigned int& white = *(const unsigned int*)&math::pddiColour::WHITE;
		float one = engine::driving::gOne;
		float half = engine::driving::gHalf;
		brightness = 0.0f;
		hue = 0.0f;
		contrastScale = one;
		contrast = one;
		saturation = one;
		cutoff = 0.9f;
		power = engine::driving::gTwo;
		midpoint = half;
		float byteScale = 1.0f / 255.0f;
		tint.r = (float)((white >> 16) & 0xFF) * byteScale;
		tint.g = (float)((white >> 8) & 0xFF) * byteScale;
		tint.b = (float)(int)(white & 0xFF) * byteScale;
		tint.a = (float)(white >> 24) * byteScale;
		weights.x = gLuminanceWeights.x;
		weights.y = gLuminanceWeights.y;
		weights.z = gLuminanceWeights.z;
		matrixValid = false;
		matrix.Identity();
		entries.SetBit(0);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x1B, false);
	}

	// FUNCTION: ENGINE 0x10760FE0
	void ProtoBloomPass::SetBlurPass(BlurPass* pass)
	{
		blurPass = pass;
	}

	// FUNCTION: ENGINE 0x10760FF0
	bool ProtoBloomPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		if (blurPass == 0)
		{
			return false;
		}
		bool ready = colourAdjust->CallIsVisible() & 1;
		ready &= composite->CallIsVisible();
		if (ready)
		{
			AddChild(colourAdjust, 0);
			AddChild(blurPass, 0);
			AddChild(composite, 0);
		}
		unknown24Bit1 = ready;
		return ready;
	}

	// FUNCTION: ENGINE 0x107610D0
	void ProtoBloomPass::SetTextures(Texture* first, Texture* second)
	{
		textureE8 = first;
		first->AddRef();
		textureEC = second;
		second->AddRef();
	}

	// FUNCTION: ENGINE 0x10761100
	void ProtoBloomPass::Begin()
	{
		if (!GetUnknown24Bit1())
		{
			CallIsVisible();
		}
		colourAdjust->Begin();
		if ((char)composite->IsActive(false))
		{
			composite->Begin();
		}
		begun = 1;
	}

	// FUNCTION: ENGINE 0x10761150
	void ProtoBloomPass::UpdateBlur()
	{
		float first = size;
		if (!(first - 0.01f >= 0.0f))
		{
			first = 0.01f;
		}
		float limited = first;
		if (first - 100.0f >= 0.0f)
		{
			limited = 100.0f;
		}
		float second = blur;
		if (!(second - 0.01f >= 0.0f))
		{
			second = 0.01f;
		}
		float otherLimited = second;
		if (second - 100.0f >= 0.0f)
		{
			otherLimited = 100.0f;
		}
		blurPass->SetBlurSize(limited);
		blurPass->SetBlurRatio(otherLimited / limited);
		blurValid = true;
	}

	// FUNCTION: ENGINE 0x10761B50
	void ProtoBloomPass::End()
	{
		colourAdjust->ReleaseTextures();
		composite->ReleaseTextures();
		Pass::End();
		core::SafeRelease(textureE8);
		core::SafeRelease(textureEC);
	}

	// FUNCTION: ENGINE 0x10761200
	ParameterHandlerTypeless* ProtoBloomPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x10761990
	void ProtoBloomPass::SetBackBufferStrength(float value)
	{
		composite->SetBackBufferStrength(value);
	}

	// FUNCTION: ENGINE 0x107619B0
	float ProtoBloomPass::GetBackBufferStrength() const
	{
		return composite->GetBackBufferStrength();
	}

	// FUNCTION: ENGINE 0x10761960
	void ProtoBloomPass::SetBloomStrength(float value)
	{
		composite->SetBloomStrength(value);
	}

	// FUNCTION: ENGINE 0x10761980
	float ProtoBloomPass::GetBloomStrength() const
	{
		return composite->GetBloomStrength();
	}

	// FUNCTION: ENGINE 0x107617D0
	void ProtoBloomPass::SetBrightness(float value)
	{
		colourAdjust->SetBrightness(value);
	}

	// FUNCTION: ENGINE 0x107617F0
	float ProtoBloomPass::GetBrightness() const
	{
		return colourAdjust->GetBrightness();
	}

	// FUNCTION: ENGINE 0x10761800
	void ProtoBloomPass::SetContrast(float value)
	{
		colourAdjust->SetContrast(value);
	}

	// FUNCTION: ENGINE 0x10761820
	float ProtoBloomPass::GetContrast() const
	{
		return colourAdjust->GetContrast();
	}

	// FUNCTION: ENGINE 0x10761890
	void ProtoBloomPass::SetHue(float value)
	{
		colourAdjust->SetHue(value);
	}

	// FUNCTION: ENGINE 0x107618B0
	float ProtoBloomPass::GetHue() const
	{
		return colourAdjust->GetHue();
	}

	// FUNCTION: ENGINE 0x107618E0
	void ProtoBloomPass::SetCutoff(float value)
	{
		colourAdjust->SetCutoff(value);
	}

	// FUNCTION: ENGINE 0x10761900
	float ProtoBloomPass::GetCutoff() const
	{
		return colourAdjust->GetCutoff();
	}

	// FUNCTION: ENGINE 0x10761910
	void ProtoBloomPass::SetPower(float value)
	{
		colourAdjust->SetPower(value);
	}

	// FUNCTION: ENGINE 0x10761930
	float ProtoBloomPass::GetPower() const
	{
		return colourAdjust->GetPower();
	}

	// FUNCTION: ENGINE 0x10761830
	void ProtoBloomPass::SetMidpoint(float value)
	{
		colourAdjust->SetMidpoint(value);
	}

	// FUNCTION: ENGINE 0x10761850
	float ProtoBloomPass::GetMidpoint() const
	{
		return colourAdjust->GetMidpoint();
	}

	// FUNCTION: ENGINE 0x10761860
	void ProtoBloomPass::SetSaturation(float value)
	{
		colourAdjust->SetSaturation(value);
	}

	// FUNCTION: ENGINE 0x10761880
	float ProtoBloomPass::GetSaturation() const
	{
		return colourAdjust->GetSaturation();
	}

	// FUNCTION: ENGINE 0x107618C0
	void ProtoBloomPass::SetTint(const math::Colour128* value)
	{
		colourAdjust->SetTint(value);
	}

	// FUNCTION: ENGINE 0x107618D0
	const math::Colour128& ProtoBloomPass::GetTint()
	{
		return colourAdjust->GetTint();
	}

	// FUNCTION: ENGINE 0x10761940
	void ProtoBloomPass::SetWeights(const math::Vector* value)
	{
		colourAdjust->SetWeights(value);
	}

	// FUNCTION: ENGINE 0x10761950
	const math::Vector& ProtoBloomPass::GetWeights()
	{
		return colourAdjust->GetWeights();
	}

	// FUNCTION: ENGINE 0x10762CE0
	ProtoBloomPass::~ProtoBloomPass()
	{
		delete colourAdjust;
		colourAdjust = 0;
		delete composite;
		composite = 0;
		core::SafeRelease(textureE8);
		core::SafeRelease(textureEC);
	}

	// FUNCTION: ENGINE 0x10762D90
	// NONMATCHING: the engine's frame is 0x24 bytes (a zeroed word next to the name of the pass description); ours is 0x20 (70.1 %)
#ifdef NONMATCHING
	ProtoBloomPass::ProtoBloomPass(const PassDesc* desc) : FrameBufferPass(desc), textureE8(0), textureEC(0),
		colourAdjust(0), composite(0), blurPass(0), size(10.0f), blur(10.0f)
	{
		blurValid = false;
		colourAdjust = new ProtoBloomColourAdjustPass(&PassDesc(&core::Name<core::CaseSensitiveKey>("BloomColourAdjustPass", 1), 1));
		composite = new ProtoBloomCompositePass(&PassDesc(&core::Name<core::CaseSensitiveKey>("BloomComposite", 1), 1));
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoBloomPass::SetParameterEnable, 0);
		parameters.AddFloatInline(&gParamBackbufferstrength, &ProtoBloomPass::SetBackBufferStrength, &ProtoBloomPass::GetBackBufferStrength);
		parameters.AddFloatInline(&gParamBloomstrength, &ProtoBloomPass::SetBloomStrength, &ProtoBloomPass::GetBloomStrength);
		parameters.AddFloatInline(&gParamBrightness, &ProtoBloomPass::SetBrightness, &ProtoBloomPass::GetBrightness);
		parameters.AddFloatInline(&gParamConstrast, &ProtoBloomPass::SetContrast, &ProtoBloomPass::GetContrast);
		parameters.AddFloatInline(&gParamHue, &ProtoBloomPass::SetHue, &ProtoBloomPass::GetHue);
		parameters.AddFloatInline(&gParamLuminanceCutoff, &ProtoBloomPass::SetCutoff, &ProtoBloomPass::GetCutoff);
		parameters.AddFloatInline(&gParamPower, &ProtoBloomPass::SetPower, &ProtoBloomPass::GetPower);
		parameters.AddFloatInline(&gParamMidpoint, &ProtoBloomPass::SetMidpoint, &ProtoBloomPass::GetMidpoint);
		parameters.AddFloatInline(&gParamRadiusx, &ProtoBloomPass::SetSize, &ProtoBloomPass::GetSize);
		parameters.AddFloatInline(&gParamRadiusy, &ProtoBloomPass::SetBlur, &ProtoBloomPass::GetBlur);
		parameters.AddFloatInline(&gParamSaturation, &ProtoBloomPass::SetSaturation, &ProtoBloomPass::GetSaturation);
		parameters.AddFloatInline(&gParamBrightness, &ProtoBloomPass::SetBrightness, &ProtoBloomPass::GetBrightness);
		parameters.AddColour128Inline(&gParamTint, &ProtoBloomPass::SetTint, &ProtoBloomPass::GetTint);
		parameters.AddVectorInline(&gParamWeights, &ProtoBloomPass::SetWeights, &ProtoBloomPass::GetWeights);
	}
#endif

	// FUNCTION: ENGINE 0x10760AB0
	ProtoFBPass::~ProtoFBPass()
	{
		delete toneMapPass;
		toneMapPass = 0;
		delete bloomPass;
		bloomPass = 0;
		delete colourMatrixPass;
		colourMatrixPass = 0;
		delete thermalPass;
		thermalPass = 0;
		delete motherPass;
		motherPass = 0;
		delete copyPass;
		copyPass = 0;
		delete blurPass;
		blurPass = 0;
		core::SafeRelease(shader10C);
		core::SafeRelease(shader110);
		core::SafeRelease(texture108);
	}

	// FUNCTION: ENGINE 0x10760BE0
	// EQUIVALENT: scheduling of the member stores and register allocation; the same stores and calls in the same order (74.9 %)
	ProtoFBPass::ProtoFBPass(const PassDesc* desc) : FrameBufferPass(desc), toneMapPass(0), bloomPass(0),
		colourMatrixPass(0), thermalPass(0), motherPass(0), unknownFC(0), copyPass(0), blurPass(0), texture108(0),
		shader10C(0), shader110(0), visionMode(0), visionStrength(0.0f), unknown11C(0), mixAmount(0.06f)
	{
		colourMix.x = 0.0f;
		colourMix.y = 0.25f;
		colourMix.z = 0.47f;
		alexColour.x = engine::driving::gHalf;
		alexColour.y = 0.0f;
		alexColour.z = 0.0f;
		unknown13C[0] = 0;
		unknown13C[1] = 0;
		unknown13C[2] = 0;
		unknown13C[3] = 0;
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoFBPass::SetParameterEnable, 0);
		toneMapPass = new ProtoToneMapPass(&PassDesc(&gPassNamePrototypeTonemap, 1));
		bloomPass = new ProtoBloomPass(&PassDesc(&gPassNamePrototypeBloom, 1));
		colourMatrixPass = new ProtoColourMatrixPass(&PassDesc(&gPassNamePrototypeColourMatrix, 1));
		thermalPass = new ProtoThermalPass(&PassDesc(&gPassNamePrototypeThermalVision, 1));
		motherPass = new ProtoMotherPass(&PassDesc(&gPassNamePrototypeMotherVision, 1));
		copyPass = new CopyPass(&PassDesc(&gPassNameCopyPass, 1));
		blurPass = new BlurPass(&PassDesc(&gPassNameBlurPass, 1));
		AddChild(toneMapPass, 0);
		AddChild(bloomPass, 0);
		AddChild(colourMatrixPass, 0);
		AddChild(thermalPass, 0);
		AddChild(motherPass, 0);
		parameters.AddVariableInline(&gParamPrototypeChameleonicColourMix, &mixAmount);
		parameters.AddVariableInline(&gParamPrototypeChameleonicAlexColour, &colourMix);
		parameters.AddVariableInline(&gParamPrototypeChameleonicInfecedColour, &alexColour);
		parameters.AddVariableInline(&gParamPrototypeVisionMode, &visionMode);
		parameters.AddVariableInline(&gParamPrototypeVisionModeStrength, &visionStrength);
	}
}

namespace pure3d
{
	// The table of the contrast scale of the colour matrix pass (0x10E5F008)
	extern const float gColourMatrixContrastTable[101];

	// FUNCTION: ENGINE 0x107634E0
	float ProtoColourMatrixPass::GetBrightness()
	{
		return brightness;
	}

	// FUNCTION: ENGINE 0x107634F0
	float ProtoColourMatrixPass::GetContrast()
	{
		return contrast;
	}

	// FUNCTION: ENGINE 0x10763500
	float ProtoColourMatrixPass::GetMidpoint()
	{
		return midpoint;
	}

	// FUNCTION: ENGINE 0x10763510
	float ProtoColourMatrixPass::GetSaturation()
	{
		return saturation;
	}

	// FUNCTION: ENGINE 0x10763520
	float ProtoColourMatrixPass::GetHue()
	{
		return hue;
	}

	// FUNCTION: ENGINE 0x10763530
	// EQUIVALENT: the engine reads the colour into ecx and the output pointer into eax, ours the other way round (80.0 %)
	void ProtoColourMatrixPass::GetTint(unsigned int* value)
	{
		*(math::pddiColour*)value = tint;
	}

	// FUNCTION: ENGINE 0x10763540
	// EQUIVALENT: the same stores and float operations in the engine's order; the sum for the table index is formed in a second register and a store is scheduled one step earlier (46.8 %)
	void ProtoColourMatrixPass::SetValues(float newBrightness, float newContrast, float newMidpoint,
		float newSaturation, float newHue, unsigned int newTint)
	{
		float low = -100.0f;
		float difference = newContrast - low;
		contrast = newContrast;
		if (!(difference >= 0.0f))
		{
			newContrast = low;
		}
		float high = 100.0f;
		if (newContrast - high >= 0.0f)
		{
			newContrast = high;
		}
		float scale;
		if (newContrast < 0.0f)
		{
			scale = newContrast * 0.01f + engine::driving::gOne;
		}
		else
		{
			scale = gColourMatrixContrastTable[(int)(newContrast + engine::driving::gHalf)];
		}
		contrastScale = scale;
		midpoint = newMidpoint;
		saturation = newSaturation;
		brightness = newBrightness;
		hue = newHue;
		*(unsigned int*)&tint = newTint;
	}

	// FUNCTION: ENGINE 0x10763600
	// EQUIVALENT: the load of the scale constant sits before the copy in the engine, after it in ours (76.2 %)
	void ProtoColourMatrixPass::SetCMY(const math::Vector* value)
	{
		float scale = 0.01f;
		cmy.x = value->x;
		cmy.y = value->y;
		cmy.z = value->z;
		_ReadWriteBarrier();
		cmy.x = cmy.x * scale;
		cmy.y = cmy.y * scale;
		cmy.z = cmy.z * scale;
	}

	// FUNCTION: ENGINE 0x10763670
	void ProtoColourMatrixPass::SetCMYScaleBias(const math::Vector2* value)
	{
		cmyScaleBias.x = value->x;
		cmyScaleBias.y = value->y * value->x;
	}

	// FUNCTION: ENGINE 0x107636B0
	void ProtoColourMatrixPass::SetOverlayValues(float opacity, float newSaturation)
	{
		overlayOpacity = opacity;
		overlaySaturation = newSaturation;
	}

	// FUNCTION: ENGINE 0x107636D0
	void ProtoColourMatrixPass::SetDistortion(Texture* texture)
	{
		distortion = texture;
		texture->AddRef();
	}

	// FUNCTION: ENGINE 0x107636F0
	void ProtoColourMatrixPass::Begin()
	{
		if (!GetUnknown24Bit1())
		{
			CallIsVisible();
		}
		begun = 1;
	}

	// FUNCTION: ENGINE 0x10763710
	ParameterHandlerTypeless* ProtoColourMatrixPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x10763460
	bool ProtoColourMatrixPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		bool ready = false;
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderColourMatrix))
			{
				shader = new Shader(gShaderColourMatrix);
				shader->AddRef();
				unknown24Bit1 = 1;
				ready = true;
			}
		}
		return ready;
	}

	// FUNCTION: ENGINE 0x107638A0
	void ProtoColourMatrixPass::SetOverlay(Texture* texture)
	{
		overlay = texture;
	}

	// FUNCTION: ENGINE 0x107638E0
	void ProtoColourMatrixPass::SetGrain(Texture* texture)
	{
		grain = texture;
	}

	// FUNCTION: ENGINE 0x10763F30
	void ProtoColourMatrixPass::End()
	{
		core::SafeRelease(distortion);
	}

	// FUNCTION: ENGINE 0x10764880
	ProtoColourMatrixPass::~ProtoColourMatrixPass()
	{
	}

	// FUNCTION: ENGINE 0x10764910
	// EQUIVALENT: the handler's construction comes after the plain member stores in the engine (the same calls and stores, scheduled differently) (29.3 %)
	ProtoColourMatrixPass::ProtoColourMatrixPass(const PassDesc* desc) : FrameBufferPass(desc), distortion(0),
		brightness(0.0f), hue(0.0f)
	{
		float one = engine::driving::gOne;
		float half = engine::driving::gHalf;
		contrastScale = one;
		contrast = one;
		midpoint = half;
		saturation = one;
		*(unsigned int*)&tint = 0xFFFFFFFF;
		cmy.x = 0.0f;
		cmy.y = 0.0f;
		cmy.z = 0.0f;
		cmyScaleBias.x = 0.0f;
		cmyScaleBias.y = 0.0f;
		grainSpeed = gColourMatrixGrainSpeed;
		grainIntensity = 0.21f;
		overlayOpacity = gColourMatrixOverlayOpacity;
		overlaySaturation = gColourMatrixOverlaySaturation;
		distortionEnabled = true;
		parameters.AddVariableInline(&gParamBrightness, &brightness);
		parameters.AddVariableInline(&gParamConstrast, &contrast);
		parameters.AddVariableInline(&gParamMidpoint, &midpoint);
		parameters.AddVariableInline(&gParamSaturation, &saturation);
		parameters.AddVariableInline(&gParamHue, &hue);
		parameters.AddVariableInline(&gParamTint, &tint);
		parameters.AddVariableInline(&gParamPrototypeCMY, &cmy);
		parameters.AddVariableInline(&gParamPrototypeCMYScaleBias, &cmyScaleBias);
		parameters.AddVariableInline(&gParamPrototypeGrainSpeed, &grainSpeed);
		parameters.AddVariableInline(&gParamPrototypeGrainIntensity, &grainIntensity);
		parameters.AddVariableInline(&gParamPrototypeOverlayOpacity, &overlayOpacity);
		parameters.AddVariableInline(&gParamPrototypeOverlaySaturation, &overlaySaturation);
		parameters.AddVariableInline(&gParamPrototypeDistortionStrength, &distortionEnabled);
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoColourMatrixPass::SetParameterEnable, 0);
		entries.SetBit(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x16, false);
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x10769900
	ParameterHandlerTypeless* ProtoFogPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107698F0
	void ProtoFogPass::Begin()
	{
		Pass::Begin();
	}

	// FUNCTION: ENGINE 0x1076A4B0
	ProtoFogPass::~ProtoFogPass()
	{
		if (object != 0)
		{
			object->Release();
			object = 0;
		}
	}

	// FUNCTION: ENGINE 0x1076A550
	// EQUIVALENT: the engine loads the constant and stores the vftable pointer after the base constructor call, ours stores the vftable pointer first; the same stores and calls (98.1 %)
	ProtoFogPass::ProtoFogPass(const PassDesc* desc) : FrameBufferPass(desc), tiling(engine::driving::gOne, engine::driving::gOne),
		variation(0.0f), speed(0.0f), object(0)
	{
		entries.SetBit(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		parameters.AddVariableInline(&gParamPrototypeFogTiling, &tiling);
		parameters.AddVariableInline(&gParamPrototypeFogVariation, &variation);
		parameters.AddVariableInline(&gParamPrototypeFogSpeed, &speed);
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoFogPass::SetParameterEnable, 0);
	}

	// FUNCTION: ENGINE 0x10772500
	ParameterHandlerTypeless* ProtoRadialBlurPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107721C0
	void ProtoRadialBlurPass::SetValues(float x, float y, float z, float newRadius, float newIntensity,
		float newSize, float newFalloff)
	{
		source.x = x;
		source.y = y;
		source.z = z;
		radius = newRadius;
		intensity = newIntensity;
		size = newSize;
		falloff = newFalloff;
	}

	// FUNCTION: ENGINE 0x10772150
	bool ProtoRadialBlurPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderRadialBlur))
			{
				shader = new Shader(gShaderRadialBlur);
				shader->AddRef();
				unknown24Bit1 = 1;
			}
		}
		return unknown24Bit1;
	}

	// FUNCTION: ENGINE 0x10773280
	ProtoRadialBlurPass::~ProtoRadialBlurPass()
	{
	}

	// FUNCTION: ENGINE 0x107732E0
	// EQUIVALENT: the same stores and calls; the arguments of the call to the setter are built differently (the zeros come from an SSE register in the engine, from the x87 unit here) (41.4 %)
	ProtoRadialBlurPass::ProtoRadialBlurPass(const PassDesc* desc) : FrameBufferPass(desc), radius(0.0f), unknownEC(0.0f),
		unknownF0(0.0f), unknownF4(0.0f), unknownF8(0.0f), source(0.0f, 0.0f, 0.0f), intensity(0.0f), size(0.0f),
		falloff(engine::driving::gOne), sampleScale(engine::driving::gOne)
	{
		SetValues(0.0f, 0.0f, 0.0f, 7.0f, 1.0f, 0.0f, 1.0f);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurRadius, &radius);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurSource, &source);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurIntensity, &intensity);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurSize, &size);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurFalloff, &falloff);
		parameters.AddVariableInline(&gParamPrototypeRadialBlurSampleScale, &sampleScale);
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoRadialBlurPass::SetParameterEnable, 0);
	}

	// FUNCTION: ENGINE 0x10773540
	ParameterHandlerTypeless* DepthOfFieldPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x10774310
	DepthOfFieldPass::~DepthOfFieldPass()
	{
		core::SafeRelease(texture100);
		core::SafeRelease(textureFC);
		core::SafeRelease(shaderF8);
		core::SafeRelease(shaderF4);
		core::SafeRelease(shaderEC);
		core::SafeRelease(shaderF0);
		core::SafeRelease(shaderE8);
	}

	// FUNCTION: ENGINE 0x107743D0
	// EQUIVALENT: scheduling of the constant load and an address computation relative to the vftable store; the same stores and calls (80.7 %)
	DepthOfFieldPass::DepthOfFieldPass(const PassDesc* desc) : FrameBufferPass(desc), shaderE8(0), shaderEC(0), shaderF0(0),
		shaderF4(0), shaderF8(0), textureFC(0), texture100(0), nearDepth(0.0f), farDepth(0.0f), range(engine::driving::gOne),
		aperture(0.0f)
	{
		parameters.AddVariableInline(&gParamDofNearDepth, &nearDepth);
		parameters.AddVariableInline(&gParamDofFarDepth, &farDepth);
		parameters.AddVariableInline(&gParamDofRange, &range);
		parameters.AddVariableInline(&gParamDofAperture, &aperture);
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &DepthOfFieldPass::SetParameterEnable, 0);
	}
}

// ---- the instances of the parameter handlers ----

	// FUNCTION: ENGINE 0x1075F570
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry&);

	// FUNCTION: ENGINE 0x1075F5A0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x1075F5C0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x1075F5D0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x1075F530
	template void pure3d::ParameterHandler<pure3d::ProtoFBPass>::SetObject(pure3d::ProtoFBPass*);

	// FUNCTION: ENGINE 0x107605D0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x107605E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x107605F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10760630
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10760670
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10760690
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107606D0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10760710
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10760780
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107607B0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107607C0
	template pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10760830
	template bool pure3d::ParameterHandler<pure3d::ProtoFBPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x10760890
	template bool pure3d::ParameterHandler<pure3d::ProtoFBPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x10760910
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x10760920
	template void pure3d::ParameterHandler<pure3d::ProtoFBPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoFBPass::*)(bool), bool (pure3d::ProtoFBPass::*)());

	// FUNCTION: ENGINE 0x10760990
	template void pure3d::ParameterHandler<pure3d::ProtoFBPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, float*);

	// FUNCTION: ENGINE 0x107609D0
	template void pure3d::ParameterHandler<pure3d::ProtoFBPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, math::Vector*);

	// FUNCTION: ENGINE 0x10760A10
	template void pure3d::ParameterHandler<pure3d::ProtoFBPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, int*);

	// FUNCTION: ENGINE 0x10760A50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFBPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFBPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x10760A60
	template pure3d::ParameterHandler<pure3d::ProtoFBPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10760A90
	template pure3d::ParameterHandler<pure3d::ProtoFBPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10761690
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry&);

	// FUNCTION: ENGINE 0x107616C0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107616E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107616F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10761670
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::SetObject(pure3d::ProtoBloomPass*);

	// FUNCTION: ENGINE 0x10761E20
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10761E30
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10761E40
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10761E80
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10762380
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107623A0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107623E0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107624E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10762550
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10762580
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10762590
	template pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10762600
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::SetFloatAdapter(void*, const core::Name<core::CaseSensitiveKey>*, float);

	// FUNCTION: ENGINE 0x10762660
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107626C0
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::SetVectorAdapter(void*, const core::Name<core::CaseSensitiveKey>*, const math::Vector*);

	// FUNCTION: ENGINE 0x10762720
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::SetColour128Adapter(void*, const core::Name<core::CaseSensitiveKey>*, const math::Colour128*);

	// FUNCTION: ENGINE 0x10762780
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::GetFloatAdapter(void*, const core::Name<core::CaseSensitiveKey>*, float*);

	// FUNCTION: ENGINE 0x10762800
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x10762880
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::GetVectorAdapter(void*, const core::Name<core::CaseSensitiveKey>*, math::Vector*);

	// FUNCTION: ENGINE 0x10762920
	// EQUIVALENT: the engine loads the getter of the second kind into edx before the compare and calls it through edx; the copy and the calls are the same (53.1 %)
	template bool pure3d::ParameterHandler<pure3d::ProtoBloomPass>::GetColour128Adapter(void*, const core::Name<core::CaseSensitiveKey>*, math::Colour128*);

	// FUNCTION: ENGINE 0x107629C0
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddAdapters(const core::Name<core::CaseSensitiveKey>*, bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, const math::Colour128*), bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, math::Colour128*));

	// FUNCTION: ENGINE 0x10762A10
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddAdapters(const core::Name<core::CaseSensitiveKey>*, bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, const math::Vector*), bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, math::Vector*));

	// FUNCTION: ENGINE 0x10762A60
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddAdapters(const core::Name<core::CaseSensitiveKey>*, bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, float), bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, float*));

	// FUNCTION: ENGINE 0x10762AB0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x10762AC0
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddColour128(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ProtoBloomPass::*)(const math::Colour128*), const math::Colour128& (pure3d::ProtoBloomPass::*)());

	// FUNCTION: ENGINE 0x10762B30
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddVector(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ProtoBloomPass::*)(const math::Vector*), const math::Vector& (pure3d::ProtoBloomPass::*)());

	// FUNCTION: ENGINE 0x10762BA0
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddFloat(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ProtoBloomPass::*)(float), float (pure3d::ProtoBloomPass::*)() const);

	// FUNCTION: ENGINE 0x10762C10
	template void pure3d::ParameterHandler<pure3d::ProtoBloomPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoBloomPass::*)(bool), bool (pure3d::ProtoBloomPass::*)());

	// FUNCTION: ENGINE 0x10762C80
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoBloomPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x10762C90
	template pure3d::ParameterHandler<pure3d::ProtoBloomPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10762CC0
	template pure3d::ParameterHandler<pure3d::ProtoBloomPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x107637F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry&);

	// FUNCTION: ENGINE 0x10763820
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x10763840
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x10763850
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107637B0
	template void pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::SetObject(pure3d::ProtoColourMatrixPass*);

	// FUNCTION: ENGINE 0x10763F50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10763F60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10763F70
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10763FB0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10764440
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10764460
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107644A0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107644E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10764550
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10764580
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10764590
	template pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10764600
	template bool pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x10764660
	template bool pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107646E0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107646F0
	template void pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoColourMatrixPass::*)(bool), bool (pure3d::ProtoColourMatrixPass::*)());

	// FUNCTION: ENGINE 0x10764760
	template void pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, math::pddiColour*);

	// FUNCTION: ENGINE 0x107647A0
	template void pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, math::Vector2*);

	// FUNCTION: ENGINE 0x107647E0
	template void pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::AddVariable(const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x10764820
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x10764830
	template pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10764860
	template pure3d::ParameterHandler<pure3d::ProtoColourMatrixPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10769930
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry&);

	// FUNCTION: ENGINE 0x10769960
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x10769980
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x10769990
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10769910
	template void pure3d::ParameterHandler<pure3d::ProtoFogPass>::SetObject(pure3d::ProtoFogPass*);

	// FUNCTION: ENGINE 0x10769A50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10769A60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10769A70
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10769AB0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10769C00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10769C20
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10769C60
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10769DC0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10769E30
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x1076A120
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x1076A130
	template pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x1076A1A0
	template bool pure3d::ParameterHandler<pure3d::ProtoFogPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x1076A200
	template bool pure3d::ParameterHandler<pure3d::ProtoFogPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x1076A2D0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x1076A2E0
	template void pure3d::ParameterHandler<pure3d::ProtoFogPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoFogPass::*)(bool), bool (pure3d::ProtoFogPass::*)());

	// FUNCTION: ENGINE 0x1076A360
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoFogPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoFogPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x1076A370
	template pure3d::ParameterHandler<pure3d::ProtoFogPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x1076A490
	template pure3d::ParameterHandler<pure3d::ProtoFogPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10772530
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry&);

	// FUNCTION: ENGINE 0x10772560
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x10772580
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x10772590
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10772510
	template void pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::SetObject(pure3d::ProtoRadialBlurPass*);

	// FUNCTION: ENGINE 0x10772E00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10772E10
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10772E20
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10772E60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10772F00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10772F20
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10772F60
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10772FA0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10773010
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10773040
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10773050
	template pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107730C0
	template bool pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x10773120
	template bool pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107731A0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107731B0
	template void pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoRadialBlurPass::*)(bool), bool (pure3d::ProtoRadialBlurPass::*)());

	// FUNCTION: ENGINE 0x10773220
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x10773230
	template pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10773260
	template pure3d::ParameterHandler<pure3d::ProtoRadialBlurPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10773570
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry&);

	// FUNCTION: ENGINE 0x107735A0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107735C0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107735D0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10773550
	template void pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::SetObject(pure3d::DepthOfFieldPass*);

	// FUNCTION: ENGINE 0x10773EF0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10773F00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10773F10
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10773F50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10773F90
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10773FB0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10773FF0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10774030
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107740A0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107740D0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107740E0
	template pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry& pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10774150
	template bool pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107741B0
	template bool pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x10774230
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x10774240
	template void pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::DepthOfFieldPass::*)(bool), bool (pure3d::DepthOfFieldPass::*)());

	// FUNCTION: ENGINE 0x107742B0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::Entry, pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107742C0
	template pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x107742F0
	template pure3d::ParameterHandler<pure3d::DepthOfFieldPass>::~ParameterHandler();

