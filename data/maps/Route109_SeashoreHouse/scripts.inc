Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hidemoneybox
	giveitem ITEM_SODA_POP
.else
	giveitem ITEM_SODA_POP
	hidemoneybox
.endif
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
    .string "我是大海之家的老板，\n你可以叫我大海先生！\p我最为喜欢的事情\n是观看激烈的宝可梦战斗。\p给我看看你的激情吧！\p如果你能打败这里的所有训练家，\n我这里有奖励送给你。$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
    .string "让我看看激烈的战斗吧！\p我开这大海之家的\n目的就在于此！$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
    .string "火热的战斗把人\n都要烧焦了！\l我已经无法描述我的兴奋了！\p这些送给你，当作是我\n对你的热情的谢礼，\p总共六瓶劲爽汽水！$"

Route109_SeashoreHouse_Text_BagFull:
    .string "哎，但是你的包包已经满了，\n我会暂时替你保管的。$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
    .string "想买劲爽汽水吗？\n宝可梦都很喜欢它！\p只卖¥300一瓶！\n来买吧！$"

Route109_SeashoreHouse_Text_HereYouGo:
    .string "给！$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
    .string "钱不够。$"

Route109_SeashoreHouse_Text_ThatsTooBad:
    .string "不买吗？\n真遗憾。$"

Route109_SeashoreHouse_Text_DwayneIntro:
    .string "伙计，知道吗，在大海之家的\n训练家之中，没有人比我\l更充满激情了！$"

Route109_SeashoreHouse_Text_DwayneDefeated:
    .string "火热的战斗！\n我心服口服了，伙计！$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
    .string "在凯那市就是要享受\n火热的战斗和冰爽的劲爽汽水！$"

Route109_SeashoreHouse_Text_JohannaIntro:
    .string "无聊的战斗不值得为之付出努力。\p只有火一般的战斗才能使\n训练家和宝可梦成长起来！$"

Route109_SeashoreHouse_Text_JohannaDefeated:
    .string "好热！$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
    .string "呼，我渴了。\n去喝点劲爽汽水吧。$"

Route109_SeashoreHouse_Text_SimonIntro:
    .string "让你见识一下我的\n宝可梦的厉害。不要哭鼻子！$"

Route109_SeashoreHouse_Text_SimonDefeated:
    .string "……输了，但我不会哭的……$"

Route109_SeashoreHouse_Text_SimonPostBattle:
    .string "如果我的宝可梦会那样\n背着我过海的招式，\l我就可以摆脱这个泳圈了。$"

