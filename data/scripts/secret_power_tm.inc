Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "哎？你问我在干什么？\p"
	.string "我正想用宝可梦的招式\n"
	.string "在这里建一个只有\l"
	.string "我自己才能住进去的房间呐！\p"
	.string "对了！要不我给你这个招式学习器\n"
	.string "你也试试看吧！怎么样？$"

Route111_Text_ExplainSecretPower:
	.string "对着面前这种藤蔓快要落下来的树\n"
	.string "使用秘密之力这个招式试试看吧！\l"
	.string "藤蔓落下来，就可以爬上去了！\p"
	.string "那样的话，树顶有十分宽敞的空间\n"
	.string "我还在那里放了许多我喜欢的东西！\l"
	.string "只属于我一个人的房间……\l"
	.string "就是，我的秘密基地了！\l"
	.string "你也可以试试做一个的！\p"
	.string "还有还有，制造秘密基地的场所\n"
	.string "可不仅仅只有树上的！\p"
	.string "在有小坑的墙壁前\n"
	.string "也使用秘密之力试试看吧！\p"
	.string "我去找找有没有别的地方去！\n"
	.string "就这样吧！拜拜！$"

Route111_Text_DontWantThis:
	.string "啊，原来你不要啊！\n"
	.string "什么时候想要了，再来找我吧！$"

Route111_Text_DontHaveAnyRoom:
	.string "啊，你的包包好像满了！\p"
	.string "我先帮你拿着，等下次包包\n"
	.string "空出来了，再过来拿吧！$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
