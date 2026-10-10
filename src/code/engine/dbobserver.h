// engine::DBObserver (RTTI name), the base of engine::camera::Director. Two virtual functions precede the virtual
// destructor in its vftable (Director::Shutdown deletes through slot 2); their names and signatures are unknown.
#ifndef ENGINE_DBOBSERVER_H
#define ENGINE_DBOBSERVER_H

namespace engine
{
	class DBObserver
	{
	public:
		virtual void OnDBSlot0() = 0;
		virtual void OnDBSlot1() = 0;
		virtual ~DBObserver()
		{
		}
	};
}

#endif
