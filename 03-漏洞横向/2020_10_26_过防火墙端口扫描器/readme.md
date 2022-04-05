使用nmap进行全端口扫描，发现全部被过滤，怀疑可能有防火墙  
手动测试发现某个ip的80端口能访问，使用nmap扫描此ip的80端口，发现被过滤，确认有防火墙  
手动测试发现telnet能通xxx.xxx.xxx.xxx的80端口，故打算编写工具，自动化telnet探测开放的端口  
脚本参见tcp-socket-portscanner.py  

由于上述脚本扫描一个ip的65535个全端口需要20小时，当要扫描一个ip段的全端口时，时间太长  
采用编写bash脚本实现多进程并行执行  
脚本参见parallel-exec.sh  

2020/05/25  
对于上述的端口扫描器：  
windows下终止的快捷键是ctrl+c，可ubuntu下终止的快捷键并不是ctrl+c，经查阅ubuntu下终止的快捷键是ctrl+\  
参考链接：  
https://stackoverflow.com/questions/1364173/stopping-python-using-ctrlc 中Junius L.的回答
