RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
    .string "哟，怎么样？\p听好，朋友！\n你想成为冠军吗？\p我不是训练师，但我可以\n给你一些取胜的建议。\p那么说定了！我们一起朝着\n宝可梦冠军的目标前进！\p作为训练师，任务之一\n就是收集道馆徽章，对吗？\p但击败道馆馆主并没那么容易！\p因此我才会在这里！\n我会给你专业的建议！\p道馆馆主杜娟\n使用岩石系宝可梦。\p岩石系非常坚固，\n但它抵挡不了水系和\l草系招式。\p你打败道馆馆主之后\n再来找我吧。\p好了，加油！$"

RustboroCity_Gym_Text_GymGuidePostVictory:
    .string "哇！令人心驰的胜利！\n看来我的鼓励派上了用场！\p太好了！\n看看你的训练师卡片，\p你得到的岩石徽章\n就记录在上面。\p换句话说…\p你踏上了通向冠军之路的\n第一级阶梯！\p感觉不错！$"

RustboroCity_Gym_Text_JoshIntro:
    .string "别小看我们道馆训练师！\n我会告诉你为什么我是最好的！$"

RustboroCity_Gym_Text_JoshDefeat:
    .string "你比我厉害多了…$"

RustboroCity_Gym_Text_JoshPostBattle:
    .string "你还没有体会过岩石系的\n可怕力量！$"

RustboroCity_Gym_Text_TommyIntro:
    .string "如果你不能打败我，\n就不可能打败杜娟！$"

RustboroCity_Gym_Text_TommyDefeat:
    .string "哇！你的潜力很大！$"

RustboroCity_Gym_Text_TommyPostBattle:
    .string "杜娟比我\n强大多了，\p你最好提高警惕！$"

RustboroCity_Gym_Text_MarcIntro:
    .string "我们也许确实在城镇中央，\n但那又如何？\p我的岩石宝可梦需要\n爆发的空间！$"

RustboroCity_Gym_Text_MarcDefeat:
    .string "哦，天哪！\n我们的挑战者这么强大！$"

RustboroCity_Gym_Text_MarcPostBattle:
    .string "只有交给我们的馆主了。\p这么年轻就培养岩石系，\n真是辛苦她了。$"

RustboroCity_Gym_Text_RoxanneIntro:
    .string "你好，我是卡那兹市\n宝可梦道馆的馆主杜娟。\p因为想要在实战中验证\n在宝可梦训练师学校中所学，\l我才成为了道馆馆主。\p让我看看你用什么宝可梦，\n怎样战斗，好吗？$"

RustboroCity_Gym_Text_RoxanneDefeat:
    .string "这样…\n我输了…\p看来我还有\n很多东西要学…\p我明白了。\p宝可梦联盟规定\n如果训练师打败了道馆馆主，\l就可以得到这个。\p接受这宝可梦\n联盟岩石徽章。$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
    .string "{PLAYER}从杜娟处\n得到了岩石徽章。$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
    .string "岩石徽章可以提升\n你的宝可梦的攻击，\p也可以让它们在战斗外\n使用秘传学习器居合斩。\p这个也拿上吧。$"

RustboroCity_Gym_Text_ExplainRockTomb:
    .string "招式学习器39里面是\n岩石封锁，\p它不只能靠投掷岩石打击敌人，\n也能降低对手的速度。\p使用招式学习器的话，\n宝可梦马上会学会里面的招式，\p但记住，一个招式学习器\n只能使用一次，\n用之前要三思。$"

RustboroCity_Gym_Text_RoxannePostBattle:
    .string "既然你这么强，\n也挑战一下其他道馆馆主吧。\p你会在跟各种训练师的战斗中\n学到很多。$"

RustboroCity_Gym_Text_GymStatue:
    .string "卡那兹市宝可梦道馆$"

RustboroCity_Gym_Text_GymStatueCertified:
    .string "卡那兹市宝可梦道馆\p杜娟认可的训练师：\n{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
    .string "… … … … … …\n… … … … …哔！\p杜娟：喂，你好，{PLAYER}吗？\n我是卡那兹市的杜娟。\p我从藤树那儿听说\n你已经打败了\l很多训练师，\p但是，我认为\n我也不会输给你的。\p我发誓，我会提升我的道馆的实力，\n你可以再来挑战我们。\p我很期待\n那时的到来！\p… … … … … …\n… … … … …咔哒！$"

RustboroCity_Gym_Text_RegisteredRoxanne:
    .string "把道馆馆主杜娟的信息\n登记进口袋领航员里。$"

RustboroCity_Gym_Text_RoxannePreRematch:
    .string "杜娟：很高兴再见到你。\n我是杜娟，这里的道馆馆主。\p我肯定，自上次战斗以来，\n我们都经历了不少战斗。\p我想试试我们成长得\n如何了。战斗吧！$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
    .string "咕…\n我又输了…$"

RustboroCity_Gym_Text_RoxannePostRematch:
    .string "杜娟：对于宝可梦的战斗，\n我仍有很多要学。\p认识到这一点后，\n我更喜欢战斗了！$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
    .string "杜娟：很高兴再见到你。\n我是杜娟，这里的道馆馆主。\p我肯定，自上次战斗以来，\n我们都经历了不少战斗。\p我想试试我们成长得\n如何了…\p哎，不…\n你只带了一只宝可梦？\p带至少两只\n宝可梦回来吧。$"
