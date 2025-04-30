Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
    .string "我哥哥是化石迷……\n他是喜欢化石的好人……\p他也喜欢挖洞……\n这个洞是他自己挖的……\p给你这个，你也可以挖洞\n就像我哥哥一样……$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
    .string "如果让你的宝可梦在山洞里挖洞\n你就会回到洞的入口……$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
    .string "不同形状的石头\n在这里展示……$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
    .string "地层的组成……\n雨后大陆的形状……石头，\l土壤，还有岩石是怎样的……\p这些全塞满了书。$"

