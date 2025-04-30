# Windows WSL指南

## 选择WSL版本

- 如果你想将项目存放在Windows系统中，优先选择WSL1。
- 如果你想获得最佳性能并尽量减少 Windows 干扰项目编译的问题，请使用 WSL2 并将项目存放在 Linux 文件系统中（位于 ~/ 目录下）。

## 安装 WSL

1. 以管理员模式打开 [Windows Powershell](https://i.imgur.com/QKmVbP9.png)， 执行下面的命令 (鼠标右键或按下Shift+Insert以粘贴到Powershell)。
	- WSL1    

        ```powershell
        wsl --install -d Ubuntu --enable-wsl1
        ```
   
	- WSL2

        ```powershell
        wsl --install -d Ubuntu
        ```

2. 等待命令完成后重启你的电脑

### WSL1

3. 重启后以管理员模式打开Powershell， 执行下面的命令将Ubuntu版本设置为WSL1。

    ```powershell
    wsl --set-version Ubuntu 1
    ```

### WSL2

3. 重启后以管理员模式打开Powershell， 执行下面的命令将Ubuntu版本设置为WSL2。

    ```powershell
    wsl --set-version Ubuntu 2
    ```

    <details>
        <summary><i>注意...</i></summary>

    >   重启后WSL可能会自动启动，但这并不会影响什么。
    </details>

### 查看WSL版本

4. 以管理员模式打开Powershell，执行下面的命令

   ```powershell
   wsl --list -v
   ```
## 安装依赖项

注意事项:
- WSL中复制/粘贴方法
    - **鼠标右键** （选中后右键单击复制，未选中内容时右键单击粘贴）
    - **Ctrl+Shift+C/Ctrl+Shift+V** （右键单击标题栏，确认已勾选"使用Ctrl+Shift+C/V作为复制/粘贴快捷键"）。
- 执行部分命令时需要输入WSL用户密码或手动确认。在需要确认时根据提示输入WSL用户密码或yes/y即可

1. 启动**Ubuntu**（ 比如在搜索中启动）。
2. 第一次启动WSL/Ubuntu时将会自动完成安装。等待WSL/Ubuntu安装结束后，需要设置用户名和密码
    <details>
        <summary><i>Note...</i></summary>

    >   输入密码时WSL不会显示输入的内容，但它仍在正常获取输入的字符。
    </details>

3. 通过下面的命令更新WSL，这可能需要一段时间：

    ```bash
    sudo apt update && sudo apt upgrade
    ```

4. 执行下面的命令以安装编译pokeemerald-expansion的依赖项：

    ```bash
    sudo apt install build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev libfreeimage-dev python3
    ```

## 在WSL1中设置源码存放位置

Windows不能直接访问WSL的文件，但WSL可以直接访问Windows文件。因此可以将文件存放在Windows系统中。

假设你想将pokeemerald Expansion存放在**C:\Users\\_\<user>_\Desktop\decomps**目录。首先确认这个文件夹存在。然后输入下面的命令进入该文件夹（**\<user>**指Windows系统用户名）：

```bash
cd /mnt/c/Users/<user>/Desktop/decomps
```

<details>
    <summary><i>注意……</i></summary>

>   1: Windows C:\ 盘在WSL中对应/mnt/c/。
>   2: 如果路径中包含空格，则必须用"将整个路径包围起来，例如`"/mnt/c/users/<user>/Desktop/decomp folder"`。
>   3: Windows路径是大小写不敏感的，所以无需注意大小写问题。
</details>

## 在WSL2中设置源码存放位置

Windows不能直接访问WSL的文件，但WSL可以直接访问Windows文件。但在WSL2中访问Windows文件速度很慢，因此最好将文件存放在WSL2中。
要从 Windows 访问 WSL中的文件，你需要在文件资源管理器中将 WSL 文件系统作为网络附加存储打开，它应该位于左侧边栏的底部，显示为“Linux”。

在WSL中运行下面的命令以创建一个文件夹用于存放pokeemerald-expansion（如果这个文件夹不存在）

```bash
cd ~/
mkdir decomps
```

运行下面的命令进入存放pokeemerald-expansion的文件夹

```bash
cd ~/decomps
```