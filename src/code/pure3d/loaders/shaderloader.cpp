// pure3d::ShaderLoader: see the header. The file name is a guess.
#include <string.h>

#include "code/pure3d/loaders/shaderloader.h"

#include "code/core/strings.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/shader.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10706960
	// NONMATCHING: the engine keeps the draw parameters' bit word in a register through the chunk loop and writes it
	// back after each change, this compiler reads and writes it in memory (42 %, the control flow and the calls are
	// the engine's)
#ifdef NONMATCHING
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
#endif
}
