:<<EOF
for (( i=64; i<=127; i++ )); do
    ip="192.168.1."$i
    python3 tcp-socket-portscanner.py $ip &
done
wait#此处没有wait，程序会直接退出，加上wait可让程序等待子进程执行完之后再退出，方便计算时间
EOF

date>result.txt
for ip in 192.168.1.{64..127}; do
    python3 tcp-socket-portscanner.py $ip &
done
wait#此处没有wait，程序会直接退出，加上wait可让程序等待子进程执行完之后再退出，方便计算时间
date>>result.txt
