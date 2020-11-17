//search for:
	void		RESULT_AFFECT_LOAD(CPeer * pkPeer, MYSQL_RES * pRes, DWORD dwHandle);

//add under:
#ifdef __SAVE_TELEPORT__
	void		RESULT_SAVE_TELEPORT_LOAD(CPeer * pkPeer, MYSQL_RES * pRes, DWORD dwHandle);
#endif

//search for:
#ifdef __AUCTION__
	void EnrollInAuction (CPeer * peer, DWORD owner_id, AuctionEnrollProductInfo* data);
	[...]
#endif

//add under:
#ifdef __SAVE_TELEPORT__
	void QUERY_SAVE_TELEPORT(CPeer * pkPeer, DWORD dwHandle, TSaveTeleportPacket * p);
#endif