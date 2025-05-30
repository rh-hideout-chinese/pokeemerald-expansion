FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
    .string "没人肯相信我，但我确实在天空中\n看到了巨大的宝可梦。\p它好像在辗转着\n飞向131号水路。\p话说……\n唔唔……你身上，呃……好像有焦味。\p你刚从火山或什么地方来吗？$"

FortreeCity_Text_SomethingBlockingGym:
    .string "我想去宝可梦道馆，\n但有东西堵了路。\p在120号道路训练了\n那么久，现在却……$"

FortreeCity_Text_ThisTimeIllBeatWinona:
    .string "我带着我漂亮又可爱的\n宝可梦一起来了。\l这一次，我一定要打败娜琪。$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
    .string "树木吸收了渗进地面的雨水，\n慢慢长大……\p我们茵郁市就是在\n水和土地上建造起来的。$"

FortreeCity_Text_EveryoneHealthyAndLively:
    .string "城市中的房子\n都建在树上。\p也许正因这种生活方式，\n大家都很健康，充满活力。\p哈，我也一样——我感觉\n好像年轻了30岁。$"

FortreeCity_Text_BugPokemonComeThroughWindow:
    .string "住在树顶上\n没什么问题，\p但有时虫属性宝可梦会\n从窗户爬进来，\l经常吓人一跳。$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
    .string "我听说，有些宝可梦\n会在交换中进化！$"

FortreeCity_Text_SomethingUnseeable:
    .string "有什么看不见的东西挡在路上。$"

FortreeCity_Text_UnseeableUseDevonScope:
    .string "有什么看不见的东西挡在路上。\p要使用得文侦测镜吗？$"

FortreeCity_Text_UsedDevonScopePokemonFled:
    .string "{PLAYER}使用得文侦测镜。\p看不见的宝可梦\n现出了原形！\p受惊的宝可梦溜掉了！$"

FortreeCity_Text_CitySign:
    .string "这里是茵郁市。\n“与自然嬉戏的树上城市。”$"

FortreeCity_Text_GymSign:
    .string "茵郁市宝可梦道馆\n馆主：娜琪\p“翱翔在世界的\n鸟宝可梦训练家！”$"

