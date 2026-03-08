IndigoPlateau_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

IndigoPlateau_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU
	specialvar VAR_RESULT, IsNationalPokedexEnabled
	call_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor
	end

IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor::
	goto_if_set FLAG_IS_CHAMPION, Common_EventScript_NopReturn
	setobjectxyperm LOCALID_LEAGUE_DOOR_GUARD, 4, 2
	return

IndigoPlateau_PokemonCenter_1F_EventScript_DoorGuard::
	lock
	faceplayer
	specialvar VAR_RESULT, IsNationalPokedexEnabled
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete::
	goto_if_set FLAG_IS_CHAMPION, IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete
	msgbox IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete::
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_GymGuy::
	msgbox IndigoPlateau_PokemonCenter_1F_Text_GymGuyAdvice, MSGBOX_NPC
	end

IndigoPlateau_PokemonCenter_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart IndigoPlateau_PokemonCenter_1F_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
IndigoPlateau_PokemonCenter_1F_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

IndigoPlateau_PokemonCenter_1F_Text_GymGuyAdvice::
    .string "哟！\n"
    .string "未来的冠军\p"
    .string "在宝可梦联盟，\n"
    .string "你将会面临四天王的车轮战\p"
    .string "如果你输了，\n"
    .string "一切都得从头来！\p"
    .string "事实就是这样了！\n"
    .string "加油！$"

IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck::
    .string "从现在开始，你得接连不断的与\n"
    .string "四天王战斗。\p"
    .string "如果你赢了，通往下一位\n"
    .string "天王的门会为你打开，祝你好运！$"

IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing::
    .string "耽误了您过来的时间，\n"
    .string "我们感到很抱歉。\p"
    .string "如您所见，\n"
    .string "四天王中的科拿小姐有事出去了。\p"
    .string "所以，宝可梦联盟\n"
    .string "在她回来之前都无法开放。$"

IndigoPlateau_PokemonCenter_1F_Text_AgathaWhuppedUs::
    .string "菊子的幽灵属性宝可梦真的\n"
    .string "强大得恐怖。\p"
    .string "我曾经把我格斗属性的宝可梦\n"
    .string "训练到了一个极限。\p"
    .string "见到菊子之前我都感觉很轻松\n"
    .string "但是后来发生的事实是残酷的。\p"
    .string "那个老太太的脾气\n"
    .string "也不太好。\p"
    .string "我可没有说那个老太太\n"
    .string "什么坏话啊！$"

IndigoPlateau_PokemonCenter_1F_Text_LancesCousinGymLeaderFarAway::
    .string "也许四天王\n"
    .string "和其他人有点血缘关系。\p"
    .string "我曾经听说过，\n"
    .string "渡是一位离这里很远的\l"
    .string "道馆馆主的表哥。$"

