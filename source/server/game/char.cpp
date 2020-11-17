//search for:
	sys_log(0, "DISCONNECT: %s (%s)", GetName(), c_pszReason ? c_pszReason : "unset" );

//add under:
#ifdef __SAVE_TELEPORT__
	m_vec_pkSavedMaps.clear();
#endif

//add at the end of the file:
#ifdef __SAVE_TELEPORT__
void CHARACTER::LoadMaps(BYTE count, TSaveTeleportPacket * pMaps)
{
	for (DWORD i = 0; i < count; ++i)
	{
		m_vec_pkSavedMaps.push_back(pMaps[i]);
		
		TPacketGCSaveTeleport pack;
		pack.header = HEADER_GC_SAVE_TELEPORT;
		pack.pos = pMaps[i].pos;
		strcpy(pack.name, pMaps[i].name);
		pack.x = pMaps[i].x;
		pack.y = pMaps[i].y;
		
		if (GetDesc() != NULL)
		{
			GetDesc()->Packet(&pack, sizeof(pack));
		}
	}
}

TSaveTeleportPacket CHARACTER::GetSavedMap(BYTE pos)
{
	itertype(m_vec_pkSavedMaps) it = m_vec_pkSavedMaps.begin();
	while (it != m_vec_pkSavedMaps.end()) 
	{
		TSaveTeleportPacket item = *(it++);

		if (item.pos == pos)
			return item;
	}
	
	TSaveTeleportPacket item;
	item.x = 0;
	item.y = 0;
	item.map_index = 0;
	return item;
}

void CHARACTER::Teleport(BYTE pos)
{
	if (pos < 0 && pos > SAVE_TELEPORT_MAX)
		return;
	
	TSaveTeleportPacket map = GetSavedMap(pos);
	
	if (!CanWarp() || IsPosition(POS_FIGHTING))
	{
		ChatPacket(CHAT_TYPE_INFO, "You cannot do it now.");
		return;
	}
	
	if (GetMapIndex() != map.map_index)
	{
		if (map.x != 0 && map.y != 0)
		{
			WarpSet(map.x, map.y, 0);
		}
	}
	else
	{
		if (map.x != 0 && map.y != 0)
		{
			Show(GetMapIndex(), map.x, map.y);
		}
	}
}

void CHARACTER::SendMaps()
{
	itertype(m_vec_pkSavedMaps) it = m_vec_pkSavedMaps.begin();
	while (it != m_vec_pkSavedMaps.end()) 
	{
		TSaveTeleportPacket item = *(it++);
		
		TPacketGCSaveTeleport pack;
		pack.header = HEADER_GC_SAVE_TELEPORT;
		pack.pos = item.pos;
		strcpy(pack.name, item.name);
		pack.x = item.x;
		pack.y = item.y;
		
		if (GetDesc() != NULL)
		{
			GetDesc()->Packet(&pack, sizeof(pack));
		}
	}
	
}

void CHARACTER::SaveTeleport(BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1])
{
	if (pos < 0 && pos > SAVE_TELEPORT_MAX)
		return;

	TSaveTeleportPacket p;
	p.pos = pos;
	strcpy(p.name, name);
	p.x = GetX();
	p.y = GetY();
	p.map_index = GetMapIndex();
	p.player_id = GetPlayerID();

	db_clientdesc->DBPacket(HEADER_GD_SAVE_TELEPORT, GetDesc()->GetHandle(), &p, sizeof(TSaveTeleportPacket));
}

void CHARACTER::UpdateMap(BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1], long x, long y, long map_index)
{	
	for (DWORD i = 0; i < m_vec_pkSavedMaps.size(); ++i)
	{
		if (m_vec_pkSavedMaps[i].pos == pos)
		{
			m_vec_pkSavedMaps.erase(m_vec_pkSavedMaps.begin() + i);
		}
	}
	
	TSaveTeleportPacket pMap;
	pMap.pos = pos;
	strcpy(pMap.name, name);
	pMap.x = x;
	pMap.y = y;
	pMap.map_index = map_index;
	
	m_vec_pkSavedMaps.push_back(pMap);
	
	TPacketGCSaveTeleport pack;
	pack.header = HEADER_GC_SAVE_TELEPORT;
	pack.pos = pMap.pos;
	strcpy(pack.name, pMap.name);
	pack.x = pMap.x;
	pack.y = pMap.y;
	
	if (GetDesc() != NULL)
	{
		GetDesc()->Packet(&pack, sizeof(pack));
	}
}
#endif