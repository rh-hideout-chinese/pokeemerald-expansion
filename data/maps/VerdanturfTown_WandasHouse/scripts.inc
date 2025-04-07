VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
    .string "小光：我输给了你，{PLAYER}，\n但我不会再消沉，\p因为我有了新目标。\n我要和拉鲁拉丝一起\l挑战宝可梦道馆，做一个\l杰出的训练师。\p看着吧，{PLAYER}。\n我会比你更强。\p到那个时候，\n我会再次挑战你。$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
    .string "小光：看着吧，{PLAYER}。\n我会比你更强。\p到那个时候，\n我会再次挑战你。$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
    .string "叔叔：哦，{PLAYER}{KUN}！\n小光就在隔壁。\p但是，孩子，有些事我想\n告诉你，\p这里的自然环境\n对小光的身体有好处，\p但让他打起精神来的\n并不只是环境，\l是宝可梦给了那孩子希望。$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
    .string "小光不在…\n他一个人溜了出去…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
    .string "叔叔：是真的吗？\n小光自己一个人\l跑了那么远…\p我想我该表扬一下他\n——不愧是弟弟的儿子。$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
    .string "小亮：你是？\n哦，对，我知道了！\p你就是小光常说的\n{PLAYER}。\p我是小光的堂姐，\n很高兴认识你！\p自从小光来这儿以后，\n他变得活泼开朗多了。$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
    .string "小亮：别担心小光，\n他没事。\p我了解我的堂弟，而且\n还有宝可梦在他的身边。$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
    .string "多亏了你，我可以天天\n跟我的女友相聚了。\l高兴？我当然很高兴！$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
    .string "我女儿的男友是那种\n精力十分充沛的人，\p他为了见我女儿\n每天都不停地挖隧道。\p女儿有些担心，\n所以经常跑到隧道去。$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
    .string "太令人吃惊了，女儿的男友\n徒手挖开了隧道！\p不敢相信！$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
    .string "如果小光发生了什么，\n我无法再面对他那\l住在橙华市的父母…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
    .string "小光去过彩幽市？\p他那住在橙华市的父母\n一定会大吃一惊的！$"

