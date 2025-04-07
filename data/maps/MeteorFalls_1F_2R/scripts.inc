MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
    .string "这里是我们龙使者\n训练的地方。\p冠军也来过。\n你看得出这里有什么特别吗？$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
    .string "呃！\n没想到你那么强！$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
    .string "前方的路还很曲折。\p何时我和我的宝可梦\n会成为最强？$"

MeteorFalls_1F_2R_Text_NicolasRegister:
    .string "我想更多了解你的力量。\n把你登记在领航员里吧。$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
    .string "自从我们相遇，我们\n为了第一的目标而努力训练。\p让我们看下对方\n有多强大吧！$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
    .string "呃！\n没想到你那么强！$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
    .string "很显然你和\n宝可梦一直都在锻炼。\p只要你变强，我\n也会变得更强！$"

MeteorFalls_1F_2R_Text_JohnIntro:
    .string "阿元：我们一直是\n两人一起战斗的。\l我们对自己充满信心。$"

MeteorFalls_1F_2R_Text_JohnDefeat:
    .string "阿元：哦，天。\n我们输了，亲爱的老婆。$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
    .string "阿元：我们结婚\n50年了。\p想想看，我都没有击败过\n我亲爱的老婆。$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
    .string "阿元：多么年轻的训练师！\p想和我们战斗吗？想的话就\n带来更多的宝可梦。$"

MeteorFalls_1F_2R_Text_JohnRegister:
    .string "阿元：年轻的训练师，如果有机会\n的话，你还会和我们对战吗？$"

MeteorFalls_1F_2R_Text_JayIntro:
    .string "阿初：我们结婚\n50年了。\p我们做为夫妻的羁绊\n永远不会解除。$"

MeteorFalls_1F_2R_Text_JayDefeat:
    .string "阿初：哦，亲爱的。\n我们输了，我亲爱的老公。$"

MeteorFalls_1F_2R_Text_JayPostBattle:
    .string "阿初：结婚50年了…\p每当我们吵架，我们都是通过\n宝可梦对战来解决…$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
    .string "阿初：好啦，好啦，你难道不是\n年轻的训练师？\p如果你想和我们战斗，就得\n拿来更多的宝可梦。$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
    .string "阿元：我们一直是\n两人一起战斗的。\l我们对自己充满信心。$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
    .string "阿元：天啊。\n我们输了，亲爱的老婆。$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
    .string "阿元：结婚50年了…\p仔细想想，我和亲爱的老婆\n每天都是在战斗的…$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
    .string "阿元：多么年轻的训练师！\p想和我们战斗吗？想的话就\n带来更多的宝可梦。$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
    .string "阿初：我们结婚\n50年了。\p我们一直互相支持\n我们会让自己变得更强。$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
    .string "阿初：哦，亲爱的。\n我们输了，我亲爱的老公。$"

MeteorFalls_1F_2R_Text_JayPostRematch:
    .string "阿初：结婚50年了…\n发生过太多事。\p我希望我们可以继续\n一起创造快乐的记忆。$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
    .string "阿初：好啦，好啦，你难道不是\n年轻的训练师？\p如果你想和我们战斗，\n就得拿来更多的宝可梦。$"

