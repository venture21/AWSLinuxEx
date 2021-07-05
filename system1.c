#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int status;
	printf("Running ps with system\n");
	system("./cmd_arg 1234 abcd &");
	printf("Process is Done\n");

	//return 0;
	exit(0);
}
