.set LOCALID_COLE, 2
.set LOCALID_GERALD, 3
.set LOCALID_AXLE, 4
.set LOCALID_DANIELLE, 5

LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_COLE, TRAINER_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_AXLE, TRAINER_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_KEEGAN, TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_DANIELLE, TRAINER_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_GERALD, TRAINER_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_JACE, TRAINER_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_JEFF, TRAINER_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_ELI, TRAINER_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
    .string "嗨，怎么样，向冠军目标\n冲刺的{PLAYER}？\p釜炎镇的道馆馆主亚莎\n使用火属性宝可梦，\p她对宝可梦的激情\n比火山还要炙热。\p别太接近她——你会被烧焦的！\n用水浇灭她的火焰，\l加油吧！$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
    .string "异常火热的战斗啊！$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
    .string "啊啊啊啊！\n呀，好烫！$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
    .string "汗水把眼睛都遮住了……$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
    .string "埋在热沙子里可以促进\n血液循环，\p对治疗关节疼痛\n有好处。$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
    .string "我在想办法减轻压力，\n别过来再给我施压！$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
    .string "我想看到你被亚莎的火焰燃烧！$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
    .string "哈啊……呼……\p埋在热沙子里太久，\n都没力气了……$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
    .string "到现在你一定很累了，\n想在热沙子里休息一下，\l是吗？\p但对训练家来说，\n坚强的毅力是一种\l非常重要的品质。$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
    .string "玩火自焚了……$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
    .string "你的技术不错……\n但我们的馆主亚莎很强，\p你不小心的话\n会被烧焦的。$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
    .string "你的宝可梦能抵挡\n392度的高温吗？$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
    .string "火还不够热……$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
    .string "岩浆的温度\n是392度。\p你的宝可梦打败了我，那么\n在岩浆中也应该能比较容易生存下来。$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
    .string "呃……\n好吧，我就和你战斗吧。$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
    .string "呀，你太强了。$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
    .string "我要成为亚莎那样\n漂亮又强大的训练家。$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
    .string "来战斗吧！\n别让我的热情冷却！$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
    .string "周围那么热，\n我的心却好像掉进了冰窟……$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
    .string "凭你心中燃烧的\n战斗热情，你也许有机会\l胜过我们的馆主。$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
    .string "看到这熊熊燃烧的烈焰了吗？\n这闪烁的是对我胜利的期盼！$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
    .string "有什么事搞错了。$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
    .string "那又怎么样？我说那又怎么样\n我能光着脚在热炭上走！\p……不用试也知道你是不可能做到的！$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
    .string "我喜欢高山，\n尤其喜欢火山。$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
    .string "呃，看来我无可挽回地\n失败了。$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
    .string "我留在这儿是因为\n迷上了亚莎的力量。\p呵呵呵呵。$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
    .string "欢迎……啊，不对。\p可怜的训练家，我很惊讶\n你能来到这里！\p我受人之托……\n啊，不对。\p我是亚莎，这里的\n道馆馆主！\p呃……\n虽然我刚刚成为馆主不久，\l但不要低估我的实力！\p用从爷爷那儿继承而来的能力，\n我，呃……会向你展示出我们\l在这片大地上磨炼出来的灼热的招式！$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
    .string "哎……\n我对自己的期待太高了……\p我……我只是刚刚成为\n道馆馆主而已。\p我总是想学那种\n不适合我的性格，\p但我应该按我自己的性格行事，\n否则我的宝可梦会迷茫的。\p谢谢你教给我的这一切，\n这个送给你吧。$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
    .string "{PLAYER}从亚莎处\n得到了烈焰徽章。$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
    .string "烈焰徽章能使包括\n交换得来的所有50级\l以下的宝可梦\l完全听从指挥，\p而且也可以让宝可梦在\n战斗以外使用秘传学习器怪力。\p这是我的谢礼，\n不用推辞，收下吧！$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
    .string "招式学习器50\n里面是过热，\p这招式可以对对手造成\n极大伤害，\p但同时会让使用这招式的\n宝可梦的特攻下降。\l这招式并不适合持久战。$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
    .string "把道馆馆主亚莎的信息\n登记进宝可导航里。$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
    .string "你的力量让我想起了一个人……\p啊，我知道了！你很像橙华市的\n道馆馆主，千里。$"

LavaridgeTown_Gym_1F_Text_GymStatue:
    .string "釜炎镇宝可梦道馆$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
    .string "釜炎镇宝可梦道馆\p亚莎认可的训练家：\n{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
    .string "亚莎：输掉一场战斗\n不会让我泄气的。\p我喜欢宝可梦，\n喜欢战斗，\l而且……我喜欢这道馆！\p我们再来一次战斗，\n释放我们的热情吧！$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
    .string "呼！\n差点喷发出来了！$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
    .string "亚莎：我输了，\n但我很高兴，\p很少能碰上\n这么畅快淋漓的战斗。\p以后我们再来一场\n这样的战斗吧！$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
    .string "亚莎：输掉一场战斗\n不会让我泄气的。\p我喜欢宝可梦，\n喜欢战斗，\l而且……我喜欢这道馆！\p我们再来一次战斗，\n释放我们的热情吧！\p啊，慢着，你只带了一只\n可以战斗的宝可梦？\p你来找我时至少得\n带两只宝可梦吧。$"
