SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
    .string "哈哈哈哈！\p没有潜水艇你是\n怎么能到这儿的？\l真是个了不起的小孩子！\p但是…这可跟让不让你\n在这里管闲事没关系，\p而且，我个人也非常想报\n天气研究所的仇…\p我会让你吃点苦头的！\n觉悟吧！$"

SeafloorCavern_Room3_Text_ShellyDefeat:
    .string "哈哈哈哈！\p哎呦！$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
    .string "哈哈哈哈！\n你真是无懈可击。\p你不是水舰队的一员\n实在是一件非常可惜的事情。\p否则你一定会喜欢\n老大向我们描绘的\l童话般的世界的…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
    .string "为了实现我们的梦想，我们\n需要宝可梦的力量。\p但是那些像你一样爱管闲事的人\n却总是用宝可梦的力量来碍事，\l甚至都追到了这里来！\p人生总是不能\n如我们所愿一般进行！$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
    .string "呃！$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
    .string "要知道，我们从来不会质疑\n头儿要干的事情。\p但是现在，你，一个小废物，\n竟然要顶撞我们的老大。\p也许…\n你是不是有点…$"

