// The task nodes of the core's asynchronous tasks (0x10B7F3A0 - 0x10B7F700): a node holds what a task runs and the nodes that run after it;
// a tree of nodes is flattened into the chains of task records and submitted (file name and member names guessed).
#include <string.h>

#include "code/core/asynctask.h"

namespace core
{
	// FUNCTION: ENGINE 0x10B7F3A0
	AsyncTaskNode::AsyncTaskNode() :
		type(0),
		function(0),
		data(0),
		callback(0),
		event(0),
		timing(0),
		childCount(0),
		firstChild(0),
		lastChild(0),
		next(0)
	{
	}

	// FUNCTION: ENGINE 0x10B7F3D0
	void AsyncTaskNode::Destroy()
	{
	}

	// FUNCTION: ENGINE 0x10B7F3E0
	bool AsyncTaskNode::Set(int functionId, void* newData, AsyncTaskCallback* newCallback, void* newEvent)
	{
		if (functionId != 0)
		{
			function = GetAsyncTaskFunction(functionId);
			if (function != 0)
			{
				type = functionId;
				data = newData;
				callback = newCallback;
				event = newEvent;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10B7F430
	void AsyncTaskNode::SetData(void* newData)
	{
		data = newData;
	}

	// FUNCTION: ENGINE 0x10B7F440
	void* AsyncTaskNode::GetData()
	{
		return data;
	}

	// FUNCTION: ENGINE 0x10B7F450
	void AsyncTaskNode::SetCallback(AsyncTaskCallback* newCallback)
	{
		callback = newCallback;
	}

	// FUNCTION: ENGINE 0x10B7F460
	AsyncTaskCallback* AsyncTaskNode::GetCallback()
	{
		return callback;
	}

	// FUNCTION: ENGINE 0x10B7F470
	void AsyncTaskNode::SetEvent(void* newEvent)
	{
		event = newEvent;
	}

	// FUNCTION: ENGINE 0x10B7F480
	void* AsyncTaskNode::GetEvent()
	{
		return event;
	}

	// FUNCTION: ENGINE 0x10B7F490
	void AsyncTaskNode::SetTiming(AsyncTaskTiming* newTiming)
	{
		timing = newTiming;
	}

	// FUNCTION: ENGINE 0x10B7F4A0
	AsyncTaskTiming* AsyncTaskNode::GetTiming()
	{
		return timing;
	}

	// FUNCTION: ENGINE 0x10B7F4B0
	void AsyncTaskNode::AddChild(AsyncTaskNode* child)
	{
		child->next = 0;
		if (firstChild == 0)
		{
			childCount++;
			firstChild = child;
			lastChild = child;
			return;
		}
		lastChild->next = child;
		childCount++;
		lastChild = child;
	}

	// FUNCTION: ENGINE 0x10B7F510
	unsigned int AsyncTaskNode::GetChildCount()
	{
		return childCount;
	}

	// FUNCTION: ENGINE 0x10B7F520
	AsyncTaskNode* AsyncTaskNode::GetFirstChild()
	{
		return firstChild;
	}

	// FUNCTION: ENGINE 0x10B7F530
	AsyncTaskNode* AsyncTaskNode::GetNext()
	{
		return next;
	}

	// FUNCTION: ENGINE 0x10B7F540
	int AsyncTaskNode::CountNodes()
	{
		int count = 1;
		for (AsyncTaskNode* child = firstChild; child != 0; child = child->next)
		{
			count += child->CountNodes();
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10B7F570
	// NONMATCHING: the engine keeps the zero in eax and copies the node's fields through ecx and edx, ours uses eax for the copies (85 %)
#ifdef NONMATCHING
	AsyncTaskNode::Flattened* AsyncTaskNode::Flatten(Flattened* result, AsyncTask* buffer, unsigned int size, AsyncTaskGroup* group,
		bool flag, int kind)
	{
		AsyncTask* task = buffer;
		memset(buffer, 0, sizeof(AsyncTask));
		buffer->kind = static_cast<unsigned char>(type);
		buffer->data = data;
		buffer->function = function;
		buffer->callback = callback;
		buffer->event = event;
		task->flags &= 1;
		buffer->timing = timing;
		if (buffer->timing != 0)
		{
			buffer->timing->start = 0;
			buffer->timing->end = 0;
			buffer->timing->processor = 0;
			buffer->timing->done = 0;
		}
		if (group != 0)
		{
			AddToAsyncTaskGroup(group, buffer, kind);
		}
		AsyncTaskNode* child = firstChild;
		result->tasks = buffer;
		result->count = 1;
		AsyncTask* next = buffer + 1;
		if (child != 0)
		{
			unsigned int remaining = size - sizeof(AsyncTask);
			do
			{
				Flattened flattened;
				child->Flatten(&flattened, next, remaining, flag ? group : 0, flag, kind);
				unsigned char flags = task->flags;
				unsigned char childFlags = flattened.tasks->flags;
				result->count += flattened.count;
				remaining -= flattened.count * sizeof(AsyncTask);
				task->flags = ((flags & 0xFE) + (childFlags & 0xFE) + 2) ^ (flags & 1);
				child = child->next;
				next += flattened.count;
			}
			while (child != 0);
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10B7F680
	void AsyncTaskNode::Submit(int unused)
	{
		AsyncTask tasks[32];
		Flattened flattened;
		Flatten(&flattened, tasks, sizeof(tasks), 0, 0, 2);
		QueueAsyncTasks(flattened.tasks, flattened.count, unused);
	}

	// FUNCTION: ENGINE 0x10B7F6C0
	void AsyncTaskNode::Run(int unused)
	{
		AsyncTask tasks[32];
		Flattened flattened;
		Flatten(&flattened, tasks, sizeof(tasks), 0, 0, 2);
		RunAsyncTasksNow(flattened.tasks, flattened.count, unused);
	}

	// FUNCTION: ENGINE 0x10B7F960
	// NONMATCHING: 93 %, the engine stores the state as an immediate and the timing record from a zero register
#ifdef NONMATCHING
	AsyncTaskJob::AsyncTaskJob()
	{
		state = 0;
		timing.start = 0;
		timing.end = 0;
		timing.processor = 0;
		timing.done = 0;
	}
#endif

	// FUNCTION: ENGINE 0x10B7F990
	AsyncTaskJob::~AsyncTaskJob()
	{
	}

	// FUNCTION: ENGINE 0x10B7F9A0
	int AsyncTaskJob::GetState()
	{
		if (state == 3 || state == 4)
		{
			if (IsAsyncTaskTimingDone(&timing))
			{
				state = 1;
			}
		}
		return state;
	}

	// FUNCTION: ENGINE 0x10B7F9D0
	void AsyncTaskJob::Set(int functionId, void* newData, AsyncTaskCallback* newCallback)
	{
		GetState();
		state = 1;
		node.Set(functionId, newData, newCallback, node.GetEvent());
		node.SetTiming(&timing);
	}

	// FUNCTION: ENGINE 0x10B7FA10
	void AsyncTaskJob::SetData(void* newData)
	{
		node.SetData(newData);
	}

	// FUNCTION: ENGINE 0x10B7FA20
	void* AsyncTaskJob::GetData()
	{
		return node.GetData();
	}

	// FUNCTION: ENGINE 0x10B7FA30
	void AsyncTaskJob::SetCallback(AsyncTaskCallback* newCallback)
	{
		node.SetCallback(newCallback);
	}

	// FUNCTION: ENGINE 0x10B7FA50
	AsyncTaskCallback* AsyncTaskJob::GetCallback()
	{
		return node.GetCallback();
	}

	// FUNCTION: ENGINE 0x10B7FA40
	void AsyncTaskJob::SetEvent(void* newEvent)
	{
		node.SetEvent(newEvent);
	}

	// FUNCTION: ENGINE 0x10B7FA60
	bool AsyncTaskJob::AddChild(AsyncTaskJob* child)
	{
		node.AddChild(&child->node);
		child->state = 3;
		return true;
	}

	// FUNCTION: ENGINE 0x10B7FAB0
	void AsyncTaskJob::RunHere()
	{
		state = 4;
		node.Run(0);
	}

	// FUNCTION: ENGINE 0x10B7FAD0
	bool AsyncTaskJob::IsQueued()
	{
		return node.GetNext() != 0;
	}

	// FUNCTION: ENGINE 0x10B7FAE0
	bool AsyncTaskJob::GetResult(unsigned int* start, unsigned int* end, unsigned char* processor)
	{
		if (!IsAsyncTaskTimingDone(&timing))
		{
			return false;
		}
		if (timing.start != 0 || timing.end != 0)
		{
			*start = timing.start;
			*end = timing.end;
			*processor = static_cast<unsigned char>(timing.processor);
			return true;
		}
		return false;
	}
}
