.set LOCALID_ATTENDANT, 1

SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_ATTENDANT, 2, 2
	turnobject LOCALID_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests:
    .string "需要一点点关于华丽大赛\n的建议吗？\p在某些特定种类的行动后\n使用特定招式\l可以给你带来额外的注视度。\p如果你知道该怎么做，\n你可以获得更高的吸引力。\p当然，你的对手会试着\n干扰你宝可梦的表演。$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
    .string "我的爸爸，是华丽大赛裁判\p我不知道长大后做什么\n裁判还是道馆馆主呢？$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
    .string "那个，兄弟，你能理解偶\n有多毛么！你知道么！\l那个，我就想不通了，\l我想不通为啥偶的宝可梦\p从来没赢过？你知道么？！\n所以，那个，偶向裁判抱怨，\p但他们根本不鸟我，\n真那啥的。\p所以那个，说你呢！闭嘴行不？\n那个，偶说，这个拿去！$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment:
    .string "拿着，TM41，\n嘿，就是无理取闹，你在听我说吗？\p就像是，它不允许同一场中\n使用两次同样的的行动，了解？\p嘿，现在，听好，就像是\n希望我并没有给你带来麻烦！$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
    .string "主持：天啊，天啊！\n它难道不是宝可梦中的花花公子？\p请一定快点来参加\n我们完美的华丽大赛！\p你会做得很好的！我相信你！\n我看好你哟！$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
    .string "裁判：你好啊！\n看来你是个训练师！\p那么，对你来说\n千万不要错过华丽大赛！\p获得绿荫镇的华丽大赛通行证\n并且随时可以再来！$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime:
    .string "吸引力时间！\n有什么我可以报导的呢？$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
    .string "他们没有太注意\n我的宝可梦的吸引力…\p哼，那个裁判，他根本\n就不懂得欣赏。$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
    .string "你好！你一定是追求此项活动的\n狂热爱好者。\p为了奖励你的热情\n给你一条忠告吧。\p如果一个行动表现的非常好，\n观众会变得很激动。\p当观众变得激动时\n做出这个行动的宝可梦吸引力就会…\p好了，会发生什么好事你应该\n可以想象得到吧！$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
    .string "我不能这么做！我比我的宝可梦\n还要紧张。\p我的心脏跳得很厉害以至于发抖了！$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike:
    .string "虽然对战和选美并不一样\n但它们也有相似之处。\p你需要更努力并且\n要相信你所培养的宝可梦。$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
    .string "那个宝可梦看起来像是比赛中的\n高手，嗯？\p宝可梦在评判比赛中做得好的话\n会比在吸引力比赛中\l看起来更放松。$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
    .string "你看起来怎么那么难过？\p嘿，我的宝可梦绝对\n是最棒的！$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
    .string "你是不是一直渴望\n宝可梦在吸引力比赛中\l有精神的表演带来的感动呢？$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage:
    .string "宝可梦华丽大赛\n特级会场！$"

