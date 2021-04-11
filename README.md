# 0x00 项目宗旨
本项目专注于更新可武器化的利用代码及批量脚本，不含漏洞分析

# 0x01 法律法规
该项目仅供合法的渗透测试使用或爱好者参考学习，请各位遵守《中华人民共和国网络安全法》以及相应地方的法律，禁止使用该项目进行违法操作，否则自行承担相关责任！

# 0x02 复现模板
```
# 0x00 软件介绍
JumpServer：一款在中国流行的开源堡垒机

# 0x01 复现环境
复现环境：本地环境 centos7 x64  
复现版本：JumpServer v2.6.1  
环境搭建：  
1、使用官方提供的v2.6.1的quick_start.sh安装后，竟然后v2.6.2，这个坑真是无语了，使用知识星球师傅提供的安装脚本，安装后是v2.6.1（这个安装脚本执行后可能会报错，多试几次）  
2、执行quick_start.sh后，一路默认即可  
3、安装完成后需要切换到/opt/jumpserver-installer-v2.6.1/下执行jmsctl.sh，直接使用绝对路径会报错  
4、需要开启iptables，否则报错

# 0x02 利用条件
无

# 0x03 影响版本
JumpServer < v2.6.2  
JumpServer < v2.5.4  
JumpServer < v2.4.5

# 0x04 漏洞复现
攻击环境：kali x64  
chrome下安装扩展：https://chrome.google.com/webstore/detail/websocket-test-client/fgponpodhbmadfljofbimhhlengambbn/related  
使用如下payload：  

如下图，红色圈出的部分即为读取到的远程服务器上的日志内容  
![image](./a1.png)

如下图，红色圈出的部分即为服务器上的日志内容  
![image](./a0.png)

# 0x05 批量脚本
无

# 0x06 参考链接
https://articles.zsxq.com/id_5raonmuwqrru.html
```
