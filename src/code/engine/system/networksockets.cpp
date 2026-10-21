// CFLAGS: !/arch
// The network socket layer: a Winsock wrapper that hands out small integer handles, with a message window that answers
// the asynchronous name lookup (the code sits in 0x1093E5D0 - 0x1093FD20; no assert path, file and function names
// guessed). The Windows SDK headers are not part of the toolchain, so the few Winsock and Win32 declarations the
// layer needs are written out here.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "code/core/heap.h"
#include "code/core/strings.h"

namespace core
{
	// 0x1063B990: core::SNPrintf as this layer calls it (the engine returns the count; name guess)
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

// The slots are imported by name; link.exe looks for the decorated stdcall name, the import library has the plain one
#pragma comment(linker, "/alternatename:__imp__getpeername@12=__imp__getpeername")
#pragma comment(linker, "/alternatename:__imp__getsockname@12=__imp__getsockname")
#pragma comment(linker, "/alternatename:__imp__htonl@4=__imp__htonl")
#pragma comment(linker, "/alternatename:__imp__htons@4=__imp__htons")
#pragma comment(linker, "/alternatename:__imp__ntohl@4=__imp__ntohl")
#pragma comment(linker, "/alternatename:__imp__ntohs@4=__imp__ntohs")
#pragma comment(linker, "/alternatename:__imp__WSAAsyncGetHostByName@20=__imp__WSAAsyncGetHostByName")
#pragma comment(linker, "/alternatename:__imp__WSACancelAsyncRequest@4=__imp__WSACancelAsyncRequest")
#pragma comment(linker, "/alternatename:__imp__Sleep@4=__imp__Sleep")
#pragma comment(linker, "/alternatename:__imp__select@20=__imp__select")
#pragma comment(linker, "/alternatename:__imp____WSAFDIsSet@8=__imp____WSAFDIsSet")
#pragma comment(linker, "/alternatename:__imp__getsockopt@20=__imp__getsockopt")
#pragma comment(linker, "/alternatename:__imp__setsockopt@20=__imp__setsockopt")
#pragma comment(linker, "/alternatename:__imp__ioctlsocket@12=__imp__ioctlsocket")
#pragma comment(linker, "/alternatename:__imp__accept@12=__imp__accept")
#pragma comment(linker, "/alternatename:__imp__socket@12=__imp__socket")
#pragma comment(linker, "/alternatename:__imp__closesocket@4=__imp__closesocket")
#pragma comment(linker, "/alternatename:__imp__WSAStartup@8=__imp__WSAStartup")
#pragma comment(linker, "/alternatename:__imp__WSACleanup@0=__imp__WSACleanup")
#pragma comment(linker, "/alternatename:__imp__GetModuleFileNameA@12=__imp__GetModuleFileNameA")
#pragma comment(linker, "/alternatename:__imp__GetModuleHandleA@4=__imp__GetModuleHandleA")
#pragma comment(linker, "/alternatename:__imp__RegisterClassExA@4=__imp__RegisterClassExA")
#pragma comment(linker, "/alternatename:__imp__CreateWindowExA@48=__imp__CreateWindowExA")
#pragma comment(linker, "/alternatename:__imp__DestroyWindow@4=__imp__DestroyWindow")
#pragma comment(linker, "/alternatename:__imp__UnregisterClassA@8=__imp__UnregisterClassA")
#pragma comment(linker, "/alternatename:__imp__DefWindowProcA@16=__imp__DefWindowProcA")
#pragma comment(linker, "/alternatename:__imp__shutdown@8=__imp__shutdown")
#pragma comment(linker, "/alternatename:__imp__bind@12=__imp__bind")
#pragma comment(linker, "/alternatename:__imp__connect@12=__imp__connect")
#pragma comment(linker, "/alternatename:__imp__listen@8=__imp__listen")
#pragma comment(linker, "/alternatename:__imp__WSAGetLastError@0=__imp__WSAGetLastError")
#pragma comment(linker, "/alternatename:__imp__recvfrom@24=__imp__recvfrom")
#pragma comment(linker, "/alternatename:__imp__sendto@24=__imp__sendto")

namespace
{
	typedef unsigned int SOCKET;

	struct sockaddr
	{
		unsigned short family;
		unsigned short port;
		unsigned int address;
		char zero[8];
	};

	struct fd_set
	{
		unsigned int fd_count;
		SOCKET fd_array[64];
	};

	struct timeval
	{
		long tv_sec;
		long tv_usec;
	};

	typedef long (__stdcall *WindowProcedure)(void* window, unsigned int message, unsigned int wparam, long lparam);

	// WNDCLASSEXA
	struct WindowClass
	{
		unsigned int size;
		unsigned int style;
		WindowProcedure procedure;
		int classExtra;
		int windowExtra;
		void* instance;
		void* icon;
		void* cursor;
		void* background;
		const char* menuName;
		const char* className;
		void* smallIcon;
	};

	// The hostent a name lookup fills in
	struct HostEntry
	{
		char* name;
		char** aliases;
		short addressType;
		short length;
		unsigned char** addresses;
	};
}

extern "C"
{
	__declspec(dllimport) int __stdcall getpeername(SOCKET s, sockaddr* name, int* namelen);
	__declspec(dllimport) int __stdcall getsockname(SOCKET s, sockaddr* name, int* namelen);
	__declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
	__declspec(dllimport) unsigned short __stdcall htons(unsigned short hostshort);
	__declspec(dllimport) unsigned long __stdcall ntohl(unsigned long netlong);
	__declspec(dllimport) unsigned short __stdcall ntohs(unsigned short netshort);
	__declspec(dllimport) void* __stdcall WSAAsyncGetHostByName(void* window, unsigned int message, const char* name, char* buffer, int length);
	__declspec(dllimport) int __stdcall WSACancelAsyncRequest(void* request);
	__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
	__declspec(dllimport) int __stdcall select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout);
	__declspec(dllimport) int __stdcall __WSAFDIsSet(SOCKET s, fd_set* set);
	__declspec(dllimport) int __stdcall getsockopt(SOCKET s, int level, int optname, char* optval, int* optlen);
	__declspec(dllimport) int __stdcall setsockopt(SOCKET s, int level, int optname, const char* optval, int optlen);
	__declspec(dllimport) int __stdcall ioctlsocket(SOCKET s, long cmd, unsigned long* argp);
	__declspec(dllimport) SOCKET __stdcall accept(SOCKET s, sockaddr* addr, int* addrlen);
	__declspec(dllimport) SOCKET __stdcall socket(int af, int type, int protocol);
	__declspec(dllimport) int __stdcall closesocket(SOCKET s);
	__declspec(dllimport) int __stdcall WSAStartup(unsigned short version, void* data);
	__declspec(dllimport) int __stdcall WSACleanup();
	__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void* module, char* fileName, unsigned long size);
	__declspec(dllimport) void* __stdcall GetModuleHandleA(const char* moduleName);
	__declspec(dllimport) unsigned short __stdcall RegisterClassExA(const WindowClass* windowClass);
	__declspec(dllimport) void* __stdcall CreateWindowExA(unsigned long exStyle, const char* className, const char* windowName, unsigned long style, int x, int y, int width, int height, void* parent, void* menu, void* instance, void* param);
	__declspec(dllimport) int __stdcall DestroyWindow(void* window);
	__declspec(dllimport) int __stdcall UnregisterClassA(const char* className, void* instance);
	__declspec(dllimport) long __stdcall DefWindowProcA(void* window, unsigned int message, unsigned int wparam, long lparam);
	__declspec(dllimport) int __stdcall shutdown(SOCKET s, int how);
	__declspec(dllimport) int __stdcall bind(SOCKET s, const sockaddr* name, int namelen);
	__declspec(dllimport) int __stdcall connect(SOCKET s, const sockaddr* name, int namelen);
	__declspec(dllimport) int __stdcall listen(SOCKET s, int backlog);
	__declspec(dllimport) int __stdcall WSAGetLastError();
	__declspec(dllimport) int __stdcall recvfrom(SOCKET s, char* buf, int len, int flags, sockaddr* from, int* fromlen);
	__declspec(dllimport) int __stdcall sendto(SOCKET s, const char* buf, int len, int flags, const sockaddr* to, int tolen);
}

// FD_SET of the Winsock headers: the socket once, up to 64 of them
#define FD_SET(fd, set) do { 	unsigned int __i; 	for (__i = 0; __i < ((fd_set*)(set))->fd_count; __i++) 	{ 		if (((fd_set*)(set))->fd_array[__i] == (fd)) 		{ 			break; 		} 	} 	if (__i == ((fd_set*)(set))->fd_count) 	{ 		if (((fd_set*)(set))->fd_count < 64) 		{ 			((fd_set*)(set))->fd_array[__i] = (fd); 			((fd_set*)(set))->fd_count++; 		} 	} } while (0)

namespace engine
{
	namespace network
	{
		// The table of sockets: the entries are handed out as small integers (the index)
		struct SocketEntry
		{
			SOCKET handle;  // +0x0
			char unknown4;  // +0x4
			char open;  // +0x5
			char pad[2];
		};

		// The free entries, linked through their first word
		struct FreeList
		{
			// 0x1093F450: takes the first free entry out
			SocketEntry* Pop()
			{
				SocketEntry* entry = head;
				if (entry != 0)
				{
					head = *(SocketEntry**)entry;
				}
				return entry;
			}

			// 0x1093F420: links the entries of a block, the last one in front
			void Fill(SocketEntry* entries, unsigned int count);

			// 0x1093F460: puts an entry in front
			void Push(SocketEntry* entry)
			{
				*(SocketEntry**)entry = head;
				head = entry;
			}

			SocketEntry* head;
		};

		struct SocketTable
		{
			SocketEntry* entries;  // +0x0
			int count;  // +0x4
			int heap;  // +0x8
			FreeList freeList;  // +0xC
			void* instance;  // +0x10
			void* window;  // +0x14
			void* lookup;  // +0x18
			int lookupResult;  // +0x1C
			HostEntry host;  // +0x20: the start of the buffer the lookup fills
			char hostBuffer[0x400 - sizeof(HostEntry)];
			int* lookupOutput;  // +0x420
		};

		// 0x1131E608 (symbols.txt): the layer's state, null before it is started
		extern SocketTable* gSockets;
		// 0x1131E60C / 0x1131E610 / 0x1131E614 (symbols.txt): what the layer was started with and whether it runs
		extern int gMaxSockets;
		extern int gSocketHeap;
		extern bool gStarted;
		// 0x111EBB74 (symbols.txt): the name of the window class the layer registers
		extern const char* gWindowClassName;

		// 0x1093E600: the entry of a handle, or null for a handle out of range
		static SocketEntry* GetEntry(int handle)
		{
			if (handle >= 0 && handle < gSockets->count)
			{
				return gSockets->entries + handle;
			}
			return 0;
		}

		// 0x1093E620: the layer's error code for a Winsock error number
		static int MapError(int error)
		{
			switch (error)
			{
			case 0x2728:
				return -4;
			case 0x2747:
				return -8;
			case 0x2733:
			case 0x2734:
				return -6;
			case 0x2726:
			case 0x2739:
			case 0x273B:
			case 0x273C:
			case 0x273F:
				return -2;
			case 0x2742:
			case 0x2744:
				return -3;
			}
			return -128;
		}

		// 0x1093E6A0: the layer's error code for the last Winsock error
		static int LastError()
		{
			return MapError(WSAGetLastError());
		}

		// The address the layer's callers see: a length, the family, the port and the four bytes of the address
		struct NetAddress
		{
			unsigned char length;  // +0x0
			unsigned char family;  // +0x1
			unsigned short port;  // +0x2
			unsigned int address;  // +0x4
			unsigned int unknown8;
			unsigned int unknownC;
		};

		// 0x1093E5D0: claims an entry (name guess)
		static SocketEntry* ClaimEntry(SocketEntry* entry)
		{
			entry->open = 1;
			entry->unknown4 = 0;
			entry->handle = 0xFFFFFFFF;
			return entry;
		}

		// 0x1093E5E0: gives an entry back
		static SocketEntry* ReleaseEntry(SocketEntry* entry)
		{
			entry->open = 0;
			return entry;
		}

		// 0x1093E5F0: the handle of an entry
		static int GetHandle(SocketEntry* entry)
		{
			return entry - gSockets->entries;
		}

		// 0x1093E6B0: the Winsock address family of the layer's (only the Internet family)
		static int MapFamily(int family, int* mapped)
		{
			if (family == 2)
			{
				*mapped = 2;
				return 0;
			}
			return -2;
		}

		// 0x1093E6D0: the Winsock socket type (stream and datagram)
		static int MapType(int type, int* mapped)
		{
			if (type == 1)
			{
				*mapped = type;
				return 0;
			}
			if (type == 2)
			{
				*mapped = type;
				return 0;
			}
			return -2;
		}

		// 0x1093E6F0: the Winsock protocol (only the default)
		static int MapProtocol(int protocol, int* mapped)
		{
			if (protocol == 0)
			{
				*mapped = 0;
				return 0;
			}
			return -2;
		}

		// 0x1093E710: the Winsock address of a layer address
		static int ToSockaddr(sockaddr* to, const NetAddress* from)
		{
			memset(to, 0, sizeof(sockaddr));
			if (from->family == 2 && from->length >= 0x10)
			{
				to->family = 2;
				to->address = from->address;
				to->port = from->port;
				return 0;
			}
			return -2;
		}

		// 0x1093E750: the layer address of a Winsock address
		static int FromSockaddr(NetAddress* to, const sockaddr* from, unsigned int length)
		{
			memset(to, 0, sizeof(NetAddress));
			if (from->family == 2 && length >= 0x10)
			{
				to->length = 0x10;
				to->family = 2;
				to->address = from->address;
				to->port = from->port;
				return 0;
			}
			return -2;
		}

		// 0x1093E790: the Winsock flags of the layer's (none are supported)
		static int MapFlags(int flags, int* mapped)
		{
			if (flags != 0)
			{
				return -2;
			}
			*mapped = 0;
			return 0;
		}

		// 0x1093E7B0: the addresses of a finished lookup into the caller's result (a count, then up to eight addresses)
		static void CopyLookupResult()
		{
			SocketTable* table = gSockets;
			char** addresses = (char**)table->host.addresses;
			*table->lookupOutput = 0;
			for (unsigned int offset = 0; offset < 0x20; offset += 4)
			{
				unsigned int* address = *(unsigned int**)((char*)addresses + offset);
				if (address == 0)
				{
					return;
				}
				*(unsigned int*)((char*)table->lookupOutput + 4 + offset) = *address;
				*table->lookupOutput = *table->lookupOutput + 1;
			}
		}

		// FUNCTION: ENGINE 0x1093E800
		long __stdcall WindowProcedure(void* window, unsigned int message, unsigned int wparam, long lparam)
		{
			if (message != 0x465)
			{
				return DefWindowProcA(window, message, wparam, lparam);
			}
			SocketTable* table = gSockets;
			if (wparam == (unsigned int)table->lookup)
			{
				if ((unsigned short)((unsigned int)lparam >> 16) == 0)
				{
					table->lookupResult = 0;
					CopyLookupResult();
				}
				else
				{
					table->lookupResult = -10;
				}
				table->lookupOutput = 0;
				table->lookup = 0;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093E860
		int Shutdown(int handle, int how)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			int mapped;
			if (how == 0)
			{
				mapped = 0;
			}
			else if (how == 1)
			{
				mapped = 1;
			}
			else if (how == 2)
			{
				mapped = 2;
			}
			if (shutdown(entry->handle, mapped) == -1)
			{
				return LastError();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093E8B0
		int Bind(int handle, const NetAddress* address)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			sockaddr native;
			int result = ToSockaddr(&native, address);
			if (result < 0)
			{
				return result;
			}
			if (bind(entry->handle, &native, 0x10) == -1)
			{
				return LastError();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093E910
		int Connect(int handle, const NetAddress* address)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			sockaddr native;
			int result = ToSockaddr(&native, address);
			if (result < 0)
			{
				return result;
			}
			if (connect(entry->handle, &native, 0x10) == -1)
			{
				return LastError();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093E970
		int Listen(int handle, int backlog)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			if (backlog <= 0)
			{
				backlog = 1;
			}
			if (listen(entry->handle, backlog) == -1)
			{
				return LastError();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093E9B0
		// EQUIVALENT: scheduling; the engine moves the source address into edx after it has formed the address of the result, ours before; every other instruction is the engine's
		int Receive(int handle, char* buffer, int length, int flags, NetAddress* from, unsigned char fromSize)
		{
			sockaddr* nativeFrom = 0;
			int nativeLength = 0;
			sockaddr native;
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			int nativeFlags;
			int result = MapFlags(flags, &nativeFlags);
			if (result < 0)
			{
				return result;
			}
			if (from != 0 && fromSize > 0)
			{
				nativeLength = 0x10;
				nativeFrom = &native;
			}
			result = recvfrom(entry->handle, buffer, length, nativeFlags, nativeFrom, &nativeLength);
			if (result == -1)
			{
				int error = WSAGetLastError();
				if (error == 0x2738)
				{
					result = length;
				}
				else
				{
					return MapError(error);
				}
			}
			if (result == 0)
			{
				return -3;
			}
			if (from != 0 && fromSize > 0)
			{
				NetAddress address;
				int converted = FromSockaddr(&address, nativeFrom, nativeLength);
				if (converted < 0)
				{
					return converted;
				}
				unsigned int size = fromSize <= address.length ? fromSize : address.length;
				memcpy(from, &address, size);
				from->length = size;
			}
			return result;
		}

		// FUNCTION: ENGINE 0x1093EAB0
		int Send(int handle, const char* buffer, int length, int flags, const NetAddress* to)
		{
			sockaddr* nativeTo = 0;
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			int nativeFlags;
			int result = MapFlags(flags, &nativeFlags);
			if (result < 0)
			{
				return result;
			}
			sockaddr native;
			if (to != 0)
			{
				result = ToSockaddr(&native, to);
				if (result < 0)
				{
					return result;
				}
				nativeTo = &native;
			}
			result = sendto(entry->handle, buffer, length, nativeFlags, nativeTo, 0x10);
			if (result == -1)
			{
				return LastError();
			}
			return result;
		}

		// FUNCTION: ENGINE 0x1093F100
		// EQUIVALENT: scheduling; the engine loads the address of the result before the address of the source for the conversion call, ours the other way round; every other instruction is the engine's
		int GetPeerName(int handle, NetAddress* address, unsigned char size)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			int length = 0x10;
			sockaddr native;
			if (getpeername(entry->handle, &native, &length) == -1)
			{
				return LastError();
			}
			if (address != 0 && size >0)
			{
				NetAddress converted;
				int result = FromSockaddr(&converted, &native, length);
				if (result < 0)
				{
					return result;
				}
				unsigned int count = size <= converted.length ? size : converted.length;
				memcpy(address, &converted, count);
				address->length = count;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093F1A0
		// EQUIVALENT: scheduling; the engine loads the address of the result before the address of the source for the conversion call, ours the other way round; every other instruction is the engine's
		int GetSocketName(int handle, NetAddress* address, unsigned char size)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			int length = 0x10;
			sockaddr native;
			if (getsockname(entry->handle, &native, &length) == -1)
			{
				return LastError();
			}
			if (address != 0 && size >0)
			{
				NetAddress converted;
				int result = FromSockaddr(&converted, &native, length);
				if (result < 0)
				{
					return result;
				}
				unsigned int count = size <= converted.length ? size : converted.length;
				memcpy(address, &converted, count);
				address->length = count;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1093F240
		unsigned long HostToNetworkLong(unsigned long value)
		{
			return htonl(value);
		}

		// FUNCTION: ENGINE 0x1093F250
		unsigned short HostToNetworkShort(unsigned short value)
		{
			return htons(value);
		}

		// FUNCTION: ENGINE 0x1093F260
		unsigned long NetworkToHostLong(unsigned long value)
		{
			return ntohl(value);
		}

		// FUNCTION: ENGINE 0x1093F270
		unsigned short NetworkToHostShort(unsigned short value)
		{
			return ntohs(value);
		}

		// FUNCTION: ENGINE 0x1093F280
		int ParseAddress(const char* text, unsigned int* address)
		{
			if (text == 0)
			{
				return 0;
			}
			unsigned int first;
			unsigned int second;
			unsigned int third;
			unsigned int fourth;
			if (sscanf_s(text, "%d.%d.%d.%d", &first, &second, &third, &fourth) == 4 && first <= 0xFF && second <= 0xFF
				&& third <= 0xFF && fourth <= 0xFF)
			{
				if (address != 0)
				{
					*address = ((((fourth & 0xFF) << 8 | (third & 0xFF)) << 8 | (second & 0xFF)) << 8) | (first & 0xFF);
				}
				return 0;
			}
			return -2;
		}

		// FUNCTION: ENGINE 0x1093F320
		int FormatAddress(unsigned int address, char* text)
		{
			if (text == 0)
			{
				return -2;
			}
			return core::SNPrintfCount(text, 0x10, "%d.%d.%d.%d", address & 0xFF, (address >> 8) & 0xFF,
				(address >> 16) & 0xFF, address >> 24);
		}

		// FUNCTION: ENGINE 0x1093F360
		int StartLookup(const char* name, int* result)
		{
			if (result == 0)
			{
				return -2;
			}
			if (gSockets->lookup != 0)
			{
				return -9;
			}
			void* request = WSAAsyncGetHostByName(gSockets->window, 0x465, name, (char*)&gSockets->host, 0x400);
			SocketTable* table = gSockets;
			table->lookup = request;
			if (request == 0)
			{
				return -10;
			}
			table->lookupOutput = result;
			return 0;
		}

		// FUNCTION: ENGINE 0x1093F3C0
		int GetLookupResult()
		{
			if (gSockets->lookup != 0)
			{
				return -6;
			}
			return gSockets->lookupResult;
		}

		// FUNCTION: ENGINE 0x1093F3E0
		int CancelLookup()
		{
			void* request = gSockets->lookup;
			if (request != 0)
			{
				WSACancelAsyncRequest(request);
				while (gSockets->lookup != 0)
				{
					Sleep(1);
				}
				return 0;
			}
			return -11;
		}

		// 0x1093F470: takes a free entry and claims it
		static SocketEntry* AllocEntry()
		{
			SocketEntry* entry = gSockets->freeList.Pop();
			if (entry != 0)
			{
				return ClaimEntry(entry);
			}
			return entry;
		}

		// 0x1093F490: gives an entry back to the free list
		static void FreeEntry(SocketEntry* entry)
		{
			gSockets->freeList.Push(ReleaseEntry(entry));
		}

		// FUNCTION: ENGINE 0x1093F420
		void FreeList::Fill(SocketEntry* entries, unsigned int count)
		{
			head = 0;
			for (; count > 0; count--)
			{
				*(SocketEntry**)entries = head;
				head = entries;
				entries++;
			}
		}

		// FUNCTION: ENGINE 0x1093F4B0
		bool Initialize(int count, int heap)
		{
			gSockets = (SocketTable*)core::HeapAlloc(heap, 0x424);
			SocketEntry* entries = (SocketEntry*)core::HeapAlloc(heap, count * 8);
			SocketTable* table = gSockets;
			table->entries = entries;
			table->count = count;
			table->heap = heap;
			for (unsigned int index = 0; index < (unsigned int)table->count; index++)
			{
				table->entries[index].open = 0;
			}
			table->freeList.Fill(table->entries, table->count);
			char path[0x100];
			GetModuleFileNameA(0, path, 0x100);
			void** instance = &gSockets->instance;
			*instance = GetModuleHandleA(path);
			WindowClass windowClass;
			windowClass.size = sizeof(WindowClass);
			windowClass.style = 0;
			windowClass.procedure = WindowProcedure;
			windowClass.classExtra = 0;
			windowClass.windowExtra = 4;
			windowClass.instance = *instance;
			windowClass.icon = 0;
			windowClass.cursor = 0;
			windowClass.background = 0;
			windowClass.menuName = 0;
			windowClass.className = gWindowClassName;
			windowClass.smallIcon = 0;
			RegisterClassExA(&windowClass);
			void* window = CreateWindowExA(4, gWindowClassName, "", 0x80000000, 0, 0, 0, 0, 0, 0, gSockets->instance, 0);
			table = gSockets;
			table->window = window;
			table->lookup = 0;
			table->lookupResult = 0;
			return true;
		}

		// FUNCTION: ENGINE 0x1093F5E0
		bool Destroy()
		{
			CancelLookup();
			DestroyWindow(gSockets->window);
			UnregisterClassA(gWindowClassName, gSockets->instance);
			core::HeapFree(gSockets->heap, gSockets->entries);
			core::HeapFree(gSockets->heap, gSockets);
			gSockets = 0;
			return true;
		}

		// FUNCTION: ENGINE 0x1093F640
		int Socket(int family, int type, int protocol)
		{
			int nativeFamily;
			int nativeType;
			int nativeProtocol;
			int result = MapFamily(family, &nativeFamily);
			if (result < 0)
			{
				return result;
			}
			result = MapType(type, &nativeType);
			if (result < 0)
			{
				return result;
			}
			result = MapProtocol(protocol, &nativeProtocol);
			if (result < 0)
			{
				return result;
			}
			SocketEntry* entry = AllocEntry();
			if (entry == 0)
			{
				return -4;
			}
			entry->handle = socket(nativeFamily, nativeType, nativeProtocol);
			if (entry->handle == 0xFFFFFFFF)
			{
				FreeEntry(entry);
				return LastError();
			}
			return GetHandle(entry);
		}

		// FUNCTION: ENGINE 0x1093F6D0
		int Close(int handle)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry != 0 && entry->open != 0)
			{
				if (closesocket(entry->handle) == -1)
				{
					return LastError();
				}
				FreeEntry(entry);
				return 0;
			}
			return -1;
		}

		// FUNCTION: ENGINE 0x1093F710
		// EQUIVALENT: scheduling; the engine forms the address of the source for the conversion call after the address of the result, ours before; every other instruction is the engine's
		int Accept(int handle, NetAddress* address, unsigned char size)
		{
			SocketEntry* entry = GetEntry(handle);
			if (entry == 0 || entry->open == 0)
			{
				return -1;
			}
			SocketEntry* accepted = AllocEntry();
			if (accepted == 0)
			{
				return -4;
			}
			int length = 0x10;
			sockaddr native;
			accepted->handle = accept(entry->handle, &native, &length);
			if (accepted->handle == 0xFFFFFFFF)
			{
				FreeEntry(accepted);
				return LastError();
			}
			if (address != 0 && size > 0)
			{
				NetAddress converted;
				int result = FromSockaddr(&converted, &native, length);
				if (result < 0)
				{
					return result;
				}
				unsigned int count = size <= converted.length ? size : converted.length;
				memcpy(address, &converted, count);
				address->length = count;
			}
			return GetHandle(accepted);
		}

		// FUNCTION: ENGINE 0x1093F7E0
		unsigned int ParseAddressValue(const char* text)
		{
			unsigned int first;
			unsigned int second;
			unsigned int third;
			unsigned int fourth;
			if (sscanf_s(text, "%d.%d.%d.%d", &first, &second, &third, &fourth) == 4 && first <= 0xFF && second <= 0xFF
				&& third <= 0xFF && fourth <= 0xFF)
			{
				return ((((fourth & 0xFF) << 8 | (third & 0xFF)) << 8 | (second & 0xFF)) << 8) | (first & 0xFF);
			}
			return 0;
		}

		// The sizes the layer is started with
		struct StartupParams
		{
			int count;
			int heap;
		};

		// FUNCTION: ENGINE 0x1093F870
		bool Startup(const StartupParams* params)
		{
			gMaxSockets = params->count;
			gSocketHeap = params->heap;
			if (Initialize(gMaxSockets, gSocketHeap))
			{
				char data[0x190];
				if (WSAStartup(2, data) != 0)
				{
					Destroy();
				}
				else
				{
					gStarted = true;
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x1093F8D0
		bool Cleanup()
		{
			gStarted = false;
			WSACleanup();
			return Destroy();
		}

		// FUNCTION: ENGINE 0x1093F8F0
		void Update()
		{
		}

		// FUNCTION: ENGINE 0x1093F900
		int GetDescription(const wchar_t** description)
		{
			if (description != 0)
			{
				*description = (const wchar_t*)0x10E8B4DC;
			}
			return 0;
		}

		// One socket to wait for (8 bytes): what to wait for and what came
		struct PollEntry
		{
			int handle;  // +0x0
			unsigned short events;  // +0x4: 1 read, 2 write
			unsigned short result;  // +0x6: 1 readable, 2 writable, 4 error, 0x80 not a socket
		};

		// FUNCTION: ENGINE 0x1093EB30
		// NONMATCHING: block layout (41 %): the engine places the return of 0 for an empty or request-less poll right behind the first loop and the wait after it, ours keeps the wait inline and the return behind it; the loops, the set updates and the result handling are the engine's
#ifdef NONMATCHING
		int Poll(PollEntry* entries, unsigned int count, unsigned int timeout)
		{
			fd_set readSet;
			fd_set writeSet;
			fd_set errorSet;
			unsigned int readCount;
			unsigned int writeCount;
			readSet.fd_count = 0;
			readCount = 0;
			writeSet.fd_count = 0;
			writeCount = 0;
			errorSet.fd_count = 0;
			PollEntry* entry;
			if (count != 0)
			{
				entry = entries;
				for (unsigned int remaining = count; remaining != 0; remaining--, entry++)
				{
					entry->result = 0;
					SocketEntry* socketEntry = GetEntry(entry->handle);
					if (socketEntry == 0 || socketEntry->open == 0)
					{
						entry->result = 0x80;
						continue;
					}
					unsigned short events = entry->events;
					bool wanted = false;
					if ((events & 1) != 0)
					{
						FD_SET(socketEntry->handle, &readSet);
						readCount++;
						wanted = true;
					}
					if ((events & 2) != 0)
					{
						FD_SET(socketEntry->handle, &writeSet);
						writeCount++;
					}
					else if (!wanted)
					{
						continue;
					}
					FD_SET(socketEntry->handle, &errorSet);
				}
				if (readCount != 0 || writeCount != 0)
				{
					goto wait;
				}
			}
			return 0;
		wait:
			timeval limit;
			const timeval* limitPointer;
			if (timeout == 0xFFFFFFFF)
			{
				limitPointer = 0;
			}
			else
			{
				limit.tv_sec = timeout / 1000;
				limit.tv_usec = (timeout % 1000) * 1000;
				limitPointer = &limit;
			}
			unsigned int most = writeCount;
			if (readCount > most)
			{
				most = readCount;
			}
			if (select(most + 1, &readSet, &writeSet, &errorSet, limitPointer) == -1)
			{
				return LastError();
			}
			int ready = 0;
			entry = entries;
			for (unsigned int remaining = count; remaining != 0; remaining--, entry++)
			{
				bool changed = false;
				unsigned short result = entry->result;
				if ((char)result < 0)
				{
					continue;
				}
				SocketEntry* socketEntry = GetEntry(entry->handle);
				if (socketEntry == 0 || socketEntry->open == 0)
				{
					entry->result = result | 0x80;
					continue;
				}
				if ((entry->events & 1) != 0 && __WSAFDIsSet(socketEntry->handle, &readSet) != 0)
				{
					entry->result |= 1;
					changed = true;
				}
				if ((entry->events & 2) != 0 && __WSAFDIsSet(socketEntry->handle, &writeSet) != 0)
				{
					entry->result |= 2;
					changed = true;
				}
				if (__WSAFDIsSet(socketEntry->handle, &errorSet) != 0)
				{
					entry->result |= 4;
					ready++;
				}
				else if (changed)
				{
					ready++;
				}
			}
			return ready;
		}
#endif

		// A sixteen byte address (the length the layer's addresses have); compared byte by byte
		struct Address16
		{
			// 0x1093FBC0 / 0x1093FC70
			bool operator==(const Address16& other) const;
			bool operator!=(const Address16& other) const;

			unsigned char bytes[16];
		};

		// FUNCTION: ENGINE 0x1093FBC0
		bool Address16::operator==(const Address16& other) const
		{
			return memcmp(bytes, other.bytes, 16) == 0;
		}

		// FUNCTION: ENGINE 0x1093FC70
		bool Address16::operator!=(const Address16& other) const
		{
			return memcmp(bytes, other.bytes, 16) != 0;
		}
	}
}
