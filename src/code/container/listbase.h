// container::ListBase (RTTI name: the class whose nested Node the engine's behaviours derive from,
// "container::ListBase::Node@104" in the RTTI of proto::VehicleBehaviour). Only the node is needed so far: it is a
// forward link, so an object that derives from Node sits in one intrusive list per node it owns. Names are guesses.
#ifndef CONTAINER_LISTBASE_H
#define CONTAINER_LISTBASE_H

namespace container
{
	class ListBase
	{
	public:
		class Node
		{
		public:
			Node* next;
		};
	};
}

#endif
