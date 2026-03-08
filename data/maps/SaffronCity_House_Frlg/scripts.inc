SaffronCity_House_Frlg_MapScripts::
	.byte 0

SaffronCity_House_EventScript_Lass::
	msgbox SaffronCity_House_Text_DontLookAtMyLetter, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Youngster::
	msgbox SaffronCity_House_Text_GettingCopycatPokeDoll, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox SaffronCity_House_Text_Pidgey
	waitmoncry
	release
	end

SaffronCity_House_EventScript_Letter::
	msgbox SaffronCity_House_Text_ExplainPPUp, MSGBOX_SIGN
	end

SaffronCity_House_Text_DontLookAtMyLetter::
    .string "……感谢你的来信。\n"
    .string "希望能很快再次见面！\p"
    .string "……嘿！\n"
    .string "别看我的信！$"

SaffronCity_House_Text_Pidgey::
    .string "波波：库鲁库！$"

SaffronCity_House_Text_GettingCopycatPokeDoll::
    .string "模仿少女很可爱！\n"
    .string "我给了她一个皮皮玩偶。$"

SaffronCity_House_Text_ExplainPPUp::
    .string "我得到了作为礼物的PP提升剂。\p"
    .string "它是用来增加宝可梦技能\n"
    .string "的PP上限的。\p"
    .string "应该把它用在PP很少但\n"
    .string "威力很大的技能上。$"

