# 0x00 限制原理
通过抓包后返回的页面源码得知  
![image](./0.png)  
微信服务端通过检查User-Agent中是否包含“micromessenger”来判断请求是否来自微信客户端，以此决定是跳转到目标网站还是提示“请在微信客户端打开链接”，因此我们可以通过获取微信客户端的User-Agent，然后修改浏览器的User-Agent，来绕过限制，目前市面上有很多现成的在线工具可用来获取User-Agent，比如http://www.atool9.com/useragent.php
