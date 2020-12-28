#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>

#define LOWER 1
#define UPPER 75
#define DELAY 20000

void delay();
char back();
void intro();
void menu();
int checkAns(int, int, int, int);
void wotd();
void search();
void game();

void delay()
{	int i,j;
	for(i=0;i<DELAY;i++)
		for(j=0;j<DELAY;j++);
}

char back()
{	char ch;
	printf("\n\n\n\n\n\t\t\t PRESS ANY KEY TO GO BACK");
	printf("\t\t\t\t  PRESS 1 TO EXIT ");
	ch = getch();
	return ch;
}

void intro()
{	printf("\n\n\t\t ****************************************************************************************");
	printf("\n\n\t\t\t\t\t\t       POWER-VOCAB ");
	printf("\n\n\t\t ****************************************************************************************");
}

void menu()
{	char b;
	do
	{	char opt;
		system("cls");
		intro();
		printf("\n\n\n\t\t\t BUILD YOUR VOCABULARY WITH \"POWER-VOCAB\" ");
		printf("\n\t\t\t FIND MEANING FOR ANY WORD IN THE WORD FINDER!");
		printf("\n\t\t\t QUIZ YOURSELF EVERY DAY TO LEARN NEW WORDS ON THE WORD GAME!");
		printf("\n\t\t\t NOW YOU CAN PRACTICE AND IMPROVE YOUR VOCABULARY ANYWHERE, ANY TIME!");
		printf("\n\n\n\t\t\t 1. WORD OF THE DAY");
		printf("\n\n\t\t\t 2. WORD FINDER");
		printf("\n\n\t\t\t 3. WORD GAME");
		printf("\n\n\t\t\t 4. EXIT");
		printf("\n\n\n\t\t\t ENTER YOUR CHOICE: ");
		scanf(" %c", &opt);
		switch(opt)
		{	case '1': wotd();
					  b = back();
					  break;
			case '2': search();
					  b = back();
			 		  break;
			case '3': game();
					  b = back();
				 	  break;	
			case '4': printf("\n\t\t\t EXITING...");
			 	 	  delay();
					  exit(0);
			default : printf("\n\n\t\t\t INCORRECT INPUT ");
					  printf("\n\t\t\t PLEASE ENTER CORRECT INPUT");
					  delay();
		}
	}while(b!='1');
}

int checkAns(random, num1, num2, num3)						//sort array in asc order
{	int a,b,n,temp;
	int arr[4] = {random, num1, num2, num3};
	for(a=0;a<4;a++)
	{	for(b=a+1;b<4;b++)
		{	if(arr[a] > arr[b])
			{	temp = arr[a];
				arr[a] = arr[b];
				arr[b] = temp;
			}
		}
	}
	for(a=0;a<4;a++)
	{	if(arr[a]==random)
			break;
	}
	a++;
	n=a;
	return n;
}

void wotd()
{	FILE *f,*x;
	int random;
	char c[80],c1[10],c2[80];

	system("cls");
	intro();
	printf("\n\n\n\t\t\t WORD OF THE DAY");
	
	f=fopen("words.txt","r");
	x=fopen("meaning.txt","r");
	
	if(f==NULL || x==NULL)
		printf("\n\t\t\t WORD/MEANING FILE NOT FOUND");
	else
	{	int i=0;
	 	srand(time(NULL));
		random = (rand() % (UPPER - LOWER + 1)) + LOWER;
	  	while(i!=random)
	  	{	fscanf(f,"%[^\n]",c);
	  		fscanf(x,"%[^\n]",c2);
			i++;
			if(i==random)
				printf("\n\n\t\t\t %s -> %s ",c,c2);
		fgets(c,strlen(c),f);
		fgets(c2,strlen(c2),x);	
		}
	}
	fclose(f);
	fclose(x);
	delay();
}

void search()
{	int check=0;
	FILE *f,*x,*y;
	char c[80],c1[10],c2[80],ch;
	
	do
	{	system("cls");
		intro();
		printf("\n\n");	
		check=0;
		
		printf("\n\t\t\t ENTER ANY WORD TO SEARCH FOR IT'S MEANING \n\n");
		
		printf("\n\t\t\t ENTER WORD: ");
		scanf("%s", c1);
		
		f=fopen("words.txt","r");
		x=fopen("meaning.txt","r");
		
		if(f==NULL || x==NULL)
			printf("\n\t\t\t WORD/MEANING FILE NOT FOUND");
		else
		{	int i=0;
			while(!feof(f))
	  		{	fscanf(f,"%[^\n]",c);
	  			fscanf(x,"%[^\n]",c2);
				i++;
				if(!strcmp(c,c1))
				{	printf("\n\n\t\t\t !!! WORD FOUND !!! \n\n");
					check=1;
					printf("\t\t\t %s -> %s \n",c,c2);
			 	}
			fgets(c,strlen(c),f);
			fgets(c2,strlen(c2),x);
			}
		}
		
		if(check==0)
		{	printf("\n\n\t\t\t WORD NOT FOUND \n");
			printf("\n\t\t\t WE'LL ADD THIS WORD IN THE UPCOMING VERSION \n");
			y = fopen("new_words.txt", "a+");
			fputs(c1, y);
			fputs("\n", y);
		}
		
		printf("\n\n\n\t\t\t WANT TO SEARCH SOME OTHER WORD(Y/N)?: ");
		scanf(" %c",&ch);
	
		fclose(f);
		fclose(x);
		fclose(y);
		delay();		
	}while(ch=='y' || ch=='Y');
}

void game()
{	FILE *f,*x;
	int num1,num2,num3,random,index,score=0,check=0,ans,no=1;
	char c[80],c1[10],c2[80];
	
	do
	{	system("cls");
		intro();
		printf("\n\n");
		
		printf("\n\t\t\t SELECT MEANING OF THE GIVEN WORD OUT OF THE FOUR OPTIONS PROVIDED \n\n");
		
		srand(time(NULL));
	
		random = (rand() % (UPPER - LOWER + 1)) + LOWER;			//to create 4 random nos
		do
		{	num1 = (rand() % (UPPER - LOWER + 1)) + LOWER;
		}while(num1==random);
		do
		{	num2 = (rand() % (UPPER - LOWER + 1)) + LOWER;
		}while(num1==num2 || num2==random);
		do
		{	num3 = (rand() % (UPPER - LOWER + 1)) + LOWER;
		}while(num1==num2 || num1==num3 || num2==num3 || num3==random);
		
		index = checkAns(random, num1, num2, num3);					//to find the correct answer(array subscript) in the sorted array

		f=fopen("words.txt","r");
		x=fopen("meaning.txt","r");

		if(f==NULL || x==NULL)
			printf("\n\t\t\t WORD/MEANING FILE NOT FOUND");
		else
		{	int i=0;
		  	while(i!=random)										//to print the random word from the file
		  	{	fscanf(f,"%[^\n]",c);
		  		i++;
				if(i==random)
			 		printf("\n\t\t\t WORD: %s ",c);
				fgets(c,strlen(c),f);
			}
			printf("\t\t\t\t\t\t\t SCORE: %d \n", score);
			printf("\n");
			i=0;
			no=1;
			while(!feof(x))											//to print any 4 meanings (asc order)
			{	fscanf(x,"%[^\n]",c2);
				i++;
				if(i==random)
				{	printf("\n\t\t\t %d) %s \n", no, c2);
					no++;
				}
				if(i==num1)
				{	printf("\n\t\t\t %d) %s \n", no, c2);
					no++;
				}
				if(i==num2)
			 	{	printf("\n\t\t\t %d) %s \n", no, c2);
					no++;
				}
				if(i==num3)
			 	{	printf("\n\t\t\t %d) %s \n", no, c2);
					no++;
				}
				fgets(c2,strlen(c2),x);	
			}
			fclose(f);
			fclose(x);
		 	
		 	f=fopen("words.txt","r");								//to check answer again opening both files
			x=fopen("meaning.txt","r");
		 	
		 	if(f==NULL || x==NULL)
				printf("\n\t\t\t WORD/MEANING FILE NOT FOUND");
		 	else
		 	{	printf("\n\n\t\t\t ENTER YOUR CHOICE: ");
				scanf("%d", &ans);
				if(index==ans)
				{	printf("\n\t\t\t CONGRATULATIONS!! ");
					printf(" CORRECT ANSWER ");
					score++;
				}		
				else
				{	printf("\n\t\t\t BETTER LUCK NEXT TIME");
					printf("\n\t\t\t THE CORRECT ANSWER IS: ");
					i=0;
					check=1;
					while(i!=random)
					{	fscanf(x,"%[^\n]",c2);	
						i++;
						if(i==random)
					 		printf("%s ", c2);
					fgets(c2,strlen(c2),x);
				  	}
				}
			}
		}
		delay();
	}while(check==0);
	
	printf("\n\n\t\t\t TOTAL SCORE: %d ", score);

	fclose(f);
	fclose(x);
	delay();
}

int main()
{	menu();
	return 0;
}
