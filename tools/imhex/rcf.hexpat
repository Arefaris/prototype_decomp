// ImHex pattern for Radical Cement File archives, version 2.1.
#pragma endian little
#pragma pattern_limit 1000000

struct DirectoryEntry {
	u32 hash [[format("hex")]];
	u32 offset [[format("hex")]];
	u32 size;
};

struct NameRecord {
	u32 timestamp [[format("std::time::to_utc")]];
	u32 alignment;
	u32 reserved;
	u32 length;
	char name[length];
	padding[3];
};

struct NameTable {
	u32 alignment;
	u32 reserved;
	NameRecord records[parent.count];
};

struct RcfFile {
	char magic[0x20];
	u8 version[4];
	u32 directoryOffset [[format("hex")]];
	u32 directorySize;
	u32 namesOffset [[format("hex")]];
	u32 namesSize;
	u32 reserved;
	u32 count;
	DirectoryEntry directory[count] @ directoryOffset;
	NameTable names @ namesOffset;
};

RcfFile rcf @ 0x00;
