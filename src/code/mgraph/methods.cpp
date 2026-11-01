// The reflected methods of the node classes of the mgraph library (0x10B41860 - 0x10B58000): the Invoke slots of the instances of
// om::MetaMethod0Const<C, B, R> and om::MetaMethod1<C, B, R, A> for the throws, switches, random nodes and property nodes.
#include "code/mgraph/nodes.h"
#include "code/om/invoke.h"
#include "code/om/metamethod.h"

#pragma warning(disable: 4661)

namespace om
{
	using namespace mgraph;

	// FUNCTION: ENGINE 0x10B12170
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12200
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12290
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12320
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B123B0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12440
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B124D0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12560
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B125F0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12680
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12710
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B127A0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12830
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B128C0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12950
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B129E0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12A70
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B12B00
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B2D530
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B2D5E0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B32630
	template void MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B32710
	template void MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41860
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41970
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41AB0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41BF0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41D30
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41E40
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B41F80
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B420C0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B421A0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42280
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42350
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42420
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B424F0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B425C0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42690
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42760
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42830
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42900
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B429D0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42AA0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42B70
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42C40
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42D10
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42DE0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42EB0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B42F80
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B43050
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B470E0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B471B0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47280
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47320
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B473F0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47490
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47560
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47630
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B476D0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B477A0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47870
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47910
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B479E0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47AB0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47B50
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47C20
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47CF0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B47D90
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B54030
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B54100
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B541D0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B54270
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B54340
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B543E0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B544B0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
}
