// pure3d::ShaderTemplateLoader: see the header. The file name is a guess.
#include <string.h>

#include "code/pure3d/loaders/shadertemplateloader.h"

#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// 0x1127F358
	extern dxContext* gPddiDx;
	// 0x1120A1D4: the kind of input each number of the file stands for
	extern int gShaderInputKinds[6];

	// FUNCTION: ENGINE 0x10B95780
	// NONMATCHING: the frame differs in the order of the four name buffers and the scalars (39 %, the control flow
	// and the calls are the engine's)
#ifdef NONMATCHING
	void ShaderTemplateLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
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
		unsigned int first;
		reader->Read(&first, 1, 4, 1);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		ReadWord(reader);
		unsigned int second = 3;
		if (reader->GetPosition() < reader->GetSize())
		{
			unsigned int value;
			reader->Read(&value, 1, 4, 1);
			second = value;
		}
		dxShaderTemplate* shaderTemplate = gPddiDx->NewShaderTemplate(shaderName, first, second);
		pddiShaderInputInitData inputs;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			switch (id)
			{
			case 0x1100E:
			{
				char inputName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(inputName, length, 1, 1);
					inputName[length] = 0;
				}
				int type;
				reader->Read(&type, 1, 4, 1);
				int kind = gShaderInputKinds[type];
				unsigned int unused;
				reader->Read(&unused, 1, 4, 1);
				bool found = false;
				ConstantSlot slot;
				core::Name<core::CaseInsensitiveKey32> inputKey(inputName, 1);
				pddi->constants->Find(&slot, kind, &inputKey);
				if (!slot.IsValid())
				{
					while (reader->HasChunk())
					{
						unsigned int innerId = reader->BeginChunk();
						switch (innerId)
						{
						case 0x11051:
						{
							found = true;
							char value;
							reader->Read(&value, 1, 1, 1);
							inputs.SetBool(kind, inputKey, value != 0);
							break;
						}
						case 0x11010:
						{
							found = true;
							float value;
							reader->Read(&value, 1, 4, 1);
							inputs.SetFloat(kind, inputKey, value);
							break;
						}
						case 0x11011:
						{
							found = true;
							float value[2];
							reader->Read(value, 2, 4, 1);
							inputs.SetVector2(kind, inputKey, value);
							break;
						}
						case 0x11012:
						{
							found = true;
							float value[3];
							reader->Read(value, 3, 4, 1);
							inputs.SetVector3(kind, inputKey, value);
							break;
						}
						case 0x11013:
						{
							found = true;
							float value[4];
							reader->Read(value, 4, 4, 1);
							inputs.SetVector4(kind, inputKey, value);
							break;
						}
						case 0x11014:
						{
							found = true;
							float value[16];
							reader->Read(value, 16, 4, 1);
							inputs.SetMatrix(kind, inputKey, value);
							break;
						}
						case 0x1100F:
						{
							found = true;
							reader->Read(&first, 1, 4, 1);
							unsigned int e = first;
							unsigned int f = first;
							unsigned int third;
							reader->Read(&third, 1, 4, 1);
							unsigned int d = third;
							unsigned int c = third;
							unsigned int b = 1;
							unsigned int h = 0;
							if (reader->GetSize() > 8)
							{
								unsigned int mode;
								reader->Read(&mode, 1, 4, 1);
								if (mode == 0)
								{
									h = 1;
								}
								else if (mode == 2)
								{
									h = mode;
								}
							}
							if (reader->GetPosition() < reader->GetSize())
							{
								unsigned int extraA;
								reader->Read(&extraA, 1, 4, 1);
								f = extraA;
								unsigned int extraB;
								reader->Read(&extraB, 1, 4, 1);
								e = extraB;
							}
							unsigned int a = 1;
							while (reader->HasChunk())
							{
								if (reader->BeginChunk() == 0x11053)
								{
									int red;
									reader->Read(&red, 1, 4, 1);
									int green;
									reader->Read(&green, 1, 4, 1);
									int blue;
									reader->Read(&blue, 1, 4, 1);
									unsigned int alpha;
									reader->Read(&alpha, 1, 4, 1);
									unsigned int swizzle[4];
									swizzle[0] = 0;
									swizzle[1] = 1;
									swizzle[2] = 2;
									swizzle[3] = 3;
									c = swizzle[green];
									d = swizzle[red];
									b = swizzle[blue];
									a = alpha;
								}
								reader->EndChunk();
							}
							SamplerSetting sampler;
							sampler.a = a;
							sampler.b = b;
							sampler.c = c;
							sampler.d = d;
							sampler.e = e;
							sampler.f = f;
							sampler.g = first;
							sampler.h = h;
							sampler.unknown0 = 0;
							inputs.SetSampler(kind, inputKey, &sampler);
							break;
						}
						}
						reader->EndChunk();
					}
					if (!found)
					{
						inputs.SetDefault(kind, inputKey);
					}
				}
							break;
			}
			case 0x1100A:
			{
				PrimStreamParameters state;
				state.unknown0 = 0.5f;
				char passName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(passName, length, 1, 1);
					passName[length] = 0;
				}
				int value;
				reader->Read(&value, 1, 4, 1);
				state.blendMode = value;
				reader->Read(&value, 1, 4, 1);
				state.blendFactor = value;
				reader->Read(&value, 1, 4, 1);
				state.unknown4Bits10 = value;
				float number;
				reader->Read(&number, 1, 4, 1);
				state.flag0 = state.unknown4Bits10 != 0;
				state.unknown0 = number;
				char vertexProgram[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(vertexProgram, length, 1, 1);
					vertexProgram[length] = 0;
				}
				char pixelProgram[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(pixelProgram, length, 1, 1);
					pixelProgram[length] = 0;
				}
				while (reader->HasChunk())
				{
					if (reader->BeginChunk() == 0x11055)
					{
						int flag;
						reader->Read(&flag, 1, 4, 1);
						state.flag1 = flag != 0;
					}
					reader->EndChunk();
				}
				if (strcmp(shaderName, "prop_damage_2nm_vtx") == 0)
				{
					if (strcmp(passName, "zfill") == 0)
					{
						strcpy(vertexProgram, "prop_damage_2nm_vtx - lit_PR - Vertex Program");
					}
				}
				shaderTemplate->AddPass(passName, vertexProgram, pixelProgram, &state, 0);
							break;
			}
			}
			reader->EndChunk();
		}
		shaderTemplate->Finish(pddi, &inputs);
		*object = 0;
		*name = content::ObjectName((const char*)0, 1);
	}
#endif
}
