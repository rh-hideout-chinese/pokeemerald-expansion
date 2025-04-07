.set LOCALID_TWIN, 2

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
    .string "爸爸说过，\p这条隧道里\n满是胆小的宝可梦，\p它们会被巨响或大骚动\n吓到，\p所以人们只有停止\n这浩大的隧道工程。\p但还是有一个人\n试图独自打通隧道！$"

VerdanturfTown_Text_ManDugTunnelForLove:
    .string "有个人为了他心爱的女人\n誓要挖通隧道。\p我不是很理解，但我很佩服他！$"

VerdanturfTown_Text_AirCleanHere:
    .string "山风从来不会\n把火山灰刮到这里，\p所以这里空气非常清新。\n住在这里，就算身体虚弱的人身体\l也有可能奇迹般地康复。$"

VerdanturfTown_Text_MakeBattleTentDebut:
    .string "我和我的宝可梦\n战无不胜，\p所以我打算在这个镇上\n设立一个自己的对战帐篷。$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
    .string "你看到宝可梦商店旁边的\n洞窟了吗？\p那里面有个人试图\n打碎里面的巨岩\l到洞的另一侧去。\p如果能穿过隧道就太好了…\n这样我们去卡那兹市就更容易了。$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
    .string "宝可梦商店旁的洞穴\n现在成了通向山的另一侧的隧道。\p这太棒了——现在去卡那兹市\n买得文的新产品更方便了。$"

VerdanturfTown_Text_TownSign:
    .string "绿荫镇\p“从高原上吹下来的风中\n夹带有青草的芳香。”$"

VerdanturfTown_Text_WandasHouse:
    .string "小亮的家$"

VerdanturfTown_Text_BattleTentSign:
    .string "对战帐篷绿荫镇分址\n“来看看这里的战斗，一饱眼福吧！”$"

VerdanturfTown_Text_RusturfTunnelSign:
    .string "卡绿隧道\n“连接卡那兹市和绿荫镇\p隧道工程\n已被取消。”$"

