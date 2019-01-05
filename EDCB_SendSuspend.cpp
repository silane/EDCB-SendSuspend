#include <iostream>
#include <locale>
#include <unistd.h>
#include "EDCBCtrlCmd/SendCtrlCmd.h"
#include "EDCBCtrlCmd/StringUtil.h"
#include "EDCBCtrlCmd/ErrDef.h"

void printUsage(void)
{
	printf("Usage: EDCB-SendSuspend [-p <port>] [-r <rebootflag>] sleep|suspend|shutdown <host>\n");
}

int main(int argc,char **argv)
{
	string ip("");
	int port=-1;
	unsigned char mode=-1;
	unsigned char reboot=0xff;

	int optchar;
	while((optchar=getopt(argc,argv,"p:r:"))!=-1)
	{
		switch(optchar)
		{
		case 'p':
			port=atoi(optarg);
			if(port<=0)
			{
				std::cerr << "Invalid Port : " << optarg << std::endl;
				printUsage();
				return 1;
			}
			break;
		case 'r':
			reboot=atoi(optarg);
			if(reboot<0)
			{
				std::cerr << "Invalid reboot flag : " << optarg << std::endl;
				printUsage();
				return 1;
			}
			break;
		}
	}

	if(argc-optind!=2)
	{
		printUsage();
		return 1;
	}

	if(strcmp(argv[optind],"sleep")==0)
		mode=1;
	else if(strcmp(argv[optind],"suspend")==0)
		mode=2;
	else if(strcmp(argv[optind],"shutdown")==0)
		mode=3;
	else
	{
		printUsage();
		return 1;
	}

	ip=argv[optind+1];

	if(port==-1)
		port=4510;

	CSendCtrlCmd controller;

	wstring wip;
	AtoW(ip,wip);
	controller.SetNWSetting(wip,port);

	DWORD ret = controller.SendSuspend(reboot<<8 | mode);
	if(ret == NO_ERR)
		return 0;
	else
	{
		std::cerr << "Error code: " << ret << std::endl;
		return 2;
	}
}
