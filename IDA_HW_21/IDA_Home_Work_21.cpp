#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
//#include <array>

//----------- INTEGER Input filtrers -------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		
int Get_Int_PG();				// peek&get вариант проверки ввода INTEGER	
//----------- DOUBLE Input filtrers --------------------------------
double Get_Dbl_SA();		// String-analysis вариант фильтра DOUBLE.
double Get_Dbl_Positive();	// String-analysis вариант фильтра DOUBLE_POSITIVE
double Get_Dbl_PG();		// peek&get вариант проверки ввода DOUBLE	
//----------- Service functions ------------------------------------
int Get_Random(int Range_min, int Range_max);
double Get_Random(double Range_min, double Range_max);
template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max);
template <typename ANY> void Array_Console_Out(ANY arr[], int Size);

// Homework 21 -----------------------------------------------------

//Task 1
void Pointers_intro()
{
	double X, Y;
	std::cout << "\n" << "Enter value X -> ";
	*(&X) = Get_Dbl_SA();
	std::cout << "\n" << "Enter value Y -> ";
	*(&Y) = Get_Dbl_SA();

	double *_pointer_X = &X;
	double *_pointer_Y = &Y;

	std::cout << "\n" << "Average of X and Y, access to values through pointers: " << (*_pointer_X + *_pointer_Y)/2;
}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	setlocale(LC_CTYPE, "Russian");
	//system("mode con cols=110 lines=40"); // ??? текст основного меню не входит в окно консоли по умолчанию. При небольшом увеличении окна (lines < 85) пропадает полоса прокрутки, что не здорово. Как ee оставить и не делать (lines > 85)?
	std::string Name_of_Work = { "Home Work 21: Pointers. In the beginning..." };
	std::string Menu_Element_1 = { "Access to values through pointers" };
	//std::string Menu_Element_2 = { "mirror_number(num): Mirror a number " };
	//std::string Menu_Element_3 = { "Sort_Array_from_N(arr[], Size, N): Search first encaunter of N in array, then sort from this position" };
	//std::string Menu_Element_4 = { "Search_First_Ordinary_in_Array(arr[], Size): Returns first ordinary number in an array" };

	do {		
		system("cls");
		std::cout << "\n\t******\t" << Name_of_Work << "\t******\n\n\t\n\nChoose an opion: \n";
		std::cout << "\n 1. " << Menu_Element_1;
		//std::cout << "\n 2. " << Menu_Element_2;
		//std::cout << "\n 3. " << Menu_Element_3;
		//std::cout << "\n 4. " << Menu_Element_4;
		std::cout << "\n\n 0. Exit\n";
		int choice = 0;
		std::cout << "\nYour choice: ";
		choice = Get_Int_Positive();		
		std::cout << "\n";
		// Обработка выбора пользователя
		if (choice == 0) { std::cout << "\nGood By"; for (int j = 0; j < 50; j++) { Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0; }
		else if (choice == 1) Pointers_intro();
		//else if (choice == 2) mirror_number_demo();
		//else if (choice == 3) Sort_Array_from_N_demo();
		//else if (choice == 4) Search_First_Ordinary_in_Array_demo();
			
		else { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
		std::cout << "\n\n";
		system("pause");
		} while (true);
		
	//system("pause");
	return 0;
}

// Вспомагательные функции -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); // заклинание средней силы против неудачного чтения getline
	std::cin.clear(); // заклинание малой силы против неудачного чтения getline
	getline(std::cin, a);
	//std::cout << "\nFunction: working with " << a << "\n"; для отладки
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	//std::cin.ignore(1024, '\n');
	getline(std::cin, a);
	if (a != "") // оказывается getline считывает пустую строку которую stoi уже не берет
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Incorrect input: INTEGER overflow. Decrease input\n";
			}
		}
		else
		{
			std::cout << "Incorrect symbols: positive INTEGER expected. Try again...\n";
			return Get_Int_Positive();
		}
		//return Get_Int_Positive();
	}
	else
		std::cout << "Input Error: NULL input\n";
	return Get_Int_Positive();
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA(){
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}		 	
				try{
					return stod(a);
				}
				catch (std::out_of_range) {
					std::cout << "Data type overflow\n";
					return Get_Dbl_SA();					
				}						
	}
	else {		
		std::cout << "Incorrect symbols: REAL expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}

