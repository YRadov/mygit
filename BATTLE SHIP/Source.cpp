#include <iostream>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
using namespace std;

struct SHIP{
	//координаты начала корабля
	int y, x;
	//направление корабля(0-горизонт.;1-верт.)
	int dist;
	//кол-во палуб
	int desk;
	//состояние(0-убит,1-жив)
	bool life;
};
//создание элемента структуры
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

//заполнение массивов
void initArray(int arr[][10]);
//вывод массивов
void printArrey(int arr[][10]);
//вывод игровых полей
void printField(int arr[][10]);
//вывод игрового поля PC
void printPCField(int arr[][10]);
//расстановка кораблей
int* setShips(int field[][10], int height, int width, int desk, int vector[]);
//автоматическа¤ расстановка кораблей
void autoSetShips(int field_hum[][10], int field_pc[][10], int height, int width, int ship_qty, int desk, SHIP user_ship[10], SHIP pc_ship[10]);
//проверка соседних полей
bool testAround(int field[][10], int y, int x, int desk, int direct);
//установка одного корабл¤
void setOneShip(int field[][10], int y, int x, int desk, int direct);
//получение координаты Х из буквы при выстреле
int getX(char choiseX);
//логика и стрельба компьютера
bool shootLogic(SHIP user_ship[], int field_hum[][10], int target[], bool direct[]);
//очистка массивов для логической стрельбы компьютера
void cleanLogic(int target[], bool direct[]);
//получение буквы по координате
char getLetter(int x);
//проверка наличия живых кораблей
bool isShipsIsset(int field[][10]);
//вывод массива элементов структуры SHIP
void printShipsArrey(SHIP ships[10]);
//проверка состояния корабля(убит/не убит)
bool testShip(SHIP ship, int field[][10]);
//обозначение полей вокруг убитого корабля
void showDeadShip(SHIP ship, int field[][10]);

//======================================================
//===========ИСХОДНЫЕ ПАРАМЕТРЫ=========================
//======================================================
void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	//высота и ширина полей
	const int height = 10, width = 10;
	//общее кол-во кораблей одного игрока
	int ship_qty = 10;
	//кол-во палуб
	int desk = 0;
	//массив поля игрока(все в 0)
	int field_hum[height][width] = {};
	//массив поля компьютера(все в 0)
	int field_pc[height][width] = {};
	//флаг для продолжения игры
	char contin = 1;
	bool go_on = true;
	//флаг для пустого поля
	bool empty = true;
	//для ввода координат выстрела
	char choiseX;
	int y, x;
	//чей ход(0 - игрока, 1 - РС)
	int WHO = 0;
	//координаты подбитого корабля для ai pc
	//target[0] - y; target[1] - x;
	int target[2] = { 10, 10 };
	//флаги изменения направления стрельбы 
	//при добивании корабля компьютером
	//0-x++; 1-x--; 2-y++; 3-y--;
	bool direct[4] = { true, false, false, false };
	//массивы структур кораблей
	SHIP user_ship[10];
	SHIP pc_ship[10];

//======================================================
//===========РАССТАНОВКА КОРАБЛЕЙ=======================
//======================================================
	
		
	/**
	1) выбор способа расстановки(вручную, автоматически);
	2) при ручном запрос кол-ва палуб, координат начала, положение(горизонт.,верт.)
	*/
	//пользовательская расстановка кораблей 
	//setShips(field_hum, height, width);
	//**********************************************

	//автоматическая расстановка кораблей
	autoSetShips(field_hum, field_pc, height, width, ship_qty, desk, user_ship, pc_ship);

	////данные по кораблям
	cout << "\nКОРАБЛИ ИГРОКА " << endl;
	printShipsArrey(user_ship);
	cout << "\nКОРАБЛИ КОМПЬЮТЕРА" << endl;
	printShipsArrey(pc_ship);



//*****************************************************************
//====================ИГРА========================================*
//*****************************************************************

	do
	{
		//======================================================
		//======ВЫВОД ИГРОВЫХ ПОЛЕЙ С ПОЛУЧЕННЫМИ ДАННЫМИ=======
		//======================================================

		//вывод полей игрока и компьютера:
		//в поле игрока выводится массив field_hum,
		//а поле РС проверяется по массиву field_pc
		//и выводятся только выстрелы или пораженные
		//корабли или их части		
		cout << "\n\tИГРОК\n";
		printField(field_hum);
		cout << "\n\t PC\n";
		printPCField(field_pc);

		//======================================================
		//=======ВВОД ВЫСТРЕЛОВ И РАСЧЕТЫ=======================
		//======================================================

		//пустое поле - 0
		//корабли(в зависимости от размеров) 1 - 4;
		//подбитые палубы - 5('Х');
		//прошлые выстрелы - 6('*');

		//проверка:чей выстрел и предоставление хода участнику
		//поразившему цель в предыдущем ходе
		if (WHO == 0)
		{
			cout << "\nХОД ИГРОКА\n";
			//======================================================
			//===========СТРЕЛЬБА ИГРОКА============================
			//======================================================

			do
			{
				go_on = false;
				//1)проверить корректность введенных значений
				//2)перевести буквы в числа
				//3)при некорректных данных-новый запрос
				cout << "Введите координаты выстрела:\n(буква A-J)(число 0-9): ";
				cin >> choiseX;
				cin >> y;
				//получаем х из буквы(???не работает проверка, валится при вводе рус.букв)
				if ((choiseX >= 65 && choiseX <= 90) || (choiseX >= 97 && choiseX <= 122))
				{
					x = getX(choiseX);
				}
				else y = -1;//чтоб были некорректные данные ввода
				//cout << "y = " << y << "; x = " << x << endl;
				//проверка на корректность координат
				if (y < 0 || y >= 10 || x < 0 || x == 10)
				{
					//флаг повторить цикл
					go_on = true;
					//вывести сообщение
					cout << "Вы ввели некорректные данные, повторите ввод.\n";
				}

				//проверка дублирования выстрела и изменения поля противника
				//после выстрела
				if (!go_on)
				{
					if (field_pc[y][x] == 5 || field_pc[y][x] == 6)
					{
						//флаг повторить цикл
						go_on = true;
						//вывести сообщение
						cout << "По полю уже стреляли, выберете другую цель.\n";
					}
					else
					{
						//если в поле корабль 'X'
						if (field_pc[y][x] >= 1 && field_pc[y][x] < 5)
						{
							field_pc[y][x] = 5;//палуба подбита
							//следующий ход игрока
							WHO = 0;
							cout << "\a\nПопадание!!!\n";
						}
						//если пустое поле '*'
						else if (field_pc[y][x] == 0)
						{
							field_pc[y][x] = 6;
							//следующий ход компьютера
							WHO = 1;
						}
					}
				}

				//проверка кораблей компьютера
				//и обрисовка убитых
				int test_y, test_x;
				for (int i = 0; i < 10; i++)
				{
					//если корабль убит,то его уже не проверяем
					if (pc_ship[i].life)
					{
						test_y = pc_ship[i].y;
						test_x = pc_ship[i].x;
						//проверяем цело ли начало корабля
						//если - нет, проверяем остальные 
						//части и,если они убиты, обводим корабль
						//и статус корабля- убит
						if (field_pc[test_y][test_x] == 5)
						{	//если однопалубный убит, сразу обводим 
							if (pc_ship[i].desk == 1 || testShip(pc_ship[i], field_pc))
							{
								//если все поля убиты, корабль мертв
								pc_ship[i].life = false;
								//отмечаем "*" поля вокруг корабля
								showDeadShip(pc_ship[i], field_pc);
							}
						}
					}
					
				}
				//проверяем наличие целых кораблей у компьютера
				if (isShipsIsset(field_pc))
				{
					cout << "\a\a\a\nВы потапили все вражеские корабли, Вы ПОБЕДИЛИ!!!\n";
				}

			} while (go_on);
		}//стрельба игрока
		//======================================================
		//===========СТРЕЛЬБА КОМПЬЮТЕРА========================
		//======================================================
		else
		{
			cout << "\nХОД КОМПЬЮТЕРА\n";

			//если есть попадания прошлых выстрелов
			//вызываем логику стрельбы на добивание
			if (target[0] != 10)
			{
				if(shootLogic(user_ship,field_hum, target, direct))
				{
					//если в логике добили корабль
					//то еще один рендомный ход компьютеру
					WHO = 1;
				}
				else
				{
					//если в логике промахнулись, ход-игроку
					WHO = 0;
				}
			}
			else//стреляем рендомно
			{
				do
				{
					x = rand() % 10;
					y = rand() % 10;

					//повторяем выстрел, если попадаем на прошлые
					//выстрелы или подбитый корабль
				} while (field_hum[y][x] == 5 || field_hum[y][x] == 6);

				//если попали в корабль
				//вызываем логику стрельбы на добивание
				if (field_hum[y][x] >= 1 && field_hum[y][x] < 5)
				{
					cout << "\a\nКомпьютер попал!!!\n";
					cout << getLetter(x) << " - " << y << endl;
					field_hum[y][x] = 5;
					//координаты попадания
					target[0] = y;
					target[1] = x;
					if (shootLogic(user_ship, field_hum, target, direct))
					{
						//если в логике добили корабль
						//то еще один рендомный ход компьютеру
						WHO = 1;
					}
					else
					{
						//если в логике промахнулись, ход-игроку
						WHO = 0;
					}
				}
				else if (field_hum[y][x] == 0)
				{
					//если попали в пустое поле,
					//в поле игрока - '*' и ход 
					//переходит игроку

					field_hum[y][x] = 6;
					cout << getLetter(x) << " - " << y << endl;
					WHO = 0;
				}

			}//else//стреляем рендомно

			//проверяем наличие целых кораблей у игрока
			if (isShipsIsset(field_hum))
			{
				cout << "\a\a\a\nУ Вас больше нет кораблей, Вы проиграли...\n";
			}

		}//стрельба компьютера


		/**
		-объявить победителя, вывести статистику,статистику в файл,
		-преложение сыграть еще или выход.
		*/


		cout << endl;
		cout << "Дальше?(да - 1; нет - 0)" << endl;
		cin >> contin;
		contin = (contin != 48)?1:0;

		//очищаем экран
		system("cls");
	} while (contin);

//*****************************************************************
//===============КОНЕЦ ИГРЫ=======================================*
//*****************************************************************

}//end MAIN

//======================================================
//==================ФУНКЦИИ=============================
//======================================================
//логика и стрельба компьютера
bool shootLogic(SHIP user_ship[], int field_hum[][10], int target[], bool direct[])
{
	/**
	*после выстрелов проверять не потоплен ли корабль
	*чтоб потом компьютер имел еще один рендомный выстрел
	*/

	//cout << "\nЗашли в логику стрельбы.\nИсходные данные:\n";
	//cout << "начальные координаты y = " << target[0] << "; x = " << target[1] << "\n";
	//cout << "направления:\n";
	//cout << "вправо = " << direct[0];
	//cout << "; влево = " << direct[1];
	//cout << "; вниз = " << direct[2];
	//cout << "; вверх = " << direct[3];

	//флаги изменения направления стрельбы 
	//при добивании корабля компьютером
	//0-x++; 1-x--; 2-y++; 3-y--;
	int Y, X;
	Y = target[0];
	X = target[1];
	bool go_on = true;
	//флаг пропуска хода при промахе
	//в одном из направлений
	bool flag;
	//переменные для проверки жизни корабля
	int test_y, test_x;

	flag = true;

	if (direct[0])
	{
		//стреляем в следующую клетку по горизонтали ВПРАВО
		//пока не промахнемся или не попадем на прошлые выстрелы
		//или не упремся в стенку
		int i = 0;
		do
		{
			i++;
			//проверяем есть ли дальше поле
			if (X + i <10)
			{
				//если попали, меняем поле и стреляем дальше
				if (field_hum[Y][X + i] >= 1 && field_hum[Y][X + i] < 5)
				{
					field_hum[Y][X + i] = 5;
					cout << "\a\nКомпьютер попал!!!\n";
					cout << getLetter(X + i) << " - " << Y << endl;
					//проверяем цел ли еще корабль.
					//если цел-продолжаем,
					//если убит-выходим из логики 
					//и компьютер стреляет еще раз рендомно

					//проверяем корабли игрока,
					//если он жив, но у него подбита первая палуба,
					//кидаем его на проверку остальных полей.
					//если окажется, что все подбиты, меняем 
					//его статус на - мертв и обводим его.
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//если однопалубный убит, сразу обводим 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//если все поля убиты, корабль мертв
									user_ship[i].life = false;
									//отмечаем "*" поля вокруг корабля
									showDeadShip(user_ship[i], field_hum);
									//обнуляем все для рендомной стрельбы
									cleanLogic(target, direct);
									//выходим из цикла,
									//а ход оставляем за компьютером
									go_on = true;
									break;
								}
							}
						}
					}
				}
				//если промахнулись, выходим
				//и ход переходит игроку
				//выходим и меняем направление стрельбы
				//в следующий ход компьютера
				//отмечаем промах
				//обнуляем это направление
				else if (field_hum[Y][X + i] == 0)
				{
					field_hum[Y][X + i] = 6;
					cout << "Компьютер промахнулся.\n";
					cout << getLetter(X + i) << " - " << Y << endl;
					direct[0] = false;
					direct[1] = true;
					go_on = false;
					flag = false;
				}
				//если попали на прошлый выстрел
				//выходим и меняем направление стрельбы
				else if (field_hum[Y][X + i] == 6)
				{
					//отключаем это направление 
					direct[0] = false;
					//и включаем следующее
					direct[1] = true;
					go_on = false;
				}
			}
			else//если уперлись в границу, а ход еще есть
			{
				cout << "\nуперся в правую границу\n";
				//обнуляем это направление
				direct[0] = false;
				//и включаем следующее
				direct[1] = true;
				//выходим из цикла,
				//а ход оставляем за компьютером
				go_on = false;
			}

		} while (go_on);
	}
//-------------ВЛЕВО-----------------------------------------------------------------
	if (direct[1] && flag)
	{
		//для срабатывания do-while пока попадаем по этому наравлению
		go_on = true;

		//стреляем в следующую клетку по горизонтали ВЛЕВО
		int i = 0;
		do
		{
			i++;
			//проверяем есть ли дальше поле
			if (X - i >= 0)
			{
				//если попали, меняем поле и стреляем дальше
				if (field_hum[Y][X - i] >= 1 && field_hum[Y][X - i] < 5)
				{
					field_hum[Y][X - i] = 5;
					cout << "\a\nКомпьютер попал!!!\n";
					cout << getLetter(X - i) << " - " << Y << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//если однопалубный убит, сразу обводим 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//если все поля убиты, корабль мертв
									user_ship[i].life = false;
									//отмечаем "*" поля вокруг корабля
									showDeadShip(user_ship[i], field_hum);
									//обнуляем все для рендомной стрельбы
									cleanLogic(target, direct);
									//выходим из цикла,
									//а ход оставляем за компьютером
									go_on = true;
									break;
								}
							}
						}
					}

				}
				else if (field_hum[Y][X - i] == 0)
				{
					//если промахнулись, выходим
					//и ход переходит игроку
					//выходим и меняем направление стрельбы
					//в следующий ход компьютера
					//отмечаем промах
					//обнуляем это направление
					field_hum[Y][X - i] = 6;
					cout << "Компьютер промахнулся.\n";
					cout << getLetter(X - i) << " - " << Y << endl;
					direct[1] = false;
					direct[2] = true;
					go_on = false;
					flag = false;
				}
				//если попали на прошлый выстрел
				//выходим и меняем направление стрельбы
				else if (field_hum[Y][X - i] == 6)
				{
					//отключаем это направление 
					direct[1] = false;
					//и включаем следующее
					direct[2] = true;
					go_on = false;
				}
			}
			else//если уперлись в границу, а ход еще есть
			{
				cout << "\nуперся в левую границу\n";
				//отключаем это направление 
				direct[1] = false;
				//и включаем следующее
				direct[2] = true;
				go_on = false;
			}

		} while (go_on);
	}
//---------------ВНИЗ----------------------------------------------------------------------------------
	if (direct[2] && flag)
	{
		//для срабатывания do-while пока попадаем по этому наравлению
		go_on = true;

		//стреляем в следующую клетку по вертикали ВНИЗ
		int i = 0;
		do
		{
			i++;
			//проверяем есть ли дальше поле
			if (Y + i <10)
			{
				//если попали, меняем поле и стреляем дальше
				if (field_hum[Y + i][X] >= 1 && field_hum[Y + i][X] < 5)
				{
					field_hum[Y + i][X] = 5;
					cout << "\a\nКомпьютер попал!!!\n";
					cout << getLetter(X) << " - " << Y + i << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//если однопалубный убит, сразу обводим 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//если все поля убиты, корабль мертв
									user_ship[i].life = false;
									//отмечаем "*" поля вокруг корабля
									showDeadShip(user_ship[i], field_hum);
									//обнуляем все для рендомной стрельбы
									cleanLogic(target, direct);
									//выходим из цикла,
									//а ход оставляем за компьютером
									go_on = true;
									break;
								}
							}
						}
					}

				}
				//если промахнулись, выходим
				//и ход переходит игроку
				//выходим и меняем направление стрельбы
				//в следующий ход компьютера
				//отмечаем промах
				//обнуляем это направление
				else if (field_hum[Y + i][X] == 0)
				{
					field_hum[Y + i][X] = 6;
					cout << "Компьютер промахнулся.\n";
					cout << getLetter(X) << " - " << Y + i << endl;
					direct[2] = false;
					direct[3] = true;
					go_on = false;
					flag = false;
				}
				//если попали на прошлый выстрел
				//выходим и меняем направление стрельбы
				else if (field_hum[Y + i][X] == 6)
				{
					//отключаем это направление 
					direct[2] = false;
					//и включаем следующее
					direct[3] = true;
					go_on = false;
				}
			}
			else//если уперлись в границу, а ход еще есть
			{
				cout << "\nуперся в нижнюю границу\n";
				//отключаем это направление 
				direct[2] = false;
				//и включаем следующее
				direct[3] = true;
				go_on = false;
			}

		} while (go_on);

	}
//----------------ВВЕРХ----------------------------------------------------------------------------
	if (direct[3] && flag)
	{
		//для срабатывания do-while пока попадаем по этому наравлению
		go_on = true;

		//стреляем в следующую клетку по вертикали ВВЕРХ
		//т.к. это последнее возможное направление
		//после всех возможных выстрелов(если не было промаха)
		//обнуляем все массивы для следующих выстрелов рендомно
		int i = 0;
		do
		{
			i++;
			//проверяем есть ли дальше поле
			if (Y - i >= 0)
			{
				//если попали, меняем поле и стреляем дальше
				if (field_hum[Y - i][X] >= 1 && field_hum[Y - i][X]  < 5)
				{
					field_hum[Y - i][X] = 5;
					cout << "\a\nКомпьютер попал!!!\n";
					cout << getLetter(X) << " - " << Y - i << endl;
					for (int i = 0; i < 10; i++)
					{
						if (user_ship[i].life)
						{
							test_y = user_ship[i].y;
							test_x = user_ship[i].x;
							if (field_hum[test_y][test_x] == 5)
							{	//если однопалубный убит, сразу обводим 
								if (user_ship[i].desk == 1 || testShip(user_ship[i], field_hum))
								{
									//если все поля убиты, корабль мертв
									user_ship[i].life = false;
									//отмечаем "*" поля вокруг корабля
									showDeadShip(user_ship[i], field_hum);
									//обнуляем все для рендомной стрельбы
									cleanLogic(target, direct);
									//выходим из цикла,
									//а ход оставляем за компьютером
									go_on = true;
									break;
								}
							}
						}
					}

				}
				else if (field_hum[Y - i][X] == 0)
				{
					//если промахнулись, выходим
					//и ход переходит игроку
					//т.к. это последнее направление
					//обнуляем все данные связанные
					//с логикой стрельбы
					field_hum[Y - i][X] = 6;
					cout << "Компьютер промахнулся.\n";
					cout << getLetter(X) << " - " << Y - i << endl;
					cleanLogic(target, direct);
					go_on = false;
				}
				else if (field_hum[Y - i][X] == 6)
				{
					//если попали на прошлый выстрел
					//выходим и тоже все чистим для 
					//следующей рендомной стрельбы

					cleanLogic(target, direct);
					go_on = true;
					break;
				}
			}
			else//если уперлись в границу, а ход еще есть
			{
				cout<<"\nуперся в верхнюю границу\n";
				//обнуляем все для рендомной стрельбы
				cleanLogic(target, direct);
				//выходим из цикла,
				//а ход оставляем за компьютером
				go_on = true;
				break;
			}

		} while (go_on);
	}

	//при true ход остается у компьютера
	//и происходит рендомная стрельба(реализовать)
	return go_on;
}
//*******************************************************

//заполнение массивов
void initArray(int arr[][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			arr[i][j] = 0;
}
//*********************************************************
//вывод массивов
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
//вывод игровых полей ИГРОКА
void printField(int arr[][10])
{
	//верхние буквы
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
//вывод игровых полей PC
void printPCField(int arr[][10])
{
	//Изначально поле выводится пустым.
	//Показываются только места выстрелов (6 - '*')
	//и подбитые палубы кораблей(5 - 'X').
	//верхние буквы
	cout << "\n   A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout.width(2);
			//если поле с подбитым кораблем
			if (arr[i][j] == 5) cout << "X";
			//если поле с выстрелом
			else if (arr[i][j] == 6) cout << "*";
			//если поле пустое
			//else cout << ".";
			//для тестов
			else if (arr[i][j] == 0)cout << ".";
			else cout << arr[i][j];
		}
		cout << endl;
	}
}

//*********************************************************
//автоматическая расстановка кораблей(вызов установщика для каждого корабля отдельно)
void autoSetShips(int field_hum[][10], int field_pc[][10], int height, int width, int ship_qty, int desk, SHIP user_ship[10], SHIP pc_ship[10])
{
	//массив для получения y,x,dist из установки кораблей
	int vector[3];
	
	int n = 0;
	//игрока
	for (int i = 4; i > 0; i--)
	{
		//кол-во палуб корабля
		desk = i;
		//кол-во кораблей размера desk
		for (int j = 0; j < 5 - desk; j++)
		{
			setShips(field_hum, height, width, desk, vector); 
			user_ship[n] = createShip(vector[0], vector[1], desk, vector[2]);
			n++;
		}
	}
	//компьютера
	n = 0;
	for (int i = 4; i > 0; i--)
	{
		//кол-во палуб корабля
		desk = i;
		//кол-во кораблей размера desk
		for (int j = 0; j < 5 - desk; j++)
		{
			setShips(field_pc, height, width, desk, vector);
			pc_ship[n] = createShip(vector[0], vector[1], desk, vector[2]);
			n++;
		}
	}
}
//*******************************************************

//расстановка кораблей
int* setShips(int field[][10], int height, int width, int desk, int vector[])
{


	//флаг для пустого поля
	bool empty;
	//начало корабля по x,y
	int y, x, direct;

	//повторяем цикл, пока не найдем 
	//подходящее место для корабля
	do
	{
		empty = true;
		x = rand() % 10;
		y = rand() % 10;
		//направление размещения корабля начиная с первой палубы
		//'0'- горизонтально, '1'- вертикально
		direct = rand() % 2;

		//если в начальном поле еще нет корабля
		if (field[y][x] == 0)
		{
			//проверяем достаточно ли места для корабля
			//согласно направлению расположения
			if (direct == 0)//если горизонтально
			{
				if (x + desk > 9)empty = true;
				else empty = false;
			}
			else if (direct == 1)//если вертикально
			{
				if (y + desk > 9)empty = true;
				else empty = false;
			}
		}

		if (!empty)
		{
			//если места хватает, проверяем окружение первого поля
			//(перед каждой проверкой проверяем существование нужного поля)
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
			//проверяем окружение остальных полей корабля
			empty = testAround(field, y, x, desk, direct);
		}
		//cout <<boolalpha<< empty<<endl;

	} while (empty);

	//после всех проверок устанавливаем корабль
	setOneShip(field, y, x, desk, direct);

	//данные для создания кораблей в структуре
	vector[0] = y;
	vector[1] = x;
	vector[2] = direct;
	return vector;
}
//*******************************************************
//проверка соседних полей
bool testAround(int field[][10], int y, int x, int desk, int direct)
{
	//если клетка пустая
	bool empty = false;
	//т.к. в первой клетке проверены поля,
	//в следующих полях корабля проверяем
	//только поля на шаг вперед и по диагонали, 
	//согласно направлению(со второго поля)
	if (direct == 0)//горизонтально
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
	else if (direct == 1)//вертикально
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
//установка одного корабля
void setOneShip(int field[][10], int y, int x, int desk, int direct)
{

	//после всех проверок устанавливаем корабль
	//из начальной точки+1, согласно направлению
	//(горизонтально или вертикально)
	if (direct == 0)//горизонтально
	{
		for (int i = 0; i < desk; i++)
		{
			field[y][x + i] = desk;
		}

	}
	else//вертикально
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
//получение координаты Х из буквы при выстреле
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
//очистка массивов для логической стрельбы компьютера
void cleanLogic(int target[], bool direct[])
{
	target[0] = 10;
	target[1] = 10;

	//чтоб изначально было открыто 
	//только одно направление стрельбы
	direct[0] = true;
	direct[1] = false;
	direct[2] = false;
	direct[3] = false;

	//все в true(старое)
	//for (int i = 0; i < 4; i++)
	//{
	//	direct[i] = true;
	//}
}
//*******************************************************
//получение буквы по координате
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
//проверка наличия живых кораблей
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
//вывод массива элементов структуры SHIP
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
//проверка состояния корабля(убит/не убит)
bool testShip(SHIP ship, int field[][10])
{
	//начинаем проверку со второй палубы
	//т.к. первую мы уже проверили
	bool flag = false;
	
	if (ship.dist == 0)//если горизонтальное расположение
	{
		for (int i = 1; i < ship.desk; i++)
		{
			(field[ship.y][ship.x + i] == 5) ? flag = true : flag = false;
		}
	}
	else//если вертикальное
	{
		for (int i = 1; i < ship.desk; i++)
		{
			(field[ship.y + i][ship.x] == 5) ? flag = true : flag = false;
		}
	}
	
	return flag;
}
//*******************************************************
//обозначение полей вокруг убитого корабля
void showDeadShip(SHIP ship, int field[][10])
{
	
	int y = ship.y;
	int x = ship.x;	
	
	if (ship.dist == 0)//если горизонтальное расположение
	{

		//проверяем первое поле(только вправо по х не ставим "*")
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

		//помечаем остальные поля
		for (int i = 1; i < ship.desk; i++)
		{
			//возвращаем значение поля как подбитого, 
			//которое переписало в 6 предыдущее поле
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
	else//если вертикальное расположение
	{

		//проверяем первое поле(по y вниз не ставим "*")
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

		//отмечаем остальные поля
		for (int i = 1; i < ship.desk; i++)
		{
			//возвращаем значение поля как подбитого, 
			//которое переписало в 6 предыдущее поле
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
	cout << "\a\a\a\nКорабль убит!!!\n";
}
