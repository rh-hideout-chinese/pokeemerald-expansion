LavenderTown_Mart_Frlg_MapScripts::
	.byte 0

LavenderTown_Mart_EventScript_BaldingMan::
	msgbox LavenderTown_Mart_Text_SearchingForStatRaiseItems, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Rocker::
	msgbox LavenderTown_Mart_Text_DidYouBuyRevives, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Youngster::
	msgbox LavenderTown_Mart_Text_TrainerDuosCanChallengeYou, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavenderTown_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
LavenderTown_Mart_Items::
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_NONE
	release
	end

LavenderTown_Mart_Text_SearchingForStatRaiseItems::
    .string "我正在寻找能提升宝可梦\n"
    .string "战斗力的物品。\p"
    .string "那些物品能在一场战斗中有效。\p"
    .string "力量强化 防御提升 速度强化 \n"
    .string "和特攻提升都是我在寻找的。\p"
    .string "你知道在哪儿能得到它们吗？$"

LavenderTown_Mart_Text_DidYouBuyRevives::
    .string "你要买一些活力碎片吗？\n"
    .string "这个能使濒死的宝可梦恢复！$"

LavenderTown_Mart_Text_TrainerDuosCanChallengeYou::
    .string "有时候，会有一对训练家\n"
    .string "同时拿出两只宝可梦\l"
    .string "来挑战你。\p"
    .string "如果你遇上了，你就要\n"
    .string "拿出两只宝可梦来战斗。$"

LavenderTown_Mart_Text_SoldNuggetFromMountainsFor5000::
	.string "この　あいだ　やまおくで\n"
	.string "きんのたまを　ひろい　ましてね！\p"
	.string "つかえない　しなもの　ですが\n"
	.string "うったら　なんと　5000¥でした$"
