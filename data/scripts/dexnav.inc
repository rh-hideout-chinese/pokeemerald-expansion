EventScript_StartDexNavBattle::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_ExclamationMark
	waitmovement 0
	waitse
	dowildbattle	
	release
	end

EventScript_NotFoundNearby::
	msgbox sText_NotFoundNearby, MSGBOX_SIGN
	end

EventScript_MovedTooFast::
	msgbox sText_TryMovingSlower, MSGBOX_SIGN
	end

EventScript_PokemonGotAway::
	msgbox sText_PokemonGotAway, MSGBOX_SIGN
	end

EventScript_LostSignal::
	msgbox sText_LostSignal, MSGBOX_SIGN
	end

EventScript_TooDark::
	msgbox sText_TooDark, MSGBOX_SIGN
	end

sText_NotFoundNearby:
	.string "附近找不到它。\n"
	.string "试着去别的地方看看吧！$"

sText_TryMovingSlower:
	.string "宝可梦逃走了！\n"
	.string "试着慢一点吧。$"

sText_PokemonGotAway:
	.string "宝可梦逃走了！$"

sText_LostSignal:
	.string "没有任何反应。\n"
	.string "信号中断了！$"

sText_TooDark:
	.string "太黑了，\n无法找到宝可梦！$"
