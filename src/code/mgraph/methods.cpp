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
	// FUNCTION: ENGINE 0x10B03E20
	template void om::WriteText(TextValue*, DynamicArray<mgraph::TriggerData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B03F40
	template bool om::ReadBinary(BinaryStream*, DynamicArray<mgraph::TriggerData,unsigned short>*);
	// FUNCTION: ENGINE 0x10B04000
	template bool om::WriteBinary(BinaryStream*, DynamicArray<mgraph::TriggerData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B040A0
	template bool om::ReadText(TextValue const*, DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10B041C0
	template void om::WriteText(TextValue*, DynamicArray<Complex,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B042E0
	template bool om::ReadBinary(BinaryStream*, DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10B043C0
	template bool om::WriteBinary(BinaryStream*, DynamicArray<Complex,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B04460
	template void om::WriteText(TextValue*, DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B04580
	template bool om::WriteBinary(BinaryStream*, DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B2DB90
	template bool MetaProperty<DynamicArray<bool,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B2DC80
	template void MetaProperty<DynamicArray<bool,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B2DD20
	template bool MetaProperty<DynamicArray<bool,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2DD90
	template bool MetaProperty<DynamicArray<bool,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2DDB0
	template void MetaProperty<DynamicArray<float,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B2DE50
	template bool MetaProperty<DynamicArray<float,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2DE70
	template bool MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B2DF60
	template void MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B2E000
	template bool MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2E070
	template bool MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2E090
	template bool MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B2E180
	template void MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B2E220
	template bool MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2E290
	template bool MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2E2B0
	template bool MetaProperty<DynamicArray<Vector,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B2E3A0
	template void MetaProperty<DynamicArray<Vector,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B2E440
	template bool MetaProperty<DynamicArray<Vector,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2E4B0
	template bool MetaProperty<DynamicArray<Vector,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B480A0
	template bool MetaProperty<DynamicArray<float,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B48190
	template bool MetaProperty<DynamicArray<float,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B48200
	template bool MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B482F0
	template void MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B48390
	template bool MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B48400
	template bool MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B48420
	template bool MetaProperty<DynamicArray<Complex,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B48510
	template void MetaProperty<DynamicArray<Complex,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B485B0
	template bool MetaProperty<DynamicArray<Complex,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B48620
	template bool MetaProperty<DynamicArray<Complex,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B487B0
	template void MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B48860
	template bool MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B545D0
	template bool MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B546F0
	template bool MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B2D7C0
	template DynamicArray<bool,unsigned short>* om::ReadArgument<class om::DynamicArray<bool,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B2D860
	template DynamicArray<unsigned int,unsigned short>* om::ReadArgument<class om::DynamicArray<unsigned int,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B2D8E0
	template unsigned __int64* om::ReadArgument<unsigned __int64>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B2D960
	template DynamicArray<unsigned __int64,unsigned short>* om::ReadArgument<class om::DynamicArray<unsigned __int64,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B2DA80
	template DynamicArray<Vector,unsigned short>* om::ReadArgument<class om::DynamicArray<class om::Vector,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B47E60
	template DynamicArray<float,unsigned short>* om::ReadArgument<class om::DynamicArray<float,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B47EF0
	template DynamicArray<mgraph::TriggerData,unsigned short>* om::ReadArgument<class om::DynamicArray<class mgraph::TriggerData,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B47F80
	template DynamicArray<Complex,unsigned short>* om::ReadArgument<class om::DynamicArray<class om::Complex,unsigned short> >(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10B54550
	template DynamicArray<mgraph::EnvelopeData,unsigned short>* om::ReadArgument<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> >(BinaryStream*, GarbageList*);
}
