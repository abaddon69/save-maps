//search for:
	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

//add under:
#ifdef __SAVE_TELEPORT__
	Set(HEADER_CG_SAVE_TELEPORT, sizeof(TPacketCGSaveTeleport), "SaveTeleport", true);
#endif