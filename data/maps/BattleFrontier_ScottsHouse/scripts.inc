.set LOCALID_SCOTT, 1

BattleFrontier_ScottsHouse_MapScripts::
	.byte 0

BattleFrontier_ScottsHouse_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_4, BattleFrontier_ScottsHouse_EventScript_GivenBerry
	goto_if_set FLAG_TEMP_3, BattleFrontier_ScottsHouse_EventScript_GivenShield
	goto_if_set FLAG_TEMP_2, BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveItems
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveItems::
	goto_if_unset FLAG_SCOTT_GIVES_BATTLE_POINTS, BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier
	goto_if_unset FLAG_COLLECTED_ALL_SILVER_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols
	goto_if_unset FLAG_COLLECTED_ALL_GOLD_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveShield::
	goto_if_unset FLAG_RECEIVED_SILVER_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield
	goto_if_unset FLAG_RECEIVED_GOLD_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols::
	goto_if_unset FLAG_SYS_TOWER_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols, MSGBOX_DEFAULT
	giveitem ITEM_LANSAT_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_SILVER_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols::
	goto_if_unset FLAG_SYS_TOWER_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols, MSGBOX_DEFAULT
	giveitem ITEM_STARF_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_GOLD_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_BerryPocketFull::
	msgbox BattleFrontier_ScottsHouse_Text_BerryPocketStuffed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenBerry::
	msgbox BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_RandomComment::
	random 3
	goto_if_eq VAR_RESULT, 1, BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment
	goto_if_eq VAR_RESULT, 2, BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment
	msgbox BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment::
	msgbox BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment::
	msgbox BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveSilverShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_SILVER_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_SILVER_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_NoRoomForShield::
	msgbox BattleFrontier_ScottsHouse_Text_ComeBackForThisLater, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenShield::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveGoldShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_GOLD_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_GOLD_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingGreatThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier::
	msgbox BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	closemessage
	delay 30
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest
	msgbox BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing, MSGBOX_DEFAULT
	goto_if_eq VAR_SCOTT_STATE, 13, BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 9, BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 6, BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint
	end

BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints::
	buffernumberstring STR_VAR_1, 4
	setvar VAR_0x8004, 4
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints::
	buffernumberstring STR_VAR_1, 3
	setvar VAR_0x8004, 3
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints::
	buffernumberstring STR_VAR_1, 2
	setvar VAR_0x8004, 2
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint::
	buffernumberstring STR_VAR_1, 1
	setvar VAR_0x8004, 1
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints::
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	msgbox BattleFrontier_ScottsHouse_Text_ExplainBattlePoints, MSGBOX_DEFAULT
	setflag FLAG_SCOTT_GIVES_BATTLE_POINTS
	setflag FLAG_TEMP_2
	release
	end

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest::
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier:
    .string "亚希达：啊，欢迎！\n呵呵呵…抱歉来的时候有点挤。\p不管如何，{PLAYER}{KUN}，请让我\n正式欢迎你来到对战开拓区。\p这个地方就是我的梦想。\n经过了一年又一年，直到今天，\l我的梦想终于可以实现了。$"

BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal:
    .string "回头想想，这一路\n还真是走了很久很久…\p我独自离开家乡，\n只为寻找强大的训练师。\p谁也无法算清我在这一路上\n究竟付出了多少时间与汗水。$"

BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing:
    .string "但那些都已经过去了，\n没必要紧盯着过去不放！\p现在，从心底里好好享受\n在这里的战斗吧！\p{PLAYER}{KUN}，这个送给你，\n就作为我们那屡次交错的旅程\l的纪念吧。$"

BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints:
    .string "{PLAYER}得到了\n{STR_VAR_1}对战点数。$"

BattleFrontier_ScottsHouse_Text_ExplainBattlePoints:
    .string "亚希达：你可以在开拓区通行证上\n查看你对战点数的数量。\p你在对战开拓区\n获得的胜利越多，收集的\l对战点数就越多。\p这些对战点数你可以随便用，\n比如用来交换物品。$"

BattleFrontier_ScottsHouse_Text_ExpectingGreatThings:
    .string "期待你的精彩表现！$"

BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers:
    .string "亚希达：每个训练师都是一个独特的人，\n他们都过着自己的生活。\p但当他们进行战斗的时候，\n他们是谁并不重要。\p他们都是一样的！\p我喜欢这样纯粹的战斗，\n大家都是平等的。\p因此我环游各地，寻找\n重视战斗的训练师，\l邀请他们来到这个地方。$"

BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain:
    .string "亚希达：你与开拓之脑\n交过手了吗？\p你得到了他们的\n印记了吗？\p开拓之脑是我从世界各地\n挑选出来的最强训练师，\p但我能肯定，看到你的能力，\n他们也会被吓一跳！$"

BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier:
    .string "亚希达：你的目标不只是战斗吧？\n对吗？\p我好像还记得你也在\n收集宝可梦图鉴。\p想知道一个好消息吗？\p在对战开拓区某处\n你也能碰到野生宝可梦…\l哈哈哈！$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols:
    .string "亚希达：在对战开拓区\n玩得还高兴吗？\p…等等…\n啊！\p你的开拓区通行证！\n你已经收集到了\l所有的银色印记！\p简直太不可置信了！\n和我预想中一样，你真的非常非常强！\p虽说通常我不会做这些，\n不过这次就让我破例一回！\p这个送给你，\n你肯定能善加利用的。$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols:
    .string "亚希达：希望你喜欢\n我的对战开拓区。\p…等等…\n啊，我不是眼花了吧！\p你的开拓区通行证！\n你已经收集到了\l所有的金色印记！\p太了不起了！\n和我预想中一样，你真是个不可思议的人！\p… … … … … …\p{PLAYER}，你一定得收下这个！\p是你的话，一定能识得\n我的礼物的价值的！$"

BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere:
    .string "我可是有天赋的，可以第一眼就\n看出训练师的实力。\p真高兴我的先见让我\n把你带到了这里！$"

BattleFrontier_ScottsHouse_Text_BerryPocketStuffed:
    .string "你的树果口袋好像\n已经塞满了。$"

BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow:
    .string "亚希达：啊，我听说过你的事了！\n你在对战塔干得不错！\l你一连打败了50个训练师？\p真让人惊讶！\n这个送给你！$"

BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow:
    .string "亚希达：啊，天哪，我听说过你的事了！\n你在对战塔干得太棒了！\l你一连打败了100个训练师？\p真令人不敢相信！\n这是送给你的奖励！$"

BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings:
    .string "希望还能听到其他\n关于你的好消息！$"

BattleFrontier_ScottsHouse_Text_ComeBackForThisLater:
    .string "哎，你装的东西太多了，\n收拾收拾再来吧。$"

