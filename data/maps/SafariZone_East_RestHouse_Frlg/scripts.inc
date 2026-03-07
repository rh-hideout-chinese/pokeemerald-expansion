SafariZone_East_RestHouse_Frlg_MapScripts::
	.byte 0

SafariZone_East_RestHouse_EventScript_Rocker::
	msgbox SafariZone_East_Text_CaughtChanseyAllWorthwhile, MSGBOX_NPC
	end

SafariZone_East_RestHouse_EventScript_Scientist::
	msgbox SafariZone_East_Text_HowManyDidYouCatch, MSGBOX_NPC
	end

SafariZone_East_RestHouse_EventScript_BaldingMan::
	msgbox SafariZone_East_Text_TiredFromAllTheFun, MSGBOX_NPC
	end

SafariZone_East_Text_HowManyDidYouCatch::
    .string "你抓了多少？\n"
    .string "我干得精疲力竭了！$"

SafariZone_East_Text_CaughtChanseyAllWorthwhile::
    .string "我抓住了一只吉利蛋！\p"
    .string "一切努力都是值得的。$"

SafariZone_East_Text_TiredFromAllTheFun::
    .string "哇哇！\n"
    .string "我终于也从兴奋中疲倦下来了！$"

