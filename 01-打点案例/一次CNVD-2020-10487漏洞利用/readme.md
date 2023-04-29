# 思路梳理
```
01、发现8009端口
02、经验证，存在tomcat ajp漏洞
03、目标还开放redis服务，尝试读取redis密码，redis可从外部连接，不过密码是加密过的
04、读取web.xml后，读取class文件（借助工具：https://github.com/LandGrey/ClassHound），反编译后审查加密方式，解密后成功连接redis，拿到shell

期间还有一些小坑
```