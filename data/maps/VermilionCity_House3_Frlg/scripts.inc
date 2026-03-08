VermilionCity_House3_Frlg_MapScripts::
	.byte 0

VermilionCity_House3_EventScript_Boy::
	msgbox VermilionCity_House3_Text_PidgeyFlyLetterToSaffron, MSGBOX_NPC
	end

VermilionCity_House3_EventScript_Lass::
	msgbox VermilionCity_House3_Text_SendMyPidgeyToUnionRoom, MSGBOX_NPC
	end

VermilionCity_House3_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox VermilionCity_House3_Text_Pidgey
	waitmoncry
	release
	end

VermilionCity_House3_EventScript_Letter::
	msgbox VermilionCity_House3_Text_DearPippiLetter, MSGBOX_SIGN
	end

VermilionCity_House3_Text_PidgeyFlyLetterToSaffron::
    .string "我正让我的波波飞去北边的金黄\n"
    .string "送一封信。$"

VermilionCity_House3_Text_Pidgey::
    .string "波波：咕噜咕！$"

VermilionCity_House3_Text_DearPippiLetter::
    .string "亲爱的比比，\n"
    .string "希望能很快见到你。\p"
    .string "我听说火箭队在金黄制造麻烦。\p"
    .string "枯叶似乎还安全。$"

VermilionCity_House3_Text_SendMyPidgeyToUnionRoom::
    .string "我想和各种各样的人通信。\p"
    .string "我常把波波派去联合房间\n"
    .string "替我传递信件。$"

