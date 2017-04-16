/****************************************************
		�ļ����ƣ�Main.cpp
		�ļ�	������������С��Ϸ
		ƽ̨��VS2015 + easyXͼ�ο�
		����: stormG by ����ʦ��
		����޸ģ�26/12/2016
		�汾��V1.0

		����˵����1. WSAD/wsad ������������
				 2. ��R/r���浱ǰ�ؿ�
*****************************************************/

#include<stdio.h>
#include<graphics.h>
#include<malloc.h>
#include<conio.h>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
#define PICTURE_SIZE 50
#define ROW (WINDOW_HEIGHT/PICTURE_SIZE)
#define COL (WINDOW_WIDTH/PICTURE_SIZE)

//��������Ľṹ��
typedef struct posCharacteristic
{
	int row;//�������ڵ���
	int col;//�������ڵ���
	bool hideTarget = false; // �Ƿ��ڵ�ָ������жϣ���������һ��ʼû���ڵ�Ŀ���
} PC;

//����һ�Ż�ӭ����ı���ͼ
IMAGE welcomeImg;
//����7��ͼƬ����
IMAGE img[7];
//����messageboxǰ�ô��ھ��
HWND hwnd;
//������ǰ�ؿ���Ŀ
int currentStage = 1;

//��ʼ��һ��ROW*COL�Ķ�ά����(��һ��)
int map_1[ROW][COL] = { {6,6,6,5,5,5,6,6,6,6}
					   ,{6,6,6,5,3,5,6,6,6,6}
					   ,{6,6,6,5,4,5,6,6,6,6}
					   ,{5,5,5,5,1,5,5,5,5,5}
					   ,{5,3,4,1,0,1,4,4,3,5}
					   ,{5,5,5,5,1,5,5,5,5,5}
					   ,{6,6,6,5,4,5,6,6,6,6}
					   ,{6,6,6,5,4,5,6,6,6,6}
					   ,{6,6,6,5,3,5,6,6,6,6}
					   ,{6,6,6,5,5,5,6,6,6,6} };

//�ڶ���
int map_2[ROW][COL]= { { 6,6,6,6,5,5,5,5,6,6 }
					  ,{ 6,6,6,5,5,3,3,5,6,6 }
					  ,{ 6,6,6,5,3,3,3,5,6,6 }
					  ,{ 6,6,5,5,4,1,4,5,6,6 }
					  ,{ 6,6,5,4,1,4,1,5,6,6 }
					  ,{ 6,6,5,4,5,1,4,5,5,6 }
					  ,{ 6,6,5,4,5,4,1,4,5,6 }
					  ,{ 6,6,5,4,4,4,4,4,5,6 }
				      ,{ 6,6,5,5,5,0,5,5,5,6 }
					  ,{ 6,6,6,6,5,5,5,6,6,6 } };

//������
int map_3[ROW][COL] = { { 6,6,5,5,5,5,5,5,5,6 }
					   ,{ 6,6,5,4,4,2,4,4,5,6 }
					   ,{ 6,6,5,4,3,1,3,4,5,6 }
					   ,{ 6,6,5,3,1,3,1,3,5,6 }
					   ,{ 6,6,5,1,3,1,3,1,5,6 }
					   ,{ 6,6,5,4,1,3,1,4,5,6 }
					   ,{ 6,6,5,5,4,0,4,4,5,6 }
					   ,{ 6,6,6,5,4,4,5,5,5,6 }
					   ,{ 6,6,6,5,5,5,5,6,6,6 }
				       ,{ 6,6,6,6,6,6,6,6,6,6 } };

//��ǰ���в����ı�Ĺؿ�
int map_current[ROW][COL] = { { 6,6,6,5,5,5,6,6,6,6 }
							 ,{ 6,6,6,5,3,5,6,6,6,6 }
						     ,{ 6,6,6,5,4,5,6,6,6,6 }
							 ,{ 5,5,5,5,1,5,5,5,5,5 }
							 ,{ 5,3,4,1,0,1,4,4,3,5 }
							 ,{ 5,5,5,5,1,5,5,5,5,5 }
						     ,{ 6,6,6,5,4,5,6,6,6,6 }
					         ,{ 6,6,6,5,4,5,6,6,6,6 }
							 ,{ 6,6,6,5,3,5,6,6,6,6 }
							 ,{ 6,6,6,5,5,5,6,6,6,6 } };

//----------------������������-----------------//
void welcome();
void initImg();
void drawCurrent();
bool isComplete();
void transfer(int mapBefore[][COL], int mapAfter[][COL]);
PC* findPos();
PC* actionUp(PC* pos);
PC* actionDown(PC* pos);
PC* actionLeft(PC* pos);
PC* actionRight(PC* pos);
//--------------------------------------------//

//���������
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//��ʼ������
	//------------------- ����ִ�� --------------------//
	welcome();
	getch();
	initImg();
	drawCurrent();
	PC* pInit = findPos();
	PC* pBefore = pInit;
	PC* pAfter = NULL;
	while (1)
	{
		char kbInput=getch();
		switch (kbInput)
		{
		
		case 'W':
		case 'w':
			pAfter = actionUp(pBefore);
			pBefore = pAfter;
			pAfter = NULL;
			break;

		case 'S':
		case 's':
			pAfter = actionDown(pBefore);
			pBefore = pAfter;
			pAfter = NULL;
			break;

		case 'A':
		case 'a':
			pAfter = actionLeft(pBefore);
			pBefore = pAfter;
			pAfter = NULL;
			break;

		case 'D':
		case 'd':
			pAfter = actionRight(pBefore);
			pBefore = pAfter;
			pAfter = NULL;
			break;

		//��R/r���浱ǰ�ؿ�
		case 'r':
		case 'R':
			switch (currentStage)
			{
			case 1:
				transfer(map_current,map_1);
				drawCurrent();
				pInit = findPos();
				pBefore = pInit;
				pAfter = NULL;
				break;
			case 2:
				transfer(map_current, map_2);
				drawCurrent();
				pInit = findPos();
				pBefore = pInit;
				pAfter = NULL;
				break;
			case 3:
				transfer(map_current, map_3);
				drawCurrent();
				pInit = findPos();
				pBefore = pInit;
				pAfter = NULL;
				break;
			}
			break;

		default:
			break;
		}
		drawCurrent();
		if (isComplete())
		{
			MessageBox(hwnd, L"���سɹ�!\n���ȷ��������һ��", L"Complete", MB_SYSTEMMODAL);
			currentStage++;
			switch (currentStage)
			{
			case 2:
				transfer(map_current, map_2);
				break;
			case 3:
				transfer(map_current, map_3);
				break;
			default:
				MessageBox(hwnd, L"ͨ�أ�\n�����ڴ��Ժ��°汾", L"Finish", MB_SYSTEMMODAL);
				exit(0);
				break;
			}

			drawCurrent();
			pInit = findPos();
			pBefore = pInit;
			pAfter = NULL;
		}
	}


	//------------------ ����ִ�н��� -----------------//
	
	getchar();
	closegraph();
	return 0;
}


//------------------------�������岿��-----------------------//

//����������
void welcome()
{
	loadimage(&welcomeImg, L"����.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
	putimage(0, 0, &welcomeImg);
	settextstyle(20, 0, L"����");
	settextcolor(RGB(50, 50, 255));
	setbkmode(TRANSPARENT);
	outtextxy(220, 200, L"������");
	outtextxy(138, 250, L"���ߣ�stormG by ����ʦ��");
	outtextxy(132, 300, L"����˵�� (Ӣ�����뷨��):");
	outtextxy(128, 320, L"1. WSAD/wsad ������������");
	outtextxy(155, 340, L"2. ��R/r���浱ǰ�ؿ�");
	outtextxy(200, 360, L"�汾��V1.0");
	outtextxy(141, 400, L"�밴��������̼��Լ�����");
}

//��ʼ������ͼƬ
void initImg()
{
	loadimage(&img[0], L"����.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[1], L"��ʼ����.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[2], L"�������.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[3], L"ָ����.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[4], L"�ذ�.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[5], L"שͷ.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[6], L"��ذ�.jpg", PICTURE_SIZE, PICTURE_SIZE);
}

void drawCurrent()
{
	BeginBatchDraw();
	//����һ�ŵ�ͼ����һ�أ�//
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			switch (map_current[r][c])
			{
			case 0:	//����
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[0]);
				break;
			case 1: //��ʼ����
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[1]);
				break;
			case 2:	//�������
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[2]);
				break;
			case 3: //ָ����
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[3]);
				break;
			case 4:	//�ذ�
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[4]);
				break;
			case 5: //שͷ
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[5]);
				break;
			case 6: //��ذ�
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[6]);
				break;
			}
		}
	}
	EndBatchDraw();
}

//�жϵ�ǰ�ؿ��Ƿ����
bool isComplete()
{
	int count = 0; //����һ����ʼ���ӵ���Ŀ����Ϊ0���ʾȫ���Ƶ�ָ��λ�ã�����true
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map_current[r][c] == 1)
			{
				count++;
			}
		}
	}
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//���غ�������һ�ص�����Ԫ��ֵ
void transfer(int mapBefore[][COL], int mapAfter[][COL])
{
	for (int r = 0; r < ROW; r++)
	{
		for (int c=0;c<COL;c++)
		{
			mapBefore[r][c] = mapAfter[r][c];
		}
	}
}

//�ҵ���ǰ�����λ��
PC* findPos()
{
	PC* currentPos = NULL;
	currentPos=(PC*)malloc(sizeof(PC));
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map_current[r][c] == 0)
			{
				currentPos->row = r;
				currentPos->col = c;
			}
		}
	}
	return currentPos;
}

//---------------------�������ҿ��ƺ�����������ģ�----------------------//
//��
PC* actionLeft(PC* pos)
{
	//�����жϵ�ǰ�������Ƿ�Ϊשǽ,Ϊשǽ��ʲôҲ����
	if (map_current[pos->row - 1][pos->col] == 5)
	{
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ�ذ�
	if (map_current[pos->row - 1][pos->col] == 4)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ���������������ƶ�һ��
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row - 1][pos->col] = 0;
			pos->hideTarget = false;
		}
		//���û��ռ��ָ���㣬�������ƶ�һ��
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row - 1][pos->col] = 0;
		}
		pos->row--;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊָ���㣬��������ָ�����غ�
	if (map_current[pos->row - 1][pos->col] == 3)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ��������������ȡ����һ��ָ����
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row - 1][pos->col] = 0;
		}
		//���֮ǰû��ռ��ָ���㣬�������ƶ�һ��ȡ����һ��ָ����
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row - 1][pos->col] = 0;
			pos->hideTarget = true;  //��ʾ��ʱ������ռ��ָ����
		}
		pos->row--;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ��ʼ����
	if (map_current[pos->row - 1][pos->col] == 1)
	{
		//��һ���ж����ӵ���һ������

		//���������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row - 2][pos->col] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
			}
			pos->row--;
			return pos;
		}
		
		//���������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��ͬʱ�������ȡ����ʼ����
		if (map_current[pos->row - 2][pos->col] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
			}
			pos->row--;
			return pos;
		}
		
		//�����������ʼ����ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row - 2][pos->col] == 1
			|| map_current[pos->row - 2][pos->col] == 2
			|| map_current[pos->row - 2][pos->col] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}
		
	}

	//����ж�������һ�������Ƿ�Ϊ�������
	if (map_current[pos->row - 1][pos->col] == 2)
	{
		//��һ���ж�������ɵ���һ������

		//������������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row - 2][pos->col] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
				pos->hideTarget = true;
			}
			pos->row--;
			return pos;
		}

		//������������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row - 2][pos->col] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
				pos->hideTarget = true;
			}
			pos->row--;
			return pos;
		}

		//����������������ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row - 2][pos->col] == 1
			|| map_current[pos->row - 2][pos->col] == 2
			|| map_current[pos->row - 2][pos->col] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}
	}
}

//��
PC* actionRight(PC* pos)
{
	//�����жϵ�ǰ�����ҷ��Ƿ�Ϊשǽ,Ϊשǽ��ʲôҲ����
	if (map_current[pos->row + 1][pos->col] == 5)
	{
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ�ذ�
	if (map_current[pos->row + 1][pos->col] == 4)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ���������������ƶ�һ��
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row + 1][pos->col] = 0;
			pos->hideTarget = false;
		}
		//���û��ռ��ָ���㣬�������ƶ�һ��
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row + 1][pos->col] = 0;
		}
		pos->row++;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊָ���㣬��������ָ�����غ�
	if (map_current[pos->row + 1][pos->col] == 3)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ��������������ȡ����һ��ָ����
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row + 1][pos->col] = 0;
		}
		//���֮ǰû��ռ��ָ���㣬�������ƶ�һ��ȡ����һ��ָ����
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row + 1][pos->col] = 0;
			pos->hideTarget = true;  //��ʾ��ʱ������ռ��ָ����
		}
		pos->row++;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ��ʼ����
	if (map_current[pos->row + 1][pos->col] == 1)
	{
		//��һ���ж����ӵ���һ������

		//���������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row + 2][pos->col] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
			}
			pos->row++;
			return pos;
		}

		//���������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��ͬʱ�������ȡ����ʼ����
		if (map_current[pos->row + 2][pos->col] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
			}
			pos->row++;
			return pos;
		}

		//�����������ʼ����ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row + 2][pos->col] == 1
			|| map_current[pos->row + 2][pos->col] == 2
			|| map_current[pos->row + 2][pos->col] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}

	}

	//����ж�������һ�������Ƿ�Ϊ�������
	if (map_current[pos->row + 1][pos->col] == 2)
	{
		//��һ���ж�������ɵ���һ������

		//������������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row + 2][pos->col] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
				pos->hideTarget = true;
			}
			pos->row++;
			return pos;
		}

		//������������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row + 2][pos->col] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
				pos->hideTarget = true;
			}
			pos->row++;
			return pos;
		}

		//����������������ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row + 2][pos->col] == 1
			|| map_current[pos->row + 2][pos->col] == 2
			|| map_current[pos->row + 2][pos->col] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}
	}
}

//��
PC* actionUp(PC* pos)
{
	//�����жϵ�ǰ�����Ϸ��Ƿ�Ϊשǽ,Ϊשǽ��ʲôҲ����
	if (map_current[pos->row][pos->col - 1] == 5)
	{
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ�ذ�
	if (map_current[pos->row][pos->col - 1] == 4)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ���������������ƶ�һ��
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col - 1] = 0;
			pos->hideTarget = false;
		}
		//���û��ռ��ָ���㣬�������ƶ�һ��
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col - 1] = 0;
		}
		pos->col--;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊָ���㣬��������ָ�����غ�
	if (map_current[pos->row][pos->col - 1] == 3)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ��������������ȡ����һ��ָ����
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col - 1] = 0;
		}
		//���֮ǰû��ռ��ָ���㣬�������ƶ�һ��ȡ����һ��ָ����
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col - 1] = 0;
			pos->hideTarget = true;  //��ʾ��ʱ������ռ��ָ����
		}
		pos->col--;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ��ʼ����
	if (map_current[pos->row][pos->col - 1] == 1)
	{
		//��һ���ж����ӵ���һ������

		//���������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col - 2] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
			}
			pos->col--;
			return pos;
		}

		//���������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��ͬʱ�������ȡ����ʼ����
		if (map_current[pos->row][pos->col - 2] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
			}
			pos->col--;
			return pos;
		}

		//�����������ʼ����ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row][pos->col - 2] == 1
			|| map_current[pos->row][pos->col - 2] == 2
			|| map_current[pos->row][pos->col - 2] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}

	}

	//����ж�������һ�������Ƿ�Ϊ�������
	if (map_current[pos->row][pos->col - 1] == 2)
	{
		//��һ���ж�������ɵ���һ������

		//������������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col - 2] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
				pos->hideTarget = true;
			}
			pos->col--;
			return pos;
		}

		//������������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col - 2] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
				pos->hideTarget = true;
			}
			pos->col--;
			return pos;
		}

		//����������������ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row][pos->col - 2] == 1
			|| map_current[pos->row][pos->col - 2] == 2
			|| map_current[pos->row][pos->col - 2] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}
	}
}

//��
PC* actionDown(PC* pos)
{
	//�����жϵ�ǰ�����·��Ƿ�Ϊשǽ,Ϊשǽ��ʲôҲ����
	if (map_current[pos->row][pos->col + 1] == 5)
	{
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ�ذ�
	if (map_current[pos->row][pos->col + 1] == 4)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ���������������ƶ�һ��
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col + 1] = 0;
			pos->hideTarget = false;
		}
		//���û��ռ��ָ���㣬�������ƶ�һ��
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col + 1] = 0;
		}
		pos->col++;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊָ���㣬��������ָ�����غ�
	if (map_current[pos->row][pos->col + 1] == 3)
	{
		//���֮ǰռ����ָ���㣬��ָ������ʾ��������������ȡ����һ��ָ����
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col + 1] = 0;
		}
		//���֮ǰû��ռ��ָ���㣬�������ƶ�һ��ȡ����һ��ָ����
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col + 1] = 0;
			pos->hideTarget = true;  //��ʾ��ʱ������ռ��ָ����
		}
		pos->col++;
		return pos;
	}

	//���ж�������һ�������Ƿ�Ϊ��ʼ����
	if (map_current[pos->row][pos->col + 1] == 1)
	{
		//��һ���ж����ӵ���һ������

		//���������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col + 2] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
				pos->hideTarget = false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
			}
			pos->col++;
			return pos;
		}

		//���������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��ͬʱ�������ȡ����ʼ����
		if (map_current[pos->row][pos->col + 2] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
				pos->hideTarget == false;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
			}
			pos->col++;
			return pos;
		}

		//�����������ʼ����ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row][pos->col + 2] == 1
			|| map_current[pos->row][pos->col + 2] == 2
			|| map_current[pos->row][pos->col + 2] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}

	}

	//����ж�������һ�������Ƿ�Ϊ�������
	if (map_current[pos->row][pos->col + 1] == 2)
	{
		//��һ���ж�������ɵ���һ������

		//������������һ������Ϊ�ذ壬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col + 2] == 4)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
				pos->hideTarget = true;
			}
			pos->col++;
			return pos;
		}

		//������������һ������Ϊָ���㣬�����������ͬʱ�ƶ�һ��
		if (map_current[pos->row][pos->col + 2] == 3)
		{
			//�������֮ǰռ����ָ���㣬��ָ������ʾ����
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
			}
			//���û��ռ��ָ���㣬������������ƶ�һ��
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
				pos->hideTarget = true;
			}
			pos->col++;
			return pos;
		}

		//����������������ǰ���ǳ�ʼ����/�������/שǽ
		if (map_current[pos->row][pos->col + 2] == 1
			|| map_current[pos->row][pos->col + 2] == 2
			|| map_current[pos->row][pos->col + 2] == 5)
		{
			//��Ϊ�Ʋ������ӣ�����ʲô��������ֱ�ӷ���
			return pos;
		}
	}
}