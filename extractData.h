#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "data.h"
void setValue(int n,struct mtData *mt,char *token);
/*
void extractMtData(char str[1000],struct mtData *mt)
{
	mt->next = NULL;
	char *token = strtok(str,",");
	
	int n = 1;
	while(token!=NULL){
		switch(n)
		{
			case 3 : strcpy(mt->firstBurst,token);
					 break;
			case 4 : strcpy(mt->lastBurst,token);
					 break;
			case 5 : strcpy(mt->solutionTime,token);
					 break;
			case 6 : strcpy(mt->bec,token);
					 break;
			case 7 : mt->trFreq = atof(token);
					 break;
			case 8 : strcpy(mt->msg,token);
					 break;
			case 9 : mt->nBurst = atoi(token);
					 break;
			case 10 : strcpy(mt->dt,token);
					 break;
			case 11 : strcpy(mt->lutId,token);
					 break;
			case 12 : mt->npkt = atoi(token);
					 break;
			case 13 : mt->nsat = atoi(token);
					 break;
			case 14 : strcpy(mt->satId,token);
					 break;
			case 15 : mt->jdop = atof(token);
					 break;
			case 16 : mt->ehe = atof(token);
					 break;
			case 17 : strcpy(mt->mthd,token);
					 break;
			case 18 : mt->lat = atof(token);
					 break;
			case 19 : mt->lon = atof(token);
					 break;
			case 20 : mt->altitude = atof(token);
					 break;
			default : printf("This value does'nt required : %s\n",token); 
		}
		n++;
		printf("%s\n",token);
		token = strtok(NULL,",");
	}

}
*/
void extractMtData(char *str,struct mtData *mt)
{
	char token[500];
	int i = 0,n=1,j=0;
	char del[]=",";
	char *buff;
	while(str[i]!='\0'){
		if(str[i]==',')
		{
			token[j]='\0';
			//printf("%s\n",token);
			setValue(n, mt,token);
			//getchar();
			n++;
			j=0;
		}else
		{
			token[j]=str[i];
			j++;
		}
		i++;
	}
	//getchar();

}
void setValue(int n,struct mtData *mt,char *token)
{
	switch(n)
		{
			case 3 : strcpy(mt->firstBurst,token);
					 break;
			case 4 : strcpy(mt->lastBurst,token);
					 break;
			case 5 : strcpy(mt->solutionTime,token);
					 break;
			case 6 : strcpy(mt->bec,token);
					 break;
			case 7 : mt->trFreq = atof(token);
					 break;
			case 8 : strcpy(mt->msg,token);
					 break;
			case 9 : mt->nBurst = atoi(token);
					 break;
			case 10 : strcpy(mt->dt,token);
					 break;
			case 11 : strcpy(mt->lutId,token);
					 break;
			case 12 : mt->npkt = atoi(token);
					 break;
			case 13 : mt->nsat = atoi(token);
					 break;
			case 14 : strcpy(mt->satId,token);
					 break;
			case 15 : mt->jdop = atof(token);
					 break;
			case 16 : mt->ehe = atof(token);
					 break;
			case 17 : strcpy(mt->mthd,token);
					 break;
			case 18 : mt->lat = atof(token);
					 break;
			case 19 : mt->lon = atof(token);
					 break;
			case 20 : mt->altitude = atof(token);
					 break;
			default : printf("This value does'nt required : %s\n",token); 
		}
}

struct bec *findBec(struct bec *head,char *becId)
{
	struct bec *ptr = head;
	if(strcmp(ptr->id,becId)==0)
	{
		return ptr;	
	}
	while(ptr->next!=NULL)
	{
		//printf("%s %s\n",becId,ptr->id);
		//getchar();
		if(strcmp(ptr->id,becId)==0){
			return ptr;
		}
		ptr = ptr->next;

	}
	struct bec *nptr = (struct bec *)malloc(sizeof(struct bec));
	strcpy(nptr->id,becId);
	nptr->head = NULL;
	nptr->next = NULL;
	ptr->next = nptr;
	return nptr;
}

int getBecId(char *str,char becId[30])
{
	char *inp = str;
	char *token = strtok(inp,",");
//	printf("%s\n",token);
	int n = 1;
	while(token!=NULL){
		if(n==6){
			strcpy(becId,token);
			return 0;
		}
		n++;
		token = strtok(NULL,",");
	}

}