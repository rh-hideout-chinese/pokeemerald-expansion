GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
    .string "喂，那边的。\n前面黑得可怕，\l继续探索下去会很危险。\p先前有个人来过……\n我想应该是大吾。\p那家伙会使用闪光，所以\n应该没事，可是……\p唔，对于我们登山者而言，帮助他人\n解决困难是我们的座右铭。\p给，这个送你了。$"

GraniteCave_1F_Text_ExplainFlash:
    .string "把闪光招式教给宝可梦，\n使用的时候，\p就能够照亮\n漆黑的山洞。\p但你必须先去武斗镇的宝可梦道馆\n取得道馆徽章。$"

