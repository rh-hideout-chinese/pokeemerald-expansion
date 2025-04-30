SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "你现在就要退出\n"
	.string "狩猎地带吗？$"

SafariZone_Text_TimesUp:
	.string "叮——咚！时间到！\n"
	.string "狩猎活动结束。$"

SafariZone_Text_OutOfBalls:
	.string "狩猎球用完了，\n"
	.string "狩猎活动结束。$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "要在宝可方块喂养器里面\n"
	.string "放进宝可方块吗？$"

SafariZone_Text_PokeblockStillHere:
	.string "你之前放进去的{STR_VAR_1}\n"
	.string "还在里面。$"

SafariZone_Text_PokeblockWasPlaced:
	.string "把{STR_VAR_1}放进了\n"
	.string "宝可方块喂养器里。$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "欢迎来到狩猎地带！\p"
	.string "在这里有许多丰缘地区\n"
	.string "难得一见的宝可梦，\p"
	.string "你可以观察这些野生宝可梦\n"
	.string "在自然栖息地的生活。\p"
	.string "另外，我们也欢迎\n"
	.string "宝可梦训练家的到来，\p"
	.string "你可以在这里捕捉\n"
	.string "你想要的宝可梦！\p"
	.string "祝你在狩猎地带玩得愉快！$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "欢迎来到狩猎地带！\n"
	.string "请问是第一次来这里吗？$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "祝你在狩猎地带玩得愉快！$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "进入狩猎地带以后，\n"
	.string "会给你30只狩猎球用来捕捉宝可梦，\p"
	.string "狩猎球用完或者你走了500步以后，\n"
	.string "狩猎活动就结束了。\p"
	.string "祝你在狩猎地带玩得愉快！$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "欢迎来到狩猎地带！\p"
	.string "花¥500就可以尽情地捕捉宝可梦！\n"
	.string "你要进行狩猎活动吗？$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "好的，\n"
	.string "欢迎下次再来！$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "抱歉，\n"
	.string "你带的钱不够。$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "请先付¥500。$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "请收好你的狩猎球。$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER}得到30个狩猎球。$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "游戏结束的时候你会收到通知，\n"
	.string "在那之前，请尽情地玩吧。\l"
	.string "野生的宝可梦们在等着你去发现！$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "很抱歉，\n"
	.string "你的电脑盒子满了。$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "很抱歉，\n"
	.string "似乎你还没有宝可方块盒。\p"
	.string "使用宝可方块会使\n"
	.string "狩猎活动变得更有趣的。\p"
	.string "拿到宝可方块盒再来吧，\p"
	.string "你可以在水静市选美大厅\n"
	.string "索要到宝可方块盒。$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "你的时间还没有用完，\n"
	.string "现在就要离开狩猎地带吗？$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "在剩下的时间里\n"
	.string "尽情享受野外冒险的乐趣吧！$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "好的，现在我要收回\n"
	.string "你余下的狩猎球。\p"
	.string "谢谢你的光临，\n"
	.string "下次再见。$"

SafariZone_South_Text_GoodLuck:
	.string "祝你好运！\p"
	.string "需要什么帮助的话，\n"
	.string "就直接告诉我吧！$"

SafariZone_South_Text_Boy:
	.string "知道吗？如果在那个\p"
	.string "方方的箱子里放进宝可方块，\n"
	.string "宝可梦就会聚集到那附近。$"

SafariZone_South_Text_Man:
	.string "我本来想走得更深一点的，\n"
	.string "但我忘记带自行车了。\p"
	.string "据说一些稀有的宝可梦\n"
	.string "生活在比较偏僻的地方。$"

SafariZone_Southwest_Text_Woman:
	.string "有的时候，宝可梦会无视\n"
	.string "我扔出去的宝可方块。\p"
	.string "是不是宝可梦们对于食物\n"
	.string "也有不同的喜好呢？$"

SafariZone_Northwest_Text_Man:
	.string "呼……呼……\n"
	.string "我……终于到这儿了……不过……\p"
	.string "我已经累了……没力气\n"
	.string "去捕捉宝可梦了……$"

SafariZone_North_Text_Fisherman:
	.string "我需要找到一些丰缘地区\n"
	.string "所没有的水属性宝可梦，\p"
	.string "你知道湖在哪儿吗？$"

SafariZone_North_Text_Man:
	.string "我要在这儿捕捉好多宝可梦，\n"
	.string "然后跟我的朋友们交换！$"

SafariZone_South_Text_Youngster:
	.string "我把宝可方块放到了宝可方块\n"
	.string "喂养器里，但它很快就消失了。\p"
	.string "一定是在我没注意的时候\n"
	.string "被宝可梦吃掉了。$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "狩猎地带要领\p"
	.string "向野生宝可梦投掷宝可方块，\n"
	.string "能够减少它们逃跑的可能性。$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "“放松一下你疲惫的双脚吧”\n"
	.string "休息客栈$"

SafariZone_RestHouse_Text_Youngster:
	.string "我没有宝可方块，\n"
	.string "但我还是捕捉了很多宝可梦。\p"
	.string "先小心地接近，\n"
	.string "然后再扔出狩猎球，\l"
	.string "就有更大的可能性捕捉到它们。$"

SafariZone_RestHouse_Text_PsychicM:
	.string "如果使用宝可方块，野生宝可梦\n"
	.string "就不会很快逃跑。\p"
	.string "而对那些本就不太容易逃跑的宝可梦，\n"
	.string "使用宝可方块效果并不大。$"

SafariZone_RestHouse_Text_FatMan:
	.string "放在喂养器里的宝可方块\n"
	.string "能够把宝可梦吸引来，\p"
	.string "我想有相似性格的宝可梦\n"
	.string "会被同一种宝可方块吸引。$"

SafariZone_South_Text_AreaOffLimits1:
	.string "此处正在建设中，\n"
	.string "禁止入内。$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "狩猎地带的扩建\n"
	.string "已经完工，\p"
	.string "希望你能喜欢。$"

SafariZone_South_Text_AreaOffLimits2:
	.string "此处正在建设中，\n"
	.string "禁止入内。$"

SafariZone_Southeast_Text_LittleGirl:
	.string "呀～嗬！这些宝可梦\n"
	.string "都是我从来没见过的！$"

SafariZone_Southeast_Text_FatMan:
	.string "这些宝可梦\n"
	.string "我还是第一次见到，\p"
	.string "而且我还能捕捉这些\n"
	.string "稀有宝可梦！太棒了！$"

SafariZone_Southeast_Text_RichBoy:
	.string "这里的宝可梦好像\n"
	.string "是从丰缘外来的。$"

SafariZone_Northeast_Text_Boy:
	.string "我的狩猎球没剩几个了，\p"
	.string "我得好好考虑一下\n"
	.string "要捕捉什么样的宝可梦。$"

SafariZone_Northeast_Text_Woman:
	.string "据说有人在这附近发现过皮卡丘，\n"
	.string "究竟在哪儿呢？$"

SafariZone_Northeast_Text_Girl:
	.string "啊，真烦！\n"
	.string "我什么都没捕捉到！\p"
	.string "要是再不捕捉些什么的话\n"
	.string "我就不在这儿浪费钱了！$"
