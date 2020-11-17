//search for:
		int				GetSyncHackCount() { return m_iSyncHackCount; }

//add under:
#ifdef __SAVE_TELEPORT__
	public:
		TSaveTeleportPacket GetSavedMap(BYTE pos);
		void Teleport(BYTE pos);
		void LoadMaps(BYTE count, TSaveTeleportPacket * pMaps);
		void SendMaps();
		void SaveTeleport(BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1]);
		void UpdateMap(BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1], long x, long y, long map_index);
	protected:
		std::vector<TSaveTeleportPacket> m_vec_pkSavedMaps;
#endif