SilphCo_4F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_4F_OnLoad
	.byte 0

SilphCo_4F_OnLoad::
	call_if_unset FLAG_SILPH_4F_DOOR_1, EventScript_Close4FDoor1
	call_if_unset FLAG_SILPH_4F_DOOR_2, EventScript_Close4FDoor2
	end

SilphCo_4F_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_4F_EventScript_WorkerMRocketsGone
	msgbox SilphCo_4F_Text_CantYouSeeImHiding
	release
	end

SilphCo_4F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_4F_Text_TeamRocketIsGone
	release
	end

SilphCo_4F_EventScript_FloorSign::
	msgbox SilphCo_4F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_4F_EventScript_Rodney::
	trainerbattle_single TRAINER_SCIENTIST_RODNEY, SilphCo_4F_Text_RodneyIntro, SilphCo_4F_Text_RodneyDefeat
	msgbox SilphCo_4F_Text_RodneyPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_4F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_26, SilphCo_4F_Text_Grunt1Intro, SilphCo_4F_Text_Grunt1Defeat
	msgbox SilphCo_4F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_4F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_27, SilphCo_4F_Text_Grunt2Intro, SilphCo_4F_Text_Grunt2Defeat
	msgbox SilphCo_4F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_4F_Text_CantYouSeeImHiding::
    .string "嘘！\n"
    .string "你看不见我在躲人吗？$"

SilphCo_4F_Text_TeamRocketIsGone::
    .string "咦？\n"
    .string "火箭队走了吗？$"

SilphCo_4F_Text_Grunt1Intro::
    .string "火箭队已经控制了\n"
    .string "整个西尔佛公司！$"

SilphCo_4F_Text_Grunt1Defeat::
    .string "啊！$"

SilphCo_4F_Text_Grunt1PostBattle::
    .string "哇哈哈哈\n"
    .string "我的老大一直都想占领这地方！$"

SilphCo_4F_Text_RodneyIntro::
    .string "我的宝可梦是我忠实的仆人。$"

SilphCo_4F_Text_RodneyDefeat::
    .string "该死！\n"
    .string "你们这些弱小的宝可梦！$"

SilphCo_4F_Text_RodneyPostBattle::
    .string "这些门都是用电子\n"
    .string "锁锁定的。\p"
    .string "看来需要一把卡片钥匙来打开\n"
    .string "这些门。$"

SilphCo_4F_Text_Grunt2Intro::
    .string "发现入侵者！$"

SilphCo_4F_Text_Grunt2Defeat::
    .string "你是谁？$"

SilphCo_4F_Text_Grunt2PostBattle::
    .string "我最好去报告在11楼的老大！$"

SilphCo_4F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "4层$"

