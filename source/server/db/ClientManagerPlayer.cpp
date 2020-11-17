//search for:
			snprintf(szQuery, sizeof(szQuery),
					"SELECT dwPID,bType,bApplyOn,lApplyValue,dwFlag,lDuration,lSPCost FROM affect%s WHERE dwPID=%d",
					GetTablePostfix(), pTab->id);
			CDBManager::instance().ReturnQuery(szQuery, QID_AFFECT, peer->GetHandle(), new ClientHandleInfo(dwHandle));

//add under:
#ifdef __SAVE_TELEPORT__
			// Item Shop
			snprintf(szQuery, sizeof(szQuery),
					"SELECT pos, name, x, y, map_index FROM save_teleport%s WHERE id=%d",
					GetTablePostfix(), packet->player_id);
			CDBManager::instance().ReturnQuery(szQuery, QID_SAVE_TELEPORT_LOAD, peer->GetHandle(), new ClientHandleInfo(dwHandle));
#endif


//search for:
			CDBManager::instance().ReturnQuery(szQuery,
					QID_AFFECT,
					peer->GetHandle(),
					new ClientHandleInfo(dwHandle, pTab->id));

//add under:
#ifdef __SAVE_TELEPORT__
			snprintf(szQuery, sizeof(szQuery), 
					"SELECT pos, name, x, y, map_index FROM save_teleport%s WHERE id=%d",
					GetTablePostfix(), packet->player_id);

			CDBManager::instance().ReturnQuery(szQuery,
					QID_SAVE_TELEPORT_LOAD,
					peer->GetHandle(),
					new ClientHandleInfo(dwHandle, pTab->id));
#endif

//search for:
		snprintf(queryStr, sizeof(queryStr),
				"SELECT dwPID,bType,bApplyOn,lApplyValue,dwFlag,lDuration,lSPCost FROM affect%s WHERE dwPID=%d",
				GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(queryStr, QID_AFFECT, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));

//add under:
#ifdef __SAVE_TELEPORT__
		snprintf(queryStr, sizeof(queryStr),
				"SELECT pos, name, x, y, map_index FROM save_teleport%s WHERE id=%d",
				GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(queryStr, QID_SAVE_TELEPORT_LOAD, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
#endif

//search for:
		case QID_AFFECT:
			sys_log(0, "QID_AFFECT %u", info->dwHandle);
			RESULT_AFFECT_LOAD(peer, pSQLResult, info->dwHandle);
			break;

//add under:
#ifdef __SAVE_TELEPORT__
		case QID_SAVE_TELEPORT_LOAD:
			sys_log(0, "QID_SAVE_TELEPORT_LOAD %u", info->dwHandle);
			RESULT_SAVE_TELEPORT_LOAD(peer, pSQLResult, info->dwHandle);
			break;
#endif

//add at the end of the file
#ifdef __SAVE_TELEPORT__
void CClientManager::RESULT_SAVE_TELEPORT_LOAD(CPeer * peer, MYSQL_RES * pRes, DWORD dwHandle)
{

	int iNumRows;

	if ((iNumRows = mysql_num_rows(pRes)) == 0) // 데이터 없음
		return;

	static std::vector<TSaveTeleportPacket> s_elements;
	s_elements.resize(iNumRows);

	MYSQL_ROW row;

	for (int i = 0; i < iNumRows; ++i)
	{
		TSaveTeleportPacket & r = s_elements[i];
		row = mysql_fetch_row(pRes);

		str_to_number(r.pos, row[0]);
		strcpy(r.name, row[1]);
		str_to_number(r.x, row[2]);
		str_to_number(r.y, row[3]);
		str_to_number(r.map_index, row[4]);
		
		sys_log(0, "RESULT_SAVE_TELEPORT: pos %d name %s x %d y %d map_index %d", r.pos, r.name, r.x, r.y, r.map_index);
	}


	BYTE bCount = s_elements.size();

	peer->EncodeHeader(HEADER_DG_SAVE_TELEPORT, dwHandle, sizeof(BYTE) + sizeof(TSaveTeleportPacket) * bCount);
	peer->Encode(&bCount, sizeof(BYTE));
	peer->Encode(&s_elements[0], sizeof(TSaveTeleportPacket) * bCount);
}
#endif