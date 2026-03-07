CeladonCity_DepartmentStore_5F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_5F_EventScript_Gentleman::
	msgbox CeladonCity_DepartmentStore_5F_Text_ExplainStatEnhancers, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_5F_EventScript_Sailor::
	msgbox CeladonCity_DepartmentStore_5F_Text_HereForStatEnhancers, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_5F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_5F_Text_Drugstore, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_5F_EventScript_ClerkXItems::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_5F_XItems
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_5F_XItems::
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_5F_EventScript_ClerkVitamins::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_5F_Vitamins
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_5F_Vitamins::
	.2byte ITEM_HP_UP
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CALCIUM
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_5F_Text_ExplainStatEnhancers::
    .string "只有这里才能买到\n"
    .string "宝可梦能力增强剂。\p"
    .string "HP提升剂增加宝可梦的基础HP。\p"
    .string "特攻增强剂提升宝可梦的基础特攻。\p"
    .string "特防增强剂提升宝可梦的基础特防。\p"
    .string "速度增强剂提升宝可梦的基础速度。$"

CeladonCity_DepartmentStore_5F_Text_HereForStatEnhancers::
	.string "我是来这里\n"
	.string "买宝可梦能力增强剂的。\p"
	.string "攻击增强剂增加宝可梦的基础攻击。\p"
	.string "防御增强剂增加宝可梦的基础防御。$"

CeladonCity_DepartmentStore_5F_Text_Drugstore::
	.string "五楼：药店$"

