/*
 ============================================================================
 Name        : upgrade.c
 Author      : Lzy
 Version     :
 Copyright   : Your copyright notice
 Description : U盘升级工具小程序
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define SH_CMD "sh /opt/start_ap.sh"

int main(void)
{
	sleep(30);
	while(1)
	{
		system(SH_CMD);
		sleep(2);
	}

	return EXIT_SUCCESS;
}
