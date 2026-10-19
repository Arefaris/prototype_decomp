// pure3d::ShaderLoader: see the header. The file name is a guess.
#include <string.h>

#include "code/pure3d/loaders/shaderloader.h"

#include "code/core/strings.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderconstants.h"

namespace pure3d
{
	// The shader's methods share the unit with its loader (0x107062D0 - 0x10707260): with SetParameters compiled here
	// the compiler knows it only reads through its reference, so the loader keeps the draw parameters in registers
	// across the other calls, as the engine's loader does.
	// FUNCTION: ENGINE 0x107062D0
	// NONMATCHING: 95.9 % with dxTechniques::IsEnabled declared (the two virtual GetTechniques calls take the vftable
	// in eax and the slot in edx, the engine the other way round; a local for the technique table, for the enabled
	// flag or for the device shader at the top, a nested call expression and a reference to the device shader keep
	// eax for the vftable); not compiled because declaring IsEnabled (0x10618560) as a fifth member function of
	// dxTechniques moves two locals of Context::LoadDebugFont out of their slots. Compiled in this unit, it lets the
	// loader below keep the draw parameters in registers (see there).
#ifdef NONMATCHING
	void Shader::SetParameters(const PrimStreamParameters& newParameters)
	{
		bool zFillChanged = (newParameters.flag0 ^ parameters.flag0) != 0;
		parameters = newParameters;
		if (parameters.blendMode == 1 && parameters.blendFactor == 0)
		{
			flags.Set(2, false);
		}
		else
		{
			flags.Set(2, true);
		}
		flags.Set(4, parameters.flag1);
		if (parameters.flag0)
		{
			flags.Set(4, false);
		}
		if (zFillChanged)
		{
			dxShader* device = shader;
			int technique = device->GetTechniques()->Find(&gShaderZFill);
			if (!device->GetTechniques()->IsEnabled(technique))
			{
				flags.Set(3, true);
			}
			else
			{
				flags.Set(3, false);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x107065C0
	bool ShaderLoader::HasName(unsigned int code, const char* type)
	{
		if (names.Find(code).node != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107065F0
	const char** ShaderLoader::InputNames::At(const unsigned int* code)
	{
		MapNode* node = Find(*code).node;
		if (node == 0)
		{
			node = Insert(Pair(*code, 0)).node;
		}
		return &node->pair.value;
	}

	// FUNCTION: ENGINE 0x10706960
	// EQUIVALENT: 41.8 % of the bytes, 435 of the engine's 617 instructions in its order; the same reads, calls (with
	// the same arguments), branches and stores. The engine keeps the draw parameters' bit word in a register through
	// the chunk loop because its compiler knows Shader::SetParameters, the only callee that takes their address, does
	// not keep it (compiled in this unit it would give 51.6 %, but it needs dxTechniques::IsEnabled declared, see
	// above); this compiler loads the word in every branch; one more frame slot (0x4E4 against 0x4E0) and the
	// placement of the 0x11003 case's SetFloat path. difftest on the two captured states: every call, argument,
	// return and store is the engine's except five bytes of the shader's parameters (the bit word's top byte, bits
	// 3 - 7 of the flag byte and the three bytes after it): both functions copy them from their own uninitialised
	// stack (`PrimStreamParameters()` sets bits 0 - 23 of the word and the three flags, the rest stays as the frame
	// had it; the engine's Shader constructor and Init leave the same bits as the heap and the technique's record
	// had them), and nothing reads them: the device's state applier 0x10629E80 masks bits 0 - 23 of the word and
	// bits 0 and 2 of the flag byte, SetParameters reads bits 0 - 9 and flag bits 0 - 1, the passes and the tracer
	// the same fields.
	void ShaderLoader::LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
		content::LoadInventory* inventory)
	{
		char shaderName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(shaderName, length, 1, 1);
			shaderName[length] = 0;
		}
		ReadWord(reader);
		char typeName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(typeName, length, 1, 1);
			typeName[length] = 0;
		}
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		char templateName[0x100];
		core::StrCpy(templateName, "error");
		if (strcmp(typeName, "legacy") == 0)
		{
			core::StrCpy(templateName, "legacy");
		}
		if (strcmp(typeName, "unlit") == 0)
		{
			core::StrCpy(templateName, "unlit");
		}
		if (strcmp(typeName, "simple") == 0 || strcmp(typeName, "layered") == 0 ||
			strcmp(typeName, "layeredReflect") == 0)
		{
			core::StrCpy(templateName, "unlit");
		}
		if (strcmp(typeName, "default") == 0 || strcmp(typeName, "nextgen") == 0 ||
			strcmp(typeName, "simplebump") == 0)
		{
			core::StrCpy(templateName, "default");
		}
		if (strcmp(typeName, "pointsprite") == 0)
		{
			core::StrCpy(templateName, "pointsprite");
		}
		Shader* shader = new Shader(templateName);
		shader->AddRef();
		PrimStreamParameters parameters;
		parameters.unknown0 = 0.5f;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			switch (id)
			{
			case 0x11002:
			{
				unsigned int code = ReadWord(reader);
				char textureName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(textureName, length, 1, 1);
					textureName[length] = 0;
				}
				content::LoadInventory::DynamicCaster<Texture> caster;
				Texture* texture = (Texture*)inventory->FindObject(&caster, content::ObjectName(textureName, 1), true);
				if (texture != 0 && HasName(code, typeName))
				{
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetTexture(key, texture->info);
				}
				break;
			}
			case 0x11003:
			{
				unsigned int code = ReadWord(reader);
				int value = ReadWord(reader);
				if (code == 0x54494C)
				{
					if (value == 1)
					{
						shader->flags.Set(0, true);
					}
				}
				else if (code == 0x444D4C42)
				{
					switch (value)
					{
					case 4:
						parameters.blendMode = 4;
						parameters.blendFactor = 0;
						break;
					case 2:
						parameters.blendMode = 1;
						parameters.blendFactor = 1;
						break;
					case 1:
						parameters.blendMode = 6;
						parameters.blendFactor = 7;
						break;
					}
				}
				else if (code == 0x54535441)
				{
					parameters.flag0 = value != 0;
				}
				else if (code == 0x504D4341)
				{
					parameters.unknown4Bits10 = value;
				}
				else if (HasName(code, typeName))
				{
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->SetFloat(key, (float)(unsigned int)value);
				}
				break;
			}
			case 0x11004:
			{
				unsigned int code = ReadWord(reader);
				float value;
				reader->Read(&value, 1, 4, 1);
				if (HasName(code, typeName))
				{
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetFloat(key, value);
				}
				break;
			}
			case 0x11005:
			{
				unsigned int code = ReadWord(reader);
				unsigned int rgba = ReadWord(reader);
				if (code != 0x49424D41 && HasName(code, typeName))
				{
					math::Vector4 colour;
					colour.x = (float)(int)(rgba >> 16 & 0xFF) * (1.0f / 255.0f);
					colour.y = (float)(int)(rgba >> 8 & 0xFF) * (1.0f / 255.0f);
					colour.z = (float)(int)(rgba & 0xFF) * (1.0f / 255.0f);
					colour.w = (float)(int)(rgba >> 24) * (1.0f / 255.0f);
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetColour(key, colour);
				}
				if (code == 0x46464944 && HasName(0x46464944, typeName))
				{
					math::Vector4 colour;
					colour.x = (float)(int)(rgba >> 16 & 0xFF) * (1.0f / 255.0f);
					colour.y = (float)(int)(rgba >> 8 & 0xFF) * (1.0f / 255.0f);
					colour.z = (float)(int)(rgba & 0xFF) * (1.0f / 255.0f);
					colour.w = (float)(int)(rgba >> 24) * (1.0f / 255.0f);
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetColour(key, colour);
				}
				break;
			}
			case 0x11006:
			{
				unsigned int code = ReadWord(reader);
				math::Vector value;
				reader->Read(&value, 3, 4, 1);
				if (HasName(code, typeName))
				{
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetVector3(key, value);
				}
				break;
			}
			case 0x11007:
			{
				unsigned int code = ReadWord(reader);
				float value[16];
				reader->Read(value, 16, 4, 1);
				if (HasName(code, typeName))
				{
					core::Name<core::CaseInsensitiveKey32> key(*names.At(&code), 1);
					shader->shader->SetMatrix(key, value);
				}
				break;
			}
			}
			reader->EndChunk();
		}
		shader->SetParameters(parameters);
		shader->SetNameText(shaderName);
		*object = shader;
		*name = content::ObjectName(shaderName, 1);
	}
}
