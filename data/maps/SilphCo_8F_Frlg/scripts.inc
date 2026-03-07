SilphCo_8F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_8F_OnLoad
	.byte 0

SilphCo_8F_OnLoad::
	call_if_unset FLAG_SILPH_8F_DOOR, EventScript_Close8FDoor
	end

SilphCo_8F_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_8F_EventScript_WorkerMRocketsGone
	msgbox SilphCo_8F_Text_WonderIfSilphIsFinished
	release
	end

SilphCo_8F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_8F_Text_ThanksForSavingUs
	release
	end

SilphCo_8F_EventScript_FloorSign::
	msgbox SilphCo_8F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_8F_EventScript_Parker::
	trainerbattle_single TRAINER_SCIENTIST_PARKER, SilphCo_8F_Text_ParkerIntro, SilphCo_8F_Text_ParkerDefeat
	msgbox SilphCo_8F_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_32, SilphCo_8F_Text_Grunt1Intro, SilphCo_8F_Text_Grunt1Defeat
	msgbox SilphCo_8F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_36, SilphCo_8F_Text_Grunt2Intro, SilphCo_8F_Text_Grunt2Defeat
	msgbox SilphCo_8F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_Text_WonderIfSilphIsFinished::
    .string "恐怕西尔佛已经完蛋了……$"

SilphCo_8F_Text_ThanksForSavingUs::
    .string "谢谢你救了我们！$"

SilphCo_8F_Text_Grunt1Intro::
    .string "你前进的道路到此为止$"

SilphCo_8F_Text_Grunt1Defeat::
    .string "如果你没有足够的勇气的话……！$"

SilphCo_8F_Text_Grunt1PostBattle::
    .string "如果你不马上滚回去……\n"
    .string "我要叫你好看！$"

SilphCo_8F_Text_ParkerIntro::
    .string "你给我们带来太多的麻烦了！$"

SilphCo_8F_Text_ParkerDefeat::
    .string "嗯？\n"
    .string "我输了？$"

SilphCo_8F_Text_ParkerPostBattle::
    .string "那么，你有什么对西尔佛\n"
    .string "大楼的迷宫有什么看法？$"

SilphCo_8F_Text_Grunt2Intro::
    .string "我是火箭队\n"
    .string "四兄弟之一！$"

SilphCo_8F_Text_Grunt2Defeat::
    .string "哇！\n"
    .string "啊，兄弟们！$"

SilphCo_8F_Text_Grunt2PostBattle::
    .string "我会把你留给我的兄弟们来对付。$"

SilphCo_8F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "8层$"

SilphCo_8F_Text_ToRocketBossMonsAreTools::
    .string "火箭队的老大\n"
    .string "是一个特别残忍的人！\p"
    .string "对他而言，宝可梦只是可以\n"
    .string "被利用的工具。\p"
    .string "如果这家伙接管了\n"
    .string "我们的公司就完了……$"
