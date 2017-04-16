/****************************************************
		文件名称：Main.cpp
		文件	描述：推箱子小游戏
		平台：VS2015 + easyX图形库
		作者: stormG by 九夏师父
		最后修改：26/12/2016
		版本：V1.0

		规则说明：1. WSAD/wsad 控制上下左右
				 2. 按R/r重玩当前关卡
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

//人物坐标的结构体
typedef struct posCharacteristic
{
	int row;//人物所在的行
	int col;//人物所在的列
	bool hideTarget = false; // 是否遮挡指定点的判断，假设人物一开始没有遮挡目标点
} PC;

//建立一张欢迎界面的背景图
IMAGE welcomeImg;
//建立7张图片对象
IMAGE img[7];
//建立messagebox前置窗口句柄
HWND hwnd;
//建立当前关卡数目
int currentStage = 1;

//初始化一个ROW*COL的二维数组(第一关)
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

//第二关
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

//第三关
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

//当前进行操作改变的关卡
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

//----------------函数声明部分-----------------//
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

//主函数入口
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//初始化窗口
	//------------------- 函数执行 --------------------//
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

		//按R/r重玩当前关卡
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
			MessageBox(hwnd, L"闯关成功!\n点击确定进入下一关", L"Complete", MB_SYSTEMMODAL);
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
				MessageBox(hwnd, L"通关！\n敬请期待以后新版本", L"Finish", MB_SYSTEMMODAL);
				exit(0);
				break;
			}

			drawCurrent();
			pInit = findPos();
			pBefore = pInit;
			pAfter = NULL;
		}
	}


	//------------------ 函数执行结束 -----------------//
	
	getchar();
	closegraph();
	return 0;
}


//------------------------函数定义部分-----------------------//

//程序进入界面
void welcome()
{
	loadimage(&welcomeImg, L"背景.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
	putimage(0, 0, &welcomeImg);
	settextstyle(20, 0, L"黑体");
	settextcolor(RGB(50, 50, 255));
	setbkmode(TRANSPARENT);
	outtextxy(220, 200, L"推箱子");
	outtextxy(138, 250, L"作者：stormG by 九夏师父");
	outtextxy(132, 300, L"规则说明 (英文输入法下):");
	outtextxy(128, 320, L"1. WSAD/wsad 控制上下左右");
	outtextxy(155, 340, L"2. 按R/r重玩当前关卡");
	outtextxy(200, 360, L"版本：V1.0");
	outtextxy(141, 400, L"请按下任意键盘键以继续！");
}

//初始化加载图片
void initImg()
{
	loadimage(&img[0], L"人物.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[1], L"初始箱子.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[2], L"箱子完成.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[3], L"指定点.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[4], L"地板.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[5], L"砖头.jpg", PICTURE_SIZE, PICTURE_SIZE);
	loadimage(&img[6], L"外地板.jpg", PICTURE_SIZE, PICTURE_SIZE);
}

void drawCurrent()
{
	BeginBatchDraw();
	//绘制一张地图（第一关）//
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			switch (map_current[r][c])
			{
			case 0:	//人物
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[0]);
				break;
			case 1: //初始箱子
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[1]);
				break;
			case 2:	//箱子完成
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[2]);
				break;
			case 3: //指定点
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[3]);
				break;
			case 4:	//地板
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[4]);
				break;
			case 5: //砖头
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[5]);
				break;
			case 6: //外地板
				putimage(r*PICTURE_SIZE, c*PICTURE_SIZE, &img[6]);
				break;
			}
		}
	}
	EndBatchDraw();
}

//判断当前关卡是否完成
bool isComplete()
{
	int count = 0; //计数一共初始箱子的数目，若为0则表示全部推倒指定位置，返回true
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

//过关后载入下一关的数组元素值
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

//找到当前人物的位置
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

//---------------------上下左右控制函数（程序核心）----------------------//
//左
PC* actionLeft(PC* pos)
{
	//首先判断当前人物左方是否为砖墙,为砖墙则什么也不做
	if (map_current[pos->row - 1][pos->col] == 5)
	{
		return pos;
	}

	//再判断人物下一个坐标是否为地板
	if (map_current[pos->row - 1][pos->col] == 4)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物移动一格
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row - 1][pos->col] = 0;
			pos->hideTarget = false;
		}
		//如果没有占用指定点，则人物移动一格
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row - 1][pos->col] = 0;
		}
		pos->row--;
		return pos;
	}

	//再判断人物下一个坐标是否为指定点，若是则与指定点重合
	if (map_current[pos->row - 1][pos->col] == 3)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物取代下一个指定点
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row - 1][pos->col] = 0;
		}
		//如果之前没有占用指定点，则人物移动一格，取代下一个指定点
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row - 1][pos->col] = 0;
			pos->hideTarget = true;  //表示此时人物已占用指定点
		}
		pos->row--;
		return pos;
	}

	//再判断人物下一个坐标是否为初始箱子
	if (map_current[pos->row - 1][pos->col] == 1)
	{
		//进一步判断箱子的下一个坐标

		//如果箱子下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row - 2][pos->col] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
			}
			pos->row--;
			return pos;
		}
		
		//如果箱子下一个坐标为指定点，则人物和箱子同时移动一格，同时箱子完成取代初始箱子
		if (map_current[pos->row - 2][pos->col] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
			}
			pos->row--;
			return pos;
		}
		
		//其他情况：初始箱子前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row - 2][pos->col] == 1
			|| map_current[pos->row - 2][pos->col] == 2
			|| map_current[pos->row - 2][pos->col] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}
		
	}

	//最后判断人物下一个坐标是否为箱子完成
	if (map_current[pos->row - 1][pos->col] == 2)
	{
		//进一步判断箱子完成的下一个坐标

		//如果箱子完成下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row - 2][pos->col] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 1;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//如果箱子完成下一个坐标为指定点，则人物和箱子同时移动一格
		if (map_current[pos->row - 2][pos->col] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row - 1][pos->col] = 0;
				map_current[pos->row - 2][pos->col] = 2;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//其他情况：箱子完成前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row - 2][pos->col] == 1
			|| map_current[pos->row - 2][pos->col] == 2
			|| map_current[pos->row - 2][pos->col] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}
	}
}

//右
PC* actionRight(PC* pos)
{
	//首先判断当前人物右方是否为砖墙,为砖墙则什么也不做
	if (map_current[pos->row + 1][pos->col] == 5)
	{
		return pos;
	}

	//再判断人物下一个坐标是否为地板
	if (map_current[pos->row + 1][pos->col] == 4)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物移动一格
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row + 1][pos->col] = 0;
			pos->hideTarget = false;
		}
		//如果没有占用指定点，则人物移动一格
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row + 1][pos->col] = 0;
		}
		pos->row++;
		return pos;
	}

	//再判断人物下一个坐标是否为指定点，若是则与指定点重合
	if (map_current[pos->row + 1][pos->col] == 3)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物取代下一个指定点
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row + 1][pos->col] = 0;
		}
		//如果之前没有占用指定点，则人物移动一格，取代下一个指定点
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row + 1][pos->col] = 0;
			pos->hideTarget = true;  //表示此时人物已占用指定点
		}
		pos->row++;
		return pos;
	}

	//再判断人物下一个坐标是否为初始箱子
	if (map_current[pos->row + 1][pos->col] == 1)
	{
		//进一步判断箱子的下一个坐标

		//如果箱子下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row + 2][pos->col] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
			}
			pos->row++;
			return pos;
		}

		//如果箱子下一个坐标为指定点，则人物和箱子同时移动一格，同时箱子完成取代初始箱子
		if (map_current[pos->row + 2][pos->col] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
			}
			pos->row++;
			return pos;
		}

		//其他情况：初始箱子前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row + 2][pos->col] == 1
			|| map_current[pos->row + 2][pos->col] == 2
			|| map_current[pos->row + 2][pos->col] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}

	}

	//最后判断人物下一个坐标是否为箱子完成
	if (map_current[pos->row + 1][pos->col] == 2)
	{
		//进一步判断箱子完成的下一个坐标

		//如果箱子完成下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row + 2][pos->col] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 1;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//如果箱子完成下一个坐标为指定点，则人物和箱子同时移动一格
		if (map_current[pos->row + 2][pos->col] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row + 1][pos->col] = 0;
				map_current[pos->row + 2][pos->col] = 2;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//其他情况：箱子完成前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row + 2][pos->col] == 1
			|| map_current[pos->row + 2][pos->col] == 2
			|| map_current[pos->row + 2][pos->col] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}
	}
}

//上
PC* actionUp(PC* pos)
{
	//首先判断当前人物上方是否为砖墙,为砖墙则什么也不做
	if (map_current[pos->row][pos->col - 1] == 5)
	{
		return pos;
	}

	//再判断人物下一个坐标是否为地板
	if (map_current[pos->row][pos->col - 1] == 4)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物移动一格
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col - 1] = 0;
			pos->hideTarget = false;
		}
		//如果没有占用指定点，则人物移动一格
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col - 1] = 0;
		}
		pos->col--;
		return pos;
	}

	//再判断人物下一个坐标是否为指定点，若是则与指定点重合
	if (map_current[pos->row][pos->col - 1] == 3)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物取代下一个指定点
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col - 1] = 0;
		}
		//如果之前没有占用指定点，则人物移动一格，取代下一个指定点
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col - 1] = 0;
			pos->hideTarget = true;  //表示此时人物已占用指定点
		}
		pos->col--;
		return pos;
	}

	//再判断人物下一个坐标是否为初始箱子
	if (map_current[pos->row][pos->col - 1] == 1)
	{
		//进一步判断箱子的下一个坐标

		//如果箱子下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col - 2] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
			}
			pos->col--;
			return pos;
		}

		//如果箱子下一个坐标为指定点，则人物和箱子同时移动一格，同时箱子完成取代初始箱子
		if (map_current[pos->row][pos->col - 2] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
			}
			pos->col--;
			return pos;
		}

		//其他情况：初始箱子前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row][pos->col - 2] == 1
			|| map_current[pos->row][pos->col - 2] == 2
			|| map_current[pos->row][pos->col - 2] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}

	}

	//最后判断人物下一个坐标是否为箱子完成
	if (map_current[pos->row][pos->col - 1] == 2)
	{
		//进一步判断箱子完成的下一个坐标

		//如果箱子完成下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col - 2] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 1;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//如果箱子完成下一个坐标为指定点，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col - 2] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col - 1] = 0;
				map_current[pos->row][pos->col - 2] = 2;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//其他情况：箱子完成前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row][pos->col - 2] == 1
			|| map_current[pos->row][pos->col - 2] == 2
			|| map_current[pos->row][pos->col - 2] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}
	}
}

//下
PC* actionDown(PC* pos)
{
	//首先判断当前人物下方是否为砖墙,为砖墙则什么也不做
	if (map_current[pos->row][pos->col + 1] == 5)
	{
		return pos;
	}

	//再判断人物下一个坐标是否为地板
	if (map_current[pos->row][pos->col + 1] == 4)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物移动一格
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col + 1] = 0;
			pos->hideTarget = false;
		}
		//如果没有占用指定点，则人物移动一格
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col + 1] = 0;
		}
		pos->col++;
		return pos;
	}

	//再判断人物下一个坐标是否为指定点，若是则与指定点重合
	if (map_current[pos->row][pos->col + 1] == 3)
	{
		//如果之前占用了指定点，则将指定点显示出来，并且人物取代下一个指定点
		if (pos->hideTarget == true)
		{
			map_current[pos->row][pos->col] = 3;
			map_current[pos->row][pos->col + 1] = 0;
		}
		//如果之前没有占用指定点，则人物移动一格，取代下一个指定点
		else
		{
			map_current[pos->row][pos->col] = 4;
			map_current[pos->row][pos->col + 1] = 0;
			pos->hideTarget = true;  //表示此时人物已占用指定点
		}
		pos->col++;
		return pos;
	}

	//再判断人物下一个坐标是否为初始箱子
	if (map_current[pos->row][pos->col + 1] == 1)
	{
		//进一步判断箱子的下一个坐标

		//如果箱子下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col + 2] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
				pos->hideTarget = false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
			}
			pos->col++;
			return pos;
		}

		//如果箱子下一个坐标为指定点，则人物和箱子同时移动一格，同时箱子完成取代初始箱子
		if (map_current[pos->row][pos->col + 2] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
				pos->hideTarget == false;
			}
			//如果没有占用指定点，则人物和箱子移动一格
			else
			{
				map_current[pos->row][pos->col] = 4;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
			}
			pos->col++;
			return pos;
		}

		//其他情况：初始箱子前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row][pos->col + 2] == 1
			|| map_current[pos->row][pos->col + 2] == 2
			|| map_current[pos->row][pos->col + 2] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}

	}

	//最后判断人物下一个坐标是否为箱子完成
	if (map_current[pos->row][pos->col + 1] == 2)
	{
		//进一步判断箱子完成的下一个坐标

		//如果箱子完成下一个坐标为地板，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col + 2] == 4)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 1;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//如果箱子完成下一个坐标为指定点，则人物和箱子同时移动一格
		if (map_current[pos->row][pos->col + 2] == 3)
		{
			//如果人物之前占用了指定点，则将指定点显示出来
			if (pos->hideTarget == true)
			{
				map_current[pos->row][pos->col] = 3;
				map_current[pos->row][pos->col + 1] = 0;
				map_current[pos->row][pos->col + 2] = 2;
			}
			//如果没有占用指定点，则人物和箱子移动一格
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

		//其他情况：箱子完成前面是初始箱子/箱子完成/砖墙
		if (map_current[pos->row][pos->col + 2] == 1
			|| map_current[pos->row][pos->col + 2] == 2
			|| map_current[pos->row][pos->col + 2] == 5)
		{
			//因为推不动箱子，所以什么都不做，直接返回
			return pos;
		}
	}
}