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