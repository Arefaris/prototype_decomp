// The property nodes of the mgraph library (0x10B37990 - 0x10B40000): the constructors, in the order the compiler emitted them.
#include "code/mgraph/propertynodector.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// Left to the engine (their symbols are mapped): the slots of these property nodes that do not match
	template<> om::DelegatePropertyBase* mgraph::PropertyNode<mgraph::Packet<bool> >::CreateDelegate(unsigned int);
	template<> om::DelegatePropertyBase* mgraph::PropertyNode<mgraph::Packet<float> >::CreateDelegate(unsigned int);
	template<> om::DelegatePropertyBase* mgraph::PropertyNode<mgraph::Packet<String> >::CreateDelegate(unsigned int);
	template<> om::DelegatePropertyBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::CreateDelegate(unsigned int);
	template<> om::DelegatePropertyBase* mgraph::PropertyNode<mgraph::Packet<Vector> >::CreateDelegate(unsigned int);
	template<> void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetNumChannels(unsigned int);
	template<> void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);

	// FUNCTION: ENGINE 0x10B37990
	template mgraph::PropertyNode<mgraph::Packet<bool> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
	// FUNCTION: ENGINE 0x10B383E0
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B38FD0
	template mgraph::PropertyNode<mgraph::Packet<float> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
	// FUNCTION: ENGINE 0x10B39A60
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B3A690
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B3B350
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B3C030
	template mgraph::PropertyNode<mgraph::Packet<String> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
	// FUNCTION: ENGINE 0x10B3CB20
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
	// FUNCTION: ENGINE 0x10B3D800
	template mgraph::PropertyNode<mgraph::Packet<Vector> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
	// FUNCTION: ENGINE 0x10B3E3B0
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B3F080
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
	// FUNCTION: ENGINE 0x10B3FD50
	// NONMATCHING: 71 %, the destructor of the temporary array packet stores a zero into its data word before releasing it, the engine's does not
#ifdef NONMATCHING
	template mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short>> >::PropertyNode(mgraph::Graph*, Name<CaseSensitive64BitKey> const&, mgraph::NodeTypeBase*);
#endif
}
