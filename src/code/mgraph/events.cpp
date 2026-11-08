// The events of the mgraph library's context (0x10AC3B00 - 0x10AC7700).
#include "code/mgraph/events.h"
#include "code/mgraph/graph.h"
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
	ResetChannelEvent::ResetChannelEvent(Graph* newTarget, unsigned int newChannel) :
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
	AddGraphToContextEvent::AddGraphToContextEvent(Graph* newTarget) :
		target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10AC76B0
	void AddGraphToContextEvent::Execute(Context* context)
	{
		target->Attach(context);
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
	GraphSetNumChannelsContextEvent::GraphSetNumChannelsContextEvent(Graph* newTarget, unsigned int newNumChannels) :
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
	RemoveGraphFromContextEvent::RemoveGraphFromContextEvent(Graph* newTarget) :
		target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10AC76D0
	void RemoveGraphFromContextEvent::Execute(Context* context)
	{
		target->Detach(context);
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
	SetChannelEnabledEvent::SetChannelEnabledEvent(Graph* newTarget, unsigned int newChannel, bool newEnabled) :
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

	// FUNCTION: ENGINE 0x10AC3630
	const char* CommandNode::AllocationTag()
	{
		return "";
	}

	// The command node a link of the list belongs to, null for no link
	static __forceinline CommandNode* NodeOfLink(NodeLink* link)
	{
		CommandNode* node;
		if (link != 0)
		{
			node = reinterpret_cast<CommandNode*>(reinterpret_cast<char*>(link) - 4);
		}
		else
		{
			node = 0;
		}
		return node;
	}

	// The link of a command node, null for no node
	static __forceinline NodeLink* LinkOfNode(CommandNode* node)
	{
		NodeLink* link;
		if (node != 0)
		{
			link = &node->link;
		}
		else
		{
			link = 0;
		}
		return link;
	}

	// FUNCTION: ENGINE 0x10AC5070
	CommandNode* CommandList::Add(void* command)
	{
		CommandNode* node = static_cast<CommandNode*>(om::Allocate(CommandNode::AllocationTag(), sizeof(CommandNode), 4));
		NodeLink* link;
		if (node != 0)
		{
			node->command = static_cast<EvaluateCommand*>(command);
			link = &node->link;
		}
		else
		{
			node = 0;
			link = 0;
		}
		if (head == 0)
		{
			head = link;
			link->previous = 0;
			tail = link;
			link->next = 0;
			return node;
		}
		tail->next = link;
		link->previous = tail;
		tail = link;
		link->next = 0;
		return node;
	}

	// FUNCTION: ENGINE 0x10AC5180
	void CommandList::Erase(CommandNode* node)
	{
		NodeLink* link = LinkOfNode(node);
		if (link->previous == 0)
		{
			head = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			tail = link->previous;
		}
		else
		{
			link->next->previous = link->previous;
		}
		if (node != 0)
		{
			if (node->command != 0)
			{
				delete node->command;
			}
			delete node;
		}
	}

	// FUNCTION: ENGINE 0x10AC5790
	void CommandList::Remove(void* command)
	{
		CommandNode* node = NodeOfLink(head);
		while (node != 0)
		{
			CommandNode* next = NodeOfLink(LinkOfNode(node)->next);
			if (node->command == command)
			{
				Erase(node);
				return;
			}
			node = next;
		}
	}

	// FUNCTION: ENGINE 0x10AC33D0
	void* Context::GetChannelOwner()
	{
		return reinterpret_cast<void*>(evaluationCount);
	}

	// FUNCTION: ENGINE 0x10AC4950
	void Context::AddNode(Node* node)
	{
		NodeLink* link;
		if (node != 0)
		{
			link = &node->contextLink;
		}
		else
		{
			link = 0;
		}
		if (firstNode == 0)
		{
			firstNode = link;
			link->previous = 0;
		}
		else
		{
			lastNode->next = link;
			link->previous = lastNode;
		}
		lastNode = link;
		link->next = 0;
		Level* level;
		if (firstLevel != 0)
		{
			level = reinterpret_cast<Level*>(reinterpret_cast<char*>(firstLevel) - 0x20);
		}
		else
		{
			level = 0;
		}
		SetNodeLevel(node, level);
	}

	// FUNCTION: ENGINE 0x10AC49B0
	void Context::RemoveNode(Node* node)
	{
		SetNodeLevel(node, 0);
		NodeLink* link;
		if (node != 0)
		{
			link = &node->contextLink;
		}
		else
		{
			link = 0;
		}
		if (link->previous == 0)
		{
			firstNode = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			lastNode = link->previous;
		}
		else
		{
			link->next->previous = link->previous;
		}
	}

	// FUNCTION: ENGINE 0x10AC5770
	void Context::AddPreEvaluateCommand(void* command)
	{
		preEvaluateCommands.Add(command);
	}

	// FUNCTION: ENGINE 0x10AC5780
	void Context::AddPostEvaluateCommand(void* command)
	{
		postEvaluateCommands.Add(command);
	}

	// FUNCTION: ENGINE 0x10AC59F0
	void Context::RemovePreEvaluateCommand(void* command)
	{
		preEvaluateCommands.Remove(command);
	}

	// FUNCTION: ENGINE 0x10AC5A00
	void Context::RemovePostEvaluateCommand(void* command)
	{
		postEvaluateCommands.Remove(command);
	}
}
