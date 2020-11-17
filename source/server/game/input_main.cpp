//search for:
void CInputMain::Refine(LPCHARACTER ch, const char* c_pData)
{
	[...]
}

//add under:
#ifdef __SAVE_TELEPORT__
void CInputMain::SaveTeleport(LPCHARACTER ch, const char* c_pData)
{
	TPacketCGSaveTeleport* p = (TPacketCGSaveTeleport*)c_pData;
	switch(p->bType)
	{
		case SAVE_TELEPORT_WARP:
		{
			if (!ch->CanWarp())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("REFRESH_DELAY"));
				return;
			}
			
			ch->Teleport(p->bPos);
			break;
		}
		case SAVE_TELEPORT_SAVE:
			if (!ch->CanWarp())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("REFRESH_DELAY"));
				return;
			}
			
			ch->SaveTeleport(p->bPos, p->szName);
	}
}
#endif

//search for:
		case HEADER_CG_DRAGON_SOUL_REFINE:
			{
				[...]
			}

			break;

//add under:
#ifdef __SAVE_TELEPORT__
		case HEADER_CG_SAVE_TELEPORT:
			SaveTeleport(ch, c_pData);
			break;
#endif