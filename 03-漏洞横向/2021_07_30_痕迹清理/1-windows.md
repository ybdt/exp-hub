```
@echo off

'wevtutil.exe cl Application
'wevtutil.exe cl Security
'wevtutil.exe cl System

rem wevtutil.exe sl Microsoft-Windows-LiveId/Operational /ca:O:BAG:SYD:(A;;0x1;;;SY)(A;;0x5;;;BA)(A;;0x1;;;LA)
rem wevtutil.exe sl Microsoft-Windows-LiveId/Analytic /ca:O:BAG:SYD:(A;;0x1;;;SY)(A;;0x5;;;BA)(A;;0x1;;;LA)

for /f "tokens=*" %%i in ('wevtutil.exe el') do wevtutil.exe cl "%%i"
pause
```
