//search for:
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;

//add under:
#ifdef ENABLE_SAVE_TELEPORT
			case HEADER_GC_SAVE_TELEPORT:
				ret = RecvSaveTeleportPacket();
				break;
#endif

//add at the end of the file
#ifdef ENABLE_SAVE_TELEPORT
bool CPythonNetworkStream::RecvSaveTeleportPacket()
{
	TPacketGCSaveTeleport packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SaveTeleportSetMap", Py_BuildValue("(isii)", packet.pos, packet.name, packet.x, packet.y));
}

bool CPythonNetworkStream::SendSaveTeleportPacket(BYTE type, BYTE pos, char name[SAVE_TELEPORT_NAME_NUM + 1])
{
	TPacketCGSaveTeleport kSaveTeleport;
	kSaveTeleport.bHeader = HEADER_CG_SAVE_TELEPORT;
	kSaveTeleport.bType = type;
	kSaveTeleport.bPos = pos;
	strncpy(kSaveTeleport.szName, name, SAVE_TELEPORT_NAME_NUM + 1);
	if (!Send(sizeof(kSaveTeleport), &kSaveTeleport))
		return false;

	return SendSequence();

}

#endif