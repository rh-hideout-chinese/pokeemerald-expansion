MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
    .string "嗨，怎么样，向冠军目标\n冲刺的{PLAYER}？\p这里的道馆馆主使用的是\n超能系宝可梦，\p如果用格斗系或\n毒系对付它们，\l会受到很大伤害！\p另外，她们会使用\n强大的组合攻击，\p想要赢的话，就给她们看看\n你与你的宝可梦之间紧密的联系吧。\l加油！$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
    .string "哇，你让我大吃一惊！\n你是个优秀的训练师！$"

MossdeepCity_Gym_Text_PrestonIntro:
    .string "战斗取决于你的精神力量！\n心灵弱小的人永远不会赢！$"

MossdeepCity_Gym_Text_PrestonDefeat:
    .string "我输了！\n我必须重新调整我的精神！$"

MossdeepCity_Gym_Text_PrestonPostBattle:
    .string "优柔寡断的人会输掉战斗，\n这是我对你的警告。$"

MossdeepCity_Gym_Text_VirgilIntro:
    .string "让我看看你的天赋吧！$"

MossdeepCity_Gym_Text_VirgilDefeat:
    .string "你拥有华美的天赋！$"

MossdeepCity_Gym_Text_VirgilPostBattle:
    .string "如果世上真的有天才，\n那么就是我们的道馆馆主！\p但你也许比她们拥有\n更高的天赋…$"

MossdeepCity_Gym_Text_BlakeIntro:
    .string "嘿嘿嘿…看我用心灵感应\n让精灵球浮起来！\p呜啊啊啊啊啊啊啊！\n… … … … … … …\p有时我还是不能同步…$"

MossdeepCity_Gym_Text_BlakeDefeat:
    .string "我的宝可梦战斗技术\n也不能同步了！$"

MossdeepCity_Gym_Text_BlakePostBattle:
    .string "要用精神力举起精灵球\n还是困难了点，但这么小的灰尘的话…\p呜啊啊啊啊啊啊啊！\n… … … … … …\p不不，我没骗人！\n我没吹！真的！$"

MossdeepCity_Gym_Text_HannahIntro:
    .string "输给我的话，也不要\n太责怪自己。\p不是你弱小——\n而是我太强了！$"

MossdeepCity_Gym_Text_HannahDefeat:
    .string "你太强了！$"

MossdeepCity_Gym_Text_HannahPostBattle:
    .string "我失败了，但我不会气馁。\n我只是需要更严格的训练。\p总是乐观看待事情——\n这是我的优势！$"

MossdeepCity_Gym_Text_SamanthaIntro:
    .string "看到了…\n你的未来…\p你能打败我的话，\n我就告诉你未来！$"

MossdeepCity_Gym_Text_SamanthaDefeat:
    .string "我投降！$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
    .string "你和我们的道馆馆主之间\n会有一场激烈的战斗…\p结果…\n我不会告诉你的！$"

MossdeepCity_Gym_Text_MauraIntro:
    .string "你走过的路…\n你经历过的事…\p用你所学会的一切\n全力攻击吧！$"

MossdeepCity_Gym_Text_MauraDefeat:
    .string "你走在通向伟大的道路上！$"

MossdeepCity_Gym_Text_MauraPostBattle:
    .string "勤奋的人们拥有\n光明的前途，\p而懒惰的人所面对的\n惟有绝望的终点。\p种下什么因，就得到什么果…$"

MossdeepCity_Gym_Text_SylviaIntro:
    .string "即使生命有危险，\n我也会赢得胜利！$"

MossdeepCity_Gym_Text_SylviaDefeat:
    .string "你所做的…\n吓倒了我…$"

MossdeepCity_Gym_Text_SylviaPostBattle:
    .string "你竟敢打败我…\p若有厄运降临于你，\n不要怪我…$"

MossdeepCity_Gym_Text_NateIntro:
    .string "呵呵呵。\p让我给你看看\n超能系的执着。$"

MossdeepCity_Gym_Text_NateDefeat:
    .string "啊，天哪，天哪！\n你的战斗无与伦比！$"

MossdeepCity_Gym_Text_NatePostBattle:
    .string "我…我不会被任—任何失败\n吓—吓倒。$"

MossdeepCity_Gym_Text_KathleenIntro:
    .string "体会一下完全绝望的\n恐怖吧！$"

MossdeepCity_Gym_Text_KathleenDefeat:
    .string "不——！$"

MossdeepCity_Gym_Text_KathleenPostBattle:
    .string "你的活力感染了我！\n快点离开吧！$"

MossdeepCity_Gym_Text_CliffordIntro:
    .string "我也许已过盛年，\n但你也不要太过接近我。$"

MossdeepCity_Gym_Text_CliffordDefeat:
    .string "啊，你身上散发着\n年轻的活力！$"

MossdeepCity_Gym_Text_CliffordPostBattle:
    .string "看来我无法\n胜过你的活力。$"

MossdeepCity_Gym_Text_MaceyIntro:
    .string "你不会走到最后的！\n如果我出手，这就毫无疑问了！$"

MossdeepCity_Gym_Text_MaceyDefeat:
    .string "你怎么会变得\n这么强的？$"

MossdeepCity_Gym_Text_MaceyPostBattle:
    .string "哼！你也许很强，但你\n却与超能系不合！\p某种程度来说，你的战斗方式极为冷漠！$"

MossdeepCity_Gym_Text_NicholasIntro:
    .string "呜啊啊啊！尝尝我的宝可梦\n那超凡脱俗的力量吧！$"

MossdeepCity_Gym_Text_NicholasDefeat:
    .string "啊\n被打败了！$"

MossdeepCity_Gym_Text_NicholasPostBattle:
    .string "好吧！下次我要找到一种\n绝对不可战胜的力量。$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
    .string "枫：嘿嘿嘿…你惊讶吗？\p南：呵呵呵…你惊讶吗？\p枫：这里有两个道馆馆主。\n南：这里有两个道馆馆主。\p枫：我们是双胞胎！\n南：我们是双胞胎！\p枫：我们不需要交谈，因为…\n南：我们可以用意识…\p枫：互相感应到…\n南：对方的想法！\p枫：你能打败我们…\n南：这完美的组合吗？$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
    .string "枫：什么？！我们的组合…\n南：被打败了！\p枫：没办法，是你赢了…\n南：那么，这是我们承认你的证明。$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
    .string "{PLAYER}从枫和南处\n得到了心灵徽章。$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
    .string "枫：心灵徽章能够提升\n宝可梦的特攻和特防。\p南：同时也可以在战斗外\n使用秘传学习器潜水。\p枫：这个也给你吧。$"

MossdeepCity_Gym_Text_ExplainCalmMind:
    .string "枫：那个招式学习器04里面是…\n南：冥想！\p枫：它能提升特攻…\n南：还能提高特防！\p枫：这是超能宝可梦…\n南：最佳的招式！\p… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
    .string "把道馆馆主枫和南的信息\n登记进口袋领航员里。$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
    .string "枫：看来你和你的宝可梦间的\n牵绊比我们之间的\l还要强得多。\p南：你会变得更强的！\n这在我们的战斗中就能看出来。$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
    .string "枫：嘿嘿嘿…你惊讶吗？\p南：这里有两个道馆馆主。\p枫：哎，你只有一只…\n南：能战斗的宝可梦。\p枫：我们不能这样战斗！\p南：要和我们战斗，\n再多带几只宝可梦来吧。$"

MossdeepCity_Gym_Text_GymStatue:
    .string "绿岭市宝可梦道馆$"

MossdeepCity_Gym_Text_GymStatueCertified:
    .string "绿岭市宝可梦道馆\p南与枫认可的训练师：\n{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
    .string "枫：宝可梦…\n南：宝可梦…\p枫：队伍改变后…\n南：战术也随之改变。\p枫：但我…\n南：但我…\p枫：我会一直跟南在一起！\n南：我会一直跟枫在一起！\p枫：我们会让你一次次…\n南：看到我们完美的组合！$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
    .string "枫：你和你的宝可梦…\n南：就像！$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
    .string "枫：你打败了我们，\n但我们不会沮丧！\p南：因为我们两人\n永远会相互依靠！$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
    .string "枫：你又回来…\n南：你又回来…\p枫：跟我们再次战斗。\n南：跟我们再次战斗。\p枫：但是…\n南：向我们挑战…\p枫：你却只带来了一只宝可梦！\n南：你却只带来了一只宝可梦！\p枫：你再来时要带来…\n南：至少两只宝可梦。$"
