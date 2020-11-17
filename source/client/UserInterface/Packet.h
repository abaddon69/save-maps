//search for:
	HEADER_CG_QUEST_CONFIRM = 31,

//add under:
#ifdef ENABLE_SAVE_TELEPORT
	HEADER_CG_SAVE_TELEPORT						= 34,
#endif

//search for:
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL			= 138,
	// END_OF_SUPPORT_BGM

//add under:
#ifdef ENABLE_SAVE_TELEPORT
	HEADER_GC_SAVE_TELEPORT						= 140,
#endif

//add at the end of the file:
#ifdef ENABLE_SAVE_TELEPORT

enum
{
	SAVE_TELEPORT_MAX = 12,
	SAVE_TELEPORT_NAME_NUM = 32,
};

typedef struct save_teleport_data
{
	BYTE	header;
	BYTE	pos;
	char	name[SAVE_TELEPORT_NAME_NUM + 1];
	long	x;
	long	y;
} TPacketGCSaveTeleport;

typedef struct save_teleport_send
{
	BYTE	bHeader;
	BYTE	bType;
	BYTE	bPos;
	char	szName[SAVE_TELEPORT_NAME_NUM + 1];
} TPacketCGSaveTeleport;

enum 
{
	SAVE_TELEPORT_WARP,
	SAVE_TELEPORT_SAVE,
};
#endif