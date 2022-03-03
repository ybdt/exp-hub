import argparse
import requests
import sys


requests.packages.urllib3.disable_warnings();


def banner():
    print('''

    ***************************************************************
    用友NC BeanShell RCE漏洞检测工具【CNVD-2021-30167】
    Affected Version: 用友NC v6.5
    Author: ybdt
    First Date: 2021/08/21
    Last  Date: 2021/08/21
    ***************************************************************
    
    *************************警 告*********************************
    本工具旨在帮助企业快速定位漏洞、修复漏洞，仅限授权安全测试使用！
    请严格遵守《中华人民共和国网络安全法》，禁止未授权非法攻击站点！
    ***************************************************************

    ''');


def usage():
    parser = argparse.ArgumentParser(description="当前工具仅检测目标是否存在漏洞");
    parser.add_argument("-f", "--file", help="包含ip地址的文件，每行一个", required=True);
    args = parser.parse_args();
    ip_file = args.file;
    return ip_file;


def nc_Check(target_url):
    print("[*]正在检测目标：" + target_url);
    url = target_url + "/servlet/~ic/bsh.servlet.BshServlet";
    headers = {
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.93 Safari/537.360"
    };
    with open("success.txt", "a") as f_a_1:
        with open("except.txt", "a") as f_a_2:
            try:
                response = requests.get(url=url, headers=headers, timeout=5);#此处设置超时等待时间，太长了程序会慢，太短了容易错过正常网站
                if response.status_code == 200 and 'BeanShell' in response.text:
                    print( "[+]BeanShell页面存在, 目标：{}可能存在漏洞\n".format(url) );
                    f_a_1.write(url + "\n");
                    return url;
                else:
                    print("[-]目标：" + url + "不存在漏洞\n");
                    return False;
            except requests.exceptions.ConnectTimeout as e1:
                print("[-]访问目标：" + url + "超时，服务端未响应\n");
                return Flase;
            except requests.exceptions.ConnectionError as e2:
                print("[-]访问目标：" + url + "拒绝或重置，可能存在WAF\n");
            except Exception as e:
                print( "[-]访问目标发生异常，目标及异常信息被保存到except.txt\n".format(url) );
                f_a_2.write(url + "\n");
                f_a_2.write( str(e) + "\n");
                f_a_2.write("\n");
                return False;


def main():
    banner();

    ip_file = usage();
    
    vuln_url = [];
    with open(ip_file, "r") as f_r:
        lines = f_r.readlines();
        for line in lines:
            target_url = line.strip("\n");
            url = nc_Check(target_url);
            if url == False:
                continue;
            else:
                vuln_url.append(url);


main();
