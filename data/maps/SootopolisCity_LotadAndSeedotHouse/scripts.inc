SootopolisCity_LotadAndSeedotHouse_MapScripts::
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother::
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother::
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord::
	special GetSeedotSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord::
	special GetLotadSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot:
    .string "你知道宝可梦橡实果吗？\n在琉璃市这里很难见到。\p我喜欢大型橡实果，\n越大越好。\p但我弟弟说\n莲叶童子更大一些。\p真是傻瓜。\n橡实果比那大多了！\p嗯？你有橡实果吗？\n拜——拜—拜托，给我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad:
    .string "{STR_VAR_2}厘米！\n啊呀，真大！\p它肯定比弟弟见过的\n大莲叶童子还要大！\p谢谢你给我看，\n这是我的谢礼！$"


@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1:
    .string "{PLAYER}收到了伤药。$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1:
    .string "嗯？\n你的包包已经塞满了。$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot:
    .string "{STR_VAR_2}厘米是吗？\p唔……我见过\n比这更大的橡实果。$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot:
    .string "哎，这看上去不错……\n但它不是橡实果！$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot:
    .string "你没有大的橡实果？\n真糟糕……\p如果你有大橡实果，\n就拿给我看看吧。$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory:
    .string "史上最大的橡实果！\n{STR_VAR_2}的{STR_VAR_3}厘米大的巨物！\p比莲叶童子更大的橡实果\n总是人们追寻的东西！$"

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad:
    .string "你知道宝可梦莲叶童子吗？\n在琉璃市这里很难见到。\p我非常非常喜欢大型莲叶童子！\p哥哥说橡实果\n更大，\p但那肯定不对！所有人\n都知道莲叶童子更大。\p嗯？你有莲叶童子吗？\n拜——拜—拜托给我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot:
    .string "{STR_VAR_2}厘米！\n哇，这么大！\p它肯定比哥哥看过的\n巨型橡实果更大。\p谢谢你给我看！\n收下我的谢意吧！$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2:
    .string "{PLAYER}收到了伤药。$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2:
    .string "嗯？\n你的包包已经塞满了。$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad:
    .string "{STR_VAR_2}厘米？\p唔……我还见过\n比它更大的莲叶童子。$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad:
    .string "哎，这个不错！\n但不是莲叶童子！$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad:
    .string "你没有大的莲叶童子？\n真可惜……\p如果你得到了大莲叶童子，\n一定要给我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory:
    .string "史上最大的莲叶童子！\n{STR_VAR_2}的{STR_VAR_3}厘米大的巨物！\p比橡实果更大的莲叶童子\n总是人们追寻的东西！$"

