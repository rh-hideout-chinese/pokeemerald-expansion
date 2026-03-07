CeladonCity_DepartmentStore_2F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_2F_EventScript_UnusedNPC::
	msgbox CeladonCity_DepartmentStore_2F_Text_SuperRepelMorePowerfulRepel, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_2F_EventScript_Lass::
	msgbox CeladonCity_DepartmentStore_2F_Text_BuyReviveForLongOutings, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_2F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_2F_Text_FloorSign, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_2F_EventScript_ClerkItems::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_2F_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_2F_Items::
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_2F_EventScript_ClerkTMs::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_2F_TMs
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_2F_TMs::
	.2byte ITEM_TM05
	.2byte ITEM_TM15
	.2byte ITEM_TM28
	.2byte ITEM_TM31
	.2byte ITEM_TM43
	.2byte ITEM_TM45
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_2F_Text_SuperRepelMorePowerfulRepel::
	.string "白银喷雾可以防止\n"
	.string "弱小的宝可梦靠近你……\p"
	.string "嗯，它是种效果更好的除虫喷雾。$"

CeladonCity_DepartmentStore_2F_Text_BuyReviveForLongOutings::
	.string "长途旅行的话，\n"
	.string "你该买些活力碎片带着。$"

CeladonCity_DepartmentStore_2F_Text_FloorSign::
	.string "为训练家准备的顶级物品！\p"
	.string "二楼：训练家商店$"

CeladonCity_DepartmentStore_2F_Text_LanceComesToBuyCapes::
	.string "我们有个偶尔会来光顾的客人，\n"
	.string "就是渡。\p"
	.string "他总是来买披风。\p"
	.string "我很想知道……他家里是不是有很多\n"
	.string "一模一样的披风？$"
