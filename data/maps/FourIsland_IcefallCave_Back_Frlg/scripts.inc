FourIsland_IcefallCave_Back_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_IcefallCave_Back_OnTransition
	.byte 0

FourIsland_IcefallCave_Back_OnTransition::
	call_if_eq VAR_MAP_SCENE_ICEFALL_CAVE_BACK, 1, FourIsland_IcefallCave_Back_EventScript_HideLorelei
	end

FourIsland_IcefallCave_Back_EventScript_HideLorelei::
	setflag FLAG_HIDE_ICEFALL_CAVE_LORELEI
	return

FourIsland_IcefallCave_Back_EventScript_LoreleiRocketsScene::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox FourIsland_IcefallCave_Back_Text_LoreleiKeepHandsOffMons
	applymovement LOCALID_ICEFALL_ROCKET1, FourIsland_IcefallCave_Back_Movement_WalkInPlaceDown
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FourIsland_IcefallCave_Back_Text_ShutItLadyLeaveUsBe
	closemessage
	playse SE_PIN
	applymovement LOCALID_ICEFALL_LORELEI, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ICEFALL_LORELEI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_ICEFALL_LORELEI, Common_Movement_Delay48
	waitmovement 0
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox FourIsland_IcefallCave_Back_Text_LoreleiPlayerHelpMeKickPoachersOut
	closemessage
	applymovement LOCALID_ICEFALL_LORELEI, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 18
	applymovement LOCALID_ICEFALL_LORELEI, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 35
	applymovement LOCALID_ICEFALL_ROCKET3, FourIsland_IcefallCave_Back_Movement_Rocket3FaceLorelei
	applymovement LOCALID_ICEFALL_LORELEI, FourIsland_IcefallCave_Back_Movement_LoreleiToRockets
	applymovement LOCALID_PLAYER, FourIsland_IcefallCave_Back_Movement_PlayerToRockets
	waitmovement 0
	applymovement LOCALID_ICEFALL_ROCKET2, FourIsland_IcefallCave_Back_Movement_WalkInPlaceDown
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FourIsland_IcefallCave_Back_Text_GruntIntro
	setvar VAR_LAST_TALKED, LOCALID_ICEFALL_ROCKET3
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_45, FourIsland_IcefallCave_Back_Text_GruntDefeat
	applymovement LOCALID_ICEFALL_LORELEI, FourIsland_IcefallCave_Back_Movement_WalkInPlaceUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox FourIsland_IcefallCave_Back_Text_LoreleiWhereHaveYouTakenMons
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FourIsland_IcefallCave_Back_Text_NotTellingYouThat
	textcolor NPC_TEXT_COLOR_FEMALE
	message FourIsland_IcefallCave_Back_Text_LoreleiWellDeepFreezeYou
	waitmessage
	waitse
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
	waitbuttonpress
	waitmoncry
	applymovement LOCALID_ICEFALL_ROCKET1, FourIsland_IcefallCave_Back_Movement_Rocket1ReactToThreat
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FourIsland_IcefallCave_Back_Text_OkayRocketWareHouseFiveIsland
	closemessage
	applymovement LOCALID_ICEFALL_LORELEI, FourIsland_IcefallCave_Back_Movement_LoreleiWatchRocketsExit
	applymovement LOCALID_PLAYER, FourIsland_IcefallCave_Back_Movement_PlayerWatchRocketsExit
	applymovement LOCALID_ICEFALL_ROCKET1, FourIsland_IcefallCave_Back_Movement_Rocket1Exit
	applymovement LOCALID_ICEFALL_ROCKET2, FourIsland_IcefallCave_Back_Movement_Rocket2Exit
	applymovement LOCALID_ICEFALL_ROCKET3, FourIsland_IcefallCave_Back_Movement_Rocket3Exit
	waitmovement 0
	removeobject LOCALID_ICEFALL_ROCKET1
	removeobject LOCALID_ICEFALL_ROCKET2
	removeobject LOCALID_ICEFALL_ROCKET3
	delay 50
	applymovement LOCALID_ICEFALL_LORELEI, FourIsland_IcefallCave_Back_Movement_LoreleiWalkToPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox FourIsland_IcefallCave_Back_Text_ThankYouThisIsAwful
	setflag FLAG_HIDE_RUIN_VALLEY_SCIENTIST
	clearflag FLAG_HIDE_LORELEI_IN_HER_HOUSE
	setvar VAR_MAP_SCENE_ICEFALL_CAVE_BACK, 1
	releaseall
	end

FourIsland_IcefallCave_Back_Movement_PlayerToRockets::
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

FourIsland_IcefallCave_Back_Movement_PlayerWatchRocketsExit::
	delay_16
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

FourIsland_IcefallCave_Back_Movement_WalkInPlaceDown::
	walk_in_place_down
	step_end

FourIsland_IcefallCave_Back_Movement_UnusedPushRight::
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

FourIsland_IcefallCave_Back_Movement_Rocket1ReactToThreat::
	walk_in_place_fast_down
	step_end

FourIsland_IcefallCave_Back_Movement_Rocket1Exit::
	walk_right
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

FourIsland_IcefallCave_Back_Movement_Rocket2Exit::
	delay_16
	walk_left
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

FourIsland_IcefallCave_Back_Movement_Rocket3Exit::
	delay_16
	walk_down
	delay_16
	walk_down
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

FourIsland_IcefallCave_Back_Movement_Rocket3FaceLorelei::
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

FourIsland_IcefallCave_Back_Movement_UnusedWalkLeft::
	walk_left
	walk_left
	step_end

FourIsland_IcefallCave_Back_Movement_LoreleiToRockets::
	walk_left
	walk_up
	step_end

FourIsland_IcefallCave_Back_Movement_WalkInPlaceUp::
	walk_in_place_up
	step_end

FourIsland_IcefallCave_Back_Movement_LoreleiWatchRocketsExit::
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

FourIsland_IcefallCave_Back_Movement_LoreleiWalkToPlayer::
	walk_right
	step_end

FourIsland_IcefallCave_Back_EventScript_Lorelei::
	msgbox FourIsland_IcefallCave_Back_Text_ThankYouThisIsAwful, MSGBOX_NPC
	end

FourIsland_IcefallCave_Back_Text_LoreleiKeepHandsOffMons::
    .string "科拿： 把你肮脏的手从\n"
    .string "洞穴里的宝可梦中挪开！\p"
    .string "照我说的做，不然要你好看！$"

FourIsland_IcefallCave_Back_Text_ShutItLadyLeaveUsBe::
    .string "啊，请冷静一下，小姐，\n"
    .string "让我们冷静一下。\p"
    .string "别让你的眼镜上爬满雾气啊！$"

FourIsland_IcefallCave_Back_Text_LoreleiPlayerHelpMeKickPoachersOut::
    .string "科拿：{PLAYER}？！\n"
    .string "你在这儿做什么？\p"
    .string "别急，我们等会儿能赶上的。\n"
    .string "现在，我需要你的帮助。\p"
    .string "在这些入侵者做出什么之前，\n"
    .string "帮我把他们赶出去。\p"
    .string "他们在这里捉宝可梦，\n"
    .string "然后统统拿拿出去去卖了！\p"
    .string "准备好了吗？\n"
    .string "你去对付他！$"

FourIsland_IcefallCave_Back_Text_GruntIntro::
    .string "什-什么？！\p"
    .string "为啥我们不能用抓到的宝可梦\n"
    .string "做我们想做的事情？$"

FourIsland_IcefallCave_Back_Text_GruntDefeat::
    .string "我们没想到结果会是这样！$"

FourIsland_IcefallCave_Back_Text_LoreleiWhereHaveYouTakenMons::
    .string "科拿：哼。\n"
    .string "真是弱爆了。\p"
    .string "你！\n"
    .string "告诉我！\p"
    .string "你把你们抓到的宝可梦放在哪了\p"
    .string "不说的话我就\n"
    .string "砸烂你的戒指！$"

FourIsland_IcefallCave_Back_Text_NotTellingYouThat::
    .string "没-没门！\n"
    .string "我不会告诉你的！$"

FourIsland_IcefallCave_Back_Text_LoreleiWellDeepFreezeYou::
    .string "科拿：我的拉普拉斯对你们对它同伴的\n"
    .string "所做所为感到十分愤怒。\p"
    .string "如果你不肯说出来的话，\n"
    .string "就让它把你们冻成冰块吧。\p"
    .string "上吧，拉普拉斯！\n"
    .string "急冻光线……$"

FourIsland_IcefallCave_Back_Text_OkayRocketWareHouseFiveIsland::
    .string "哇！好吧！\n"
    .string "我说！\p"
    .string "宝可梦在五之岛的\n"
    .string "火箭队仓库里面。\p"
    .string "就在哪里！我说了！\n"
    .string "我们现在能过去吧！\p"
    .string "……但是我怀疑你能不能进得了\n"
    .string "火箭队仓库！\p"
    .string "呵呵呵呵！$"

FourIsland_IcefallCave_Back_Text_ThankYouThisIsAwful::
    .string "{PLAYER}，谢谢你。\n"
    .string "但情况太糟糕了……\p"
    .string "我在这片岛屿上出生和长大。\p"
    .string "我没想到那些可恶的\n"
    .string "罪犯会来这里……$"

