import requests
import argparse
import urllib3

#disable ssl warning
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

#如果报错ssl.SSLError: [SSL: UNSUPPORTED_PROTOCOL] unsupported protocol (_ssl.c:852)
#修改/etc/ssl/openssl.cnf，将TLSv1.2改为TLSv1.0
#参考链接：https://stackoverflow.com/questions/59408646/ssl-sslerror-ssl-unsupported-protocol-unsupported-protocol-ssl-c852-in-d


ENDPOINT = '/ui/vropspluginui/rest/services/uploadova'

def banner():
    print(
        """
   _______      ________    ___   ___ ___  __      ___  __  ___ ______ ___  
  / ____\\ \\    / /  ____|  |__ \\ / _ \\__ \\/_ |    |__ \\/_ |/ _ \\____  |__ \\ 
 | |     \\ \\  / /| |__ ______ ) | | | | ) || |______ ) || | (_) |  / /   ) |
 | |      \\ \\/ / |  __|______/ /| | | |/ / | |______/ / | |\\__, | / /   / / 
 | |____   \\  /  | |____    / /_| |_| / /_ | |     / /_ | |  / / / /   / /_ 
  \\_____|   \\/   |______|  |____|\\___/____||_|    |____||_| /_/ /_/   |____|
                        Author: ybdt                                                    


    """
    );

def check(ip):
    try:
        if "https://" in ip:
            r = requests.get(ip + ENDPOINT, verify=False, timeout=10);
        else:
            r = requests.get('https://' + ip + ENDPOINT, verify=False, timeout=10)
    except requests.exceptions.ConnectTimeout:
        print('[-] ' + ip + ' ConnectTimeout');
        return False;
    except requests.exceptions.ReadTimeout:
        print('[-] ' + ip + ' ReadTimeout');
        return False;
    except requests.exceptions.ConnectionError:
        print('[-] ' + ip + ' ConnectionError');
        return False;
    
    if r.status_code == 405:
        print('[+] ' + ip + ' vulnerable to CVE-2021-21972!')
        return True
    else:
        print('[-] ' + ip + ' not vulnerable to CVE-2021-21972. Response code: ' + str(r.status_code) + '.')
        return False

def main():
    banner();

    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--inputfile", help="The file contains ips, one per line", required=True);
    args = parser.parse_args()
    
    with open(args.inputfile, "r") as f_r:
        with open("vulnerable.txt", "w") as f_w:
            lines = f_r.readlines();
            for line in lines:
                line = line.strip("\n").strip("\r\n");
                vulnerable = check(line);
                if vulnerable:
                    f_w.write(line + "\n");

main();