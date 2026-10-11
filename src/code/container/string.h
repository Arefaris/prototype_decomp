// container::String and container::StringC<N> (RTTI names): a string over storage its subclass provides. String's
// four virtual slots are the destructor, the writable and the constant buffer and the capacity; StringC<N> keeps N
// characters inline. Only what the engine's users need is reconstructed (the class lives in the core library);
// member names are guesses.
#ifndef CONTAINER_STRING_H
#define CONTAINER_STRING_H

namespace container
{
	class String
	{
	public:
		String()
		{
		}
		virtual ~String()
		{
		}
		virtual char* Data() = 0;
		virtual const char* ConstData() const = 0;
		virtual int Capacity() const = 0;

		// 0x1060ED50: printf into the string
		void Format(const char* format, ...);
	};

	template<int N> class StringC : public String
	{
	public:
		StringC()
		{
			buffer[0] = 0;
		}
		virtual char* Data()
		{
			return buffer;
		}
		virtual const char* ConstData() const
		{
			return buffer;
		}
		virtual int Capacity() const
		{
			return N;
		}

		char buffer[N];
	};
}

#endif
