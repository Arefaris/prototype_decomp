// The proto stream manager (RTTI proto::StreamManager, vftable 0x10E24E14, one slot; not engine::StreamManager): the
// scripted control of the world streaming (the psm_ script natives; 0x112735C8 is the one manager). The layout and the
// member names are guesses.
#ifndef PROTO_STREAMMANAGER_H
#define PROTO_STREAMMANAGER_H

namespace proto
{
	// RTTI: proto::StreamManager
	class StreamManager
	{
	public:
		// 0x1056F780
		StreamManager();
		// 0x1056F7B0
		virtual ~StreamManager();

		int unknown4;
		int unknown8;
		int unknownC;
	};

	// 0x112735C8: the one stream manager (null: none)
	extern StreamManager* gProtoStreamManager;
}

#endif
