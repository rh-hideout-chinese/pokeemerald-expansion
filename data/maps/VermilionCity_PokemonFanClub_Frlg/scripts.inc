.set SPOKE_TO_WOMAN_LAST,   FLAG_TEMP_2
.set SPOKE_TO_FAT_MAN_LAST, FLAG_TEMP_3

VermilionCity_PokemonFanClub_Frlg_MapScripts::
	.byte 0

VermilionCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BIKE_VOUCHER, VermilionCity_PokemonFanClub_EventScript_AlreadyHeardStory
	msgbox VermilionCity_PokemonFanClub_Text_DidYouComeToHearAboutMyMons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VermilionCity_PokemonFanClub_EventScript_ChairmanStory
	msgbox VermilionCity_PokemonFanClub_Text_ComeBackToHearStory
	release
	end

VermilionCity_PokemonFanClub_EventScript_AlreadyHeardStory::
	msgbox VermilionCity_PokemonFanClub_Text_DidntComeToSeeAboutMonsAgain
	release
	end

VermilionCity_PokemonFanClub_EventScript_ChairmanStory::
	msgbox VermilionCity_PokemonFanClub_Text_ChairmansStory
	checkitemspace ITEM_BIKE_VOUCHER
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher
	setflag FLAG_GOT_BIKE_VOUCHER
	giveitem_msg VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman, ITEM_BIKE_VOUCHER, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher
	release
	end

VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher::
	msgbox VermilionCity_PokemonFanClub_Text_MakeRoomForThis
	release
	end

VermilionCity_PokemonFanClub_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, VermilionCity_PokemonFanClub_EventScript_WorkerFGameClear
	msgbox VermilionCity_PokemonFanClub_Text_ChairmanVeryVocalAboutPokemon
	release
	end

VermilionCity_PokemonFanClub_EventScript_WorkerFGameClear::
	famechecker FAMECHECKER_DAISY, 1
	msgbox VermilionCity_PokemonFanClub_Text_ChairmanReallyAdoresHisMons
	release
	end

VermilionCity_PokemonFanClub_EventScript_Woman::
	lock
	faceplayer
	goto_if_set SPOKE_TO_FAT_MAN_LAST, VermilionCity_PokemonFanClub_EventScript_WomanSpokeToFatMan
	msgbox VermilionCity_PokemonFanClub_Text_AdoreMySeel
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag SPOKE_TO_WOMAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_WomanSpokeToFatMan::
	msgbox VermilionCity_PokemonFanClub_Text_SeelFarMoreAttractive
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	clearflag SPOKE_TO_FAT_MAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set SPOKE_TO_WOMAN_LAST, VermilionCity_PokemonFanClub_EventScript_FatManSpokeToWoman
	msgbox VermilionCity_PokemonFanClub_Text_AdmirePikachusTail
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag SPOKE_TO_FAT_MAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_FatManSpokeToWoman::
	msgbox VermilionCity_PokemonFanClub_Text_PikachuTwiceAsCute
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	clearflag SPOKE_TO_WOMAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VermilionCity_PokemonFanClub_Text_Pikachu
	waitmoncry
	release
	end

VermilionCity_PokemonFanClub_EventScript_Seel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SEEL, CRY_MODE_NORMAL
	msgbox VermilionCity_PokemonFanClub_Text_Seel
	waitmoncry
	release
	end

VermilionCity_PokemonFanClub_EventScript_RulesSign1::
	msgbox VermilionCity_PokemonFanClub_Text_ListenPolitelyToOtherTrainers, MSGBOX_SIGN
	end

VermilionCity_PokemonFanClub_EventScript_RulesSign2::
	msgbox VermilionCity_PokemonFanClub_Text_SomeoneBragsBragBack, MSGBOX_SIGN
	end

VermilionCity_PokemonFanClub_Text_AdmirePikachusTail::
    .string "你不喜欢我的皮卡丘的\n"
    .string "讨人爱的尾巴吗？$"

VermilionCity_PokemonFanClub_Text_PikachuTwiceAsCute::
    .string "哼！\p"
    .string "我的皮卡丘有\n"
    .string "你那一只两倍的可爱！$"

VermilionCity_PokemonFanClub_Text_AdoreMySeel::
    .string "我非常喜欢我的小海狮！\n"
    .string "它太可爱啦！\p"
    .string "当我抱着它时，\n"
    .string "它会叫着，“咕呜。”$"

VermilionCity_PokemonFanClub_Text_SeelFarMoreAttractive::
    .string "噢，天哪！\p"
    .string "我的小海狮太有吸引力了。\n"
    .string "我不得不说。$"

VermilionCity_PokemonFanClub_Text_Pikachu::
    .string "皮卡丘：丘！皮卡丘！$"

VermilionCity_PokemonFanClub_Text_Seel::
    .string "小海狮：咕呜！$"

VermilionCity_PokemonFanClub_Text_DidYouComeToHearAboutMyMons::
    .string "我经营着宝可梦同好会！\p"
    .string "我培养着100多只宝可梦！\p"
    .string "当谈到宝可梦时我会变得很激动！\n"
    .string "真的是这样！\p"
    .string "所以……\p"
    .string "你是来听我的宝可梦的故事的吗？$"

VermilionCity_PokemonFanClub_Text_ChairmansStory::
    .string "好！\n"
    .string "听好了！\p"
    .string "我最喜爱的烈焰马……\p"
    .string "它真是漂亮……可爱……聪明……\n"
    .string "异乎寻常……你这样认为吗？\l"
    .string "对……它很出色……\l"
    .string "友好……好喜欢它！\p"
    .string "抱着它……睡觉时……\n"
    .string "感到温暖……亲切……\l"
    .string "迷人……\l"
    .string "……哎！看这时间！\l"
    .string "我让你呆太久了！\p"
    .string "谢谢你一直在听我说！\n"
    .string "我要给你这个！$"

VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman::
    .string "{PLAYER}从主席那里\n"
    .string "得到了自行车兑换券。$"

VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher::
    .string "拿着这个自行车兑换券去\n"
    .string "华蓝市的自行车行。\p"
    .string "可以免费换到一辆自行车！\p"
    .string "别担心，我的大嘴雀\n"
    .string "会带我飞翔到任何我想去的地方。\p"
    .string "所以，我不需要自行车。\p"
    .string "我希望你喜欢骑车！$"

VermilionCity_PokemonFanClub_Text_ComeBackToHearStory::
    .string "噢。当你想听我的故事时\n"
    .string "就再回来吧！$"

VermilionCity_PokemonFanClub_Text_DidntComeToSeeAboutMonsAgain::
    .string "你好，{PLAYER}！\p"
    .string "你是再来听我讲我的\n"
    .string "宝可梦的吗？\p"
    .string "不是？\n"
    .string "太糟糕了！$"

VermilionCity_PokemonFanClub_Text_MakeRoomForThis::
    .string "要腾出空间来放这个！$"

VermilionCity_PokemonFanClub_Text_ChairmanVeryVocalAboutPokemon::
    .string "我们的主席在说到\n"
    .string "宝可梦时口才特别好。$"

VermilionCity_PokemonFanClub_Text_ListenPolitelyToOtherTrainers::
    .string "我们都很耐心地听其他\n"
    .string "训练家说话！$"

VermilionCity_PokemonFanClub_Text_SomeoneBragsBragBack::
    .string "当有人在晒的时侯，给他晒回去！$"

VermilionCity_PokemonFanClub_Text_ChairmanReallyAdoresHisMons::
    .string "我们的主席真的很喜欢他的宝可梦。\p"
    .string "但是我觉得更喜欢\n"
    .string "宝可梦的人是奈奈美。$"
