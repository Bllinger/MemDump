# MemDump

Android内存dump工具，核心思想用ptrace注入进程，然后在目标进程地址空间内，新建文件然后写入。hook代码用的古河大大的，做了适当的修改。

目前主要用于dump so文件，若有其他需要可自行下载源码修改编译

**usage：** 
将_inject和libdump.so这两个文件放入/data/data，然后执行就行
```
./_inject <pid> <libname.so> //libname 是需要dump的so文件的名称
./_inject 2393 libnative-lib.so
```

注：
* ndk版本：r10e
* cpu平台：arm-v7
* 系统：android 4.4（API 19）


最后注意记得给输出文件的目标路径加权限，最好777，不然可能会创建文件失败
