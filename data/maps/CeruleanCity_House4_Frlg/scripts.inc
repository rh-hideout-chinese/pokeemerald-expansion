.set REWARD_TYPE, VAR_0x8004
.set REWARD_ITEM, VAR_0x8008

CeruleanCity_House4_Frlg_MapScripts::
	.byte 0

CeruleanCity_House4_EventScript_WonderNewsBerryMan::
	lock
	specialvar REWARD_TYPE, WonderNews_GetRewardInfo
	copyvar REWARD_ITEM, VAR_RESULT
	goto_if_eq REWARD_TYPE, NEWS_REWARD_NONE,       CeruleanCity_House4_EventScript_NoNews
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_SMALL, CeruleanCity_House4_EventScript_Reward_RecvSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_BIG,   CeruleanCity_House4_EventScript_Reward_RecvBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_WAITING,    CeruleanCity_House4_EventScript_Waiting
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_SMALL, CeruleanCity_House4_EventScript_Reward_SentSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_BIG,   CeruleanCity_House4_EventScript_Reward_SentBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_AT_MAX,     CeruleanCity_House4_EventScript_AtMax
	end

@ Mystery Gift is not enabled, or the player has no saved Wonder News
CeruleanCity_House4_EventScript_NoNews::
	msgbox CeruleanCity_House4_Text_NothingEntertaining
	release
	end

@ Small reward for receiving Wonder News from friend
CeruleanCity_House4_EventScript_Reward_RecvSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_NewNewsInformativeHaveThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for receiving Wonder News from non-friend source
CeruleanCity_House4_EventScript_Reward_RecvBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_IncredibleNewsHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has not recently sent Wonder News
CeruleanCity_House4_EventScript_Waiting::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_WishCouldShareNewsWithOthers
	release
	end

@ Small reward for sending Wonder News every 1-3 times
CeruleanCity_House4_EventScript_Reward_SentSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_ThanksForSpreadingNewsTakeThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for sending Wonder News every 4th time
CeruleanCity_House4_EventScript_Reward_SentBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_MagnificentNewsSpreadHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has hit reward limit and must wait to receive new rewards
CeruleanCity_House4_EventScript_AtMax::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_EnjoyingMyselfWithAllSortsOfNews
	release
	end

CeruleanCity_House4_EventScript_MovementReactionToNews::
	playse SE_PIN
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_Delay48
	waitmovement 0
	return

CeruleanCity_House4_EventScript_NoRoomForBerries::
	msgbox CeruleanCity_House4_Text_YourBerryPouchIsFull
	release
	end

CeruleanCity_House4_Text_NothingEntertaining::
    .string "唉……\n"
    .string "太多的时间，太少能做的事……\p"
    .string "就没有什么有趣的事情发生吗？$"

CeruleanCity_House4_Text_NewNewsInformativeHaveThis::
    .string "啊！\n"
    .string "一条新的消息！\p"
    .string "嗯……\p"
    .string "我知道了！\n"
    .string "真是长见识了！\p"
    .string "我很欣赏你这么年轻\n"
    .string "能对这条消息感兴趣。\p"
    .string "作为你和我分享这条消息的谢意。\n"
    .string "我要给你这个。$"

CeruleanCity_House4_Text_IncredibleNewsHaveBerries::
    .string "噢，噢！\n"
    .string "这-这条消息！\p"
    .string "嗯……\p"
    .string "令人震惊！\n"
    .string "多么不可思议的消息！\p"
    .string "我好久都没有听到过\n"
    .string "这么难以置信的事情了！\p"
    .string "谢谢你分享这条惊异的消息。\n"
    .string "给你一些树果！$"

CeruleanCity_House4_Text_WishCouldShareNewsWithOthers::
    .string "不跟其他人分享这条消息\n"
    .string "好像很不厚道……\p"
    .string "我希望我能告诉大家……\n"
    .string "让大家知道这个消息……$"

CeruleanCity_House4_Text_ThanksForSpreadingNewsTakeThis::
    .string "啊，你把这条消息告诉了我？\p"
    .string "当各种人分享它时，\n"
    .string "好消息就会变得有价值。\p"
    .string "谢谢你传播这条消息，\n"
    .string "作为谢意，拿着这个吧！$"

CeruleanCity_House4_Text_MagnificentNewsSpreadHaveBerries::
    .string "你又告诉了其他的人？\n"
    .string "好极了！\p"
    .string "那条新闻肯定很高兴\n"
    .string "被这样广泛的传播。\p"
    .string "是的，真的！\p"
    .string "从我和这条消息的角度\n"
    .string "想想这个价值。\p"
    .string "我要给你比平常多的树果。$"

CeruleanCity_House4_Text_EnjoyingMyselfWithAllSortsOfNews::
    .string "沉浸在各种各样的新闻中\n"
    .string "我很享受。\p"
    .string "是的，我很满足！\n"
    .string "我暂时是不会无聊了。$"

CeruleanCity_House4_Text_YourBerryPouchIsFull::
    .string "嗯？你的树果袋满了。\n"
    .string "我的礼物送不出去了。$"

