CeruleanCity_House2_Frlg_MapScripts::
	.byte 0

CeruleanCity_House2_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, CeruleanCity_House2_EventScript_HikerGotTM28
	msgbox CeruleanCity_House2_Text_RocketsStoleTMForDig
	release
	end

CeruleanCity_House2_EventScript_HikerGotTM28::
	msgbox CeruleanCity_House2_Text_TeachDiglettDigWithoutTM
	release
	end

CeruleanCity_House2_EventScript_Lass::
	msgbox CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_WallHole::
	msgbox CeruleanCity_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end

CeruleanCity_House2_Text_RocketsStoleTMForDig::
    .string "那些卑鄙的火箭队！\p"
    .string "看看他们在我家里都干了些什么！\p"
    .string "他们偷了一个技能去教\n"
    .string "宝可梦如何挖地洞洞！\p"
    .string "我是打算把它用在\n"
    .string "猴怪或者穿山鼠上的……\p"
    .string "它花了我好多钱呢！$"

CeruleanCity_House2_Text_TeachDiglettDigWithoutTM::
    .string "我想丢的东西就丢了吧。\p"
    .string "我打算让地鼠不通过技能\n"
    .string "学会挖地洞。$"

CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood::
    .string "火箭队一定想挖地洞\n"
    .string "来做见不得人的事。$"

CeruleanCity_House2_Text_TeamRocketLeftWayOut::
    .string "火箭队逃跑时留下了个洞！$"

