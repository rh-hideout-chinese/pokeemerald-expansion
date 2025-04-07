BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
    .string "…你想干什么？\p没看见我们很忙吗？\n你就不能一边去等等？$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
    .string "…嗯？\n我觉得你是个挺强的训练师。\p呵呵呵…\n听着，我有个小提议。\p现在我们在对战开拓区\n有一组人，\l我们正在做一个小游戏。\p规则很简单，\p首先，我们选择一种\n对战开拓区的设施，\p然后我们各自选择一个\n正在挑战的训练师，\l赌上自己的对战点数，\p选的训练师获得成绩最好\n的人就可以得到所有的\l对战点数。\p很简单是吧？\n然后…$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
    .string "我正在找想要挑战\n对战塔里单人对战\l房间的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
    .string "我正在找想要挑战\n对战塔里双打对战\l房间的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
    .string "我正在找想要挑战\n对战塔里多人对战\l房间的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
    .string "我正在找想要挑战\n对战巨蛋里单人对战\l锦标赛的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
    .string "我正在找想要挑战\n对战巨蛋里双打对战\l锦标赛的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
    .string "我正在找想要挑战\n对战工厂里交换式对战\l单人锦标赛的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
    .string "我正在找想要挑战\n对战工厂里交换式对战\l双人锦标赛的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
    .string "我正在找想要挑战\n对战宫殿里单人对战\l大厅的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
    .string "我正在找想要挑战\n对战宫殿里双打对战\l大厅的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
    .string "我正在找想要参加\n对战竞技场里三回合定胜负\l锦标赛的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
    .string "我正在找想要参加\n对战水管里选择式对战\l的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
    .string "我正在找想要参加\n对战金字塔里追寻式战斗\l的训练师，\p但到现在我还没看到\n有能力胜出的训练师。$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
    .string "我觉得也许你值得一试，\n怎么样？\l能替我参加吗？$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
    .string "好的，太好了。\n那么，呃…能先给我\l一些对战点数吗？\p相信我，事后我会\n感谢你的。$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
    .string "太好了，太好了！\n那你能给我多少？$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
    .string "啊，不不不！\n你的对战点数不够！\p你还是别在这儿乱转\n浪费别人的时间了！$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
    .string "呵呵呵！谢谢！\n好了，去吧！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
    .string "马上就去对战塔的\n单人对战房间吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
    .string "马上就去对战塔的\n双打对战房间吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
    .string "马上就去对战塔的\n多人对战房间吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
    .string "马上就去对战巨蛋的\n单人对战锦标赛吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
    .string "马上就去对战巨蛋的\n双打对战锦标赛吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
    .string "马上就去对战工厂的\n单人交换式对战锦标赛吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
    .string "马上就去对战工厂的\n双人交换式对战锦标赛吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
    .string "马上就去对战宫殿的\n单人对战大厅吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
    .string "马上就去对战宫殿的\n双打对战大厅吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
    .string "马上就去对战竞技场的\n三回合定胜负锦标赛吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
    .string "马上就去对战水管的\n选择式对战吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
    .string "马上就去对战金字塔的\n追寻式战斗吧！\p决不能输！\n别放过这个机会！\l我们的未来就全靠你了！$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
    .string "啊，你来了…\n你很努力了…\p不过抱歉，我没法把\n对战点数还给你了…\p就让我们下一回\n更加努力一些吧！$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
    .string "啊，太棒了！\n我在这儿！\p我就知道你可以的！\n我就知道你会成功！\l今天我们两个是大赢家！\p你的对战点数还给你，\n还有，这是额外的奖品！$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
    .string "{PLAYER}得到\n{STR_VAR_1}对战点数。$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
    .string "你还准备挑战什么的话\n别忘了叫上我！$"

BattleFrontier_Lounge3_Text_NotInterested::
    .string "你不感兴趣吗？！\n不要怕挑战啊！$"

BattleFrontier_Lounge3_Text_Oh::
    .string "啊…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
    .string "我又押错了训练师！\p也许我还是老老实实\n像别人那样去战斗比较好…$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
    .string "那边的训练师…\p他的实力其实不错，可惜太容易紧张，\n总是通不过对战巨蛋…$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
    .string "嘻嘻！\n我一眼就能看出谁会是赢家！$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
    .string "那些训练师…\n他们在干什么？\l他们应该去挑战啊。$"
