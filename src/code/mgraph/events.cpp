// The events of the mgraph library's context (0x10AC3B00 - 0x10AC7700).
#include "code/mgraph/events.h"
#include "code/core/time.h"

namespace mgraph
{
	// 0x11327700
	int ContextEvent::liveEvents = 0;

	inline BarrierEvent::~BarrierEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC3BB0
	BarrierEvent::BarrierEvent(BarrierSignal* newSignal, unsigned int* newTime)
	{
		time = newTime;
		signal = newSignal;
	}

	// FUNCTION: ENGINE 0x10AC3C00
	void BarrierEvent::Execute(Context* context)
	{
		if (time != 0)
		{
			*time = core::GetMilliseconds();
		}
		signal->Signal();
	}

	// FUNCTION: ENGINE 0x10AC3620
	const char* BarrierEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC3930
	inline AddPreEvaluateCommandEvent::~AddPreEvaluateCommandEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC38E0
	AddPreEvaluateCommandEvent::AddPreEvaluateCommandEvent(void* newCommand) :
		command(newCommand)
	{
	}

	// FUNCTION: ENGINE 0x10AC58A0
	void AddPreEvaluateCommandEvent::Execute(Context* context)
	{
		context->AddPreEvaluateCommand(command);
	}

	// FUNCTION: ENGINE 0x10AC3570
	const char* AddPreEvaluateCommandEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC39C0
	inline AddPostEvaluateCommandEvent::~AddPostEvaluateCommandEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC3970
	AddPostEvaluateCommandEvent::AddPostEvaluateCommandEvent(void* newCommand) :
		command(newCommand)
	{
	}

	// FUNCTION: ENGINE 0x10AC58B0
	void AddPostEvaluateCommandEvent::Execute(Context* context)
	{
		context->AddPostEvaluateCommand(command);
	}

	// FUNCTION: ENGINE 0x10AC3580
	const char* AddPostEvaluateCommandEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC3A50
	inline RemovePreEvaluateCommandEvent::~RemovePreEvaluateCommandEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC3A00
	RemovePreEvaluateCommandEvent::RemovePreEvaluateCommandEvent(void* newCommand) :
		command(newCommand)
	{
	}

	// FUNCTION: ENGINE 0x10AC5A80
	void RemovePreEvaluateCommandEvent::Execute(Context* context)
	{
		context->RemovePreEvaluateCommand(command);
	}

	// FUNCTION: ENGINE 0x10AC3590
	const char* RemovePreEvaluateCommandEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC3AE0
	inline RemovePostEvaluateCommandEvent::~RemovePostEvaluateCommandEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC3A90
	RemovePostEvaluateCommandEvent::RemovePostEvaluateCommandEvent(void* newCommand) :
		command(newCommand)
	{
	}

	// FUNCTION: ENGINE 0x10AC5A90
	void RemovePostEvaluateCommandEvent::Execute(Context* context)
	{
		context->RemovePostEvaluateCommand(command);
	}

	// FUNCTION: ENGINE 0x10AC35A0
	const char* RemovePostEvaluateCommandEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC6310
	inline ResetChannelEvent::~ResetChannelEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC62C0
	ResetChannelEvent::ResetChannelEvent(Context* newTarget, unsigned int newChannel) :
		target(newTarget),
		channel(newChannel)
	{
	}

	// FUNCTION: ENGINE 0x10AC76A0
	void ResetChannelEvent::Execute(Context* context)
	{
		target->ResetChannel(channel);
	}

	// FUNCTION: ENGINE 0x10AC5EE0
	const char* ResetChannelEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC63A0
	inline AddGraphToContextEvent::~AddGraphToContextEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC6350
	AddGraphToContextEvent::AddGraphToContextEvent(Context* newTarget) :
		target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10AC76B0
	void AddGraphToContextEvent::Execute(Context* context)
	{
		target->AddGraph(context);
	}

	// FUNCTION: ENGINE 0x10AC5EF0
	const char* AddGraphToContextEvent::AllocationTag()
	{
		return "";
	}

	inline GraphSetNumChannelsContextEvent::~GraphSetNumChannelsContextEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC63E0
	GraphSetNumChannelsContextEvent::GraphSetNumChannelsContextEvent(Context* newTarget, unsigned int newNumChannels) :
		target(newTarget),
		numChannels(newNumChannels)
	{
	}

	// FUNCTION: ENGINE 0x10AC76C0
	void GraphSetNumChannelsContextEvent::Execute(Context* context)
	{
		target->SetNumChannels(numChannels);
	}

	// FUNCTION: ENGINE 0x10AC5F00
	const char* GraphSetNumChannelsContextEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC64C0
	inline RemoveGraphFromContextEvent::~RemoveGraphFromContextEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC6470
	RemoveGraphFromContextEvent::RemoveGraphFromContextEvent(Context* newTarget) :
		target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10AC76D0
	void RemoveGraphFromContextEvent::Execute(Context* context)
	{
		target->RemoveGraph(context);
	}

	// FUNCTION: ENGINE 0x10AC5F10
	const char* RemoveGraphFromContextEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AC6560
	inline SetChannelEnabledEvent::~SetChannelEnabledEvent()
	{
	}

	// FUNCTION: ENGINE 0x10AC6500
	SetChannelEnabledEvent::SetChannelEnabledEvent(Context* newTarget, unsigned int newChannel, bool newEnabled) :
		target(newTarget),
		channel(newChannel),
		enabled(newEnabled)
	{
	}

	// FUNCTION: ENGINE 0x10AC76E0
	void SetChannelEnabledEvent::Execute(Context* context)
	{
		target->SetChannelEnabled(channel, enabled);
	}

	// FUNCTION: ENGINE 0x10AC5F20
	const char* SetChannelEnabledEvent::AllocationTag()
	{
		return "";
	}
}
