PewterCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PewterCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_PEWTER_CITY
	end

PewterCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

PewterCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox PewterCity_PokemonCenter_1F_Text_TeamRocketMtMoonImOnPhone, MSGBOX_NPC
	end

PewterCity_PokemonCenter_1F_EventScript_Jigglypuff::
	lock
	faceplayer
	fadeoutbgm 0
	playbgm MUS_RG_JIGGLYPUFF, 0
	message PewterCity_PokemonCenter_1F_Text_Jigglypuff
	waitmessage
	delay 455
	playbgm MUS_POKE_CENTER, 1
	release
	end

PewterCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PewterCity_PokemonCenter_1F_Text_WhenJiggylypuffSingsMonsGetDrowsy, MSGBOX_NPC
	end

PewterCity_PokemonCenter_1F_EventScript_GBAKid1::
	lock
	msgbox PewterCity_PokemonCenter_1F_Text_TradingMyClefairyForPikachu
	release
	end

PewterCity_PokemonCenter_1F_EventScript_GBAKid2::
	msgbox PewterCity_PokemonCenter_1F_Text_TradingPikachuWithKid, MSGBOX_NPC
	end

PewterCity_PokemonCenter_1F_Text_TeamRocketMtMoonImOnPhone::
    .string "什么！？\p"
    .string "火箭队在月见山？\n"
    .string "是么？\p"
    .string "我在打电话！\n"
    .string "要走了！$"

PewterCity_PokemonCenter_1F_Text_Jigglypuff::
    .string "胖丁：噗噗！$"

PewterCity_PokemonCenter_1F_Text_WhenJiggylypuffSingsMonsGetDrowsy::
    .string "呵欠！\p"
    .string "当胖丁唱歌时，\n"
    .string "宝可梦会昏睡……\p"
    .string "……我也会……\n"
    .string "呼噜……$"

PewterCity_PokemonCenter_1F_Text_TradingMyClefairyForPikachu::
    .string "我真的想要一只皮卡丘，\n"
    .string "所以我用我的皮皮交换了一只。$"

PewterCity_PokemonCenter_1F_Text_TradingPikachuWithKid::
    .string "我和那边的小孩交换了宝可梦。\p"
    .string "我有两只皮卡丘，所以我\n"
    .string "寻思着可以交换一只。$"

