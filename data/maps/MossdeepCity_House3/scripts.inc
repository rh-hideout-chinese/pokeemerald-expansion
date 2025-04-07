MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
    .string "喂，那边那位训练师！\n超级钓竿真的非常妙！\p即使你想要海底的宝可梦，\n它也能把它们钓出来！\p你觉得呢？\n你想要是吧？$"

MossdeepCity_House3_Text_SuperRodIsSuper:
    .string "当然，当然！\n毕竟，超级钓竿真的非常妙！$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
    .string "只要有水，\n就甩出你的钓竿来钓鱼吧！$"

MossdeepCity_House3_Text_DontYouLikeToFish:
    .string "哎？\n你不喜欢钓鱼吗？$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
    .string "用你的超级钓竿\n寻找海底的宝可梦吧。$"

