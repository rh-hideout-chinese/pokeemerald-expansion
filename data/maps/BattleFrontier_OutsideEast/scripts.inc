.set LOCALID_SUDOWOODO, 14

BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
    .string "这里是对战塔！\n保持你的不败纪录，\l成为最强的训练家吧！$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
    .string "这里是对战宫殿！\n关注你的宝可梦的战斗吧！$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
    .string "这里是对战竞技场！\n最强的队伍在这里集结！$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
    .string "这里是对战金字塔！\n升华你的对战之道！$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
    .string "对战开拓区排行榜\n关注最新的纪录！$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
    .string "对战点数交换服务中心\n交换对战点数！$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
    .string "哇！\n好大！\p对战塔看起来很特别，\n和别的建筑都不同。$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
    .string "我的目标是征服整个\n对战开拓区和\l宝可梦联盟。\p如果成功了的话……\p我……我就去求我家隔壁\n的咪咪跟我做朋友！$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
    .string "对战金字塔的战斗非常严酷！\n我想我是走不到最上层了。\p实在没有其他办法的话，\n也许我可以试试从外面爬上去……$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
    .string "我是在黑暗中长大的……\n是的……哪里最适合我？\l必然是对战金字塔……\p在黑暗中探索的时候\n你是不是也会陷入完全的绝望？$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
    .string "我一个星期没有睡觉了，\n但我已经找到了最强组合！\p我是绝对不会输的，这不是玩笑，\n我们的风暴会席卷对战竞技场！$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
    .string "你也是亚希达带来的吗？\n那家伙到底是什么人？\p他好像总能发现\n天才训练家，不过……\p我从来没见过\n他跟别人战斗。$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
    .string "兹格！\n我相信你能行的，伙计！\p我的小兹格赢了的话\n什么好东西都买给你！$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
    .string "蛇纹熊看起来挺清闲……$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
    .string "大家都说我爱管闲事，\n但我总是忍不住啊。\p你的帽子歪了！\n啊，天哪，地上有垃圾！\l哎呀，到晚饭时间了！\p真不知道我究竟能不能\n安静地看对战宫殿里的战斗……$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
    .string "也许我看起来不像那种人，\n但我确实打败过道馆馆主。\p哎，我是不是应该再做一些什么\n来保持我的荣誉？$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
    .string "我骑自行车很快，\n战斗的时候也一样快。\p眨眼之间我就可以\n赢得战斗！$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
    .string "对于宝可梦，我比爸爸\n还要更胜一筹。$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
    .string "去吧，小甜心！\n为了爸爸取得胜利吧！\p你和你妈妈一样的，\n绝对能够主导战斗！$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
    .string "我听说过对战竞技场的\n这个令人倾心的女孩。\l从现在开始要加油了！\p除了她，你知道我还\n找到了什么？\p一大群满身汗臭的\n自然的武术家！$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
    .string "有时候能看到这位看上去\n明显是大人物的老人到这儿来，\p他的宝可梦真强，\n但他本人很和善。$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
    .string "你听说过那个关于\n对战金字塔的传说吗？\p当一位勇敢的训练家到达\n金光照耀的顶峰之时，\l就会有一个人出现在人群中。\p你知道这个传说吗？\n哈哈，你当然不知道！\l这是我刚刚编的！\p至于这是什么意思，\n那是，呃，不告诉你！$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
    .string "可恶！\n我以前从来没输过！\p但一到这里我就被\n毫不留情地打败了！\p然后有人说我根本没有天赋？！\n可恶！$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
    .string "这个人在挑战\n对战塔的时候\l碰上了个非常强的训练家。\p唉，现在他变成这样了……\p挑战对战塔的话\n一定要三思而后行。$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
    .string "好了！\n终于攒够了对战点数！\p可以再换一个\n毛绒玩具了！$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
    .string "啊哈哈！\n这里就是排行榜！\p我要让历史记住我这个\n超级冠军，把我的名字记录在这里，\l让所有的子孙后代都能看到！$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
    .string "只要有你在身边，我会无往不利。$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
    .string "哦哦，亲爱的，你太棒了！\p哦哦，我再也等不及了！\p我们马上去挑战\n多人对战房间吧！\p如果我们一起去对战沙龙，\n我们之间爱的力量一定会\l使我们战胜所有人。\p啊，亲爱的，在我们两人面前，\n一切都像推倒多米诺一样！$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
    .string "对战开拓区并不是\n强大的训练家专属的，\p似乎很多拥有特别能力的人\n也在被邀请的行列。\p那个亚希达……\p他建造这个地方一定有着\n远大的目标……$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
    .string "打扰一下，年轻人，\n你的视力还可以吧？\p我刚才看到那边有棵奇怪的树\n好像在摇摆。$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
    .string "打扰一下，年轻人，\n你的记忆力还可以吧？\p我好像记得那边曾经\n有棵奇怪的树。$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
    .string "我……\n我看见了！\p是一只举着长长尾巴的\n小小的宝可梦！\p刚才它藏在一块大石头底下，\n还一直偷偷地盯着我看！$"
