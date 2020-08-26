#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
char repword[100],word[100],match[50],stack[]={'\\','/','|','/','0','\\'};
int flag=0,matchlen,top=5,win=-1,len;
void figure(int);
char pop();
void getword()
{
	int i;
	clrscr();
	printf("Enter the word\n");
	flushall();
	gets(word);
	for(i=0;i<strlen(word);i++)
		word[i]=tolower(word[i]);
	printf("The word is %s\n",word);

	len=strlen(word);
	for(i=0;i<strlen(word);i++)
		if(word[i]==' ')
			len=len-1;
	printf("The word contains %d letters\n",len);
}

void replace()
{
	int i=0,j=0,k=0,m=0,z,f1,replen=0;
	char miss[50],rep[50],hit[50];
	do
	{
		printf("Enter letters to hide\n");
		flushall();
		scanf("%c",&rep[replen]);
		if(isalpha(rep[replen]))
		{
			rep[replen]=tolower(rep[replen]);
			replen+=1;
			jump1: printf("Do you wish to hide more letters? 1-Yes 2-No\n");
			flushall();
			scanf("%d",&z);
			if(z==2)
				break;
			if(z!=1)
			{
				printf("Invalid Input\n");
				goto jump1;
			}
		}
		else
		{
			printf("Invalid Input. Please enter an alphabet\n");
			continue;
		}
	}while(1);
	strcpy(repword,word);
	for(i=0;i<replen;i++)
	{
		f1=0;
		for(j=0;j<strlen(repword);j++)
		{
			if(rep[i]==repword[j])
			{
				repword[j]='_';
				match[j]=rep[i];
				hit[k]=rep[i];
				k++;
				f1=1;
			}
		}
		if(f1==0)
		{
			miss[m]=rep[i];
			m++;
		}
	}
	for(i=0;i<k;i++)
	{
		printf("%c ",hit[i]);
		flag=1;
	}
	if(flag==1)
		printf("have been replaced\n");
	if(m>0)
	{
		for(i=0;i<m;i++)
			printf("%c ",miss[i]);
			printf("do not exist in the word\n");
	}
	if((strcmp(repword,word)==0))
	{
		printf("None of the characters have been replaced\nEnter again\n");
		replace();
	}
	printf("The replaced word is - ");
	for(i=0;i<strlen(repword);i++)
	printf("%c ",repword[i]);
	printf("\n");
	printf("The word contains %d letters\n",len);
	jump2: printf("1 - Continue  2 - Reenter the word\n");
	scanf("%d",&z);
	if(z==1)
		return;
	else if (z==2)
	       {	flag=2;
			return;
	       }
	else
		printf("Invalid input\n");
		goto jump2;

}

void playgame()
{
	int tries=6,i,j,k=0,n=0,correct=-1;
	char guess,guesslist[50],shown[50];
	loop:getword();
	     replace();
	     if(flag==2)
		goto loop;

	for(i=0;i<strlen(repword);i++)
	{
		if(repword[i]!='_'&&repword[i]!=' ')
			{
				shown[n]=repword[i];
				n++;
			}
	}

	while(1)
       {
	clrscr();
	figure(tries);

	if(tries>3)
		printf("\n\n\n\n\n");
	else if(tries==3)
		printf("\n\n\n\n");
	else if(tries==2)
		printf("\n\n\n");
	else
		printf("\n\n\n");

	printf("Guess the word. It has %d letters\n",len);
	printf("\n");
	for(i=0;i<strlen(word);i++)
	printf("%c ",repword[i]);
	printf("\n\n");
	printf("You have %d chances\n",tries);
	printf("Enter a letter in lowercase\n");
	jump4: fflush(stdin);
	scanf("%c",&guess);

	if(guess>='a'&&guess<='z')
	{
		for(i=0;i<n;i++)
			if(guess==shown[i])
			{
				printf("The letter is already shown. Try a different letter!\n");
				goto jump4;
			}

		for(i=0;i<k;i++)
			if(guess==guesslist[i])
			{
				printf("You have already guessed this letter. Try a different letter!\n");
				goto jump4;
			}
		guesslist[k++]=guess;
		correct=-1;
		for(i=0;i<strlen(repword);i++)
		{
			if(guess==match[i])
			{	repword[i]=guess;
				correct=1;
			}
		}
		if(correct==1)
		{
			printf("Nice guess!!\n");
			printf("Press ENTER\n");
			getch();
			if(strcmp(repword,word)==0)
				{ win=1;
				  goto jump5;
				}
			continue;
		}
		else
		{
			printf("Wrong guess!\n");
				tries=tries-1;
			if(tries==0)
				{
				 goto jump5;
				}
			printf("You have %d chances left\n",tries);
			printf("Press ENTER\n");
			getch();
			continue;
		  }

	      jump5:if(win==1)
		{
			clrscr();
		      //	printf("\n");
		      //	figure(0);
			printf("\n\n\n");
			printf("\t\tCONGRATULATIONS!! YOU WON!!\n");
			printf("\t\tThe word is - %s\n",word);
			printf("\t\tYOU SAVED THE MAN FROM BEING HANGED!!\n");
			printf("\t\tPress Enter to return to main menu\n");
			getch();
			return;
		}
		else
		{
			clrscr();
			printf("\n");
			figure(0);
			printf("\n\n\n\t\tOH NO!! THE MAN HAS BEEN HANGED\n");
			printf("\t\tYOU LOSE! :(\n");
			printf("\t\tThe word was - %s\n",word);				printf("\t\tPress Enter to return to main menu\n");
			getch();
			return;
		 }
	}
	else
	{
		printf("Invalid Input. Try again\n");
		goto jump4;
	}
       }
}



void figure(int tries)
{
	char part;
	int i,l=0;
       //	if(win!=1)
       //	{
		printf("\t__________\n");
		printf("\t         |\n");
		printf("\t         |\n");
       //	}

	for(i=5;i>=tries;i--)
	{
		part=pop();
		if(part=='|')
			l=1;
		switch(part)
		{
			case '\\': if(l!=1)
				   printf("\t\t%c",part);
				   else
				   printf("%c",part);
				   break;
			case '0': printf("%c",part);
				  break;
			case '/': if(l!=1)
				  printf("%c\n",part);
				  else
				  printf("\t\t%c ",part);
				  break;
			case '|': printf("\t\t %c\n",part);
				  break;
		}
	}
	top=5;
}

char pop()
{
	return stack[top--];
}

void rules()
{
	clrscr();
	printf("\n\n");
	printf("\tRULES FOR HANGMAN GAME\n\n");
	printf("\t1. There are two players. The first player gives the word and the other \t   player guesses it\n");
	printf("\t2. The letters in the word are hidden with blanks by the first player.\n");
	printf("\t3. The second player guesses each letter. For every wrong guess, a body\n\t   part of a man being hanged is drawn\n");
	printf("\t4. The second player gets 6 wrong tries. If the hangman is completed,\n\t   the player loses\n");
	printf("\nPress Enter to return to main menu\n");
	getch();
}

void main()
{
	int choice;
	while(1)
	{
		clrscr();


		printf("\n\n\t||| HANGMAN GAME |||\n\n");
		printf("\tEnter the option\n");
		printf("\t1 - Play game\n");
		printf("\t2 - Rules\n");
		printf("\t3 - Exit\n");
		printf("\t");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: playgame();
				break;
			case 2: rules();
				break;
			case 3: exit(0);
				break;
			default: printf("Invalid input");
		}
	}
	getch();
}