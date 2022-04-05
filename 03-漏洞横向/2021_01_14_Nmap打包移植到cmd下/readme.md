# 0x00 起源
在内网渗透中，有时会碰到目标主机没有安装nmap的情况，而我们只有控制台权限，nmap的正常安装需要在GUI下安装winpcap，故有此项目

# 0x01 原理
此项目将GUI下安装winpcap转化为cmd下安装，可在未安装winpcap和nmap的主机下运行

# 0x02 使用
执行0-install-winpcap.bat后，即可在cmd下使用nmap
