// engine::FEResourceStreamClient (RTTI name; bases engine::StreamClient and, at +0x1C, content::SimpleChunkHandler):
// the stream client that loads the frontend's resources. Of it only the nested load objects of the text bible are
// reconstructed (RTTI: TextBibleStorage, TextBibleHolder, TextBibleEntry; each derives from content::LoadObject). The
// text bible is the frontend's table of texts: the storage owns the buffer the entries' texts are copied into. Names
// other than the RTTI ones are guesses.
#ifndef ENGINE_FRONTEND_FERESOURCESTREAMCLIENT_H
#define ENGINE_FRONTEND_FERESOURCESTREAMCLIENT_H

#include "code/content/chunkhandler.h"
#include "code/content/loadinventory.h"

namespace engine
{
	class FEResourceStreamClient
	{
	public:
		// The memory the texts of the bible are copied into: a block of the size the bible needs and the position the
		// next text goes to
		class TextBibleStorage : public content::LoadObject
		{
		public:
			// 0x108733D0: a block of that many bytes, nothing taken yet
			explicit TextBibleStorage(unsigned int newSize);
			// 0x10873330 (the deleting destructor is 0x10873410)
			virtual ~TextBibleStorage();
			// 0x10873350: takes that many bytes and answers where they start
			char* Take(int bytes);
			// 0x10873360
			unsigned int GetSize() const;

			unsigned int size;  // +8
			char* buffer;  // +0xC
			char* cursor;  // +0x10
		};

		// Keeps the storage alive for as long as the entries of the bible are (0x108734B0; destructor 0x10873370,
		// deleting destructor 0x108734E0)
		class TextBibleHolder : public content::LoadObject
		{
		public:
			explicit TextBibleHolder(TextBibleStorage* newStorage);
			virtual ~TextBibleHolder();
			// 0x10873390
			TextBibleStorage* GetStorage() const;

			TextBibleStorage* storage;  // +8
		};

		// What a chunk reader hands the entries: the stream it reads through (at +0x284; the rest is unrecovered)
		struct TextBibleSource
		{
			unsigned char unknown0[0x284];
			content::LoadStream* stream;
		};

		// One text of the bible (0x10873430; the destructor 0x10873480 and the deleting destructor 0x10873490 are the
		// compiler's)
		class TextBibleEntry : public content::LoadObject
		{
		public:
			TextBibleEntry(TextBibleSource* source, unsigned int length, TextBibleStorage* storage);

			char* text;  // +8
		};
	};
}

#endif
