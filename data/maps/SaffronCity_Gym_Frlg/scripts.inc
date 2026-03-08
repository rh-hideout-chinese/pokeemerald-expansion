SaffronCity_Gym_Frlg_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_Sabrina::
	famechecker FAMECHECKER_SABRINA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_SABRINA, SaffronCity_Gym_Text_SabrinaIntro, SaffronCity_Gym_Text_SabrinaDefeat, SaffronCity_Gym_EventScript_DefeatedSabrina, NO_MUSIC
	goto_if_unset FLAG_GOT_TM04_FROM_SABRINA, SaffronCity_Gym_EventScript_GiveTM04
	msgbox SaffronCity_Gym_Text_ExplainTM04
	release
	end

SaffronCity_Gym_EventScript_DefeatedSabrina::
	famechecker FAMECHECKER_SABRINA, 2
	famechecker FAMECHECKER_SABRINA, 3
	clearflag FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS
	setflag FLAG_DEFEATED_SABRINA
	setflag FLAG_BADGE06_GET
	set_gym_trainers_frlg 6
	goto SaffronCity_Gym_EventScript_GiveTM04
	end

SaffronCity_Gym_EventScript_GiveTM04::
	msgbox SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis
	checkitemspace ITEM_TM04
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_Gym_EventScript_NoRoomForTM04
	giveitem_msg SaffronCity_Gym_Text_ReceivedTM04FromSabrina, ITEM_TM04
	setflag FLAG_GOT_TM04_FROM_SABRINA
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle
	release
	end

SaffronCity_Gym_EventScript_NoRoomForTM04::
	msgbox SaffronCity_Gym_Text_BagFullOfOtherItems
	release
	end

SaffronCity_Gym_EventScript_Johan::
	trainerbattle_single TRAINER_PSYCHIC_JOHAN, SaffronCity_Gym_Text_JohanIntro, SaffronCity_Gym_Text_JohanDefeat
	msgbox SaffronCity_Gym_Text_JohanPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tyron::
	trainerbattle_single TRAINER_PSYCHIC_TYRON, SaffronCity_Gym_Text_TyronIntro, SaffronCity_Gym_Text_TyronDefeat
	famechecker FAMECHECKER_SABRINA, 5
	msgbox SaffronCity_Gym_Text_TyronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Cameron::
	trainerbattle_single TRAINER_PSYCHIC_CAMERON, SaffronCity_Gym_Text_CameronIntro, SaffronCity_Gym_Text_CameronDefeat
	msgbox SaffronCity_Gym_Text_CameronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PSYCHIC_PRESTON, SaffronCity_Gym_Text_PrestonIntro, SaffronCity_Gym_Text_PrestonDefeat
	msgbox SaffronCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Amanda::
	trainerbattle_single TRAINER_CHANNELER_AMANDA, SaffronCity_Gym_Text_AmandaIntro, SaffronCity_Gym_Text_AmandaDefeat
	msgbox SaffronCity_Gym_Text_AmandaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Stacy::
	trainerbattle_single TRAINER_CHANNELER_STACY, SaffronCity_Gym_Text_StacyIntro, SaffronCity_Gym_Text_StacyDefeat
	msgbox SaffronCity_Gym_Text_StacyPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tasha::
	trainerbattle_single TRAINER_CHANNELER_TASHA, SaffronCity_Gym_Text_TashaIntro, SaffronCity_Gym_Text_TashaDefeat
	msgbox SaffronCity_Gym_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_Gym_EventScript_GymGuyPostVictory
	msgbox SaffronCity_Gym_Text_GymGuyAdvice
	release
	end

SaffronCity_Gym_EventScript_GymGuyPostVictory::
	msgbox SaffronCity_Gym_Text_GymGuyPostVictory
	release
	end

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SaffronCity_Gym_Text_SabrinaIntro::
    .string "我能预感到你的到来。\p"
    .string "当我还是个小女孩的时候，\n"
    .string "我拥有了超能力。\p"
    .string "那个早上我拿起汤勺\n"
    .string "使它弯曲了过来。\p"
    .string "虽然我厌恶暴力，但如果你是认真的，\n"
    .string "我是不会手下留情的！{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

SaffronCity_Gym_Text_SabrinaDefeat::
    .string "真是惊讶，我竟然输了！\n"
    .string "不过，输了就是输了。\p"
    .string "我承认，\n"
    .string "我没有用尽全力来取得胜利。\p"
    .string "为了嘉奖你的胜利，\n"
    .string "给予你这枚金黄徽章。$"

SaffronCity_Gym_Text_SabrinaPostBattle::
    .string "超能力并不只是\n"
    .string "少数人的特异功能。\p"
    .string "每个人都拥有超能力。\n"
    .string "只是人们没有意识到这一点罢了。$"

SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis::
    .string "金黄徽章能让\n"
    .string "70级以下的宝可梦听从你的命令。\p"
    .string "强大的宝可梦会更具有野性，\n"
    .string "会在战斗中无视你的命令。\p"
    .string "为了避免这个问题，就不要把\n"
    .string "你的宝可梦训练得过于强大。\p"
    .string "等等，这个TM是给你的。$"

SaffronCity_Gym_Text_ReceivedTM04FromSabrina::
    .string "{PLAYER}从娜姿那里\n"
    .string "得到了TM04。$"

SaffronCity_Gym_Text_ExplainTM04::
    .string "TM04是冥想。\p"
    .string "它能让宝可梦集中起精力\n"
    .string "把它们的特攻和特防一起提升。$"

SaffronCity_Gym_Text_BagFullOfOtherItems::
    .string "你的背包装满了其它道具。$"

SaffronCity_Gym_Text_AmandaIntro::
    .string "娜姿比我更年轻。\n"
    .string "但是我依然尊敬她。$"

SaffronCity_Gym_Text_AmandaDefeat::
    .string "做得还不够好！$"

SaffronCity_Gym_Text_AmandaPostBattle::
    .string "在普通的战斗中，\n"
    .string "更强的那只将会成为赢家。\p"
    .string "如果你想打败娜姿，\n"
    .string "就集中精神祈祷你能够胜利吧。$"

SaffronCity_Gym_Text_JohanIntro::
    .string "我们隐藏的力量吓到你了吗？$"

SaffronCity_Gym_Text_JohanDefeat::
    .string "我根本没料到这种事！$"

SaffronCity_Gym_Text_JohanPostBattle::
    .string "超能力属性宝可梦只害怕\n"
    .string "幽灵和虫子们！$"

SaffronCity_Gym_Text_StacyIntro::
    .string "从宝可梦身上看得出它们训练家\n"
    .string "的样子。\p"
    .string "你的宝可梦一定是强大的那种！$"

SaffronCity_Gym_Text_StacyDefeat::
    .string "我知道！$"

SaffronCity_Gym_Text_StacyPostBattle::
    .string "我还有得学呢……\p"
    .string "我必须掌握好超能力，然后教给\n"
    .string "我的宝可梦……$"

SaffronCity_Gym_Text_TyronIntro::
    .string "你明白了吗？\p"
    .string "只靠蛮力并不足以在\n"
    .string "宝可梦的世界中获胜？$"

SaffronCity_Gym_Text_TyronDefeat::
    .string "我不相信！$"

SaffronCity_Gym_Text_TyronPostBattle::
    .string "娜姿轻松地打败了\n"
    .string "隔壁的空手大王。$"

SaffronCity_Gym_Text_TashaIntro::
    .string "你和我，我们的宝可梦必须\n"
    .string "战上一场！$"

SaffronCity_Gym_Text_TashaDefeat::
    .string "最终还是我败了！$"

SaffronCity_Gym_Text_TashaPostBattle::
    .string "我早就知道会\n"
    .string "结果会是这样。$"

SaffronCity_Gym_Text_CameronIntro::
    .string "虽然娜姿很年轻，但她也是\n"
    .string "我们本领高强的领袖。\p"
    .string "你要超越她很难！$"

SaffronCity_Gym_Text_CameronDefeat::
    .string "噢！\n"
    .string "出局了！$"

SaffronCity_Gym_Text_CameronPostBattle::
    .string "在金黄曾经有两个\n"
    .string "宝可梦道馆。\p"
    .string "不过隔壁的格斗道场\n"
    .string "不再是道馆了。\p"
    .string "当我们决定只保留一个道馆时，\n"
    .string "我们就把它们简单地合并了。$"

SaffronCity_Gym_Text_PrestonIntro::
    .string "金黄宝可梦道馆以\n"
    .string "超能力训练而闻名。\p"
    .string "你想见娜姿，对吗？\n"
    .string "我已经预感到了！$"

SaffronCity_Gym_Text_PrestonDefeat::
    .string "哇啊！$"

SaffronCity_Gym_Text_PrestonPostBattle::
    .string "我用读心术了解了你的想法！\n"
    .string "没错！$"

SaffronCity_Gym_Text_GymGuyAdvice::
    .string "唷！\n"
    .string "未来的冠军！\p"
    .string "娜姿的宝可梦用超能力\n"
    .string "来对抗暴力。\p"
    .string "超能力属性宝可梦对\n"
    .string "格斗属性宝可梦效果拔群。\p"
    .string "甚至在它们还没打出一拳之前，\n"
    .string "就被撂翻在地了。$"

SaffronCity_Gym_Text_GymGuyPostVictory::
    .string "超能力的力量，哈？\p"
    .string "如果我也有，我就能把力量\n"
    .string "萃集在一起。$"

SaffronCity_Gym_Text_GymStatue::
    .string "金黄宝可梦道馆\n"
    .string "馆主：娜姿\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
    .string "金黄宝可梦道馆\n"
    .string "馆主：娜姿\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}，{PLAYER}$"

