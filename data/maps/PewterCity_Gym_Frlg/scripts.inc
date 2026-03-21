PewterCity_Gym_Frlg_MapScripts::
	.byte 0

PewterCity_Gym_EventScript_Brock::
	famechecker FAMECHECKER_BROCK, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_BROCK, PewterCity_Gym_Text_BrockIntro, PewterCity_Gym_Text_BrockDefeat, PewterCity_Gym_EventScript_DefeatedBrock, NO_MUSIC
	goto_if_unset FLAG_GOT_TM39_FROM_BROCK, PewterCity_Gym_EventScript_GiveTM39
	msgbox PewterCity_Gym_Text_BrockPostBattle
	release
	end

PewterCity_Gym_EventScript_DefeatedBrock::
	famechecker FAMECHECKER_BROCK, 1
	setflag FLAG_DEFEATED_BROCK
	setflag FLAG_BADGE01_GET
	setvar VAR_MAP_SCENE_PEWTER_CITY, 1
	setflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY
	set_gym_trainers_frlg 1
	goto PewterCity_Gym_EventScript_GiveTM39
	end

PewterCity_Gym_EventScript_GiveTM39::
	msgbox PewterCity_Gym_Text_TakeThisWithYou
	checkitemspace ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, PewterCity_Gym_EventScript_NoRoomForTM39
	giveitem_msg PewterCity_Gym_Text_ReceivedTM39FromBrock, ITEM_TM39
	setflag FLAG_GOT_TM39_FROM_BROCK
	msgbox PewterCity_Gym_Text_ExplainTM39
	release
	end

PewterCity_Gym_EventScript_NoRoomForTM39::
	msgbox PewterCity_Gym_Text_DontHaveRoomForThis
	release
	end

PewterCity_Gym_EventScript_Liam::
	trainerbattle_single TRAINER_CAMPER_LIAM, PewterCity_Gym_Text_LiamIntro, PewterCity_Gym_Text_LiamDefeat
	msgbox PewterCity_Gym_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BROCK, PewterCity_Gym_EventScript_GymGuyPostVictory
	msgbox PewterCity_Gym_Text_LetMeTakeYouToTheTop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Gym_EventScript_GymGuyTakeMeToTop
	goto_if_eq VAR_RESULT, NO, PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop
	end

PewterCity_Gym_EventScript_GymGuyPostVictory::
	msgbox PewterCity_Gym_Text_YoureChampMaterial
	release
	end

PewterCity_Gym_EventScript_GymGuyTakeMeToTop::
	msgbox PewterCity_Gym_Text_LetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop::
	msgbox PewterCity_Gym_Text_ItsFreeLetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyAdvice::
	msgbox PewterCity_Gym_Text_TryDifferentPartyOrders
	release
	end

PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_BrockIntro::
    .string "啊，你来了，我是小刚。\n"
    .string "深灰市的道馆馆主。\p"
    .string "我，以及我的宝可梦的意志力\n"
    .string "都和岩石一样坚定。\p"
    .string "身体都和岩石一样坚硬，\n"
    .string "并且都有着坚定的决心！\p"
    .string "没错，我的宝可梦就是岩石属性的！\p"
    .string "哼，明明知道会输，\n"
    .string "还是要来挑战我？\p"
    .string "是训练家的荣誉心让你\n"
    .string "挑战我的吧！\p"
    .string "好吧，\n"
    .string "展示一下你最好的能力吧！{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PewterCity_Gym_Text_BrockDefeat::
    .string "我输了。\n"
    .string "你赢得毫无悬念。\p"
    .string "作为通过尼比市道馆挑战的证明，\n"
    .string "请你收下这个……\l"
    .string "宝可梦联盟的灰色徽章。\p"
    .string "{FONT_NORMAL}{PLAYER}从小刚那儿得到了灰色徽章！\n"
    .string "{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
    .string "{FONT_MALE}有了灰色徽章，\n"
    .string "宝可梦就能变得更加强大。\p"
    .string "而且在战斗以外\n"
    .string "也能够使用闪光了。\p"
    .string "当然，宝可梦必须得\n"
    .string "学会闪光才行。$"

PewterCity_Gym_Text_TakeThisWithYou::
    .string "等等！\n"
    .string "拿着这个。$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
    .string "{PLAYER}从小刚那儿得到了TM39。$"

PewterCity_Gym_Text_ExplainTM39::
    .string "TM是技能学习机，\n"
    .string "里面有宝可梦能学习的技能。\p"
    .string "使用技能让一只宝可梦学习。\p"
    .string "一个技能只能用一次。\p"
    .string "所以，当你使用时，\n"
    .string "要认真挑选宝可梦。\p"
    .string "嗯……\n"
    .string "TM39包含岩石封锁。\p"
    .string "它的作用是向敌人投石头\n"
    .string "而且降低其速度。$"

PewterCity_Gym_Text_BrockPostBattle::
    .string "在这个广阔的世界上\n"
    .string "有着各种各样的训练家。\p"
    .string "你作为一个宝可梦训练家\n"
    .string "看起来很有天赋。\p"
    .string "那么我给你个建议吧。\p"
    .string "去挑战华蓝的道馆\n"
    .string "来检验你的能力。$"

PewterCity_Gym_Text_DontHaveRoomForThis::
    .string "你没有空间装这个了。$"

PewterCity_Gym_Text_LiamIntro::
    .string "在那站好别动，小孩！\p"
    .string "要想挑战馆主小刚，\n"
    .string "你还差了10000光年！$"

PewterCity_Gym_Text_LiamDefeat::
    .string "呃！\p"
    .string "光年不是时间……\n"
    .string "而是路程的单位！$"

PewterCity_Gym_Text_LiamPostBattle::
    .string "你相当热血啊。\n"
    .string "……但是比不过小刚！$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
    .string "嗨！\n"
    .string "你抱有着很大的梦想吗？\p"
    .string "你梦想着当上宝可梦的冠军吗？\p"
    .string "我不是训练家，\n"
    .string "但是我可以教你如何取胜。\p"
    .string "让我助你登上顶峰吧！$"

PewterCity_Gym_Text_LetsGetHappening::
    .string "好！\n"
    .string "我们开始吧！$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
    .string "在比赛中第一个出来的宝可梦\n"
    .string "是宝可梦列表最左边的那个。\p"
    .string "改变宝可梦的顺序，\n"
    .string "你能获得不同的有利形势。\p"
    .string "根据你的对手不同\n"
    .string "试着使用不同的顺序。$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
    .string "这是免费服务！\n"
    .string "我们开始吧！$"

PewterCity_Gym_Text_YoureChampMaterial::
    .string "和我想的一样！\n"
    .string "你是当宝可梦冠军的材料！$"

PewterCity_Gym_Text_GymStatue::
    .string "深灰宝可梦道馆\n"
    .string "馆主：小刚\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "深灰宝可梦道馆\n"
    .string "馆主：小刚\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}，{PLAYER}$"

