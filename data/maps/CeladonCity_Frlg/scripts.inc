CeladonCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_OnTransition
	.byte 0

CeladonCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CELADON_CITY
	end

CeladonCity_EventScript_LittleGirl::
	msgbox CeladonCity_Text_GotMyKoffingInCinnabar, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan1::
	lock
	msgbox CeladonCity_Text_GymIsGreatFullOfWomen
	release
	end

CeladonCity_EventScript_Woman::
	msgbox CeladonCity_Text_GameCornerIsBadForCitysImage, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan2::
	msgbox CeladonCity_Text_BlewItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_EventScript_SoftboiledTutor::
	goto EventScript_SoftboiledTutor
	end

CeladonCity_EventScript_FatMan::
	lock
	faceplayer
	msgbox CeladonCity_Text_MyTrustedPalPoliwrath
	closemessage
	applymovement LOCALID_CELADON_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath
	closemessage
	waitmoncry
	applymovement LOCALID_CELADON_POLIWRATH, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_RocketGrunt1::
	msgbox CeladonCity_Text_KeepOutOfTeamRocketsWay, MSGBOX_NPC
	end

CeladonCity_EventScript_RocketGrunt2::
	msgbox CeladonCity_Text_GetLostOrIllPunchYou, MSGBOX_NPC
	end

CeladonCity_EventScript_Boy::
	msgbox CeladonCity_Text_ScaldedTongueOnTea, MSGBOX_NPC
	end

CeladonCity_EventScript_SilphCoScientist::
	msgbox CeladonCity_Text_SomeoneStoleSilphScope, MSGBOX_NPC
	end

CeladonCity_EventScript_TrainerTips1::
	msgbox CeladonCity_Text_ExplainXAccuracyDireHit, MSGBOX_SIGN
	end

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_CitySign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_ERIKA, 0
	msgbox CeladonCity_Text_GymSign
	releaseall
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_DeptStoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips2::
	msgbox CeladonCity_Text_GuardSpecProtectsFromStatus, MSGBOX_SIGN
	end

CeladonCity_EventScript_PrizeExchangeSign::
	msgbox CeladonCity_Text_PrizeExchangeSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

CeladonCity_Text_GotMyKoffingInCinnabar::
	.string "我在红莲得到了瓦斯弹。\p"
	.string "它很棒，不过每次它一生气就\n"
	.string "会喷出毒气。$"

CeladonCity_Text_GymIsGreatFullOfWomen::
	.string "呵呵呵呵！这个道馆很来劲啊！\n"
	.string "里面全都是女生啊！$"

CeladonCity_Text_GameCornerIsBadForCitysImage::
	.string "玉虹市长久不变的靓景一直是\n"
	.string "城市引以为豪的地方。\p"
	.string "但是这样一来游戏厅的营业\n"
	.string "是不利于市容市貌的。$"

CeladonCity_Text_BlewItAllAtSlots::
	.string "哇……\n"
	.string "我玩老虎机人品爆发啦！\p"
	.string "赶紧用代币去兑换超级\n"
	.string "大奖去！$"

CeladonCity_Text_MyTrustedPalPoliwrath::
	.string "这是我最信任的朋友，蚊香泳士！\p"
	.string "当我使用水之石之后，\n"
	.string "它从蚊香君进化过来了。$"

CeladonCity_Text_Poliwrath::
	.string "蚊香泳士 哩吡哩吡特！$"

CeladonCity_Text_GetLostOrIllPunchYou::
	.string "你在看什么呢？\n"
	.string "滚开，不然我就揍你。$"

CeladonCity_Text_KeepOutOfTeamRocketsWay::
	.string "离火箭队远点！$"

CeladonCity_Text_ExplainXAccuracyDireHit::
	.string "训练家贴士\p"
	.string "命中强化能提高攻击的准确性。\p"
	.string "致命攻击提高触发命中要害的几率。\p"
	.string "它们在玉虹百货大楼都能买到！$"

CeladonCity_Text_CitySign::
	.string "玉虹市\n"
	.string "拥有彩虹般梦想的城市$"

CeladonCity_Text_GymSign::
	.string "玉虹市宝可梦道馆\n"
	.string "馆主：莉佳\l"
	.string "热爱自然的公主！$"

CeladonCity_Text_MansionSign::
	.string "玉虹大厦$"

CeladonCity_Text_DeptStoreSign::
	.string "在玉虹百货大楼寻找你想要的！$"

CeladonCity_Text_GuardSpecProtectsFromStatus::
	.string "训练家贴士\p"
	.string "能力防守保护宝可梦\n"
	.string "使其战斗中能力不会下降。\p"
	.string "在玉虹百货大楼都能买到！$"

CeladonCity_Text_PrizeExchangeSign::
	.string "代币兑换奖品！\n"
	.string "奖品兑换$"

CeladonCity_Text_GameCornerSign::
	.string "火箭队游戏厅\n"
	.string "大人们的游乐场！$"

CeladonCity_Text_ScaldedTongueOnTea::
	.string "啊 喔……\n"
	.string "我的舌头被烫伤了！\p"
	.string "大厦里的老妇人\n"
	.string "给我喝了一些茶。\p"
	.string "但茶太烫了！\n"
	.string "必须等凉下来之后再喝。$"

Text_SoftboiledTeach::
	.string "小朋友，你好！\p"
	.string "我曾经看见过你好多次，\n"
	.string "但未能有过畅谈的机会。\p"
	.string "所幸现在我们成功相聚。\p"
	.string "让我教你技能生蛋\n"
	.string "来庆祝下这感人的一刻吧。$"

Text_SoftboiledDeclined::
	.string "我会一直关注你的。\p"
	.string "有空了再过来聊聊啊。$"

Text_SoftboiledWhichMon::
	.string "那么，哪只宝可梦想要\n"
	.string "学习生蛋呢？$"

Text_SoftboiledTaught::
	.string "祝你好运！$"

CeladonCity_Text_SomeoneStoleSilphScope::
	.string "呃，我在做什么啊……\p"
	.string "有人把我们的西尔佛观测镜偷走了。\p"
	.string "小偷从这条路跑了，\n"
	.string "没错。\p"
	.string "但我找不到他了！\n"
	.string "他去哪了？$"

