#include<graphics.h>
#include<ctime>
#include<conio.h>
#define BL 100
#define BH 100
bool player = true;
bool open[4][4] = { 0 };
IMAGE p_xiang_1;
IMAGE p_shi_1;
IMAGE p_hu_1;
IMAGE p_bao_1;
IMAGE p_lang_1;
IMAGE p_gou_1;
IMAGE p_mao_1;
IMAGE p_shu_1;

IMAGE p_xiang_0;
IMAGE p_shi_0;
IMAGE p_hu_0;
IMAGE p_bao_0;
IMAGE p_lang_0;
IMAGE p_gou_0;
IMAGE p_mao_0;
IMAGE p_shu_0;
IMAGE p_null;

struct Pieces
{
	IMAGE p;
	int level;
	int player;
};
Pieces ps[16];
Pieces pnull = { p_null,-1,-1 };

bool operator==(Pieces p1, Pieces p2)
{
	if (p1.level == p2.level)
	{
		return true;
	}
	else
	{
		return false;
	}
}
struct  Block
{
	int x;
	int y;
	Pieces c;
};

Block BS[4][4];
void initData();
void initGame();
void drawGame();

//�ж���
//����
bool openBlock(int l, int h);
//�ƶ���
bool MoveBlock(int l, int h, int i, int j);
//ѡ�в������ж���
bool control(int l, int h);

int main()
{
	srand(time(nullptr));
	initgraph(500, 500);
	//setorigin(100, 50);
	initData();
	initGame();
	drawGame();
	player = true;//һ����ҿ�ʼ
	MOUSEMSG m, mm;//ѡ������1��2
	int l, h, i, j;
	while (true)
	{
		m = GetMouseMsg();

		if (m.mkLButton)//�������
		{
			m = GetMouseMsg();
			l = m.x / BL;
			h = m.y / BH;
			if (openBlock(l, h))
			{
				player = !player;
				continue;//����ѭ��
			}
			else
			{
				if (BS[l][h].c.player == player)
				{
					if (control(l, h)) 
					{

						while (true)
						{
							mm = GetMouseMsg();
							if (mm.mkLButton)
							{
								mm = GetMouseMsg();
								i = mm.x / BL;
								j = mm.y / BH;
								break;//�ڶ�����������õ�������ѭ��
							}
						}
						if (MoveBlock(l, h, i, j))
						{
							player = !player;
							continue;
						}
						else
						{
							drawGame();
							continue;
						}
					}
					else
					{
						drawGame();
						continue;
					}
				}
				else
				{
					drawGame();
					continue;//����ѭ��
				}
			}

		}




	}

	_getch();


	return 0;
}

void initData()
{
	loadimage(&p_xiang_0, L"��0.jpg", BL, BH);
	loadimage(&p_shi_0, L"ʨ0.jpg", BL, BH);
	loadimage(&p_hu_0, L"��0.jpg", BL, BH);
	loadimage(&p_bao_0, L"��0.jpg", BL, BH);
	loadimage(&p_lang_0, L"��0.jpg", BL, BH);
	loadimage(&p_gou_0, L"��0.jpg", BL, BH);
	loadimage(&p_mao_0, L"è0.jpg", BL, BH);
	loadimage(&p_shu_0, L"��0.jpg", BL, BH);

	loadimage(&p_xiang_1, L"��1.jpg", BL, BH);
	loadimage(&p_shi_1, L"ʨ1.jpg", BL, BH);
	loadimage(&p_hu_1, L"��1.jpg", BL, BH);
	loadimage(&p_bao_1, L"��1.jpg", BL, BH);
	loadimage(&p_lang_1, L"��1.jpg", BL, BH);
	loadimage(&p_gou_1, L"��1.jpg", BL, BH);
	loadimage(&p_mao_1, L"è1.jpg", BL, BH);
	loadimage(&p_shu_1, L"��1.jpg", BL, BH);


	ps[0] = { p_xiang_0,1,0 };
	ps[1] = { p_shi_0, 2, 0 };
	ps[2] = { p_hu_0, 3, 0 };
	ps[3] = { p_bao_0, 4, 0 };
	ps[4] = { p_lang_0, 5, 0 };
	ps[5] = { p_gou_0, 6, 0 };
	ps[6] = { p_mao_0,7,0 };
	ps[7] = { p_shu_0, 8, 0 };
	ps[8] = { p_xiang_1, 1, 1 };
	ps[9] = { p_shi_1, 2, 1 };
	ps[10] = { p_hu_1, 3, 1 };
	ps[11] = { p_bao_1, 4, 1 };
	ps[12] = { p_lang_1, 5, 1 };
	ps[13] = { p_gou_1, 6, 1 };
	ps[14] = { p_mao_1, 7, 1 };
	ps[15] = { p_shu_1, 8, 1 };

}
void initGame()
{
	bool flag[16] = { false };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int c;
			while (true)
			{
				c = rand() % 16;
				if (!flag[c])
				{
					BS[i][j].c = ps[c];
					flag[c] = true;
					break;
				}
			}
			BS[i][j].x = i * BL;
			BS[i][j].y = j * BH;
		}
	}
}
void drawGame()
{

	cleardevice();
	if (player)
		outtextxy(425, 425, L"�̷��ж�");
	else
		outtextxy(425, 425, L"�췽�ж�");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (open[i][j])
			{
				putimage(BS[i][j].x, BS[i][j].y, &BS[i][j].c.p);
				
			}
			else
			{
				setfillcolor(BROWN);
				fillrectangle(BS[i][j].x, BS[i][j].y,
					BS[i][j].x + BL, BS[i][j].y + BH);
			}
			if (BS[i][j].c==pnull)
			{
				setfillcolor(BLACK);
				fillrectangle(BS[i][j].x, BS[i][j].y,
					BS[i][j].x + BL, BS[i][j].y + BH);
			}
			
		}
	}
	for (int i = 0; i < 5; i++)
	{
		line(0, i * BH, 4 * BL, i * BH);
		line(i * BL, 0, i * BL, 4 * BH);
	}

}
bool openBlock(int l, int h)
{
	if (open[l][h])
	{
		return false;
	}
	else
	{
		open[l][h] = true;
		drawGame();
		return true;
	}
}
bool control(int l, int h)
{
	//����ѡ�п�
	if (!player)
		setlinecolor(GREEN);
	else
		setlinecolor(RED);
	rectangle(BS[l][h].x, BS[l][h].y,
		BS[l][h].x + BL, BS[l][h].y + BH);
	setlinecolor(RGB(255, 255, 255));
	return true;
}
bool MoveBlock(int l, int h, int i, int j)
{
	if (l==i)
	{
		if (h == j + 1 || h == j - 1) {}
		else
			return false;
		
	}
	else if(h==j)
	{
		if (l == i + 1 || l == i - 1) {}
		else
			return false;
	}else
	{
		return false;
	}

	if (BS[i][j].c == pnull)
	{
		BS[i][j].c = BS[l][h].c;
		BS[l][h].c = pnull;
		drawGame();
		return true;
	}//�ƶ�
	else if (BS[l][h].c.player != BS[i][j].c.player)
	{

		if (BS[l][h].c.level < BS[i][j].c.level)
		{
			//����
			BS[i][j].c = pnull;
			BS[i][j].c = BS[l][h].c;
			BS[l][h].c = pnull;
			
			drawGame();
			return true;
		}
		else  if (BS[l][h].c.level == BS[i][j].c.level)
		{
			//����
			BS[i][j].c = pnull;
			BS[l][h].c = pnull;
			drawGame();
			return true;
		}else
		{
			if (BS[l][h].c.level == 8 && BS[i][j].c.level == 1)
			{
				//����
				BS[i][j].c = pnull;
				BS[l][h].c = pnull;
			}
			drawGame();
			return true;
		}
	}
	return false;
}
