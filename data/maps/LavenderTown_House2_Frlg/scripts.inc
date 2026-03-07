LavenderTown_House2_Frlg_MapScripts::
	.byte 0

LavenderTown_House2_EventScript_NameRater::
	lock
	faceplayer
	msgbox LavenderTown_House2_Text_WantMeToRateNicknames, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LavenderTown_House2_EventScript_ChooseMon
	goto_if_eq VAR_RESULT, NO, LavenderTown_House2_EventScript_DontRateNickname
	end

LavenderTown_House2_EventScript_ChooseMon::
	msgbox LavenderTown_House2_Text_CritiqueWhichMonsNickname
	special ChoosePartyMon
	waitstate
	goto_if_lt VAR_0x8004, PARTY_SIZE, LavenderTown_House2_EventScript_CheckCanRateMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, LavenderTown_House2_EventScript_DontRateNickname
	end

LavenderTown_House2_EventScript_DontRateNickname::
	msgbox LavenderTown_House2_Text_ISeeComeVisitAgain
	release
	end

LavenderTown_House2_EventScript_CheckCanRateMon::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, LavenderTown_House2_EventScript_CantNicknameEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, LavenderTown_House2_EventScript_CantNicknameTradeMon
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, LavenderTown_House2_EventScript_CantNicknameTradeMon
	msgbox LavenderTown_House2_Text_GiveItANicerName, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LavenderTown_House2_EventScript_ChooseNewNickname
	goto_if_eq VAR_RESULT, NO, LavenderTown_House2_EventScript_DontRateNickname
	end

LavenderTown_House2_EventScript_CantNicknameEgg::
	msgbox LavenderTown_House2_Text_ThatIsMerelyAnEgg
	release
	end

LavenderTown_House2_EventScript_CantNicknameTradeMon::
	msgbox LavenderTown_House2_Text_TrulyImpeccableName
	release
	end

LavenderTown_House2_EventScript_ChooseNewNickname::
	msgbox LavenderTown_House2_Text_WhatShallNewNicknameBe
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, LavenderTown_House2_EventScript_ChoseNewNickname
	msgbox LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName
	release
	end

LavenderTown_House2_EventScript_ChoseNewNickname::
	msgbox LavenderTown_House2_Text_FromNowOnShallBeKnownAsName
	release
	end

LavenderTown_House2_Text_WantMeToRateNicknames::
    .string "嗨！\n"
    .string "我是权威的姓名鉴定师！\p"
    .string "想让我鉴定一下你的宝可梦的昵称吗？$"

LavenderTown_House2_Text_CritiqueWhichMonsNickname::
    .string "要我鉴定哪只宝可梦的昵称？$"

LavenderTown_House2_Text_GiveItANicerName::
    .string "{STR_VAR_1}，是它吗？\n"
    .string "这是一个相当好的昵称！\p"
    .string "但是，想让我给它一个\n"
    .string "更好的名字吗？\p"
    .string "怎么样？$"

LavenderTown_House2_Text_WhatShallNewNicknameBe::
    .string "哦，好的。那么，\n"
    .string "新的昵称是什么？$"

LavenderTown_House2_Text_FromNowOnShallBeKnownAsName::
    .string "完成！从现在起，这只宝可梦\n"
    .string "会被叫做{STR_VAR_1}！\p"
    .string "比以前的那个名字要好！\n"
    .string "会给你带来好运的！$"

LavenderTown_House2_Text_ISeeComeVisitAgain::
    .string "我知道了。\n"
    .string "请务必再来。$"

LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName::
    .string "好啦！从现在起，这只宝可梦\n"
    .string "会被叫做{STR_VAR_1}！\p"
    .string "它看起来和以前没什么两样，\n"
    .string "但是，这个名字显得更优秀。\p"
    .string "会给你带来好运的！$"

LavenderTown_House2_Text_TrulyImpeccableName::
    .string "{STR_VAR_1}，是吗？\n"
    .string "这真是一个棒极了的名字！\p"
    .string "好好照顾{STR_VAR_1}！$"

LavenderTown_House2_Text_ThatIsMerelyAnEgg::
    .string "现在看起来……\n"
    .string "它只是一个蛋！$"

