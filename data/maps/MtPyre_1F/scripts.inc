MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
    .string "送神火山码头的山坡上\n有许多生灵在徘徊…\p无人得知将会发生何事。\n带上这个，对你有好处。$"

MtPyre_1F_Text_ExplainCleanseTag:
    .string "让一只宝可梦携带\n这个净化之符，\p就能够避开一些野生宝可梦。$"

MtPyre_1F_Text_ComeToPayRespects:
    .string "你是来祭奠死去的宝可梦\n的灵魂的么？\p你一定很怀念你的宝可梦。$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
    .string "这是我的蛇纹熊的安息之地。\n我很怀念它…$"

