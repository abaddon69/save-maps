#search for:
import event

#add under:
import uiSaveTeleport

#search for:
		self.wndGuildBuilding = None

#add under:
		self.wndSaveMaps = None

#search for:
		self.dlgRefineNew = uiRefine.RefineDialogNew()
		self.dlgRefineNew.Hide()

#add under:
		self.wndSaveMaps = uiSaveTeleport.SaveMapsDialog()
		self.wndSaveMaps.Hide()

#search for:
		# ACCESSORY_REFINE_ADD_METIN_STONE
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()
		# END_OF_ACCESSORY_REFINE_ADD_METIN_STONE

#add under:
		if self.wndSaveMaps:
			self.wndSaveMaps.Destroy()
			del self.wndSaveMaps