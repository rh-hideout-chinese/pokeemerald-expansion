.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_SCOTT, 12, 13
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
    .string "叔叔：我想，是宝可梦\n让那孩子打起精神来的…\l但他好像有点兴奋过头了…$"

MauvilleCity_Text_WallyWantToChallengeGym:
    .string "小光：好啦，叔叔，拜托了，\p我想挑战这个道馆，\n我想试试我变得多强了。\p好吗？求你了，好吗？$"

MauvilleCity_Text_UncleYourePushingIt:
    .string "叔叔：好了，好了，小光，\p自从你开始和宝可梦旅行以来，\n确实成长了不少，\p但你不觉得现在就去挑战道馆\n还太早了吗？$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
    .string "小光：我不这么认为，\p只要和拉鲁拉丝齐心协力的话，\n我们就能打败任何人！$"

MauvilleCity_Text_WallyWillYouBattleMe:
    .string "小光：噢，你好，{PLAYER}！\p自从我们上次见面，\n我已经变得更强了。\p{PLAYER}，我想向你和叔叔\n证明这点。\p{PLAYER}，拜托了，\n和我战斗吧？$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
    .string "小光：呃…{PLAYER}，如果你不跟我战斗，\n叔叔就不会相信\l我真的变强了。$"

MauvilleCity_Text_UncleCanYouBattleWally:
    .string "叔叔：你是{PLAYER}{KUN}吧？\n为了小光，\l能请你和他战斗一次吗？\p我想他现在这样\n是不可能听得进劝说的。$"

MauvilleCity_Text_WallyPleaseBattleMe:
    .string "小光：{PLAYER}，拜托了！\n我们战斗吧。$"

MauvilleCity_Text_WallyHereICome:
    .string "小光：{PLAYER}，谢谢。\p好…我要上了！$"

MauvilleCity_Text_WallyDefeat:
    .string "小光：… … … … … … …\p… … … … … … … …\p我输了…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
    .string "小光：叔叔…\n我会回绿荫镇的…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
    .string "{PLAYER}，谢谢。\n做一个训练师也没那么容易，是吗？\p仅仅是让自己的宝可梦去战斗\n还不够，这样并不会成为\l真正的训练师。$"

MauvilleCity_Text_UncleNoNeedToBeDown:
    .string "叔叔：小光，\n不要这么沮丧。\p想想是什么激励着你\n要变得越来越强的？\p好了，我们回家吧，\n大家都在等你呢。$"

MauvilleCity_Text_UncleVisitUsSometime:
    .string "叔叔：{PLAYER}{KUN}，我刚刚才想起来，\n你就是那位看着小光\l抓到他的第一只宝可梦的\l训练师吧？\p有空的话，\n可以来绿荫镇转转吗？\l我想小光也会很高兴的。$"


MauvilleCity_Text_WallyPokenavCall:
    .string "… … … … … …\n… … … … …哔！\p小光：啊，{PLAYER}！\p我只是想告诉你\n我叔叔刚给我买了个口袋领航员！\p现在我随时都\n可以和你联系了，{PLAYER}！\p… … … … … …\n… … … … …咔哒！$"

MauvilleCity_Text_RegisteredWally:
    .string "把小光的信息\n登记到口袋领航员里。$"

MauvilleCity_Text_ScottYouDidntHoldBack:
    .string "亚希达：嘿嘿…\n我刚才一直在看你们的战斗！\p那个叫小光的男孩是你的朋友，\n对吗？\p但你击败他的时候\n没有任何犹豫。\p没错！这才是\n真正的宝可梦战斗！\p我所仰慕的就是这样的训练师！\p… … … … … …\n我会为你加油的！$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
    .string "铁旋：嗨，{PLAYER}{KUN}！\n你看起来挺精神嘛！\l不错，不错，啊哈哈哈哈！\p好！我决定了！\n{PLAYER}{KUN}，我需要帮助！\p紫堇市这里有一个\n叫做新紫堇的地下区域。\p{PLAYER}{KUN}，希望你能\n去那里关掉发电器。\p最近发电器的运转有些失控，\n现在那里不是很安全。\p给，这是\n进入新紫堇的钥匙。$"

MauvilleCity_Text_WattsonWontBeChallenge:
    .string "铁旋：不用担心，\n这对你应该是小菜一碟。\p新紫堇的入口\n在110号公路近海用冲浪一下就到了。\p很简单的，我相信你！\n啊哈哈哈哈！$"

MauvilleCity_Text_WattsonThanksTakeTM:
    .string "铁旋：啊哈哈哈哈！\p我就知道，{PLAYER}{KUN}！我就知道\n叫你去肯定没问题！\p这是我的谢礼——\n十万伏特的招式学习器！\p来，收下它吧！$"

MauvilleCity_Text_WattsonYoungTakeCharge:
    .string "铁旋：啊哈哈哈哈！\p我最喜欢看到年轻人\n挑起重担，引领这个时代！$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
    .string "你知道么，看着宝可梦去战斗\n真是太棒了…\p但如果你的宝可梦受了伤，\n就得赶快帮它治疗。$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
    .string "这个镇子的道路\n通向四面八方，\p因此在这里\n能见到各式各样的人。$"

MauvilleCity_Text_RydelVeryGenerous:
    .string "你去过风野的自行车行了吗？\p那里的主人风野\n是个很大方的人。$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
    .string "就算你骑着自行车，\n野生宝可梦也会跳出来袭击你。$"

MauvilleCity_Text_CitySign:
    .string "紫堇市\n“洋溢着欢乐气息的城市！”$"

MauvilleCity_Text_GymSign:
    .string "紫堇市宝可梦道馆\n馆主：铁旋\l“一个活力与电力四射的男人！”$"

MauvilleCity_Text_BikeShopSign:
    .string "“骑车到砂石路上去，\n晃动爱车的灵魂！”\l风野自行车行$"

MauvilleCity_Text_GameCornerSign:
    .string "“大家的游乐场！”\n紫堇市游戏中心$"

MauvilleCity_Text_ExplainTV:
    .string "嗨，你看电视了吗？\p最近电视台\n设立了很多新节目。\p电视太棒了，有一次\n我意外地发现我朋友上电视了。\p而且有时候电视台根本不告诉你\n你就会出现在荧屏上了。\p希望哪天我也能上电视，\p所以你要\n经常看电视哦。$"

MauvilleCity_Text_BeenCheckingOutTV:
    .string "嗨，你看过电视了吗？$"
