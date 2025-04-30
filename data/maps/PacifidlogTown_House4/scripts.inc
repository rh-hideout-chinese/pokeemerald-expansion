PacifidlogTown_House4_MapScripts::
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl::
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman::
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogTown_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes::
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No::
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon:
    .string "有人说看到一只宝可梦\n从丰缘地区上空飞过。\p它总是在天空中飞吗？\n它不用休息吗？$"

PacifidlogTown_House4_Text_SkyPokemon:
    .string "空中的宝可梦！\n空中的宝可梦！$"

PacifidlogTown_House4_Text_WhereDidYouComeFrom:
    .string "什么？你来自叫”是”的小镇？$"

PacifidlogTown_House4_Text_YesTown:
    .string "什么？\n噎死镇？\p我从没听说过那种地方。$"

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere:
    .string "什么？我可不信，\n你肯定是从什么地方来的。\p哎！等等！你不会说\n你是生在海底的吧？$"

