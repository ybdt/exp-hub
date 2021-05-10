公众号“洛米唯熊”上看到的

首先声明：只复现出了XSS漏洞，没复现出命令执行漏洞

从![官网](https://www.xmind.cn/xmind2020/)下载最新版（截止到2021/05/10 15：30），并安装

打开XMind，随便选择一个模板，此处选择SnowBrush，选择大纲模式，将“中心主题”替换为如下代码
```
<audio src=x onerror=confirm("ybdt")>
```
ctlr+s会弹框如下图  
![image](./pic/a0.png)
