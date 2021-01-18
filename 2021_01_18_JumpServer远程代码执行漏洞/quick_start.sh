#!/bin/bash
#

flag=0

echo -ne "User    Check \t........................ "
isRoot=`id -u -n | grep root | wc -l`
if [ "x$isRoot" == "x1" ]; then
    echo -e "[\033[32m OK \033[0m]"
else
    echo -e "[\033[31m ERROR \033[0m] 请用 root 用户执行安装脚本"
    flag=1
fi

echo -ne "OS      Check \t........................ "
if [ -f /etc/redhat-release ]; then
    osVersion=`cat /etc/redhat-release | grep -oE '[0-9]+\.[0-9]+'`
    majorVersion=`echo $osVersion | awk -F. '{print $1}'`
    if [ "x$majorVersion" == "x" ]; then
        echo -e "[\033[31m ERROR \033[0m] 操作系统类型版本不符合要求，请使用 CentOS 7 64 位版本"
        flag=1
    else
        if [[ $majorVersion == 7 ]]; then
            is64bitArch=`uname -m`
            if [ "x$is64bitArch" == "xx86_64" ]; then
            echo -e "[\033[32m OK \033[0m]"
            else
                echo -e "[\033[31m ERROR \033[0m] 操作系统必须是 64 位的，32 位的不支持"
                flag=1
            fi
        else
            echo -e "[\033[31m ERROR \033[0m] 操作系统类型版本不符合要求，请使用 CentOS 7"
            flag=1
        fi
    fi
else
    echo -e "[\033[31m ERROR \033[0m] 操作系统类型版本不符合要求，请使用 CentOS 7"
    flag=1
fi
echo -ne "CPU     Check \t........................ "
processor=`cat /proc/cpuinfo| grep "processor"| wc -l`
if [ $processor -lt 2 ]; then
    echo -e "[\033[31m ERROR \033[0m] CPU 小于 2核，JumpServer 所在机器的 CPU 需要至少 2核"
    flag=1
else
    echo -e "[\033[32m OK \033[0m]"
fi

echo -ne "Memory  Check \t........................ "
memTotal=`cat /proc/meminfo | grep MemTotal | awk '{print $2}'`
if [ $memTotal -lt 7500000 ]; then
    echo -e "[\033[31m ERROR \033[0m] 内存小于 8G，JumpServer 所在机器的内存需要至少 8G"
    flag=1
else
    echo -e "[\033[32m OK \033[0m]"
fi
if [ $flag -eq 1 ]; then
    echo "安装环境检测未通过，请查阅上述环境检测结果"
    exit 1
fi
which wget >/dev/null 2>&1
if [ $? -ne 0 ];then
    yum install -y wget
fi

Version=$(curl -s 'https://api.github.com/repos/jumpserver/installer/releases/latest' | grep "tag_name" | head -n 1 | awk -F ":" '{print $2}' | sed 's/\"//g;s/,//g;s/ //g')

cd /opt
if [ ! -d "/opt/jumpserver-installer-$Version" ]; then
    wget https://github.com/jumpserver/installer/releases/download/$Version/jumpserver-installer-$Version.tar.gz || {
        rm -rf /opt/jumpserver-installer-$Version.tar.gz
        echo -e "\033[31m [ERROR] 下载 jumpserver-installer 失败, 请检查网络是否正常或尝试重新执行脚本 \033[0m"
        exit 1
    }
    tar -xf /opt/jumpserver-installer-$Version.tar.gz -C /opt || {
        rm -rf /opt/jumpserver-installer-$Version
        echo -e "\033[31m [ERROR] 解压 jumpserver-installer 失败, 请检查网络是否正常或尝试重新执行脚本 \033[0m"
        exit 1
    }
    rm -rf /opt/jumpserver-installer-$Version.tar.gz
fi

cd /opt/jumpserver-installer-$Version

JMS_Version="v2.6.1"

sed -i "s/VERSION=.*/VERSION=$JMS_Version/g" /opt/jumpserver-installer-$Version/static.env

echo ""
echo -e "\033[33m JumpServer 部署脚本已经下载至 /opt/jumpserver-installer-$Version 目录 \n \033[0m"
sleep 5s

export DOCKER_IMAGE_PREFIX=docker.mirrors.ustc.edu.cn
./jmsctl.sh install
