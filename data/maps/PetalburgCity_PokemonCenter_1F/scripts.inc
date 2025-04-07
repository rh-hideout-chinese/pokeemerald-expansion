.set LOCALID_NURSE, 1

PetalburgCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

PetalburgCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan::
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo::
	call_if_eq VAR_STARTER_MON, 0, PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType
	call_if_eq VAR_STARTER_MON, 1, PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType
	call_if_eq VAR_STARTER_MON, 2, PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem:
    .string "电脑上的\n宝可梦存储系统…\p无论是谁发明的，\n那人一定是个科学狂人！$"

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP:
    .string "我的宝可梦吃了蓝橘果后，\n它的HP就恢复了！$"

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon:
    .string "宝可梦分为很多属性，\p每种属性对其他属性\n都有不同的优势和弱点。\p由于宝可梦属性的不同，\n战斗可能会变得很容易或变得更加棘手。$"

PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType:
    .string "比如，你的木守宫\n是草系。\p它对水系和地上系时\n占有优势，\p但对炎系宝可梦时\n则处于劣势。$"

PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType:
    .string "比如，你的火稚鸡\n是炎系。\p它对草系和虫系时\n占有优势，\p但对水系宝可梦时\n则处于劣势。$"

PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType:
    .string "比如，你的水跃鱼\n是水系。\p它对炎系时占有优势，\p但对草系和电系宝可梦时\n则处于劣势。$"

