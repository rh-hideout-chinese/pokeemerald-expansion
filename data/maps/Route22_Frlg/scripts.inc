Route22_Frlg_MapScripts::
	.byte 0

Route22_EventScript_EarlyRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_ROUTE22_RIVAL
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_EarlyRivalApproach
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_EarlyRivalApproach
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_EarlyRivalApproachBottom
	delay 6
	msgbox Route22_Text_EarlyRivalIntro
	call_if_eq VAR_STARTER_MON, 2, Route22_EventScript_EarlyRivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, Route22_EventScript_EarlyRivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, Route22_EventScript_EarlyRivalCharmander
	msgbox Route22_Text_EarlyRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_EarlyRivalExit
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_EarlyRivalExit
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_EarlyRivalExitBottom
	fadedefaultbgm
	removeobject LOCALID_ROUTE22_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 2
	releaseall
	end

Route22_EventScript_EarlyRivalApproach::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproach
	waitmovement 0
	return

Route22_EventScript_EarlyRivalApproachBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproachBottom
	applymovement LOCALID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_EarlyRivalSquirtle::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalBulbasaur::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalCharmander::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalExit::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_EarlyRivalExit
	waitmovement 0
	return

Route22_EventScript_EarlyRivalExitBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_EarlyRivalExitBottom
	waitmovement 0
	return

Route22_Movement_UnusedRivalExit:: @ 8
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_EarlyRivalExit::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_EarlyRivalExitBottom::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_RivalApproach::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_RivalApproachBottom::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

Route22_Movement_PlayerFaceRival::
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_up
	step_end

Route22_EventScript_LateRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_ROUTE22_RIVAL
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_LateRivalApproach
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_LateRivalApproach
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_LateRivalApproachBottom
	msgbox Route22_Text_LateRivalIntro
	setvar VAR_LAST_TALKED, LOCALID_ROUTE22_RIVAL
	call_if_eq VAR_STARTER_MON, 2, Route22_EventScript_LateRivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, Route22_EventScript_LateRivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, Route22_EventScript_LateRivalCharmander
	msgbox Route22_Text_LateRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RG_RIVAL_EXIT, 0
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_LateRivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ROUTE22_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 4
	releaseall
	end

Route22_EventScript_LateRivalApproach::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproach
	waitmovement 0
	return

Route22_EventScript_LateRivalApproachBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproachBottom
	applymovement LOCALID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_LateRivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER, Route22_Text_LateRivalDefeat
	return

Route22_Movement_LateRivalExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route22_EventScript_LeagueGateSign::
	msgbox Route22_Text_LeagueGateSign, MSGBOX_SIGN
	end

Route22_Text_EarlyRivalIntro::
	.string "{RIVAL}：喂！{PLAYER}！\p"
	.string "你想要到宝可梦联盟里去？\n"
	.string "得了吧！\p"
	.string "你得到的徽章\n"
	.string "还不够吧？\p"
	.string "这样的话，\n"
	.string "守卫是不会让你通过的。\p"
	.string "顺便问一句，\n"
	.string "你的宝可梦变强了吗？$"

Route22_Text_EarlyRivalDefeat::
	.string "啊啊！\n"
	.string "你只是运气好罢了！$"

Route22_Text_EarlyRivalPostBattle::
	.string "我听说宝可梦联盟遍布\n"
	.string "很厉害的训练家。\p"
	.string "我必须想想该怎样\n"
	.string "战胜他们。\p"
	.string "你不能这样磨磨蹭蹭了，\n"
	.string "继续前进吧！$"

@ Translated in RB as "{RIVAL}: What? Why do I have 2 POKéMON? You should catch some more too!"
Route22_Text_RivalShouldCatchSomeMons::
	.string "{RIVAL}“なんだ？\n"
	.string "ポケモン　2ひきも\l"
	.string "もってるの　なぜか　だって？\p"
	.string "おまえも\n"
	.string "つかまえれば　いい　じゃん！$"

Route22_Text_LateRivalIntro::
	.string "{RIVAL}：什么？{PLAYER}！\n"
	.string "在这儿碰到你真是令我惊讶！\p"
	.string "你是打算去宝可梦联盟吗？\p"
	.string "你也收集齐了全部徽章？\n"
	.string "真是太好了！\p"
	.string "作为去宝可梦联盟之前的热身！\n"
	.string "我要先击败你，{PLAYER}\p"
	.string "来吧！$"

Route22_Text_LateRivalDefeat::
	.string "什么！？\p"
	.string "我太大意了！$"

Route22_Text_LateRivalPostBattle::
	.string "这下我放松多了。\n"
	.string "已经为宝可梦联盟做好了充分准备！\p"
	.string "{PLAYER}，你还得再练习练习。\p"
	.string "不过，你自己应该很清楚吧！\n"
	.string "我走了，回见！$"

@ Translated in RB as "{RIVAL}: Hahaha! {PLAYER}! That's your best? You're nowhere near as good as me, pal! Go train some more! You loser!"
Route22_Text_LateRivalVictory::
	.string "{RIVAL}“ひゃははッ　{PLAYER}ー！\n"
	.string "それで　がんばってるのかよ！\l"
	.string "おれの　さいのうに　くらべりゃ\l"
	.string "{PLAYER}は　まだまだ　だな！\p"
	.string "もっと　れんしゅう　こいよ！\n"
	.string "あははーッ！$"

Route22_Text_LeagueGateSign::
	.string "宝可梦联盟\n"
	.string "正门$"

