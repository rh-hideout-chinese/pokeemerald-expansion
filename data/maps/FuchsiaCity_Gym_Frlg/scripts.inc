FuchsiaCity_Gym_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Gym_EventScript_Koga::
	famechecker FAMECHECKER_KOGA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_KOGA, FuchsiaCity_Gym_Text_KogaIntro, FuchsiaCity_Gym_Text_KogaDefeat, FuchsiaCity_Gym_EventScript_DefeatedKoga, NO_MUSIC
	goto_if_unset FLAG_GOT_TM06_FROM_KOGA, FuchsiaCity_Gym_EventScript_GiveTM06
	msgbox FuchsiaCity_Gym_Text_KogaPostBattle
	release
	end

FuchsiaCity_Gym_EventScript_DefeatedKoga::
	famechecker FAMECHECKER_KOGA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL
	setflag FLAG_DEFEATED_KOGA
	setflag FLAG_BADGE05_GET
	set_gym_trainers_frlg 5
	goto FuchsiaCity_Gym_EventScript_GiveTM06
	end

FuchsiaCity_Gym_EventScript_GiveTM06::
	msgbox FuchsiaCity_Gym_Text_KogaExplainSoulBadge
	checkitemspace ITEM_TM06
	goto_if_eq VAR_RESULT, FALSE, FuchsiaCity_Gym_EventScript_NoRoomForTM06
	giveitem_msg FuchsiaCity_Gym_Text_ReceivedTM06FromKoga, ITEM_TM06
	setflag FLAG_GOT_TM06_FROM_KOGA
	msgbox FuchsiaCity_Gym_Text_KogaExplainTM06
	release
	end

FuchsiaCity_Gym_EventScript_NoRoomForTM06::
	msgbox FuchsiaCity_Gym_Text_MakeSpaceForThis
	release
	end

FuchsiaCity_Gym_EventScript_Phil::
	trainerbattle_single TRAINER_TAMER_PHIL, FuchsiaCity_Gym_Text_PhilIntro, FuchsiaCity_Gym_Text_PhilDefeat
	msgbox FuchsiaCity_Gym_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Edgar::
	trainerbattle_single TRAINER_TAMER_EDGAR, FuchsiaCity_Gym_Text_EdgarIntro, FuchsiaCity_Gym_Text_EdgarDefeat
	msgbox FuchsiaCity_Gym_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_JUGGLER_KIRK, FuchsiaCity_Gym_Text_KirkIntro, FuchsiaCity_Gym_Text_KirkDefeat
	famechecker FAMECHECKER_KOGA, 2
	msgbox FuchsiaCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_JUGGLER_SHAWN, FuchsiaCity_Gym_Text_ShawnIntro, FuchsiaCity_Gym_Text_ShawnDefeat
	msgbox FuchsiaCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kayden::
	trainerbattle_single TRAINER_JUGGLER_KAYDEN, FuchsiaCity_Gym_Text_KaydenIntro, FuchsiaCity_Gym_Text_KaydenDefeat
	msgbox FuchsiaCity_Gym_Text_KaydenPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_JUGGLER_NATE, FuchsiaCity_Gym_Text_NateIntro, FuchsiaCity_Gym_Text_NateDefeat
	msgbox FuchsiaCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_KOGA, FuchsiaCity_Gym_EventScript_GymGuyPostVictory
	msgbox FuchsiaCity_Gym_Text_GymGuyAdvice
	release
	end

FuchsiaCity_Gym_EventScript_GymGuyPostVictory::
	msgbox FuchsiaCity_Gym_Text_GymGuyPostVictory
	release
	end

FuchsiaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, FuchsiaCity_Gym_EventScript_GymStatuePostVictory
	msgbox FuchsiaCity_Gym_Text_GymStatue
	releaseall
	end

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

FuchsiaCity_Gym_Text_KogaIntro::
    .string "阿桔哇哈哈哈哈哈！\p"
    .string "不过是个小孩子居然\n"
    .string "妄想挑战我？\p"
    .string "这个天真的想法真是\n"
    .string "让我乐得发抖啊！\p"
    .string "很好很好，让我向你展示\n"
    .string "一下忍者的恐怖之处吧。\p"
    .string "猛毒会把你慢慢推向毁灭的深渊。\n"
    .string "催眠会使得所有的敌人感到无助！\p"
    .string "在毒属性宝可梦带来\n"
    .string "的绝望面前颤抖吧！{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

FuchsiaCity_Gym_Text_KogaDefeat::
    .string "呃！\n"
    .string "你证明了你的实力！\p"
    .string "这枚浅红徽章\n"
    .string "你拿去吧！$"

FuchsiaCity_Gym_Text_KogaPostBattle::
    .string "中了剧毒之后，宝可梦\n"
    .string "受的伤害会越来越多。\p"
    .string "还要坚持战斗的话\n"
    .string "承受的伤害就会越来越大！\p"
    .string "这是一个货真价实的危险品！$"

FuchsiaCity_Gym_Text_KogaExplainSoulBadge::
    .string "既然现在你得到了浅红徽章，\n"
    .string "你宝可梦的防御会上升一点。\p"
    .string "同时冲浪在战斗之外的时候\n"
    .string "也可以使用了。\p"
    .string "啊！\n"
    .string "顺便拿着这个！$"

FuchsiaCity_Gym_Text_ReceivedTM06FromKoga::
    .string "{PLAYER}从阿桔那里\n"
    .string "得到了TM06。$"

FuchsiaCity_Gym_Text_KogaExplainTM06::
    .string "TM06是\n"
    .string "剧毒！\p"
    .string "它可是个历史能追朔到\n"
    .string "四百年前的秘密技能。$"

FuchsiaCity_Gym_Text_MakeSpaceForThis::
    .string "腾点空间再来，小孩！$"

FuchsiaCity_Gym_Text_KaydenIntro::
    .string "力量不是宝可梦的一切，\n"
    .string "你懂这个道理吗？\p"
    .string "宝可梦需要智慧！\p"
    .string "我将会向你展示智慧\n"
    .string "是怎样战胜野蛮的暴力的。$"

FuchsiaCity_Gym_Text_KaydenDefeat::
    .string "什么？\n"
    .string "太惊人了！$"

FuchsiaCity_Gym_Text_KaydenPostBattle::
    .string "这样啊，你智慧和力量完美结合了起来？\n"
    .string "干得好！\p"
    .string "这正是值得年轻的\n"
    .string "训练家们学习的地方。$"

FuchsiaCity_Gym_Text_KirkIntro::
    .string "我过去是一名魔术师。\p"
    .string "但是我一直想成为一名忍者。\n"
    .string "所以我很享受在这个道馆度过的时光。$"

FuchsiaCity_Gym_Text_KirkDefeat::
    .string "我做到了！$"

FuchsiaCity_Gym_Text_KirkPostBattle::
    .string "即使我曾经失败过，\n"
    .string "我仍然会跟阿桔继续修炼，\l"
    .string "他是最强的忍者。$"

FuchsiaCity_Gym_Text_NateIntro::
    .string "让我们看看你被我强大的\n"
    .string "技艺打败的惨样！$"

FuchsiaCity_Gym_Text_NateDefeat::
    .string "你愚弄了我！$"

FuchsiaCity_Gym_Text_NatePostBattle::
    .string "当消耗战拉开序幕的时候，\n"
    .string "下毒和催眠即是我擅用之术！$"

FuchsiaCity_Gym_Text_PhilIntro::
    .string "站在那里别动！\p"
    .string "浅红道馆传说中的\n"
    .string "隐形墙壁有没有使你感到绝望？$"

FuchsiaCity_Gym_Text_PhilDefeat::
    .string "呃啊！\n"
    .string "你做到了！$"

FuchsiaCity_Gym_Text_PhilPostBattle::
    .string "真是令我惊讶！\n"
    .string "给你一个小提示！\p"
    .string "在隐形墙壁里\n"
    .string "有一条不明显的缝！$"

FuchsiaCity_Gym_Text_EdgarIntro::
    .string "我也在阿桔老师那里学习\n"
    .string "忍者之道！\p"
    .string "忍者有很长的\n"
    .string "使用动物的历史！$"

FuchsiaCity_Gym_Text_EdgarDefeat::
    .string "哇喔！$"

FuchsiaCity_Gym_Text_EdgarPostBattle::
    .string "我还有很多的要学。$"

FuchsiaCity_Gym_Text_ShawnIntro::
    .string "阿桔大师来自\n"
    .string "忍者世家。\p"
    .string "你来自哪个世家？$"

FuchsiaCity_Gym_Text_ShawnDefeat::
    .string "你比我想象得\n"
    .string "更有战术！$"

FuchsiaCity_Gym_Text_ShawnPostBattle::
    .string "哪里有光，\n"
    .string "哪里就有影！\p"
    .string "光与影！\n"
    .string "你选择走哪条路？$"

FuchsiaCity_Gym_Text_GymGuyAdvice::
    .string "呦！\n"
    .string "未来的冠军！\p"
    .string "浅红道馆是一个忍者屋。\n"
    .string "这儿有充满谜团的隐形墙壁！\p"
    .string "阿桔应该就在这附近，\n"
    .string "但路被挡住了。\p"
    .string "你得通过墙中间的缝隙\n"
    .string "去找到他。$"

FuchsiaCity_Gym_Text_GymGuyPostVictory::
    .string "忍者带来的恐惧会使你震惊，\n"
    .string "就在下一刻逼近！$"

FuchsiaCity_Gym_Text_GymStatue::
    .string "浅红宝可梦道馆\n"
    .string "馆主：阿桔\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}$"

FuchsiaCity_Gym_Text_GymStatuePlayerWon::
    .string "浅红宝可梦道馆\n"
    .string "馆主：阿桔\p"
    .string "优胜训练家：\n"
    .string "{RIVAL} {PLAYER}$"

