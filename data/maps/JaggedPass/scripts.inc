.set LOCALID_HIDEOUT_GUARD, 5

JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
    .string "烟囱山的崎岖山路…\p这正是我在每一座山中\n所渴望寻找到的东西。\p这崎岖不平的路面…\n震动着我的灵魂！$"

JaggedPass_Text_EricDefeat:
    .string "失败让我痛苦！$"

JaggedPass_Text_EricPostBattle:
    .string "确实，在宝可梦的对战中我失败了…\p但说到对山的热爱\n我绝对不会输给你！$"

JaggedPass_Text_DianaIntro:
    .string "这可不是可以随便来闲逛的地方，\n这里并不适合野餐。$"

JaggedPass_Text_DianaDefeat:
    .string "哦哦哦，不！\n地面实在太颠簸了…$"

JaggedPass_Text_DianaPostBattle:
    .string "知道吗？\p有些人能够轻松地驾着自行车\n在这可怕的路面上行驶呢。$"

JaggedPass_Text_DianaRegister:
    .string "你还会回这儿来吗？\n回来的话，希望能和你再比试一次。$"

JaggedPass_Text_DianaRematchIntro:
    .string "不管在哪里，野餐都是愉快的。\n宝可梦也一样！$"

JaggedPass_Text_DianaRematchDefeat:
    .string "我只是因为地面太颠簸\n才输的！$"

JaggedPass_Text_DianaPostRematch:
    .string "我会忘记这次失败，享受\n在这崎岖的山中远足的乐趣。$"

JaggedPass_Text_EthanIntro:
    .string "崎岖山路很难走，\n这是个训练的好地方。$"

JaggedPass_Text_EthanDefeat:
    .string "在我们还在寻找一个合适立足点\n的时候，一切就结束了…$"

JaggedPass_Text_EthanPostBattle:
    .string "如果有飞跃自行车的话，\n我就能跳过断坡了。$"

JaggedPass_Text_EthanRegister:
    .string "等我习惯了这崎岖的路面，\n就一定能赢！\p能把我登记进你的口袋领航员吗？$"

JaggedPass_Text_EthanRematchIntro:
    .string "我已经习惯这里崎岖的路，\n能一边唱歌一边攀登了。$"

JaggedPass_Text_EthanRematchDefeat:
    .string "在这么高低不平的地面上战斗\n还是不容易啊…$"

JaggedPass_Text_EthanPostRematch:
    .string "我真该先去紫堇市的风野那儿\n弄台飞跃自行车…$"

JaggedPass_Text_GruntIntro:
    .string "哇啊！\n你在这做什么？\p我在这儿干什么事？\p跟你有什么关系？$"

JaggedPass_Text_GruntDefeat:
    .string "唔咕咕…\p我应该早点躲进\n基地里面的…$"

JaggedPass_Text_GoWhereverYouWant:
    .string "好吧好吧！\n我承认--你很强！\p别管我在干什么，\n赶紧去你想去的地方吧！$"

JaggedPass_Text_BoulderShakingInResponseToEmblem:
    .string "喔！这块大石头对火岩徽章\n有反应！石头晃动起来了！$"

JaggedPass_Text_JulioIntro:
    .string "哎呀！一下子从山顶冲下来\n真的好可怕！$"

JaggedPass_Text_JulioDefeat:
    .string "我觉得好像要崩溃了…$"

JaggedPass_Text_JulioPostBattle:
    .string "在自行车上被颠得这么厉害，\n屁股痛死了…$"

JaggedPass_Text_AutumnIntro:
    .string "我每天都要爬这座山，\n对自己的体力很自信喔！$"

JaggedPass_Text_AutumnDefeat:
    .string "嗯…\n哪里不对劲呢？$"

JaggedPass_Text_AutumnPostBattle:
    .string "那边那块突起来一些的\n奇怪的岩石究竟是怎么回事？$"

