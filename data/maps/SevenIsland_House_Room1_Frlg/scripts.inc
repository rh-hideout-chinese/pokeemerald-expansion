.equ TRAINER_VISITING, VAR_TEMP_1

SevenIsland_House_Room1_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_House_Room1_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SevenIsland_House_Room1_OnFrame
	.byte 0

SevenIsland_House_Room1_OnTransition::
	special ValidateEReaderTrainer
	call_if_eq VAR_RESULT, 0, SevenIsland_House_Room1_EventScript_SetTrainerVisitingLayout
	call_if_ne VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 0, SevenIsland_House_Room1_EventScript_MoveOldWomanToDoor
	end

SevenIsland_House_Room1_EventScript_SetTrainerVisitingLayout::
	setvar TRAINER_VISITING, TRUE
	setobjectxyperm LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN, 4, 2
	setobjectmovementtype LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN
	setmaplayoutindex LAYOUT_SEVEN_ISLAND_HOUSE_ROOM1_DOOR_OPEN
	return

SevenIsland_House_Room1_EventScript_MoveOldWomanToDoor::
	setobjectxyperm LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN, 3, 2
	setobjectmovementtype LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN, MOVEMENT_TYPE_FACE_RIGHT
	return

SevenIsland_House_Room1_OnFrame::
	map_script_2 VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 1, SevenIsland_House_Room1_EventScript_OldWomanCommentOnBattle
	map_script_2 VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 2, SevenIsland_House_Room1_EventScript_OldWomanCommentOnBattle
	map_script_2 VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 3, SevenIsland_House_Room1_EventScript_OldWomanCommentOnBattle
	.2byte 0

SevenIsland_House_Room1_EventScript_OldWomanCommentOnBattle::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	applymovement LOCALID_PLAYER, SevenIsland_House_Room1_Movement_PlayerReEnterRoom
	waitmovement 0
	applymovement LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN, SevenIsland_House_Room1_Movement_OldWomanWalkBehindPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_SEVEN_ISLAND_HOUSE_OLD_WOMAN
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call_if_eq VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 1, SevenIsland_House_Room1_EventScript_BattleWonComment
	call_if_eq VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 2, SevenIsland_House_Room1_EventScript_BattleLostComment
	call_if_eq VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 3, SevenIsland_House_Room1_EventScript_BattleTiedComment
	special LoadPlayerParty
	setvar VAR_MAP_SCENE_SEVEN_ISLAND_HOUSE_ROOM1, 0
	releaseall
	end

SevenIsland_House_Room1_EventScript_BattleWonComment::
	msgbox SevenIsland_House_Room1_Text_AstoundingBattle
	return

SevenIsland_House_Room1_EventScript_BattleLostComment::
	msgbox SevenIsland_House_Room1_Text_FeelYourDisappointment
	return

SevenIsland_House_Room1_EventScript_BattleTiedComment::
	msgbox SevenIsland_House_Room1_Text_DrawWasIt
	return

SevenIsland_House_Room1_Movement_PlayerReEnterRoom::
	walk_down
	step_end

SevenIsland_House_Room1_Movement_OldWomanWalkBehindPlayer::
	walk_right
	walk_in_place_faster_down
	step_end

SevenIsland_House_Room1_EventScript_OldWoman::
	lock
	faceplayer
	special ValidateEReaderTrainer
	call_if_eq VAR_RESULT, 1, SevenIsland_House_Room1_EventScript_InvalidVisitingTrainer
	goto_if_eq TRAINER_VISITING, TRUE, SevenIsland_House_Room1_EventScript_TrainerVisiting
	msgbox SevenIsland_House_Room1_Text_OnlyEnjoymentWatchingBattles
	release
	end

SevenIsland_House_Room1_EventScript_InvalidVisitingTrainer::
	msgbox SevenIsland_House_Room1_Text_OnlyEnjoymentWatchingBattles
	release
	end

SevenIsland_House_Room1_EventScript_TrainerVisiting::
	special SavePlayerParty
	special BufferEReaderTrainerName
	msgbox SevenIsland_House_Room1_Text_ChallengeVisitingTrainer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SevenIsland_House_Room1_EventScript_DeclineBattle
	call SevenIsland_House_Room1_EventScript_ChooseParty
	goto_if_eq VAR_RESULT, 0, SevenIsland_House_Room1_EventScript_DeclineBattle
	msgbox SevenIsland_House_Room1_Text_SaveProgressBeforeBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SevenIsland_House_Room1_EventScript_DeclineBattle
	special LoadPlayerParty
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, SevenIsland_House_Room1_EventScript_DeclineBattle
	special SavePlayerParty
	special ReducePlayerPartyToSelectedMons
	msgbox SevenIsland_House_Room1_Text_DontHoldAnythingBack
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, SevenIsland_House_Room1_EventScript_EnterBattleRoomNorth
	call_if_eq VAR_FACING, DIR_EAST, SevenIsland_House_Room1_EventScript_EnterBattleRoomEast
	call_if_eq VAR_FACING, DIR_WEST, SevenIsland_House_Room1_EventScript_EnterBattleRoomWest
	warp MAP_SEVEN_ISLAND_HOUSE_ROOM2, 3, 1
	waitstate
	release
	end

SevenIsland_House_Room1_EventScript_DeclineBattle::
	special LoadPlayerParty
	msgbox SevenIsland_House_Room1_Text_OhYouWontBattle
	release
	end

SevenIsland_House_Room1_EventScript_ChooseParty::
	msgbox SevenIsland_House_Room1_Text_LimitThreeMonsPerSide
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	return

SevenIsland_House_Room1_EventScript_EnterBattleRoomNorth::
	applymovement VAR_LAST_TALKED, SevenIsland_House_Room1_Movement_OldWomanMoveAsideLeft
	applymovement LOCALID_PLAYER, SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomNorth
	waitmovement 0
	return

SevenIsland_House_Room1_EventScript_EnterBattleRoomEast::
	applymovement VAR_LAST_TALKED, SevenIsland_House_Room1_Movement_OldWomanMoveAsideRight
	applymovement LOCALID_PLAYER, SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomEast
	waitmovement 0
	return

SevenIsland_House_Room1_EventScript_EnterBattleRoomWest::
	applymovement VAR_LAST_TALKED, SevenIsland_House_Room1_Movement_OldWomanMoveAsideLeft
	applymovement LOCALID_PLAYER, SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomWest
	waitmovement 0
	return

SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomNorth::
	delay_16
	walk_up
	walk_up
	step_end

SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomEast::
	delay_16
	walk_right
	walk_up
	step_end

SevenIsland_House_Room1_Movement_PlayerEnterBattleRoomWest::
	delay_16
	walk_left
	walk_up
	step_end

SevenIsland_House_Room1_Movement_OldWomanMoveAsideLeft::
	walk_left
	walk_in_place_faster_right
	step_end

SevenIsland_House_Room1_Movement_OldWomanMoveAsideRight::
	walk_right
	walk_in_place_faster_left
	step_end

SevenIsland_House_Room1_EventScript_Box::
	msgbox SevenIsland_House_Room1_Text_SlightBreezeAroundBox, MSGBOX_SIGN
	end

SevenIsland_House_Room1_Text_OnlyEnjoymentWatchingBattles::
    .string "虽然看起来不像，\n"
    .string "但是我年轻时……\p"
    .string "我曾飞到每个地方，\n"
    .string "挑战每一个我遇到的训练家。\p"
    .string "现在，我仅有的乐趣\n"
    .string "就是在看对战时\l"
    .string "回想着我的往事。$"

SevenIsland_House_Room1_Text_SlightBreezeAroundBox::
    .string "在箱子的四周\n"
    .string "有微风吹着。$"

SevenIsland_House_Room1_Text_ChallengeVisitingTrainer::
    .string "啊呀！\n"
    .string "欢迎，我的朋友！\p"
    .string "让我告诉你点东西吧。这里的\n"
    .string "地下层有个隐藏的房间。\p"
    .string "一个叫{STR_VAR_1}的训练家\n"
    .string "在那里等着。\p"
    .string "告诉我，你是来挑战\n"
    .string "{STR_VAR_1}的，对不？$"

SevenIsland_House_Room1_Text_OhYouWontBattle::
    .string "噢……\n"
    .string "你不想对战啊……\p"
    .string "好吧，好吧。\n"
    .string "……\p"
    .string "嗯，如果你想\n"
    .string "改变主意的话，就来找我吧。$"

SevenIsland_House_Room1_Text_LimitThreeMonsPerSide::
    .string "啊！\n"
    .string "你会为我而战？\p"
    .string "那么，这就值得我把\n"
    .string "这些箱子推到一边去。\p"
    .string "……\n"
    .string "不过还有一个小问题。\p"
    .string "这个密室不是建得\n"
    .string "非常牢固。\p"
    .string "我可以把你战斗的\n"
    .string "宝可梦限制在三只吗？$"

SevenIsland_House_Room1_Text_SaveProgressBeforeBattle::
    .string "很好！在你开始前，\n"
    .string "你要先记录吗？$"

SevenIsland_House_Room1_Text_DontHoldAnythingBack::
    .string "好了。\n"
    .string "尽你的全力吧！$"

@ Unused
SevenIsland_House_Room1_Text_StrVar1_1::
    .string "{STR_VAR_1}$"

SevenIsland_House_Room2_Text_MatchEndedUpDraw::
    .string "这场比赛打成平手。$"

SevenIsland_House_Room1_Text_DrawWasIt::
    .string "平手，嗯哼？\p"
    .string "不过，我可以说这场\n"
    .string "是一场很精彩的比赛。\p"
    .string "我可以肯定的说，\n"
    .string "这是一场很有深度的比赛！$"

@ Unused
SevenIsland_House_Room1_Text_StrVar1_2::
    .string "{STR_VAR_1}$"

SevenIsland_House_Room1_Text_AstoundingBattle::
    .string "太美了！\p"
    .string "太美了，真的！\n"
    .string "真是场令人震惊的比赛！\p"
    .string "真让人非常震惊，真的。\n"
    .string "这让我感动得流泪了！\p"
    .string "信任和熟练的技巧还有\n"
    .string "巧妙的回避！\p"
    .string "力量跟力量间的对决！\p"
    .string "是的！\n"
    .string "这就是最壮丽的事情了！$"

@ Unused
SevenIsland_House_Room1_Text_StrVar1_3::
    .string "{STR_VAR_1}$"

SevenIsland_House_Room1_Text_FeelYourDisappointment::
    .string "太糟糕了\n"
    .string "我能感到你的失落。\p"
    .string "不过，\n"
    .string "失败乃是成功之母！\p"
    .string "运用它，从它学习，然后让它\n"
    .string "成为你寻求成功的动力。\p"
    .string "忘记这次失败，\n"
    .string "然后加倍的训练！$"

