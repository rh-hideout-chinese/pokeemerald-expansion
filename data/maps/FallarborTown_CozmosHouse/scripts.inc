FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
    .string "索蓝斯博士：唉…\n真后悔被火岩队\l骗出了能找到陨石的\l地点…\p流星瀑布的陨石…\n再也不会属于我了…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
    .string "哦！\n啊？\p那个东西…\p是真的吗？\p那是火岩队从流星瀑布\n抢走的陨石吗？\p拜托给我好吗？\p我不会白要的，\n我用这个招式学习器跟你换。$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
    .string "索蓝斯博士：这个\n招式学习器\n是我的谢礼。\l好好使用吧！$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
    .string "索蓝斯博士：啊，不敢相信，\n真是太棒了！\p这样我的研究会有大进展的！$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
    .string "索蓝斯博士：哎，但…\n我好失望…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
    .string "索蓝斯博士：拜托，能把\n那陨石给我吗？\p我不会白要的，\n我用这个招式学习器\n跟你换。$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
    .string "索蓝斯博士和一些火岩队的人\n去了114号公路上的\l流星瀑布。$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
    .string "可怜的索蓝斯博士…\n他一回来就很沮丧…真为他难过。$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
    .string "看看索蓝斯博士…\n他完全兴奋起来了！那样子真可爱。$"

