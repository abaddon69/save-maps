//search for:
		void		Roulette(LPCHARACTER ch, const char* c_pData);

//add under:
#ifdef __SAVE_TELEPORT__
		void		SaveTeleport(LPCHARACTER ch, const char* c_pData);
#endif

//search for:

	void		AffectLoad(LPDESC d, const char * c_pData);

//add under:
#ifdef __SAVE_TELEPORT__
	void LoadSaveTeleport(LPDESC d, const char * c_pData);
	void ResultSaveTeleport(LPDESC d, const char * c_pData);
#endif