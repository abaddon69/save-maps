import uiScriptLocale

window = {
	"name" : "ItemShopDialog",
	"style" : ("movable", "float",),

	"x" : 0,
	"y" : 0,

	"width" : 200,
	"height" : 90,

	"children" :
	(
		{
			"name" : "Board",
			"type" : "board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : 200,
			"height" : 90,

			"children" : (
				{
					"name" : "text",
					"type" : "text",

					"x" : 0,
					"y" : 10,

					"text_horizontal_align" : "center",
					"horizontal_align" : "center",

					"text" : uiScriptLocale.SAVE_MAPS_ENTER_NAME,
				},

				{
					"name" : "input_slot",
					"type" : "thinboardcircle",

					"x" : 20,
					"y" : 30,

					"width" : 160,
					"height" : 20,

					"children" : (
						{
							"name" : "input_value",
							"type" : "editline",

							"x" : 3,
							"y" : 3,

							"width" : 160,
							"height" : 20,

							"input_limit" : 32,

						},
					),
				},
				{
					"name": "confirm_button",
					"type": "button",

					"x": 0,
					"y": 60,

					"text": uiScriptLocale.SAVE_MAPS_SAVE,

					"horizontal_align" : "center",

					"default_image": "d:/ymir work/ui/public/middle_button_01.sub",
					"over_image": "d:/ymir work/ui/public/middle_button_02.sub",
					"down_image": "d:/ymir work/ui/public/middle_button_03.sub",
				},

				{
					"name": "close_button",
					"type": "button",

					"x": 30,
					"y": 13,

					"horizontal_align": "right",

					"default_image": "d:/ymir work/ui/public/close_button_01.sub",
					"over_image": "d:/ymir work/ui/public/close_button_02.sub",
					"down_image": "d:/ymir work/ui/public/close_button_03.sub",
				},
			),
		},
	),
}