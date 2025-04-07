.set LOCALID_STAIR_GUARD, 2

RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
    .string "您好，欢迎来到\n得文公司。\p我们公司发明\n改变人们生活的药品和道具。$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
    .string "我们的一个调查员被人\n把很重要的包裹抢走了。$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
    .string "哎，那是风速鞋！\n那也是我们的产品！\p每次看到别人使用我们的发明，\n我都会很高兴。$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
    .string "被偷走的包裹…\p虽然确实很重要，\n但也不是所有人都会使用的东西。\p我看那个强盗\n没那么聪明。$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
    .string "听说被抢走的得文的包裹\n找回来了。$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
    .string "对不起，\n无关人士请勿入内。$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
    .string "说什么傻话，\n谁会抢我们的东西？$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
    .string "您好！\n随时欢迎您来参观！$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
    .string "玻璃箱子里展示着\n岩石和金属的样品，\p上面有张卡片上\n写了些什么…\p“得文公司创立时\n仅仅是一家以采石为业的小公司，\p同时也利用沙子中的\n铁屑炼铁。\p得文从一个微小的\n原材料处理公司起家，\p现在已发展成为一个开发出的产品\n覆盖很多工业领域的大型制造商。”$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
    .string "玻璃展示柜里放了些\n产品的原型和试验品。\p有张卡片上写着说明…\p“除工业产品外，\n得文如今也开发\l日常用品与药品。\p近年来，得文致力于\n为宝可梦训练师开发包括\l精灵球和口袋领航员系统等一系列工具。”$"

