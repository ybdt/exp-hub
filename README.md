很久之前打的一次AWD，让我萌生了将常见漏洞都打一遍的想法，积累过大量漏洞后，在打红队期间发现，剩下的就是漏洞的检测以及漏洞的利用（或者说WAF的绕过）

##### 本项目中所有POC/EXP仅用于测试，不可作为生产环境使用！

资产收集完成后，漏洞检测环节，推荐Fscan先对弱口令跑一波（尽管概率不大，但还是做一遍，万一有弱口令呢），然后AWVS、Xray、Nuclei对收集到的URL跑一波，最后可以用Goby对收集到的域名采用全端口跑一波

AWVS可以采用基于docker的破解版，Xray的话提交几个POC换取高级版，Goby的话提交几个POC换取红队版
![image](./README.image/awvs.png)  
![image](./README.image/xray.png)  
![image](./README.image/goby.png)  