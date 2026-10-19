// pure3d::dxTexture, the Direct3D 9 texture of the pddi layer (unit around 0x1061C400 - 0x1061F200; the file name is
// guessed, no assert path survives).
#include <new>

#include "code/pure3d/pddi/dx9/dxtexture.h"

#include "code/content/loadmanager.h"
#include "code/core/thread.h"
#include "code/engine/display.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// 0x11276D48: the bytes of texture memory all the textures hold (name guess)
	extern int gTextureMemory;

	// The level records of the texture leave the level array through the pool manager (0x10624D10)
	void FreePooledTexture(IDirect3DTexture9** slot);

	int gCubeFaces[6] = { 0, 1, 2, 3, 4, 5 };

	int IsTextureFormatSupported(unsigned int format);

	// FUNCTION: ENGINE 0x1061C400
	dxTexture::dxTexture(IDirect3DDevice9* device)
		: surface(0), levelData(0), texture(0), defaultTexture(0), volumeTexture(0), cubeTexture(0), d3dFormat(0),
			lockLevel(-1), lockSlice(-1), locked(0), memory(0), unknown84(0), unknown88(0), unknown8C(0)
	{
	}

	// FUNCTION: ENGINE 0x1061CA00
	void dxTexture::Unknown1061CA00(bool stretched)
	{
		if (unknown84)
		{
			char supported = IsTextureFormatSupported(d3dFormat);
			if (supported == 0)
			{
				IDirect3DSurface9* level;
				texture->lpVtbl->GetSurfaceLevel(texture, 0, &level);
				unsigned int filter;
				if (stretched)
				{
					filter = (engine::gRenderDisplay->unknown78F != 0) + 1;
				}
				else
				{
					filter = 1;
				}
				gD3DDevice->lpVtbl->StretchRect(gD3DDevice, surface->surface, 0, level, 0, filter);
				level->Release();
			}
		}
	}

	// FUNCTION: ENGINE 0x1061CBE0
	dxTexture::~dxTexture()
	{
		if (unknown88 != 0)
		{
			ReleaseRef(&unknown88->unknown8C);
			ReleaseRef(&unknown88);
		}
		for (unsigned int i = 0; i < (unsigned int)description.levels; i++)
		{
			operator delete[](levelData[i].data);
			levelData[i].data = 0;
		}
		operator delete[](levelData);
		levelData = 0;
		if (texture != 0)
		{
			if (pool == 0)
			{
				FreePooledTexture(&texture);
			}
			else
			{
				texture->Release();
			}
			texture = 0;
		}
		ReleaseRef(&surface);
		ReleaseRef(&volumeTexture);
		ReleaseRef(&cubeTexture);
		ReleaseRef(&defaultTexture);
		gTextureMemory -= memory;
		if (gContext != 0)
		{
			int released = -memory;
			float value = (float)released;
			gContext->textureMemory = value + gContext->textureMemory;
		}
	}

	// FUNCTION: ENGINE 0x1061CD70
	bool dxTexture::Create(const TextureDescription* description)
	{
		if (!SetDescription(description))
		{
			return false;
		}
		int usage = 0;
		pool = D3DPOOL_MANAGED;
		if ((((unsigned char)(this->description.usage >> 1)) & 1) != 0)
		{
			char supported = IsTextureFormatSupported(d3dFormat);
			usage = (supported != 0) + 1;
			this->description.levels = 1;
			pool = D3DPOOL_DEFAULT;
		}
		BuildLevels(&this->description);
		if (gContext != 0)
		{
			gContext->textureMemory = (float)memory + gContext->textureMemory;
		}
		gTextureMemory += memory;
		switch (this->description.type)
		{
		case 3:
			gD3DDevice->lpVtbl->CreateVolumeTexture(gD3DDevice, this->description.width, this->description.height,
				this->description.depth, this->description.levels, 0, d3dFormat, pool, &volumeTexture, 0);
			return true;
		case 2:
			gD3DDevice->lpVtbl->CreateCubeTexture(gD3DDevice, this->description.width, this->description.levels, 0,
				d3dFormat, pool, &cubeTexture, 0);
			return true;
		case 1:
			if (pool == D3DPOOL_DEFAULT)
			{
				AssignRef(&surface, new dxSurface());
				if ((description->flags & 0x20) != 0 && engine::gRenderDisplay->GetUnknown28() != 0)
				{
					unknown84 = true;
					dxSurfaceLevel level;
					level.format = description->format;
					level.width = description->width;
					level.height = description->height;
					if (description->unknown34)
					{
						level.multiSampleType = engine::gRenderDisplay->GetUnknown28();
					}
					else
					{
						level.multiSampleType = 0;
					}
					surface->SetLevel(&level);
					if (usage != 2)
					{
						PoolAllocateTexture(this->description.width, this->description.height,
							this->description.levels, usage, d3dFormat, &texture, 0, 0.0f);
					}
				}
				else
				{
					PoolAllocateTexture(this->description.width, this->description.height, this->description.levels,
						usage, d3dFormat, &texture, &surface->surface, 0.0f);
					surface->SetSurface(surface->surface);
				}
			}
			else
			{
				gD3DDevice->lpVtbl->CreateTexture(gD3DDevice, this->description.width, this->description.height,
					this->description.levels, usage, d3dFormat, pool, &texture, 0);
				if (texture == 0 && content::gLoadManager->IsCurrentThread())
				{
					while (texture == 0)
					{
						gD3DDevice->lpVtbl->CreateTexture(gD3DDevice, this->description.width,
							this->description.height, this->description.levels, usage, d3dFormat, pool, &texture, 0);
						core::ThreadSleep(100);
					}
				}
			}
			break;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1061D010
	bool dxTexture::Create(const TextureDescription* description, const dxTexture* image)
	{
		if (!SetDescription(description))
		{
			return false;
		}
		if (image->description.format != this->description.format)
		{
			return false;
		}
		if (image->levelData[0].data->height * 2 != this->description.height)
		{
			return false;
		}
		if (image->levelData[0].data->width * 2 != this->description.width)
		{
			return false;
		}
		if (image->description.type != this->description.type)
		{
			return false;
		}
		if (this->description.usage == 2)
		{
			return false;
		}
		if (this->description.levels != 1)
		{
			return false;
		}
		this->description.levels = image->description.levels + 1;
		BuildLevels(&this->description);
		if (gContext != 0)
		{
			gContext->textureMemory = (float)memory + gContext->textureMemory;
		}
		gTextureMemory += memory;
		switch (this->description.type)
		{
		case 3:
			gD3DDevice->lpVtbl->CreateVolumeTexture(gD3DDevice, this->description.width, this->description.height,
				this->description.depth, this->description.levels, 0, d3dFormat, D3DPOOL_MANAGED, &volumeTexture, 0);
			break;
		case 2:
			gD3DDevice->lpVtbl->CreateCubeTexture(gD3DDevice, this->description.width, this->description.levels, 0,
				d3dFormat, D3DPOOL_MANAGED, &cubeTexture, 0);
			break;
		case 1:
			gD3DDevice->lpVtbl->CreateTexture(gD3DDevice, this->description.width, this->description.height,
				this->description.levels, 0, d3dFormat, D3DPOOL_MANAGED, &texture, 0);
			if (texture == 0 && content::gLoadManager->IsCurrentThread())
			{
				while (texture == 0)
				{
					gD3DDevice->lpVtbl->CreateTexture(gD3DDevice, this->description.width,
						this->description.height, this->description.levels, 0, d3dFormat, D3DPOOL_MANAGED, &texture, 0);
					core::ThreadSleep(100);
				}
			}
			break;
		default:
			return false;
		}
		bool compressed = IsCompressedFormat(this->description.format);
		switch (this->description.type)
		{
		case 2:
			{
				IDirect3DCubeTexture9* source = image->cubeTexture;
				for (unsigned int level = 1; level < this->description.levels; level++)
				{
					for (int face = 0; face < 6; face++)
					{
						D3DLOCKED_RECT sourceRect;
						D3DLOCKED_RECT destRect;
						source->lpVtbl->LockRect(source, gCubeFaces[face], level - 1, &sourceRect, 0,
							D3DLOCK_READONLY);
						cubeTexture->lpVtbl->LockRect(cubeTexture, gCubeFaces[face], level, &destRect, 0, 0);
						CopyLevelRows(destRect.pBits, sourceRect.pBits, sourceRect.Pitch,
							levelData[level].data[face].height, compressed);
						source->lpVtbl->UnlockRect(source, gCubeFaces[face], level - 1);
						cubeTexture->lpVtbl->UnlockRect(cubeTexture, gCubeFaces[face], level);
					}
				}
			}
			break;
		case 1:
			{
				IDirect3DTexture9* source = image->texture;
				for (unsigned int level = 1; level < this->description.levels; level++)
				{
					D3DLOCKED_RECT sourceRect;
					D3DLOCKED_RECT destRect;
					source->lpVtbl->LockRect(source, level - 1, &sourceRect, 0, D3DLOCK_READONLY);
					texture->lpVtbl->LockRect(texture, level, &destRect, 0, 0);
					CopyLevelRows(destRect.pBits, sourceRect.pBits, sourceRect.Pitch,
						levelData[level].data->height, compressed);
					source->lpVtbl->UnlockRect(source, level - 1);
					texture->lpVtbl->UnlockRect(texture, level);
				}
			}
			break;
		case 3:
			return false;
		default:
			return false;
		}
		AssignRef(&unknown88, const_cast<dxTexture*>(image));
		const_cast<dxTexture*>(image)->unknown8C = this;
		return true;
	}

	// Whether the usage allows the lock and the level and slice exist (the engine's checks before its body)
	inline bool CanLock(const dxTexture* texture, unsigned int flags, unsigned int level, unsigned int slice)
	{
		if (((flags & 1) != 0 && (~texture->description.usage & 1) != 0) ||
			((flags & 2) != 0 && (texture->description.usage & 2) != 0))
		{
			return false;
		}
		return level < (unsigned int)texture->description.levels &&
			slice < (unsigned int)texture->levelData[level].count;
	}

	// FUNCTION: ENGINE 0x1061C600
	// EQUIVALENT: register allocation, 9.7 %: the engine keeps `level` in edx and reads it again from the argument
	// slot after the calls, this compiler gives it ebx, which moves the push of ebx in front of the checks and shifts
	// the whole body. Both bodies make the same device calls with the same arguments and leave the same description.
	// The checks as an inline returning a bool (CanLock) give the engine's blocks: the early return for a locked
	// texture, one shared `return false` for the failed checks and the body behind them; the surface pointers are
	// left uninitialised and the system-memory copy is reached through a pointer, as in the engine. A copy of
	// `level` after the checks, the plain arm first, the bookkeeping stores moved up and the members written
	// directly do not take ebx away from `level`; nor do a barrier after any statement (14.6 % at best) or the
	// orders of the box's and of the lock's stores.
	bool dxTexture::Lock(TextureLock* lock, unsigned int flags, unsigned int level, unsigned int slice)
	{
		if (locked)
		{
			return false;
		}
		unsigned int readOnly = flags & 1;
		if (!CanLock(this, flags, level, slice))
		{
			return false;
		}
		TextureLevelData* levelData_ = &levelData[level].data[slice];
		switch (description.type)
		{
		case 3:
			{
				TextureBox box;
				box.left = 0;
				box.top = 0;
				box.bottom = levelData_->height;
				box.right = levelData_->width;
				box.front = slice;
				box.back = slice + 1;
				volumeTexture->lpVtbl->LockBox(volumeTexture, level, &lockBox, &box, readOnly << 4);
			}
			break;
		case 2:
			cubeTexture->lpVtbl->LockRect(cubeTexture, gCubeFaces[slice], level, &lockRect, 0, readOnly << 4);
			break;
		case 1:
			if ((description.usage & 2) != 0)
			{
				IDirect3DTexture9** system = &defaultTexture;
				if (*system == 0)
				{
					gD3DDevice->lpVtbl->CreateTexture(gD3DDevice, description.width, description.height,
						description.levels, 0, d3dFormat, D3DPOOL_SYSTEMMEM, system, 0);
				}
				IDirect3DSurface9* defaultSurface;
				IDirect3DSurface9* textureSurface;
				(*system)->lpVtbl->GetSurfaceLevel(*system, 0, &defaultSurface);
				texture->lpVtbl->GetSurfaceLevel(texture, 0, &textureSurface);
				gD3DDevice->lpVtbl->GetRenderTargetData(gD3DDevice, textureSurface, defaultSurface);
				textureSurface->lpVtbl->Release(textureSurface);
				defaultSurface->lpVtbl->Release(defaultSurface);
				(*system)->lpVtbl->LockRect(*system, level, &lockRect, 0, readOnly << 4);
			}
			else
			{
				texture->lpVtbl->LockRect(texture, level, &lockRect, 0, readOnly << 4);
			}
			break;
		}
		lock->slice = slice;
		lock->width = levelData_->width;
		lock->height = levelData_->height;
		lock->format = description.format;
		lock->size = levelData_->size;
		lock->unknown1C = 1;
		if (description.type == 3)
		{
			if ((description.flags & 2) != 0)
			{
				lock->pitch = lockBox.RowPitch;
				lock->offset = (int)lockBox.pBits;
			}
			else
			{
				lock->pitch = -lockBox.RowPitch;
				lock->offset = (levelData_->height - 1) * lockBox.RowPitch + (int)lockBox.pBits;
			}
		}
		else if ((description.flags & 2) != 0)
		{
			lock->pitch = lockRect.Pitch;
			lock->offset = (int)lockRect.pBits;
		}
		else if (description.type == 1)
		{
			lock->pitch = -lockRect.Pitch;
			lock->offset = (levelData_->height - 1) * lockRect.Pitch + (int)lockRect.pBits;
		}
		lockLevel = level;
		lockSlice = slice;
		locked = true;
		return true;
	}


	// Holds a new texture in one of the default texture slots (another copy of AssignRef, called by the default
	// textures' unit; name guess)
	// FUNCTION: ENGINE 0x1061CBB0
	void AssignTextureSlot(dxTexture** slot, dxTexture* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (*slot != 0)
		{
			(*slot)->Release();
		}
		*slot = value;
	}

	// FUNCTION: ENGINE 0x1061C360
	// The formats a texture may be created with (the two four-character ones are "DF16" and "DF24", the depth
	// formats; the single bytes are the back end's own format codes). It is an int (the engine's code sets the whole
	// register), while its callers test its low byte, so they keep the answer in a char.
	// Declared inline so that its callers are not given its register use (the engine's callers do not know it)
	inline int IsTextureFormatSupported(unsigned int format)
	{
		if (format == 0x49 || format == 0x50 || format == 0x46 || format == 0x4F || format == 0x53 ||
			format == 0x4D || format == 0x4B || format == 0x52 || format == 0x47 || format == 0x34324644 ||
			format == 0x36314644)
		{
			return true;
		}
		return false;
	}
}
