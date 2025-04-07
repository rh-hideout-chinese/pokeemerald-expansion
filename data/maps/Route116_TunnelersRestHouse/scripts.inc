Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
    .string "卡绿隧道…\p我们用先进的机器在石头上\n做了好多庞大无聊的工作。\l但是，我们不得不停止了。\p看来我们所做的\n对这里的野生宝可梦\l产生了不好的影响。\p因此，我们要做的\n就是什么都不做。$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
    .string "有人为见女友而\n要挖洞去绿荫镇。\l他不顾一切挖通了。\p他说如果不使用机器\n一点一点的挖\l就不会影响到宝可梦\l也就避免了影响自然环境。\p我怀疑他现在是否完成了。$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
    .string "不通过隧道要到达绿荫\n的话，你不得不穿越\l大海到武斗，航行到凯那\l最后穿过紫堇。$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
    .string "听到了吗？到绿荫的隧道\n已经打通了！\p有时，当你的愿望很强烈时，\n美梦就会成真。$"

