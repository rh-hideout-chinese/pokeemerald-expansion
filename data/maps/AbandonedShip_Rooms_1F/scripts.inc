AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
    .string "这种船很罕见，我得\n趁机参观一下。\p嗯……\n似乎还有其它船舱……$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
    .string "你究竟是为什么来\n这里？肯定是好奇吧！$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
    .string "不仅好奇，还很强……$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
    .string "隔壁的那个人……\p他说他只是来观光，\n可我觉得不对劲。$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
    .string "你真是太强了！\n我登记下你的信息作纪念吧！$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
    .string "你究竟为什么回到\n这里？肯定是好奇吧！$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
    .string "你也太强了吧？$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
    .string "我敢肯定那个人有什么企图！\n他的行为太可疑了！$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
    .string "哇啊！\n被发现了！……啊？$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
    .string "呼，你不是我妈。$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
    .string "我惹我妈生气了，所以就跑了出来。\n可不要告诉别人我在这儿！$"

