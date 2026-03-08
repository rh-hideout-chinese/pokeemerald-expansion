SilphCo_9F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_9F_OnLoad
	.byte 0

SilphCo_9F_OnLoad::
	call_if_unset FLAG_SILPH_9F_DOOR_1, EventScript_Close9FDoor1
	call_if_unset FLAG_SILPH_9F_DOOR_2, EventScript_Close9FDoor2
	call_if_unset FLAG_SILPH_9F_DOOR_3, EventScript_Close9FDoor3
	call_if_unset FLAG_SILPH_9F_DOOR_4, EventScript_Close9FDoor4
	end

SilphCo_9F_EventScript_HealWoman::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_9F_EventScript_HealWomanRocketsGone
	msgbox SilphCo_9F_Text_YouShouldTakeQuickNap
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SilphCo_9F_Text_DontGiveUp
	release
	end

SilphCo_9F_EventScript_HealWomanRocketsGone::
	msgbox SilphCo_9F_Text_ThankYouSoMuch
	release
	end

SilphCo_9F_EventScript_FloorSign::
	msgbox SilphCo_9F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_9F_EventScript_Ed::
	trainerbattle_single TRAINER_SCIENTIST_ED, SilphCo_9F_Text_EdIntro, SilphCo_9F_Text_EdDefeat
	msgbox SilphCo_9F_Text_EdPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_9F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_37, SilphCo_9F_Text_Grunt1Intro, SilphCo_9F_Text_Grunt1Defeat
	msgbox SilphCo_9F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_9F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_38, SilphCo_9F_Text_Grunt2Intro, SilphCo_9F_Text_Grunt2Defeat
	msgbox SilphCo_9F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_9F_Text_YouShouldTakeQuickNap::
    .string "你看起来很累。\n"
    .string "你应该快去休息一下。$"

SilphCo_9F_Text_DontGiveUp::
    .string "不要放弃！$"

SilphCo_9F_Text_ThankYouSoMuch::
    .string "太感谢你了。$"

SilphCo_9F_Text_Grunt1Intro::
    .string "你的宝可梦看起来很喜欢你，\n"
    .string "孩子！$"

SilphCo_9F_Text_Grunt1Defeat::
    .string "嘎哈哈哈！$"

SilphCo_9F_Text_Grunt1PostBattle::
    .string "要是我在你的年龄就已经\n"
    .string "成为一个训练家的话……$"

SilphCo_9F_Text_EdIntro::
    .string "你的宝可梦有弱点！\n"
    .string "我能感觉到这些弱点！$"

SilphCo_9F_Text_EdDefeat::
    .string "你彻底打败了我！$"

SilphCo_9F_Text_EdPostBattle::
    .string "利用对方的弱点做出对策。\n"
    .string "想想属性优势。$"

SilphCo_9F_Text_Grunt2Intro::
    .string "我是火箭队\n"
    .string "四兄弟之一！$"

SilphCo_9F_Text_Grunt2Defeat::
    .string "哇\n"
    .string "兄弟们，我输了！$"

SilphCo_9F_Text_Grunt2PostBattle::
    .string "我的兄弟们会为我报仇的！$"

SilphCo_9F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "9层$"

