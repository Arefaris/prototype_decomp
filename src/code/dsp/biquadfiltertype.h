// The kinds of biquad filter of the dsp library (RTTI: dsp::BiQuadFilterType, an enumeration; the names are the reflection's)
#ifndef DSP_BIQUADFILTERTYPE_H
#define DSP_BIQUADFILTERTYPE_H

namespace dsp
{
	enum BiQuadFilterType
	{
		BiQuadFilterType_LowPass,
		BiQuadFilterType_HighPass,
		BiQuadFilterType_BandPass1,
		BiQuadFilterType_BandPass2,
		BiQuadFilterType_Notch,
		BiQuadFilterType_AllPass,
		BiQuadFilterType_PeakingEq,
		BiQuadFilterType_LowShelf,
		BiQuadFilterType_HighShelf
	};
}

#endif
