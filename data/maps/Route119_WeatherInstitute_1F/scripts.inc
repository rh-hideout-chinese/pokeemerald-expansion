.set LOCALID_LITTLE_BOY, 5

Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  @ Both defeated
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
    .string "老大对这儿的调查\n很感兴趣，所以\l派我们来这里。\p你别来碍事！$"

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
    .string "毁灭了……\n被一个孩子毁灭了……$"

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
    .string "老大什么都知道，\p但我只是个小人物，\n又怎么能知道他的想法？$"

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
    .string "嗯？\n这儿怎么有个小孩子？$"

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
    .string "嗯？\n我输了？！$"

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
    .string "哦，不……\n输给个小鬼，我又得被唠叨了……\p我是不是该小睡一觉……$"

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
    .string "我睡觉的时候\n大家都上楼去了！$"

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
    .string "哇，你真强！\p真想成为和你一样的\n宝可梦训练家！$"

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
    .string "教授很喜欢下雨，\n这是事实。\p但如果雨一直不停，就会给人们\n带来麻烦，这也是事实。\p因此，教授在研究\n如何让雨造福于人。$"

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
    .string "我们在研究所二楼\n研究丰缘地区的\l天气变化情况，\p我们一直关注着一些\n最近出现的短暂的特例，\l比如干旱或大雨……$"

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
    .string "嗨！\n是你救了我们！\p我真的不明白海洋队\n究竟在找什么东西。$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
    .string "有张床……\n休息一下吧。$"

