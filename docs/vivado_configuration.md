# 体系结构I 环境配置参考

## Vivado 安装指引

（以下操作基于kubuntu 20.04 LTS）

1. 获取安装包(2018.2: https://jbox.sjtu.edu.cn/l/noXqCD 2020.1可从官网获得)

2. 对于2018.2，使用gui安装即可；对于2020.1，执行以下命令

    ```
    sudo ./xsetup -b ConfigGen
    ```

    ```
    sudo ./xsetup --agree XilinxEULA,3rdPartyEULA,WebTalkTerms --batch Install --config /root/.Xilinx/install_config.txt
    ```

    （第一条命令生成config，根据环境不同第二行命令中config路径可能不同，请参考第一行命令输出）

    一般通过执行/tools/Xilinx/Vivado/2020.1/bin/vivado来打开vivado

3. (Optional) 创建快捷方式：在~/Desktop/（桌面）或/usr/share/applications/（快捷启动）下建立`vivido.desktop`文件，内容为（以下为2020.1示例，2018.2自行对照，2018.2安装目录通常为/opt/而非/tools/）

    ```
    [Desktop Entry]
    Encoding=UTF-8
    Type=Application
    Name=Vivado 2020.1
    Comment=Vivado 2020.1
    Icon=/tools/Xilinx/Vivado/2020.1/doc/images/vivado_logo.png
    Exec={path to your launch script/exectuable}                                             
    ```

    （kde方法，不保证gnome、xfce下可用，若不可用建议自己查询对应方法）

### 可能问题

1. 出现如下错误

    ```
    terminate called after throwing an instance of 'std::runtime_error'
      what():  locale::facet::_S_create_c_locale name not valid
    /opt/Xilinx/Vivado/2016.4/bin/loader: line 179:  2309 Aborted                 (core dumped) "$RDI_PROG" "$@"
    ```

    解决方法：将环境改变至en_US

    在终端执行以下代码以改变环境变量

    ```
    export LC_ALL="en_US.UTF-8"
    ```

    若需要这样解决，通常需要创建launch script，并在script里执行export命令后再启动vivado

    

2. ```
    application-specific initialization failed: couldn't load file "librdi_commontasks.so": libtinfo.so.5: cannot open shared object file: No such file or directory
    ```

    解决方法：安装libtinfo-dev，再执行

    ```
    sudo ln -s /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.5
    ```

3. 激活：使用vivado2037.llc

    使用方法见https://www.cnblogs.com/maskerk/p/7350182.html

## riscv-toolchains 安装

1. 获取repo：

    ```
    git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
    ```

    （注：repo较大，直接clone建议在稳定网络环境下通过梯子clone）

2. 安装必要库，以下为原repo中提示：

    Several standard packages are needed to build the toolchain.

    On Ubuntu, executing the following command should suffice:

    ```
    $ sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
    ```

    On Fedora/CentOS/RHEL OS, executing the following command should suffice:

    ```
    $ sudo yum install autoconf automake python3 libmpc-devel mpfr-devel gmp-devel gawk  bison flex texinfo patchutils gcc gcc-c++ zlib-devel expat-devel
    ```

    On Arch Linux, executing the following command should suffice:

    ```
    $ pacman -Syyu autoconf automake curl python3 mpc mpfr gmp gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib expat
    ```

3. 安装：执行

    ```
    ./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32
    ```

    ```
    sudo make
    ```

    ### 可能问题

    1. 提示缺包

        按照对应错误信息安装所需包

    2. 出现

        ```
        checking for sysdeps preconfigure fragments... aarch64 alpha arm csky hppa i386 m68k microblaze mips nios2 powerpc riscv glibc requires the A extension
        make: *** [Makefile:242：stamps/build-glibc-linux-rv32i-ilp32] error 1
        ```

        解决：使用

        ```
        ./configure --prefix=/opt/riscv --with-arch=rv32ia --with-abi=ilp32
        ```

        进行configuration

    3. 网上找到了solution，但不起作用

        `make clean`

