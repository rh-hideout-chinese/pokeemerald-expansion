@ VAR_LAST_TALKED would have made all these direct references unnecessary
.set LOCALID_SMART_MC, 4
.set LOCALID_SMART_JUDGE, 5
.set LOCALID_SMART_CONTESTANT_1, 6
.set LOCALID_SMART_CONTESTANT_2, 7
.set LOCALID_SMART_CONTESTANT_3, 8
.set LOCALID_SMART_CONTESTANT_4, 9
.set LOCALID_SMART_AUDIENCE_4, 11
.set LOCALID_SMART_AUDIENCE_2, 12
.set LOCALID_BEAUTY_MC, 13
.set LOCALID_BEAUTY_JUDGE, 14
.set LOCALID_BEAUTY_CONTESTANT_1, 15
.set LOCALID_BEAUTY_CONTESTANT_2, 16
.set LOCALID_BEAUTY_CONTESTANT_3, 17
.set LOCALID_BEAUTY_CONTESTANT_4, 18
.set LOCALID_BEAUTY_AUDIENCE_1, 19
.set LOCALID_BEAUTY_AUDIENCE_3, 20
.set LOCALID_BEAUTY_AUDIENCE_2, 21
.set LOCALID_SMART_AUDIENCE_3, 22
.set LOCALID_CUTE_MC, 23
.set LOCALID_CUTE_JUDGE, 24
.set LOCALID_CUTE_CONTESTANT_1, 25
.set LOCALID_CUTE_CONTESTANT_2, 26
.set LOCALID_CUTE_CONTESTANT_3, 27
.set LOCALID_CUTE_CONTESTANT_4, 28
.set LOCALID_CUTE_AUDIENCE_1, 29
.set LOCALID_CUTE_AUDIENCE_3, 30
.set LOCALID_CUTE_AUDIENCE_2, 31

LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
    .string "这只宝可梦曾在这里\n胜过漂亮华丽大赛，\p然后你猜怎么了？我今天又带它\n赢了聪明华丽大赛！\p我的能力连我自己都吓了一跳…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
    .string "我多次参加过华丽大赛，\n所以比较了解这里的规则。\p如果你参加帅气大赛，\n帅气的招式才会吸引人，\p相对地，聪明的招式或可爱的招式等等\n就吸引不了别人。$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
    .string "刚刚赢了的那个年轻人\n拥有一大堆不同的能量方块。\p无论谁有那么多，\n都肯定会赢吧？$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
    .string "哇，这儿好大！\p空气中充满了紧张感…\n一点也不像是华丽大赛大厅。$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
    .string "主持：好了，聪明宝可梦和\n训练师们，准备好了吗？！\p努力吧！\n开始！$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
    .string "评委：你喜欢这华丽大赛吗？\p和三个朋友一起来，\n大家可以一起参加大赛！$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
    .string "啊呀啊呀啊呀…\n我参加错了，\p我让我强大的宝可梦\n参加了聪明大赛…\p好吧，用你聪慧的碎岩\n让他们大吃一惊吧。$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
    .string "我花了多年时间，\n用尽心思让我的宝可梦\l看上去聪明些，\p我不会被那些年轻人的宝可梦\n轻易比下去的。\p亲爱的，你看到了吗？$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
    .string "就是现在！\p如果下面我的宝可梦使用聪明的招式，\n观众的兴奋点会达到巅峰！$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
    .string "哎，宝贝，不！\p我亲爱的超音蝠的吸血太可爱了，\n我就一遍遍不断使用它！\p但这就意味着大家不会\n再欣赏它了！$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
    .string "呀啊啊啊！爷爷，你真棒！$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
    .string "即使训练师使用相同的宝可梦，\n他们用来吸引人的招式\l也会不一样，\p这和大家的战斗方式不同\n是同样的道理。$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
    .string "我想宝可梦看上去\n比它们的训练师还要聪明。$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
    .string "无论人们说什么，\n我都喜欢聪明大赛。\p那智慧的绿色…\n它非常…非常…美妙。$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
    .string "主持：你也要参加\n漂亮部门吗？加油！$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
    .string "评委：啊，这儿的每只宝可梦\n都拥有着纯洁的美！\p哎，我都忘了要为它们计分了！$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
    .string "这么漂亮的宝可梦…\n没有什么能比得上它，\p大家的目光都会聚集在\n它的美丽上。$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
    .string "哇啊啊啊！\p参加大赛前我非常细心地\n为我的宝可梦梳洗…\p但我做得好像过头了…\n我的宝可梦的服装看上去很乱…\p我该怎么办？$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
    .string "极光光线太耀眼了，\n评委会看不清的。\p呃，等等…\n这根本没有意义！$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
    .string "这只漂亮的宝可梦\n和我小时候很像。\p我这么说的时候，\n老公把咖啡都喷了。\p这句话很奇怪吗？$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
    .string "如果我在美丽组取胜\n我会比平常任何时候都开心。$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
    .string "啊哈哈哈哈！\p看看这些漂亮的宝可梦！\n我最喜欢这种华丽！$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
    .string "只有美丽不可能\n长久获胜下去，\p还得经常为宝可梦梳洗，\n让它像我一样光彩照人。$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
    .string "主持：呃，啊，你好！\n现在华丽大赛正在进行之中！\p请先去接待处登记\n再来参加比赛。$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
    .string "评委：啊，如此迷人，\n如此可爱！\p哎，天啊！那水之游\n多么完美，多么可爱！$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
    .string "哦，不…我的小露力丽\n被忽视了。$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
    .string "我的宝可梦战斗从未赢过，\n但看看它在华丽大赛的表现吧！$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
    .string "我的宝可梦的花之舞\n奇妙而优美，\p我不会让任何人\n打扰它的表演。$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
    .string "大家的宝可梦都很可爱，\p但是，如果我的宝可梦\n想表现的可爱一些…\p我相信它会\n比其他的更可爱。$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
    .string "我孩子正在参加华丽大赛。$"

LilycoveCity_ContestHall_Text_ComeOnDear:
    .string "来吧，加油！\n你的宝可梦是最棒的！$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
    .string "我想那边的女孩\n是人群中最可爱的。\p你说什么？他们在\n评判宝可梦的外貌？$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
    .string "看着这些可爱的宝可梦，\n让我也想自己拥有一只！\p我要去抓一只来！$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
    .string "漂亮部门会场\n美丽宝可梦的诱惑！$"

LilycoveCity_ContestHall_Text_CuteContestStage:
    .string "可爱部门会场\n迷醉于可爱的宝可梦吧！$"

LilycoveCity_ContestHall_Text_SmartContestStage:
    .string "聪明部门会场\n聪明的宝可梦，深刻的印象！$"

