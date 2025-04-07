.set LOCALID_WALLACE, 1

CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
    .string "啊，那么你就是{PLAYER}{KUN}？\n我听说过你的事。\p我是米可利，\p曾经是琉璃市的道馆馆主，\n不过因为某些原因，\p现在我把管理道馆的事情\n委托给我的老师亚当了。\p… … … … … …\n… … … … … …\p那两只正在制造浩劫的宝可梦，\n固拉多和盖欧卡，被称作\l超古代宝可梦，\p但是，超古代宝可梦\n并不仅此两只，\p还有另一只的存在。\p在世界某处生存着的\n超古代宝可梦，烈空坐。\p据说在远古时期，\n就是烈空坐平息了\l交战的两只宝可梦的怒火。\p但是就连我也没有\n关于烈空坐生存之处的线索…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
    .string "米可利：{PLAYER}{KUN}，你有\n关于烈空坐的所在的消息么？\p如果你知道，请务必告诉我。$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
    .string "米可利：觉醒神殿？\p那不就是这里么！\n我希望你能更准确一点！\p拜托，请你帮我想一想\n烈空坐现在到底在哪里。$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
    .string "米可利：送神火山码头？\p但在我之前去见那里的那位老夫人时，\n她并没有提及这种事啊。\p我可不认为老夫人\n会隐瞒什么…\p{PLAYER}{KUN}，能不能\n再好好想想？$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
    .string "米可利：哈？你想不起来了？\n唔…这是个问题…\p你什么也记不起来了？$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
    .string "米可利：天空之柱？\p就是它！\n肯定是天空之柱！\p{PLAYER}{KUN}，没时间浪费了！\n我要马上赶到天空之柱去！$"

