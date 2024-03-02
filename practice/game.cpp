//左右控制光标，空格键确定 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
mt19937 rd(random_device{}());

namespace cursor
{
	void gotoxy(int x, int y)
	{
		COORD pos; pos.X = x, pos.Y = y;
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
	}
	void getxy(int &x, int &y)
	{
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO pos;
		GetConsoleScreenBufferInfo(output, &pos);
		x = pos.dwCursorPosition.X, y = pos.dwCursorPosition.Y;
	}
	void hide()
	{
		CONSOLE_CURSOR_INFO cursor_info = {1, 0};
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	}
}

void setsize(int col, int row)
{
	char cmd[64];
	sprintf(cmd, "mode con cols=%d lines=%d", col, row);
	system(cmd);
}

void zhujiemian();
void game();
void jieshao();
void round1();
void round2();
void round3();
int AI();
void change(int a1, int a2, int b1, int b2); 
void win();
void lose();

int main()
{
	system("chcp 65001");
	SetConsoleTitle("Buckshot Roulette");
	setsize(104, 30);
	cursor::hide();
	
	zhujiemian();
	return 0;
}

void zhujiemian()
{
	system("cls");
	cout << R"(
	
	
	
  _____                                                   _____ 
 |     \                                                 |     \
 |      |               |          |                     |      |             |
 |     /                |    +---- |              |      |     /              | +---+   |     |   +---+ 
 |====+   |    | +----- |  / |     +----+ +---+ --+--    |-----  +---+ |    | | |   | --+-- --+-- |   |
 |     \  |    | |      |/   +---+ |    | |   |   |      | \     |   | |    | | +---+   |     |   +---+ 
 |      | |    | |      |\       | |    | |   |   |      |   \   |   | |    | | |       |     |   | 
 |_____/  \____/ +----- |  \ ----+ |    | +---+   |      |     \ +---+ \____/ | +----   |     |   +---- 
	
	
	
	



                                              开始游戏
												  
												  
                                              游戏介绍)";
    
    int y = 19;
    cursor::gotoxy(57, y), printf("<<");
    while(1)
    {
    	char ch = getch();
		if(ch == 72 || ch == 75 || ch == 77 || ch == 80)
		{
			cursor::gotoxy(57, y), printf("  ");
			cursor::gotoxy(57, y = 41 - y), printf("<<");
		}
		else if(ch == ' ') break;
	}
	
	if(y == 19) game();
	else jieshao();
}

string name;
void game()
{
	system("cls");
	Sleep(500);
	puts("(你睁开眼睛，站起身推开了面前的门)");
	Sleep(500);
	puts("(面前还有一扇门，你走过去将其推开)\n");
	Sleep(1000);
	puts("“这是恶魔的赌局，要想在这里拿到钱，先签下这份生死状”\n");
	Sleep(1000);
	puts("[生死状]\nyour name:（仅包含除空格、换行外字符，无汉字，长度不超过 10）");
	cin >> name; 
	puts("（将[生死状]放进了盒子里）");
	Sleep(1500);
	
	round1();
	round2();
	win();
}

int a, b;
vector<int> x, y, q;
string s[] = {"  枪  ", "放大镜", "香  烟", "饮  料", "小  刀", "手  铐"}, space = "                                                                  ";
void round1()
{
	system("cls");
	puts("\n\n\n                        Round 1");
	Sleep(3500);
	
	system("cls");
	printf("                恶魔：               ");
	for(int i = 1; i <= 10 - name.size(); i++) putchar(' ');
	cout << name << "：" << endl << endl; 
	a = b = rd() % 2 + 2;
	change(0, a, 0, b);
	x = {0}, y = {0};
	printf("\n\n         恶魔：");
	for(int i : x) cout << " " << s[i] << " "; 
	puts("");
	for(int i = 1; i <= 13 - name.size(); i++) putchar(' ');
	cout << name << "："; 
	for(int i : y) cout << " " << s[i] << " "; 
	puts("\n");
	Sleep(1500);
	
	while(a && b)
	{
		q.clear();
		int num0 = rd() % 3 + 2, num1 = rd() % 3 + 2;
		cursor::gotoxy(0, 5);
		printf("        本轮子弹：%d 发实弹，%d 发空弹", num1, num0);
		for(int i = 1; i <= num0; i++) q.push_back(0);
		for(int i = 1; i <= num1; i++) q.push_back(1);
		random_shuffle(q.begin(), q.end());
		Sleep(3000);
		cursor::gotoxy(0, 5), puts("        恶魔正在装弹……            ");
		Sleep(2000);
		
		int player = 1;
		while(a && b && !q.empty())
			if(player)
			{
				cursor::gotoxy(0, 5);
				puts("        你的回合         ");
				int now = 0;
				cursor::gotoxy(15, 3);
				printf("[");
				cursor::gotoxy(22, 3);
				printf("]");
				while(1)
				{
					char ch = getch();
					if(ch == ' ') break;
				}
				cursor::gotoxy(0, 6);
				puts("        恶魔  <<         你");
				now = 14;
				while(1)
				{
					char ch = getch();
					if(ch == 75 || ch == 77)
					{
						cursor::gotoxy(now, 6);
						printf("  ");
						cursor::gotoxy(now = 43 - now, 6);
						printf("<<");
					}
					if(ch == ' ') break;
				}
				
				cursor::gotoxy(0, 6);
				cout << space << endl;
				cout << "        你选择对【" << (now == 14 ? "恶魔" : "自己") << "】发射子弹！" << endl;
				Sleep(1000);
				printf("        这发子弹是…… ");
				Sleep(1000);
				int t = q.back(); q.pop_back();
				puts(t ? "实弹！" : "空弹！");
				Sleep(1500);
				if(t)
				{
					if(now == 14) change(a, a - 1, b, b), a--;
					else change(a, a, b, b - 1), b--;
					player ^= 1;
				}
				else if(now == 14) player ^= 1;
				cursor::gotoxy(0, 7);
				cout << space << endl << space << endl;
				cursor::gotoxy(15, 3); cout << space;
				cursor::gotoxy(15, 3);
				for(int i : y) cout << " " << s[i] << " "; 
			}
			else
			{
				cursor::gotoxy(0, 5);
				puts("        恶魔的回合         ");
				Sleep(2000);
				int ai = AI();
				cout << "\n        恶魔选择对【" << (ai == 0 ? "你" : "自己") << "】发射子弹！" << endl;
				Sleep(1000);
				printf("        这发子弹是…… ");
				Sleep(1000);
				int t = q.back(); q.pop_back();
				puts(t ? "实弹！" : "空弹！");
				Sleep(1500);
				if(t)
				{
					if(ai == 0) change(a, a, b, b - 1), b--;
					else change(a, a - 1, b, b), a--;
					player ^= 1;
				}
				else if(ai == 0) player ^= 1;
				cursor::gotoxy(0, 7);
				cout << space << endl << space << endl;
			}
	}
	
	system("cls");
	puts("\n\n\n                        You Win!");
	Sleep(3500);
}
int knife, skip, know;
void round2()
{
	system("cls");
	puts("\n\n\n                        Round 2");
	Sleep(3500);
	
	system("cls");
	printf("                恶魔：               ");
	for(int i = 1; i <= 10 - name.size(); i++) putchar(' ');
	cout << name << "：" << endl << endl; 
	a = b = rd() % 2 + 4;
	change(0, a, 0, b);
	x = {0}, y = {0};
	printf("\n\n         恶魔：");
	for(int i : x) cout << " " << s[i] << " "; 
	puts("");
	for(int i = 1; i <= 13 - name.size(); i++) putchar(' ');
	cout << name << "："; 
	for(int i : y) cout << " " << s[i] << " "; 
	puts("\n");
	Sleep(1500);
	
	while(a && b)
	{
		cursor::gotoxy(0, 5);
		printf("        正在发放道具……");
		Sleep(1000);
		cout << space << endl;
		int num = rd() % 2 + 2;
		for(int i = 1; i <= num && x.size() < 9; i++)
		{
			x.push_back(rd() % 5 + 1);
			cursor::gotoxy(8 * x.size() + 8, 2);
			cout << s[x.back()];
			Sleep(500);
		}
		for(int i = 1; i <= num && y.size() < 9; i++)
		{
			y.push_back(rd() % 5 + 1);
			cursor::gotoxy(8 * y.size() + 8, 3);
			cout << s[y.back()];
			Sleep(500);
		}
		q.clear();
		int num0 = rd() % 3 + 2, num1 = rd() % 3 + 2;
		cursor::gotoxy(0, 5);
		printf("        本轮子弹：%d 发实弹，%d 发空弹", num1, num0);
		for(int i = 1; i <= num0; i++) q.push_back(0);
		for(int i = 1; i <= num1; i++) q.push_back(1);
		random_shuffle(q.begin(), q.end());
		Sleep(3000);
		cursor::gotoxy(0, 5), puts("        恶魔正在装弹……            ");
		Sleep(2000);
		
		int player = 1;
		knife = skip = know = 0;
		while(a && b && !q.empty())
			if(player)
			{
				cursor::gotoxy(0, 5);
				puts("        你的回合        ");
				int now = 0;
				cursor::gotoxy(15, 3);
				printf("[");
				cursor::gotoxy(22, 3);
				printf("]");
				while(1)
				{
					char ch = getch();
					if(ch == 75)
					{
						if(now) 
						{
							cursor::gotoxy(8 * now + 15, 3), printf(" ");
							cursor::gotoxy(8 * now + 22, 3), printf(" ");
							now--;
							cursor::gotoxy(8 * now + 15, 3), printf("[");
							cursor::gotoxy(8 * now + 22, 3), printf("]");
						}
					}
					else if(ch == 77)
					{
						if(now < y.size() - 1) 
						{
							cursor::gotoxy(8 * now + 15, 3), printf(" ");
							cursor::gotoxy(8 * now + 22, 3), printf(" ");
							now++;
							cursor::gotoxy(8 * now + 15, 3), printf("[");
							cursor::gotoxy(8 * now + 22, 3), printf("]");
						}
					}
					else if(ch == ' ') break;
				}
				if(y[now] == 0)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔  <<         你");
					now = 14;
					while(1)
					{
						char ch = getch();
						if(ch == 75 || ch == 77)
						{
							cursor::gotoxy(now, 6);
							printf("  ");
							cursor::gotoxy(now = 43 - now, 6);
							printf("<<");
						}
						if(ch == ' ') break;
					}
					
					cursor::gotoxy(0, 6);
					cout << space << endl;
					cout << "        你选择对【" << (now == 14 ? "恶魔" : "自己") << "】发射子弹！" << endl;
					Sleep(1000);
					printf("        这发子弹是…… ");
					Sleep(1500);
					int t = q.back(); q.pop_back();
					puts(t ? "实弹！" : "空弹！");
					Sleep(1000);
					if(t)
					{
						if(now == 14) change(a, max(a - 1 - knife, 0), b, b), a = max(a - 1 - knife, 0);
						else change(a, a, b, max(b - 1 - knife, 0)), b = max(b - 1 - knife, 0);
						player ^= 1;
					}
					else
					{
						Sleep(1000);
						if(now == 14) player ^= 1;
					}
					knife = 0;
					
					cursor::gotoxy(0, 7);
					cout << space << endl << space << endl;
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
					
					if(a && b && !player && skip == 1)
					{
						cursor::gotoxy(0, 5);
						puts("        恶魔的回合      ");
						Sleep(500);
						puts("        恶魔的手铐尚未取下，跳过此回合！");
						Sleep(2500);
						skip++, player = 1;
						cursor::gotoxy(0, 6);
						cout << space;
					}
					else if(a && b && !player && skip == 2)
					{
						cursor::gotoxy(0, 5);
						puts("        恶魔的回合      ");
						Sleep(1000);
						puts("        恶魔挣脱了手铐！");
						Sleep(2000);
						skip = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
				}
				else if(y[now] == 1)
				{
					cursor::gotoxy(0, 6);
					puts("        你使用了【放大镜】！");
					Sleep(1500);
					puts(q.back() ? "        查看当前子弹：实弹！" : "        查看当前子弹：空弹");
					Sleep(2500);
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = now + 1; i < y.size(); i++) swap(y[i - 1], y[i]);
					y.pop_back();
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
				}
				else if(y[now] == 2)
				{
					cursor::gotoxy(0, 6);
					puts("        你使用【香烟】，恢复了一格电量！");
					Sleep(1000);
					change(a, a, b, b + 1), b++;
					cursor::gotoxy(0, 6);
					cout << space;
					for(int i = now + 1; i < y.size(); i++) swap(y[i - 1], y[i]);
					y.pop_back();
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
				}
				else if(y[now] == 3)
				{
					cursor::gotoxy(0, 6);
					puts("        你使用【饮料】，弹出了一颗子弹！");
					Sleep(1000);
					printf("        它是……");
					Sleep(600);
					puts(q.back() ? "实弹！" : "空弹！");
					Sleep(1500);
					q.pop_back();
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = now + 1; i < y.size(); i++) swap(y[i - 1], y[i]);
					y.pop_back();
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
				}
				else if(y[now] == 4)
				{
					if(!knife)
					{
						cursor::gotoxy(0, 6);
						puts("        你使用了【小刀】！");
						Sleep(500);
						printf("        正在切短枪口……");
						Sleep(1000);
						puts("伤害已增加!");
						Sleep(2000);
						knife = 1;
						cursor::gotoxy(0, 6);
						cout << space << endl << space;
						for(int i = now + 1; i < y.size(); i++) swap(y[i - 1], y[i]);
						y.pop_back();
					}
					else
					{
						cursor::gotoxy(0, 6);
						puts("        本轮已经使用过小刀！");
						Sleep(2000); 
						cursor::gotoxy(0, 6);
						cout << space;
					}
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
				}
				else if(y[now] == 5)
				{
					if(!skip)
					{
						cursor::gotoxy(0, 6);
						puts("        你使用了【手铐】！");
						Sleep(500);
						puts("        正在为恶魔戴上手铐……");
						Sleep(2000);
						skip = 1;
						cursor::gotoxy(0, 6);
						cout << space << endl << space;
						for(int i = now + 1; i < y.size(); i++) swap(y[i - 1], y[i]);
						y.pop_back();
					}
					else
					{
						cursor::gotoxy(0, 6);
						puts("        恶魔已经被拷上手铐！");
						Sleep(2000); 
						cursor::gotoxy(0, 6);
						cout << space;
					}
					cursor::gotoxy(15, 3); cout << space;
					cursor::gotoxy(15, 3);
					for(int i : y) cout << " " << s[i] << " "; 
				}
			}
			else
			{
				cursor::gotoxy(0, 5);
				puts("        恶魔的回合        ");
				Sleep(2000);
				int ai = AI();
				if(ai <= 0)
				{
					cout << "\n        恶魔选择对【" << (ai == 0 ? "你" : "自己") << "】发射子弹！" << endl;
					Sleep(1000);
					printf("        这发子弹是…… ");
					Sleep(1500);
					int t = q.back(); q.pop_back();
					puts(t ? "实弹！" : "空弹！");
					Sleep(1000);
					if(t)
					{
						if(ai == 0) change(a, a, b, max(b - 1 - knife, 0)), b = max(b - 1 - knife, 0);
						else change(a, max(a - 1 - knife, 0), b, b), a = max(a - 1 - knife, 0);
						player ^= 1;
					}
					else
					{
						Sleep(1000);
						if(ai == 0) player ^= 1;
					}
					knife = know = 0;
					cursor::gotoxy(0, 7);
					cout << space << endl << space << endl;
					
					if(a && b && player && skip == 1)
					{
						cursor::gotoxy(0, 5);
						puts("        你的回合      ");
						Sleep(500);
						puts("        可惜你的手铐还未取下，跳过此回合！");
						Sleep(2500);
						skip++, player = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
					else if(a && b && player && skip == 2)
					{
						cursor::gotoxy(0, 5);
						puts("        你的回合      ");
						Sleep(1000);
						puts("        你终于挣脱了手铐！");
						Sleep(2000);
						skip = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
				}
				else if(x[ai] == 1)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔使用了【放大镜】！");
					Sleep(1500);
					puts(q.back() ? "        恶魔正在查看当前子弹……（实弹）" : "        恶魔正在查看当前子弹……（空弹）");
					know = 1;
					Sleep(2500);
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = ai + 1; i < x.size(); i++) swap(x[i - 1], x[i]);
					x.pop_back();
					cursor::gotoxy(15, 2); cout << space;
					cursor::gotoxy(15, 2);
					for(int i : x) cout << " " << s[i] << " "; 
				}
				else if(x[ai] == 2)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔使用【香烟】，恢复了一格电量！");
					Sleep(1000);
					change(a, a + 1, b, b), a++;
					cursor::gotoxy(0, 6);
					cout << space;
					for(int i = ai + 1; i < x.size(); i++) swap(x[i - 1], x[i]);
					x.pop_back();
					cursor::gotoxy(15, 2); cout << space;
					cursor::gotoxy(15, 2);
					for(int i : x) cout << " " << s[i] << " "; 
				}
				else if(x[ai] == 3)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔使用【饮料】，弹出了一颗子弹！");
					Sleep(1000);
					printf("        它是……");
					Sleep(600);
					puts(q.back() ? "实弹！" : "空弹！");
					Sleep(1500);
					q.pop_back();
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = ai + 1; i < x.size(); i++) swap(x[i - 1], x[i]);
					x.pop_back();
					cursor::gotoxy(15, 2); cout << space;
					cursor::gotoxy(15, 2);
					for(int i : x) cout << " " << s[i] << " "; 
				}
				else if(x[ai] == 4)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔使用了【小刀】！");
					Sleep(500);
					printf("        正在切短枪口……");
					Sleep(1000);
					puts("伤害已增加!");
					Sleep(2000);
					knife = 1;
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = ai + 1; i < x.size(); i++) swap(x[i - 1], x[i]);
					x.pop_back();
					cursor::gotoxy(15, 2); cout << space;
					cursor::gotoxy(15, 2);
					for(int i : x) cout << " " << s[i] << " "; 
				}
				else if(x[ai] == 5)
				{
					cursor::gotoxy(0, 6);
					puts("        恶魔使用了【手铐】！");
					Sleep(500);
					puts("        你被恶魔戴上了手铐……");
					Sleep(2000);
					skip = 1;
					cursor::gotoxy(0, 6);
					cout << space << endl << space;
					for(int i = ai + 1; i < x.size(); i++) swap(x[i - 1], x[i]);
					x.pop_back();
					cursor::gotoxy(15, 2); cout << space;
					cursor::gotoxy(15, 2);
					for(int i : x) cout << " " << s[i] << " "; 
				}
			}
	}
	
	system("cls");
	puts("\n\n\n                        You Win!");
	Sleep(3500);
}
void round3()
{
	system("cls");
	puts("\n\n\n                        You Win!");
	Sleep(3500);
}

int AI()
{
	/*
    char c;
    while(1)
    {
        c = getch();
        if(c == '-' || '0' <= c && c <= '0' + x.size() - 1) break;
    }
    return c == '-' ? -1 : c - '0'; 
	*/
	
	int num1=0,num0=0;
	for(int i=0;i<q.size();i++)
	{
		if(q[i]==0)num0++;
		else num1++;
	}
	double p=1.0*num1/(num1+num0);
	if(know)
	{
		if(q.back()==0)p=0;
		else p=1;
	}
	int mark[6]={};
	for(int i=1;i<x.size();i++) mark[x[i]]=i;
	if(mark[2]!=0) return mark[2];
	if(!(p<0.3 or p>0.7))
		if(mark[1]!=0) return mark[1];
	if(p<0.3) return -1;
	if(num1+num0>1)
	{
		double p2=p*(num1-1)*(num1+num0-1)+(1.0-p)*num1/(num1+num0-1);
		if(p2>0.6 and skip==0 and mark[5]!=0) return mark[5];
		if(p>0.7 and p2>0.7 and skip==1) return 0;
		if(p2>0.7 and mark[3]!=0) return mark[3];
		if(p>0.7 and knife==0 and mark[4]!=0) return mark[4];
		return 0;
	}
	if(p<0.5)return -1;
	return 0;
}

void change(int a1, int a2, int b1, int b2)
{
	if(!b2) lose();
	Sleep(1000);
	for(int T = 1; T <= 3; T++)
	{
		cursor::gotoxy(22, 0);
		for(int i = 1; i <= a1; i++) putchar('#');
		for(int i = a1 + 1; i <= a2; i++) putchar(' ');
		cursor::gotoxy(49, 0);
		for(int i = 1; i <= b1; i++) putchar('#');
		for(int i = b1 + 1; i <= b2; i++) putchar(' ');
		Sleep(300);
		cursor::gotoxy(22, 0);
		for(int i = 1; i <= a2; i++) putchar('#');
		for(int i = a2 + 1; i <= a1; i++) putchar(' ');
		cursor::gotoxy(49, 0);
		for(int i = 1; i <= b2; i++) putchar('#');
		for(int i = b2 + 1; i <= b1; i++) putchar(' ');
		Sleep(500);
	}
	Sleep(700);
}

void win()
{
	int sum = rd() % 20000 + 10000;
	for(int i = 1; i <= sum; i += rd() % 300)
	{
		system("cls");
		printf("奖励：%d", i);
		Sleep(1);
	}
	Sleep(2000);
	puts("\n\n（你得到了装满现金的箱子，并打开确认了一下）");
	Sleep(1000);
	puts("（之后，你带着这些钱上了早已准备好的车，远远离去……）");
	Sleep(2000);
	if(rd() % 10 == 0)
	{
		puts("（喵喵喵喵喵~~~~~~~~~~~~~）");
		Sleep(1000);
	}
}

void lose()
{
	system("cls");
	Sleep(2000);
	puts("\n\n\n                        You Lose!");
	Sleep(3500);
	exit(0);
}

void jieshao()
{
	system("cls");
	puts("原作为恶魔轮盘赌(Buckshot Roulette)，作者 naoliaok_lovely（洛谷）。");
	puts("博客网址 https://www.luogu.com.cn/blog/511676/e-luo-si-lun-pan-du，欢迎博客支持！");
	puts("规则与原游戏一致，这里再介绍一遍：");
	
	puts("\n游戏背景：");
	puts("恶魔与上帝玩了一个轮盘赌的游戏，不过可惜的是上帝输给了恶魔。");
	puts("后来，恶魔决定以金钱为诱惑，吸引贪婪的人类进行游戏。");
	puts("你就是其中的一员。当然，你并不是来送命的，赌场外已经停好了准备好的车辆。");
	puts("这场关乎生死的轮盘赌，就此展开……"); 
	
	puts("\n游戏规则：");
	puts("普通模式共三轮，其中后两轮有道具。");
	puts("由于原作的恶魔并算不上十分智能，所以本作中不会修改这一点，即会使用较多的随机，当然会加入少量的策略！");
	puts("游戏为回合制。每回合开始的时候，会更换弹夹并发放道具，双方的状态全部消除，然后由玩家率先行动。");
	puts("单次操作内，可以在使用【枪】前使用若干道具。如果使用了枪，则会根据当前弹药触发效果：");
	puts("- 实弹：中弹方失去一格电量。");
	puts("- 空弹：如果选择用空弹打自己，则可以继续行动。");
	puts("一旦弹夹打空，立即进入新的回合。直到某一方的电量归零为止！"); 
	
	puts("\n以下是游戏内道具作用：（有数量上限 8 个）");
	puts("放大镜：查看当前弹药。（比较特殊的是，在恶魔使用放大镜的时候你也可以知道这颗子弹，显然对胜负没有影响，不过方便双人对战）");
	puts("香烟：恢复一格电量。（为了方便，其实并没有设置电量上限，所以理论上可以叠加到超出屏幕的电量）");
	puts("饮料：弹出当前子弹。");
	puts("小刀：下一发子弹伤害翻倍。（无论空弹还是实弹，不能叠加）");
	puts("手铐：跳过对方一个回合。");
	
	puts("\n附：双人对战");
	puts("作者比较懒，所以并没有手写这一模式。不过可以通过修改简单的源码实现：");
	puts("代码中有一个 AI() 函数，将当中的注释部分取消。这样可以通过输入一个字符进行游戏。");
	puts("其中，这个字符为一个数，表示使用的道具（枪不算），从 1 开始编号。");
	puts("特殊的，0 表示打对方，- 表示打自己。"); 
	puts("请保证操作合法！由于你接管的是恶魔，并没有判断操作的非法性！"); 
	
	getch();
	zhujiemian();
}