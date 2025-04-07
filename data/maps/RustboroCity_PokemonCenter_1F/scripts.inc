.set LOCALID_NURSE, 1

RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
    .string "我的宝可梦是天真性格，\n而我朋友的是开朗性格。\p宝可梦也有自己的性格，\n真有趣！$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
    .string "就像人类一样，\n宝可梦也有性别，\p但似乎没人知道\n它们的不同点在何处。$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
    .string "隔壁的人给了我一个\n秘传学习器！\p我用它教我的宝可梦\n怎样砍倒小树。$"

