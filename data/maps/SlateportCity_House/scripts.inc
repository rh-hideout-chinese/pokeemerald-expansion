SlateportCity_House_MapScripts::
	.byte 0

SlateportCity_House_EventScript_PokefanM::
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl::
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains:
    .string "我的宝可梦是急躁性格，\p比起我的其它宝可梦，\n它的速度比较快。\p也许宝可梦的性格\n也会影响到它们的成长。$"

SlateportCity_House_Text_MustBeGoingToBattleTent:
    .string "你是个训练师对吧？\p你来凯那市\n一定是想去对战帐篷。$"

