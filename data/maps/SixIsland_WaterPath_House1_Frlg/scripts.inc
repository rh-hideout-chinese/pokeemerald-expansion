SixIsland_WaterPath_House1_Frlg_MapScripts::
	.byte 0

SixIsland_WaterPath_House1_EventScript_Beauty::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_HERACROSS
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, FALSE, SixIsland_WaterPath_House1_EventScript_NoHeracrossInParty
	special GetHeracrossSizeRecordInfo
	msgbox SixIsland_WaterPath_House1_Text_MayIMeasureHeracross
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_ge VAR_RESULT, PARTY_SIZE, SixIsland_WaterPath_House1_EventScript_DontShowMon
	special CompareHeracrossSize
	goto_if_eq VAR_RESULT, 1, SixIsland_WaterPath_House1_EventScript_ShownNonHeracross
	goto_if_eq VAR_RESULT, 2, SixIsland_WaterPath_House1_EventScript_ShownSmallHeracross
	goto_if_eq VAR_RESULT, 3, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	goto_if_eq VAR_RESULT, 4, SixIsland_WaterPath_House1_EventScript_ShownTiedHeracross
	release
	end

SixIsland_WaterPath_House1_EventScript_NoHeracrossInParty::
	msgbox SixIsland_WaterPath_House1_Text_LoveItNeedItHeracross
	release
	end

SixIsland_WaterPath_House1_EventScript_DontShowMon::
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownNonHeracross::
	msgbox SixIsland_WaterPath_House1_Text_ThisWontDo
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownSmallHeracross::
	goto_if_unset FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesYInchesWasBiggest
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownTiedHeracross::
	goto_if_unset FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesSameAsBefore
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownBigHeracross::
	setflag FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesDeserveReward
	giveitem ITEM_NEST_BALL
	goto_if_eq VAR_RESULT, FALSE, SixIsland_WaterPath_House1_EventScript_NoRoomForNestBall
	msgbox SixIsland_WaterPath_House1_Text_WantToSeeBiggerOne
	release
	end

SixIsland_WaterPath_House1_EventScript_NoRoomForNestBall::
	msgbox SixIsland_WaterPath_House1_Text_YourBagIsFull
	release
	end

SixIsland_WaterPath_House1_EventScript_SizeRecord::
	lockall
	goto_if_set FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_SizeRecordNonEmpty
	msgbox SixIsland_WaterPath_House1_Text_BlankChartOfSomeSort
	releaseall
	end

SixIsland_WaterPath_House1_EventScript_SizeRecordNonEmpty::
	special GetHeracrossSizeRecordInfo
	msgbox SixIsland_WaterPath_House1_Text_BiggestHeracrossIsXInches
	releaseall
	end

SixIsland_WaterPath_House1_Text_LoveItNeedItHeracross::
    .string "赫拉，赫拉，赫拉克罗斯！\n"
    .string "威武闪光的虫属性之王！\l"
    .string "我爱它，我需要它！赫拉克罗斯！$"

SixIsland_WaterPath_House1_Text_MayIMeasureHeracross::
    .string "哎呦！\n"
    .string "那是一只赫拉克罗斯！\p"
    .string "快，快！\n"
    .string "我能量量它有多大吗……$"

SixIsland_WaterPath_House1_Text_ItsXInchesDeserveReward::
    .string "哎呦它居然有{STR_VAR_2}英寸！\n"
    .string "我从来没见过这样大的！\l"
    .string "这是你应得的奖励。$"

SixIsland_WaterPath_House1_Text_WantToSeeBiggerOne::
    .string "我想看到一只比这个\n"
    .string "还要大一些的赫拉克罗斯。\p"
    .string "啊，我是多么喜欢它啊！\n"
    .string "巨大的赫拉克罗斯！$"

SixIsland_WaterPath_House1_Text_ItsXInchesSameAsBefore::
    .string "哼？这只{STR_VAR_2}英寸的……\n"
    .string "不是和原来那只一样吗！$"

SixIsland_WaterPath_House1_Text_ItsXInchesYInchesWasBiggest::
    .string "哦，它只有{STR_VAR_2}英寸。\n"
    .string "原来那只赫拉克罗斯比它更大。\p"
    .string "它有{STR_VAR_3}英寸，\n"
    .string "那是我见过的最大的赫拉克罗斯。$"

SixIsland_WaterPath_House1_Text_ThisWontDo::
    .string "哦，不！这不可能是赫拉克罗斯！\p"
    .string "赫拉克罗斯看起来更有气概，\n"
    .string "更加冷酷，还有一只可爱的触角！$"

SixIsland_WaterPath_House1_Text_YourBagIsFull::
    .string "你的背包满了。\n"
    .string "装不下我的奖励了。$"

SixIsland_WaterPath_House1_Text_BiggestHeracrossIsXInches::
    .string "目前为止，我看过的最大的赫拉克罗斯，\n"
    .string "尺寸为：\p"
    .string "{STR_VAR_3}英寸！$"

SixIsland_WaterPath_House1_Text_BlankChartOfSomeSort::
    .string "那差不多是一张空白的图表。\p"
    .string "它有空间\n"
    .string "来写一些记录。$"

