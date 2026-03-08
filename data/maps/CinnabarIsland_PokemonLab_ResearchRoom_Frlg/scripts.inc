CinnabarIsland_PokemonLab_ResearchRoom_Frlg_MapScripts::
	.byte 0

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_MetronomeTutor::
	goto EventScript_MetronomeTutor
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Scientist::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_EeveeCanEvolveIntroThreeMons, MSGBOX_NPC
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Computer::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_LegendaryBirdEmail, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_AmberPipe::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_AnAmberPipe, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_ResearchRoom_Text_EeveeCanEvolveIntroThreeMons::
    .string "伊布可以进化成\n"
    .string "三种不同的宝可梦。$"

CinnabarIsland_PokemonLab_ResearchRoom_Text_LegendaryBirdEmail::
    .string "一封电子邮件\p"
    .string "…… …… ……\p"
    .string "世界上有三只传说中的\n"
    .string "鸟宝可梦。\p"
    .string "他们是急冻鸟，闪电鸟，和\n"
    .string "火焰鸟。\p"
    .string "它们的栖息地还是个未解之谜。\p"
    .string "我们计划先从\n"
    .string "华蓝附近的山洞开始寻找。\p"
    .string "来自：宝可梦研究组……$"

CinnabarIsland_PokemonLab_ResearchRoom_Text_AnAmberPipe::
    .string "一支琥珀笛子！$"

