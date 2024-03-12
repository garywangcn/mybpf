# 功能
  1. 在用户态运行ebpf程序  
  2. 将ebpf程序AOT编译成SPF(simple bpf format)，或者Bare(更简单的格式)，运行在目标机器上  

# 目录mybpf
  是AOT编译器代码所在目录  
  
# 目录runtime
  是运行Bare格式的示例  

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



  
