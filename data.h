struct mtData{
	char firstBurst[100];
	char lastBurst[100];
	char solutionTime[100];
	char bec[30];
	double trFreq;
	char msg[50];
	int nBurst;
	char dt[5];
	char lutId[100];
	int npkt;
	int nsat;
	char satId[200];
	double jdop;
	double ehe;
	char mthd[10];
	double lat;
	double lon;
	double altitude;
	struct mtData* next;	
};

struct bec{
	char id[30];
	struct mtData *head;
	struct bec* next;
};
