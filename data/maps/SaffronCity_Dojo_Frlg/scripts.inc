SaffronCity_Dojo_Frlg_MapScripts::
	.byte 0

SaffronCity_Dojo_EventScript_TriggerMasterBattleLeft::
	lockall
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	releaseall
	end

SaffronCity_Dojo_EventScript_TriggerMasterBattleRight::
	lockall
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	releaseall
	end

SaffronCity_Dojo_EventScript_HitmonleeBall::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_AlreadyGotHitmon
	showmonpic SPECIES_HITMONLEE, 10, 3
	setvar VAR_TEMP_1, SPECIES_HITMONLEE
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox SaffronCity_Dojo_Text_YouWantHitmonlee, MSGBOX_YESNO
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, YES, SaffronCity_Dojo_EventScript_GiveHitmon
	hidemonpic
	release
	end

SaffronCity_Dojo_EventScript_AlreadyGotHitmon::
	msgbox SaffronCity_Dojo_Text_BetterNotGetGreedy
	release
	end

SaffronCity_Dojo_EventScript_HitmonchanBall::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_AlreadyGotHitmon
	showmonpic SPECIES_HITMONCHAN, 10, 3
	setvar VAR_TEMP_1, SPECIES_HITMONCHAN
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox SaffronCity_Dojo_Text_YouWantHitmonchan, MSGBOX_YESNO
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, YES, SaffronCity_Dojo_EventScript_GiveHitmon
	hidemonpic
	release
	end

SaffronCity_Dojo_EventScript_GiveHitmon::
	hidemonpic
	givemon VAR_TEMP_1, 25
	goto_if_eq VAR_RESULT, 0, SaffronCity_Dojo_EventScript_ReceivedHitmonParty
	goto_if_eq VAR_RESULT, 1, SaffronCity_Dojo_EventScript_ReceivedHitmonPC
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	release
	end

SaffronCity_Dojo_EventScript_ReceivedHitmonParty::
	removeobject VAR_LAST_TALKED
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster
	waitmessage
	waitfanfare
	setflag FLAG_GOT_HITMON_FROM_DOJO
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SaffronCity_Dojo_EventScript_EndGiveMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto SaffronCity_Dojo_EventScript_EndGiveMon
	end

SaffronCity_Dojo_EventScript_ReceivedHitmonPC::
	removeobject VAR_LAST_TALKED
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster
	waitmessage
	waitfanfare
	setflag FLAG_GOT_HITMON_FROM_DOJO
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SaffronCity_Dojo_EventScript_TransferredHitmonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto SaffronCity_Dojo_EventScript_TransferredHitmonToPC
	end

SaffronCity_Dojo_EventScript_TransferredHitmonToPC::
	call Common_EventScript_TransferredToPC
	goto SaffronCity_Dojo_EventScript_EndGiveMon
	end

SaffronCity_Dojo_EventScript_EndGiveMon::
	release
	end

SaffronCity_Dojo_EventScript_Statue::
	msgbox SaffronCity_Dojo_Text_FightingDojo, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_LeftScroll::
	msgbox SaffronCity_Dojo_Text_EnemiesOnEverySide, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_RightScroll::
	msgbox SaffronCity_Dojo_Text_GoesAroundComesAround, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_Hitoshi::
	trainerbattle_single TRAINER_BLACK_BELT_HITOSHI, SaffronCity_Dojo_Text_HitoshiIntro, SaffronCity_Dojo_Text_HitoshiDefeat
	msgbox SaffronCity_Dojo_Text_HitoshiPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Hideki::
	trainerbattle_single TRAINER_BLACK_BELT_HIDEKI, SaffronCity_Dojo_Text_HidekiIntro, SaffronCity_Dojo_Text_HidekiDefeat
	msgbox SaffronCity_Dojo_Text_HidekiPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Aaron::
	trainerbattle_single TRAINER_BLACK_BELT_AARON, SaffronCity_Dojo_Text_AaronIntro, SaffronCity_Dojo_Text_AaronDefeat
	msgbox SaffronCity_Dojo_Text_AaronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Mike::
	trainerbattle_single TRAINER_BLACK_BELT_MIKE, SaffronCity_Dojo_Text_MikeIntro, SaffronCity_Dojo_Text_MikeDefeat
	msgbox SaffronCity_Dojo_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_MasterKoichi::
	trainerbattle_single TRAINER_BLACK_BELT_KOICHI, SaffronCity_Dojo_Text_MasterKoichiIntro, SaffronCity_Dojo_Text_MasterKoichiDefeat, SaffronCity_Dojo_EventScript_DefeatedMasterKoichi
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_MasterKoichiAlreadyGotHitmon
	msgbox SaffronCity_Dojo_Text_ChoosePrizedFightingMon, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_MasterKoichiAlreadyGotHitmon::
	msgbox SaffronCity_Dojo_Text_StayAndTrainWithUs
	release
	end

SaffronCity_Dojo_EventScript_DefeatedMasterKoichi::
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	release
	end

SaffronCity_Dojo_Text_MasterKoichiIntro::
    .string "哼哼！\p"
    .string "我就是空手大王！\n"
    .string "也是这里的馆主！\p"
    .string "你想要挑战我？\n"
    .string "我可不会手下留情的！\p"
    .string "哇哈哈！$"

SaffronCity_Dojo_Text_MasterKoichiDefeat::
    .string "哇啊！\n"
    .string "哎呀！打着我了！$"

SaffronCity_Dojo_Text_ChoosePrizedFightingMon::
    .string "我输了！这是事实！\p"
    .string "但是，我求你一件事，能不能\n"
    .string "别把我们的徽章作为你战利品！\p"
    .string "作为回报，我会送给你一只\n"
    .string "格斗属性宝可梦！\p"
    .string "选一只你喜欢的吧！$"

SaffronCity_Dojo_Text_StayAndTrainWithUs::
    .string "哼哼！\n"
    .string "在那儿站好陪我练练空手道吧！$"

SaffronCity_Dojo_Text_MikeIntro::
    .string "嚯利哟根！\n"
    .string "格斗前先脱掉你的鞋！$"

SaffronCity_Dojo_Text_MikeDefeat::
    .string "我认输了！$"

SaffronCity_Dojo_Text_MikePostBattle::
    .string "等你见到我们的掌门再说吧！\n"
    .string "和他比起来我不过是个杂鱼罢了！$"

SaffronCity_Dojo_Text_HidekiIntro::
    .string "听说你很厉害！\n"
    .string "展示给我看看吧！$"

SaffronCity_Dojo_Text_HidekiDefeat::
    .string "裁判！\n"
    .string "判分吧！$"

SaffronCity_Dojo_Text_HidekiPostBattle::
    .string "我们的掌门是一位格斗专家。\n"
    .string "做好失败的准备吧！$"

SaffronCity_Dojo_Text_AaronIntro::
    .string "嘿呀！\n"
    .string "任何事情都不能吓到我！\p"
    .string "为了训练\n"
    .string "我每天都在练习击碎巨石！$"

SaffronCity_Dojo_Text_AaronDefeat::
    .string "哟！\n"
    .string "我的手指断了！$"

SaffronCity_Dojo_Text_AaronPostBattle::
    .string "对我们格斗家来说\n"
    .string "最害怕的就是超能力！$"

SaffronCity_Dojo_Text_HitoshiIntro::
    .string "哗！\p"
    .string "你擅自闯入了我们的\n"
    .string "格斗道场$"

SaffronCity_Dojo_Text_HitoshiDefeat::
    .string "喔！\n"
    .string "我认输！$"

SaffronCity_Dojo_Text_HitoshiPostBattle::
    .string "这位祖师级的格斗大师\n"
    .string "跋山涉水来到这里修炼。$"

SaffronCity_Dojo_Text_YouWantHitmonlee::
    .string "你想要这只擅长踢技的\n"
    .string "飞腿郎？$"

SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster::
    .string "{PLAYER}从空手大王那里\n"
    .string "得到了{STR_VAR_1}$"

SaffronCity_Dojo_Text_YouWantHitmonchan::
    .string "你想要这只擅长拳击的\n"
    .string "快拳郎？$"

SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster2::
	.string "{PLAYER}は　カラテ　だいおう　から\n"
	.string "{STR_VAR_1}を　もらった！$"

SaffronCity_Dojo_Text_BetterNotGetGreedy::
    .string "不要贪心……$"

SaffronCity_Dojo_Text_EnemiesOnEverySide::
    .string "四面楚歌$"

SaffronCity_Dojo_Text_GoesAroundComesAround::
    .string "因果报应$"

SaffronCity_Dojo_Text_FightingDojo::
    .string "格斗道场$"

