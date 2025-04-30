SlateportCity_SternsShipyard_2F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_2F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding:
    .string "虽说是组装交通工具，\n设计一条大船\l更像是建造大楼。$"

SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy:
    .string "你觉得用沉重的铁制成的船\n能浮在水上很奇怪吗？\p它是因为浮力原理\n浮起来的。$"

