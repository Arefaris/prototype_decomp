// pure3d::NewShaderLoader: see the header. The file name is a guess.
#include "code/pure3d/loaders/newshaderloader.h"

#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/shader.h"

namespace content
{
	// 0x104D7740: the texture of that name in the inventory (the engine keeps the copy of the template this unit
	// calls)
	template<> pure3d::Texture* LoadInventory::Find<pure3d::Texture>(const char* name);
}

namespace pure3d
{
	// 0x112806E0: the name the shader's default texture goes under
	extern core::Name<core::CaseInsensitiveKey32> gDefaultTextureName;

	// FUNCTION: ENGINE 0x10B96280
	void NewShaderLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
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
		char templateName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(templateName, length, 1, 1);
			templateName[length] = 0;
		}
		ReadWord(reader);
		Shader* shader = new Shader(templateName);
		shader->AddRef();
		bool defaultTexture = false;
		if (core::Name<core::CaseInsensitiveKey32>("error", 1) == shader->shader->GetTechniques()->templateName)
		{
			if (listener != 0)
			{
				listener->Report(shaderName, templateName);
			}
		}
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			switch (id)
			{
			case 0x11016:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				char textureName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(textureName, length, 1, 1);
					textureName[length] = 0;
				}
				if (textureName[0] != 0)
				{
					Texture* texture = inventory->Find<Texture>(textureName);
					if (texture != 0)
					{
						core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
						shader->shader->SetTexture(key, texture->info);
					}
				}
				break;
			}
			case 0x1101D:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				char value;
				reader->Read(&value, 1, 1, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetBool(key, value != 0);
				break;
			}
			case 0x11017:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				float value;
				reader->Read(&value, 1, 4, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetFloat(key, value);
				break;
			}
			case 0x11018:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				float value[2];
				reader->Read(value, 2, 4, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetVector2(key, value);
				break;
			}
			case 0x11019:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				math::Vector value;
				reader->Read(&value, 3, 4, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetVector3(key, value);
				break;
			}
			case 0x1101A:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				math::Vector4 value;
				reader->Read(&value, 4, 4, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetVector4(key, value);
				break;
			}
			case 0x1101B:
			{
				char parameterName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(parameterName, length, 1, 1);
					parameterName[length] = 0;
				}
				float value[16];
				reader->Read(value, 16, 4, 1);
				core::Name<core::CaseInsensitiveKey32> key(parameterName, 1);
				shader->shader->SetMatrix(key, value);
				break;
			}
			case 0x1101C:
			{
				PrimStreamParameters state;
				state.unknown0 = 0.5f;
				unsigned short first;
				reader->Read(&first, 1, 2, 1);
				state.blendMode = first;
				unsigned short second;
				reader->Read(&second, 1, 2, 1);
				state.blendFactor = second;
				unsigned short third;
				reader->Read(&third, 1, 2, 1);
				state.unknown4Bits10 = third;
				state.flag0 = state.unknown4Bits10 != 0;
				float number;
				reader->Read(&number, 1, 4, 1);
				state.unknown0 = number;
				shader->SetParameters(state);
				break;
			}
			case 0x11020:
			{
				unsigned short first;
				reader->Read(&first, 1, 2, 1);
				shader->unknown24Bits = first;
				unsigned short flags;
				reader->Read(&flags, 1, 2, 1);
				if ((flags & 1) == 0)
				{
					defaultTexture = true;
				}
				break;
			}
			case 0x1101F:
			{
				unsigned short value;
				reader->Read(&value, 1, 2, 1);
				shader->unknown24Bits = value;
				break;
			}
			}
			reader->EndChunk();
		}
		if (defaultTexture)
		{
			shader->shader->SetTexture(gDefaultTextureName, 0);
		}
		shader->SetNameText(shaderName);
		*object = shader;
		*name = content::ObjectName(shaderName, 1);
	}
}
