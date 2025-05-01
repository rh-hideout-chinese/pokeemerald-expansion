# Termux编译指南

## 安装Termux

在termux的[github](https://github.com/termux/termux-app/releases)中下载并安装termux

## 配置编译环境

### Termux命令部分

```bash
pkg update && pkg upgrade
pkg install vim proot
termux-chroot
pkg install proot-distro
```

重启Termux

```bash
proot-distro install ubuntu
```

### 启动Ubuntu

```bash
proot-distro login ubuntu
```

### 配置Ubuntu环境

```bash
apt update && apt upgrade
apt install build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev libfreeimage-dev python3
```

### 可选

在termux中输入

```bash
vim ~/.bashrc
```

将下面的命令写入到~/.bashrc中，后续启动termux时会自动启动ubuntu

```
proot-distro login ubuntu
```

