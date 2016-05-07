#include <stdio.h>
#include <stdlib.h>
#include <termio.h> // 리눅스용 getch함수를 사용하기 위해 헤더포함 
#include <time.h>



//점수를 위한 전역변수
int score = 0;

//첫 화면 mainscreen.txt를 불러 들어오기 위한 배열
int ch[50][50];

//게임 오버 화면 endscreen.txt를 불러오기 위한배열
int end[80][80];

//점수를 score1.txt 쓴다 없으면 자동생성
int savescore(){
	FILE* fp = NULL;
	fp = fopen("score1.txt", "a+");
	if (fp == NULL){
		printf("file open error\n");
		exit(0);
	}
	fprintf(fp, "%d\n", score);


	fclose(fp);
}
//score1.txt. 파일에서 점수를 불러드리고 최고값을 찾는다.파일이 없으면 자동생성.
int scorecompare(){
	int n = 0;
	int i, j;
	int score[100];
	int tmp;
	FILE* fp = NULL;
	fp = fopen("score1.txt", "a+");
	while (1)
	{
		fscanf(fp, "%d", score + n);
		if (feof(fp)) break;
		n++;
	}

	for (i = 0; i<8; i++){
		for (j = i + 1; j<8; j++){
			if (score[i]<score[j])
			{
				tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;
			}
		}
	}
	fclose(fp);
	printf("최고기록은 %d 입니다.", score[0]);
	return 0;
}

//처음 화면 파일
void mainscreen(){
	int i;
	int j;
	FILE* fp = NULL;
	fp = fopen("mainscreen.txt", "a+");
	for (i = 0; i < 50; i++){
		for (j = 0; j < 50; j++){
		
			fscanf(fp, "%c", &ch[i][j]);
		//	printf("%c",ch[i][j]);
		}
	
	
	}
	for(i=0;i<50;i++){
	for (j=0; j<50; j++){
	printf ("%c",ch[i][j]);
	}
	}
	fclose(fp);

}

//게임 오버 화면 파일
void endscreen(){
	int i;
	int j;
	FILE* fp = NULL;
	fp = fopen("endscreen.txt", "a+");
	for (i = 0; i < 80; i++){
		for (j = 0; j < 80; j++){
		
			fscanf(fp, "%c", &end[i][j]);
		//	printf("%c",end[i][j]);
		}
	
	
	}
	for(i=0;i<80;i++){
	for (j=0; j<80; j++){
	printf ("%c",end[i][j]);
	}
	}
	fclose(fp);

}

//리눅스용 getch 함수구현
int getch(void){

	int ch;

	struct termios buf, save;

	tcgetattr(0, &save);

	buf = save;

	buf.c_lflag &= ~(ICANON | ECHO);

	buf.c_cc[VMIN] = 1;

	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();

	tcsetattr(0, TCSAFLUSH, &save);

	return ch;

}



void plus(int(*plate)[4], char *input) // 이동 시 서로 붙어 있는 수가 같으면  더해주기 위한 함수
{
	int i, j;

	if ((*input == 'w') || (*input == 'W')) // 위로 몰아넣으므로, 맨 위에 붙어있는 수들부터 차례대로 더한다.
		for (i = 0; i<3; i++)
		{
			{
				for (j = 0; j<4; j++)
				{
					if (plate[i][j] == plate[i + 1][j]) //배열값이 같으면 2배해줌
					{
						plate[i][j] *= 2;
						plate[i + 1][j] = 0;
						score += plate[i][j];
					}
				}
			}
		}

	else if ((*input == 's') || (*input == 'S')) // 아래로 몰아넣으므로, 맨 아래에 붙어있는 수들끼리 차례대로 더한다.
		for (i = 3; i>0; i--)
		{
			{
				for (j = 3; j >= 0; j--)
				{
					if (plate[i][j] == plate[i - 1][j])
					{
						plate[i][j] *= 2;
						plate[i - 1][j] = 0;
						score += plate[i][j];
					}
				}
			}
		}

	else if ((*input == 'a') || (*input == 'A')) // 같은 방법 왼쪽으로
		for (j = 0; j<3; j++)
		{
			{
				for (i = 0; i<4; i++)
				{
					if (plate[i][j] == plate[i][j + 1])
					{
						plate[i][j] *= 2;
						plate[i][j + 1] = 0;
						score += plate[i][j];
					}
				}
			}
		}

	else if ((*input == 'd') || (*input == 'D')) // 같은방법 오른쪽으로
		for (j = 3; j>0; j--)
		{
			{
				for (i = 3; i >= 0; i--)
				{
					if (plate[i][j] == plate[i][j - 1])
					{
						plate[i][j] *= 2;
						plate[i][j - 1] = 0;
						score += plate[i][j];
					}
				}
			}
		}
}

void move(int(*plate)[4], char *input) // 이동 방향으로 수들을 몰아넣기 위한 함수
{
	int i, j, k;

	if ((*input == 'w') || (*input == 'W'))
		for (k = 0; k<10; k++) // 충분히 여러번 반복해서 완전히 몰아넣게 하기 위함
			for (i = 0; i<3; i++)
			{
				{
					for (j = 0; j<4; j++)
					{
						if (plate[i][j] == 0) //배열값이 0이면 움직이는곳에 있는 수를 넣어줌 수가 있으면 넘어감
						{
							plate[i][j] = plate[i + 1][j];
							plate[i + 1][j] = 0;

						}
					}
				}
			}

	else if ((*input == 's') || (*input == 'S'))
		for (k = 0; k<10; k++)
			for (i = 3; i>0; i--)
			{
				{
					for (j = 3; j >= 0; j--)
					{
						if (plate[i][j] == 0)
						{
							plate[i][j] = plate[i - 1][j];
							plate[i - 1][j] = 0;
						}
					}
				}
			}

	else if ((*input == 'a') || (*input == 'A'))
		for (k = 0; k<10; k++)
			for (j = 0; j<3; j++)
			{
				{
					for (i = 0; i<4; i++)
					{
						if (plate[i][j] == 0)
						{
							plate[i][j] = plate[i][j + 1];
							plate[i][j + 1] = 0;
						}
					}
				}
			}

	else if ((*input == 'd') || (*input == 'D'))
		for (k = 0; k<10; k++)
			for (j = 3; j>0; j--)
			{
				{
					for (i = 3; i >= 0; i--)
					{
						if (plate[i][j] == 0)
						{
							plate[i][j] = plate[i][j - 1];
							plate[i][j - 1] = 0;
						}
					}
				}
			}
}

void main()
{
	int plate[4][4] = { 0 };
	int before[4][4] = { 0 };

	int i, j, width, vertical, count = 0, first = 0, finish = 0;

	char input;

	srand((unsigned)time(NULL)); //랜덤으로 찍기위해 시간으로 초기화
	
	width = rand() % 4;
	vertical = rand() % 4;
	system("clear");
	mainscreen();
	printf("Welcome to the 2048 game.\n\n");
	printf("coded by 인천대학교 컴퓨터 공학과 3학년 신현성\n\n");
	printf("w : 위,   s : 아래,   a : 왼쪽,   d : 오른쪽,   b : 되돌리기\n\n");
	printf("아무키나 눌러주세요.\n\n\n");

	scanf("%c", &input);
	fflush(stdin);
	system("clear");

restart:

	score = 0;

keeprestart :

	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			plate[i][j] = 0;
	plate[width][vertical] = 2; // 맨 처음 시작할 때 아무 칸에서나 랜덤하게 2가 생겨나게 하기 위함

	while (1)
	{
		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (plate[i][j] != 0)
				{
					printf("[%5d]", plate[i][j]);
				}

				else
					printf("[     ]");
			}
			printf("\n\n\n\n\n");
		}
		printf("현재 점수는 %d 입니다. 신기록을 위해 화이팅!", score);
		input = getch();
		fflush(stdin);
		system("clear");

		for (i = 0; i<3; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				if (plate[i][j] == plate[i + 1][j]) // 세로로 같은 숫자가 서로 붙어있는 경우가 하나라도 있으면 finish=1
					finish = 1;
			}
		}

		for (j = 0; j<3; j++)
		{
			for (i = 0; i <= 3; i++)
			{
				if (plate[i][j] == plate[i][j + 1]) // 가로로 같은 숫자가 서로 붙어있는 경우가 하나라도 있으면 finish=1
					finish = 1;
			}
		}

		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (plate[i][j] == 0) // 한 칸이라도 비어있으면 finish=1
					finish = 1;
			}
		}

		if (finish == 0) // 같은 숫자가 서로 붙어있는 경우가 아얘 없거나, 비어있는 칸도 없어서 더 이상의 게임 진행이 불가능한 경우
			break;

		finish = 0;

		if (input == 'w' || input == 'W' || input == 'a' || input == 'A' || input == 's' || input == 'S' || input == 'd' || input == 'D')
		{
			count = 0;
			first = 1;

			for (i = 0; i<4; i++)
			{
				for (j = 0; j<4; j++)
				{
					before[i][j] = plate[i][j];
				}
			}

			move(plate, &input); //움직이고
			plus(plate, &input); //계산하고
			move(plate, &input); //움직이고 3개의함수는 한 싸이클로 움직여야한다.


			for (i = 0; i<4; i++)
			{
				for (j = 0; j<4; j++)
				{
					if (before[i][j] != plate[i][j]) // 바로 전의 칸과 현재의 칸이 완벽히 같은지를 구별하기 위함
						count = 1;
				}
			}

			if (count == 0)//바로전 배열로 돌아갈때 사용 0이면 돌아갈수있음
				goto end;


			width = rand() % 4;
			vertical = rand() % 4;

			for (i = 0; i<4; i++)
			{
				for (j = 0; j<4; j++)
				{
					if (plate[i][j] == 0)
						count = 1;
				}
			}

			if (count == 1)
				while (1)
				{
				if (plate[width][vertical] == 0)
				{
					plate[width][vertical] = 2;
					break;
				}

				width = rand() % 4;
				vertical = rand() % 4;
				}
		end:
			count = 0;
		}
		else if (input == 'b' || input == 'B')
		{
			if (first == 0)
				printf("맨 처음에는 뒤로 갈 수 없습니다!\n\n");

			else if (count != 1)
				for (i = 0; i<4; i++)
				{
				for (j = 0; j<4; j++)
				{
					plate[i][j] = before[i][j];
					before[i][j] = 0;
				}
				}
			else
				printf("뒤로가기는 바로 전의 상태로밖에 돌아갈 수 없습니다.\n\n");

			count = 1;
		}
	}//와일문 끝

	system("clear");
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			printf("[%5d]", plate[i][j]);
		}

		printf("\n\n\n\n\n");
	}

	//여기에 게임 오버 텍스트 스크린 삽입

	system("clear");
	endscreen();
	savescore();
	printf("\n\n");
	scorecompare();
	printf("\n현재 점수는 %d 입니다",score);
	printf("\n\nGAME OVER\n\n");
	printf("r : 다시시작(점수 초기화)\nk : 다시시작(전판 점수에 이어서)\ne : 게임 나가기\n");
	printf("입력후 엔터 :");
	scanf("%c", &input);

	while (1)
	{
		if (input == 'r' || input == 'R')
		{
			system("clear");
			goto restart;
		}

		else if (input == 'k' || input == 'K')
		{
			system("clear");
			goto keeprestart;
		}

		else if (input == 'e' || input == 'E')
		{
			system("clear");
			break;
		}
	}
}



