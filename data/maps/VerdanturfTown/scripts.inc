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
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
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
    .string "爸爸告诉我，\n这隧道里全是胆小的宝可梦。\p它们听到巨响就会受惊，\n引发大骚乱。\p所以大型隧道工程\n被迫中止了。\p但有个男人还在\n独自挖掘！$"

VerdanturfTown_Text_ManDugTunnelForLove:
    .string "听说那人挖隧道是\n为了心爱的姑娘。\p虽然不太懂，\n但真浪漫啊！$"

VerdanturfTown_Text_AirCleanHere:
    .string "因风向关系，\n火山灰永远吹不到这里，\p所以这里空气非常清新。\n住在这里，就算是体弱多病的人\l也可能有奇迹般的好转。$"

VerdanturfTown_Text_MakeBattleTentDebut:
    .string "我和宝可梦最近连胜不断，\n决定在绿茵镇的对战帐篷首秀！$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
    .string "你看到友好商店旁边的\n洞窟了吗？\p里面有个人在努力打碎岩石\n来打通隧道。\p要是隧道能打通就太好了……\n这样我们去卡那兹市就更容易了。$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
    .string "友好商店旁的洞穴\n已经是连通两地的隧道啦！\p太棒了——现在去卡那兹市买得文的\n新产品方便多了。$"

VerdanturfTown_Text_TownSign:
    .string "这里是绿茵镇。\n“带有青草气息的风吹高原。”$"

VerdanturfTown_Text_WandasHouse:
    .string "满盈的家$"

VerdanturfTown_Text_BattleTentSign:
    .string "对战帐篷绿茵镇分址\n“精彩对战，尽收眼底！”$"

VerdanturfTown_Text_RusturfTunnelSign:
    .string "卡绿隧道\n“连接卡那兹市和绿茵镇\p隧道工程现已\n终止施工。”$"

