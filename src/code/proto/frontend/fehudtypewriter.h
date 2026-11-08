// proto::FEHUDTypewriter (RTTI name; base engine::IRealTimeTask): the typewriter of the head-up display. It takes a text
// (the key of a localised text), writes it letter by letter into the front end's movie and reports when it is done; it runs
// as a real time task while it types. The scripts start and stop it and set its speeds. The movie paths and script names are
// original, the member names are guessed. Unit 0x104D9720 - 0x104DA5A0 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDTYPEWRITER_H
#define PROTO_FRONTEND_FEHUDTYPEWRITER_H

#include "code/engine/gamestate.h"
#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHUDTypewriter : public engine::IRealTimeTask
	{
	public:
		// 0x104DA760
		FEHUDTypewriter();
		// 0x104DA160
		~FEHUDTypewriter();

		// vftable slot 0 (0x104D9B10)
		virtual void Update(engine::UpdateContext context);

		// 0x104D9740: writes the variables that changed (or all of them when forced)
		void Update(bool force);
		// 0x104D9A90: puts the typewriter among the real time tasks, or takes it out
		void SetTaskActive(bool active);
		// 0x104D9790: the scripts' fe_StartTypeWriter (the last three arguments are not used)
		void Start(const char* key, float new13A8, float new13A4, float unused1, const char* unused2, float unused3,
			const char* unused4);
		// 0x104D98A0
		void StartText(const char* key, float new13A8, float new13A4, bool newUnknown13B1);
		// 0x104D9900: the scripts' fe_StopTypeWriter
		void Stop();
		// 0x104D99C0: the scripts' fe_TypeWriterOutroComplete
		void OutroComplete();
		// 0x104D9990: the scripts' fe_SetTypeWriterSpeeds
		void SetSpeeds(float new13A0, float new13AC);
		// 0x104D9980: the scripts' fe_GetIsTypeWriterActive
		bool IsActive();
		// 0x104D9780
		void SetUnknown13B0(bool value);

		FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 1> text;  // +8
		FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 1> shadowText;  // +0x130
		FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 1> visible;  // +0x258
		float unknown380;
		float unknown384;
		float unknown388;
		int state;  // +0x38C: 3 stopping, 4 stopped
		bool taskActive;  // +0x390
		unsigned char unknown391;
		unsigned short buffer[0x200];  // +0x392
		unsigned char unknown792[0x1394 - 0x792];
		int characterCount;  // +0x1394
		int unknown1398;
		bool unknown139C;
		float unknown13A0;
		float unknown13A4;
		float unknown13A8;
		float unknown13AC;
		bool unknown13B0;
		bool unknown13B1;
	};
}

#endif
