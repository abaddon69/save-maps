import uiScriptLocale

window = {
	"name" : "ItemShopDialog",
	"style" : ("movable", "float",),

	"x" : 0,
	"y" : 0,

	"width" : 490,
	"height" : 340,

	"children" :
	(
		{
			"name" : "Board",
			"type" : "board_with_titlebar",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : 490,
			"height" : 340,
			"title" : uiScriptLocale.SAVE_MAPS_TITLE,
		},
	),
}