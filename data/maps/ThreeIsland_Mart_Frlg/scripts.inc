ThreeIsland_Mart_Frlg_MapScripts::
	.byte 0

ThreeIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart ThreeIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
ThreeIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

ThreeIsland_Mart_EventScript_Picnicker::
	msgbox ThreeIsland_Mart_Text_TrueThatCeldadonDeptStoreBigger, MSGBOX_NPC
	end

ThreeIsland_Mart_EventScript_BugCatcher::
	msgbox ThreeIsland_Mart_Text_PeopleHealWithBerriesFromForest, MSGBOX_NPC
	end

ThreeIsland_Mart_EventScript_Youngster::
	msgbox ThreeIsland_Mart_Text_BikersWereAboutToTrashMart, MSGBOX_NPC
	end

ThreeIsland_Mart_Text_TrueThatCeldadonDeptStoreBigger::
	.string "真的假的？\p"
	.string "玉虹百货大楼\n"
	.string "比这个商店大好几倍？！$"

ThreeIsland_Mart_Text_PeopleHealWithBerriesFromForest::
	.string "有时我在这儿买药。\p"
	.string "但有很多人用来自树果森林\n"
	.string "的树果治疗宝可梦。\p"
	.string "这是因为树果不要钱\n"
	.string "而且取之不尽，用之不竭！$"

ThreeIsland_Mart_Text_BikersWereAboutToTrashMart::
	.string "这些飙车族会弄脏\n"
	.string "这座宝可梦商店。\p"
	.string "要是他们能离开就好了！$"

