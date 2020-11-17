//search for:
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

//add under:
#ifdef ENABLE_SAVE_TELEPORT
			Set(HEADER_GC_SAVE_TELEPORT, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCSaveTeleport), STATIC_SIZE_PACKET));
#endif