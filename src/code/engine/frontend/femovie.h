// engine::FEMovie (RTTI name; base render::FlashScriptCallback): the front end's Flash movies. A script callback is
// bound to an ActionScript function name; the values passed between ActionScript and the engine are the 16-byte
// FEMovie::Value (a type: 2 for a boolean, 3 for a number, 4 for a string; the payload at +8). Only what other units
// use is declared; the class lives in another unit.
#ifndef ENGINE_FRONTEND_FEMOVIE_H
#define ENGINE_FRONTEND_FEMOVIE_H

namespace engine
{
	// The front end's Flash movies (another unit); a callback answers a call from ActionScript
	class FEMovie
	{
	public:
		struct Value
		{
			// 0x104B0890 (shared by the arrays of values)
			Value()
			{
				type = 0;
			}

			int type;
			int unknown4;
			union
			{
				const char* string;
				double number;
				// The payload as two words (copied as such)
				unsigned __int64 bits;
			};
		};

		struct Callback
		{
			virtual void OnCall(void* movie, const Value* arguments, unsigned int count, Value* result) = 0;
		};

		// 0x10872860 / 0x108728D0 (another unit): binds / unbinds the ActionScript function name
		static void AddCallback(const char* name, Callback* callback, int unknown);
		static void RemoveCallback(const char* name);
	};


}

#endif
