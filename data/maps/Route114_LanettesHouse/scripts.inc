Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
    .string "真由美：哦！{PLAYER}{KUN}！\p对不起这里太乱了……\n当我全神贯注于研究时\l东西就会这样了……\p这很难为情……请帮我保守秘密\n作为交换给你这个。$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
    .string "关于宝可梦寄放系统\n给你一些建议吧\p你只需要整理下盒子\n就可以分辨出宝可梦存在哪。$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
    .string "真由美的研究注释。\n关于盒子的信息。\p每个盒子可以保管30只宝可梦。\p每个训练家可以在电脑\n系统里保管420只宝可梦。\p继续阅读吗？$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
    .string "标记系统是为了用来\n使宝可梦更容易被管理。\p每个盒子的壁纸和名字\n都是用来使被保管的\l宝可梦更开心。\p继续阅读吗？$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
    .string "当存放宝可梦时，它会被送往\n你最后所使用的盒子里。\p如果那个盒子满了的话\n宝可梦就会被送到下一个盒子。\p也就是说，检查盒子后\n系统会自动选择存放\l宝可梦的盒子。$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
    .string "{PLAYER}合上了笔记本。$"

Route114_LanettesHouse_Text_EmailFromBill:
    .string "通过电脑收到了\n某人发来的信件。\p“…… …… …… ……\p“你的寄放系统比我的\n更加方便。\p“而且它也有许多容易掌握的因素\n使得更有用有趣。\p“在它的发展中我起到了作用\n我感到很骄傲。\p“希望你会继续做出\n寄放系统方面的研究。\p“来自正辉\n…… …… …… ……”$"

