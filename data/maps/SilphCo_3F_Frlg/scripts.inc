SilphCo_3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_3F_OnLoad
	.byte 0

SilphCo_3F_OnLoad::
	call_if_unset FLAG_SILPH_3F_DOOR_1, EventScript_Close3FDoor1
	call_if_unset FLAG_SILPH_3F_DOOR_2, EventScript_Close3FDoor2
	end

SilphCo_3F_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_3F_EventScript_WorkerMRocketsGone
	msgbox SilphCo_3F_Text_WhatAmIToDo
	release
	end

SilphCo_3F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_3F_Text_YouAndYourMonsSavedUs
	release
	end

SilphCo_3F_EventScript_FloorSign::
	msgbox SilphCo_3F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_3F_EventScript_Jose::
	trainerbattle_single TRAINER_SCIENTIST_JOSE, SilphCo_3F_Text_JoseIntro, SilphCo_3F_Text_JoseDefeat
	msgbox SilphCo_3F_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_3F_EventScript_Grunt::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_25, SilphCo_3F_Text_GruntIntro, SilphCo_3F_Text_GruntDefeat
	msgbox SilphCo_3F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_3F_Text_WhatAmIToDo::
    .string "我是西尔佛公司的员工。\n"
    .string "我该做什么好呢？$"

SilphCo_3F_Text_YouAndYourMonsSavedUs::
    .string "{PLAYER}！\n"
    .string "你和你的宝可梦救了我们！$"

SilphCo_3F_Text_GruntIntro::
    .string "不要给我们添乱了，小孩！$"

SilphCo_3F_Text_GruntDefeat::
    .string "我放弃！$"

SilphCo_3F_Text_GruntPostBattle::
    .string "一个提示？你可以用一个卡片钥匙\n"
    .string "来打开门！$"

SilphCo_3F_Text_JoseIntro::
    .string "比起火箭队我\n"
    .string "更支持西尔佛公司！$"

SilphCo_3F_Text_JoseDefeat::
    .string "你真的打败我了！$"

SilphCo_3F_Text_JosePostBattle::
    .string "哼……\p"
    .string "火箭队说，如果我帮助\n"
    .string "他们，他们就会让我研究宝可梦。$"

SilphCo_3F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "3层$"

