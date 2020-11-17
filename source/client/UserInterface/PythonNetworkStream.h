//search for:
		void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);

//add under:
#ifdef ENABLE_SAVE_TELEPORT
	public:
		bool SendSaveTeleportPacket(BYTE type, BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1] = "");
	private:
		bool RecvSaveTeleportPacket();
#endif