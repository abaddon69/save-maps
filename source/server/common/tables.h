//search for:
	HEADER_GD_REQUEST_CHANNELSTATUS	= 140,

//add under:
#ifdef __SAVE_TELEPORT__
	HEADER_GD_SAVE_TELEPORT = 147,
#endif

//search for:
	HEADER_DG_RESPOND_CHANNELSTATUS		= 181,

//add under:
#ifdef __SAVE_TELEPORT__
	HEADER_DG_SAVE_TELEPORT			= 185,
	HEADER_DG_SAVE_TELEPORT_SAVE	= 186,
#endif

//add at the end of the file
ifdef __SAVE_TELEPORT__

enum
{
	SAVE_TELEPORT_MAX = 12,
	SAVE_TELEPORT_NAME_NUM = 32,
};

enum
{
	SAVE_TELEPORT_SUCCESS,
	SAVE_TELEPORT_FAIL,
};

typedef struct SSaveTeleportPacket
{
	BYTE	pos;
	char	name[SAVE_TELEPORT_NAME_NUM + 1];
	long	x;
	long	y;
	long	map_index;
	DWORD	player_id;
} TSaveTeleportPacket;

typedef struct SSaveTeleportUpdatePacket
{
	BYTE	pos;
	char	name[SAVE_TELEPORT_NAME_NUM + 1];
	long	x;
	long	y;
	long	map_index;
} TPacketSaveTeleportUpdate;

#endif