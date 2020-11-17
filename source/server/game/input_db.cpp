//search for:
	case HEADER_DG_RESPOND_CHANNELSTATUS:
		[...]

//add under:

#ifdef __SAVE_TELEPORT__
	case HEADER_DG_SAVE_TELEPORT:
		LoadSaveTeleport(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
		
	case HEADER_DG_SAVE_TELEPORT_SAVE:
		ResultSaveTeleport(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif

//add at the end of the file:
#ifdef __SAVE_TELEPORT__
void CInputDB::LoadSaveTeleport(LPDESC d, const char * c_pData)
{
	if (!d)
		return;

	if (!d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();

	BYTE bCount = decode_byte(c_pData);
	c_pData += sizeof(BYTE);
	
	ch->LoadMaps(bCount, (TSaveTeleportPacket *) c_pData);

}

void CInputDB::ResultSaveTeleport(LPDESC d, const char * c_pData)
{
	if (!d)
		return;

	if (!d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();

	BYTE bFlag = decode_byte(c_pData);
	c_pData += sizeof(BYTE);
	
	
	if (bFlag == SAVE_TELEPORT_FAIL)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Saving failded.");
	}
	
	else if (bFlag == SAVE_TELEPORT_SUCCESS)
	{
		sys_log(0, "%s", c_pData);
		ch->ChatPacket(CHAT_TYPE_INFO, "Saving successful.");
		TPacketSaveTeleportUpdate packet = *(TPacketSaveTeleportUpdate*)c_pData;
		ch->UpdateMap(packet.pos, packet.name, packet.x, packet.y, packet.map_index);
		//ch->UpdateMap( (TSaveTeleportPacket *) c_pData);
	}
}

#endif