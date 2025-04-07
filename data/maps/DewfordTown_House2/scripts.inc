DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
    .string "来一饱眼福吧！\p这是丝绸围巾，是正\n流行的款式！\p啊，你的眼睛兴奋地发光了！\n你欣赏我这眩目的款式！\p啊，真高兴！\n给你吧，送给你了！$"

DewfordTown_House2_Text_NoRoom:
    .string "呀，你没地方装了？\p那，听好，这个围巾是\n你的必备品！哎，我要是你，\l我会卖掉我的一切来得到它！$"

DewfordTown_House2_Text_ExplainSilkScarf:
    .string "丝绸围巾能提升\n一般系招式的威力，\p是对几乎所有宝可梦都有\n极大用处的头巾！$"

DewfordTown_House2_Text_BrawlySoCool:
    .string "哇，你是渡海来到\n武斗镇的吗？\p是因为听说藤树\n而来的吗？\p他真的很棒…\n大家都很崇敬他。$"

