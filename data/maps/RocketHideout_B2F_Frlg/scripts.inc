RocketHideout_B2F_Frlg_MapScripts::
	.byte 0

RocketHideout_B2F_EventScript_Grunt::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_13, RocketHideout_B2F_Text_GruntIntro, RocketHideout_B2F_Text_GruntDefeat
	msgbox RocketHideout_B2F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B2F_Text_GruntIntro::
    .string "老大说用西尔佛观测镜\n"
    .string "你可以看清幽灵。$"

RocketHideout_B2F_Text_GruntDefeat::
    .string "我投降！$"

RocketHideout_B2F_Text_GruntPostBattle::
    .string "火箭队总部有\n"
    .string "四层建在地下。\p"
    .string "你以为你能见到老大吗？$"

