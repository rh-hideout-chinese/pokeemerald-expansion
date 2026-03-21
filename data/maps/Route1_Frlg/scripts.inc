Route1_Frlg_MapScripts::
	.byte 0

Route1_EventScript_MartClerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POTION_ON_ROUTE_1, Route1_EventScript_AlreadyGotPotion
	msgbox Route1_Text_WorkAtPokeMartTakeSample
	textcolor NPC_TEXT_COLOR_NEUTRAL
	checkitemspace ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	bufferitemname STR_VAR_2, ITEM_POTION
	playfanfare MUS_LEVEL_UP
	message gText_ObtainedTheItem
	waitmessage
	waitfanfare
	additem ITEM_POTION
	msgbox Route1_Text_PutPotionAway
	call EventScript_RestorePrevTextColor
	setflag FLAG_GOT_POTION_ON_ROUTE_1
	release
	end

Route1_EventScript_AlreadyGotPotion::
	msgbox Route1_Text_ComeSeeUsIfYouNeedPokeBalls
	release
	end

Route1_EventScript_Boy::
	msgbox Route1_Text_CanJumpFromLedges, MSGBOX_NPC
	end

Route1_EventScript_RouteSign::
	msgbox Route1_Text_RouteSign, MSGBOX_SIGN
	end

Route1_Text_WorkAtPokeMartTakeSample::
    .string "嗨！\n"
    .string "我是一家宝可梦商店的职员。\p"
    .string "宝可梦商店是可以很方便\n"
    .string "的买到各种商品的连锁店。\p"
    .string "有空请去常青市的宝可梦商店看看。\p"
    .string "我知道，我会送你个样品。\n"
    .string "给你！$"

Route1_Text_ComeSeeUsIfYouNeedPokeBalls::
    .string "如果你想要精灵球收服宝可梦的话，\n"
    .string "就来我们这儿看看吧。$"

Route1_Text_PutPotionAway::
    .string "{PLAYER}把伤药放进了\n"
    .string "背包的道具口袋里。$"

Route1_Text_CanJumpFromLedges::
    .string "看到路边那些突起的岩石吗？\p"
    .string "虽然有点吓人，\n"
    .string "但是你可以直接从那里跳下去。\p"
    .string "走那条路的话。\n"
    .string "你可以更快的回到真新镇。$"

Route1_Text_RouteSign::
    .string "1号道路\n"
    .string "真新镇-常青市$"

