VermilionCity_House1_Frlg_MapScripts::
	.byte 0

VermilionCity_House1_EventScript_FishingGuru::
	lock
	faceplayer
	goto_if_set FLAG_GOT_OLD_ROD, VermilionCity_House1_EventScript_AlreadyGotOldRod
	msgbox VermilionCity_House1_Text_ImFishingGuruDoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VermilionCity_House1_EventScript_GiveOldRod
	msgbox VermilionCity_House1_Text_OhThatsSoDisappointing
	release
	end

VermilionCity_House1_EventScript_AlreadyGotOldRod::
	msgbox VermilionCity_House1_Text_HowAreTheFishBiting
	release
	end

VermilionCity_House1_EventScript_GiveOldRod::
	checkitemspace ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_House1_EventScript_NoRoomForOldRod
	additem ITEM_OLD_ROD
	msgbox VermilionCity_House1_Text_TakeThisAndFish
	msgreceiveditem VermilionCity_House1_Text_ReceivedOldRodFromFishingGuru, ITEM_OLD_ROD
	setflag FLAG_GOT_OLD_ROD
	msgbox VermilionCity_House1_Text_FishingIsAWayOfLife
	release
	end

VermilionCity_House1_EventScript_NoRoomForOldRod::
	msgbox VermilionCity_House1_Text_NoRoomForNiceGift
	release
	end

VermilionCity_House1_Text_ImFishingGuruDoYouLikeToFish::
    .string "我是钓鱼大师！\p"
    .string "我相当喜欢钓鱼。\n"
    .string "不钓鱼的日子我一天也受不了。\p"
    .string "告诉我，你喜欢钓鱼吗？$"

VermilionCity_House1_Text_TakeThisAndFish::
    .string "好极了，我喜欢你的风格。\n"
    .string "我想我们能成为朋友。\p"
    .string "拿着这个享受垂钓吧，朋友！$"

VermilionCity_House1_Text_ReceivedOldRodFromFishingGuru::
    .string "{PLAYER}从钓鱼大师那儿得到了破钓竿。$"

VermilionCity_House1_Text_FishingIsAWayOfLife::
    .string "钓鱼是一种生活方式！\n"
    .string "就像是最美的诗歌。\p"
    .string "从海洋到河流，\n"
    .string "去钓上最大的那条，我的朋友。$"

VermilionCity_House1_Text_OhThatsSoDisappointing::
    .string "噢……\n"
    .string "那太失望了……$"

VermilionCity_House1_Text_HowAreTheFishBiting::
    .string "嘿，{PLAYER}！\p"
    .string "鱼儿是如何咬钩的？$"

VermilionCity_House1_Text_NoRoomForNiceGift::
    .string "噢，不！\p"
    .string "我有个好的礼物要送给你，\n"
    .string "可惜你的背包满了！$"

