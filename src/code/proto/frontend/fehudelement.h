// proto::FEHudElement, proto::FEHudVariable and proto::FEHudVariableTemplate<...> (RTTI names): the base of the head-up
// display's elements and the variables they keep in the front end's movie. An element counts how often it was hidden
// and tells its subclass when it appears or disappears (slot 1); it updates its variables in slot 0. A variable
// remembers the last value it was given and writes it to the movie, by the path its subclass names, when it is
// flushed. The member names are guesses. Unit 0x104C0390 - 0x104C0450 and 0x104C23B0 - 0x104C2600 (no assert path;
// the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDELEMENT_H
#define PROTO_FRONTEND_FEHUDELEMENT_H

#include "code/container/string.h"
#include "code/proto/frontend/flashvalue.h"

namespace proto
{
	class FEHudVariable
	{
	public:
		// 0x104C23B0
		FEHudVariable();
		virtual ~FEHudVariable()
		{
		}
		// The path of the variable in the movie
		virtual const char* GetPath() = 0;

		// 0x104C2590: remembers a new value and marks it to be written
		void Set(FlashValue newValue);
		// 0x104C23D0: writes the value to the movie when it changed (or always when forced)
		void Flush(bool force);
		// 0x104C2430: reads the variable's value back from the movie
		FlashVariant Get();

		FlashValue value;  // +8
		bool changed;  // +0x98
	};

	// A path that is a string of the code (Literal) or one the variable keeps (FixedLength); the second argument tells
	// the instances of one policy apart
	class SymbolPathStoragePolicy_Literal
	{
	public:
		typedef container::StringLiteral Storage;
	};

	class SymbolPathStoragePolicy_FixedLength
	{
	public:
		typedef container::StringC<128> Storage;
	};

	template<class Policy, int N> class FEHudVariableTemplate : public FEHudVariable
	{
	public:
		explicit FEHudVariableTemplate(const char* newPath) : path(newPath)
		{
		}
		// An empty path (the paths of an array of variables are set after the construction)
		FEHudVariableTemplate() : path("")
		{
		}
		virtual const char* GetPath()
		{
			return path.ConstData();
		}
		// Replaces the path (the instance of the typewriter keeps its own path)
		void SetPath(const char* newPath)
		{
			path = newPath;
		}

		typename Policy::Storage path;  // +0xA0
	};

	// The variable with a path of its own (the path is set after the construction)
	template<> class FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 0> : public FEHudVariable
	{
	public:
		// 0x104AA380 (another unit): an empty path
		FEHudVariableTemplate();
		virtual const char* GetPath()
		{
			return path.ConstData();
		}

		container::StringC<128> path;  // +0xA0
	};

	class FEHudElement
	{
	public:
		// 0x104C0390
		FEHudElement();
		// vftable slot 0: writes the variables that changed (or all of them when forced)
		virtual void Update(bool force) = 0;
		// vftable slot 1: the element appears or disappears
		virtual void OnShow(bool shown) = 0;

		// 0x104C0440
		bool IsShown() const;
		// 0x104C03B0: one more request to show (or hide) the element; true when its state changed
		bool Show(bool show);
		// 0x104C0450
		void SetHideCount(const int& count);
		// 0x104C04A0
		int GetHideCount() const;

		bool shown;  // +4
		int hideCount;  // +8
	};
}

#endif
