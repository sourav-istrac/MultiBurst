#include<stdio.h>
#include<string.h>
#include<math.h>
#include "OFmb.h"
#include "RTmb.h"

int main(int arg,char *argc[]){
	if(arg< 1){
		printf("No Input File!!\n");
		return 1;
	}
	FILE *fp = fopen(argc[1],"r");
	if(fp==NULL)
	{
		printf("Wrong Input File\n");
		return 1;
	}
	int method;
	printf("Please choose the method\n1. Offline\n2. RT\n");
	scanf("%d",&method);
	
	if(method==1){
		OfflineProcess(fp);
	}else if(method==2){
		RTProcess();
	}else{
		printf("No Such Method Exists!!\n");
		return 1;
	}
	fclose(fp);
	
	return 0;
}
