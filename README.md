# poc-hub
此项目源于要参加一场线下的CTF决赛，由于断网，故需要大量本地poc，考虑到也可为日后的渗透测试工作提供便利  
当前仓库没有漏洞分析只有POC

漏洞复现模板如下：
```
# 0x00 软件介绍
基于ThinkPHP 3.2.3，让开发者更方便的一款开发框架

# 0x01 复现环境
使用环境：本地搭建的环境  
复现版本：ThinkCMF X2.2.3

# 0x02 环境搭建
靶机环境：win10_1909_pro_x64_zh-chs

下载ThinkCMF X2.2.3，直接放到phpstudy的目录下，访问/ThinkCMFX/，根据提示操作即可

# 0x03 利用条件
无

# 0x04 影响版本
ThinkCMF X1.6.0  
ThinkCMF X2.1.0  
ThinkCMF X2.2.0  
ThinkCMF X2.2.1  
ThinkCMF X2.2.2  
ThinkCMF X2.2.3

# 0x05 漏洞复现
攻击环境：win10_1909_pro_x64_zh-chs（在英文的kali系统下访问会提示“just a demo for multi lang user! LANG IS en-us;”）

任意文件写入漏洞复现：  
浏览器下访问  
某某地址  
访问test.php，可以看到phpinfo已经加载出来
![image](./0.png)

任意文件包含漏洞复现：  
浏览器下访问  
某某地址  
可以看到成功包含了README.md
![image](./1.png)

# 0x06 踩坑记录
坑1：  
搭建环境时，第三步报错，提示“thinkcmf 安装报错 Driver.class.php 　LINE: 350”，执行“drop database thinkcmf”后，重新安装成功，原因未知

# 0x07 参考链接
无
```
