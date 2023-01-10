# 0x01-漏洞浅析
无

# 0x02-影响版本
通达OA < 11.5.200417  
通达OA 2017

# 0x03-环境搭建
安装包下载参见：https://ybdt.me/2022/04/28/通达OA漏洞研究/  
安装：双击后一路下一步

# 0x04-复现过程
借助工具：https://github.com/NS-Sp4ce/TongDaOA-Fake-User/blob/master/POC.py  
获取cookie  
![pic](./pic/01.png)  
使用获取到的cookie访问页面/general/index.php?isIE=0&modify_pwd=0  
![pic](./pic/02.png)

# 0x05-需要注意
01、获取cookie有时会失败，多执行两次  

# 0x06-参考链接
https://www.cnblogs.com/yuzly/p/13602239.html