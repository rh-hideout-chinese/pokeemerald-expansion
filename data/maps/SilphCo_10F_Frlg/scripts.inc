SilphCo_10F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_10F_OnLoad
	.byte 0

SilphCo_10F_OnLoad::
	call_if_unset FLAG_SILPH_10F_DOOR, EventScript_Close10FDoor
	end

SilphCo_10F_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_10F_EventScript_WorkerFRocketsGone
	msgbox SilphCo_10F_Text_WaaaImScared
	release
	end

SilphCo_10F_EventScript_WorkerFRocketsGone::
	msgbox SilphCo_10F_Text_KeepMeCryingASecret
	release
	end

SilphCo_10F_EventScript_FloorSign::
	msgbox SilphCo_10F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_10F_EventScript_Travis::
	trainerbattle_single TRAINER_SCIENTIST_TRAVIS, SilphCo_10F_Text_TravisIntro, SilphCo_10F_Text_TravisDefeat
	msgbox SilphCo_10F_Text_TravisPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_EventScript_Grunt::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_39, SilphCo_10F_Text_GruntIntro, SilphCo_10F_Text_GruntDefeat
	msgbox SilphCo_10F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_Text_GruntIntro::
    .string "欢迎来到10F！\n"
    .string "很高兴你能找到我！$"

SilphCo_10F_Text_GruntDefeat::
    .string "我震惊了！$"

SilphCo_10F_Text_GruntPostBattle::
    .string "做的不错，但会议室\n"
    .string "在这层楼上。$"

SilphCo_10F_Text_TravisIntro::
    .string "够了，你和你愚蠢的游戏！$"

SilphCo_10F_Text_TravisDefeat::
    .string "不能让你继续下去了！$"

SilphCo_10F_Text_TravisPostBattle::
    .string "你打败了我，满意了吗？\n"
    .string "那么回家吧！$"

SilphCo_10F_Text_WaaaImScared::
    .string "哇啊啊啊啊！\n"
    .string "我很害怕！$"

SilphCo_10F_Text_KeepMeCryingASecret::
    .string "至于我哭的原因……\n"
    .string "请为我保密。$"

SilphCo_10F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "10层$"

