﻿// StudyC++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

void foo() {
	static unsigned char  A;
	A = 255;
	do {
		A++;
	} while (A != 0);
}

void foo2() {
	static signed __int8 A;
	A = -127;
	while (A < 0)
	{
		A = A - 1;
	}
}
void foo3() {
	static float S;
	static unsigned char N = 11;
	std::cout << "N = " << (int)N << std::endl;
	S = 1. / N;
	while (S != 1)
	{
		std::cout << S << std::endl;
		S += 1. / N;
	}
	std::cout << S << std::endl;
};



//LAB2
//////////////////

int Inc(int x) {
	return x + 1;
}

int Z(int x) {
	return 0;
}

int L11(int x) {
	return x;
}

int iterAdd(int x, int y) {
	for (int i = 0; i < y; i++) {
		x = Inc(x);
	}
	return L11(x);
}

int recAdd(int x, int y) {
	if (y == 0) return L11(x);
	return Inc(recAdd(x,y-1));
}

int iterMulty(int x, int y) {
	int res = Z(x);
	for (int i = Z(x); i < y; i = Inc(i)) {
		res = iterAdd(res, x);
	}
	return L11(res);
}

int recMulty(int x, int y) {
	if (y == 0) return Z(x);
	return recAdd(x, recMulty(x, y - 1));
}

int iterPower(int x, int y) {
	int res = Inc(Z(x));
	for (int i = Z(x); i < y; i = Inc(i)) {
		res = iterMulty(res, x);
	}
	return L11(res);
}

int recPower(int x, int y) {
	if (y == 0) return Inc(Z(x));
	return recMulty(x, recPower(x, y - 1));
}

int foo4(int n) {
	if ((n == 1) || (n == 2)) return 1;
	return foo4(n - 2) + foo4(n - 1) ;
}

int foo5(int n) {
	int last = 0;
	int current = 1;
	for (int i = 0; i < n - 1; i++) {
		int buffer = current + last;
		last = current;
		current = buffer;
	}
	return current;
}




char picture[17][17] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', ' ', '@', '@', '@', ' ', '@', '@', '@', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', '@', ' ', ' ', '@', '@', '@', ' ', ' ', '@', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ', ' ',' '},
	{ ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@',' '},
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
};

char picture2[17][17] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', ' ', '@', '@', '@', ' ', '@', '@', '@', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', '@', ' ', ' ', '@', '@', '@', ' ', ' ', '@', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ', ' ',' '},
	{ ' ', ' ', '@', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', '@', ' ',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', '@', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', ' ', ' ', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@',' '},
	{ ' ', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@',' '},
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
};
int count = 0;
void FILL(int x, int y, char border, char filColor) {
	char c;	
	if (count >= 17) return;
	c = picture[y][x];
	count++;
	if (c != border and c != filColor) {
		picture[y][x] = filColor;		
		FILL(x - 1, y, border, filColor);
		FILL(x + 1, y, border, filColor);	
		FILL(x, y - 1, border, filColor);
		FILL(x, y + 1, border, filColor);
	}
}

int fooM(int n) {
	if (n > 100) return n - 10;
	return fooM(fooM(n + 11));
}



int fooA(int m, int n) {
	if (m == 0) return n + 1;
	else if (n == 0) return fooA(m - 1, 1);
	else return fooA(m - 1, fooA(m, n - 1));
}
int main()
{	


	std::cout << foo4(6) << "\n";
	std::cout << foo5(6) << "\n";


	int n, m;
	std::cin >> n;
	std::cin >> m;
	std::cout << fooA(m, n);
	

	std::cout << std::endl; std::cout << std::endl;


	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < 200; i++) {
		std::cout << "Для значения n = " << i << " Функция Маккарти = " << fooM(i) << "\t";
		if(i % 3 == 2)
			std::cout << std::endl;		
	}

	


	std::cout << std::endl;
	std::cout << recAdd(4, 2) << std::endl;
	std::cout << recMulty(4, 2) << std::endl;
	std::cout << recPower(4, 2) << std::endl;

	std::cout << std::endl;
	std::cout << iterAdd(4, 2) << std::endl;
	std::cout << iterMulty(4, 2) << std::endl;
	std::cout << iterPower(4, 2) << std::endl;
	std::cout << std::endl;

	return 0;

	for (int i = 0; i < 7; i++) {
		std::cout << '\n';
		std::cout << foo4(i) << std::endl;
		std::cout << foo5(i) << std::endl;
	}
	 n = 17;
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < n; ++j)
			std::cout << picture[i][j] << " ";
		std::cout << "\n";
	}
	// 10 3
	// 2 5
	FILL(10,3,'@','0');
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < n; ++j)
			std::cout << picture[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << count;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
