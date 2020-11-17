#Filip.
import ui
import net
import localeInfo

CLOSE_EVENT = None

def SET_CLOSE_EVENT(event):
	global CLOSE_EVENT
	CLOSE_EVENT = event

def GET_CLOSE_EVENT():
	global CLOSE_EVENT
	return CLOSE_EVENT

class SaveMapsDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadWindow(self):
		try:
			pythonScriptLoader = ui.PythonScriptLoader()
			pythonScriptLoader.LoadScriptFile(self, "uiscript/savemapswindow.py")
		except:
			import exception
			exception.Abort("SaveMapsDialog.LoadWindow.LoadObject")

		try:
			self.board = self.GetChild("Board")

			self.listBox = NewListBox()
			self.listBox.SetParent(self.board)
			self.listBox.SetSize(440, 295)
			self.listBox.SetPosition(10, 34)
			self.listBox.Show()

			self.scrollBar = ui.ScrollBar()
			self.scrollBar.SetParent(self.board)
			self.scrollBar.SetPosition(30, 10)
			self.scrollBar.SetScrollBarSize(self.board.GetHeight() - 16 - 30)
			self.scrollBar.SetWindowHorizontalAlignRight()
			self.scrollBar.SetWindowVerticalAlignCenter()
			self.scrollBar.Show()

			self.listBox.SetScrollBar(self.scrollBar)

			self.inputDlg = TextInput()
			self.inputDlg.Hide()

			for i in xrange(12):
				temp_item = SaveMapsItem(i)
				temp_item.BindInputDlg(self.inputDlg)
				temp_item.SetNameText(localeInfo.SAVE_MAPS_EMPTY_SLOT)
				temp_item.SetPositionText(0, 0)
				self.listBox.AppendItem(temp_item)

			self.board.SetCloseEvent(self.OpenWindow)

			SET_CLOSE_EVENT(self.Hide)

		except:
			import exception
			exception.Abort("SaveMapsDialog.LoadWindow.BindObject")

		self.SetCenterPosition()

	def SetMap(self, index, name, x, y):
		item = self.listBox.GetItem(index)
		item.SetNameText(name)
		item.SetPositionText(x, y)


	def OpenWindow(self):
		if self.IsShow():
			self.Hide()
		else:
			self.Show()

	def OnPressEscapeKey(self):
		self.Hide()
		return True

import grp

class NewListBox(ui.Window):
	def __init__(self):
		ui.Window.__init__(self)

		self.items = []
		self.selected = None
		self.basePos = 0
		self.itemWidth = 100
		self.itemStep = 4
		self.scrollbar = None
		self.scrollBarPos = 0.0

		self.selectEvent = None

	def SetSize(self, w, h):
		ui.Window.SetSize(self, w, h + self.itemStep)
		self.SetItemWidth(w)

		self.UpdateList()

	def SetScrollBar(self, scrollbar):
		self.scrollbar = scrollbar
		self.scrollbar.SetScrollEvent(ui.__mem_func__(self.__OnScroll))
		self.scrollbar.SetScrollStep(0.10)
		self.UpdateList()

	def CalcTotalItemHeight(self):
		total_height = 0
		for item in self.items:
			total_height += item.GetHeight()
			total_height += self.itemStep

		return total_height

	def ConfigureScrollBar(self):
		if self.scrollbar:
			itemheight = self.CalcTotalItemHeight()
			myheight = self.GetHeight() - 2 * self.itemStep
			dif = 0.97
			if itemheight > myheight and itemheight != 0:
				dif = 1.0 * myheight / itemheight

			self.scrollbar.SetMiddleBarSize(dif)

	def __OnScroll(self, position=None):
		pos = self.scrollbar.GetPos() if position == None else position
		self.scrollBarPos = pos
		toscr = self.CalcTotalItemHeight() - self.GetHeight() + 2 * self.itemStep
		self.basePos = toscr * pos

		self.UpdateList()

	def GetScrollBarPosition(self):
		return self.scrollBarPos

	def OnScroll(self, pos):
		self.__OnScroll(pos)

	def SelectItem(self, item):
		self.selected = item

		if self.selectEvent:
			self.selectEvent(item)

	def AppendItem(self, item):
		item.SetParent(self)
		item.SetWidth(self.itemWidth)
		item.Show()
		self.items.append(item)

		self.UpdateList()

	def RemoveItem(self, item):
		item.Hide()

		self.items.remove(item)
		self.UpdateList()

	def ClearItems(self):
		map(lambda wnd: wnd.Hide(), self.items)
		del self.items[:]

		self.basePos = 0
		if self.scrollbar:
			self.scrollbar.SetPos(0)
		self.UpdateList()

	def UpdateList(self):
		self.ConfigureScrollBar()
		self.RecalcItemPositions()

	def IsEmpty(self):
		return len(self.itemList) == 0

	def SetItemWidth(self, w):
		self.itemWidth = w
		for item in self.items:
			item.SetWidth(w)

	def RecalcItemPositions(self):
		curbp = self.basePos

		itemheight = self.CalcTotalItemHeight()
		myheight = self.GetHeight() - 2 * self.itemStep

		if itemheight < myheight:
			curbp = 0

		fromPos = curbp
		curPos = 0
		toPos = curbp + self.GetHeight()
		for item in self.items:
			hw = item.GetHeight()
			if curPos + hw < fromPos:
				item.Hide()
			elif curPos < fromPos and curPos + hw > fromPos:
				item.SetRenderMin(fromPos - curPos)
				item.Show()
			elif curPos < toPos and curPos + hw > toPos:
				item.SetRenderMax(toPos - curPos)
				item.Show()
			elif curPos > toPos:
				item.Hide()
			else:
				item.SetRenderMin(0)
				item.Show()

			item.SetPosition(0, curPos - fromPos)
			curPos += hw + self.itemStep

	def GetItem(self, index):
		return self.items[index]

class NewListBoxItem(ui.Window):
	def __init__(self):
		ui.Window.__init__(self)

		self.width = 0
		self.height = 0
		self.minh = 0
		self.maxh = 0

		self.components = []

	def __del__(self):
		ui.Window.__del__(self)

	def SetColor(self, color=0xff0099ff):
		self.color = color

	def SetParent(self, parent):
		ui.Window.SetParent(self, parent)

	def SetHeight(self, h):
		self.SetSize(self.width, h)

	def SetWidth(self, w):
		self.SetSize(w, self.height)

	def SetSize(self, w, h):
		self.width = w
		self.height = h
		self.maxh = h
		ui.Window.SetSize(self, w, h)

	def SetRenderMin(self, minh):
		self.minh = minh
		self.maxh = self.height
		self.RecalculateRenderedComponents()

	def SetRenderMax(self, maxh):
		self.maxh = maxh
		self.minh = 0
		self.RecalculateRenderedComponents()

	def RegisterComponent(self, component):
		mtype = type(component).__name__
		if mtype == "Bar":
			(x, y, w, h) = component.GetRect()
			(x, y) = component.GetLocalPosition()
			component.__list_data = [x, y, w, h]
		self.components.append(component)

	def UnregisterComponent(self, component):
		self.components.remove(component)
# if component.__list_data:
#	component.__list_data = None

	def RecalculateRenderedComponents(self):
		for component in self.components:
			(xl, yl) = component.GetLocalPosition()
			(x, y, w, h) = component.GetRect()
			mtype = type(component).__name__
			if mtype == "TextLine":
				(w, h) = component.GetTextSize()

			if yl + h < self.minh:
				component.Hide()
			elif yl > self.maxh:
				component.Hide()
			else:
				if mtype == "ExpandedImageBox" or mtype == "ExpandedButton":

					miny = 0
					if self.minh > 0 and yl < self.minh:
						miny = -float(self.minh - yl) / float(h)

					maxy = 0
					if h != 0:
						maxy = float(self.maxh - yl - h) / float(h)

					maxy = min(0, max(-1, maxy))

					component.SetRenderingRect(0.0, miny, 0.0, maxy)
					component.Show()

				else:
					if yl < self.minh or yl + h > self.maxh:
						component.Hide()
					else:
						component.Show()

	def OnRender(self):
		x, y = self.GetGlobalPosition()
		grp.SetColor(self.color)
		grp.RenderBar(x, y + self.minh, self.GetWidth(), self.maxh - self.minh)

class SaveMapsItem(NewListBoxItem):
	def __init__(self, index):
		NewListBoxItem.__init__(self)
		self.__index = index
		self.__inputDlg = None
		self.__LoadWindow()

		self.SetColor(0x70000000)

	def __del__(self):
		NewListBoxItem.__del__(self)

	def __LoadWindow(self):

		self.slotBar = ui.ExpandedImageBox()
		self.slotBar.SetParent(self)
		self.slotBar.SetPosition(0, 0)
		self.slotBar.LoadImage("d:/ymir work/ui/tab_menu_01.tga")
		self.slotBar.Show()

		self.RegisterComponent(self.slotBar)

		self.nameText = ui.TextLine()
		self.nameText.SetParent(self.slotBar)
		self.nameText.SetPosition(8, 4)
		self.nameText.Show()

		self.RegisterComponent(self.nameText)

		self.positionText = ui.TextLine()
		self.positionText.SetParent(self.slotBar)
		self.positionText.SetPosition(24, 22)
		self.positionText.SetWindowVerticalAlignCenter()
		self.positionText.Show()

		self.RegisterComponent(self.positionText)

		self.teleportButton = ui.ExpandedButton()
		self.teleportButton.SetParent(self)
		self.teleportButton.SetUpVisual("d:/ymir work/ui/itemshop/buy_button_0.tga")
		self.teleportButton.SetOverVisual("d:/ymir work/ui/itemshop/buy_button_1.tga")
		self.teleportButton.SetDownVisual("d:/ymir work/ui/itemshop/buy_button_2.tga")
		self.teleportButton.SetPosition(337, 30)
		self.teleportButton.SetEvent(self.__OnClickTeleportButton)
		self.teleportButton.Show()

		self.RegisterComponent(self.teleportButton)

		self.saveButton = ui.ExpandedButton()
		self.saveButton.SetParent(self)
		self.saveButton.SetUpVisual("d:/ymir work/ui/itemshop/buy_button_0.tga")
		self.saveButton.SetOverVisual("d:/ymir work/ui/itemshop/buy_button_1.tga")
		self.saveButton.SetDownVisual("d:/ymir work/ui/itemshop/buy_button_2.tga")
		self.saveButton.SetPosition(337 - 94, 30)
		self.saveButton.SetEvent(self.__OnClickSaveTeleportButton)
		self.saveButton.Show()

		self.RegisterComponent(self.saveButton)

		self.SetSize(self.slotBar.GetWidth(), 60)

	def SetNameText(self, text):
		self.nameText.SetText(text)

	def SetPositionText(self, x, y):
		self.positionText.SetText(localeInfo.SAVE_MAPS_POSITION % (x, y))

	def BindInputDlg(self, dlg):
		self.__inputDlg = dlg

	def __OnClickTeleportButton(self):
		closeEvent = GET_CLOSE_EVENT()
		closeEvent()
		net.SendSaveTeleportWarpPacket(self.__index)

	def __OnClickSaveTeleportButton(self):
		self.__inputDlg.Open(self.__index)

class TextInput(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__index = -1
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadWindow(self):

		try:
			pythonScriptLoader = ui.PythonScriptLoader()
			pythonScriptLoader.LoadScriptFile(self, "uiscript/savemapsinput.py")
		except:
			import exception
			exception.Abort("TextInput.LoadWindow.LoadObject")

		try:
			self.editLine = self.GetChild("input_value")

			self.GetChild("confirm_button").SetEvent(self.__OnClickConfirmButton)
			self.GetChild("close_button").SetEvent(self.Hide)

		except:
			import exception
			exception.Abort("TextInput.LoadWindow.BindObject")

		self.SetCenterPosition()


	def Open(self, index):
		self.__index = index
		self.editLine.SetText("")
		self.editLine.SetFocus()
		self.Show()
		self.SetTop()

	def __OnClickConfirmButton(self):
		text = self.editLine.GetText()

		if text == "" or self.__index == -1:
			return

		net.SendSaveTeleportSavePacket(self.__index, text)
		self.Hide()

	def OpenWindow(self):
		if self.IsShow():
			self.Hide()
		else:
			self.Show()

	def OnPressEscapeKey(self):
		self.Hide()
		return True

