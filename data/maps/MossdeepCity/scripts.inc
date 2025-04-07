.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
    .string "我从大吾那儿得到的这东西，\n但我不知道它有什么用。\p我想它叫做王者之证，\n你想要吗？$"

MossdeepCity_Text_YouCanKeepIt:
    .string "你想要它？为什么？\n你真奇怪。\p拿着吧，\n但千万对大吾保密。$"

MossdeepCity_Text_StevensHouseOverThere:
    .string "大吾的家就在那儿！$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
    .string "是么，你也这么想啊！\n拿着这种奇怪的石头有什么用吗？$"

MossdeepCity_Text_WailmerWatching:
    .string "在绿岭市周围可以看到\n野生吼吼鲸。\p这叫啥来着，呃…\n是那啥…\p皮，皮，皮…\p观赏吼吼鲸！$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
    .string "岛上的宇宙中心曾经\n发射过巨大的火箭。\p最近他们收到了一封信，\n引起了大骚动。$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
    .string "岛上的宇宙中心曾经\n发射过巨大的火箭。$"

MossdeepCity_Text_MossdeepTargetedByMagma:
    .string "我听一个海员说\n水舰队在水静市惹了些麻烦，\p但后来有人到那儿，\n把他们都驱逐了出去！\p可现在绿岭市被\n火岩队盯上了。\p你想要知道他们的目的的话，\n就去宇宙中心看看吧。$"

MossdeepCity_Text_FeelReliefOnLand:
    .string "我是个水手，\n大海对我来说应该更重要。\p但你知道么？在每次长途航行后\n回到陆地上时，我都会觉得松了口气！$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
    .string "如果整个世界都像这个小岛\n一样被红花绿草所覆盖，\p那不是很好吗？$"

MossdeepCity_Text_LifeNeedsSeaToLive:
    .string "所有的生命都要依靠大海才能生存，\n即使是生活在陆地上的生命也一样。\p当一个生命走完了它的旅程，\n它又变成泥土回归大地。\p而大地总是和海洋\n紧密相连的。\p没错，就像这里的海岸线一样。$"

MossdeepCity_Text_SurfExhilarating:
    .string "虽然乘船航行还算不错，\p但乘着宝可梦\n渡海的话…\p那简直是太美妙了！\n你不这么想吗，年轻人？$"

MossdeepCity_Text_SpecialSpaceCenterRock:
    .string "这块石头对宇宙中心的人来说\n意义非凡，\p他们把它放在这里，\n祈祷火箭能安全上天。\p你许愿的时候会怎么做？\n你会向流星许愿吗？\p我会把愿望写在纸签上，\n祈祷它能实现。$"

MossdeepCity_Text_ItsAWhiteRock:
    .string "这是一块白色石头。$"

MossdeepCity_Text_GymSign:
    .string "绿岭市宝可梦道馆\n馆主：枫和南\p“神秘的组合！”$"

MossdeepCity_Text_CitySign:
    .string "绿岭市\n“我们的口号是：珍爱宝可梦！”$"

MossdeepCity_Text_SpaceCenterSign:
    .string "绿岭市宇宙中心\n“最接近宇宙的地方。”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
    .string "亚希达：{PLAYER}{KUN}，还好吗？\n我这儿很顺利！\p我听说绿岭市的道馆馆主\n实力很强，所以我打算\l来这调查一下。\p但这镇子上好像\n出了什么事，\p人们都在谈论宇宙中心\n和一封警告信…\p不过，我认为那与我\n一毛钱的关系也没有。$"

MossdeepCity_Text_SootopolisNewGymLeader:
    .string "啊…海浪冲刷在脚上的感觉\n真好…\p说到海浪，你知道\n那个海岛城市琉璃市吗？\p那儿的道馆来了个\n新馆主，\p据说他\n曾教导过米可利。$"

