# 功能
mybpf是一个可以在用户态、嵌入式、内核ko中都可以运行的一套ebpf框架。支持多种方式运行ebpf：  
  1. 可以以字节码方式解释执行  
  2. 可以JIT成本机指令运行  
  3. 可以编译为BARE和SPF格式文件运行  

# 特点
mybpf的特点  
  1. BARE和SPF格式文件非常小，占用空间小  
  2. mybpf runtime很轻量，最精简的bare runtime实现不到100行C代码  
  3. 支持Verifier、MAP、子函数调用、回调函数、全局变量  
  4. 内置部分系统helper，支持自定义helper  

# 架构
mybpf主要分为两部分： 编译工具 + runtime。  
编译工具支持将ebpf文件编译为SPF/BARE文件  
runtime负责运行SPF/BARE文件  

# 文件格式
当前支持两种目标指令集：ARM64和X86-64，其它还待增加。  
支持输出两种不同的文件格式：SPF格式和BARE格式。  
BARE格式较简单，支持bss全局变量(不支持data, rodata),  支持内部子函数、支持helper。不支持map。  
SPF格式比BARE格式复杂(但也比elf要简单)，支持全局变量(bss、data、rodata)、子函数、map、helper。  

SPF/BARE格式文件的好处:  
1. 相比ELF, mybpf的文件格式非常简单，这使得处理这种格式的runtime代码非常少。  
2. 因为runtime代码非常精简，所以非常容易到处移植  
3. 占用存储空间很少(Flash、RAM需求都很少)，需要的代码段资源也很少，这对资源紧张的嵌入式系统很友好  
4. 简洁的runtime不用频繁更新，大多数的功能升级、演进工作在编译工具中完成  

附：不同格式文件大小:  
![image](https://github.com/windgorain/mybpf/assets/35138361/7a62a067-4d74-49cc-8cb9-3735041291e5)

# runtime说明
| 名称  | 目录 | 说明 |
| --- | --- | --- |
| bare_cmd | mybpf/src/spf_runtime/bare_cmd | 运行BARE文件 |
| bare_interactive | mybpf/src/spf_runtime/bare_interactive | 以交互模式运行BARE文件 |
| bare_spf | mybpf/src/spf_runtime/bare_spf | 以交互模式运行SPF文件 |
| mini | runtime/mini | 非常小的bare runtime |
| uboot | runtime/uboot | 支持在uboot上运行 |

# 性能测试
测试环境:  
MacBook Pro  芯片：Apple M2 Pro  macOS：14.2.1   

测试方法： 计算Fibonacci，使用time命令计算消耗时间  

测试结果:  
本地指令执行：  
gcc -O3 fib.c  
time ./a.out 10000000000  
执行两次结果  
3.72s user 0.00s system 99% cpu 3.751 total  
3.74s user 0.00s system 98% cpu 3.793 total  

解释执行:  
time ./runbpf run file fibonacci.o -p 10000000000  
91.65s user 0.01s system 99% cpu 1:32.14 total  
可以看出解释执行性能很低，需要90多秒

JIT执行:  
time ./runbpf run file fibonacci.o -p 10000000000 -j  
执行两次结果:  
2.89s user 0.00s system 99% cpu 2.908 total  
2.89s user 0.00s system 99% cpu 2.914 total  

编译成SPF格式执行:  
./runbpf con sim -j -m 4 fibonacci.o -o fibonacci.spf  
time ./runbpf run file fibonacci.spf -p 10000000000  
执行两次结果:  
2.89s user 0.00s system 99% cpu 2.911 total  
2.89s user 0.00s system 99% cpu 2.908 total  

编译成BARE格式执行:  
./runbpf con bare -j -m 4 fibonacci.o -o fibonacci.bare  
time ./runbpf run bare fibonacci.bare -p 10000000000  
执行两次结果:  
2.89s user 0.00s system 99% cpu 2.910 total  
2.89s user 0.00s system 99% cpu 2.907 total  

# 已实验环境
已经尝试在多种不同环境移植并运行，包括：  
Linux用户态(Centos/Ubuntu)  
Linux内核态  
Macos用户态 (Intel CPU 笔记本、M1笔记本、M2笔记本)  
Windows用户态  
嵌入式(uboot + qemu)  
Openwrt (Newifi2+解释器)  
树莓派 (2B+)  
华为手机 (P20+Termux)  

# 测试展示
Linux内核：  
![KBCM1vnTKk](https://github.com/windgorain/mybpf/assets/35138361/880a3a22-2a07-45b1-a495-234095fd2712)
![TtDGHepWlM](https://github.com/windgorain/mybpf/assets/35138361/366fdb65-c9ac-4752-866c-ba48f1b3ffca)

Uboot：  
![img_v3_028f_3492d659-26c0-4d64-ba7e-7c1a0d54f70g](https://github.com/windgorain/mybpf/assets/35138361/2842b492-0960-4033-b62f-92424ad2e51d)

MacOS：  
![img_v3_028f_cd5a074f-8457-4308-b7db-d4ac7f6b81fg](https://github.com/windgorain/mybpf/assets/35138361/4a781dfc-a6b6-4acc-9707-1c95dd4d7405)


# 编译mybpf
cd mybpf  
这里有两个build_xxx.sh文件，分别是不同环境下的编译脚本  

在MACOS机器上  
./build_macos.sh  

在Linux机器上  
./build_linux.sh  

编译结果在: build/out/  

# 用法
## 编译  
  编译为BARE格式  
    runbpf convert bare ebpf文件名 -o 输出文件名  
  编译为SPF格式  
    runbpf convert simple -j ebpf文件名 -o 输出文件名  

## 执行 
  运行BARE格式文件:  
    runbpf run bare bare文件名  
  运行spf格式文件:  
    runbpf run file SPF文件名  

## runtime
### bare_cmd
  bare_cmd是以命令行方式执行BARE文件的runtime  
  用法:  bare_cmd file.bare  
  file.bare: 文件名  

### bare_interactive
  bare_interactive是交互模式的 bare runtime  

### bare_spf
  bare_spf是交互模式的runtime，依赖 spf_loader.bare 文件  
  用法:  
将bare_spf 和 spf_loader.arm64.bare spf_loader.x64.bare放在一起  
执行bare_spf，注意根据自己环境选择对应的spf_loader:  ./bare_spf spf_loader_x64.bare  
加载spf文件:  load file instance_name file.spf  
卸载spf文件: unload instance instance_name  
卸载所有spf文件: unload all  
触发cmd执行: testcmd

# 使用示例
```
cd mybpf

./build_mac.sh 或者 ./build_linux.sh

cd build/out/spf_runtime
cp ../../../loader/*.bare ./
cp ../../../example/ulc/test/*.o ./

../tool/runbpf con bare test_sub_prog.o -o test_sub_prog.bare
./bare_cmd test_sub_prog.bare

../tool/runbpf con simple test_func_ptr_global.o -o test_func_ptr_global.spf -j
./bare_spf spf_loader.x64.bare
> load file test test_func_ptr_global.spf
> testcmd
> quit

```

# 编写APP 示例
cd example/ulc/test  
创建 hello_world.c, 输入以下内容:  
```
#include "utl/ulc_user.h"

SEC("tcmd/hello_test")
int main()
{
    printf("Hello world!! \n");
    return 0;
}
```

编译成ebpf字节码文件:  
```
clang -O2 -I ../../../h -target bpf -c hello_world.c  -D IN_ULC_USER  
```


