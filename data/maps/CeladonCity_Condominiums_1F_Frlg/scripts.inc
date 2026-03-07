CeladonCity_Condominiums_1F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_1F_EventScript_TeaWoman::
	lock
	faceplayer
	goto_if_set FLAG_TALKED_TO_TEA_LADY_AFTER_HOF, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	goto_if_set FLAG_SYS_GAME_CLEAR, CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy
	goto_if_set FLAG_GOT_TEA, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	msgbox CeladonCity_Condominiums_1F_Text_TryThisDrinkInstead
	setflag FLAG_GOT_TEA
	giveitem ITEM_TEA
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox CeladonCity_Condominiums_1F_Text_NothingBeatsThirstLikeTea
	release
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea::
	msgbox CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany
	release
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy::
	famechecker FAMECHECKER_DAISY, 4
	setflag FLAG_TALKED_TO_TEA_LADY_AFTER_HOF
	msgbox CeladonCity_Condominiums_1F_Text_DaisyComesToBuyTea
	release
	end

CeladonCity_Condominiums_1F_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Meowth
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Clefairy
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Nidoran::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Nidoran
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_SuiteSign::
	msgbox CeladonCity_Condominiums_1F_Text_ManagersSuite, MSGBOX_SIGN
	end

CeladonCity_Condominiums_1F_Text_Meowth::
    .string "喵喵：喵！$"

CeladonCity_Condominiums_1F_Text_TryThisDrinkInstead::
    .string "你不该把钱都花在饮料上。\p"
    .string "试试这个。$"

CeladonCity_Condominiums_1F_Text_NothingBeatsThirstLikeTea::
    .string "没有什么能比热茶更解渴了。\p"
    .string "茶是最好的饮品。$"

CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany::
    .string "我亲爱的宝可梦一直陪伴着我。\n"
    .string "喵喵还会拾钱回来呢！$"

CeladonCity_Condominiums_1F_Text_DaisyComesToBuyTea::
    .string "你好哦，甜心。\n"
    .string "我的茶好喝吗？\p"
    .string "对了亲爱的。你是不是从\n"
    .string "真新镇来的吗？\p"
    .string "一个从真新镇来的小女孩，叫奈奈美，\n"
    .string "她每天都要喝茶。\p"
    .string "她经常去玉虹百货大楼买茶叶。$"

CeladonCity_Condominiums_1F_Text_Clefairy::
    .string "皮皮：皮 皮皮皮！$"

CeladonCity_Condominiums_1F_Text_Nidoran::
    .string "尼多兰：咔 咔呜！$"

CeladonCity_Condominiums_1F_Text_ManagersSuite::
    .string "玉虹大厦\n"
    .string "经理套间$"

