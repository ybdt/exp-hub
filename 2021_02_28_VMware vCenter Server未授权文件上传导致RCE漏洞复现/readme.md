# 0x00 软件介绍
VMware vSphere是一个类似MS Office的套件，它包含VMware ESXi、VMware vCenter Server、VMware vSphere Client  
VMware ESXi：安装在物理机上，负责虚拟化服务  
VMware vCenter Server：通常安装在虚拟机上，负责管理虚拟机  
VMware vSphere Client：通常安装在管理员的笔记本上面，负责连接到VMware vCenter Server来管理虚拟机，或直接管理虚拟机  
通常部署在内网中  
具体关于它们都是干什么的，可参考这篇文章https://blog.csdn.net/eastyell/article/details/91581878

# 0x01 复现环境
###### 使用本地搭建的环境：  
VMware Workstation 16 Pro + VMware-VMvisor-Installer-7.0.0-15843807.x86_64.iso + VMware-VCSA-all-7.0.0-15952498.iso  
复现版本：  
VMware vCenter Server 7.0.0  
环境搭建过程：  
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
