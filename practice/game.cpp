//���ҿ��ƹ�꣬�ո��ȷ�� 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
mt19937 rd(time(0));

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
	
	
	
	



                                              ��ʼ��Ϸ
												  
												  
                                              ��Ϸ����)";
    
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
	puts("(�������۾���վ�����ƿ�����ǰ����)");
	Sleep(500);
	puts("(��ǰ����һ���ţ����߹�ȥ�����ƿ�)\n");
	Sleep(1000);
	puts("�����Ƕ�ħ�Ķľ֣�Ҫ���������õ�Ǯ����ǩ���������״��\n");
	Sleep(1000);
	puts("[����״]\nyour name:�����������ո񡢻������ַ����޺��֣����Ȳ����� 10��");
	cin >> name; 
	puts("����[����״]�Ž��˺����");
	Sleep(1500);
	
	round1();
	round2();
	win();
}

int a, b;
vector<int> x, y, q;
string s[] = {"  ǹ  ", "�Ŵ�", "��  ��", "��  ��", "С  ��", "��  ��"}, space = "                                                                  ";
void round1()
{
	system("cls");
	puts("\n\n\n                        Round 1");
	Sleep(3500);
	
	system("cls");
	printf("                ��ħ��               ");
	for(int i = 1; i <= 10 - name.size(); i++) putchar(' ');
	cout << name << "��" << endl << endl; 
	a = b = rd() % 2 + 2;
	change(0, a, 0, b);
	x = {0}, y = {0};
	printf("\n\n         ��ħ��");
	for(int i : x) cout << " " << s[i] << " "; 
	puts("");
	for(int i = 1; i <= 13 - name.size(); i++) putchar(' ');
	cout << name << "��"; 
	for(int i : y) cout << " " << s[i] << " "; 
	puts("\n");
	Sleep(1500);
	
	while(a && b)
	{
		q.clear();
		int num0 = rd() % 3 + 2, num1 = rd() % 3 + 2;
		cursor::gotoxy(0, 5);
		printf("        �����ӵ���%d ��ʵ����%d ���յ�", num1, num0);
		for(int i = 1; i <= num0; i++) q.push_back(0);
		for(int i = 1; i <= num1; i++) q.push_back(1);
		random_shuffle(q.begin(), q.end());
		Sleep(3000);
		cursor::gotoxy(0, 5), puts("        ��ħ����װ������            ");
		Sleep(2000);
		
		int player = 1;
		while(a && b && !q.empty())
			if(player)
			{
				cursor::gotoxy(0, 5);
				puts("        ��Ļغ�         ");
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
				puts("        ��ħ  <<         ��");
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
				cout << "        ��ѡ��ԡ�" << (now == 14 ? "��ħ" : "�Լ�") << "�������ӵ���" << endl;
				Sleep(1000);
				printf("        �ⷢ�ӵ��ǡ��� ");
				Sleep(1000);
				int t = q.back(); q.pop_back();
				puts(t ? "ʵ����" : "�յ���");
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
				puts("        ��ħ�Ļغ�         ");
				Sleep(2000);
				int ai = AI();
				cout << "\n        ��ħѡ��ԡ�" << (ai == 0 ? "��" : "�Լ�") << "�������ӵ���" << endl;
				Sleep(1000);
				printf("        �ⷢ�ӵ��ǡ��� ");
				Sleep(1000);
				int t = q.back(); q.pop_back();
				puts(t ? "ʵ����" : "�յ���");
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
	printf("                ��ħ��               ");
	for(int i = 1; i <= 10 - name.size(); i++) putchar(' ');
	cout << name << "��" << endl << endl; 
	a = b = rd() % 2 + 4;
	change(0, a, 0, b);
	x = {0}, y = {0};
	printf("\n\n         ��ħ��");
	for(int i : x) cout << " " << s[i] << " "; 
	puts("");
	for(int i = 1; i <= 13 - name.size(); i++) putchar(' ');
	cout << name << "��"; 
	for(int i : y) cout << " " << s[i] << " "; 
	puts("\n");
	Sleep(1500);
	
	while(a && b)
	{
		cursor::gotoxy(0, 5);
		printf("        ���ڷ��ŵ��ߡ���");
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
		printf("        �����ӵ���%d ��ʵ����%d ���յ�", num1, num0);
		for(int i = 1; i <= num0; i++) q.push_back(0);
		for(int i = 1; i <= num1; i++) q.push_back(1);
		random_shuffle(q.begin(), q.end());
		Sleep(3000);
		cursor::gotoxy(0, 5), puts("        ��ħ����װ������            ");
		Sleep(2000);
		
		int player = 1;
		knife = skip = know = 0;
		while(a && b && !q.empty())
			if(player)
			{
				cursor::gotoxy(0, 5);
				puts("        ��Ļغ�        ");
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
					puts("        ��ħ  <<         ��");
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
					cout << "        ��ѡ��ԡ�" << (now == 14 ? "��ħ" : "�Լ�") << "�������ӵ���" << endl;
					Sleep(1000);
					printf("        �ⷢ�ӵ��ǡ��� ");
					Sleep(1500);
					int t = q.back(); q.pop_back();
					puts(t ? "ʵ����" : "�յ���");
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
						puts("        ��ħ�Ļغ�      ");
						Sleep(500);
						puts("        ��ħ��������δȡ�£������˻غϣ�");
						Sleep(2500);
						skip++, player = 1;
						cursor::gotoxy(0, 6);
						cout << space;
					}
					else if(a && b && !player && skip == 2)
					{
						cursor::gotoxy(0, 5);
						puts("        ��ħ�Ļغ�      ");
						Sleep(1000);
						puts("        ��ħ����������");
						Sleep(2000);
						skip = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
				}
				else if(y[now] == 1)
				{
					cursor::gotoxy(0, 6);
					puts("        ��ʹ���ˡ��Ŵ󾵡���");
					Sleep(1500);
					puts(q.back() ? "        �鿴��ǰ�ӵ���ʵ����" : "        �鿴��ǰ�ӵ����յ�");
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
					puts("        ��ʹ�á����̡����ָ���һ�������");
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
					puts("        ��ʹ�á����ϡ���������һ���ӵ���");
					Sleep(1000);
					printf("        ���ǡ���");
					Sleep(600);
					puts(q.back() ? "ʵ����" : "�յ���");
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
						puts("        ��ʹ���ˡ�С������");
						Sleep(500);
						printf("        �����ж�ǹ�ڡ���");
						Sleep(1000);
						puts("�˺�������!");
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
						puts("        �����Ѿ�ʹ�ù�С����");
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
						puts("        ��ʹ���ˡ�������");
						Sleep(500);
						puts("        ����Ϊ��ħ����������");
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
						puts("        ��ħ�Ѿ�����������");
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
				puts("        ��ħ�Ļغ�        ");
				Sleep(2000);
				int ai = AI();
				if(ai <= 0)
				{
					cout << "\n        ��ħѡ��ԡ�" << (ai == 0 ? "��" : "�Լ�") << "�������ӵ���" << endl;
					Sleep(1000);
					printf("        �ⷢ�ӵ��ǡ��� ");
					Sleep(1500);
					int t = q.back(); q.pop_back();
					puts(t ? "ʵ����" : "�յ���");
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
						puts("        ��Ļغ�      ");
						Sleep(500);
						puts("        ��ϧ�������δȡ�£������˻غϣ�");
						Sleep(2500);
						skip++, player = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
					else if(a && b && player && skip == 2)
					{
						cursor::gotoxy(0, 5);
						puts("        ��Ļغ�      ");
						Sleep(1000);
						puts("        ����������������");
						Sleep(2000);
						skip = 0;
						cursor::gotoxy(0, 6);
						cout << space;
					}
				}
				else if(x[ai] == 1)
				{
					cursor::gotoxy(0, 6);
					puts("        ��ħʹ���ˡ��Ŵ󾵡���");
					Sleep(1500);
					puts(q.back() ? "        ��ħ���ڲ鿴��ǰ�ӵ�������ʵ����" : "        ��ħ���ڲ鿴��ǰ�ӵ��������յ���");
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
					puts("        ��ħʹ�á����̡����ָ���һ�������");
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
					puts("        ��ħʹ�á����ϡ���������һ���ӵ���");
					Sleep(1000);
					printf("        ���ǡ���");
					Sleep(600);
					puts(q.back() ? "ʵ����" : "�յ���");
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
					puts("        ��ħʹ���ˡ�С������");
					Sleep(500);
					printf("        �����ж�ǹ�ڡ���");
					Sleep(1000);
					puts("�˺�������!");
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
					puts("        ��ħʹ���ˡ�������");
					Sleep(500);
					puts("        �㱻��ħ������������");
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
		printf("������%d", i);
		Sleep(1);
	}
	Sleep(2000);
	puts("\n\n����õ���װ���ֽ�����ӣ�����ȷ����һ�£�");
	Sleep(1000);
	puts("��֮���������ЩǮ��������׼���õĳ���ԶԶ��ȥ������");
	Sleep(2000);
	if(rd() % 10 == 0)
	{
		puts("������������~~~~~~~~~~~~~��");
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
	puts("ԭ��Ϊ��ħ���̶�(Buckshot Roulette)������ naoliaok_lovely����ȣ���");
	puts("������ַ https://www.luogu.com.cn/blog/511676/e-luo-si-lun-pan-du����ӭ����֧�֣�");
	puts("������ԭ��Ϸһ�£������ٽ���һ�飺");
	
	puts("\n��Ϸ������");
	puts("��ħ���ϵ�����һ�����̶ĵ���Ϸ��������ϧ�����ϵ�����˶�ħ��");
	puts("��������ħ�����Խ�ǮΪ�ջ�����̰�������������Ϸ��");
	puts("��������е�һԱ����Ȼ���㲢�����������ģ��ĳ����Ѿ�ͣ����׼���õĳ�����");
	puts("�ⳡ�غ����������̶ģ��ʹ�չ������"); 
	
	puts("\n��Ϸ����");
	puts("��ͨģʽ�����֣����к������е��ߡ�");
	puts("����ԭ���Ķ�ħ���㲻��ʮ�����ܣ����Ա����в����޸���һ�㣬����ʹ�ý϶���������Ȼ����������Ĳ��ԣ�");
	puts("��ϷΪ�غ��ơ�ÿ�غϿ�ʼ��ʱ�򣬻�������в����ŵ��ߣ�˫����״̬ȫ��������Ȼ������������ж���");
	puts("���β����ڣ�������ʹ�á�ǹ��ǰʹ�����ɵ��ߡ����ʹ����ǹ�������ݵ�ǰ��ҩ����Ч����");
	puts("- ʵ�����е���ʧȥһ�������");
	puts("- �յ������ѡ���ÿյ����Լ�������Լ����ж���");
	puts("һ�����д�գ����������µĻغϡ�ֱ��ĳһ���ĵ�������Ϊֹ��"); 
	
	puts("\n��������Ϸ�ڵ������ã������������� 8 ����");
	puts("�Ŵ󾵣��鿴��ǰ��ҩ�����Ƚ�������ǣ��ڶ�ħʹ�÷Ŵ󾵵�ʱ����Ҳ����֪������ӵ�����Ȼ��ʤ��û��Ӱ�죬��������˫�˶�ս��");
	puts("���̣��ָ�һ���������Ϊ�˷��㣬��ʵ��û�����õ������ޣ����������Ͽ��Ե��ӵ�������Ļ�ĵ�����");
	puts("���ϣ�������ǰ�ӵ���");
	puts("С������һ���ӵ��˺������������ۿյ�����ʵ�������ܵ��ӣ�");
	puts("���������Է�һ���غϡ�");
	
	puts("\n����˫�˶�ս");
	puts("���߱Ƚ��������Բ�û����д��һģʽ����������ͨ���޸ļ򵥵�Դ��ʵ�֣�");
	puts("��������һ�� AI() �����������е�ע�Ͳ���ȡ������������ͨ������һ���ַ�������Ϸ��");
	puts("���У�����ַ�Ϊһ��������ʾʹ�õĵ��ߣ�ǹ���㣩���� 1 ��ʼ��š�");
	puts("����ģ�0 ��ʾ��Է���- ��ʾ���Լ���"); 
	puts("�뱣֤�����Ϸ���������ӹܵ��Ƕ�ħ����û���жϲ����ķǷ��ԣ�"); 
	
	getch();
	zhujiemian();
}