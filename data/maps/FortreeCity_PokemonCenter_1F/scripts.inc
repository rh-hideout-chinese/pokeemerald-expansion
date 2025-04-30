.set LOCALID_NURSE, 1

FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
    .string "孩子，我问你，你\n在收集宝可梦图鉴吗？\p唔……那么听我的，\n到狩猎地带去。$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
    .string "你去过\n联机中心吗？\p那里很方便，可以\n混合训练家的记录。\p我不知道它的原理如何，\n但它很棒，甚至令人吃惊！$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
    .string "哇，你有宝可导航！\n就和我的一样！\p你知道宝可导航的\n对战寻呼系统吗？\p用它能随时跟\n登记的训练家联系，\p同时也能显示出\n哪个训练家想跟你战斗。\p这太方便了！得文的人\n真的很优秀！$"

