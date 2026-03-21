SilphCo_11F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_11F_OnLoad
	.byte 0

SilphCo_11F_OnLoad::
	call_if_unset FLAG_SILPH_11F_DOOR, EventScript_Close11FDoor
	end

SilphCo_11F_EventScript_President::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MASTER_BALL_FROM_SILPH, SilphCo_11F_EventScript_AlreadyGotMasterBall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SilphCo_11F_EventScript_PresidentThanksMale
	call_if_eq VAR_RESULT, FEMALE, SilphCo_11F_EventScript_PresidentThanksFemale
	checkitemspace ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, SilphCo_11F_EventScript_NoRoomForMasterBall
	giveitem_msg SilphCo_11F_Text_ObtainedMasterBallFromPresident, ITEM_MASTER_BALL, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox SilphCo_11F_Text_ThatsOurSecretPrototype
	setflag FLAG_GOT_MASTER_BALL_FROM_SILPH
	release
	end

SilphCo_11F_EventScript_PresidentThanksMale::
	msgbox SilphCo_11F_Text_ThanksForSavingMeDearBoy
	return

SilphCo_11F_EventScript_PresidentThanksFemale::
	msgbox SilphCo_11F_Text_ThanksForSavingMeDearGirl
	return

SilphCo_11F_EventScript_NoRoomForMasterBall::
	msgbox SilphCo_11F_Text_YouHaveNoRoomForThis
	release
	end

SilphCo_11F_EventScript_AlreadyGotMasterBall::
	msgbox SilphCo_11F_Text_ThatsOurSecretPrototype
	release
	end

SilphCo_11F_EventScript_Secretary::
	msgbox SilphCo_11F_Text_ThanksForRescuingUs, MSGBOX_NPC
	end

SilphCo_11F_EventScript_GiovanniTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto SilphCo_11F_EventScript_BattleGiovanni
	end

SilphCo_11F_EventScript_GiovanniTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto SilphCo_11F_EventScript_BattleGiovanni
	end

SilphCo_11F_EventScript_BattleGiovanni::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_SILPH_CO_GIOVANNI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	msgbox SilphCo_11F_Text_GiovanniIntro
	closemessage
	call_if_eq VAR_TEMP_1, 0, SilphCo_11F_EventScript_GiovanniApproachLeft
	call_if_eq VAR_TEMP_1, 1, SilphCo_11F_EventScript_GiovanniApproachRight
	setvar VAR_LAST_TALKED, LOCALID_SILPH_CO_GIOVANNI
	trainerbattle_no_intro TRAINER_BOSS_GIOVANNI_2, SilphCo_11F_Text_GiovanniDefeat
	msgbox SilphCo_11F_Text_GiovanniPostBattle
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SILPH_CO_GIOVANNI
	removeobject LOCALID_SILPH_CO_11F_GRUNT1
	removeobject LOCALID_SILPH_CO_11F_GRUNT2
	fadescreen FADE_FROM_BLACK
	setvar VAR_MAP_SCENE_SILPH_CO_11F, 1
	setflag FLAG_HIDE_SAFFRON_ROCKETS
	clearflag FLAG_HIDE_SAFFRON_CIVILIANS
	releaseall
	end

SilphCo_11F_EventScript_GiovanniApproachLeft::
	applymovement LOCALID_SILPH_CO_GIOVANNI, SilphCo_11F_Movement_GiovanniApproachLeft
	applymovement LOCALID_PLAYER, SilphCo_11F_Movement_PlayerFaceGiovanni
	waitmovement 0
	return

SilphCo_11F_EventScript_GiovanniApproachRight::
	applymovement LOCALID_SILPH_CO_GIOVANNI, SilphCo_11F_Movement_GiovanniApproachRight
	waitmovement 0
	return

SilphCo_11F_Movement_GiovanniApproachLeft::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

SilphCo_11F_Movement_GiovanniApproachRight::
	walk_down
	walk_down
	walk_down
	step_end

SilphCo_11F_Movement_PlayerFaceGiovanni::
	delay_16
	delay_16
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_right
	step_end

@ Unused
SilphCo_11F_EventScript_Monitor::
	msgbox SilphCo_11F_Text_MonitorHasMonsOnIt, MSGBOX_SIGN
	end

SilphCo_11F_EventScript_FloorSign::
	msgbox SilphCo_11F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_11F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_40, SilphCo_11F_Text_Grunt1Intro, SilphCo_11F_Text_Grunt1Defeat
	msgbox SilphCo_11F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_11F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_41, SilphCo_11F_Text_Grunt2Intro, SilphCo_11F_Text_Grunt2Defeat
	msgbox SilphCo_11F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_11F_Text_ThanksForSavingMeDearBoy::
    .string "总裁：哦，勇敢的少年！\n"
    .string "谢谢你救了西尔佛。\p"
    .string "我永远不会忘记，你在我们危险的时候\n"
    .string "救了我们。\p"
    .string "我必须想办法来感谢你。\p"
    .string "我很富有，我可以给你\n"
    .string "任何东西。\p"
    .string "来拿着，这个或许有用。$"

SilphCo_11F_Text_ThanksForSavingMeDearGirl::
    .string "总裁：哦，亲爱的少女！\n"
    .string "谢谢你救了西尔佛。\p"
    .string "我永远不会忘记，你在我们危险的时候\n"
    .string "救了我们。\p"
    .string "我要想办法来感谢你。\p"
    .string "我很富有，我可以给你\n"
    .string "任何东西。\p"
    .string "来拿着，这个或许有用。$"

SilphCo_11F_Text_ObtainedMasterBallFromPresident::
    .string "{PLAYER}从总裁那里\n"
    .string "得到了一个大师球！$"

SilphCo_11F_Text_ThatsOurSecretPrototype::
    .string "总裁：你在任何地方\n"
    .string "都买不到它。\p"
    .string "这是我们秘密制作的试验品\n"
    .string "大师球。\p"
    .string "它将能成功收服任何\n"
    .string "宝可梦！\p"
    .string "不过你在使用它时\n"
    .string "可不要声张。$"

SilphCo_11F_Text_YouHaveNoRoomForThis::
    .string "你的背包里没有空间了。$"

SilphCo_11F_Text_ThanksForRescuingUs::
    .string "秘书：谢谢你救了我们所有人\p"
    .string "我们全公司上下，包括总裁，\n"
    .string "都欠了你一个天大的人情。$"

SilphCo_11F_Text_GiovanniIntro::
    .string "啊，{PLAYER}！\n"
    .string "我们又见面了！\p"
    .string "总裁和我正在讨论\n"
    .string "一个重要的商业计划。\p"
    .string "你还是别太关心\n"
    .string "大人的事为好……\p"
    .string "知道这些可是相当痛苦的呢！$"

SilphCo_11F_Text_GiovanniDefeat::
    .string "呃！！\n"
    .string "我又输了！？$"

SilphCo_11F_Text_GiovanniPostBattle::
    .string "该死！\n"
    .string "你毁了我们在西尔佛的计划！\p"
    .string "但是，火箭队不会倒下的！\p"
    .string "{PLAYER}！永远不要忘记所有\n"
    .string "宝可梦都是为火箭队存在的！\p"
    .string "我得走了，但我会回来的！$"

SilphCo_11F_Text_Grunt2Intro::
    .string "给我站住！\n"
    .string "你敢再走一步！$"

SilphCo_11F_Text_Grunt2Defeat::
    .string "不要……\n"
    .string "求你了！$"

SilphCo_11F_Text_Grunt2PostBattle::
    .string "那么，你想要见我的老大？$"

SilphCo_11F_Text_Grunt1Intro::
    .string "站住！你和我的老大\n"
    .string "预约过吗？$"

SilphCo_11F_Text_Grunt1Defeat::
    .string "哇哇哇！\n"
    .string "不好了！$"

SilphCo_11F_Text_Grunt1PostBattle::
    .string "走路给我小心点……\n"
    .string "我的老大喜欢强大的宝可梦！$"

SilphCo_11F_Text_MonitorHasMonsOnIt::
    .string "显示屏上有宝可梦！$"

SilphCo_11F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "11层$"

