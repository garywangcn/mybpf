# 功能
mybpf是一个可以在用户态、嵌入式、内核ko中都可以运行的一套ebpf框架。支持多种方式运行ebpf：
  1. 可以以字节码方式解释执行
  2. 可以JIT成本机指令运行
  3. 可以AOT成指定目标指运行(Arm64和X86-64)

# 特点
mybpf的特点  
  1. 既可以JIT，也可以AOT  
  2. mybpf runtime很轻量，最精简的bare runtime实现不到100行C代码  
  3. 可以AOT生成两种不同的文件格式，Bare格式极度精简但特性较少，SPF格式则支持的特性较多  
  4. 支持Verifier、MAP、子函数调用、回调函数、全局变量  
  5. 内置部分系统helper，支持自定义helper  

# 架构
mybpf主要分为两部分： 工具 + runtime。  
工具部分支持JIT、AOT、解释器、dump、verifier 等功能  
runtime运行AOT后的文件  

选择runtime和工具分离的架构，主要原因是为了方便可移植，并同时还有以下好处：  
1. AOT文件格式非常简单(相比ELF)，处理它的runtime代码非常少。又因为runtime代码非常精简，所以非常容易移植  
2. 占用存储空间很少(Flash、RAM需求都很少)，需要的代码段资源也很少，这对资源紧张的嵌入式系统很友好  
3. runtime不用频繁更新，大多数升级、功能演进工作在工具库中完成

附：不同格式文件大小:  
![image](https://github.com/windgorain/mybpf/assets/35138361/7a62a067-4d74-49cc-8cb9-3735041291e5)

# AOT格式
AOT当前支持两种目标指令集：ARM64和X86-64，其它还待增加。  
支持输出两种不同的文件格式：SPF格式和BARE格式。  
Bare格式较简单，支持bss全局变量(不支持data, rodata),  支持内部子函数、支持helper。不支持map。  
SPF格式是TLV格式，比Bare格式复杂(但也比elf要简单)，其runtime不到一千行，支持全局变量(bss、data、rodata)、子函数、map、helper。  

# Helper
分为四种不同类型Helper： Base、Sys、User、Temp  
Base (0-1,000,000) ：ebpf的官方Helper，如6号bpf_trace_printk。预留一百万个范围给官方helper的空间  
Sys [1,000,000 - 2,000,000)： 通用的系统helper，如malloc、free，strcpy等。这些helper需要小心使用  
User [2,000,000 - 3,000,000):  用户可自定义的全局Helper  
Temp [3,000,000 - 4,000,000): 用户可自定义的临时Helper  

# 安全性
mybpf的安全性依赖可选择开启的verifier。在解释、JIT、AOT之前，先对ebpf字节码进行安全性验证，验证通过后，再继续执行、JIT、AOT操作。  

# SPF的支持
SPF比BARE格式要复杂，其runtime也更为复杂，移植的代价也会更高一些(但依然比直接支持ELF文件的移植要简单)。  
那么有没有更好的办法支持SPF呢。答案是肯定的。  
首先，移植BARE格式的Runtime到目标系统上，然后再加载spf_loader.bare文件(不需要移植其Runtime)，它会初始化SPF环境，并接受SPF文件的进一步加载。这样，只需要一个极简单的Bare Runtime + spf的Bare文件即可支持SPF。  
再进一步，还可以加载ebpf_loader.spf，进而支持在目标环境上直接解释、JIT运行ebpf文件。  

# 热升级
热升级分为几种情况：  
  1. APP的热升级：这是ebpf框架原生支持的，可以随时加载、卸载、替换ebpf文件到内核。同样，mybpf也可以很方便对APP进行加载、卸载和升级。但需要注意的是，如果使用了非base helper的危险性helper，如malloc可能会造成内存泄露。  
  2. EBPF环境和SPF环境的热升级：可以热升级EPBF、SPF的运行环境，但需要注意的是，这会导致所有APP的卸载，热升级后需要重新加载这些APP。  
  3. 不支持BARE环境的热升级，BARE环境当前是直接内嵌到目标系统，不支持热升级。当然，大多数情况下它也不需要升级。  

# 性能测试
测试环境:  
MacBook Pro  芯片：Apple M2 Pro  macOS：14.2.1   

测试方法： 计算Fibonacci，使用time命令计算消耗时间  

测试结果:  
本地指令执行：  
gcc -O3 fib.c  
time ./a.out 10000000000  
3.72s user 0.00s system 99% cpu 3.751 total  
3.74s user 0.00s system 98% cpu 3.793 total  

解释执行:  
time ./runbpf run file fibonacci.o -p 10000000000
91.65s user 0.01s system 99% cpu 1:32.14 total

JIT执行:  
time ./runbpf run file fibonacci.o -p 10000000000 -j  
2.89s user 0.00s system 99% cpu 2.908 total  
2.89s user 0.00s system 99% cpu 2.914 total  

AOT成SPF格式执行:  
./runbpf con sim -j -m 4 fibonacci.o -o fibonacci.spf  
time ./runbpf run file fibonacci.spf -p 10000000000  
2.89s user 0.00s system 99% cpu 2.911 total  
2.89s user 0.00s system 99% cpu 2.908 total  

AOT成BARE格式执行:  
./runbpf con bare -j -m 4 fibonacci.o -o fibonacci.bare  
time ./runbpf run bare fibonacci.bare -p 10000000000  
2.89s user 0.00s system 99% cpu 2.910 total  
2.89s user 0.00s system 99% cpu 2.907 total  

# 已实验环境
已经尝试在多种不同环境移植并运行，包括：  
Linux用户态(Centos/Ubuntu)  
Linux内核态  
Macos用户态 (Intel CPU 笔记本、M1笔记本、M2笔记本)  
Windows用户态  
嵌入式(uboot + qemu)  
Openwrt (Newifi2)  
树莓派 (zero 和 2B+)  
华为手机 (P20+Termux)  

# 测试展示
Linux内核：  
![KBCM1vnTKk](https://github.com/windgorain/mybpf/assets/35138361/880a3a22-2a07-45b1-a495-234095fd2712)
![TtDGHepWlM](https://github.com/windgorain/mybpf/assets/35138361/366fdb65-c9ac-4752-866c-ba48f1b3ffca)

Uboot：  
![img_v3_028f_3492d659-26c0-4d64-ba7e-7c1a0d54f70g](https://github.com/windgorain/mybpf/assets/35138361/2842b492-0960-4033-b62f-92424ad2e51d)

MacOS：  
![img_v3_028f_cd5a074f-8457-4308-b7db-d4ac7f6b81fg](https://github.com/windgorain/mybpf/assets/35138361/4a781dfc-a6b6-4acc-9707-1c95dd4d7405)


# 目录mybpf
  是AOT编译器代码所在目录  
  
# 目录runtime
  是runtime代码目录  

# 编译mybpf
cd mybpf  
这里有两个build_xxx.sh文件，分别是不同环境下的编译脚本  

在MACOS机器上  
./build_macos.sh  

在Linux机器上  
./build_linux.sh  

编译出 build/out/tool/runbpf 文件 

# 编译runtime
  cd runtime  
  执行对应环境的编译脚本 (分别为build_linux.sh 和 build_macos.sh)  
  编译出 build/out/example/user_example  

# 用法
  编译为bare格式  
    runbpf convert bare -j -m 4 ebpf文件名 -o 输出文件名  
  编译为SPF格式  
    runbpf convert simple -j -m 4 ebpf文件名 -o 输出文件名  
  运行  
    runbpf run bare bare文件名  
    或者  
    runbpf run file SPF文件名

# 示例
cd runtime/test  
runbpf con bare -j -m 4 test_sub_prog.o  
user_example test_sub_prog.o.bare  



  
