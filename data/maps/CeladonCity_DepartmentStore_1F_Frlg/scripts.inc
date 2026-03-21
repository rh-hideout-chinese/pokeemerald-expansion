CeladonCity_DepartmentStore_1F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_1F_EventScript_Receptionist::
	msgbox CeladonCity_DepartmentStore_1F_Text_WelcomeToDeptStore, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_1F_EventScript_LayoutSign::
	msgbox CeladonCity_DepartmentStore_1F_Text_FloorDescriptions, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_1F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_1F_Text_ServiceCounter, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_1F_Text_WelcomeToDeptStore::
	.string "你好！\n"
	.string "欢迎光临玉虹百货大楼。\p"
	.string "右边的告示板\n"
	.string "罗列了商场的布局。$"

CeladonCity_DepartmentStore_1F_Text_FloorDescriptions::
	.string "一楼：服务台\p"
	.string "二楼：训练家商店\p"
	.string "三楼：电玩商店\p"
	.string "四楼：神秘的礼物\p"
	.string "五楼：药店\p"
	.string "天台：自动售货机$"

CeladonCity_DepartmentStore_1F_Text_ServiceCounter::
	.string "一楼：服务台$"

