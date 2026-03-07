MtMoon_B2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_B2F_OnTransition
	.byte 0

MtMoon_B2F_OnTransition::
	call_if_unset FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_ShowFossils
	end

MtMoon_B2F_EventScript_ShowFossils::
	clearflag FLAG_HIDE_DOME_FOSSIL
	clearflag FLAG_HIDE_HELIX_FOSSIL
	return

MtMoon_B2F_EventScript_MiguelTrigger::
	lockall
	applymovement LOCALID_MIGUEL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call MtMoon_B2F_EventScript_BattleMiguel
	releaseall
	end

MtMoon_B2F_EventScript_Miguel::
	lock
	faceplayer
	goto_if_set FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_MiguelFossilPicked
	goto_if_defeated TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_EventScript_MiguelGoPickFossil
	call MtMoon_B2F_EventScript_BattleMiguel
	release
	end

MtMoon_B2F_EventScript_BattleMiguel::
	textcolor NPC_TEXT_COLOR_MALE
	message MtMoon_B2F_Text_MiguelIntro
	waitmessage
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_MIGUEL
	trainerbattle_no_intro TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_Text_MiguelDefeat
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 1
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	return

MtMoon_B2F_EventScript_MiguelFossilPicked::
	msgbox MtMoon_B2F_Text_LabOnCinnabarRegeneratesFossils
	release
	end

MtMoon_B2F_EventScript_MiguelGoPickFossil::
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	release
	end

MtMoon_B2F_EventScript_DomeFossil::
	lock
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantDomeFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	removeobject LOCALID_DOME_FOSSIL
	giveitem_msg MtMoon_B2F_Text_ObtainedDomeFossil, ITEM_DOME_FOSSIL, 1, MUS_RG_OBTAIN_KEY_ITEM
	closemessage
	delay 10
	applymovement LOCALID_MIGUEL, MtMoon_B2F_Movement_MiguelToHelixFossil
	waitmovement 0
	copyobjectxytoperm LOCALID_MIGUEL
	textcolor NPC_TEXT_COLOR_MALE
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message MtMoon_B2F_Text_ThenThisFossilIsMine
	waitmessage
	waitfanfare
	removeobject LOCALID_HELIX_FOSSIL
	setflag FLAG_GOT_DOME_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	release
	end

MtMoon_B2F_Movement_MiguelToHelixFossil::
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

MtMoon_B2F_EventScript_HelixFossil::
	lock
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantHelixFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	removeobject LOCALID_HELIX_FOSSIL
	giveitem_msg MtMoon_B2F_Text_ObtainedHelixFossil, ITEM_HELIX_FOSSIL, 1, MUS_RG_OBTAIN_KEY_ITEM
	closemessage
	delay 10
	applymovement LOCALID_MIGUEL, MtMoon_B2F_Movement_MiguelToDomeFossil
	waitmovement 0
	copyobjectxytoperm LOCALID_MIGUEL
	textcolor NPC_TEXT_COLOR_MALE
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message MtMoon_B2F_Text_ThenThisFossilIsMine
	waitmessage
	waitfanfare
	removeobject LOCALID_DOME_FOSSIL
	setflag FLAG_GOT_HELIX_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	release
	end

MtMoon_B2F_EventScript_DontTakeFossil::
	release
	end

MtMoon_B2F_Movement_MiguelToDomeFossil::
	walk_up
	walk_up
	walk_up
	step_end

MtMoon_B2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT, MtMoon_B2F_Text_Grunt1Intro, MtMoon_B2F_Text_Grunt1Defeat
	msgbox MtMoon_B2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_2, MtMoon_B2F_Text_Grunt2Intro, MtMoon_B2F_Text_Grunt2Defeat
	msgbox MtMoon_B2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_3, MtMoon_B2F_Text_Grunt3Intro, MtMoon_B2F_Text_Grunt3Defeat
	msgbox MtMoon_B2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_4, MtMoon_B2F_Text_Grunt4Intro, MtMoon_B2F_Text_Grunt4Defeat
	msgbox MtMoon_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_Text_MiguelIntro::
    .string "嘿，站住！\p"
    .string "这些化石是我发现的！\n"
    .string "它们都是我的！$"

MtMoon_B2F_Text_MiguelDefeat::
    .string "算了！\n"
    .string "我们平分吧！$"

MtMoon_B2F_Text_WellEachTakeAFossil::
    .string "化石我们一人一个！\n"
    .string "不要贪心啊！$"

MtMoon_B2F_Text_ThenThisFossilIsMine::
    .string "好吧。\n"
    .string "那这个化石就是我的了！$"

MtMoon_B2F_Text_LabOnCinnabarRegeneratesFossils::
    .string "在遥远的红莲镇上，\n"
    .string "有一个宝可梦实验室。\p"
    .string "实验室里的研究人员从事着\n"
    .string "从化石中复活宝可梦的研究。$"

MtMoon_B2F_Text_Grunt1Intro::
    .string "我们火箭队将会找到化石！\p"
    .string "然后把宝可梦们从化石中复活，\n"
    .string "让我们都发大财！$"

MtMoon_B2F_Text_Grunt1Defeat::
    .string "啊！\n"
    .string "我生气了！$"

MtMoon_B2F_Text_Grunt1PostBattle::
    .string "我很生气！\n"
    .string "你将被列入火箭队的黑名单！$"

MtMoon_B2F_Text_Grunt2Intro::
    .string "我们火箭队是专门\n"
    .string "掠夺宝可梦的组织！\l"
    .string "我们的力量强大到令人颤抖！$"

MtMoon_B2F_Text_Grunt2Defeat::
    .string "被我搞砸了！$"

MtMoon_B2F_Text_Grunt2PostBattle::
    .string "该死！\n"
    .string "我的队友不会袖手旁观的！$"

MtMoon_B2F_Text_Grunt3Intro::
    .string "我们在这里做大事呢！\n"
    .string "小孩给我走开点！$"

MtMoon_B2F_Text_Grunt3Defeat::
    .string "呃，你还不赖嘛……$"

MtMoon_B2F_Text_Grunt3PostBattle::
    .string "如果你找到化石就赶快交给我，\n"
    .string "然后你就可以滚了！$"

MtMoon_B2F_Text_Grunt4Intro::
    .string "小孩就不要给大人添乱！\p"
    .string "这可不是什么好事！$"

MtMoon_B2F_Text_Grunt4Defeat::
    .string "热死我了！$"

MtMoon_B2F_Text_Grunt4PostBattle::
    .string "宝可梦在这里生活\n"
    .string "的历史比人类更悠久。$"

MtMoon_B2F_Text_YouWantDomeFossil::
    .string "你想要甲壳化石吗？$"

MtMoon_B2F_Text_YouWantHelixFossil::
    .string "你想要贝壳化石吗？$"

MtMoon_B2F_Text_ObtainedHelixFossil::
    .string "获得了贝壳化石！$"

MtMoon_B2F_Text_ObtainedDomeFossil::
    .string "获得了甲壳化石！$"

