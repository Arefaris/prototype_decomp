// engine::DBObserver (RTTI name), the base of engine::camera::Director: two virtual functions taking two arguments
// and no virtual destructor (the Director's destructor is the first one in the hierarchy and takes slot 2; its
// destructor stores no base vftable). The names and the meaning of the arguments are unknown.
#ifndef ENGINE_DBOBSERVER_H
#define ENGINE_DBOBSERVER_H

namespace engine
{
	class DBObserver
	{
	public:
		virtual void OnDBSlot0(int a, int b) = 0;
		virtual void OnDBSlot1(int a, int b);
	};
}

#endif
