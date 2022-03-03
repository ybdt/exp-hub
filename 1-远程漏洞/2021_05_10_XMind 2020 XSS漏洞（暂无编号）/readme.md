公众号“洛米唯熊”上看到的，参考链接：https://mp.weixin.qq.com/s/yImhOCX3Xy91XaHtFFUnng

首先声明：只复现出了XSS漏洞，没复现出命令执行漏洞

从![官网](https://www.xmind.cn/xmind2020/)下载最新版（截止到2021/05/10 15：30），并安装

打开XMind，随便选择一个模板，此处选择SnowBrush，选择大纲模式，将“中心主题”替换为如下代码
```
<audio src=x onerror=confirm("ybdt")>
```
ctlr+s会弹框如下图  
![image](./pic/a0.png)
保存为ybdt.xmind，想再次触发漏洞，打开ybdt.xmind，选择大纲模式  
1、ctrl+s会触发漏洞  
2、alt+tab会触发漏洞  
3、鼠标移动到代码中<的左边，再点击键盘中的<键会触发漏洞  
（漏洞的触发目前没找到规律）
