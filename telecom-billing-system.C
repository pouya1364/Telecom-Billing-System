#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <cstring>
#include <unistd.h>
// #include <windows.h> //uncomment it if you are running it in windows
struct subscriber
{
char phonenumber[20];
char name[20];
float amount;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;

int main()
{	int password;
	int phonenumber;
	char choice;



	system("clear");
printf("\n\n\n\n\n\n\n\n\n**************************************************************");
	printf("\n\t\t------TELECOM BILLING MANAGEMENT SYSTEM------");
	printf("\n\t\t****************************************************************");
	//sleep(2000);
	getchar();
    system("clear");
	while (1)
	{
		system("clear");
		printf("\n Enter\n A : for adding new records.\n L : for list of records");
		printf("\n M : for modifying records.\n P : for payment");
		printf("\n S : for searching records.");
		printf("\n D : for deleting records.\n E : for exit\n");
		choice=getchar();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("clear");
				printf("\n\n\t\t\t\tTHANK YOU");
				printf("\n\n\n\n\n:\n\tFOR USING OUR SERVICE");
				//sleep(2000);
				exit(0);
				break;
			default:
				system("clear");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getchar();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test;
	f=fopen("file.ojs","ab+");
	if(f==0)
	{   f=fopen("file.ojs","wb+");
		system("clear");
		printf("please wait while we configure your computer");
		printf("/npress any key to continue");
		getchar();
	}
	while(1)
	{
		system("clear");
		printf("\n Enter phone number:");
		scanf("%s",s.phonenumber);
		printf("\n Enter name:");
		fflush(stdin);
		scanf("%s",s.name);
		printf("\n Enter amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("clear");
		printf("1 record successfully added");
		printf("\n Press esc key to exit, any other key to add other record:");
		test=getchar();

		if(test==27) break;
	}
	fclose(f);
}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("file.ojs","rb"))==NULL)
		exit(0);
	system("clear");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getchar();
}
void deleterecords()
{
	FILE *f,*t;
	int i=1;
	char phonenumber[20];
	if((t=fopen("temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("file.ojs","rb"))==NULL)
	exit(0);
	system("clear");
	printf("Enter the phone number to be deleted from the Database");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("clear");
		printf("Phone number \"%s\" not found",phonenumber);
		remove("file.ojs");
		rename("temp.ojs","file.ojs");
		getchar();
		fclose(f);
		fclose(t);
		main();
	}
	remove("file.ojs");
	rename("temp.ojs","file.ojs");
	system("clear");
	printf("The Number %s Successfully Deleted!!!!",phonenumber);
	fclose(f);
	fclose(t);
	getchar();
}
void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("clear");
	printf("Enter Phone Number to search in our database");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{	system("clear");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("clear");
			printf("Requested Phone Number Not found in our database");
		}
	}
	getchar();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("file.ojs","rb+"))==NULL)
		exit(0);
	system("clear");
	printf("Enter phone number of the subscriber to modify:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("clear");
			printf("\n Enter phone number:");
			scanf("%s",s.phonenumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
void payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("file.ojs","rb+"))==NULL)
		exit(0);
	system("clear");
	printf("Enter phone number of the subscriber for payment");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("clear");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("clear");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getchar();
	fclose(f);

}
	
