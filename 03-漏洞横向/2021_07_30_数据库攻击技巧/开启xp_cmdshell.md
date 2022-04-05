1、SQL Server 2016开启xp_cmdshell
```
执行SELECT * FROM sys.configurations WHERE name='xp_cmdshell' OR name='show advanced options'
其中Enable or disable command shell的value为0，则未开启xp_cmdshell，依次执行如下SQL语句开启xp_cmdshell
USE master
EXEC sp_configure 'show advanced options', 1
RECONFIGURE WITH OVERRIDE
EXEC sp_configure 'xp_cmdshell', 1
RECONFIGURE WITH OVERRIDE
EXEC sp_configure 'show advanced options', 0
RECONFIGURE WITH OVERRIDE
再次执行SELECT * FROM sys.configurations WHERE name='xp_cmdshell' OR name='show advanced options'
发现Enable or disable command shell的value为1
```
