// pure3d::FrameControllerLoader, the frame controller handlers and the old frame controller loader (unit around
// 0x10777AE0 - 0x10779700; the file name is a guess). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/framecontroller.h"
#include "code/pure3d/loaders/drawableloaders.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10777AF0
	bool DefaultFrameControllerHandler::IsSupported(unsigned int chunkId)
	{
		switch (chunkId)
		{
			case 0x4D534E43:
			case 0x584554:
			case 0x475142:
			case 0x4D4143:
			case 0x505845:
			case 0x584645:
			case 0x44414853:
			case 0x4554494C:
			case 0x53495650:
			case 0x4E474552:
			case 0x4E525450:
			case 0x4E525453:
			case 0x53495653:
			case 0x53595350:
			case 0x58545256:
				return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10777BC0
	FrameControllerHandler* FrameControllerLoader::FindHandler(unsigned int chunkId)
	{
		for (unsigned int i = 0; i < handlerCount; i++)
		{
			if (handlers[i]->IsSupported(chunkId) == true)
			{
				return handlers[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10777C20
	bool OldFrameControllerLoader::IsSupported(unsigned int chunkId)
	{
		switch (chunkId)
		{
			case 0x584554:
			case 0x475142:
			case 0x4D4143:
			case 0x505845:
			case 0x584645:
			case 0x44414853:
			case 0x4554494C:
			case 0x53495650:
			case 0x4E525450:
			case 0x4E525453:
			case 0x53495653:
			case 0x58545256:
				return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10778430
	void FrameControllerLoader::AddHandler(FrameControllerHandler* handler)
	{
		if (handler != 0 && handlerCount < 4)
		{
			core::RefAssign(handlers[handlerCount], handler);
			handlerCount++;
		}
	}

	// FUNCTION: ENGINE 0x10778460
	// NONMATCHING: the engine keeps the loader in a slot that the name temporary shares and has a 4-byte larger frame (19.1 %)
#ifdef NONMATCHING
	void FrameControllerLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		unsigned int version;
		reader->Read(&version, 1, 4, 1);
		unsigned char lengthByte;
		char controllerName[0x100];
		reader->Read(&lengthByte, 1, 1, 1);
		unsigned int length = lengthByte;
		reader->Read(controllerName, length, 1, 1);
		controllerName[length] = 0;
		unsigned int chunkId;
		reader->Read(&chunkId, 1, 4, 1);
		FrameController* controller = 0;
		for (unsigned int i = 0; i < handlerCount; i++)
		{
			if (handlers[i]->IsSupported(chunkId) == true)
			{
				controller = handlers[i]->Load(controllerName, chunkId, version, reader, inventory);
			}
		}
		if (controller != 0)
		{
			controller->AddRef();
			*object = controller;
			*name = content::ObjectName(controllerName, 1);
		}
		else
		{
			*object = 0;
			*name = content::ObjectName((const char*)0, 1);
		}
	}
#endif

	// FUNCTION: ENGINE 0x107785A0
	// NONMATCHING: register allocation and a 4-byte smaller frame in the engine (17.5 %)
#ifdef NONMATCHING
	void OldFrameControllerLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		unsigned int chunkId;
		reader->Read(&chunkId, 1, 4, 1);
		unsigned char lengthByte;
		char controllerName[0x100];
		reader->Read(&lengthByte, 1, 1, 1);
		unsigned int length = lengthByte;
		reader->Read(controllerName, length, 1, 1);
		controllerName[length] = 0;
		reader->Read(&chunkId, 1, 4, 1);
		FrameController* controller = 0;
		if (IsSupported(chunkId) == true)
		{
			controller = Load(controllerName, chunkId, reader, inventory);
		}
		controller->AddRef();
		*object = controller;
		*name = content::ObjectName(controllerName, 1);
	}
#endif
}
