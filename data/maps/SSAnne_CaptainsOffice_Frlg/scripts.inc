SSAnne_CaptainsOffice_Frlg_MapScripts::
	.byte 0

SSAnne_CaptainsOffice_EventScript_Captain::
	lock
	goto_if_set FLAG_GOT_HM01, SSAnne_CaptainsOffice_EventScript_AlreadyGotCut
	msgbox SSAnne_CaptainsOffice_Text_CaptainIFeelSeasick
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message SSAnne_CaptainsOffice_Text_RubbedCaptainsBack
	waitmessage
	playfanfare MUS_HEAL
	waitfanfare
	call EventScript_RestorePrevTextColor
	delay 50
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SSAnne_CaptainsOffice_Text_ThankYouHaveHMForCut
	giveitem_msg SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain, ITEM_HM01, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox SSAnne_CaptainsOffice_Text_ExplainCut
	setflag FLAG_GOT_HM01
	setvar VAR_MAP_SCENE_VERMILION_CITY, 1
	release
	end

@ Unused
SSAnne_CaptainsOffice_EventScript_NoRoomForCut::
	msgbox SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis
	closemessage
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SSAnne_CaptainsOffice_EventScript_AlreadyGotCut::
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon
	release
	end

SSAnne_CaptainsOffice_EventScript_TrashCan::
	msgbox SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_EventScript_Book::
	msgbox SSAnne_CaptainsOffice_Text_HowToConquerSeasickness, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_Text_CaptainIFeelSeasick::
    .string "船长 呕……\n"
    .string "我很不舒服……\l"
    .string "呕！好晕啊……$"

SSAnne_CaptainsOffice_Text_RubbedCaptainsBack::
    .string "{PLAYER}揉了揉船长的背！\p"
    .string "揉揉……\n"
    .string "揉揉……$"

SSAnne_CaptainsOffice_Text_ThankYouHaveHMForCut::
    .string "船长：唔！谢谢你！\n"
    .string "我现在好多了。\p"
    .string "你想看我的秘传技居合斩吗？\p"
    .string "如果我不是那么虚弱的话倒是可以让你\n"
    .string "见识下我独步天下的居合斩技术……\p"
    .string "我想起来了！给你这个！\n"
    .string "这个秘传学习机！\p"
    .string "把居合斩教给你的宝可梦，\n"
    .string "你就能让它随时表演居合斩给你看了！$"

SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain::
    .string "{PLAYER}从船长那里\n"
    .string "获得了HM01！$"

SSAnne_CaptainsOffice_Text_ExplainCut::
    .string "使用居合斩，你就能砍掉小树。\p"
    .string "可以找枯叶市周围的树试试哦！$"

SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon::
    .string "船长 ……唔！\p"
    .string "我现在好了，\n"
    .string "我想时间也差不多到了。\p"
    .string "圣特安努号马上就要启航了！\p"
    .string "下次回枯叶市时我们再见！$"

SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis::
    .string "哦，不！\n"
    .string "你已经没有多余的空间了！$"

SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked::
    .string "真恶心！\n"
    .string "早知就不应该看！$"

SSAnne_CaptainsOffice_Text_HowToConquerSeasickness::
    .string "怎么样才能克服晕船……\n"
    .string "船长正在阅读中！$"

