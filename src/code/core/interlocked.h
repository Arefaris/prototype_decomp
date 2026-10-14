// The interlocked compiler intrinsics (the engine's own atomic helpers compile to these).
#ifndef CORE_INTERLOCKED_H
#define CORE_INTERLOCKED_H

extern "C"
{
	long _InterlockedIncrement(long volatile*);
	long _InterlockedDecrement(long volatile*);
	long _InterlockedExchangeAdd(long volatile*, long);
	long _InterlockedCompareExchange(long volatile*, long, long);
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedExchange(long volatile*, long);
}
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchangeAdd, _InterlockedCompareExchange, _InterlockedAnd, _InterlockedExchange)

#endif
