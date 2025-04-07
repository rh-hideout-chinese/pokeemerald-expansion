VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
    .string "我和我的家人一起训练，\n整个一个大家族啊！\l我不会输给任何人的！$"

VictoryRoad_B2F_Text_VitoDefeat:
    .string "比我的家人更强？！\n这可能么？！$"

VictoryRoad_B2F_Text_VitoPostBattle:
    .string "我比我家里的任何一个人都强，\n我之前从没输过的…\p我失去信心了…\n回家好了…$"

VictoryRoad_B2F_Text_OwenIntro:
    .string "听说这附近来了一个很强的\n小孩，说的是你吗？$"

VictoryRoad_B2F_Text_OwenDefeat:
    .string "你这小虾米竟然这么强！$"

VictoryRoad_B2F_Text_OwenPostBattle:
    .string "有流言说那个很强的小孩\n来自橙华市。$"

VictoryRoad_B2F_Text_CarolineIntro:
    .string "你一定有点累了吧。$"

VictoryRoad_B2F_Text_CarolineDefeat:
    .string "一点也看不出累来！$"

VictoryRoad_B2F_Text_CarolinePostBattle:
    .string "冠军之路和宝可梦联盟\n的挑战都会很累人的，\l作好准备吧！$"

VictoryRoad_B2F_Text_JulieIntro:
    .string "有了很多道馆徽章\n就自大起来可不行，\p没听说过\n山外有山么！$"

VictoryRoad_B2F_Text_JulieDefeat:
    .string "看来你比我还强！$"

VictoryRoad_B2F_Text_JuliePostBattle:
    .string "看着自己收集的徽章，回忆一下\n那些曾与自己相逢的训练师们吧。$"

VictoryRoad_B2F_Text_FelixIntro:
    .string "我做了这么多努力，\n但是紧张让我的肚子疼得厉害…$"

VictoryRoad_B2F_Text_FelixDefeat:
    .string "哦…\n痛死了…$"

VictoryRoad_B2F_Text_FelixPostBattle:
    .string "一想到宝可梦联盟已经近在咫尺了\n我就紧张得不行。\p我只是假装冷静而已。$"

VictoryRoad_B2F_Text_DianneIntro:
    .string "这个洞穴里聚集着\n精英中的精英。\p你有什么感觉？$"

VictoryRoad_B2F_Text_DianneDefeat:
    .string "一点都不紧张！$"

VictoryRoad_B2F_Text_DiannePostBattle:
    .string "有胆量！我喜欢！\n加油吧！$"

