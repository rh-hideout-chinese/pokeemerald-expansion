AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
    .string "什么？什么？\n你找海洋队做什么？\p我们的老大不在这里！\n他去找一些很重要的东西了！\p……\n他去哪了？\p哇哈哈！你以为我会告诉你\n这么重要的事吗？$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
    .string "什么？什么？\n你是熔岩队的人吗？\p我听说熔岩队试图\n在他们的基地里唤醒\l一只不得了的宝可梦，\p但是他们的基地在哪里呢？$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
    .string "什么？什么？\n你找海洋队做什么？\p我们的老大不在这里！\n他去抢潜水艇了！\p……\n他去哪了？\p哇哈哈！你以为我会告诉你\n这么重要的事吗？$"

AquaHideout_1F_Text_BossIsOnRoute122:
    .string "什么？什么？\n你找海洋队做什么？\p我们的老大不在这里！\n他到122号水路上的送神山去了！\p……\n他去干什么？\p哇哈哈！你以为我会告诉你\n这么重要的事吗？$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
    .string "什么？什么？\n你是熔岩队的人吗？\p我听说熔岩队正在烟囱山\n寻找一只极其可怕的宝可梦。\p那宝可梦到底是什么样子啊？$"

AquaHideout_1F_Text_BossIsInSlateportCity:
    .string "什么？什么？\n你找海洋队做什么？\p我们的老大不在这里！\n他到凯那市去了！\p……\n他去干什么？\p哇哈哈！你以为我会告诉你\n这么重要的事吗？$"

AquaHideout_1F_Text_Grunt1Intro:
    .string "哎咦咦咦！\n发现可疑人物！$"

AquaHideout_1F_Text_Grunt1Defeat:
    .string "咕啊啊啊……\n我输了！$"

AquaHideout_1F_Text_Grunt1PostBattle:
    .string "虽然为组织吃了败仗，\n但我的任务完成了……$"

