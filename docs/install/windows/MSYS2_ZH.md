# Msys2编译指南

## 安装并配置Msys2

1. 在Msys2的[github](https://github.com/msys2/msys2-installer/releases)页面中下载.exe，下载完成后打开并安装

2. 安装后进入Msys2安装目录，运行mingw64.exe

3. 执行下面的命令以安装需要的依赖

   ```bash
   pacman -S mingw-w64-x86_64-arm-none-eabi-toolchain mingw-w64-x86_64-toolchain mingw-w64-x86_64-libpng mingw-w64-x86_64-freeimage mingw-w64-x86_64-python make
   ```

## 编译

使用cd命令进入存放源码的目录，输入make，等待编译完成即可