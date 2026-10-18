// ravenphysics::PhysicsContextCallBack (RTTI name): what the physics manager runs around the context's update; its
// one virtual is pure in the base. The callbacks are kept in singly linked lists through the pointer behind the
// vftable. Member names are guesses.
#ifndef RAVENPHYSICS_CALLBACK_H
#define RAVENPHYSICS_CALLBACK_H

namespace ravenphysics
{
	class PhysicsContextCallBack
	{
	public:
		virtual void OnCallback() = 0;
		// 0x1082BD90: links the callback in front of another (or ends the list)
		void SetNext(PhysicsContextCallBack* callback);

		PhysicsContextCallBack* mNext;   // 0x04
	};
}

#endif
