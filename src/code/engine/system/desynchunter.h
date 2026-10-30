// engine::DesyncHunter (RTTI name, 4 vftable slots; engine::DesyncHunterOnline derives from it): watches the
// simulation for a desynchronisation between the machines of an online game. It owns a checker (another unit) that
// records the state of the game objects; Update resets or verifies it, depending on the mode. A global instance
// pointer lets the rest of the engine start, stop and update the hunt without knowing the class. Unit 0x108214D0 -
// 0x10821720 (no assert path; the file name is a guess); the names other than the class's are guesses.
#ifndef ENGINE_SYSTEM_DESYNCHUNTER_H
#define ENGINE_SYSTEM_DESYNCHUNTER_H

namespace engine
{
	// The recorder of the game object state the hunter compares (0x34 bytes; constructor 0x108BFA80, destructor
	// 0x108BFAF0, Reset 0x108BFBC0 and Verify 0x108BFBD0 in the online manager's unit)
	class DesyncChecker
	{
	public:
		DesyncChecker(int size, int count, bool flag);
		~DesyncChecker();
		void Reset();
		void Verify();
		// 0x108214D0: the value the last check ended with
		unsigned int GetValue() const
		{
			return value;
		}

		unsigned char unknown0[0x20];
		unsigned int value;
		unsigned char unknown24[0x34 - 0x24];
	};

	// The settings the checker is made from (0x11318538; the fields the hunter reads are at +0x8, +0xC and +0x18)
	struct DesyncSettings
	{
		unsigned char unknown0[8];
		int size;
		int count;
		unsigned char unknown10[8];
		bool flag;
		unsigned char unknown19[3];
		// The heap the online manager's objects are made in once the settings ask for the desync heap
		int heap;  // +0x1C
	};

	// The engine's instance of the settings (0x11318538; another unit defines it)
	extern DesyncSettings gDesyncSettings;

	class DesyncHunter
	{
	public:
		DesyncHunter();
		virtual ~DesyncHunter();
		// Slot 1: Update resets the checker; slot 2: it stops
		virtual void Start();
		virtual void Stop();
		virtual void Update();

		// The mode and the stack of modes the callers push (0x111C3054 / 0x1130CCE8)
		static void PushMode(unsigned char mode);
		static void PopMode();
		static unsigned char GetMode();
		static DesyncSettings* GetSettings();
		static void RecordThread();
		// The instance the engine drives (0x1130CCF8) and the calls the other units make on it
		static void SetInstance(DesyncHunter* hunter);
		static DesyncHunter* GetInstance();
		static void UpdateInstance();
		static void StartInstance();
		static void StopInstance();

		// 0: stopped, 1: the checker is reset on every update, 2: it is verified
		int state;
		DesyncChecker* checker;
		unsigned int last;

		static DesyncHunter* sInstance;
		static int sThread;
		static unsigned char sModeStack[10];
		static unsigned int sModeDepth;
		static unsigned char sMode;
	};
}

#endif
