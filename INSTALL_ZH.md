
# 安装说明
每个支持的操作系统的安装说明可在 `docs/install/` 目录下的对应子目录中找到。
各个系统的链接列在各自的标题下。
本文件仅包含对每个支持系统的简要介绍。
如果遇到问题，请在 Discord 上寻求帮助（见 [README_ZH.md](README_ZH.md)）。

完成对应操作系统的安装说明后，继续阅读 [构建 pokeemerald-expansion](#构建-pokeemerald-expansion)。

## Windows
**Windows 需要以下系统之一来构建项目**

**注意事项**：由于 Microsoft 已停止对 Windows 7 和 Windows 8 的官方支持，一些维护者不再维护这两个系统的安装说明。因此，这些说明可能在未来失效，并且修复速度会慢于 Windows 10/11 的相关说明。

在 Windows 上，可以使用以下系统构建项目：
- WSL2，最快
- WSL1，速度是 WSL2 的七分之一
- Msys2，速度是 WSL2 的二十分之一（**注意**：当前在 pret 上游版本中已损坏）
- Cygwin，速度是 WSL2 的三十分之一（**注意**：当前在 pret 上游版本中已损坏）

**注意**：仅推荐使用 WSL 系统。

[WSL 安装说明](docs/install/windows/WSL_ZH.md)

[Msys2 安装说明](docs/install/windows/MSYS2_ZH.md)

[Cygwin 安装说明](docs/install/windows/CYGWIN.md)

## Linux
该项目可在任意 Linux 发行版上构建。
已有说明的发行版：
- [Ubuntu](docs/install/linux/UBUNTU.md)
- [Debian](docs/install/linux/DEBIAN.md)
- [Arch Linux](docs/install/linux/ARCH_LINUX.md)
- [NixOS](docs/install/linux/NIXOS.md)

其他发行版请参考 [通用说明](docs/install/linux/OTHERS.md)。

## Mac
在启用测试系统时需要额外考虑一些事项。

[Mac 安装说明](docs/install/mac/MAC_OS.md)

## ChromeOS
仅在基于 x86_64 的系统上测试过。

[Chrome OS 安装说明](docs/install/chromeos/CHROME_OS.md)

# 构建 pokeemerald-expansion
按以下步骤构建 `pokeemerald-expansion` 项目。
1. 进入你想保存项目的目录，注意系统的路径限制。
2. 使用 `git` 下载 `pokeemerald-expansion`

    ```console
    git clone https://github.com/rh-hideout-chinese/pokeemerald-expansion
    ```
3. 进入新下载的项目目录。

    ```console
    cd pokeemerald-expansion
    ```
4. 构建项目。

    ```console
    make
    ```
5. 如果一切顺利，你应该能看到类似下面这样的输出。

    ```console
    arm-none-eabi-ld: warning: ../../pokeemerald.elf has a LOAD segment with RWX permissions
    Memory region         Used Size  Region Size  %age Used
               EWRAM:      243354 B       256 KB     92.83%
               IWRAM:       30492 B        32 KB     93.05%
                 ROM:    26072244 B        32 MB     77.70%
    cd build/modern && arm-none-eabi-ld  -T ../../ld_script_modern.ld --print-memory-usage -o ../../pokeemerald.elf <objs> <libs> | cat
    tools/gbafix/gbafix pokeemerald.elf -t"POKEMON EMER" -cBPEE -m01 -r0 --silent
    arm-none-eabi-objcopy -O binary pokeemerald.elf pokeemerald.gba
    tools/gbafix/gbafix pokeemerald.gba -p --silent
    ```
    构建好的 ROM 文件将保存在目录中，名为 `pokeemerald.gba`。

# 构建指南

## 并行构建

更多信息请参见 [GNU 文档](https://www.gnu.org/software/make/manual/html_node/Parallel.html) 和 [Stack Exchange 线程](https://unix.stackexchange.com/questions/208568)。

为加快构建速度，先通过以下命令获取 `nproc` 的值：
```bash
nproc
```
然后通过以下命令进行并行构建：
```bash
make -j<由 nproc 返回的数字>
```
将 `<由 nproc 返回的数字>` 替换为实际数值。

macOS 不支持 `nproc`。可使用替代命令 `sysctl -n hw.ncpu`（参考 [Stack Overflow 线程](https://stackoverflow.com/questions/1715580)）。

### 其他工具链

若使用非 devkitARM 工具链构建，请通过环境变量 `TOOLCHAIN` 覆盖路径，该路径必须包含 `bin` 子目录。
```bash
make TOOLCHAIN="/path/to/toolchain/here"
```
例如：
```bash
make TOOLCHAIN="/usr/local/arm-none-eabi"
```
要使用此工具链构建 `modern` 目标，还需存在 `lib`、`include` 和 `arm-none-eabi` 子目录。

### 带调试信息的构建

使用现代工具链构建带有调试符号和优化设置的 **pokeemerald.elf**：
```bash
make debug
```

# 附加工具推荐

* [porymap](https://github.com/huderlem/porymap)：用于查看和编辑地图
* [poryscript](https://github.com/huderlem/poryscript)：用于脚本编写（[VS Code 扩展](https://marketplace.visualstudio.com/items?itemName=karathan.poryscript)）
* [Tilemap Studio](https://github.com/Rangi42/tilemap-studio)：用于查看和编辑图块地图
