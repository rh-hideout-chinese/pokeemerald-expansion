PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
    .string "今天看不见梦幻岛…$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
    .string "啊！哦，天哪！\n今天看见了梦幻岛！$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
    .string "梦幻岛…\p那大概是因为\n天气变化而\l不断隐现的幻影。\p还是说，它真的不停地\n消失或出现？$"

