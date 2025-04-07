.set LOCALID_NURSE, 1

SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
    .string "想要我指点一下怎么战斗吗？\p你应该用较平衡的方式\n培养多种宝可梦。\p仅仅培养一只强大的\n宝可梦并不够，\p如果它的类型被克制，\n战斗会处于相当被动的局面。$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
    .string "我和朋友交换宝可梦。\p如果交换来的宝可梦带有物品，\n我会更加兴奋的！$"

