#include <iostream>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
using namespace std;

struct SHIP{
	//���������� ������ �������
	int y, x;
	//����������� �������(0-��������.;1-����.)
	int dist;
	//���-�� �����
	int desk;
	//���������(0-����,1-���)
	bool life;
};
//�������� �������� ���������
SHIP createShip(int _y,int _x,int _desk,int _district)
{
	SHIP ship;
	ship.life = true;
	ship.x = _x;
	ship.y = _y;
	ship.desk = _desk;
	ship.dist = _district;
	return ship;
}

//���������� ��������
void initArray(int arr[][10]);
//����� ��������
void printArrey(int arr[][10]);
//����� ������� �����
void printField(int arr[][10]);
//����� �������� ���� PC
void printPCField(int arr[][10]);
//����������� ��������
int* setShips(int field[][10], int height, int width, int desk, int vector[]);
//������������� ����������� ��������
void autoSetShips(int field_hum[][10], int field_pc[][10], int height, int width, int ship_qty, int desk, SHIP user_ship[10], SHIP pc_ship[10]);
//�������� �������� �����
bool testAround(int field[][10], int y, int x, int desk, int direct);
//��������� ������ ������
void setOneShip(int field[][10], int y, int x, int desk, int direct);
//��������� ���������� � �� ����� ��� ��������
int getX(char choiseX);
//������ � �������� ����������
bool shootLogic(SHIP user_ship[], int field_hum[][10], int target[], bool direct[]);
//������� �������� ��� ���������� �������� ����������
void cleanLogic(int target[], bool direct[]);
//��������� ����� �� ����������
char getLetter(int x);
//�������� ������� ����� ��������
bool isShipsIsset(int field[][10]);
//����� ������� ��������� ��������� SHIP
void printShipsArrey(SHIP ships[10]);
//�������� ��������� �������(����/�� ����)
bool testShip(SHIP ship, int field[][10]);
//����������� ����� ������ ������� �������
void showDeadShip(SHIP ship, int field[][10]);

//======================================================
//===========�������� ���������=========================
//======================================================
void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	//������ � ������ �����
	const int height = 10, width = 10;
	//����� ���-�� �������� ������ ������
	int ship_qty = 10;
	//���-�� �����
	int desk = 0;
	//������ ���� ������(��� � 0)
	int field_hum[height][width] = {};
	//������ ���� ����������(��� � 0)
	int field_pc[height][width] = {};
	//���� ��� ����������� ����
	char contin = 1;
	bool go_on = true;
	//���� ��� ������� ����
	bool empty = true;
	//��� ����� ��������� ��������
	char choiseX;
	int y, x;
	//��� ���(0 - ������, 1 - ��)
	int WHO = 0;
	//���������� ��������� ������� ��� ai pc
	//target[0] - y; target[1] - x;
	int target[2] = { 10, 10 };
	//����� ��������� ����������� �������� 
	//��� ��������� ������� �����������
	//0-x++; 1-x--; 2-y++; 3-y--;
	bool direct[4] = { true, false, false, false };
	//������� �������� ��������
	SHIP user_ship[10];
	SHIP pc_ship[10];

//======================================================
//===========����������� ��������=======================
//======================================================
	
		
	/**
	1) ����� ������� �����������(�������, �������������);
	2) ��� ������ ������ ���-�� �����, ��������� ������, ���������(��������.,����.)
	*/
	//���������������� ����������� �������� 
	//setShips(field_hum, height, width);
	//**********************************************

	//�������������� ����������� ��������
	autoSetShips(field_hum, field_pc, height, width, ship_qty, desk, user_ship, pc_ship);

	////������ �� ��������
	cout << "\n������� ������ " << endl;
	printShipsArrey(user_ship);
	cout << "\n������� ����������" << endl;
	printShipsArrey(pc_ship);



//*****************************************************************
//====================����========================================*
//*****************************************************************

	do
	{
		//======================================================
		//======����� ������� ����� � ����������� �������=======
		//======================================================

		//����� ����� ������ � ����������:
		//� ���� ������ ��������� ������ field_hum,
		//� ���� �� ����������� �� ������� field_pc
		//� ��������� ������ �������� ��� ����������
		//������� ��� �� �����		
		cout << "\n\t�����\n";
		printField(field_hum);
		cout << "\n\t PC\n";
		printPCField(field_pc);

		//======================================================
		//=======���� ��������� � �������=======================
		//======================================================

		//������ ���� - 0
		//�������(� ����������� �� ��������) 1 - 4;
		//�������� ������ - 5('�');
		//������� �������� - 6('*');

		//��������:��� ������� � �������������� ���� ���������
		//����������� ���� � ���������� ����
		if (WHO == 0)
		{
			cout << "\n��� ������\n";
			//======================================================
			//===========�������� ������============================
			//======================================================

			do
			{
				go_on = false;
				//1)��������� ������������ ��������� ��������
				//2)��������� ����� � �����
				//3)��� ������������ ������-����� ������
				cout << "������� ���������� ��������:\n(����� A-J)(����� 0-9): ";
				cin >> choiseX;
				cin >> y;
				//�������� � �� �����(???�� �������� ��������, ������� ��� ����� ���.����)
				if ((choiseX >= 65 && choiseX <= 90) || (choiseX >= 97 && choiseX <= 122))
				{
					x = getX(choiseX);
				}
				else y = -1;//���� ���� ������������ ������ �����
				//cout << "y = " << y << "; x = " << x << endl;
				//�������� �� ������������ ���������
				if (y < 0 || y >= 10 || x < 0 || x == 10)
				{
					//���� ��������� ����
					go_on = true;
					//������� ���������
					cout << "�� ����� ������������ ������, ��������� ����.\n";
				}

				//�������� ������������ �������� � ��������� ���� ����������
				//����� ��������
				if (!go_on)
				{
					if (field_pc[y][x] == 5 || field_pc[y][x] == 6)
					{
						//���� ��������� ����
						go_on = true;
						//������� ���������
						cout << "�� ���� ��� ��������, �������� ������ ����.\n";
					}
					else
					{
						//���� � ���� ������� 'X'
						if (field_pc[y][x] >= 1 && field_pc[y][x] < 5)
						{
							field_pc[y][x] = 5;//������ �������
							//��������� ��� ������
							WHO = 0;
							cout << "\a\n���������!!!\n";
						}
						//���� ������ ���� '*'
						else if (field_pc[y][x] == 0)
						{
							field_pc[y][x] = 6;
							//��������� ��� ����������
							WHO = 1;
						}
					}
				}

				//�������� �������� ����������
				//� ��������� ������
				int test_y, test_x;
				for (int i = 0; i < 10; i++)
				{
					//���� ������� ����,�� ��� ��� �� ���������
					if (pc_ship[i].life)
					{
						test_y = pc_ship[i].y;
						test_x = pc_ship[i].x;
						//��������� ���� �� ������ �������
						//���� - ���, ��������� ��������� 
						//����� �,���� ��� �����, ������� �������
						//� ������ �������- ����
						if (field_pc[test_y][test_x] == 5)
						{	//���� ������������ ����, ����� ������� 
							if (pc_ship[i].desk == 1 || testShip(pc_ship[i], field_pc))
							{
								//���� ��� ���� �����, ������� �����
								pc_ship[i].life = false;
								//�������� "*" ���� ������ �������
								showDeadShip(pc_ship[i], field_pc);
							}
						}
					}
					
				}
				//��������� ������� ����� �������� � ����������
				if (isShipsIsset(field_pc))
				{
					cout << "\a\a\a\n�� �������� ��� ��������� �������, �� ��������!!!\n";
				}

			} while (go_on);
		}//�������� ������
		//======================================================
		//===========�������� ����������========================
		//======================================================
		else
		{
			cout << "\n��� ����������\n";

			//���� ���� ��������� ������� ���������
			//�������� ������ �������� �� ���������
			if (target[0] != 10)
			{
				if(shootLogic(user_ship,field_hum, target, direct))
				{
					//���� � ������ ������ �������
					//�� ��� ���� ��������� ��� ����������
					WHO = 1;
				}
				else
				{
					//���� � ������ ������������, ���-������
					WHO = 0;
				}
			}
			else//�������� ��������
			{
				do
				{
					x = rand() % 10;
					y = rand() % 10;

					//��������� �������, ���� �������� �� �������
					//�������� ��� �������� �������
				} while (field_hum[y][x] == 5 || field_hum[y][x] == 6);

				//���� ������ � �������
				//�������� ������ �������� �� ���������
				if (field_hum[y][x] >= 1 && field_hum[y][x] < 5)
				{
					cout << "\a\n��������� �����!!!\n";
					cout << getLetter(x) << " - " << y << endl;
					field_hum[y][x] = 5;
					//���������� ���������
					target[0] = y;
					target[1] = x;
					if (shootLogic(user_ship, field_hum, target, direct))
					{
						//���� � ������ ������ �������
						//�� ��� ���� ��������� ��� ����������
						WHO = 1;
					}
					else
					{
						//���� � ������ ������������, ���-������
						WHO = 0;
					}
				}
				else if (field_hum[y][x] == 0)
				{
					//���� ������ � ������ ����,
					//� ���� ������ - '*' � ��� 
					//��������� ������

					field_hum[y][x] = 6;
					cout << getLetter(x) << " - " << y << endl;
					WHO = 0;
				}

			}//else//�������� ��������

			//��������� ������� ����� �������� � ������
			if (isShipsIsset(field_hum))
			{
				cout << "\a\a\a\n� ��� ������ ��� ��������, �� ���������...\n";
			}

		}//�������� ����������


		/**
		-�������� ����������, ������� ����������,���������� � ����,
		-���������� ������� ��� ��� �����.
		*/


		cout << endl;
		cout << "������?(�� - 1; ��� - 0)" << endl;
		cin >> contin;
		contin = (contin != 48)?1:0;

		//������� �����
		system("cls");
	} while (contin);

//*****************************************************************
//===============����� ����=======================================*
//*****************************************************************

}//end MAIN

//======================================================
//==================�������=============================
//======================================================
//������ � �������� ����������
bool shootLogic(SHIP user_ship[], int field_hum[][10], int target[], bool direct[])
{
	/**
	*����� ��������� ��������� �� �������� �� �������
	*���� ����� ��������� ���� ��� ���� ��������� �������
	*/

	//cout << "\n����� � ������ ��������.\n�������� ������:\n";
	//cout << "��������� ���������� y = " << target[0] << "; x = " << target[1] << "\n";
	//cout << "�����������:\n";
	//cout << "������ = " << direct[0];
	//cout << "; ����� = " << direct[1];
	//cout << "; ���� = " << direct[2];
	//cout << "; ����� = " << direct[3];

	//����� ��������� ����������� �������� 
	//��� ��������� ������� �����������
	//0-x++; 1-x--; 2-y++; 3-y--;
	int Y, X;
	Y = target[0];
	X = target[1];
	bool go_on = true;
	//���� �������� ���� ��� �������
	//� ����� �� �����������
	bool flag;
	//���������� ��� �������� ����� �������
	int test_y, test_x;

	flag = true;

	if (direct[0])
	{
		//�������� � ��������� ������ �� ����������� ������
		//���� �� ����������� ��� �� ������� �� ������� ��������
		//��� �� ������� � ������
		int i = 0;
		do
		{
			i++;
			//��������� ���� �� ������ ����
			if (X + i <10)
			{
				//���� ������, ������ ���� � �������� ������
				if (field_hum[Y][X + i] >= 1 && field_hum[Y][X + i] < 5)
				{
					field_hum[Y][X + i] = 5;
					cout << "\a\n��������� �����!!!\n";
					cout << getLetter(X + i) << " - " << Y << endl;
					//��������� ��� �� ��� �������.
					//���� ���-����������,
					//���� ����-������� �� ������ 
					//� ��������� �������� ��� ��� ��������

					//��������� ������� ������,
					//���� �� ���, �� � ���� ������� ������ ������,
					//������ ��� �� �������� ��������� �����.
					//���� ��������, ��� ��� �������, ������ 
					//��� ������ �� - ����� � ������� ���.
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//���� ������������ ����, ����� ������� 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//���� ��� ���� �����, ������� �����
									user_ship[i].life = false;
									//�������� "*" ���� ������ �������
									showDeadShip(user_ship[i], field_hum);
									//�������� ��� ��� ��������� ��������
									cleanLogic(target, direct);
									//������� �� �����,
									//� ��� ��������� �� �����������
									go_on = true;
									break;
								}
							}
						}
					}
				}
				//���� ������������, �������
				//� ��� ��������� ������
				//������� � ������ ����������� ��������
				//� ��������� ��� ����������
				//�������� ������
				//�������� ��� �����������
				else if (field_hum[Y][X + i] == 0)
				{
					field_hum[Y][X + i] = 6;
					cout << "��������� �����������.\n";
					cout << getLetter(X + i) << " - " << Y << endl;
					direct[0] = false;
					direct[1] = true;
					go_on = false;
					flag = false;
				}
				//���� ������ �� ������� �������
				//������� � ������ ����������� ��������
				else if (field_hum[Y][X + i] == 6)
				{
					//��������� ��� ����������� 
					direct[0] = false;
					//� �������� ���������
					direct[1] = true;
					go_on = false;
				}
			}
			else//���� �������� � �������, � ��� ��� ����
			{
				cout << "\n������ � ������ �������\n";
				//�������� ��� �����������
				direct[0] = false;
				//� �������� ���������
				direct[1] = true;
				//������� �� �����,
				//� ��� ��������� �� �����������
				go_on = false;
			}

		} while (go_on);
	}
//-------------�����-----------------------------------------------------------------
	if (direct[1] && flag)
	{
		//��� ������������ do-while ���� �������� �� ����� ����������
		go_on = true;

		//�������� � ��������� ������ �� ����������� �����
		int i = 0;
		do
		{
			i++;
			//��������� ���� �� ������ ����
			if (X - i >= 0)
			{
				//���� ������, ������ ���� � �������� ������
				if (field_hum[Y][X - i] >= 1 && field_hum[Y][X - i] < 5)
				{
					field_hum[Y][X - i] = 5;
					cout << "\a\n��������� �����!!!\n";
					cout << getLetter(X - i) << " - " << Y << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//���� ������������ ����, ����� ������� 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//���� ��� ���� �����, ������� �����
									user_ship[i].life = false;
									//�������� "*" ���� ������ �������
									showDeadShip(user_ship[i], field_hum);
									//�������� ��� ��� ��������� ��������
									cleanLogic(target, direct);
									//������� �� �����,
									//� ��� ��������� �� �����������
									go_on = true;
									break;
								}
							}
						}
					}

				}
				else if (field_hum[Y][X - i] == 0)
				{
					//���� ������������, �������
					//� ��� ��������� ������
					//������� � ������ ����������� ��������
					//� ��������� ��� ����������
					//�������� ������
					//�������� ��� �����������
					field_hum[Y][X - i] = 6;
					cout << "��������� �����������.\n";
					cout << getLetter(X - i) << " - " << Y << endl;
					direct[1] = false;
					direct[2] = true;
					go_on = false;
					flag = false;
				}
				//���� ������ �� ������� �������
				//������� � ������ ����������� ��������
				else if (field_hum[Y][X - i] == 6)
				{
					//��������� ��� ����������� 
					direct[1] = false;
					//� �������� ���������
					direct[2] = true;
					go_on = false;
				}
			}
			else//���� �������� � �������, � ��� ��� ����
			{
				cout << "\n������ � ����� �������\n";
				//��������� ��� ����������� 
				direct[1] = false;
				//� �������� ���������
				direct[2] = true;
				go_on = false;
			}

		} while (go_on);
	}
//---------------����----------------------------------------------------------------------------------
	if (direct[2] && flag)
	{
		//��� ������������ do-while ���� �������� �� ����� ����������
		go_on = true;

		//�������� � ��������� ������ �� ��������� ����
		int i = 0;
		do
		{
			i++;
			//��������� ���� �� ������ ����
			if (Y + i <10)
			{
				//���� ������, ������ ���� � �������� ������
				if (field_hum[Y + i][X] >= 1 && field_hum[Y + i][X] < 5)
				{
					field_hum[Y + i][X] = 5;
					cout << "\a\n��������� �����!!!\n";
					cout << getLetter(X) << " - " << Y + i << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//���� ������������ ����, ����� ������� 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//���� ��� ���� �����, ������� �����
									user_ship[i].life = false;
									//�������� "*" ���� ������ �������
									showDeadShip(user_ship[i], field_hum);
									//�������� ��� ��� ��������� ��������
									cleanLogic(target, direct);
									//������� �� �����,
									//� ��� ��������� �� �����������
									go_on = true;
									break;
								}
							}
						}
					}

				}
				//���� ������������, �������
				//� ��� ��������� ������
				//������� � ������ ����������� ��������
				//� ��������� ��� ����������
				//�������� ������
				//�������� ��� �����������
				else if (field_hum[Y + i][X] == 0)
				{
					field_hum[Y + i][X] = 6;
					cout << "��������� �����������.\n";
					cout << getLetter(X) << " - " << Y + i << endl;
					direct[2] = false;
					direct[3] = true;
					go_on = false;
					flag = false;
				}
				//���� ������ �� ������� �������
				//������� � ������ ����������� ��������
				else if (field_hum[Y + i][X] == 6)
				{
					//��������� ��� ����������� 
					direct[2] = false;
					//� �������� ���������
					direct[3] = true;
					go_on = false;
				}
			}
			else//���� �������� � �������, � ��� ��� ����
			{
				cout << "\n������ � ������ �������\n";
				//��������� ��� ����������� 
				direct[2] = false;
				//� �������� ���������
				direct[3] = true;
				go_on = false;
			}

		} while (go_on);

	}
//----------------�����----------------------------------------------------------------------------
	if (direct[3] && flag)
	{
		//��� ������������ do-while ���� �������� �� ����� ����������
		go_on = true;

		//�������� � ��������� ������ �� ��������� �����
		//�.�. ��� ��������� ��������� �����������
		//����� ���� ��������� ���������(���� �� ���� �������)
		//�������� ��� ������� ��� ��������� ��������� ��������
		int i = 0;
		do
		{
			i++;
			//��������� ���� �� ������ ����
			if (Y - i >= 0)
			{
				//���� ������, ������ ���� � �������� ������
				if (field_hum[Y - i][X] >= 1 && field_hum[Y - i][X]  < 5)
				{
					field_hum[Y - i][X] = 5;
					cout << "\a\n��������� �����!!!\n";
					cout << getLetter(X) << " - " << Y - i << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//���� ������������ ����, ����� ������� 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//���� ��� ���� �����, ������� �����
									user_ship[i].life = false;
									//�������� "*" ���� ������ �������
									showDeadShip(user_ship[i], field_hum);
									//�������� ��� ��� ��������� ��������
									cleanLogic(target, direct);
									//������� �� �����,
									//� ��� ��������� �� �����������
									go_on = true;
									break;
								}
							}
						}
					}

				}
				else if (field_hum[Y - i][X] == 0)
				{
					//���� ������������, �������
					//� ��� ��������� ������
					//�.�. ��� ��������� �����������
					//�������� ��� ������ ���������
					//� ������� ��������
					field_hum[Y - i][X] = 6;
					cout << "��������� �����������.\n";
					cout << getLetter(X) << " - " << Y - i << endl;
					cleanLogic(target, direct);
					go_on = false;
				}
				else if (field_hum[Y - i][X] == 6)
				{
					//���� ������ �� ������� �������
					//������� � ���� ��� ������ ��� 
					//��������� ��������� ��������

					cleanLogic(target, direct);
					go_on = true;
					break;
				}
			}
			else//���� �������� � �������, � ��� ��� ����
			{
				cout<<"\n������ � ������� �������\n";
				//�������� ��� ��� ��������� ��������
				cleanLogic(target, direct);
				//������� �� �����,
				//� ��� ��������� �� �����������
				go_on = true;
				break;
			}

		} while (go_on);
	}

	//��� true ��� �������� � ����������
	//� ���������� ��������� ��������(�����������)
	return go_on;
}
//*******************************************************

//���������� ��������
void initArray(int arr[][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			arr[i][j] = 0;
}
//*********************************************************
//����� ��������
void printArrey(int arr[][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << arr[i][j];
		cout << endl;
	}
}
//*********************************************************
//����� ������� ����� ������
void printField(int arr[][10])
{
	//������� �����
	cout << "\n   A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout.width(2);
			if (arr[i][j] == 5)cout << "X";
			else if (arr[i][j] == 6)cout << "*";
			else if (arr[i][j] == 0)cout << ".";
			else cout << arr[i][j];
		}
		cout << endl;
	}
}

//*********************************************************
//����� ������� ����� PC
void printPCField(int arr[][10])
{
	//���������� ���� ��������� ������.
	//������������ ������ ����� ��������� (6 - '*')
	//� �������� ������ ��������(5 - 'X').
	//������� �����
	cout << "\n   A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout.width(2);
			//���� ���� � �������� ��������
			if (arr[i][j] == 5) cout << "X";
			//���� ���� � ���������
			else if (arr[i][j] == 6) cout << "*";
			//���� ���� ������
			//else cout << ".";
			//��� ������
			else if (arr[i][j] == 0)cout << ".";
			else cout << arr[i][j];
		}
		cout << endl;
	}
}

//*********************************************************
//�������������� ����������� ��������(����� ����������� ��� ������� ������� ��������)
void autoSetShips(int field_hum[][10], int field_pc[][10], int height, int width, int ship_qty, int desk, SHIP user_ship[10], SHIP pc_ship[10])
{
	//������ ��� ��������� y,x,dist �� ��������� ��������
	int vector[3];
	
	int n = 0;
	//������
	for (int i = 4; i > 0; i--)
	{
		//���-�� ����� �������
		desk = i;
		//���-�� �������� ������� desk
		for (int j = 0; j < 5 - desk; j++)
		{
			setShips(field_hum, height, width, desk, vector); 
			user_ship[n] = createShip(vector[0], vector[1], desk, vector[2]);
			n++;
		}
	}
	//����������
	n = 0;
	for (int i = 4; i > 0; i--)
	{
		//���-�� ����� �������
		desk = i;
		//���-�� �������� ������� desk
		for (int j = 0; j < 5 - desk; j++)
		{
			setShips(field_pc, height, width, desk, vector);
			pc_ship[n] = createShip(vector[0], vector[1], desk, vector[2]);
			n++;
		}
	}
}
//*******************************************************

//����������� ��������
int* setShips(int field[][10], int height, int width, int desk, int vector[])
{


	//���� ��� ������� ����
	bool empty;
	//������ ������� �� x,y
	int y, x, direct;

	//��������� ����, ���� �� ������ 
	//���������� ����� ��� �������
	do
	{
		empty = true;
		x = rand() % 10;
		y = rand() % 10;
		//����������� ���������� ������� ������� � ������ ������
		//'0'- �������������, '1'- �����������
		direct = rand() % 2;

		//���� � ��������� ���� ��� ��� �������
		if (field[y][x] == 0)
		{
			//��������� ���������� �� ����� ��� �������
			//�������� ����������� ������������
			if (direct == 0)//���� �������������
			{
				if (x + desk > 9)empty = true;
				else empty = false;
			}
			else if (direct == 1)//���� �����������
			{
				if (y + desk > 9)empty = true;
				else empty = false;
			}
		}

		if (!empty)
		{
			//���� ����� �������, ��������� ��������� ������� ����
			//(����� ������ ��������� ��������� ������������� ������� ����)
			if (y - 1 < 0 && x + 1 >9)
			{
				if (field[y][x - 1] != 0) empty = true;
				if (field[y + 1][x - 1] != 0) empty = true;
				if (field[y + 1][x] != 0) empty = true;
			}
			else if (y - 1 < 0 && x - 1<0)
			{
				if (field[y][x + 1] != 0) empty = true;
				if (field[y + 1][x + 1] != 0) empty = true;
				if (field[y + 1][x] != 0) empty = true;
			}
			else if (y + 1 >9 && x + 1>9)
			{
				if (field[y][x - 1] != 0) empty = true;
				if (field[y - 1][x - 1] != 0) empty = true;
				if (field[y - 1][x] != 0) empty = true;
			}
			else if (y + 1 > 9 && x - 1 < 0)
			{
				if (field[y][x + 1] != 0) empty = true;
				if (field[y - 1][x + 1] != 0) empty = true;
				if (field[y - 1][x] != 0) empty = true;
			}
			else if (y - 1 < 0)
			{
				if (field[y][x - 1] != 0) empty = true;
				if (field[y + 1][x - 1] != 0) empty = true;
				if (field[y + 1][x] != 0) empty = true;
				if (field[y][x + 1] != 0) empty = true;
				if (field[y + 1][x + 1] != 0) empty = true;
			}
			else if (x + 1 > 9)
			{
				if (field[y - 1][x] != 0) empty = true;
				if (field[y - 1][x - 1] != 0) empty = true;
				if (field[y][x - 1] != 0) empty = true;
				if (field[y + 1][x - 1] != 0) empty = true;
				if (field[y + 1][x] != 0) empty = true;
			}
			else if (x + 1 > 9)
			{
				if (field[y][x - 1] != 0) empty = true;
				if (field[y - 1][x - 1] != 0) empty = true;
				if (field[y - 1][x] != 0) empty = true;
				if (field[y - 1][x + 1] != 0) empty = true;
				if (field[y][x + 1] != 0) empty = true;
			}
			else if (x - 1 < 0)
			{
				if (field[y + 1][x] != 0) empty = true;
				if (field[y + 1][x + 1] != 0) empty = true;
				if (field[y][x + 1] != 0) empty = true;
				if (field[y - 1][x + 1] != 0) empty = true;
				if (field[y - 1][x] != 0) empty = true;
			}
			else
			{
				if (field[y - 1][x - 1] != 0) empty = true;
				if (field[y - 1][x] != 0) empty = true;
				if (field[y - 1][x + 1] != 0) empty = true;
				if (field[y + 1][x - 1] != 0) empty = true;
				if (field[y + 1][x] != 0) empty = true;
				if (field[y + 1][x + 1] != 0) empty = true;
				if (field[y][x - 1] != 0) empty = true;
				if (field[y][x + 1] != 0) empty = true;
			}

		}

		if (!empty)
		{
			//��������� ��������� ��������� ����� �������
			empty = testAround(field, y, x, desk, direct);
		}
		//cout <<boolalpha<< empty<<endl;

	} while (empty);

	//����� ���� �������� ������������� �������
	setOneShip(field, y, x, desk, direct);

	//������ ��� �������� �������� � ���������
	vector[0] = y;
	vector[1] = x;
	vector[2] = direct;
	return vector;
}
//*******************************************************
//�������� �������� �����
bool testAround(int field[][10], int y, int x, int desk, int direct)
{
	//���� ������ ������
	bool empty = false;
	//�.�. � ������ ������ ��������� ����,
	//� ��������� ����� ������� ���������
	//������ ���� �� ��� ������ � �� ���������, 
	//�������� �����������(�� ������� ����)
	if (direct == 0)//�������������
	{
		for (int i = 1; i <= desk; i++)
		{
			if (y - 1 >= 0)
			{
				if (field[y - 1][x + i] != 0)
				{
					empty = true;
					break;
				}
			}

			if (field[y][x + i] != 0)
			{
				empty = true;
				break;
			}

			if (y + 1 < 10)
			{
				if (field[y + 1][x + i] != 0)
				{
					empty = true;
					break;
				}
			}
		}
	}
	else if (direct == 1)//�����������
	{
		for (int i = 1; i <= desk; i++)
		{
			if (x - 1 >= 0)
			{
				if (field[y + i][x - 1] != 0)
				{
					empty = true;
					break;
				}
			}

			if (field[y + i][x] != 0)
			{
				empty = true;
				break;
			}

			if (x + 1 < 10)
			{
				if (field[y + i][x + 1] != 0)
				{
					empty = true;
					break;
				}
			}
		}
	}
	return empty;
}
//*******************************************************
//��������� ������ �������
void setOneShip(int field[][10], int y, int x, int desk, int direct)
{

	//����� ���� �������� ������������� �������
	//�� ��������� �����+1, �������� �����������
	//(������������� ��� �����������)
	if (direct == 0)//�������������
	{
		for (int i = 0; i < desk; i++)
		{
			field[y][x + i] = desk;
		}

	}
	else//�����������
	{
		for (int i = 0; i < desk; i++)
		{
			field[y + i][x] = desk;
		}
	}

	//cout << "Set " << desk << "-desk ship, y =" << y << ", x = " << x << ", direct - " << direct<< endl;
	//printField(field);
	//printArrey(field);
}
//*******************************************************
//��������� ���������� � �� ����� ��� ��������
int getX(char choiseX)
{
	int x;
	switch (choiseX)
	{
	case 'A':
	case 'a':
		x = 0;
		break;
	case 'B':
	case 'b':
		x = 1;
		break;
	case 'C':
	case 'c':
		x = 2;
		break;
	case 'D':
	case 'd':
		x = 3;
		break;
	case 'E':
	case 'e':
		x = 4;
		break;
	case 'F':
	case 'f':
		x = 5;
		break;
	case 'G':
	case 'g':
		x = 6;
		break;
	case 'H':
	case 'h':
		x = 7;
		break;
	case 'I':
	case 'i':
		x = 8;
		break;
	case 'J':
	case 'j':
		x = 9;
		break;
	default:
		x = 10;
	}
	return x;
}
//*******************************************************
//������� �������� ��� ���������� �������� ����������
void cleanLogic(int target[], bool direct[])
{
	target[0] = 10;
	target[1] = 10;

	//���� ���������� ���� ������� 
	//������ ���� ����������� ��������
	direct[0] = true;
	direct[1] = false;
	direct[2] = false;
	direct[3] = false;

	//��� � true(������)
	//for (int i = 0; i < 4; i++)
	//{
	//	direct[i] = true;
	//}
}
//*******************************************************
//��������� ����� �� ����������
char getLetter(int x)
{
	char L;
	switch (x)
	{
	case 0:
		L = 'A';
		break;
	case 1:
		L = 'B';
		break;
	case 2:
		L = 'C';
		break;
	case 3:
		L = 'D';
		break;
	case 4:
		L = 'E';
		break;
	case 5:
		L = 'F';
		break;
	case 6:
		L = 'G';
		break;
	case 7:
		L = 'H';
		break;
	case 8:
		L = 'I';
		break;
	case 9:
		L = 'J';
		break;
	default:
		L = 'Z';
	}
	return L;
}
//*******************************************************
//�������� ������� ����� ��������
bool isShipsIsset(int field[][10])
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (field[i][j] == 5)
				count++;
		}
	}

	if (count == 20)return true;
	else return false;

}
//*******************************************************
//����� ������� ��������� ��������� SHIP
void printShipsArrey(SHIP ships[10])
{
	for (int i = 0; i < 10; i++)
	{
		cout << "=========== " << endl;
		cout << "ship[" << i << "]" << endl;
		cout << "y = " << ships[i].y << endl;
		cout << "x = " << ships[i].x << endl;
		cout << "dist = " << ships[i].dist << endl;
		cout << "desk = " << ships[i].desk << endl;
		cout << "life = " << ships[i].life << endl;
	}

}
//*******************************************************
//�������� ��������� �������(����/�� ����)
bool testShip(SHIP ship, int field[][10])
{
	//�������� �������� �� ������ ������
	//�.�. ������ �� ��� ���������
	bool flag = false;
	
	if (ship.dist == 0)//���� �������������� ������������
	{
		for (int i = 1; i < ship.desk; i++)
		{
			(field[ship.y][ship.x + i] == 5) ? flag = true : flag = false;
		}
	}
	else//���� ������������
	{
		for (int i = 1; i < ship.desk; i++)
		{
			(field[ship.y + i][ship.x] == 5) ? flag = true : flag = false;
		}
	}
	
	return flag;
}
//*******************************************************
//����������� ����� ������ ������� �������
void showDeadShip(SHIP ship, int field[][10])
{
	
	int y = ship.y;
	int x = ship.x;	
	
	if (ship.dist == 0)//���� �������������� ������������
	{

		//��������� ������ ����(������ ������ �� � �� ������ "*")
		if (y - 1 < 0 && x + 1 >9)
		{
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			field[y + 1][x] = 6;
		}
		else if (y - 1 < 0 && x - 1<0)
		{
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
			field[y + 1][x + 1] = 6;
			field[y + 1][x] = 6;
		}
		else if (y + 1 >9 && x + 1>9)
		{
			field[y][x - 1] = 6;
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
		}
		else if (y + 1 > 9 && x - 1 < 0)
		{
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
			field[y - 1][x + 1] = 6;
			field[y - 1][x] = 6;
		}
		else if (y - 1 < 0)
		{
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			field[y + 1][x] = 6;
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
			field[y + 1][x + 1] = 6;
		}
		else if (x + 1 > 9)
		{
			field[y - 1][x] = 6;
			field[y - 1][x - 1] = 6;
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			field[y + 1][x] = 6;
		}
		else if (x + 1 > 9)
		{
			field[y][x - 1] = 6;
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
			field[y - 1][x + 1] = 6;
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
		}
		else if (x - 1 < 0)
		{
			field[y + 1][x] = 6;
			field[y + 1][x + 1] = 6;
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
			field[y - 1][x + 1] = 6;
			field[y - 1][x] = 6;
		}
		else
		{
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
			field[y - 1][x + 1] = 6;
			field[y + 1][x - 1] = 6;
			field[y + 1][x] = 6;
			field[y + 1][x + 1] = 6;
			field[y][x - 1] = 6;
			//if (ship.desk == 1)
			field[y][x + 1] = 6;
		}

		//�������� ��������� ����
		for (int i = 1; i < ship.desk; i++)
		{
			//���������� �������� ���� ��� ���������, 
			//������� ���������� � 6 ���������� ����
			field[y][x + i] = 5;
			
			if (y - 1 >= 0 && (x + i + 1)< 10)
			{
				field[y - 1][x + i + 1] = 6;
			}

			if ((x + i + 1) < 10)
			{
				field[y][x + i + 1] = 6;
			}

			if (y + 1 < 10 && (x + i + 1) < 10)
			{
				field[y + 1][x + i + 1] = 6;
			}
		}
	}
	else//���� ������������ ������������
	{

		//��������� ������ ����(�� y ���� �� ������ "*")
		if (y - 1 < 0 && x + 1 >9)
		{
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
		}
		else if (y - 1 < 0 && x - 1<0)
		{
			field[y][x + 1] = 6;
			field[y + 1][x + 1] = 6;
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
		}
		else if (y + 1 >9 && x + 1>9)
		{
			field[y][x - 1] = 6;
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
		}
		else if (y + 1 > 9 && x - 1 < 0)
		{
			field[y][x + 1] = 6;
			field[y - 1][x + 1] = 6;
			field[y - 1][x] = 6;
		}
		else if (y - 1 < 0)
		{
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
			field[y][x + 1] = 6;
			field[y + 1][x + 1] = 6;
		}
		else if (x + 1 > 9)
		{
			field[y - 1][x] = 6;
			field[y - 1][x - 1] = 6;
			field[y][x - 1] = 6;
			field[y + 1][x - 1] = 6;
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
		}
		else if (x + 1 > 9)
		{
			field[y][x - 1] = 6;
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
			field[y - 1][x + 1] = 6;
			field[y][x + 1] = 6;
		}
		else if (x - 1 < 0)
		{
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
			field[y + 1][x + 1] = 6;
			field[y][x + 1] = 6;
			field[y - 1][x + 1] = 6;
			field[y - 1][x] = 6;
		}
		else
		{
			field[y - 1][x - 1] = 6;
			field[y - 1][x] = 6;
			field[y - 1][x + 1] = 6;
			field[y + 1][x - 1] = 6;
			//if (ship.desk == 1)
			field[y + 1][x] = 6;
			field[y + 1][x + 1] = 6;
			field[y][x - 1] = 6;
			field[y][x + 1] = 6;
		}

		//�������� ��������� ����
		for (int i = 1; i < ship.desk; i++)
		{
			//���������� �������� ���� ��� ���������, 
			//������� ���������� � 6 ���������� ����
			field[y+i][x] = 5;

			if (x - 1 >= 0)
			{
				field[y + i + 1][x - 1] = 6;
			}

			if ((y + i +1) < 10)
			{
				field[y+i+1][x] = 6;
			}


			if (x + 1 < 10)
			{
				field[y + i + 1][x + 1] = 6;
			}
		}
	}
	cout << "\a\a\a\n������� ����!!!\n";
}
