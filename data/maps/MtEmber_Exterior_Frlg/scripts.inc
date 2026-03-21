MtEmber_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MtEmber_Exterior_OnLoad
	.byte 0

MtEmber_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_MT_EMBER_EXTERIOR
	call_if_eq VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 2, MtEmber_Exterior_EventScript_RocketsFaceDown
	end

MtEmber_Exterior_EventScript_RocketsFaceDown::
	setobjectmovementtype LOCALID_MT_EMBER_GRUNT1, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_MT_EMBER_GRUNT2, MOVEMENT_TYPE_FACE_DOWN
	return

MtEmber_Exterior_OnLoad::
	call_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_OpenCave
	end

MtEmber_Exterior_EventScript_OpenCave::
	setmetatile 42, 39, METATILE_MtEmber_CaveEntrance, 0
	return

MtEmber_Exterior_EventScript_Grunt1::
	lock
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_EventScript_Grunt1Defeated
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_BattleGrunt1
	msgbox MtEmber_Exterior_Text_WellTryDiggingHere
	release
	end

MtEmber_Exterior_EventScript_Grunt1Defeated::
	msgbox MtEmber_Exterior_Text_Grunt1PostBattle
	release
	end

MtEmber_Exterior_EventScript_BattleGrunt1::
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_FacePlayer
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	msgbox MtEmber_Exterior_Text_Grunt1Intro
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_Text_Grunt1Defeat
	msgbox MtEmber_Exterior_Text_Grunt1PostBattle
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_EventScript_DefeatedBothGrunts
	release
	end

MtEmber_Exterior_EventScript_DefeatedBothGrunts::
	msgbox MtEmber_Exterior_Text_WellRegroupDontStepInsideThere
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_EMBER_GRUNT1
	removeobject LOCALID_MT_EMBER_GRUNT2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtEmber_Exterior_EventScript_Grunt2::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_EventScript_DefeatedGrunt2
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_BattleGrunt2
	msgbox MtEmber_Exterior_Text_YoureInTheWayGetLost
	closemessage
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MtEmber_Exterior_EventScript_DefeatedGrunt2::
	msgbox MtEmber_Exterior_Text_Grunt2PostBattle
	release
	end

MtEmber_Exterior_EventScript_BattleGrunt2::
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	msgbox MtEmber_Exterior_Text_Grunt2Intro
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_Text_Grunt2Defeat
	msgbox MtEmber_Exterior_Text_Grunt2PostBattle
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_EventScript_DefeatedBothGrunts
	release
	end

MtEmber_Exterior_EventScript_RocketPasswordScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox MtEmber_Exterior_Text_PunchedThroughAtLast
	message MtEmber_Exterior_Text_WhatsPasswordAgain
	waitmessage
	playse SE_PIN
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_QuestionMark
	waitmovement 0
	waitbuttonpress
	msgbox MtEmber_Exterior_Text_FirstPasswordGoldeen
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	call MtEmber_Exterior_EventScript_RocketsFaceDown
	msgbox MtEmber_Exterior_Text_SnoopsBeenListeningIn
	setvar VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 2
	releaseall
	end

MtEmber_Exterior_EventScript_Logan::
	trainerbattle_single TRAINER_PKMN_RANGER_LOGAN, MtEmber_Exterior_Text_LoganIntro, MtEmber_Exterior_Text_LoganDefeat
	msgbox MtEmber_Exterior_Text_LoganPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmber_Exterior_EventScript_Beth::
	trainerbattle_single TRAINER_PKMN_RANGER_BETH, MtEmber_Exterior_Text_BethIntro, MtEmber_Exterior_Text_BethDefeat
	msgbox MtEmber_Exterior_Text_BethPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmber_Exterior_EventScript_Jocelyn::
	trainerbattle_single TRAINER_CRUSH_GIRL_JOCELYN, MtEmber_Exterior_Text_JocelynIntro, MtEmber_Exterior_Text_JocelynDefeat
	msgbox MtEmber_Exterior_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

Text_ExplosionTeach::
    .string "你能想象吗？\n"
    .string "如果这座火山喷发？\p"
    .string "随之而来的爆炸会要了\n"
    .string "我们的命。那该有多恐怖？\p"
    .string "趁我们还在害怕的时候\n"
    .string "你想让我教你大爆炸吗？$"

Text_ExplosionDeclined::
    .string "嗯，没错。\n"
    .string "这太可怕了。$"

Text_ExplosionWhichMon::
    .string "你真是勇敢！\p"
    .string "哪只宝可梦想要学会\n"
    .string "大爆炸？$"

Text_ExplosionTaught::
    .string "在这座火山上使用大爆炸……\p"
    .string "这真是让我毛骨悚然地兴奋！$"

MtEmber_Exterior_Text_WellTryDiggingHere::
    .string "在这里。\n"
    .string "我们会试着在这里挖掘。\p"
    .string "干部们谈论的宝藏应该就在这里。$"

MtEmber_Exterior_Text_YoureInTheWayGetLost::
    .string "搞什么呢……\n"
    .string "你挡道了。给我滚开。$"

MtEmber_Exterior_Text_PunchedThroughAtLast::
    .string "呼，总算打穿了。\n"
    .string "让我们去挖掘宝藏吧！$"

MtEmber_Exterior_Text_WhatsPasswordAgain::
    .string "我们发现的任何宝藏，\n"
    .string "都要拖回仓库的，明白吗？\p"
    .string "……哦，顺便密码是什么？\n"
    .string "我是说火箭队仓库的密码。$"

MtEmber_Exterior_Text_FirstPasswordGoldeen::
    .string "什么，你把密码忘了？\n"
    .string "实际上密码有两个。\p"
    .string "第一个是“多多少少\n"
    .string "少少多多。”\p"
    .string "第二个是……$"

MtEmber_Exterior_Text_SnoopsBeenListeningIn::
    .string "嘿！\n"
    .string "这家伙一直在偷听！$"

MtEmber_Exterior_Text_Grunt1Intro::
    .string "你一直在偷听我们说话，\n"
    .string "对吗？$"

MtEmber_Exterior_Text_Grunt1Defeat::
    .string "呃，什么？$"

MtEmber_Exterior_Text_Grunt1PostBattle::
    .string "为什么你一定要赢？$"

MtEmber_Exterior_Text_Grunt2Intro::
    .string "想要着偷走我们的宝藏？\n"
    .string "趁早放弃吧！$"

MtEmber_Exterior_Text_Grunt2Defeat::
    .string "等等！\n"
    .string "可是现在该怎么办？$"

MtEmber_Exterior_Text_Grunt2PostBattle::
    .string "健忘症能很方便地\n"
    .string "使你忘记你所听到的一切！$"

MtEmber_Exterior_Text_WellRegroupDontStepInsideThere::
    .string "好一次挫折啊……\n"
    .string "我们要重新组队。\p"
    .string "你！不要妄想从这儿往里走一步！\p"
    .string "如果你想知道做什么最好，\n"
    .string "那就放弃往里走的念头吧！$"

MtEmber_Exterior_Text_LoganIntro::
    .string "活火山是指正在喷发的，\n"
    .string "或将要喷发的火山。$"

MtEmber_Exterior_Text_LoganDefeat::
    .string "呜……太热了！\n"
    .string "汗山爆发啊！$"

MtEmber_Exterior_Text_LoganPostBattle::
    .string "有人说世界上有超过1500个活火山。\p"
    .string "只是想想就让我感到全身发热！$"

MtEmber_Exterior_Text_BethIntro::
    .string "你知道火山中的洞穴是如何形成的吗？$"

MtEmber_Exterior_Text_BethDefeat::
    .string "啊！\n"
    .string "你真是令人震惊的强大！$"

MtEmber_Exterior_Text_BethPostBattle::
    .string "当岩浆表面的熔岩变硬，\n"
    .string "其内部的岩浆流了出来，\l"
    .string "洞穴就形成了。$"

MtEmber_Exterior_Text_JocelynIntro::
    .string "我不断地锻炼来修补\n"
    .string "我破碎的心……\p"
    .string "那至少让我在身体上更坚韧！\n"
    .string "嗬呀！$"

MtEmber_Exterior_Text_JocelynDefeat::
    .string "我觉得我做太过了……$"

MtEmber_Exterior_Text_JocelynPostBattle::
    .string "你战斗的方式，\n"
    .string "使我想起了甩了我的家伙……$"

