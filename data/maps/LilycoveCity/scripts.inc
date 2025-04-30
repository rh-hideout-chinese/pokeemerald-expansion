.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
    .string "小遥：嗨，你好啊？\n{PLAYER}{KUN}，你也来买东西吗？\p我买了一大堆\n玩偶和海报。\p当然，我捕捉了不少\n宝可梦，也训练得不错。\p不过，我更在意的是\n你的宝可梦训练得如何了，{PLAYER}{KUN}。\p我要和你战斗，\n看看你的宝可梦，{PLAYER}{KUN}。$"

LilycoveCity_Text_MayNotRaisingPokemon:
    .string "小遥：啊，怎么了？{PLAYER}{KUN}，\n你没好好训练你的宝可梦吗？\p作为一个训练家\n可不该这样呢……$"

LilycoveCity_Text_MayBattleMe:
    .string "小遥：来吧，和我战斗，\n让我看看你的宝可梦！$"

LilycoveCity_Text_MayWontBeBeaten:
    .string "小遥：我训练的宝可梦不会\n被你的宝可梦打败的，{PLAYER}{KUN}！$"

LilycoveCity_Text_MayDefeat:
    .string "…… …… …… ……\p我还记得我们上次\n在103号道路的战斗，{PLAYER}{KUN}。\p那场战斗让你变得这么强了，\n是吗，{PLAYER}{KUN}？$"

LilycoveCity_Text_MayGoingBackToLittleroot:
    .string "小遥：我打算\n回未白镇去。\p我已经捕捉了很多不错的宝可梦，\n宝可梦图鉴也快完成了，\l我要回家给爸爸看。$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
    .string "{PLAYER}{KUN}，你打算做什么？\p收集所有的道馆徽章，\n然后去挑战宝可梦联盟吗？\p好吧，{PLAYER}{KUN}，那你收集徽章的时候，\n我就致力于我的宝可梦图鉴吧。\l我会比你更早完成的！\p再见了！$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
    .string "{PLAYER}{KUN}，你打算做什么？\p想挑战宝可梦联盟吗？\p或者你想完成\n宝可梦图鉴？\p也许战斗我会输给你，\n但我会比你更快完成宝可梦图鉴！\p再见了！$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
    .string "{PLAYER}{KUN}，你打算做什么？\p你要挑战\n对战开拓区吗？\p或者你想完成\n宝可梦图鉴？\p也许战斗我会输给你，\n但我会比你更快完成宝可梦图鉴的！\p再见了！$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
    .string "小悠：嗨，这不是{PLAYER}吗。\p我在替老爸跑腿呢。\n不，我才不是来买玩偶的。\p不管怎样，离上次我们\n碰面已经有段时间了，\p想试试我们两个谁的宝可梦\n训练得更好吗？$"

LilycoveCity_Text_BrendanNoConfidence:
    .string "小悠：哦，怎么了？\n没信心吗？$"

LilycoveCity_Text_BrendanBattleMe:
    .string "小悠：想来战斗一场看看\n谁的宝可梦训练得更好吗？$"

LilycoveCity_Text_BrendanWontBeBeaten:
    .string "小悠：好，我是\n不会输给{PLAYER}的。$"

LilycoveCity_Text_BrendanDefeat:
    .string "唔……\n你的宝可梦训练得不错。\p我开始对你改变看法了——\n你会成为一个出色的训练家的……$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
    .string "小悠：我……\n我打算回未白镇去。\p你知道我在帮老爸收集\n宝可梦图鉴，现在进展得不错，\l我要回去给他看看。$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
    .string "{PLAYER}，你准备怎么办？\p收集所有的道馆徽章，然后\n去挑战宝可梦联盟吗？\p也许我也会去……\p好了，无论如何，加油吧！$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
    .string "{PLAYER}，你准备怎么办？\p你变得这么强了，\n试试挑战宝可梦联盟去吗？\p呵呵，就算我——如果能\n努力训练一下，\l我也会比你更强的，{PLAYER}。\p好了，无论如何，加油吧！$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
    .string "{PLAYER}，你准备怎么办？\p想去对战开拓区\n挑战吗？\p或者你想完成\n宝可梦图鉴？\p既然你已经这么强了，\n考虑一下去对战开拓区吧。\p呵呵，如果我更努力训练的话，\n我就会比你更强了，{PLAYER}。\p也许我也该去对战开拓区。\p好了，无论如何，加油吧！$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
    .string "哼哼哼……\p我们今天往基地里\n搬了不少战利品……\p你……你是谁？！\n我只是在自言自语而已！$"

LilycoveCity_Text_ChanceToDoBigThings:
    .string "我只不过是个小兵，\n根本不知道老大在想什么……\p但我知道，只要加入海洋队，\n我总有机会做些大事的！\p你……你是谁？！\n我只是在自言自语而已！$"

LilycoveCity_Text_DontGoNearCaveInCove:
    .string "喂，说你呢！\p别靠近海湾那儿的洞窟！\p为什么？我干啥要告诉你！\n我是大人，所以你得听我的！$"

LilycoveCity_Text_IfWorldBecomesOurs:
    .string "如果这广大的世界都归属于我们\n海洋队，那么世界中的\l宝可梦会生活得更快乐的。$"

LilycoveCity_Text_WailmerLeapOutOfWater:
    .string "这里！吼吼鲸！\n跳出水来！$"

LilycoveCity_Text_GetLostMessingUpTraining:
    .string "嗯？你想干什么？\p你打扰了我们训练了，\n呃，请你有多远死多远行吗？$"

LilycoveCity_Text_ContestHallInTown:
    .string "就在这个镇子里有个\n宝可梦华丽大赛会场，\p全国的悉心培育的宝可梦\n都会在这里聚集。\p我已经激动得心跳加速了！$"

LilycoveCity_Text_StrangeCaveInCove:
    .string "你看到镇子边缘的海湾里\n那个可疑的洞窟了吗？$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
    .string "我打算教我的宝可梦\n一些新的招式去参加比赛，\p但我得先去遗忘爷爷那儿\n让它忘记秘传学习\l器招式。$"

LilycoveCity_Text_ImFromKanto:
    .string "我是从关都来的。\p有着青山碧水的丰缘地区\n真的很美。\p呃？等等……\p也许会有只在这片地区生活的\n稀有宝可梦吧？$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
    .string "海洋队一直在海湾\n训练他们的吼吼鲸。\p他们挡着路，\n我们水手根本没法驾船出海！$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
    .string "喂，知道吗？\p有人替我们\n赶走了海洋队！\p海湾那边的那些吼吼鲸也因此离开了，\n我们的船又能出海了。$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
    .string "刚才我在海边的民宿里\n听着潮声睡了一觉……\p有人却趁机偷了我的宝可梦！\p是谁干的？\n海洋队？是海洋队吗？$"

LilycoveCity_Text_MissingPokemonCameBack:
    .string "我那失踪的宝可梦……\n在我没注意时自己回来了！$"

LilycoveCity_Text_ImArtDealer:
    .string "我是一名艺术品商人，\p我的工作是买卖艺术品，\n尤其是绘画。\p我听说这里的美术馆\n正在展出极棒的艺术品……$"

LilycoveCity_Text_SeaRemainsForeverYoung:
    .string "时间在我们的脸上刻下了皱纹，\n而大海却还是一如既往地年轻，\l充满了生命的活力……\p呼呵呵呵呵……$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
    .string "丈夫提议到这儿来居住\n已经是六十年前的事了，\l而大海却依旧那样年轻美丽。\p呼呵呵呵呵……$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
    .string "你知道这个海湾那里\n奇怪的山洞吗？\p那里原来是个天然洞窟，\n后来海洋队来到这里，\l整修了那个山洞。\p他们自称\n“热爱自然的海洋队”！\p但他们说的跟做的\n完全背道而驰！$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
    .string "那个海湾的洞窟……\p一开始我没注意，\n但它现在已经空了。\p那些海洋队一定是\n全体卷铺盖跑路了。$"

LilycoveCity_Text_CitySign:
    .string "水静市\p“连接大海与陆地的\n城市。”$"

LilycoveCity_Text_ContestHallSign:
    .string "宝可梦华丽大赛会场\n“训练家聚集的地方！”$"

LilycoveCity_Text_MotelSign:
    .string "静水民宿\p“请记住我们——\n水静市的静水。”$"

LilycoveCity_Text_MuseumSign:
    .string "水静市美术馆\p“大量宝可梦名作\n正在展出！”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
    .string "水静市美术馆\p“{PLAYER}的宝可梦收藏品\n正在展出！”$"

LilycoveCity_Text_HarborSignUnderConstruction:
    .string "水静市港口\p“破浪号游船正在\n凯那市建造中，\p预计近期\n即可通航。”$"

LilycoveCity_Text_HarborSign:
    .string "水静市港口\p“愿破浪号游船\n能为您带来最快乐的旅行体验。”$"

LilycoveCity_Text_TrainerFanClubSign:
    .string "宝可梦训练家俱乐部\p牌子上潦草地写着一些\n训练家的名字……$"

LilycoveCity_Text_DepartmentStoreSign:
    .string "水静百货\p“满载着商品\n和快乐回家！”\p“寻找你所需要的物品的\n最佳地点！”$"

LilycoveCity_Text_MoveDeletersHouseSign:
    .string "遗忘爷爷的家\p“让宝可梦忘记不需要的招式。”$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
    .string "你知道那个叫\n树果混合器的机器吗？$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
    .string "大家要齐心合力\n让它转得更快。\p据说它转得越快，\n得到的宝可方块就越好。$"

LilycoveCity_Text_ExplainBerryBlender:
    .string "它是用来制作一种\n叫做宝可方块的树果的。\p如果给宝可梦吃优质宝可方块，\n它的外貌会有很大成长。$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
    .string "据说水路某处\n有座塔，\p叫做天空之柱。$"

LilycoveCity_Text_SawTallTowerOnRoute131:
    .string "我在130号水路的附近\n看到过一座高高的塔，\p那会不会是……？$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
    .string "我们刚刚来这里\n度蜜月，\p却偶然看到一只龙属性\n宝可梦从天空飞过。\p丰缘有生活着\n那么厉害的宝可梦吗？$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
    .string "我们曾许愿要在蜜月中\n看到很多很多稀有宝可梦，\p并且我们一到这儿\n就看到了稀有宝可梦。\p我是说，我真的很高兴！$"

