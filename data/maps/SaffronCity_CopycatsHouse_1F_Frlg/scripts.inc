SaffronCity_CopycatsHouse_1F_Frlg_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_1F_EventScript_CopycatsMom::
	msgbox SaffronCity_CopycatsHouse_1F_Text_DaughterIsSelfCentered, MSGBOX_NPC
	end

SaffronCity_CopycatsHouse_1F_EventScript_CopycatsDad::
	msgbox SaffronCity_CopycatsHouse_1F_Text_DaughterLikesToMimicPeople, MSGBOX_NPC
	end

SaffronCity_CopycatsHouse_1F_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_1F_Text_Chansey
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_1F_Text_DaughterIsSelfCentered::
    .string "我女儿总是以自己为中心。\n"
    .string "所以她几乎没有什么朋友。$"

SaffronCity_CopycatsHouse_1F_Text_DaughterLikesToMimicPeople::
    .string "我的女儿喜欢模仿其他人\n"
    .string "这确实有点令人恼火。\p"
    .string "这种模仿他人的行为使她在附近\n"
    .string "赢得了模仿少女的外号。$"

SaffronCity_CopycatsHouse_1F_Text_Chansey::
    .string "吉利蛋：琴！茜！$"

