# poc-hub
此项目源于要参加一场线下的CTF决赛，由于断网，故需要大量本地poc，考虑到也可为日后的渗透测试工作提供便利  
当前仓库没有漏洞分析只有POC

漏洞复现模板如下：
```
# 0x00 软件介绍
git：分布式版本控制系统

# 0x01 复现环境
使用环境：攻防世界中的环境  
复现版本：无

# 0x02 环境搭建
无

# 0x03 利用条件
无

# 0x04 影响版本
无

# 0x05 漏洞复现
攻击环境：kali_x64_en-us

git clone https://github.com/lijiejie/GitHack  
cd ./GitHack-master  
python ./GitHack.py http://124.126.19.106:31232/.git/  
如下图  
![image](./0.png)  
![image](./1.png)  

# 0x06 踩坑记录
无

# 0x07 参考链接
无
```
