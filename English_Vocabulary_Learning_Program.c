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
#define DelayTime 3000 // 메뉴 복귀 지연시간 (단위: 1/1000초) 
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
	char *FBanner = "*************** 영어단어공부 v0.1 **************\n";

	puts(FBanner);

	WCount = openWord(Dict);     // 단어장 파일 열기

	do {
		system("cls");  // 화면지우기
		puts(FBanner);
		printf("*** 다음 메뉴 중 하나를 선택하세요.\n\n");
		printf("1.입력(A), 2.검색(S), 3.목록(L), 4.암기(M), 5.종료(Q) : ");

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
					printf("\a\a** 단어장이 가득찼습니다!");
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
					printf("\a\a** 단어장이 비어있습니다!");
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
					printf("\a\a** 단어장이 비어있습니다!");
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
					printf("\a\a** 단어장이 비어있습니다!");
					Sleep(DelayTime);
				}
				break;

			case '5':
			case 'Q':
			case 'q':
				printf("%c\n",choice);
				if (WCount > 0) {
					saveWord(Dict, WCount);
					printf("\n\n ** %d개의 단어를 단어장에 저장했습니다.\n", WCount);
				}
				else
					printf("\n\n ** 단어장에 저장할 단어가 없습니다.\n");

				printf("\n\a*** 프로그램을 종료하겠습니다. ***\n");
				Sleep(DelayTime);
				break;

			default:
				printf("\a잘못 입력하셨습니다.\n");
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
		printf("*** 단어장 파일(eng.dic)을 읽을 수 없습니다.\n");
		printf("  - 단어장 파일은 프로그램과 같은 위치에 있어야 합니다.\n");
		printf("  - 선택하세요 - (1) 단어장 새로 만들기  (2) 종료하기 : ");
		while (1) {
			choice = _getche();
			if (choice == '1') {
				printf("\n단어장을 새로 만들었습니다.\n");
				Sleep(2000);
				return rCount;  // 0
			}
			else if (choice == '2') {
				printf("\n프로그램을 종료합니다!\n");
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
		printf("\a단어장에서 %d개의 단어를 읽어들였습니다.\n", rCount);
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
		printf(" \a**단어장 파일 쓰기 오류!\n");
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
	printf("\n단어의 철자을 입력하세요: ");
	fgets(eng[num].word, MaxWLen, stdin);
	printf("\n단어의 뜻을 입력하세요: ");
	fgets(eng[num].mean, MaxMLen, stdin);
	printf("\n단어의 유의어을 입력하세요: ");
	fgets(eng[num].synonym, MaxWLen, stdin);
	printf("\n단어의 반의어을 입력하세요: ");
	fgets(eng[num].antonym, MaxWLen, stdin);
	printf("\n단어의 예문을 입력하세요: ");
	fgets(eng[num].sentence, MaxSLen, stdin);
	printf("목록으로 가려면 Q를 누르시고 더 입력시 아무키나누르세요");
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
		printf("=====[%d]번째 단어=====\n",i+1);
	printf("- 단어 : %s", eng[i].word);
	printf("- 의미 : %s", eng[i].mean);
	printf("- 유의어 : %s", eng[i].synonym);
	printf("- 반의어 : %s", eng[i].antonym);
	printf("- 예문 : %s\n", eng[i].sentence);
	}
	 system("PAUSE");
}

void  searchWord   (EWord *eng, int num)
{
	int i,j;
	char Sword[20];         // 탐색 단어 저장 배열
	printf("뜻을 알고자 하는 단어를 입력하세요: ");
	fgets(Sword, sizeof(Sword), stdin);
	for(i=0;i<num; i++)
		if(strcmp(Sword,eng[i].word)==0)
			j=i;
		
	if(j>=0&&j<=num){
		printf("- 단어 : %s", eng[j].word);
		printf("- 의미 : %s", eng[j].mean);
		printf("- 유의어 : %s", eng[j].synonym);
		printf("- 반의어 : %s", eng[j].antonym);
		printf("- 예문 : %s\n", eng[j].sentence);
		
	}else
			printf("입력한 단어가 없습니다.\n");
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
	printf("- 단어 : %s", eng[a].word);
	printf("단어의 뜻을 보려면 아무키나 누르세요.\n");
	b=_getch();
	printf("- 의미 : %s", eng[a].mean);
		
	system("PAUSE");
			return;
	}
		}
	