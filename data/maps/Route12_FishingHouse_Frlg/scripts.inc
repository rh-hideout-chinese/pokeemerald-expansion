Route12_FishingHouse_Frlg_MapScripts::
	.byte 0

Route12_FishingHouse_EventScript_FishingGuruBrother::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUPER_ROD, Route12_FishingHouse_EventScript_CheckMagikarpRecord
	msgbox Route12_FishingHouse_Text_DoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route12_FishingHouse_EventScript_GiveSuperRod
	msgbox Route12_FishingHouse_Text_OhThatsDisappointing
	release
	end

Route12_FishingHouse_EventScript_GiveSuperRod::
	checkitemspace ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoRoomForSuperRod
	additem ITEM_SUPER_ROD
	msgbox Route12_FishingHouse_Text_TakeThisAndFish
	msgreceiveditem Route12_FishingHouse_Text_ReceivedSuperRod, ITEM_SUPER_ROD
	setflag FLAG_GOT_SUPER_ROD
	msgbox Route12_FishingHouse_Text_IfYouCatchBigMagikarpShowMe
	release
	end

Route12_FishingHouse_EventScript_NoRoomForSuperRod::
	msgbox Route12_FishingHouse_Text_NoRoomForGift
	release
	end

Route12_FishingHouse_EventScript_CheckMagikarpRecord::
	setvar VAR_0x8004, SPECIES_MAGIKARP
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoMagikarpInParty
	special GetMagikarpSizeRecordInfo
	msgbox Route12_FishingHouse_Text_OhMagikarpAllowMeToSee
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_ge VAR_RESULT, PARTY_SIZE, Route12_FishingHouse_EventScript_CancelShowMon
	special CompareMagikarpSize
	goto_if_eq VAR_RESULT, 1, Route12_FishingHouse_EventScript_NotMagikarp
	goto_if_eq VAR_RESULT, 2, Route12_FishingHouse_EventScript_NotRecordMagikarp
	goto_if_eq VAR_RESULT, 3, Route12_FishingHouse_EventScript_NewRecordMagikarp
	goto_if_eq VAR_RESULT, 4, Route12_FishingHouse_EventScript_TieRecordMagikarp
	release
	end

Route12_FishingHouse_EventScript_NoMagikarpInParty::
	msgbox Route12_FishingHouse_Text_TryFishingBringMeMagikarp
	release
	end

Route12_FishingHouse_EventScript_CancelShowMon::
	release
	end

Route12_FishingHouse_EventScript_NotMagikarp::
	msgbox Route12_FishingHouse_Text_DoesntLookLikeMagikarp
	release
	end

Route12_FishingHouse_EventScript_NotRecordMagikarp::
	goto_if_unset FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_NewRecordMagikarp
	msgbox Route12_FishingHouse_Text_HmmXInchesDoesntMeasureUp
	release
	end

Route12_FishingHouse_EventScript_TieRecordMagikarp::
	goto_if_unset FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_NewRecordMagikarp
	msgbox Route12_FishingHouse_Text_HuhXInchesSameSizeAsLast
	release
	end

Route12_FishingHouse_EventScript_NewRecordMagikarp::
	setflag FLAG_GOT_RECORD_SETTING_MAGIKARP
	msgbox Route12_FishingHouse_Text_WhoaXInchesTakeThis
	giveitem ITEM_NET_BALL
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoRoomForNetBall
	msgbox Route12_FishingHouse_Text_LookForwardToGreaterRecords
	release
	end

Route12_FishingHouse_EventScript_NoRoomForNetBall::
	msgbox Route12_FishingHouse_Text_NoRoomForGift
	release
	end

Route12_FishingHouse_EventScript_MagikarpRecordSign::
	lockall
	goto_if_set FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_MagikarpRecordSignRecordSet
	msgbox Route12_FishingHouse_Text_BlankChartOfSomeSort
	releaseall
	end

Route12_FishingHouse_EventScript_MagikarpRecordSignRecordSet::
	special GetMagikarpSizeRecordInfo
	msgbox Route12_FishingHouse_Text_MostGiganticMagikarpXInches
	releaseall
	end

Route12_FishingHouse_Text_DoYouLikeToFish::
    .string "我是钓鱼大师的\n"
    .string "年轻弟弟。\p"
    .string "我真的很爱钓鱼！\n"
    .string "没有它我活不下去。\p"
    .string "告诉我吧，你喜欢钓鱼吗？$"

Route12_FishingHouse_Text_TakeThisAndFish::
    .string "很好！我喜欢你的态度。\n"
    .string "我认为我们能够成为朋友，\p"
    .string "带上它，去钓鱼吧年轻的朋友！$"

Route12_FishingHouse_Text_ReceivedSuperRod::
    .string "{PLAYER}从钓鱼大师的弟弟那儿\n"
    .string "得到了超级钓竿。$"

Route12_FishingHouse_Text_IfYouCatchBigMagikarpShowMe::
    .string "钓鱼是人生的一种旅途。\n"
    .string "它就像是最美的诗歌。\p"
    .string "从海洋到河流 \n"
    .string "快去吧，我的朋友，钓条大鱼给我看看！\p"
    .string "现在，我还有一个请求。\p"
    .string "如果你用破钓竿钓到了大鲤鱼王。\n"
    .string "就给我看看吧，\p"
    .string "我不但喜欢钓鱼\n"
    .string "还喜欢看大的鲤鱼王。$"

Route12_FishingHouse_Text_OhThatsDisappointing::
    .string "哦……\n"
    .string "太令人失望了……$"

Route12_FishingHouse_Text_TryFishingBringMeMagikarp::
    .string "嗨 {PLAYER}\n"
    .string "你钓过鱼了吗？\p"
    .string "尝试用超级钓竿在不同\n"
    .string "的地方钓鱼吧。\p"
    .string "在不同的地方你会\n"
    .string "钓到不同的宝可梦。\p"
    .string "还有，不要忘了带\n"
    .string "大的鲤鱼王给我看喔。$"

Route12_FishingHouse_Text_OhMagikarpAllowMeToSee::
    .string "哦？{PLAYER}？\n"
    .string "给我看看 那只鲤鱼王够不够大\p"
    .string "给我看看 快！$"

Route12_FishingHouse_Text_WhoaXInchesTakeThis::
    .string "……哇！\n"
    .string "{STR_VAR_2}英寸！\p"
    .string "在捕鱼方面\n"
    .string "你的技能好棒啊！\p"
    .string "我坚信，\n"
    .string "这个一定会对你有用的。$"

Route12_FishingHouse_Text_LookForwardToGreaterRecords::
    .string "我希望能从你这儿\n"
    .string "看到更好的记录。$"

Route12_FishingHouse_Text_HuhXInchesSameSizeAsLast::
    .string "哼？\n"
    .string "{STR_VAR_2}英寸？\p"
    .string "这和我以前看到过的\n"
    .string "是一个尺寸。$"

Route12_FishingHouse_Text_HmmXInchesDoesntMeasureUp::
    .string "呃……\n"
    .string "这条只有{STR_VAR_2}英寸。\p"
    .string "它和你以前买的那条\n"
    .string "{STR_VAR_3}英寸的，完全比不了……$"

Route12_FishingHouse_Text_DoesntLookLikeMagikarp::
    .string "呃……这看起来不像是\n"
    .string "一条鲤鱼王。$"

Route12_FishingHouse_Text_NoRoomForGift::
    .string "哦，太不好了！\p"
    .string "我要给你一件礼物，\n"
    .string "但你身上没有足够的空间来放。$"

Route12_FishingHouse_Text_MostGiganticMagikarpXInches::
    .string "我曾见过的\n"
    .string "最大的鲤鱼王它有……\p"
    .string "{STR_VAR_3}英尺！$"

Route12_FishingHouse_Text_BlankChartOfSomeSort::
    .string "一张空白的图表。\p"
    .string "空白的地方可以\n"
    .string "做一些记录。$"

