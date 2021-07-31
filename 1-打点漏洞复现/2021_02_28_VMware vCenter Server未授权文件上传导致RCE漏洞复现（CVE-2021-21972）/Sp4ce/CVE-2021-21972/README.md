# CVE-2021-21972
CVE-2021-21972


# Works On

- VMware-VCSA-all-6.7.0-8217866、VMware-VIM-all-6.7.0-8217866 ✔
- VMware-VCSA-all-6.5.0-16613358 ✔

# For vCenter6.7 U2+
vCenter 6.7U2+ running website in memory,so this exp can't work for 6.7 u2+.

# Need test

- ~~vCenter 6.5 Linux(VCSA)/Window **Waiting For Test**~~
- ~~vCenter 6.7 Linux(VCSA)/Window **Waiting For Test**~~
- ~~vCenter 7.0 Linux(VCSA)/Window **Waiting For Test**~~

# Details

1. 漏洞为任意文件上传
2. 存在问题的接口为`/ui/vropspluginui/rest/services/uploadova`，完整路径（`https://domain.com/ui/vropspluginui/rest/services/uploadova`）
3. 仓库内的`payload`文件夹内的`tar`文件为默认冰蝎3 webshell

#  Screenshots

## Runtime

![3.png](/img/3.png)

## Success



![1.png](/img/1.png)

![1.png](/img/2.png)

# 声明

- 工具仅用于安全人员安全测试与研究使用，任何未授权检测造成的直接或者间接的后果及损失，均由使用者本人负责。
- The tool is only used for security testing and research by security personnel. Any direct or indirect consequences and losses caused by unauthorized testing are the responsibility of the user.
