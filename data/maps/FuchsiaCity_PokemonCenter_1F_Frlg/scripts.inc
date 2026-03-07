FuchsiaCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FuchsiaCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_FUCHSIA_CITY
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Man::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_CantBecomeGoodTrainerWithOneMon, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_EventScript_CooltrainerF::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_PokemonLeagueWestOfViridian, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_VisitSafariZoneForPokedex, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_Text_CantBecomeGoodTrainerWithOneMon::
    .string "只训练厉害的宝可梦\n"
    .string "你永远成为不了强大的训练家\p"
    .string "但是训练许多宝可梦\n"
    .string "也不是一件轻松的事。$"

FuchsiaCity_PokemonCenter_1F_Text_PokemonLeagueWestOfViridian::
    .string "常青市西边\n"
    .string "有一条小道，\p"
    .string "通向宝可梦联盟总部。\n"
    .string "总部统管所有的训练家。$"

FuchsiaCity_PokemonCenter_1F_Text_VisitSafariZoneForPokedex::
    .string "如果你在制作宝可梦图鉴，\n"
    .string "去野生原野区看看吧。\p"
    .string "所有稀有的宝可梦\n"
    .string "都被饲养在那里。$"

