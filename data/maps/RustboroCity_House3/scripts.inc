RustboroCity_House3_MapScripts::
	.byte 0

RustboroCity_House3_EventScript_OldMan::
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman::
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames:
    .string "我给我的宝可梦起了\n最合适的名字！\p这是我，呃…\n创造力的表现！$"

RustboroCity_House3_Text_NamingPikachuPekachu:
    .string "但叫皮卡丘为\n猫卡球？这没什么意义。\p我想最好起个容易\n让人理解的名字，但是…$"

RustboroCity_House3_Text_Pekachu:
    .string "猫卡球：猫球！$"

