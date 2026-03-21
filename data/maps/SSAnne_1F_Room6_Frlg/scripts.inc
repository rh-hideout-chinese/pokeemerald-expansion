SSAnne_1F_Room6_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room6_EventScript_Woman::
	lock
	faceplayer
	msgbox SSAnne_1F_Room6_Text_TakeAShortRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_1F_Room6_EventScript_DeclineHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SSAnne_1F_Room6_Text_GladEveryoneIsRefreshed
	release
	end

SSAnne_1F_Room6_EventScript_DeclineHeal::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SSAnne_1F_Room6_EventScript_DeclineHealMale
	msgbox SSAnne_1F_Room6_Text_SorryYouLookLikeMySister
	release
	end

SSAnne_1F_Room6_EventScript_DeclineHealMale::
	msgbox SSAnne_1F_Room6_Text_SorryYouLookLikeMyBrother
	release
	end

SSAnne_1F_Room6_Text_TakeAShortRest::
    .string "你看上去有点累。\n"
    .string "想休息一会儿吗？$"

SSAnne_1F_Room6_Text_GladEveryoneIsRefreshed::
    .string "我很高兴看到大家\n"
    .string "都恢复了精神。$"

SSAnne_1F_Room6_Text_SorryYouLookLikeMyBrother::
    .string "哦，我对过分关心你感到抱歉。\n"
    .string "你看起来像我的小弟弟……$"

SSAnne_1F_Room6_Text_SorryYouLookLikeMySister::
    .string "哦，我对过分关心你感到抱歉。\n"
    .string "你看起来像我的小妹妹……$"

