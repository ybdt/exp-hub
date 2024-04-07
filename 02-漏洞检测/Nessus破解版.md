# 起源
twitter上看到的一篇帖子：https://twitter.com/Elliot58616851
# Docker地址
```
https://github.com/elliot-bia/nessus

docker run -itd -p 8834:8834 ramisec/nessuslite
```
# 破解方式
```
原理：进到docker内部，修改nessus的web密码

操作：
cd /opt/nessus/sbin/
sudo ./nessuscli lsuser  # 列出所有用户
sudo ./nessuscli chpasswd admin(要更新密码的用户名)  # 更新密码
Nessus_Ps0d
会有2次提示确认
```
# 使用方法
https://rorschachchan.github.io/2018/01/23/使用Nessus进行漏洞扫描的过程/