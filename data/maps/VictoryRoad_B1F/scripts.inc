VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
    .string "一想到我离宝可梦联盟\n越来越近了…\p我开始有些怯场的感觉了…$"

VictoryRoad_B1F_Text_SamuelDefeat:
    .string "我什么也做不了…$"

VictoryRoad_B1F_Text_SamuelPostBattle:
    .string "宝可梦联盟又变得\n遥远了…好失望…$"

VictoryRoad_B1F_Text_ShannonIntro:
    .string "想要通过宝可梦联盟\n的考验，你必须信任你的\l宝可梦。$"

VictoryRoad_B1F_Text_ShannonDefeat:
    .string "是你们之间的信赖\n将你们紧紧联系在一起。$"

VictoryRoad_B1F_Text_ShannonPostBattle:
    .string "形影不离，患难与共，\n宝可梦和训练师的信任会逐渐增强。$"

VictoryRoad_B1F_Text_MichelleIntro:
    .string "这里不是终点，这只是通向\n宝可梦联盟的道路上的一个小站。$"

VictoryRoad_B1F_Text_MichelleDefeat:
    .string "就是这样！$"

VictoryRoad_B1F_Text_MichellePostBattle:
    .string "你一定会干得很好的！\n你的宝可梦都那么渴望着胜利！$"

VictoryRoad_B1F_Text_MitchellIntro:
    .string "我的宝可梦的士气已经\n达到了顶点！$"

VictoryRoad_B1F_Text_MitchellDefeat:
    .string "我从来没见过像你这样的人。$"

VictoryRoad_B1F_Text_MitchellPostBattle:
    .string "就算在战斗之外，我也能感受到\n从你和你的宝可梦身上\l散发出的力量。$"

VictoryRoad_B1F_Text_HalleIntro:
    .string "好了，别那么紧张！\n放松，放松一点！$"

VictoryRoad_B1F_Text_HalleDefeat:
    .string "哇啊！\n漂亮！$"

VictoryRoad_B1F_Text_HallePostBattle:
    .string "虽然这里确实是冠军之路，\p但它与你之前所经过的道路\n并无太大不同。\p试着去享受你之后\n将会遇到的一切吧！$"

