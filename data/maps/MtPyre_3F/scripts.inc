MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
    .string "山里丰富的灵力\n提升了我的精神力！\p像你这样的小孩子……\n妄想赢我吗？$"

MtPyre_3F_Text_WilliamDefeat:
    .string "我沉浸在自怨自艾中……$"

MtPyre_3F_Text_WilliamPostBattle:
    .string "我的精神力量无疑\n上升了几倍，但是……$"

MtPyre_3F_Text_KaylaIntro:
    .string "啊哈哈哈哈！\p这儿可不是小孩子玩的地方，\n对于你也一样！$"

MtPyre_3F_Text_KaylaDefeat:
    .string "我这么干脆地输掉了……$"

MtPyre_3F_Text_KaylaPostBattle:
    .string "这意味我的锻炼\n还是不够……\p我必须不断\n向高处攀登……\p前进！$"

MtPyre_3F_Text_GabrielleIntro:
    .string "你来这儿做什么？$"

MtPyre_3F_Text_GabrielleDefeat:
    .string "好厉害！你真是个\n不同寻常的训练家。$"

MtPyre_3F_Text_GabriellePostBattle:
    .string "已经不再属于这世界的宝可梦，\n现在正与你共度时光的宝可梦，\p还有未来将与你相会的\n宝可梦……\p它们都需要我们同等的珍爱。\n请记住这一点。$"

MtPyre_3F_Text_GabrielleRegister:
    .string "当你的宝可梦稍微成长时\n请让我看看……\p拿出你的宝可导航来吧。$"

MtPyre_3F_Text_GabrielleRematchIntro:
    .string "喔，是你……\p是来让我看看你长大的\n宝可梦吗？$"

MtPyre_3F_Text_GabrielleRematchDefeat:
    .string "真的好厉害！\n你真是个非同寻常的人。$"

MtPyre_3F_Text_GabriellePostRematch:
    .string "已经不再属于这世界的宝可梦，\n现在正与你共度时光的宝可梦，\p还有未来将与你相会的\n宝可梦……\p它们都需要我们同等的珍爱。\n看来你已经记住了这一点。$"

