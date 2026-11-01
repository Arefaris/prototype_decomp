// The events of the mgraph library's context (RTTI: mgraph::ContextEvent and the events derived from it): commands that
// other threads queue for the context of the graphs and that the context executes in its own turn. All of them count
// the events alive in one shared counter.
#ifndef MGRAPH_EVENTS_H
#define MGRAPH_EVENTS_H

#include "code/mgraph/node.h"
#include "code/om/allocation.h"
#include "code/om/refcount.h"

namespace mgraph
{
	// What the evaluation context does for the events (RTTI not recovered; the name and the methods are guesses)
	class Context
	{
	public:
		// 0x10AC4950 / 0x10AC49B0: puts a node in the lists of the context, takes it out
		void AddNode(Node* node);
		void RemoveNode(Node* node);
		// 0x10AC33D0: what the nodes allocate their channels for (name guessed)
		void* GetChannelOwner();
		// 0x10AC5770 / 0x10AC5780 / 0x10AC59F0 / 0x10AC5A00: a command of the evaluation pass
		void AddPreEvaluateCommand(void* command);
		void AddPostEvaluateCommand(void* command);
		void RemovePreEvaluateCommand(void* command);
		void RemovePostEvaluateCommand(void* command);
		// 0x10AC6CA0 / 0x10AC6D20 / 0x10AC6E40 / 0x10AC6F00 / 0x10AC6F60: the graphs and the channels of the context
		void AddGraph(Context* context);
		void ResetChannel(unsigned int channel);
		void SetNumChannels(unsigned int newNumChannels);
		void SetChannelEnabled(unsigned int channel, bool enabled);
		void RemoveGraph(Context* context);
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

		unsigned int unknown4;
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
		ResetChannelEvent(Context* newTarget, unsigned int newChannel);
		virtual ~ResetChannelEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(ResetChannelEvent);

		Context* target;  // 8
		unsigned int channel;  // 0xC
	};

	class AddGraphToContextEvent : public ContextEvent
	{
	public:
		explicit AddGraphToContextEvent(Context* newTarget);
		virtual ~AddGraphToContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(AddGraphToContextEvent);

		Context* target;  // 8
	};

	class GraphSetNumChannelsContextEvent : public ContextEvent
	{
	public:
		GraphSetNumChannelsContextEvent(Context* newTarget, unsigned int newNumChannels);
		virtual ~GraphSetNumChannelsContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(GraphSetNumChannelsContextEvent);

		Context* target;  // 8
		unsigned int numChannels;  // 0xC
	};

	class RemoveGraphFromContextEvent : public ContextEvent
	{
	public:
		explicit RemoveGraphFromContextEvent(Context* newTarget);
		virtual ~RemoveGraphFromContextEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(RemoveGraphFromContextEvent);

		Context* target;  // 8
	};

	class SetChannelEnabledEvent : public ContextEvent
	{
	public:
		SetChannelEnabledEvent(Context* newTarget, unsigned int newChannel, bool newEnabled);
		virtual ~SetChannelEnabledEvent();
		virtual void Execute(Context* context);
		OM_ALLOCATION(SetChannelEnabledEvent);

		Context* target;  // 8
		unsigned int channel;  // 0xC
		bool enabled;  // 0x10
	};
}

#endif
