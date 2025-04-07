.set LOCALID_GRUNT, 3
.set LOCALID_DEVON_EMPLOYEE, 4

PetalburgWoods_MapScripts::
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_GRUNT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
    .string "唔…\n什么也没有啊…$"

PetalburgWoods_Text_HaveYouSeenShroomish:
    .string "嗨，你在附近见到过\n叫做蘑蘑菇的宝可梦吗？\p我真的很喜欢那种宝可梦。$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
    .string "本打算偷袭你的，但看你好像\n准备在橙华森林里\l呆一辈子，\p等不及你出去，我就进来了！$"

PetalburgWoods_Text_HandOverThosePapers:
    .string "就是你！得文的研究员！\p把资料交出来！$"

PetalburgWoods_Text_YouHaveToHelpMe:
    .string "啊耶！\p你是个宝可梦训练师，对吗？\n拜托你帮帮我吧！$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
    .string "嗯？你知道自己在做什么吗？\n什么，你要保护他？\p就算你只是个孩子，\n和水舰队作对也没好下场！\p来战斗吧！$"

PetalburgWoods_Text_YoureKiddingMe:
    .string "你打败了我！你太强了！$"

PetalburgWoods_Text_YouveGotSomeNerve:
    .string "呼呼…敢和\n水舰队作对，你胆子不小！\l再来战斗一次吧！\p虽然想这么说，可我已经\n没有宝可梦了…\p而且，哼，我们水舰队\n还得在卡那兹市找某些东西，\p今天先放过你！$"

PetalburgWoods_Text_ThatWasAwfullyClose:
    .string "呼…\n好险哪！\p多亏了你，重要的文件\n才没被抢走\p好吧，作为答谢，送你\n一个超级球！$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
    .string "这么说来刚才那个水舰队\n的混混说，他们也在寻找\l卡那兹市的什么东西，是吗？$"

PetalburgWoods_Text_ICantBeWastingTime:
    .string "唔喔！糟糕了！\n我可不能再浪费时间了！$"

PetalburgWoods_Text_YoureLoadedWithItems:
    .string "你的道具已经满了，\n我没法把这个超级球给你。$"

PetalburgWoods_Text_GoBugPokemonTeam:
    .string "我捉了许多的宝可梦！\p上啊！\n我的虫宝可梦之队！$"

PetalburgWoods_Text_ICouldntWin:
    .string "拥有这些宝可梦，\n我却无法获胜…$"

PetalburgWoods_Text_ImOutOfPokeBalls:
    .string "我捉了许多的宝可梦，\n现在已经没有精灵球了。$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
    .string "如果把虫宝可梦带到学校里，\n马上就会变成明星的！$"

PetalburgWoods_Text_CantBePopularIfILose:
    .string "输了的话就不会成为明星了。$"

PetalburgWoods_Text_PeopleRespectYou:
    .string "如果拥有一只好大的虫宝可梦，\n大家会很羡慕你的。$"

PetalburgWoods_Text_IWantRematch1:
    .string "等我的虫宝可梦\n长大后，我们再比一次吧！\p我把你登记进口袋领航员里了！$"

PetalburgWoods_Text_IWantRematch2:
    .string "等我的虫宝可梦\n长大后，我们再比一次吧！\p我把你登记进口袋领航员里了！$"

PetalburgWoods_Text_MyPokemonHaveGrown:
    .string "我的虫宝可梦长大了，\n我会再次变成明星的。$"

PetalburgWoods_Text_CantBePopularIfLose:
    .string "输了的话就不会成为明星了。$"

PetalburgWoods_Text_IveBeenTrainingHard:
    .string "如果拥有强大的宝可梦\n就会被大家追捧的，对吧？\l所以我一直在刻苦训练。$"

PetalburgWoods_Text_StayOutOfTallGrass:
    .string "哟，那边的！\n你的宝可梦没事吧？\p如果你的宝可梦很虚弱，\n想避免战斗，那就得避开草堆。$"

PetalburgWoods_Text_HiddenItemsExplanation:
    .string "有时候，地上会有些\n你看不见的东西。\p所以我不管走到哪儿\n都会仔细搜索四周。$"

PetalburgWoods_Text_TryUsingThisItem:
    .string "哦，真漂亮！\n那是卡那兹市道馆的徽章！\p你一定是个训练师，\n试试这个东西吧。$"

PetalburgWoods_Text_MiracleSeedExplanation:
    .string "这是奇迹种子，\n让宝可梦携带上的话，它的\l草系招式就会变强。\p我想除了奇迹种子，还有\n其它的可以让宝可梦携带的\l方便的物品。$"

PetalburgWoods_Text_TrainerTipsExperience:
    .string "训练师小技巧\p所有在战斗中出过场的宝可梦\n都会得到经验值。\p想培养弱小的宝可梦，\n就把它放到队伍列表的左侧。\p战斗开始时，先把它换下场。\n这样它不会受伤\l也能获得经验值了。$"

PetalburgWoods_Text_TrainerTipsPP:
    .string "训练师小技巧\p除了被打击点数(HP)，宝可梦\n还拥有用来在战斗中\l发动招式的招式点数(PP)。\p如果宝可梦的PP值耗尽，必须把它\n带到宝可梦中心去。$"

