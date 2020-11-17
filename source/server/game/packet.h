//search for:
	HEADER_CG_QUEST_CONFIRM			= 31,
	
//add under:
#ifdef __SAVE_TELEPORT__
	HEADER_CG_SAVE_TELEPORT			= 34,
#endif

//search for:
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL	= 138,
	// END_OF_SUPPORT_BGM
	

//add under:
#ifdef __SAVE_TELEPORT__
	HEADER_GC_SAVE_TELEPORT						= 140,
#endif

//add at the end of the file
#ifdef __SAVE_TELEPORT__
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