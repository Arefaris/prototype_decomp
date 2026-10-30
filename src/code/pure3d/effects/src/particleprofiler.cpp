// The counters of the particle profiler (pure3d::particles::profiler; unit around 0x1075D210 - 0x1075D4E0, the file name
// is a guess): the particle code adds to them while it runs. Names are guesses.
namespace pure3d
{
	namespace particles
	{
		namespace profiler
		{
			// 0x11282BA0, 0x11282BAC, 0x11282BB0, 0x11282BB4, 0x11282BB8
			int gCounter0;
			int gCounter1;
			int gCounter2;
			int gCounter3;
			int gCounter4;

			// FUNCTION: ENGINE 0x1075D2E0
			void AddCounter0(int count)
			{
				gCounter0 += count;
			}

			// FUNCTION: ENGINE 0x1075D2F0
			void AddCounter1(int count)
			{
				gCounter1 += count;
			}

			// FUNCTION: ENGINE 0x1075D300
			void AddCounter2(int count)
			{
				gCounter2 += count;
			}

			// FUNCTION: ENGINE 0x1075D310
			void AddCounter3(int count)
			{
				gCounter3 += count;
			}

			// FUNCTION: ENGINE 0x1075D320
			void AddCounter4(int count)
			{
				gCounter4 += count;
			}
		}
	}
}
