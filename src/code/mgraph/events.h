// The events of the mgraph library's context (RTTI: mgraph::ContextEvent and the events derived from it): commands that
// other threads queue for the context of the graphs and that the context executes in its own turn. All of them count
// the events alive in one shared counter.
#ifndef MGRAPH_EVENTS_H
#define MGRAPH_EVENTS_H

#include "code/mgraph/node.h"
#include "code/om/allocation.h"
#include "code/om/delegate.h"
#include "code/om/refcount.h"

namespace mgraph
{
	// A command of the evaluation pass (RTTI not recovered; the name is a guess): the context deletes it with the list
	class EvaluateCommand
	{
	public:
		virtual ~EvaluateCommand();
	};

	// A command in a list of the context: the command and the node's links
	struct CommandNode
	{
		OM_ALLOCATION(CommandNode);

		EvaluateCommand* command;
		NodeLink link;  // 4
	};

	// The commands the context runs before or after an evaluation pass (name guessed)
	class CommandList
	{
	public:
		// 0x10AC5070: appends a command
		CommandNode* Add(void* command);
		// 0x10AC5180: takes a node out of the list and deletes it and its command
		void Erase(CommandNode* node);
		// 0x10AC5790: deletes the node of a command
		void Remove(void* command);

		NodeLink* head;
		NodeLink* tail;
	};

	class Level;
	class ContextConnectionBase;
	// 0x10AC46F0 (name guessed): puts a node in the list of a level (null: none) and takes it out of the list of its old one
	void SetNodeLevel(Node* node, Level* level);

	// What a context is run by (RTTI not recovered; the name is a guess): it knows whether the caller is its thread
	class ContextOwner
	{
	public:
		virtual void Slot0() = 0;
		// Slot 1: the sample rate the nodes run at
		virtual float GetSampleRate() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual bool IsCurrentThread() = 0;
	};

	// What the evaluation context does for the events (RTTI not recovered; the name and the methods are guesses)
	class Context
	{
	public:
		CommandList preEvaluateCommands;  // 0
		CommandList postEvaluateCommands;  // 8
		char unknown10[8];
		NodeLink* firstNode;  // 0x18: the nodes of the context (the links at 0x2C of the nodes)
		NodeLink* lastNode;  // 0x1C
		NodeLink* firstLevel;  // 0x20: the levels of the nodes (the links at 0x20 of the levels)
		NodeLink* lastLevel;  // 0x24
		char unknown28[0x24];
		ContextOwner* owner;  // 0x4C
		char unknown50[0x40];
		char lockSection[0x18];  // 0x90: the critical section the context is locked with
		unsigned int lockCount;  // 0xA8
		char unknownAC[0xC];
		unsigned int evaluationCount;  // 0xB8

		// 0x10AC3380: whether the caller runs on the thread of the context's owner (false without an owner)
		bool IsOwnerThread();
		// 0x10AC33A0: lets go of the lock (see 0x10AC5680)
		void Unlock();
		// 0x10AC33C0: whether the context is locked
		bool IsLocked();

		// 0x10AC4950 / 0x10AC49B0: puts a node in the lists of the context, takes it out
		void AddNode(Node* node);
		void RemoveNode(Node* node);
		// 0x10AC33D0: what the nodes allocate their channels for (name guessed)
		void* GetChannelOwner();
		// 0x10AC5430 / 0x10AC5520: a connection of a pin of a graph in the context, and out of it (names guessed)
		void AddConnection(ContextConnectionBase* connection);
		void RemoveConnection(ContextConnectionBase* connection);
		// 0x10AC5770 / 0x10AC5780 / 0x10AC59F0 / 0x10AC5A00: a command of the evaluation pass
		void AddPreEvaluateCommand(void* command);
		void AddPostEvaluateCommand(void* command);
		void RemovePreEvaluateCommand(void* command);
		void RemovePostEvaluateCommand(void* command);
	};

	// What a barrier event signals once the context got to it (name guessed)
	class BarrierSignal
	{
	public:
		virtual void Signal() = 0;
	};

	class ContextEvent
	{
	public:
		ContextEvent()
		{
			om::ThreadSafeRefCount::AddRef(&liveEvents);
		}
		// Slot 0
		virtual ~ContextEvent()
		{
			om::ThreadSafeRefCount::Release(&liveEvents);
		}
		// Slot 1: the context executes the event
		virtual void Execute(Context* context) = 0;

		// 0x11327700: how many events are alive (name guessed)
		static int liveEvents;

		// +4: the link of the event in its queue
		om::GarbageLink link;
	};

	class BarrierEvent : public ContextEvent
	{
	public:
		BarrierEvent(BarrierSignal* newSignal, unsigned int* newTime);
		virtual ~BarrierEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(BarrierEvent);

		BarrierSignal* signal;  // 8
		unsigned int* time;  // 0xC: where the milliseconds of the signal go
	};

	class AddPreEvaluateCommandEvent : public ContextEvent
	{
	public:
		explicit AddPreEvaluateCommandEvent(void* newCommand);
		virtual ~AddPreEvaluateCommandEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(AddPreEvaluateCommandEvent);

		void* command;  // 8
	};

	class AddPostEvaluateCommandEvent : public ContextEvent
	{
	public:
		explicit AddPostEvaluateCommandEvent(void* newCommand);
		virtual ~AddPostEvaluateCommandEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(AddPostEvaluateCommandEvent);

		void* command;  // 8
	};

	class RemovePreEvaluateCommandEvent : public ContextEvent
	{
	public:
		explicit RemovePreEvaluateCommandEvent(void* newCommand);
		virtual ~RemovePreEvaluateCommandEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(RemovePreEvaluateCommandEvent);

		void* command;  // 8
	};

	class RemovePostEvaluateCommandEvent : public ContextEvent
	{
	public:
		explicit RemovePostEvaluateCommandEvent(void* newCommand);
		virtual ~RemovePostEvaluateCommandEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(RemovePostEvaluateCommandEvent);

		void* command;  // 8
	};

	class ResetChannelEvent : public ContextEvent
	{
	public:
		ResetChannelEvent(Graph* newTarget, unsigned int newChannel);
		virtual ~ResetChannelEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(ResetChannelEvent);

		Graph* target;  // 8
		unsigned int channel;  // 0xC
	};

	class AddGraphToContextEvent : public ContextEvent
	{
	public:
		explicit AddGraphToContextEvent(Graph* newTarget);
		virtual ~AddGraphToContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(AddGraphToContextEvent);

		Graph* target;  // 8
	};

	class GraphSetNumChannelsContextEvent : public ContextEvent
	{
	public:
		GraphSetNumChannelsContextEvent(Graph* newTarget, unsigned int newNumChannels);
		virtual ~GraphSetNumChannelsContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(GraphSetNumChannelsContextEvent);

		Graph* target;  // 8
		unsigned int numChannels;  // 0xC
	};

	class RemoveGraphFromContextEvent : public ContextEvent
	{
	public:
		explicit RemoveGraphFromContextEvent(Graph* newTarget);
		virtual ~RemoveGraphFromContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(RemoveGraphFromContextEvent);

		Graph* target;  // 8
	};

	class SetChannelEnabledEvent : public ContextEvent
	{
	public:
		SetChannelEnabledEvent(Graph* newTarget, unsigned int newChannel, bool newEnabled);
		virtual ~SetChannelEnabledEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(SetChannelEnabledEvent);

		Graph* target;  // 8
		unsigned int channel;  // 0xC
		bool enabled;  // 0x10
	};
}

#endif
