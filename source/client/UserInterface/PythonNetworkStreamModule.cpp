//search for:
PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}

//add under:
#ifdef ENABLE_SAVE_TELEPORT

PyObject* netSendSaveTeleportSavePacket(PyObject* poSelf, PyObject* poArgs)
{
	int pos;
	char * name;

	if (!PyTuple_GetInteger(poArgs, 0, &pos))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &name))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendSaveTeleportPacket(SAVE_TELEPORT_SAVE, pos, name);

	return Py_BuildNone();
}

PyObject* netSendSaveTeleportWarpPacket(PyObject* poSelf, PyObject* poArgs)
{

	int pos;

	if (!PyTuple_GetInteger(poArgs, 0, &pos))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendSaveTeleportPacket(SAVE_TELEPORT_WARP, pos);

	return Py_BuildNone();
}
#endif

//search for:
		{ "RegisterErrorLog",						netRegisterErrorLog,						METH_VARARGS },

//add under:
#ifdef ENABLE_SAVE_TELEPORT
		{ "SendSaveTeleportSavePacket", netSendSaveTeleportSavePacket, METH_VARARGS },
		{ "SendSaveTeleportWarpPacket", netSendSaveTeleportWarpPacket, METH_VARARGS },
#endif