FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
    .string "嗨，怎么样，向冠军的目标\n冲刺的{PLAYER}？\p茵郁市道馆馆主娜琪是\n飞行属性宝可梦大师，\p她在道馆的旋转门后面\n等着，\p等待着想要\n飞翔的挑战者！\p好了，加油吧！$"

FortreeCity_Gym_Text_GymGuidePostVictory:
    .string "你做到了！\n你飞上了天空！$"

FortreeCity_Gym_Text_JaredIntro:
    .string "观赏一下鸟类宝可梦\n优雅的战斗吧！$"

FortreeCity_Gym_Text_JaredDefeat:
    .string "你……\n你真强……$"

FortreeCity_Gym_Text_JaredPostBattle:
    .string "训练家必须有面对\n意料之外的转变的智慧，\p你有足够的智慧\n到达我们的馆主那儿吗？$"

FortreeCity_Gym_Text_EdwardoIntro:
    .string "所有鸟类宝可梦爱好者\n都渴望进入这道馆，\p作为茵郁市道馆的一员，\n我不能输！$"

FortreeCity_Gym_Text_EdwardoDefeat:
    .string "这对我来说\n压力太大了……$"

FortreeCity_Gym_Text_EdwardoPostBattle:
    .string "世界如此广大，\n在其中有数不清的优秀训练家。\p我得继续训练，\n让自己变得更强。$"

FortreeCity_Gym_Text_FlintIntro:
    .string "这里不需要我们的馆主娜琪出马！\n我就足以对付你！$"

FortreeCity_Gym_Text_FlintDefeat:
    .string "娜琪，我……\n我输了！$"

FortreeCity_Gym_Text_FlintPostBattle:
    .string "娜琪很可爱，也很强。\n她是最棒的馆主！\p脸红……$"

FortreeCity_Gym_Text_AshleyIntro:
    .string "娜琪单独教过我！\n我不会轻易输给你的！$"

FortreeCity_Gym_Text_AshleyDefeat:
    .string "我败了……$"

FortreeCity_Gym_Text_AshleyPostBattle:
    .string "多亏了娜琪，住在茵郁市的人们\n不必心惊胆战了。$"

FortreeCity_Gym_Text_HumbertoIntro:
    .string "当娜琪战斗的时候，她的脸上\n闪耀着坚定的决心……\p我不会让你看到\n她那可爱的一幕！$"

FortreeCity_Gym_Text_HumbertoDefeat:
    .string "哎！\n我阻止不了你。$"

FortreeCity_Gym_Text_HumbertoPostBattle:
    .string "你最好小心！\n别分心盯着娜琪看，\l否则你会败得一塌糊涂！$"

FortreeCity_Gym_Text_DariusIntro:
    .string "你最好知道世界上\n有多种多样的飞行属性宝可梦。\p你知道的，是吗？$"

FortreeCity_Gym_Text_DariusDefeat:
    .string "看来你很清楚自己的实力！$"

FortreeCity_Gym_Text_DariusPostBattle:
    .string "你确实打败了我，\n但你最好小心点！我们的馆主\l娜琪的宝可梦都不好对付。$"

FortreeCity_Gym_Text_WinonaIntro:
    .string "我是娜琪，茵郁市\n宝可梦道馆的馆主。\p我是鸟类宝可梦的朋友，\n同它们一起在天空中翱翔……\p无论战斗多么困难，\n我们都会优雅地凯旋……\p见识一下我和鸟类宝可梦\n那华丽的舞步吧！$"

FortreeCity_Gym_Text_WinonaDefeat:
    .string "我以前从未见过\n指挥宝可梦比我更优雅的\l训练家……\p作为承认你的才能的标志，\n我把这道馆徽章送给你。$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
    .string "{PLAYER}从娜琪处\n得到白羽徽章。$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
    .string "白羽徽章能使包括交换\n得来的所有LV70以下\l宝可梦听从指挥，\p同时也可以在战斗之外\n使用秘传学习器飞翔。\p还有这个……\n这是我的礼物。$"

FortreeCity_Gym_Text_ExplainAerialAce:
    .string "招式学习器40的\n里面是燕返，\p它的速度……\n没有任何宝可梦能躲过。\p…… …… ……$"

FortreeCity_Gym_Text_RegisteredWinona:
    .string "把道馆馆主娜琪的信息\n登记进宝可导航里。$"

FortreeCity_Gym_Text_WinonaPostBattle:
    .string "尽管我输给了你，\n我还会尽心抚养我的鸟类宝可梦。$"

FortreeCity_Gym_Text_GymStatue:
    .string "茵郁市宝可梦道馆$"

FortreeCity_Gym_Text_GymStatueCertified:
    .string "茵郁市宝可梦道馆\p娜琪认可的训练家：\n{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
    .string "娜琪：我们人类永远\n无法逃离大地重力的牵引，\p但若向着更高的目标努力，\n我们依然能够耸立于天地！\p你作为称雄一方的冠军，\n已经攀上了巅峰。\p让我看看你是如何\n全力飞翔的吧！$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
    .string "我依然没有追上你的高度……$"

FortreeCity_Gym_Text_WinonaPostRematch:
    .string "娜琪：尽管我输了，\n我心灵的双翼还未折断，\p我依然能够一次次\n在天空中展翅飞翔，\p我坚信！$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
    .string "娜琪：我们人类永远\n无法逃离大地重力的牵引，\p但若向着更高的目标努力，\n我们依然能够耸立于天地！\p你作为称雄一方的冠军，\n已经攀上了巅峰。\p让我看看你是如何\n全力飞翔的吧！\p哎，不……你只\n带了一只宝可梦吗？\p至少带两只宝可梦\n再回来吧。$"
