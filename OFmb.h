#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//#include "data.h"
#include "extractData.h"

struct bec *head =NULL;
int compareTime(char t1[100],char t2[100]);
double Mjd(int Year, int Month, int Date, int Hr, int Min, double Sec);
int uniqueChar(char inp[70][10],char uni[70][10],int n);
void computeLocation(struct bec *becTemp,FILE *fp,int count);

void OfflineProcess(FILE *fp){
    char inp[1000],inp2[1000];
    struct bec *becTemp1;
    struct mtData *mtDataTemp1,*ptr;
    int flag;
    int count = 1;
    char t1[100],t2[100];
    FILE *op = fopen("MT_E4.csv","w");
    while(fgets(inp,sizeof(inp),fp)!=NULL)
    {   
        strcpy(inp2,inp);
        //getchar(); 
        mtDataTemp1 = (struct mtData *)malloc(sizeof(struct mtData));
        extractMtData(inp,mtDataTemp1);
        //printf("-----------------------------------------------------\n");
        //printf("%s\n%s\n%s\n",mtDataTemp1->firstBurst,mtDataTemp1->lastBurst,mtDataTemp1->solutionTime);
        //getchar();
        char becId[30];
        getBecId(inp2,becId);
        if(head==NULL)
        {
            head = (struct bec *)malloc(sizeof(struct bec));
            strcpy(head->id,becId);
            head->head = NULL;
            head->next = NULL;
        }
        //printf("%s\n",head->id);
        becTemp1 = findBec(head,becId);
        printf("%s  DATA EXTRACTED!!\n",mtDataTemp1->bec);

        if(becTemp1->head!=NULL)
        {
            printf("%s %s\n",becTemp1->head->firstBurst,mtDataTemp1->firstBurst);
            //getchar();
            strcpy(t1,becTemp1->head->firstBurst);
            strcpy(t2,mtDataTemp1->firstBurst);
            flag = compareTime(t1,t2);
            printf("flag : %d\n",flag);
            //getchar();
            if(flag==1)
            {
                computeLocation(becTemp1,op,count);
                becTemp1->head = mtDataTemp1;
                count++;
            }else
            {
                ptr = becTemp1->head;
                while(ptr->next!=NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = mtDataTemp1;
            }
        }else
        {
            becTemp1->head = mtDataTemp1;
        }
    }
    while(becTemp1!=NULL)
    {
        if(becTemp1->head!=NULL)
        {
            computeLocation(becTemp1,op,count);
            count++;
        }
        becTemp1 = becTemp1->next;
    }
    fclose(op);
    printf("Method is building\n");

}
void computeLocation(struct bec *becTemp,FILE *fp,int count)
{
    struct mtData *ptr, *nptr;
    struct mtData *tempHead;
    tempHead = becTemp->head;
    char lutId[70][10],satId[70][10],uLutId[70][10],uSatId[70][10];
    char FirstBurst[50],LastBurst[50],solnTime[50];
    int burst=0,pkt=0,i;
    double avJdop=0,avEhe=0,avLat=0,avLon=0,avAlt=0,avTrFreq=0;
    char *token;
    ptr = becTemp->head;
    becTemp->head = NULL;
    strcpy(FirstBurst,ptr->firstBurst);
    char *msg;
    int nlut=0;
    strcpy(msg,ptr->msg);
    while(ptr!=NULL)
    {
        strcpy(LastBurst,ptr->lastBurst);
        strcpy(solnTime,ptr->solutionTime);
        avJdop+=ptr->jdop;
        avEhe += ptr->ehe;
        avTrFreq += ptr->trFreq;
        avLat += ptr->lat;
        avLon += ptr->lon;
        avAlt += ptr->altitude;
        i=0;
        token = strtok(ptr->lutId," ");
        while(token!=NULL)
        {
            strcpy(lutId[nlut],token);
            token = strtok(NULL," ");
            i++;
        }
        nlut+=i;
        i=0;
        token = strtok(ptr->satId," ");
        while(token!=NULL)
        {
            strcpy(satId[pkt],token);
            token = strtok(NULL," ");
            i++;
        }
        pkt+=i;
        burst++;
        ptr = ptr->next;
    }
    //nlut = uniqueChar(lutId,uLutId, nlut);
    //pkt = uniqueChar(satId, uSatId, pkt);
    avLat/=burst;
    avLon/=burst;
    avAlt/=burst;
    avJdop/=burst;
    avEhe/=burst;
    avTrFreq/=burst;
    fprintf(fp,"%d,%s,%s,%s,%s,%15.5lf,%s,%02d,D,",count,
    FirstBurst,LastBurst,solnTime,becTemp->id,avTrFreq,msg,burst);
    /*
    for(i=0;i<nlut;i++)
        fprintf(fp,"%s ",uLutId[i]);
    fprintf(fp,",%03d,",pkt);
    for(i=0;i<pkt;i++)
        fprintf(fp,"%s ",uSatId[i]);
    */
    fprintf(fp,",%8.3f,%8.3f,P3D,%15.8lf,%15.8lf,%15.8lf\n",
    avJdop,avEhe,avLat,avLon,avAlt);

    //getchar();
    ptr = tempHead;
    /*
    while(ptr!=NULL)
    {
        nptr = ptr->next;
        free(ptr);
        ptr = nptr;   
    }*/
}
int uniqueChar(char inp[70][10],char uni[70][10],int n)
{
    int count=0,i,j,flag=-1;
    for(i=0;i<n;i++)
    {
        for(j=0;j<count;j++)
        {
            if(strcmp(inp[i],uni[j])==0)
                flag = 0;
                break;

        }
        if(flag!=0)
        {
            strcpy(uni[count],inp[i]);
            count++;
        }
    }
    return count;

}
int compareTime(char t1[100],char t2[100])
{
    char dt[20];
    char tt[80];
    char *tk1;
    tk1 = strtok(t1," ");
    strcpy(dt,tk1);
    tk1 = strtok(NULL," ");
    strcpy(tt,tk1);
    int yy,mn,dd,hh,mm;
    double sec;
    tk1 = strtok(dt,"-");
    yy = atoi(tk1);
    tk1 = strtok(NULL,"-");
    mn = atoi(tk1);
    tk1 = strtok(NULL,"-");
    dd = atoi(tk1);
    tk1 = strtok(tt,":");
    hh = atoi(tk1);
    tk1 = strtok(NULL,":");
    mm = atoi(tk1);
    tk1 = strtok(NULL,":");
    sec = atof(tk1);
    double mjd1 = Mjd(yy,mn,dd,hh,mm,sec);
    printf("%d-%d-%d %d:%d:%5.3lf -> %lf\n",yy,mn,dd,hh,mm,sec,mjd1);
    tk1 = strtok(t2," ");
    strcpy(dt,tk1);
    tk1 = strtok(NULL," ");
    strcpy(tt,tk1);
    tk1 = strtok(dt,"-");
    yy = atoi(tk1);
    tk1 = strtok(NULL,"-");
    mn = atoi(tk1);
    tk1 = strtok(NULL,"-");
    dd = atoi(tk1);
    tk1 = strtok(tt,":");
    hh = atoi(tk1);
    tk1 = strtok(NULL,":");
    mm = atoi(tk1);
    tk1 = strtok(NULL,":");
    sec = atof(tk1);
    double mjd2 = Mjd(yy,mn,dd,hh,mm,sec);
    printf("%d-%d-%d %d:%d:%5.3lf -> %lf\n",yy,mn,dd,hh,mm,sec,mjd1);
     
    printf("%lf\n",fabs(mjd2 - mjd1)*3600*24);   
    if(fabs(mjd2 - mjd1)*3600*24 >= 600)
        return 1;
    return 0;
}
double Mjd(int Year, int Month, int Date, int Hr, int Min, double Sec)
{
        int b;

        long MjdMidnight;

        double FracOfDay, mjd, jd;


        if (Month<=2)
        {
                Month+=12;
                --Year;
        }

        if( (10000L*Year+100L*Month+Date) <= 15821004L )
                b = -2 + ((Year+4716)/4) - 1179;
        else
                b = (Year/400)-(Year/100)+(Year/4);
        MjdMidnight = 365L*Year - 679004L + b + (int)(30.6001*(Month+1)) + Date;
        FracOfDay   = (Hr + Min/60.0 + Sec/3600.0) / 24.0;

        mjd = MjdMidnight + FracOfDay;
        jd = mjd + 2400000.5;
        return (mjd);
}
