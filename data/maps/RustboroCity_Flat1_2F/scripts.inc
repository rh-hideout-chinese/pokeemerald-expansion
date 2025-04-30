.set LOCALID_WALDAS_DAD, 6

RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	waitstate
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
    .string "唉，天天这样太难了……\p什么难？\n还用问吗？\p当然是考虑一天三餐\n该吃什么。\p每天都想着做什么饭\n也不容易。$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
    .string "哎，你好！\n欢迎来到箱神家。\p问你一个问题，\n你带过小孩吗？\p你看，我刚当上爸爸，\n抚养孩子什么的都得从头学。\p我现在有点麻烦，\n女儿文乃总是不爱笑。\p我想如果给她讲笑话\n她就会笑起来的。\p你知道什么有趣的故事\n或词语吗？$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
    .string "我最近试过说\n“{STR_VAR_1}”逗她笑，\p你还知道什么\n更好点的词吗？$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
    .string "哎，不错，那就听你的，\n说给她听听吧。$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
    .string "唉，是吗？\p如果你想到什么好主意，\n我洗耳恭听。$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
    .string "啊，知道了。\n来试试吧？$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
    .string "{STR_VAR_1}。\n{STR_VAR_1}。\p啊，太好了，她笑了！\n啊，我也跟她一样开心！$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
    .string "啊，知道了。\n来试试吧？$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
    .string "{STR_VAR_1}。\n{STR_VAR_1}。\p唔……她根本不笑。\n也许文乃生来就很严肃……$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
    .string "唉，你也不知道什么好词啊。\n那我只能自己想一个了。\p嗯……\n“{STR_VAR_1}”怎么样？\l我们试试看。$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
    .string "{STR_VAR_1}。\n{STR_VAR_1}。\p唔……她根本不笑。\n也许文乃生来就很严肃……$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
    .string "唉，你也不知道什么好词啊。\n看来我只能用上次的词\l逗她笑了。\p对了，如果你想到了什么，\n要赶快告诉我，好吗？$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
    .string "谢谢！\p多亏了你，我亲爱的文乃\n开始笑了！\p实际上，虽然我看起来\n很普通，但我是得文\l公司的主力研究员之一。\p我该做点什么\n报答你？\p对了，我给你的\n电脑宝可梦寄放系统里的\l盒子加些新的背景图片吧。\p在选择背景图案的菜单中\n选择“朋友”，\p就能连接到\n新的背景图片。$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
    .string "是宝可梦毛绒玩具！$"

