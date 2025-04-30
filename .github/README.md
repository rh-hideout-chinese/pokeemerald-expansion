# pokeemerald-expansion-Chinese

pokeemerald-expansion-Chinese是基于ROM Hacking Hideout的[pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion/)项目的中文汉化项目。

更改内容包括：
  - 汉化了项目中几乎所有的文本、含文字的图片(包括原版与expansion新增的部分)，并修改了与汉化后文字展示相关的代码。原版游戏脚本文本主要使用2011年发布的由漫游&TGB联合汉化的口袋妖怪绿宝石的文本。
  - 修正原汉化文本单行字数溢出换行及换行符数量超标导致的文字显示不全的问题。
  - 统一游戏内文本的译名及标点使用，专有名词及常用功能文本参照最新官方正作简体中文版译名及神奇宝贝百科的民间译名。
  - 按照绿宝石日文版还原了一部分包括标题画面、读取存档及部分细节功能的内容。

注：本项目不包含对于expansion项目的优化及新功能开发。

汉化人员名单（不分先后）：
- 字库破解及文本提取程序：卧看微尘，泡泡
- 文本整理、英文翻译及润色：Chaotix，sayseong，会飞的鱼
- 图片文字汉化及调整：兔砸博士，SKT，猫猫，Chaotix
- 日文翻译及日版功能还原：SKT
- 程序支持：明雅，墟芜，卧看微尘
- 测试BUG反馈：摆烂

感谢大家的努力与贡献！

也感谢之前于2011年发布的漫游&TGB联合汉化的绿宝石汉化版的参与人员：
飞眼，enler，胡里胡涂，ルナ，零度雨，灰米，绿叶枫，yeyezai，lazybone，雪山肥壶，信天翁，爱姿病，troy1229，夜露死苦，阿宝，lioyy，凛，酷酷的安仔，空白君，AISU，吾鱼（小黑屋）

# 以下是pokeemerald-expansion项目的Readme文件翻译（其中链接直接指向该项目，请用相对路径寻找汉化项目中的对应文件）：

## pokeemerald-expansion

pokeemerald-expansion是基于pret的[pokeemerald](https://github.com/pret/pokeemerald)反编译项目的一个***ROM改版蓝本***。***它不是一个可玩的ROM改版***，但它为ROM修改者提供了多种功能，以便他们可以创建自己的游戏，因此它本身不是用来单独游玩的。

## 我应该使用它还是原版的pokeemerald作为我的改版蓝本？

使用原版pokeemerald作为基础的主要优势是能够与其他官方的GBA《宝可梦》游戏进行战斗和交换。而pokeemerald-expansion则开箱即用地支持与自己进行战斗和交换。如果你不介意失去与原版完全兼容的能力，我们建议使用pokeemerald-expansion。否则，请使用pret的pokeemerald。你仍然可以获得pret提供的文档改进，因为我们定期合并pret的文档更改。

## 使用pokeemerald-expansion

如果你在你的改版中使用了pokeemerald-expansion，请在制作人员名单中添加RHH（Rom Hacking Hideout）。可选地，你可以列出使用的版本，这样可以帮助玩家了解可以期待哪些功能。

你可以这样表述：


基于RHH的pokeemerald-expansion 1.11.1 https://github.com/rh-hideout/pokeemerald-expansion/


***重要提示***：不要使用GitHub的“Download Zip”选项。使用这个选项将无法下载更新你的扩展版本或合并其他功能分支所需的提交历史。相反，请阅读[此指南](https://github.com/Pawkkie/Team-Aquas-Asset-Repo/wiki/The-Basics-of-GitHub)以了解如何分叉存储库并从那里本地克隆。

请按照`INSTALL.md`中的说明在你的机器上设置pokeemerald-expansion。

### 如果我已经有一个基于原版pokeemerald的项目，我可以使用pokeemerald-expansion吗？

可以！请注意，我们紧跟pret对pokeemerald的文档更新，这意味着如果你的项目有点旧，你可能会遇到需要手动解决的合并冲突。
- 如果你还没有设置远程仓库，请运行命令`git remote add RHH https://github.com/rh-hideout/pokeemerald-expansion`。
- 一旦你设置了远程仓库，请运行命令`git pull RHH master`。

这样，你将获得pokeemerald-expansion的最新版本，以及一些尚未发布到下一个补丁版本中的bug修复。

## 文档
[请点击此处访问我们的文档页面。](https://rh-hideout.github.io/pokeemerald-expansion/)

## ***如何更新我的pokeemerald-expansion版本？***

- 如果你还没有设置远程仓库，请运行命令`git remote add RHH https://github.com/rh-hideout/pokeemerald-expansion`。
- 检查你的当前版本。
  - 你可以在调试菜单的`Utilities -> Expansion Version`选项中检查。
  - 如果该选项不可用，你可能拥有的是1.6.2或更早的版本。在那种情况下，请查看[更改日志](docs/CHANGELOG.md)以确定你的版本，基于你仓库中可用的功能。
- ***重要提示***：如果你落后了几个版本，我们建议你一次更新一个小版本，而不是直接跳到最新的补丁版本（例如，1.5.3 -> 1.6.2 -> 1.7.4等等。查看在线文档网站](https://rh-hideout.github.io/pokeemerald-expansion/CHANGELOG.html)以查看每个步骤的最新版本。）
- 一旦你设置了远程仓库，请运行命令`git pull RHH expansion/X.Y.Z`，将X、Y和Z替换为你想要更新到的相应版本的数字（例如，要更新到1.11.1，请使用`git pull RHH expansion/1.11.1`）。
- ***重要提示***：如果你落后了几个版本，我们建议你一次更新一个小版本，而不是直接跳到最新的补丁版本（例如，1.5.3 -> 1.6.2 -> 1.7.4等等）
- 另外，你可以更新到扩展的未发布版本。
  - ***master（稳定版）***：它包含将在下一个补丁版本中发布的***bug修复***。要合并，请使用`git pull RHH master`。
  - ***upcoming（不稳定版，可能存在bug）***：它包含将在下一个小版本中发布的***功能***。要合并，请使用`git pull RHH upcoming`。

### 请考虑在你的项目中归功于整个贡献者名单](https://github.com/rh-hideout/pokeemerald-expansion/wiki/Credits)，因为他们都为开发这个项目付出了辛勤的努力 :)

## 谁在维护这个项目？

这个项目最初是由DizzyEgg与其他贡献者一起启动的。现在它由ROM Hacking Hideout社区中的一个团队“Expansion Senate”维护。ROM Hacking Hideout（简称RHH）是一个基于Discord的ROM修改社区，专门研究《宝可梦》ROM改版。关于项目开发的大部分讨论都在那里进行。

[点击此处加入RHH Discord服务器！](https://discord.gg/6CzjAG6GZk)

## 项目中有一个bug。我该如何让你们知道？

请在此[提交](https://github.com/rh-hideout/pokeemerald-expansion/issues)项目的任何问题，并确保在提交之前使用过滤器搜索，确认问题尚未被其他人报告。你也可以加入Discord服务器，以尝试从团队和其他服务器成员那里获得更深入的支持。

## 即使我不是ROM Hacking Hideout的成员，我也可以贡献吗？

可以！欢迎通过Pull Request进行贡献，它们将由维护者及时审查。

此外，*请遵循Pull Request模板，并随时讨论如何处理审查。***沟通是关键！***如果我们花了一些时间来审查你的PR，请不要感到气馁，我们会处理的。

## 包含了哪些功能？

- ***重要❗❗ 阅读以下内容以了解你可以切换哪些功能***：
- [战斗配置](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/battle.h)
- [宝可梦配置](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/pokemon.h)
- [物品配置](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/item.h)
- [大地图配置](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/overworld.h)
- [调试配置](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/debug.h)

- ***升级的战斗引擎***
    - Gen5+伤害计算。
    - 支持2v2野外战斗。
    - 支持1v2/2v1战斗。
    - 妖精属性（可配置）。
    - 物理/特殊/变化招式划分（可配置）。
    - 新增招式和能力，直至朱/紫。
      - 自定义大赛数据，直至剑/盾，新增招式正在开发中。（来源](https://web.archive.org/web/20240910012333/https://pokemonurpg.com/info/contests/rse-move-list/)）
    - 新增战斗机制支持：
      - 超级进化
      - 原始回归
      - 极巨化
      - Z招式
        - Gen 8+的攻击招式根据Gen 7进行威力推算。
        - Gen 8+的变化招式没有额外效果，如治愈之愿。
      - 极巨化和超极巨化
    - 初始战斗参数
      - 一系列增强（例如霸主等）
      - 设置场地。
    - 回合中速度重新计算。
    - 野外战斗中快速选择精灵球
      - 按住`R`使用方向键更改选择。
      - 按`R`使用上次选择的精灵球。
    - 逃走快捷键
    - 战斗开场更快 - 消息和动画/叫声同时发生。
    - HP减少加速。
    - 战斗调试菜单。
      - 在“战斗/背包/宝可梦/逃跑”菜单上按`Select`进入。
    - 在野生宝可梦战斗中使用AI标志的选项。
    - FRLG/Gen4+白屏时的金钱计算。
    - 可配置的经验设置
      - 捕捉时获得经验。
      - 学习装置影响全队。
      - 训练家经验。
      - 动态经验。
      - 未进化时经验加成。
      - 冻伤
        - 如果不启用配置则不会替换冻结效果，因此你可以混合搭配。
      - 会心捕获。
      - 可配置的移除徽章加成。
      - 每场战斗结束时重新计算属性。
      - 等级100的宝可梦可以获得努力值。
      - 反转对战支持。
      - 大量其他功能[在此](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/battle.h)。

- ***全面的训练家自定义***

    - 昵称、努力值（EVs）、个体值（IVs）、招式、特性、精灵球、亲密度、性格、性别、异色。
    - 自定义双打对战支持（与NPC组队）。
    - 中途的训练家信息。
    - 升级后的训练家AI
      - 考虑了最新的招式效果。
      - 新的标志选项，允许你自定义训练家的AI。
      - 更快的计算速度。
      - 可以按训练家类型指定精灵球。

- ***宝可梦涵盖第1至第9世代***

    - 简化了添加新宝可梦的过程。
    - 可以禁用不需要的宝可梦进化链。
    - 更新为DS风格的宝可梦图像。
    - 可配置的更新属性、类型、特性和蛋组。
    - 可配置的更新丰缘地区图鉴以匹配《欧米伽红宝石/阿尔法蓝宝石》。
    - 更新全国图鉴，纳入新宝可梦。
    - 宝可梦和动画可视化工具，通过在宝可梦摘要屏幕上按`Select`键访问。
    - 第四世代及以后的进化方法，并做出了一些改动：
      - 苔藓岩石、冰冷岩石和磁场位置的改动以匹配《欧米伽红宝石/阿尔法蓝宝石》。
        - 可以使用叶之石、冰之石和雷之石。
      - 好啦鱿只需达到30级即可进化。
        - 由于物理上无法同时拥有实时时钟（RTC）和陀螺仪，因此我们跳过了此要求。
      - 奇鲁莉安使用第八世代及以后的进化方法（亲密度+妖精系招式）。
      - 可以选择直接使用进化道具（如石头）。
    - 隐藏特性
      - 可以通过特性膏药获得。
      - 兼容Ghoul的DexNav分支。
    - 保留了所有性别差异。
      - 为雌性河马兽、沙河马、皮卡丘和晃晃斑自定义了雌性图标。
    - 传说宝可梦、幻之宝可梦和究极异兽拥有3项完美个体值。

- ***可自定义的形态变化表。完整方法列表[在此](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/constants/form_change_types.h)***

    - 持有道具（如骑拉帝纳/阿尔宙斯）
    - 使用道具（如花舞鸟）
      - 特定时间（如谢米）
    - 昏厥
    - 战斗开始和结束（如哲尔尼亚斯）
      - 招式改变（如苍响/藏玛然特）
    - 在特定地形战斗结束时（如百变怪）
    - 在战斗中切换（如海豚侠）
    - HP阈值（如达摩狒狒）
    - 天气（如飘浮泡泡）
    - 回合结束时（如莫鲁贝可）
    - 特定时间（如谢米）
    - 融合（如酋雷姆）

- ***孵蛋改进***

    - 需要香薰孵化的幼年宝可梦蛋现在可以直接孵化（可配置）。
    - 1级蛋（可配置）。
    - 精灵球遗传（可配置）。
    - 蛋招式传递，包括模仿香草（可配置）。
    - 使用不变石可确保100%遗传性格（可配置）
    - 第六世代及以后的特性遗传（可配置）。

- ***新世代道具。完整列表[在此](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/constants/items.h)***

    - 第六世代及以后的学习装置（可配置）
    - 破坏因子
    - 大多数第四世代及以后的战斗道具

- ***合并的功能分支（已获授权）***

    - [RHH开场动画](https://github.com/Xhyzi/pokeemerald/tree/rhh-intro-credits)由@Xhyzi制作
        - 展示我们所有人签名的小环节，体现了项目的集体努力 :)
    - [大地图调试](https://github.com/TheXaman/pokeemerald/tree/tx_debug_system)由@TheXaman制作
      - 可禁用。
      - 默认情况下，在大地图中按`R + Start`键访问。
      - ‌**附加功能**‌：
          - *清空盒子*：清空所有盒子中的宝可梦。
          - *孵化蛋*：选择队伍中的一颗蛋并立即孵化。
    - [HGSS风格宝可梦图鉴](https://github.com/TheXaman/pokeemerald/tree/tx_pokedexPlus_hgss)由@TheXaman制作
      - 可禁用。
      - ‌**附加功能**‌：
          - *支持新的进化方式*。
          - *暗色模式*。
    - [特性颜色](https://github.com/DizzyEggg/pokeemerald/tree/nature_color)摘要屏幕由@DizzyEggg制作
    - [动态多选框](https://github.com/SBird1337/pokeemerald/tree/feature/dynmulti)由@SBird1337制作
    - [SaveBlock清理](https://github.com/ghoulslash/pokeemerald/tree/saveblock)由@ghoulslash制作
    - [宝可梦跟随&扩展ID](https://github.com/aarant/pokeemerald/tree/followers-expanded-id)由@aarant制作
      - 可禁用。
      - 包括《心金/魂银》中的宝可梦跟随，包括互动功能。
      - ‌**扩展了可能的物体事件ID数量，超出255个**‌。
      - ‌**包含了动态调色板（DOWP）的实现**‌。
      - ‌**附加功能**‌：
          - *宝可梦跟随行走图更新至第八世代*。
          - *与我们的宝可梦宝可梦图像可视化工具集成，允许用户浏览宝可梦跟随及战斗图像*。

- ***其他功能***

    - 抓起宝可梦时按B键可以像官方新作中那样放下（可配置）。
    - 室内跑步（可配置）。
    - 可配置的战斗外大地图中毒伤害。
    - 可配置的标志，用于禁用野生宝可梦遭遇和训练家对战。
    - 可配置的标志，用于强制或禁用异色宝可梦。
    - 可重复使用的招式学习器（TM）（可配置）。
    - 《黑2/白2》及以后的驱虫喷雾系统，也支持《Let's Go!皮卡丘/伊布》中的香水。
    - 第六世代及以后的努力值上限。
    - 包含了pret的所有错误修复。
    - 修复了地图上的下雪天气效果。