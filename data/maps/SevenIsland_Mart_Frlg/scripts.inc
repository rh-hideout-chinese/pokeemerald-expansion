SevenIsland_Mart_Frlg_MapScripts::
	.byte 0

SevenIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SevenIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
SevenIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

SevenIsland_Mart_EventScript_Lass::
	msgbox SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Hiker::
	msgbox SevenIsland_Mart_Text_PreparationsCompleteForRuins, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Fisher::
	msgbox SevenIsland_Mart_Text_NeedToFishOnSevenIsland, MSGBOX_NPC
	end

SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn::
    .string "宝可梦有他们自己独特的\n"
    .string "个性，就像人类一样。\p"
    .string "我的皮卡丘有着急躁的性格，\n"
    .string "所以它会成长成速度型的宝可梦。$"

SevenIsland_Mart_Text_PreparationsCompleteForRuins::
    .string "好了，我已经做好\n"
    .string "充足的准备去探索遗迹了。$"

SevenIsland_Mart_Text_NeedToFishOnSevenIsland::
    .string "我会去七之岛钓鱼。\p"
    .string "这样的话我的七岛钓鱼\n"
    .string "之旅就结束了。\p"
    .string "不过，我要先买一些\n"
    .string "精灵球以备不时之需。$"

