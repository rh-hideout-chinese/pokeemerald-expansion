ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "嘿，训练家！\n"
	.string "你有一个很灿烂的微笑。\p"
	.string "我有一个爱好——收集宝可梦训练家\n"
	.string "的各种信息档案。$"

ProfileMan_Text_MayISeeYourProfile:
	.string "那么，这个怎么样？\n"
	.string "我能看看你的档案吗？$"

ProfileMan_Text_EasyChatExplanation:
	.string "你要确定一个由四个\n"
	.string "单词或短语构成的信息。\p"
	.string "这里，我会给你一个由四个词构成\n"
	.string "的档案的例子。\p"
	.string "你可以把里面的词换成\n"
	.string "你自己喜欢的词\l"
	.string "来构成你自己的档案。\p"
	.string "这里有很多的档案可以\n"
	.string "供你使用。\p"
	.string "那些词可以代表你的\n"
	.string "宝可梦，生活方式，或是爱好，\l"
	.string "所以他们相当直观。\p"
	.string "那么，首先，选上一些信息\n"
	.string "来列一个选择表。\p"
	.string "然后，从中选出你想要的。\p"
	.string "再继续选选剩下的，之后你就会\n"
	.string "有一个真正属于自己的档案了。$"

ProfileMan_Text_LetsSeeItThen:
	.string "好的！谢谢！\n"
	.string "那么接下来，让我看看。$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "啊，不，确定吗？\p"
	.string "我认为像你这样的人应该\n"
	.string "有一份华丽的档案的……$"

ProfileMan_Text_NotIntoItRightNow:
	.string "啊？你现在还不想编辑？\p"
	.string "那随时都可以来找我！$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "你好呀，训练家！\n"
	.string "你有一个很灿烂的微笑啊。$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "我能看看你的新档案吗？$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "好的！谢谢！\p"
	.string "我希望这分档案一定比之前\n"
	.string "那份要强的多。$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "啊，你喜欢这种形式的档案呀。\p"
	.string "我没有看错你——现在它是一份\n"
	.string "非常棒的档案了。$"

ProfileMan_Text_FantasticProfile:
	.string "太，太强了！\p"
	.string "你的档案，太棒了！\n"
	.string "你完美的表现了自己的想法。\p"
	.string "任何看到这份档案的人\n"
	.string "都会被你迷住的！\p"
	.string "谢谢！$"

@ Unused
ProfileMan_Text_YouKnowSecretSaying:
	.string "哦？\n"
	.string "你明白这句话的含义了！\p"
	.string "你现在是神秘事件\n"
	.string "俱乐部的一员了！$"
