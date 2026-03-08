FiveIsland_MemorialPillar_Frlg_MapScripts::
	.byte 0

FiveIsland_MemorialPillar_EventScript_MemorialMan::
	lock
	goto_if_set FLAG_GOT_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42
	goto_if_set FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_ReturnedForTM42
	msgbox FiveIsland_MemorialPillar_Text_ScrubScrub
	closemessage
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_FacePlayer
	waitmovement 0
	delay 45
	msgbox FiveIsland_MemorialPillar_Text_YourMonsLookHealthy
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox FiveIsland_MemorialPillar_Text_ThisIsWhereIBuriedMyOnix
	release
	end

FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42::
	msgbox FiveIsland_MemorialPillar_Text_ScrubScrubTectonix
	release
	end

FiveIsland_MemorialPillar_EventScript_ReturnedForTM42::
	msgbox FiveIsland_MemorialPillar_Text_StillHaveThingAsMyThanks
	giveitem ITEM_TM42
	goto_if_eq VAR_RESULT, FALSE, FiveIsland_MemorialPillar_EventScript_NoRoomForTM42
	call FiveIsland_MemorialPillar_EventScript_ReceivedTM42
	release
	end

FiveIsland_MemorialPillar_EventScript_Memorial::
	lockall
	goto_if_set FLAG_GOT_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced
	goto_if_set FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced
	msgbox FiveIsland_MemorialPillar_Text_HereLiesTectonixLemonadeOffering
	checkitem ITEM_LEMONADE
	goto_if_eq VAR_RESULT, TRUE, FiveIsland_MemorialPillar_EventScript_AskPlaceLemonade
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_AskPlaceLemonade::
	msgbox FiveIsland_MemorialPillar_Text_LeaveAnotherLemonadeOffering, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FiveIsland_MemorialPillar_EventScript_PlaceLemonade
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_PlaceLemonade::
	removeitem ITEM_LEMONADE
	msgbox FiveIsland_MemorialPillar_Text_PlacedCanOfLemonade
	closemessage
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 45
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FiveIsland_MemorialPillar_Text_ThankYouPleaseTakeThis
	giveitem ITEM_TM42
	goto_if_eq VAR_RESULT, FALSE, FiveIsland_MemorialPillar_EventScript_NoRoomForTM42
	call FiveIsland_MemorialPillar_EventScript_ReceivedTM42
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_ReceivedTM42::
	msgbox FiveIsland_MemorialPillar_Text_BeGoodToYourMonsToo
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	setflag FLAG_GOT_TM42_AT_MEMORIAL_PILLAR
	return

FiveIsland_MemorialPillar_EventScript_NoRoomForTM42::
	setflag FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR
	msgbox FiveIsland_MemorialPillar_Text_DontHaveRoomForIt
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced::
	msgbox FiveIsland_MemorialPillar_Text_HereLiesTectonix
	releaseall
	end

FiveIsland_MemorialPillar_Text_MiloIntro::
    .string "我是驯鸟师兄弟中年纪最大的。\p"
    .string "鸟系宝可梦最吸引人的地方……\n"
    .string "当然是它们的喙。$"

FiveIsland_MemorialPillar_Text_MiloDefeat::
    .string "噢，太突然了！$"

FiveIsland_MemorialPillar_Text_MiloPostBattle::
    .string "从这儿你可以飞去四之岛。$"

FiveIsland_MemorialPillar_Text_ChazIntro::
    .string "我是驯鸟师兄弟中的老二。\p"
    .string "鸟系宝可梦吸引人的地方……\n"
    .string "当然是它们的翅膀。$"

FiveIsland_MemorialPillar_Text_ChazDefeat::
    .string "啪，砰！$"

FiveIsland_MemorialPillar_Text_ChazPostBattle::
    .string "那条路上有一个阴沉的家伙。$"

FiveIsland_MemorialPillar_Text_HaroldIntro::
    .string "我是驯鸟师兄弟中年龄最小的。\p"
    .string "鸟系宝可梦最吸引人的地方……\n"
    .string "当然是它们的羽毛。$"

FiveIsland_MemorialPillar_Text_HaroldDefeat::
    .string "羽毛太舒服了……\n"
    .string "它让我想美美地睡过去……$"

FiveIsland_MemorialPillar_Text_HaroldPostBattle::
    .string "当鸟系宝可梦缠着我跟它们\n"
    .string "玩耍时，我心中就充满了快乐……$"

FiveIsland_MemorialPillar_Text_ScrubScrub::
    .string "刷，刷……$"

FiveIsland_MemorialPillar_Text_YourMonsLookHealthy::
    .string "你好……\n"
    .string "你的宝可梦看起来很健康……$"

FiveIsland_MemorialPillar_Text_ThisIsWhereIBuriedMyOnix::
    .string "这是埋葬我的大岩蛇的地方……\n"
    .string "它叫做阿岩……$"

FiveIsland_MemorialPillar_Text_HereLiesTectonixLemonadeOffering::
    .string "碑上刻着：\n"
    .string "“阿岩长眠于此”。\p"
    .string "坟墓的前面放着\n"
    .string "一罐果汁牛奶作为祭品。$"

FiveIsland_MemorialPillar_Text_LeaveAnotherLemonadeOffering::
    .string "你也想留下一罐果汁牛奶\n"
    .string "作为祭品吗？$"

FiveIsland_MemorialPillar_Text_PlacedCanOfLemonade::
    .string "{PLAYER}在坟墓前面\n"
    .string "放了一罐果汁牛奶。$"

FiveIsland_MemorialPillar_Text_ThankYouPleaseTakeThis::
    .string "谢谢你……\p"
    .string "那是我的阿岩最爱喝的饮料……\p"
    .string "我不知道你是谁，但是\n"
    .string "你的仁慈感动了我……\p"
    .string "我现在振作一些了。\p"
    .string "作为我的谢意，\n"
    .string "你能收下这个吗？$"

FiveIsland_MemorialPillar_Text_BeGoodToYourMonsToo::
    .string "请你也好好对待你自己的宝可梦。$"

FiveIsland_MemorialPillar_Text_DontHaveRoomForIt::
    .string "如果你没有空间装这个了，\n"
    .string "我会下次给你的。$"

FiveIsland_MemorialPillar_Text_StillHaveThingAsMyThanks::
    .string "噢，你是上次的那个孩子……\p"
    .string "我仍然拿着想给你\n"
    .string "作为谢礼的礼物。$"

FiveIsland_MemorialPillar_Text_ScrubScrubTectonix::
    .string "呲，呲……\p"
    .string "…………\n"
    .string "阿岩……$"

FiveIsland_MemorialPillar_Text_HereLiesTectonix::
    .string "这个碑是一些很干净的石块做成的。\p"
    .string "碑上刻着：\n"
    .string "“阿岩长眠于此”。$"

