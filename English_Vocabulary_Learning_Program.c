#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>   // for _getche()
#include <stdlib.h>  // for system(), exit() 
#include <Windows.h> // for Sleep()
#include <time.h>    // for time()

#define MaxWord 1000
#define MaxWLen 20
#define MaxMLen 50
#define MaxSLen 160
#define DelayTime 3000 // �޴� ���� �����ð� (����: 1/1000��) 
#define DictName "eng.dic"

typedef struct {
	char word    [MaxWLen];
	char mean    [MaxMLen];
	char synonym [MaxWLen];
	char antonym [MaxWLen];
	char sentence[MaxSLen];

} EWord;

int  openWord  (EWord *);
int  addWord   (EWord *, int);
void listWord  (EWord *, int);
void searchWord(EWord *, int);
void memoryWord(EWord *, int);
void saveWord  (EWord *, int);

int main(void)
{
	EWord Dict[MaxWord] = { 0 };    // Main Dictionary
	char choice;					// Input character
	int line = 0;                   // line counter
	int WCount = 0;					// Total Number of EWord
	char *FBanner = "*************** ����ܾ���� v0.1 **************\n";

	puts(FBanner);

	WCount = openWord(Dict);     // �ܾ��� ���� ����

	do {
		system("cls");  // ȭ�������
		puts(FBanner);
		printf("*** ���� �޴� �� �ϳ��� �����ϼ���.\n\n");
		printf("1.�Է�(A), 2.�˻�(S), 3.���(L), 4.�ϱ�(M), 5.����(Q) : ");

		choice=_getch();
		fflush(stdin);

		switch (choice) {
			case '1':
			case 'A':
			case 'a':
				printf("%c\n",choice);
				if (WCount < MaxWord)
					WCount = addWord(Dict, WCount);
				else {
					printf("\a\a** �ܾ����� ����á���ϴ�!");
					Sleep(DelayTime);
				}
				break;

			case '2':
			case 'S':
			case 's':
				printf("%c\n",choice);
				if (WCount > 0)
					searchWord(Dict, WCount);
				else {
					printf("\a\a** �ܾ����� ����ֽ��ϴ�!");
					Sleep(DelayTime);
				}
				break;

			case '3':
			case 'L':
			case 'l':
				printf("%c\n",choice);
				if (WCount > 0){
				
					listWord(Dict, WCount);
				}
				else {
					printf("\a\a** �ܾ����� ����ֽ��ϴ�!");
					Sleep(DelayTime);
				}
				break;

			case '4':
			case 'M':
			case 'm':
				printf("%c\n",choice);
				if (WCount > 0)
					memoryWord(Dict, WCount);
				else {
					printf("\a\a** �ܾ����� ����ֽ��ϴ�!");
					Sleep(DelayTime);
				}
				break;

			case '5':
			case 'Q':
			case 'q':
				printf("%c\n",choice);
				if (WCount > 0) {
					saveWord(Dict, WCount);
					printf("\n\n ** %d���� �ܾ �ܾ��忡 �����߽��ϴ�.\n", WCount);
				}
				else
					printf("\n\n ** �ܾ��忡 ������ �ܾ �����ϴ�.\n");

				printf("\n\a*** ���α׷��� �����ϰڽ��ϴ�. ***\n");
				Sleep(DelayTime);
				break;

			default:
				printf("\a�߸� �Է��ϼ̽��ϴ�.\n");
				Sleep(DelayTime);
				break;
		}

	} while ((choice != 'q') && (choice != 'Q') && (choice != '5'));

	return 0;
}

int openWord(EWord *pDict)
{
	FILE *file;
	int rCount = 0, line = 0;
	int choice;
	char temp[MaxSLen];			// read buffer


	if ((file = fopen(DictName, "rt")) == NULL) {
		printf("*** �ܾ��� ����(eng.dic)�� ���� �� �����ϴ�.\n");
		printf("  - �ܾ��� ������ ���α׷��� ���� ��ġ�� �־�� �մϴ�.\n");
		printf("  - �����ϼ��� - (1) �ܾ��� ���� �����  (2) �����ϱ� : ");
		while (1) {
			choice = _getche();
			if (choice == '1') {
				printf("\n�ܾ����� ���� ��������ϴ�.\n");
				Sleep(2000);
				return rCount;  // 0
			}
			else if (choice == '2') {
				printf("\n���α׷��� �����մϴ�!\n");
				Sleep(2000);
				exit(0);
			}
			else
				continue;
		}
	}
	else {
		while (fgets(temp, sizeof(temp), file) != NULL) {
			temp[strlen(temp) - 1] = '\0';
			switch (line) {
				case 0:
					strcpy(pDict[rCount].word, temp);
					line++;
					break;
				case 1:
					strcpy(pDict[rCount].mean, temp);
					line++;
					break;
				case 2:
					strcpy(pDict[rCount].synonym, temp);
					line++;
					break;
				case 3:
					strcpy(pDict[rCount].antonym, temp);
					line++;
					break;
				case 4:
					strcpy(pDict[rCount].sentence, temp);
					line = 0;
					rCount++;
					break;
			}
		}
		printf("\a�ܾ��忡�� %d���� �ܾ �о�鿴���ϴ�.\n", rCount);
		Sleep(DelayTime);
		fclose(file);
		return rCount;
	}
}

void saveWord(EWord *pDict, int WNum)
{
	FILE *file;
	int i;

	if ((file = fopen(DictName, "wt")) == NULL) {
		printf(" \a**�ܾ��� ���� ���� ����!\n");
		return;
	}

	for (i = 0; i < WNum; i++) {
		fprintf(file, "%s\n", pDict[i].word);
		fprintf(file, "%s\n", pDict[i].mean);
		fprintf(file, "%s\n", pDict[i].synonym);
		fprintf(file, "%s\n", pDict[i].antonym);
		fprintf(file, "%s\n", pDict[i].sentence);
	}

	fclose(file);
}
int  addWord   (EWord *eng,int num)
{
	int i;
	char j=0;
	for(i=0;j!='Q'&&j!='q';num++){
	printf("\n�ܾ��� ö���� �Է��ϼ���: ");
	fgets(eng[num].word, MaxWLen, stdin);
	printf("\n�ܾ��� ���� �Է��ϼ���: ");
	fgets(eng[num].mean, MaxMLen, stdin);
	printf("\n�ܾ��� ���Ǿ��� �Է��ϼ���: ");
	fgets(eng[num].synonym, MaxWLen, stdin);
	printf("\n�ܾ��� ���Ǿ��� �Է��ϼ���: ");
	fgets(eng[num].antonym, MaxWLen, stdin);
	printf("\n�ܾ��� ������ �Է��ϼ���: ");
	fgets(eng[num].sentence, MaxSLen, stdin);
	printf("������� ������ Q�� �����ð� �� �Է½� �ƹ�Ű����������");
	j=_getch();
	}


	return num;
}
void  listWord   (EWord* eng, int num)
{
	int i,j;
	EWord temp;
	for(i=0; i<num-1; i++){
		for(j=i+1; j<num; j++){
		if(strcmp(eng[i].word,eng[j].word)>0){
			temp=eng[i];
			eng[i]=eng[j];
			eng[j]=temp;
		}
		}
	}
	
	for(i=0; i<num; i++){
		printf("=====[%d]��° �ܾ�=====\n",i+1);
	printf("- �ܾ� : %s", eng[i].word);
	printf("- �ǹ� : %s", eng[i].mean);
	printf("- ���Ǿ� : %s", eng[i].synonym);
	printf("- ���Ǿ� : %s", eng[i].antonym);
	printf("- ���� : %s\n", eng[i].sentence);
	}
	 system("PAUSE");
}

void  searchWord   (EWord *eng, int num)
{
	int i,j;
	char Sword[20];         // Ž�� �ܾ� ���� �迭
	printf("���� �˰��� �ϴ� �ܾ �Է��ϼ���: ");
	fgets(Sword, sizeof(Sword), stdin);
	for(i=0;i<num; i++)
		if(strcmp(Sword,eng[i].word)==0)
			j=i;
		
	if(j>=0&&j<=num){
		printf("- �ܾ� : %s", eng[j].word);
		printf("- �ǹ� : %s", eng[j].mean);
		printf("- ���Ǿ� : %s", eng[j].synonym);
		printf("- ���Ǿ� : %s", eng[j].antonym);
		printf("- ���� : %s\n", eng[j].sentence);
		
	}else
			printf("�Է��� �ܾ �����ϴ�.\n");
	 system("PAUSE");
}
void  memoryWord   (EWord *eng, int num)
{
	int a;
	char b;
	int i;	
	srand(time(NULL)); 
	a= rand() % num;
	for(i=0; a<num; i++)
	{
	printf("- �ܾ� : %s", eng[a].word);
	printf("�ܾ��� ���� ������ �ƹ�Ű�� ��������.\n");
	b=_getch();
	printf("- �ǹ� : %s", eng[a].mean);
		
	system("PAUSE");
			return;
	}
		}
	