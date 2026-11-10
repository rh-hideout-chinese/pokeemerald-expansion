Route119_WeatherInstitute_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_2F_OnTransition
	.byte 0

Route119_WeatherInstitute_2F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 1, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone
	call_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear
	end

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 1, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 4, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 2, 2
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_UP
	return

Route119_WeatherInstitute_2F_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_5, Route119_WeatherInstitute_2F_Text_Grunt5Intro, Route119_WeatherInstitute_2F_Text_Grunt5Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_2, Route119_WeatherInstitute_2F_Text_Grunt2Intro, Route119_WeatherInstitute_2F_Text_Grunt2Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_3, Route119_WeatherInstitute_2F_Text_Grunt3Intro, Route119_WeatherInstitute_2F_Text_Grunt3Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_WEATHER_INSTITUTE, Route119_WeatherInstitute_2F_Text_ShellyIntro, Route119_WeatherInstitute_2F_Text_ShellyDefeat, Route119_WeatherInstitute_2F_EventScript_ShellyDefeated
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_ShellyDefeated::
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3, Route119_WeatherInstitute_2F_Movement_GruntApproachShelly
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_Delay48
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre, MSGBOX_DEFAULT
	closemessage
	setvar VAR_WEATHER_INSTITUTE_STATE, 1
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_1
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_2
	removeobject LOCALID_WEATHER_INSTITUTE_2F_SHELLY
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_4
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition
	waitmovement 0
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastform::
	msgbox Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CASTFORM_NORMAL
	givemon SPECIES_CASTFORM_NORMAL, 25, ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	end

Route119_WeatherInstitute_2F_EventScript_SendCastformToPC::
	call Common_EventScript_TransferredToPC
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_CASTFORM_NORMAL
	return

Route119_WeatherInstitute_2F_EventScript_ExplainCastform::
	msgbox Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_CASTFORM
	release
	end

Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather::
	goto_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather
	msgbox Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather::
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather  @ Both defeated
	call_if_unset FLAG_TEMP_2, Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather
	specialvar VAR_RESULT, GetAbnormalWeatherMapNameAndType
	goto_if_eq VAR_RESULT, 1, Route119_WeatherInstitute_2F_EventScript_KyogreWeather
	msgbox Route119_WeatherInstitute_2F_Text_GroudonWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_KyogreWeather::
	msgbox Route119_WeatherInstitute_2F_Text_KyogreWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather::
	special CreateAbnormalWeatherEvent
	setflag FLAG_TEMP_2
	return

Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather::
	msgbox Route119_WeatherInstitute_2F_Text_NoAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_Movement_GruntApproachShelly:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	ride_water_current_up
	walk_in_place_faster_down
	step_end

Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition:
	slide_down
	walk_in_place_faster_left
	step_end

Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer:
	walk_right
	walk_right
	walk_right
	step_end

Route119_WeatherInstitute_2F_EventScript_WeatherScientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CASTFORM, Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_Text_Grunt2Intro:
    .string "研究所制造出了一种\n与天气有关的宝可梦，\l我们要来带走它们！$"

Route119_WeatherInstitute_2F_Text_Grunt2Defeat:
    .string "难道我们的计划被一个孩子打破了？$"

Route119_WeatherInstitute_2F_Text_Grunt2PostBattle:
    .string "如果这里制造出的宝可梦\n真能自由控制天气，\l那我们海洋队肯定需要它！$"

Route119_WeatherInstitute_2F_Text_Grunt3Intro:
    .string "我们是海洋队！\n哪里有稀有的东西，\l哪里就有我们！$"

Route119_WeatherInstitute_2F_Text_Grunt3Defeat:
    .string "我认输！$"

Route119_WeatherInstitute_2F_Text_Grunt3PostBattle:
    .string "你根本不了解我们\n海洋队的理想！\l少来碍事！$"

Route119_WeatherInstitute_2F_Text_Grunt5Intro:
    .string "别告诉我你也想\n要那只天气宝可梦，\p想都别想！\n是我们先盯上的！$"

Route119_WeatherInstitute_2F_Text_Grunt5Defeat:
    .string "唉……看看我的宝可梦？$"

Route119_WeatherInstitute_2F_Text_Grunt5PostBattle:
    .string "哼，那又怎么样？\n我们想要的……\p我们真正想要的并不在这里……\n咿嘻嘻嘻嘻……$"

Route119_WeatherInstitute_2F_Text_ShellyIntro:
    .string "啊哈哈哈哈！\p竟敢插手我们\n海洋队的行动吗？\p你是无畏，还是无知，\n或是两者兼有呢？\p太可爱了，太可恶了！\n我这就打倒你，小家伙！$"

Route119_WeatherInstitute_2F_Text_ShellyDefeat:
    .string "啊哈哈哈哈！\n你强得让人反胃！$"

Route119_WeatherInstitute_2F_Text_ShellyPostBattle:
    .string "有熔岩队在周围瞎捣乱就够烦了，\n现在又多了个你！\p你到底为什么非要\n追着我们不放？$"

Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy:
    .string "紧急情况！\p有一批熔岩队的家伙刚刚\n经过天气研究所，\p他们好像是朝着\n送神山去了！$"

Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre:
    .string "什么？！\p我们不能再在这里浪费时间了！\n我们也得赶紧去送神山了！\p啊哈哈哈哈！\n熔岩队，你们给我等着！$"

Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon:
    .string "谢谢！\n多亏你救了我们！\p也许作为谢礼有点特别，\n不过，收下这只宝可梦吧。$"

@ Unused
Route119_WeatherInstitute_2F_Text_NoRoomForPokemon:
    .string "嗯？你没有放下这只\n宝可梦的空间。$"

Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform:
    .string "{PLAYER}得到了飘浮泡泡！$"

Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather:
    .string "这种宝可梦能根据\n天气状况改变形态。\p研究所里面还有不少，\n这只就给你了。$"

Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous:
    .string "我研究降雨数十年，\n但如果说想要随心操控天气，\n简直荒谬至极！$"

Route119_WeatherInstitute_2F_Text_GroudonWeather:
    .string "我在追踪监测丰缘地区的\n气候状况，\p最近，我们发现{STR_VAR_1}地区\n持续异常干旱，\p难道说，\n在{STR_VAR_1}附近……$"

Route119_WeatherInstitute_2F_Text_KyogreWeather:
    .string "我在追踪监测丰缘地区的\n气候状况，\p最近，我们发现{STR_VAR_1}地区\n正遭遇特大暴雨，\p难道说，\n在{STR_VAR_1}附近……$"

Route119_WeatherInstitute_2F_Text_NoAbnormalWeather:
    .string "最近没再收到异常的\n气候报告了。\p偶然下一场雨才算是\n自然的恩惠吧。$"

