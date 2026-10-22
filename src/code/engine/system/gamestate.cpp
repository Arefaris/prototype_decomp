// The game state machine and the simulation driver: see the header. The file name is a guess.
#include "code/engine/system/simulationdriver.h"

#include <new>

#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/system/desynchunter.h"
#include "code/engine/system/gamestatetable.h"

namespace engine
{
	// The unit's unnamed callees and data (every name is a guess)
	class OnlineClock
	{
	public:
		// 0x108C7340: the time the network brought; flag is set when it did
		core::Time GetTime(bool* flag);
	};
	extern OnlineClock* gOnlineClock;                   // 0x11318894
	void RegisterDesyncVariable(void* variable, int size, const char* name, int mode);   // 0x108BF9C0
	void UnregisterDesyncVariable(void* variable);      // 0x108BFA20

	// FUNCTION: ENGINE 0x108372E0
	ISimulationDriver::ISimulationDriver() : time5(0, 0), time6(0, 0), time7(0, 0)
	{
		variablesRegistered = false;
		scaleA = 1.0f;
		scaleB = 1.0f;
		unknown6C = false;
	}

	// 0x10836820 (the body of the deleting destructor 0x10837370)
	ISimulationDriver::~ISimulationDriver()
	{
		if (variablesRegistered)
		{
			UnregisterDesyncVariable(&time4.milliseconds);
			UnregisterDesyncVariable(&time4.microseconds);
		}
	}

	// FUNCTION: ENGINE 0x10836850
	void ISimulationDriver::SetTime1Raw(unsigned int a, unsigned int b, unsigned int c)
	{
		time1.microseconds = a;
		time1.milliseconds = b;
		*(unsigned int*)&time1.seconds = c;
	}

	// FUNCTION: ENGINE 0x10836870
	void ISimulationDriver::SetTime4Raw(unsigned int a, unsigned int b, unsigned int c)
	{
		time4.microseconds = a;
		time4.milliseconds = b;
		*(unsigned int*)&time4.seconds = c;
	}

	// FUNCTION: ENGINE 0x10836890
	void ISimulationDriver::SetScaleA(float value)
	{
		scaleA = value;
	}

	// FUNCTION: ENGINE 0x108368A0
	void ISimulationDriver::SetScaleB(float value)
	{
		scaleB = value;
	}

	// FUNCTION: ENGINE 0x10836650
	core::Time ISimulationDriver::GetTime5()
	{
		return time5;
	}

	// FUNCTION: ENGINE 0x10836700
	void SimulationDriverTimeData::AddStep()
	{
		unsigned __int64 step = (unsigned __int64)time0.milliseconds * 1000 + time0.microseconds;
		if (scaleA != 1.0f)
		{
			step = (unsigned __int64)(step * scaleA);
		}
		if (scaleB != 1.0f)
		{
			step = (unsigned __int64)(step * scaleB);
		}
		time3.SetMicroseconds(step);
		time4.AddMicroseconds(step);
	}

	// FUNCTION: ENGINE 0x108368B0
	void ISimulationDriver::Slot6()
	{
		if (unknown6C)
		{
			time4 = time7;
			unknown6C = false;
		}
		AddStep();
		controller::InputSystem::Get()->CollectPlayers();
	}

	// FUNCTION: ENGINE 0x108368E0
	void ISimulationDriver::Slot7()
	{
		if (!unknown6C)
		{
			time7 = time4;
			unknown6C = true;
		}
		bool flag = false;
		time3 = gOnlineClock->GetTime(&flag);
		if (flag)
		{
			time4.Add(time3.milliseconds, time3.microseconds);
			controller::InputSystem::Get()->CollectPlayers();
			return;
		}
		AddStep();
		controller::InputSystem::Get()->CollectPlayers();
	}

	// FUNCTION: ENGINE 0x10836970
	void ISimulationDriver::Slot8()
	{
		time3.Clear();
		time2.Clear();
	}

	// FUNCTION: ENGINE 0x10836990
	void ISimulationDriver::Slot9()
	{
		time1.Set(0, 0);
		time0.Set(0, 0);
		time4.Set(0, 0);
		time3.Set(0, 0);
		time6.Set(0, 0);
		time5.Set(0, 0);
		scaleA = 1.0f;
		unknown6C = false;
		time7.Set(0, 0);
		if (!variablesRegistered)
		{
			RegisterDesyncVariable(&time4.milliseconds, 4, "SimTime-Milli", 2);
			RegisterDesyncVariable(&time4.microseconds, 4, "SimTime-MicroRemainder", 2);
			variablesRegistered = true;
		}
	}

	// The sync layer the machine talks to (0x108C7750 answers it; the members' names are guesses)
	class OnlineSync
	{
	public:
		void Unknown108C8030();
		char Unknown108C7760(unsigned int id);
		void Unknown108C7B50(unsigned int id, SyncCommands::SyncCallback* callback);
		void Unknown108C7BE0(unsigned int id);
		unsigned int Unknown108C7860(unsigned int id);
		char Unknown108C77C0(unsigned int id);
		char Unknown108C7820(unsigned int id);
		void Unknown108C8DB0();
	};
	OnlineSync* Unknown108C7750();
	void Unknown10899F60();
	void Unknown108336F0();
	void Unknown10821560();
	void Unknown10821540();

	extern GameStateEntry* gGameStates;                           // 0x1130DFC8
	extern GameStateName* gRequestNames;                          // 0x1130DFD0
	extern int gCurrentRequestName;                               // 0x1130DFD4
	extern unsigned int gStateFlags;                              // 0x111C6424
	extern ISimulationDriver* gSimulationDriver;                  // 0x1130DFE0
	extern ISimulationDriver* gDefaultSimulationDriver;           // 0x1130DFE4
	extern core::Fiber* gMainFiber;                               // 0x1130DFEC
	extern int gTransitionState;                                  // 0x1130DFF8
	extern GameStateRequest gCurrentRequest;                      // 0x111C6490
	extern unsigned int gTransitionMessage;                       // 0x1130DFBC

	// FUNCTION: ENGINE 0x10836AD0
	ISimulationDriver* GetSimulationDriver()
	{
		return gSimulationDriver;
	}

	// FUNCTION: ENGINE 0x10836AB0
	// EQUIVALENT: the engine loads the vftable slot before it stores the driver into the global, this compiler stores first (73 %); both orders do the same
	void SetSimulationDriver(SimulationDriver* driver)
	{
		if (driver == 0)
		{
			driver = (SimulationDriver*)gDefaultSimulationDriver;
		}
		gSimulationDriver = driver;
		driver->Slot9();
	}

	// FUNCTION: ENGINE 0x10836AE0
	// EQUIVALENT: the engine keeps the table pointer in a register from the start and addresses the entry as [eax + edx + 0x1C], this compiler adds the pointer from memory (48 %); the same loads, stores and result
	unsigned int* AddStateFlags(unsigned int flags)
	{
		GameStateEntry* table = gGameStates;
		gStateFlags |= flags;
		GameStateEntry* entry = &table[gCurrentRequest.state];
		entry->flagMask |= flags;
		return &entry->flagMask;
	}

	// FUNCTION: ENGINE 0x10836B10
	// EQUIVALENT: as AddStateFlags (51 %)
	unsigned int* RemoveStateFlags(unsigned int flags)
	{
		GameStateEntry* table = gGameStates;
		gStateFlags &= ~flags;
		GameStateEntry* entry = &table[gCurrentRequest.state];
		entry->flagMask |= flags;
		return &entry->flagMask;
	}

	// FUNCTION: ENGINE 0x10836B40
	void AddGameState(void* stateObject, int id, int priority, int flag, int mode, int parent)
	{
		GameState* state = (GameState*)stateObject;
		if (state->id == 0)
		{
			state->id = id;
		}
		GameStateEntry entry(state, id, priority, flag, mode, parent);
		gGameStates[id] = entry;
	}

	// The vector of the machine's lists (begin, end of the elements and end of the storage; the members' names are
	// guesses, the shapes follow the instances the unit keeps)
	struct EmptyAllocator
	{
	};

	template<class T> inline void CopyElement(T* to, const T* from)
	{
		*to = *from;
	}

	template<class T> inline T* AssignElements(const T* first, const T* last, T* to)
	{
		for (; first != last; first++, to++)
		{
			*to = *first;
		}
		return to;
	}

	template<class T> inline void ConstructElements(T* to, int count, const T& value)
	{
		T* element = to;
		while (count != 0)
		{
			count--;
			if (element != 0)
			{
				new (element) T(value);
			}
			element++;
		}
	}

	template<class T> inline void ConstructElementAt(T* to, const T& value)
	{
		if (to != 0)
		{
			new (to) T(value);
		}
	}

	template<class T> class StateVector
	{
	public:
		StateVector(unsigned int count, const EmptyAllocator& allocator);
		bool Create(unsigned int count);
		void Reset();
		~StateVector();
		void ShiftUp(T* position, int count);
		T* Insert(T* position, int count, const T& value);
		inline T* Insert(T* position, const T& value);
		inline T* Erase(T* position);
		inline void RemoveAt(T* position);
		inline T* Begin();
		inline T* End();
		inline int Size() const;
		inline T& operator[](int index);

		T* begin;
		T* end;
		T* capacity;
	};

	template<class T> StateVector<T>::StateVector(unsigned int count, const EmptyAllocator& allocator)
	{
		if (count != 0)
		{
			begin = (T*)operator new[](count * sizeof(T));
			if (begin != 0)
			{
				capacity = begin + count;
				end = begin;
				return;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacity = 0;
	}

	template<class T> bool StateVector<T>::Create(unsigned int count)
	{
		if (count != 0)
		{
			begin = (T*)operator new[](count * sizeof(T));
			if (begin != 0)
			{
				capacity = begin + count;
				end = begin;
				return true;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacity = 0;
		return false;
	}

	template<class T> void StateVector<T>::Reset()
	{
		end = begin;
	}

	template<class T> StateVector<T>::~StateVector()
	{
		end = begin;
		if (begin != 0)
		{
			operator delete[](begin);
		}
	}

	template<class T> void StateVector<T>::ShiftUp(T* position, int count)
	{
		T* from = end;
		end += count;
		T* to = end;
		while (from != position)
		{
			from--;
			to--;
			ConstructElementAt(to, *from);
		}
	}

	template<class T> T* StateVector<T>::Insert(T* position, int count, const T& value)
	{
		T* result = end;
		if (end + count <= capacity)
		{
			ShiftUp(position, count);
			ConstructElements(position, count, value);
			result = position;
		}
		return result;
	}

	template<class T> inline T* StateVector<T>::Insert(T* position, const T& value)
	{
		T* result = end;
		if (end + 1 <= capacity)
		{
			ShiftUp(position, 1);
			ConstructElements(position, 1, value);
			result = position;
		}
		return result;
	}

	template<class T> inline void StateVector<T>::RemoveAt(T* position)
	{
		T* to = position;
		T* from = position + 1;
		if (from != end)
		{
			while (from != end)
			{
				*to = *from;
				from++;
				to++;
			}
		}
		end--;
	}

	template<class T> inline T* StateVector<T>::Erase(T* position)
	{
		AssignElements(position + 1, end, position);
		end--;
		return position;
	}

	template<class T> inline T* StateVector<T>::Begin()
	{
		return begin;
	}

	template<class T> inline T* StateVector<T>::End()
	{
		return end;
	}

	template<class T> inline int StateVector<T>::Size() const
	{
		return end - begin;
	}

	template<class T> inline T& StateVector<T>::operator[](int index)
	{
		return begin[index];
	}

	// The vector of the state stack, with the older erase
	class IntVector
	{
	public:
		// 0x10685380 (another unit): the place of the value in the list, or its end
		int* Unknown10685380(const int* value);
		// 0x1007B160 (another unit): appends
		void Unknown1007B160(const int* value);

		void Erase(int* position)
		{
			int* to = position;
			int* from = position + 1;
			if (from != end)
			{
				while (from != end)
				{
					*to = *from;
					from++;
					to++;
				}
			}
			end--;
		}

		int* begin;
		int* end;
		int* capacity;
	};

	// FUNCTION: ENGINE 0x10836E70
	// FUNCTION: ENGINE 0x10836E80
	// FUNCTION: ENGINE 0x10836FB0
	// FUNCTION: ENGINE 0x10837090
	// FUNCTION: ENGINE 0x10837170
	// FUNCTION: ENGINE 0x10837660
	// FUNCTION: ENGINE 0x108376B0
	// FUNCTION: ENGINE 0x108377B0
	// FUNCTION: ENGINE 0x108377E0
	// FUNCTION: ENGINE 0x108378D0
	// FUNCTION: ENGINE 0x10837B90
	// FUNCTION: ENGINE 0x10837C20
	// FUNCTION: ENGINE 0x10838630
	template class StateVector<TaskEntry>;
	// FUNCTION: ENGINE 0x10836E90
	// FUNCTION: ENGINE 0x10836EA0
	// FUNCTION: ENGINE 0x10836F40
	// FUNCTION: ENGINE 0x108370E0
	// FUNCTION: ENGINE 0x108371A0
	// FUNCTION: ENGINE 0x108376E0
	// FUNCTION: ENGINE 0x10837730
	// FUNCTION: ENGINE 0x108377C0
	// FUNCTION: ENGINE 0x10837830
	// FUNCTION: ENGINE 0x10837910
	// FUNCTION: ENGINE 0x10837BB0
	// FUNCTION: ENGINE 0x10837C60
	// FUNCTION: ENGINE 0x10838670
	template class StateVector<SimulationTaskEntry>;
	// FUNCTION: ENGINE 0x10836EB0
	// FUNCTION: ENGINE 0x10836EC0
	// FUNCTION: ENGINE 0x10836ED0
	// FUNCTION: ENGINE 0x10836EF0
	// FUNCTION: ENGINE 0x10837760
	// FUNCTION: ENGINE 0x108377D0
	// FUNCTION: ENGINE 0x10837880
	// FUNCTION: ENGINE 0x10837BD0
	// FUNCTION: ENGINE 0x10837BF0
	// FUNCTION: ENGINE 0x10837CA0
	// FUNCTION: ENGINE 0x108386B0
	// FUNCTION: ENGINE 0x10838960
	// FUNCTION: ENGINE 0x108389A0
	template class StateVector<GameStateRequest>;
	template void ConstructElements<TaskEntry>(TaskEntry*, int, const TaskEntry&);

	// The callbacks that are told when a switch is over, and that are destroyed afterwards (virtual destructor)
	class StateCallback
	{
	public:
		virtual ~StateCallback();
	};

	extern StateVector<GameStateRequest>* gPendingRequests;       // 0x1130DFB8
	extern StateVector<TaskEntry>* gRealTimeTasks;                // 0x1130DFC0
	extern StateVector<SimulationTaskEntry>* gSimulationTasks;    // 0x1130DFC4
	extern IntVector* gStateStack;                                // 0x1130DFCC
	extern StateCallback* gTransitionStateCallback;               // 0x1130DFFC
	extern unsigned int gMessageEnter;                            // 0x111C6428
	extern unsigned int gMessageReplace;                          // 0x111C642C
	extern unsigned int gMessageLeave;                            // 0x111C6430
	extern unsigned int gMessageReturn;                           // 0x111C6434

	// FUNCTION: ENGINE 0x108366D0
	GameState::GameState(int newId, int newStackSize) : id(newId), running(0), stackSize(newStackSize)
	{
	}

	// FUNCTION: ENGINE 0x10836BA0
	GameState* GetGameState(int id)
	{
		return gGameStates[id].state;
	}

	// FUNCTION: ENGINE 0x10836BC0
	void RemoveGameState(int id)
	{
		GameStateName* entry = &gRequestNames[id];
		entry->state = 0;
		entry->name.Clear();
	}

	// FUNCTION: ENGINE 0x10836BE0
	// EQUIVALENT: the engine loads the table pointer before the two tests and forms the name address with lea, this compiler loads it later and addresses the entry in the load (54 %); same loads and stores
	void GetRequestName(int index, int* state, const char** name)
	{
		GameStateName* names = gRequestNames;
		if (state != 0)
		{
			*state = names[index].state;
		}
		if (name != 0)
		{
			GameStateName* entry = &names[index];
			*name = entry->name.Data();
		}
	}

	// FUNCTION: ENGINE 0x10836C20
	int GetCurrentRequestName()
	{
		return gCurrentRequestName;
	}

	// FUNCTION: ENGINE 0x10836C30
	void RequestTransition(unsigned int id, StateCallback* callback)
	{
		if (gTransitionState != 0)
		{
			if (callback != 0)
			{
				callback->~StateCallback();
			}
		}
		else
		{
			gTransitionStateCallback = callback;
			unsigned int message = ((gMessageReturn | 0x100) << 16) | id;
			gTransitionState = 7;
			gTransitionMessage = message;
			Unknown108C7750()->Unknown108C7B50(message, 0);
		}
	}

	// FUNCTION: ENGINE 0x10836C90
	bool IsMessageSent(unsigned int id)
	{
		if (Unknown108C7750()->Unknown108C7820(((gMessageEnter | 0x100) << 16) | id))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10836CD0
	bool IsRealTimeStepping()
	{
		if (gTransitionState != 3 && gTransitionState != 4 && (gStateFlags & 4) != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10836CF0
	bool IsSimulationPaused()
	{
		if (gTransitionState != 3 && gTransitionState != 4 && (gStateFlags & 8) != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10836D10
	void StartSimulationDriver()
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->Unknown10897DC0(true);
		}
	}

	// FUNCTION: ENGINE 0x10836D40
	void StopSimulationDriver()
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->Unknown10897DC0(false);
		}
	}

	// FUNCTION: ENGINE 0x10836D70
	bool IsSimulationDriverRunning()
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			return driver->Unknown10897DB0();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10836DA0
	void ResetSimulationDriver()
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->Unknown10897DE0(-1);
		}
	}

	// FUNCTION: ENGINE 0x10836DD0
	void SetSimulationDriverValue(int value)
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->SetUnknown70(value);
		}
	}

	// FUNCTION: ENGINE 0x10836E00
	void SetSimulationDriverOther(int value)
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->Unknown10897DD0(value);
		}
	}

	// FUNCTION: ENGINE 0x10836E30
	void SetSimulationDriverScale(float value)
	{
		SimulationDriver* driver = dynamic_cast<SimulationDriver*>(GetSimulationDriver());
		if (driver != 0)
		{
			driver->SetScaleB(value);
		}
	}

	// The object 0x10890930 answers (its byte at +0x26 keeps some request away; names guessed)
	struct StateGate
	{
		unsigned char unknown0[0x26];
		bool unknown26;
	};
	StateGate* Unknown10890930();

	// The front end's request line (0x10864330 answers the front end; the names are guesses)
	class FrontEnd
	{
	public:
		void Unknown10872920(const char* name);
	};
	FrontEnd* Unknown10864330();

	// The state stack's push (0x1007B160) and search (0x10685380)
	class StateStackOps
	{
	};

	// FUNCTION: ENGINE 0x10837CE0
	bool GameState::RunEnter()
	{
		return Run(1);
	}

	// FUNCTION: ENGINE 0x10837CF0
	bool GameState::RunLeave()
	{
		return Run(2);
	}


	// The way a state stands in the machine (0: no such state, 1: free, 2: the first kind of overlay, 3: the second,
	// 4: waiting to be entered, 5: on the stack but not the top); 0x108373B0
	// FUNCTION: ENGINE 0x108373B0
	// EQUIVALENT: the engine keeps the id in ebx where this compiler reloads it from the stack (33 %); the same tests, loads and calls in the same order
	int GetGameStateStatus(int id)
	{
		if (id == 0)
		{
			return 0;
		}
		GameState* state = gGameStates[id].state;
		if (state == 0)
		{
			return 0;
		}
		if (state->running == 1)
		{
			return 2;
		}
		if (state->running == 2)
		{
			return 3;
		}
		IntVector* stack = gStateStack;
		if (stack->Unknown10685380(&id) != stack->end)
		{
			return 5;
		}
		StateVector<GameStateRequest>* pending = gPendingRequests;
		for (unsigned int i = 0; i < (unsigned int)pending->Size(); i++)
		{
			if ((*pending)[i].state == id)
			{
				return 4;
			}
		}
		if (gTransitionState == 0 || gCurrentRequest.state != id)
		{
			return 1;
		}
		return 4;
	}

	// FUNCTION: ENGINE 0x10837470
	// EQUIVALENT: the registers of the stack pointer and of the end are swapped (14 %); the same loads and tests in the same order
	bool IsGameStateOnTop(int id)
	{
		IntVector* stack = gStateStack;
		if (stack->begin != stack->end)
		{
			GameStateEntry* entry = &gGameStates[stack->end[-1]];
			if (entry->id == id)
			{
				GameState* state = entry->state;
				if (state != 0 && state->running != 1 && state->running != 2)
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108374B0
	// EQUIVALENT: the engine tests the transition state against an immediate, this compiler against a zeroed register (82 %)
	bool HasPendingStateChange()
	{
		if (gPendingRequests->Size() != 0)
		{
			return true;
		}
		return gTransitionState != 0;
	}

	// FUNCTION: ENGINE 0x108374E0
	// EQUIVALENT: the two returns sit in the other order (42 %); the same tests
	bool IsStateMachineBusy()
	{
		IntVector* stack = gStateStack;
		if (stack->end - stack->begin == 0)
		{
			if (gPendingRequests->Size() == 0)
			{
				return gTransitionState != 0;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10837560
	void ServicePendingRequest()
	{
		if (gCurrentRequestName != 0 && GetGameStateStatus(gRequestNames[gCurrentRequestName].state) == 5)
		{
			FrontEnd* frontEnd = Unknown10864330();
			if (frontEnd != 0)
			{
				if (!gRequestNames[gCurrentRequestName].name.IsEmpty())
				{
					frontEnd->Unknown10872920(gRequestNames[gCurrentRequestName].name.Data());
				}
				gCurrentRequestName = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x10837B10
	// EQUIVALENT: the engine adds the entry address to the table pointer held in a register where this compiler adds the memory operand (68 %); the same stores
	void FreeGameState(int id)
	{
		int status = GetGameStateStatus(id);
		if (status != 0 && status == 1)
		{
			GameStateEntry* entry = &gGameStates[id];
			entry->id = 0;
			entry->state = 0;
		}
	}

	// FUNCTION: ENGINE 0x10837B40
	void SetGameStateScreen(int index, int state, const char* name)
	{
		GameStateName* entry = &gRequestNames[index];
		entry->state = state;
		if (name != 0)
		{
			int length = core::StrLen(name) + 1;
			if (length > 0x20)
			{
				length = 0x20;
			}
			core::StrNCpy(entry->name.buffer, name, (unsigned int)length);
			return;
		}
		entry->name.buffer[0] = 0;
	}

	// FUNCTION: ENGINE 0x10837A50
	void RemoveRealTimeTask(IRealTimeTask* task)
	{
		StateVector<TaskEntry>* list = gRealTimeTasks;
		TaskEntry* entry = list->begin;
		TaskEntry* end = list->end;
		if (entry < end)
		{
			do
			{
				if (entry->task == task)
				{
					{
						TaskEntry* to = entry;
						TaskEntry* from = entry + 1;
						TaskEntry* last = list->end;
						if (from != last)
						{
							while (from != last)
							{
								*to = *from;
								from++;
								to++;
							}
						}
						list->end--;
					}
					return;
				}
				entry++;
			}
			while (entry < end);
		}
	}

	// FUNCTION: ENGINE 0x10837AB0
	void RemoveSimulationTask(IRealTimeTask* task)
	{
		StateVector<SimulationTaskEntry>* list = gSimulationTasks;
		SimulationTaskEntry* entry = list->begin;
		SimulationTaskEntry* end = list->end;
		if (entry < end)
		{
			do
			{
				if (entry->task == task)
				{
					{
						SimulationTaskEntry* to = entry;
						SimulationTaskEntry* from = entry + 1;
						SimulationTaskEntry* last = list->end;
						if (from != last)
						{
							while (from != last)
							{
								*to = *from;
								from++;
								to++;
							}
						}
						list->end--;
					}
					return;
				}
				entry++;
			}
			while (entry < end);
		}
	}

	// FUNCTION: ENGINE 0x108388A0
	// EQUIVALENT: the priority is reloaded into ecx after the shift-up call where the engine uses eax (98 %)
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data)
	{
		StateVector<TaskEntry>* list = gRealTimeTasks;
		TaskEntry* entry = list->begin;
		while (entry < list->end && priority >= (int)entry->priority)
		{
			entry++;
		}
		TaskEntry value = { task, mask, priority, data };
		list->Insert(entry, value);
	}

	// FUNCTION: ENGINE 0x10838900
	// EQUIVALENT: the priority is reloaded into ecx after the shift-up call where the engine uses eax (98 %)
	void AddSimulationTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data)
	{
		StateVector<SimulationTaskEntry>* list = gSimulationTasks;
		SimulationTaskEntry* entry = list->begin;
		while (entry < list->end && priority >= (int)entry->priority)
		{
			entry++;
		}
		SimulationTaskEntry value = { task, mask, priority, data };
		list->Insert(entry, value);
	}

	void YieldFiber();

	// The body of the fiber a state runs in: enters the state or leaves it, works out the flags of the states that
	// stay on the stack, and gives the thread back
	// FUNCTION: ENGINE 0x10837200
	// EQUIVALENT: the engine zeroes the mask with an immediate and stores the running word after popping the saved registers, this compiler shares a zeroed register and stores before the pops (55 %); the same operations in the same order
	void RunStateFiber(GameState* state)
	{
		if (state->running == 1)
		{
			gGameStates[state->id].flagMask = 0;
			state->Enter();
			gGameStates[state->id].savedFlags = gStateFlags;
			state->running = 0;
			YieldFiber();
			return;
		}
		state->Leave();
		IntVector* stack = gStateStack;
		int* begin = stack->begin;
		int* end = stack->end;
		int* position = begin;
		while (position != end && *position != state->id)
		{
			position++;
		}
		unsigned int flags = 1;
		if (position != begin)
		{
			flags = gGameStates[position[-1]].savedFlags;
		}
		gStateFlags = flags;
		int* next = position + 1;
		if (next < end)
		{
			do
			{
				GameStateEntry* entry = &gGameStates[*next];
				flags = (entry->savedFlags & entry->flagMask) | (~entry->flagMask & flags);
				next++;
			}
			while (next < end);
			gStateFlags = flags;
		}
		state->running = 0;
		YieldFiber();
	}

	// FUNCTION: ENGINE 0x10837990
	bool GameState::Run(int mode)
	{
		if (running == 0)
		{
			core::CreateFiber(&fiber, (int (*)(void*))RunStateFiber, this, stackSize, 0, 0);
			running = mode;
		}
		DesyncHunter::PushMode(0);
		core::SwitchFiber(&fiber);
		DesyncHunter::PopMode();
		if (running == 0)
		{
			core::DestroyFiber(&fiber);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108366F0
	void YieldFiber()
	{
		core::SwitchFiber(gMainFiber);
	}

	// FUNCTION: ENGINE 0x108382B0
	// EQUIVALENT: the registers of the list and of the callback are swapped (90 %)
	void CancelStateRequest(int state)
	{
		if (gTransitionState == 1 && gCurrentRequest.state == state)
		{
			gCurrentRequest.unknownD = true;
			gCurrentRequest.started = false;
			Unknown108C7750()->Unknown108C7BE0(gTransitionMessage);
			return;
		}
		StateVector<GameStateRequest>* pending = gPendingRequests;
		GameStateRequest* request = pending->begin;
		GameStateRequest* end = pending->end;
		if (request != end)
		{
			do
			{
				if (request->state == state)
				{
					SyncCommands::SyncCallback* callback = request->callback;
					pending->Erase(request);
					if (callback != 0)
					{
						callback->OnFinished(state, false);
					}
					return;
				}
				request++;
			}
			while (request != end);
		}
	}

	void StartNextRequest();

	// FUNCTION: ENGINE 0x10838340
	// NONMATCHING: the mode switch is laid out in the other order (63 %); the transitions themselves are written out
#ifdef NONMATCHING
	void StartNextRequest()
	{
		StateVector<GameStateRequest>* pending = gPendingRequests;
		gCurrentRequest = pending->begin[0];
		pending->Erase(pending->begin);
		if (gCurrentRequest.mode == 0)
		{
			gTransitionMessage = ((gMessageEnter | 0x100) << 16) | gCurrentRequest.state;
			gTransitionState = 1;
			if (gCurrentRequest.overlay)
			{
				gTransitionMessage |= 0x8000;
			}
			unsigned int message = gTransitionMessage;
			Unknown108C7750()->Unknown108C7B50(message, &gCurrentRequest);
		}
		else if (gCurrentRequest.mode == 1)
		{
			gTransitionMessage = ((gMessageReplace | 0x100) << 16) | gCurrentRequest.state;
			gTransitionState = 2;
			if (gCurrentRequest.overlay)
			{
				gTransitionMessage |= 0x8000;
			}
			unsigned int message = gTransitionMessage;
			Unknown108C7750()->Unknown108C7B50(message, 0);
		}
		else if (gCurrentRequest.mode == 2)
		{
			gTransitionState = 5;
			if (gCurrentRequest.state == 0)
			{
				DesyncHunter::StopInstance();
				return;
			}
			if (gGameStates[gCurrentRequest.state].flag == 0 && !gCurrentRequest.overlay)
			{
				DesyncHunter::StopInstance();
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10838490
	bool PopGameState()
	{
		GameStateEntry* entry = &gGameStates[gStateStack->end[-1]];
		if (entry->state->RunLeave())
		{
			IntVector* stack = gStateStack;
			if (stack->begin != stack->end)
			{
				stack->end--;
			}
			return true;
		}
		return false;
	}

	bool RemoveGameStateFromStack(int id);

	// FUNCTION: ENGINE 0x108384D0
	// NONMATCHING: the search loop and the erase are laid out differently (34 %)
#ifdef NONMATCHING
	bool RemoveGameStateFromStack(int id)
	{
		IntVector* stack = gStateStack;
		int* position = stack->begin;
		int* end = stack->end;
		GameStateEntry* entry = &gGameStates[id];
		if (position != end)
		{
			while (*position != id)
			{
				position++;
				if (position == end)
				{
					break;
				}
			}
			if (position != end)
			{
				if (!entry->state->RunLeave())
				{
					return false;
				}
				IntVector* list = gStateStack;
				list->Erase(position);
			}
		}
		return true;
	}
#endif

	bool GotoGameState(int id);

	// FUNCTION: ENGINE 0x10838540
	// NONMATCHING: the control flow around the stack search is laid out differently (25 %)
#ifdef NONMATCHING
	bool GotoGameState(int id)
	{
		IntVector* stack = gStateStack;
		int* begin = stack->begin;
		int* end = stack->end;
		if (begin != end && end[-1] == id)
		{
			return true;
		}
		if (id == 0)
		{
			PopGameState();
			return gStateStack->begin == gStateStack->end;
		}
		GameStateEntry* entry = &gGameStates[id];
		if (begin == end || (entry->mode != 1 && stack->Unknown10685380(&id) == end))
		{
			if (entry->mode == 0)
			{
				int* position = begin;
				if (position != end)
				{
					while (*position != id)
					{
						position++;
						if (position == end)
						{
							break;
						}
					}
					if (position != end)
					{
						goto leave;
					}
				}
			}
			if (entry->mode == 2 && (begin == end || end[-1] != entry->parent))
			{
				GotoGameState(entry->parent);
				return false;
			}
			if (entry->state->RunEnter())
			{
				gStateStack->Unknown1007B160(&id);
				return true;
			}
		}
		else
		{
		leave:
			if (PopGameState())
			{
				IntVector* list = gStateStack;
				if (list->begin != list->end && id == list->end[-1])
				{
					return true;
				}
			}
		}
		return false;
	}
#endif

	void RequestGameStateInternal(int state, int mode, SyncCommands::SyncCallback* callback, bool overlay);

	// FUNCTION: ENGINE 0x108389D0
	// NONMATCHING: the checks and the insertion are laid out differently (33 %)
#ifdef NONMATCHING
	void RequestGameStateInternal(int state, int mode, SyncCommands::SyncCallback* callback, bool overlay)
	{
		StateVector<GameStateRequest>* pending = gPendingRequests;
		unsigned int count = pending->Size();
		for (unsigned int i = 0; i < count; i++)
		{
			if ((*pending)[i].state == state && (*pending)[i].overlay == overlay)
			{
				goto already;
			}
		}
		if (gTransitionState == 0 || gCurrentRequest.state != state || gCurrentRequest.overlay != overlay)
		{
			GameStateEntry* table = gGameStates;
			GameStateRequest request;
			request.state = state;
			request.callback = callback;
			request.mode = mode;
			request.overlay = overlay;
			unsigned int priority;
			if (state == 0)
			{
				priority = 0x29;
			}
			else
			{
				priority = table[state].priority;
			}
			GameStateRequest* position = pending->begin;
			GameStateRequest* end = pending->end;
			while (position != end && priority <= (unsigned int)table[position->state].priority)
			{
				position++;
			}
			pending->Insert(position, request);
			if (gTransitionState == 0)
			{
				StartNextRequest();
				return;
			}
			if (gTransitionState == 1 && (unsigned int)table[gCurrentRequest.state].priority < priority)
			{
				if (!gCurrentRequest.unknownD)
				{
					gCurrentRequest.started = true;
					gCurrentRequest.unknownD = true;
				}
				Unknown108C7750()->Unknown108C7BE0(gTransitionMessage);
			}
			return;
		}
	already:
		if (callback != 0)
		{
			callback->OnFinished(state, false);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10838B40
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback)
	{
		if (state == 2 && Unknown10890930() != 0 && Unknown10890930()->unknown26)
		{
			return;
		}
		RequestGameStateInternal(state, mode, callback, false);
	}

	// FUNCTION: ENGINE 0x10838B80
	void RequestGameStateOverlay(int state, int mode, SyncCommands::SyncCallback* callback)
	{
		RequestGameStateInternal(state, mode, callback, true);
	}

	// FUNCTION: ENGINE 0x108391A0
	// EQUIVALENT: the engine forms the entry offset before it stores the request name, this compiler after (89 %)
	void RequestGameStateByIndex(int index, int mode)
	{
		gCurrentRequestName = index;
		RequestGameState(gRequestNames[index].state, mode, 0);
	}

	// FUNCTION: ENGINE 0x108390F0
	// EQUIVALENT: the engine stores the transition state after the size of the pending list is computed, this compiler before (85 %)
	void GameStateRequest::OnFinished(int newState, bool wasAborted)
	{
		if (!wasAborted)
		{
			if (gCurrentRequest.started)
			{
				gTransitionState = 0;
				if (gCurrentRequest.overlay)
				{
					RequestGameStateOverlay(gCurrentRequest.state, 0, 0);
					return;
				}
				RequestGameState(gCurrentRequest.state, 0, gCurrentRequest.callback);
				return;
			}
			if (gCurrentRequest.callback != 0)
			{
				gCurrentRequest.callback->OnFinished(gCurrentRequest.state, false);
			}
			bool more = gPendingRequests->Size() != 0;
			gTransitionState = 0;
			if (more)
			{
				StartNextRequest();
			}
		}
		else
		{
			aborted = true;
		}
	}
}

// Kept copies (inline members of this unit's classes):
// FUNCTION: ENGINE 0x10836690
// FUNCTION: ENGINE 0x108367E0
// FUNCTION: ENGINE 0x10837520
// FUNCTION: ENGINE 0x10837950
