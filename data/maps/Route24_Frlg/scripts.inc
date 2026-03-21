Route24_Frlg_MapScripts::
	.byte 0

Route24_EventScript_Rocket::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 1, Route24_EventScript_RocketPostBattle
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNugget
	call Route24_EventScript_BattleRocket
	release
	end

Route24_EventScript_NoRoomForNugget::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

Route24_EventScript_RocketPostBattle::
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	release
	end

Route24_EventScript_RocketTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketApproachPlayer
	call_if_eq VAR_TEMP_1, 1, Route24_EventScript_RocketMotionToPlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNuggetTrigger
	call Route24_EventScript_BattleRocket
	releaseall
	end

Route24_EventScript_BattleRocket::
	giveitem_msg Route24_Text_ReceivedNuggetFromMysteryTrainer, ITEM_NUGGET
	message Route24_Text_JoinTeamRocket
	waitmessage
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_ROUTE24_ROCKET
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_6, Route24_Text_RocketDefeat
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	return

Route24_EventScript_RocketApproachPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketApproachPlayer
	waitmovement 0
	return

Route24_EventScript_RocketMotionToPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route24_EventScript_NoRoomForNuggetTrigger::
	msgbox Route24_Text_YouDontHaveAnyRoom
	closemessage
	applymovement LOCALID_PLAYER, Route24_Movement_WalkDown
	waitmovement 0
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketWalkBackToPos
	release
	end

Route24_EventScript_RocketWalkBackToPos::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketWalkBackToPos
	waitmovement 0
	return

Route24_Movement_RocketApproachPlayer::
	walk_left
	step_end

Route24_Movement_RocketWalkBackToPos::
	walk_right
	walk_in_place_faster_left
	step_end

Route24_Movement_WalkDown::
	walk_down
	step_end

Route24_Text_JustEarnedFabulousPrize::
    .string "祝贺你！你战胜了\n"
    .string "我们五个训练家！\p"
    .string "你获得了一份神秘大礼！$"

Route24_Text_ReceivedNuggetFromMysteryTrainer::
    .string "{PLAYER}从谜之训练家那儿\n"
    .string "获得了一个金珠！$"

Route24_Text_YouDontHaveAnyRoom::
    .string "你没有退路了！$"

Route24_Text_JoinTeamRocket::
    .string "顺便问问，\n"
    .string "你想加入火箭队吗？\p"
    .string "我们是以抢夺宝可梦为主的\n"
    .string "专业犯罪组织。\p"
    .string "想加入吗？\p"
    .string "你确定？\p"
    .string "来吧，加入我们吧！\p"
    .string "我是叫你加入我们！\p"
    .string "好吧，看来得给你来点硬的！\p"
    .string "我要让你无法拒绝！$"

Route24_Text_RocketDefeat::
    .string "啊！\n"
    .string "你太强了！$"

Route24_Text_YoudBecomeTopRocketLeader::
    .string "以你的能力，\n"
    .string "你能成为火箭队的高级干部。\p"
    .string "瞧瞧，多么好的机会！\n"
    .string "浪费掉真是太可惜了。$"

Route24_Text_ShaneIntro::
    .string "我看见了你草地上的壮举！$"

Route24_Text_ShaneDefeat::
    .string "我想不通！$"

Route24_Text_ShanePostBattle::
    .string "我藏着是因为\n"
    .string "我害怕桥上的人们。$"

Route24_Text_EthanIntro::
    .string "嗯！我是5号！\n"
    .string "我要把你踏在脚下！$"

Route24_Text_EthanDefeat::
    .string "哇！\n"
    .string "真厉害！$"

Route24_Text_EthanPostBattle::
    .string "我尽力了，我不后悔！$"

Route24_Text_ReliIntro::
    .string "我是4号！\n"
    .string "感觉累了吗？$"

Route24_Text_ReliDefeat::
    .string "我也失败了！$"

Route24_Text_ReliPostBattle::
    .string "我尽力了，我不后悔！$"

Route24_Text_TimmyIntro::
    .string "3号在这儿！\n"
    .string "我可没那么容易搞定！$"

Route24_Text_TimmyDefeat::
    .string "啊！\n"
    .string "被牵制住了！$"

Route24_Text_TimmyPostBattle::
    .string "我尽力了，我不后悔！$"

Route24_Text_AliIntro::
    .string "我是2号！\n"
    .string "现在要认真了！$"

Route24_Text_AliDefeat::
    .string "我是怎么输的？$"

Route24_Text_AliPostBattle::
    .string "我尽力了，我不后悔！$"

Route24_Text_CaleIntro::
    .string "人们把这里称作\n"
    .string "金珠大桥！\p"
    .string "战胜我们五个训练家就可以\n"
    .string "获得一份神秘大礼！\p"
    .string "你能得到它吗？$"

Route24_Text_CaleDefeat::
    .string "呼！\n"
    .string "好家伙！$"

Route24_Text_CalePostBattle::
    .string "我尽力了。我不后悔！$"
