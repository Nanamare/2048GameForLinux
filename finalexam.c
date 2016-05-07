#include <stdio.h>
#include <stdlib.h>
#include <termio.h> // �������� getch�Լ��� ����ϱ� ���� ������� 
#include <time.h>



//������ ���� ��������
int score = 0;

//ù ȭ�� mainscreen.txt�� �ҷ� ������ ���� �迭
int ch[50][50];

//���� ���� ȭ�� endscreen.txt�� �ҷ����� ���ѹ迭
int end[80][80];

//������ score1.txt ���� ������ �ڵ�����
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
//score1.txt. ���Ͽ��� ������ �ҷ��帮�� �ְ��� ã�´�.������ ������ �ڵ�����.
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
	printf("�ְ����� %d �Դϴ�.", score[0]);
	return 0;
}

//ó�� ȭ�� ����
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

//���� ���� ȭ�� ����
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

//�������� getch �Լ�����
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



void plus(int(*plate)[4], char *input) // �̵� �� ���� �پ� �ִ� ���� ������  �����ֱ� ���� �Լ�
{
	int i, j;

	if ((*input == 'w') || (*input == 'W')) // ���� ���Ƴ����Ƿ�, �� ���� �پ��ִ� ������� ���ʴ�� ���Ѵ�.
		for (i = 0; i<3; i++)
		{
			{
				for (j = 0; j<4; j++)
				{
					if (plate[i][j] == plate[i + 1][j]) //�迭���� ������ 2������
					{
						plate[i][j] *= 2;
						plate[i + 1][j] = 0;
						score += plate[i][j];
					}
				}
			}
		}

	else if ((*input == 's') || (*input == 'S')) // �Ʒ��� ���Ƴ����Ƿ�, �� �Ʒ��� �پ��ִ� ���鳢�� ���ʴ�� ���Ѵ�.
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

	else if ((*input == 'a') || (*input == 'A')) // ���� ��� ��������
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

	else if ((*input == 'd') || (*input == 'D')) // ������� ����������
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

void move(int(*plate)[4], char *input) // �̵� �������� ������ ���Ƴֱ� ���� �Լ�
{
	int i, j, k;

	if ((*input == 'w') || (*input == 'W'))
		for (k = 0; k<10; k++) // ����� ������ �ݺ��ؼ� ������ ���Ƴְ� �ϱ� ����
			for (i = 0; i<3; i++)
			{
				{
					for (j = 0; j<4; j++)
					{
						if (plate[i][j] == 0) //�迭���� 0�̸� �����̴°��� �ִ� ���� �־��� ���� ������ �Ѿ
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

	srand((unsigned)time(NULL)); //�������� ������� �ð����� �ʱ�ȭ
	
	width = rand() % 4;
	vertical = rand() % 4;
	system("clear");
	mainscreen();
	printf("Welcome to the 2048 game.\n\n");
	printf("coded by ��õ���б� ��ǻ�� ���а� 3�г� ������\n\n");
	printf("w : ��,   s : �Ʒ�,   a : ����,   d : ������,   b : �ǵ�����\n\n");
	printf("�ƹ�Ű�� �����ּ���.\n\n\n");

	scanf("%c", &input);
	fflush(stdin);
	system("clear");

restart:

	score = 0;

keeprestart :

	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			plate[i][j] = 0;
	plate[width][vertical] = 2; // �� ó�� ������ �� �ƹ� ĭ������ �����ϰ� 2�� ���ܳ��� �ϱ� ����

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
		printf("���� ������ %d �Դϴ�. �ű���� ���� ȭ����!", score);
		input = getch();
		fflush(stdin);
		system("clear");

		for (i = 0; i<3; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				if (plate[i][j] == plate[i + 1][j]) // ���η� ���� ���ڰ� ���� �پ��ִ� ��찡 �ϳ��� ������ finish=1
					finish = 1;
			}
		}

		for (j = 0; j<3; j++)
		{
			for (i = 0; i <= 3; i++)
			{
				if (plate[i][j] == plate[i][j + 1]) // ���η� ���� ���ڰ� ���� �پ��ִ� ��찡 �ϳ��� ������ finish=1
					finish = 1;
			}
		}

		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (plate[i][j] == 0) // �� ĭ�̶� ��������� finish=1
					finish = 1;
			}
		}

		if (finish == 0) // ���� ���ڰ� ���� �پ��ִ� ��찡 �ƾ� ���ų�, ����ִ� ĭ�� ��� �� �̻��� ���� ������ �Ұ����� ���
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

			move(plate, &input); //�����̰�
			plus(plate, &input); //����ϰ�
			move(plate, &input); //�����̰� 3�����Լ��� �� ����Ŭ�� ���������Ѵ�.


			for (i = 0; i<4; i++)
			{
				for (j = 0; j<4; j++)
				{
					if (before[i][j] != plate[i][j]) // �ٷ� ���� ĭ�� ������ ĭ�� �Ϻ��� �������� �����ϱ� ����
						count = 1;
				}
			}

			if (count == 0)//�ٷ��� �迭�� ���ư��� ��� 0�̸� ���ư�������
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
				printf("�� ó������ �ڷ� �� �� �����ϴ�!\n\n");

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
				printf("�ڷΰ���� �ٷ� ���� ���·ιۿ� ���ư� �� �����ϴ�.\n\n");

			count = 1;
		}
	}//���Ϲ� ��

	system("clear");
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			printf("[%5d]", plate[i][j]);
		}

		printf("\n\n\n\n\n");
	}

	//���⿡ ���� ���� �ؽ�Ʈ ��ũ�� ����

	system("clear");
	endscreen();
	savescore();
	printf("\n\n");
	scorecompare();
	printf("\n���� ������ %d �Դϴ�",score);
	printf("\n\nGAME OVER\n\n");
	printf("r : �ٽý���(���� �ʱ�ȭ)\nk : �ٽý���(���� ������ �̾)\ne : ���� ������\n");
	printf("�Է��� ���� :");
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



