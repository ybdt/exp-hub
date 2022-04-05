# 0x00 起源
在内网渗透中，有时会碰到目标主机没有安装maascan的情况，而我们只有控制台权限，masscan需要winpcap，故有此项目

# 0x01 原理
此项目将winpcap转化为cmd下安装，可在未安装winpcap和masscan的主机下运行

# 0x02 使用
执行0-install-winpcap.bat后，即可在cmd下使用masscan
