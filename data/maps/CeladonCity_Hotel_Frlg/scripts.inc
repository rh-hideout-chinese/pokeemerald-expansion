CeladonCity_Hotel_Frlg_MapScripts::
	.byte 0

CeladonCity_Hotel_EventScript_Receptionist::
	msgbox CeladonCity_Hotel_Text_ThisHotelIsForPeople, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_Beauty::
	msgbox CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBoyfriend::
	msgbox CeladonCity_Hotel_Text_WhyDidSheBringBrother, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBrother::
	msgbox CeladonCity_Hotel_Text_SisBroughtMeOnVacation, MSGBOX_NPC
	end

CeladonCity_Hotel_Text_ThisHotelIsForPeople::
	.string "宝可梦？\n"
	.string "不，这儿是给人住的旅馆。\p"
	.string "不幸的是，已经客满了。$"

CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend::
	.string "我在和弟弟、男朋友度假。\p"
	.string "玉虹市真是个美丽的城市！$"

CeladonCity_Hotel_Text_WhyDidSheBringBrother::
	.string "怎么会这样？\n"
	.string "为什么她要带弟弟一起来？$"

CeladonCity_Hotel_Text_SisBroughtMeOnVacation::
	.string "好耶！我在度假！\n"
	.string "我姐姐带我一起来的！真棒！$"

