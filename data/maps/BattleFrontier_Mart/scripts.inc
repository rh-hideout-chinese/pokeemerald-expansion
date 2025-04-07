.set LOCALID_OLD_WOMAN, 2

BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
    .string "我们是来陪我们的\n孙子的。\p但既然来这儿了，我们\n觉得至少该带些纪念品回去。$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
    .string "亲爱的，你觉得这个怎么样？\n这应该是个不错的礼物吧？\p这是…攻击…之…源？\n听上去挺好吃的，不是吗？$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
    .string "对战开拓区里的\n比赛都不允许在战斗中\l使用物品，\p这条规定让原来就很困难的战斗\n难上加难！$"

