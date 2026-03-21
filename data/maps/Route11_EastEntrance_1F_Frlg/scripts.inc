Route11_EastEntrance_1F_Frlg_MapScripts::
	.byte 0

Route11_EastEntrance_1F_EventScript_TopGuard::
	msgbox Route11_EastEntrance_1F_Text_ManInLavenderRatesNames, MSGBOX_NPC
	end

Route11_EastEntrance_1F_EventScript_BottomGuard::
	msgbox Route11_EastEntrance_1F_Text_RockTunnelToReachLavender, MSGBOX_NPC
	end

@ Unclear where this is originally from
Route11_EastEntrance_1F_Text_BagIsFull::
	.string "{PLAYER}{KUN}の　バッグ\n"
	.string "いっぱい　みたい　だね$"

Route11_EastEntrance_1F_Text_ManInLavenderRatesNames::
    .string "难道你不认为\n"
    .string "给宝可梦取一个好名字很难吗？\p"
    .string "尤其是当你\n"
    .string "已经有了一个队伍的时候。\p"
    .string "在紫苑镇 有一个\n"
    .string "给宝可梦取名字的男人。\p"
    .string "他甚至也可以帮你\n"
    .string "给宝可梦重新起名。$"

Route11_EastEntrance_1F_Text_RockTunnelToReachLavender::
    .string "如果你想去紫苑\n"
    .string "镇 就穿过岩山隧道吧。\p"
    .string "你可以从华蓝市到达\n"
    .string "岩山隧道。$"

