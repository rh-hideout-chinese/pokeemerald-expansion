CeruleanCity_Gym_Frlg_MapScripts::
	.byte 0

CeruleanCity_Gym_EventScript_Misty::
	famechecker FAMECHECKER_MISTY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_MISTY, CeruleanCity_Gym_Text_MistyIntro, CeruleanCity_Gym_Text_MistyDefeat, CeruleanCity_Gym_EventScript_MistyDefeated, NO_MUSIC
	goto_if_unset FLAG_GOT_TM03_FROM_MISTY, CeruleanCity_Gym_EventScript_GiveTM03
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_MistyDefeated::
	famechecker FAMECHECKER_MISTY, 1
	setflag FLAG_DEFEATED_MISTY
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	set_gym_trainers_frlg 2
	goto CeruleanCity_Gym_EventScript_GiveTM03
	end

CeruleanCity_Gym_EventScript_GiveTM03::
	msgbox CeruleanCity_Gym_Text_ExplainCascadeBadge
	checkitemspace ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM03
	giveitem_msg CeruleanCity_Gym_Text_ReceivedTM03FromMisty, ITEM_TM03
	setflag FLAG_GOT_TM03_FROM_MISTY
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_NoRoomForTM03::
	msgbox CeruleanCity_Gym_Text_BetterMakeRoomForThis
	release
	end

CeruleanCity_Gym_EventScript_Diana::
	trainerbattle_single TRAINER_PICNICKER_DIANA, CeruleanCity_Gym_Text_DianaIntro, CeruleanCity_Gym_Text_DianaDefeat
	msgbox CeruleanCity_Gym_Text_DianaPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_Luis::
	trainerbattle_single TRAINER_SWIMMER_MALE_LUIS, CeruleanCity_Gym_Text_LuisIntro, CeruleanCity_Gym_Text_LuisDefeat
	famechecker FAMECHECKER_MISTY, 2
	msgbox CeruleanCity_Gym_Text_LuisPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MISTY, CeruleanCity_Gym_EventScript_GymGuyPostVictory
	msgbox CeruleanCity_Gym_Text_GymGuyAdvice
	release
	end

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
	msgbox CeruleanCity_Gym_Text_WeMakePrettyGoodTeam
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanCity_Gym_Text_MistyIntro::
    .string "嗨，你是个新人啊！\p"
    .string "只有那些懂战术的训练家\n"
    .string "能在这儿出现。\p"
    .string "你收服和训练宝可梦时\n"
    .string "会讲究战术吗？\p"
    .string "我的战术就是用\n"
    .string "我的水属性宝可梦全力地猛攻！{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeruleanCity_Gym_Text_ExplainTM03::
    .string "TM03是水波动。\p"
    .string "把它用在一只水属性宝可梦身上吧！$"

CeruleanCity_Gym_Text_ExplainCascadeBadge::
    .string "蓝色徽章能让所有的\n"
    .string "30级以下的宝可梦听你的话。\p"
    .string "包括那些从别人那儿交换得到的。\p"
    .string "而且你可以随时使用居合斩。\n"
    .string "甚至是没在战斗的时候。\p"
    .string "你可以居合斩一些小树\n"
    .string "去开辟新的道路。\p"
    .string "你也能得到我最喜欢的技能。$"

CeruleanCity_Gym_Text_ReceivedTM03FromMisty::
    .string "{PLAYER}从小霞那儿得到了TM03。$"

CeruleanCity_Gym_Text_BetterMakeRoomForThis::
    .string "你最好为这个准备一些空间！$"

CeruleanCity_Gym_Text_MistyDefeat::
    .string "哇！\n"
    .string "你很厉害！\p"
    .string "很好！\p"
    .string "这个蓝色徽章你拿着，\n"
    .string "来证明你打败过我的证明。$"

CeruleanCity_Gym_Text_DianaIntro::
    .string "什么？你？\n"
    .string "我比你强多了！\p"
    .string "不能随便去打扰小霞。$"

CeruleanCity_Gym_Text_DianaDefeat::
    .string "你打败了我！$"

CeruleanCity_Gym_Text_DianaPostBattle::
    .string "你必须面对其他的训练家，\n"
    .string "看看你到底有多强大。$"

CeruleanCity_Gym_Text_LuisIntro::
    .string "哈！\p"
    .string "我是第一个！\n"
    .string "我们开始吧！$"

CeruleanCity_Gym_Text_LuisDefeat::
    .string "不可能！$"

CeruleanCity_Gym_Text_LuisPostBattle::
    .string "小霞总是不断地提升着自己。\p"
    .string "她是不会输给像你这样的人的。$"

CeruleanCity_Gym_Text_GymGuyAdvice::
    .string "哟！\n"
    .string "未来的冠军！\p"
    .string "给你一些建议吧！\p"
    .string "这个馆主小霞，\n"
    .string "使用的是水属性宝可梦。\p"
    .string "你可以用草属性宝可梦\n"
    .string "吸收它们的水份。\p"
    .string "或者你也可以用电属性\n"
    .string "宝可梦电击它们！$"

CeruleanCity_Gym_Text_WeMakePrettyGoodTeam::
    .string "你战胜了小霞！\n"
    .string "看吧，我说什么来着？\p"
    .string "你和我，小子，\n"
    .string "我们组成了一个强大之极的队伍！$"

CeruleanCity_Gym_Text_GymStatue::
    .string "华蓝宝可梦道馆\n"
    .string "馆主：小霞\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
    .string "华蓝宝可梦道馆\n"
    .string "馆主：小霞\p"
    .string "优胜训练家：\n"
    .string "{RIVAL} {PLAYER}$"

