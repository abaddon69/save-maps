//search for:
			case HEADER_GD_REQUEST_CHANNELSTATUS:
				[...]

//add under:
#ifdef __SAVE_TELEPORT__
			case HEADER_GD_SAVE_TELEPORT:
				QUERY_SAVE_TELEPORT(peer, dwHandle, (TSaveTeleportPacket *) data);
				break;
#endif

//search for:
		case QID_AFFECT:

//add under:
#ifdef __SAVE_TELEPORT__
		case QID_SAVE_TELEPORT_LOAD:
#endif

//add at the end of the file
#ifdef __SAVE_TELEPORT__
void CClientManager::QUERY_SAVE_TELEPORT(CPeer * pkPeer, DWORD dwHandle, TSaveTeleportPacket * p)
{
	/*char queryStr[QUERY_MAX_LEN];
			
	snprintf(queryStr, sizeof(queryStr),
			"REPLACE INTO save_teleport%s (id, name, pos, x, y, map_index) VALUES(%d, '%s', %d, %d, %d, %d)",
			GetTablePostfix(), p->player_id, p->name, p->pos, p->x, p->y, p->map_index);

	CDBManager::instance().ReturnQuery(queryStr, QID_SAVE_TELEPORT_SAVE, pkPeer->GetHandle(), NULL);*/

	char queryStr[QUERY_MAX_LEN];
	
	BYTE bFlag;
	
	snprintf(queryStr, sizeof(queryStr),
			"REPLACE INTO save_teleport%s (id, name, pos, x, y, map_index) VALUES(%d, '%s', %d, %d, %d, %d)",
			GetTablePostfix(), p->player_id, p->name, p->pos, p->x, p->y, p->map_index);
	
	std::unique_ptr<SQLMsg> pMsg(CDBManager::instance().DirectQuery(queryStr));

	if (pMsg->Get()->uiAffectedRows <= 0)
	{
		bFlag = SAVE_TELEPORT_FAIL;
		pkPeer->EncodeHeader(HEADER_DG_SAVE_TELEPORT_SAVE, dwHandle, sizeof(BYTE));
		pkPeer->Encode(&bFlag, sizeof(BYTE));
		return;
	}

	TPacketSaveTeleportUpdate packet;
	packet.pos = p->pos;
	strcpy(packet.name, p->name);
	packet.x = p->x;
	packet.y = p->y;
	packet.map_index = p->map_index;
	
	bFlag = SAVE_TELEPORT_SUCCESS;
	pkPeer->EncodeHeader(HEADER_DG_SAVE_TELEPORT_SAVE, dwHandle, sizeof(BYTE) + sizeof(TPacketSaveTeleportUpdate));
	pkPeer->Encode(&bFlag, sizeof(BYTE));
	pkPeer->Encode(&packet, sizeof(TPacketSaveTeleportUpdate));
}
#endif