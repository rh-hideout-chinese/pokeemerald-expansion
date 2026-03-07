SSAnne_Kitchen_Frlg_MapScripts::
	.byte 0

SSAnne_Kitchen_EventScript_Chef1::
	msgbox SSAnne_Kitchen_Text_BusyOutOfTheWay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef2::
	msgbox SSAnne_Kitchen_Text_SawOddBerryInTrash, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef3::
	msgbox SSAnne_Kitchen_Text_SoBusyImDizzy, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef4::
	lock
	faceplayer
	msgbox SSAnne_Kitchen_Text_IAmLeChefMainCourseIs
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, SSAnne_Kitchen_EventScript_SalmonDuSalad
	call_if_eq VAR_0x8008, 1, SSAnne_Kitchen_EventScript_EelsAuBarbecue
	call_if_eq VAR_0x8008, 2, SSAnne_Kitchen_EventScript_PrimeBeefsteak
	release
	end

SSAnne_Kitchen_EventScript_SalmonDuSalad::
	msgbox SSAnne_Kitchen_Text_SalmonDuSalad
	return

SSAnne_Kitchen_EventScript_EelsAuBarbecue::
	msgbox SSAnne_Kitchen_Text_EelsAuBarbecue
	return

SSAnne_Kitchen_EventScript_PrimeBeefsteak::
	msgbox SSAnne_Kitchen_Text_PrimeBeefsteak
	return

SSAnne_Kitchen_EventScript_Chef5::
	msgbox SSAnne_Kitchen_Text_PeelSpudsEveryDay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef6::
	msgbox SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef7::
	msgbox SSAnne_Kitchen_Text_OnlyGetToPeelOnions, MSGBOX_NPC
	end

SSAnne_Kitchen_Text_BusyOutOfTheWay::
    .string "喂，小家伙！\n"
    .string "我们很忙！\l"
    .string "闪开点！$"

SSAnne_Kitchen_Text_SawOddBerryInTrash::
    .string "我在垃圾桶里看到个奇怪的树果。\n"
    .string "我很想知道那是个什么果子？$"

SSAnne_Kitchen_Text_SoBusyImDizzy::
    .string "我快忙晕啦！\n"
    .string "你别占地方！$"

SSAnne_Kitchen_Text_PeelSpudsEveryDay::
    .string "哼哼哈兮……\p"
    .string "我天天削土豆！\n"
    .string "嗯嗯……$"

SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton::
    .string "你听说过卡比兽吗？\n"
    .string "它是一个大胃王。\p"
    .string "再没有其它宝可梦能像\n"
    .string "卡比兽那样吃那么多、睡那么久！$"

SSAnne_Kitchen_Text_OnlyGetToPeelOnions::
    .string "鼻涕……泪……\p"
    .string "我只能剥剥洋葱……\n"
    .string "鼻涕……$"

SSAnne_Kitchen_Text_IAmLeChefMainCourseIs::
    .string "没错！\n"
    .string "我就是主厨！\p"
    .string "主菜是$"

SSAnne_Kitchen_Text_SalmonDuSalad::
    .string "三文鱼色拉！\p"
    .string "不过客人们大概又会抱怨\n"
    .string "里面的鱼不好，无所谓了！$"

SSAnne_Kitchen_Text_EelsAuBarbecue::
    .string "烤鳗鱼！\p"
    .string "恐怕我的客人会发起暴动的。$"

SSAnne_Kitchen_Text_PrimeBeefsteak::
    .string "皇室牛排！\p"
    .string "不过，我的牛肉够吗？$"

