//c++ Hotel booking project

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<dos.h>
#include<conio.h>
#include<ctime>
#include"ClassHotel.h"
#include"Func.h"

//main function
int main()
{   
	hotel R;
	std::string user_name;            //username = yassir
	std::string pass_word;            //password = 0123
	bool access = false;
	
	do
	{
		system("cls");
	std::cout << "\t\t***************************************************\n";
	std::cout << "\t\t**                                               **\n";
	std::cout << "\t\t*                     WELCOME                     *\n";
	std::cout << "\t\t*                        TO                       *\n";
	std::cout << "\t\t*                      HOTELO                     *\n";
	std::cout << "\t\t**                                               **\n";
	std::cout << "\t\t***************************************************\n";
	
	
		std::cout << "\n\n\t\t\t\t-Username: ";
		std::cin >> user_name;
		std::cout << "\t\t\t\t-Password: ";
		std::cin >> pass_word;
		
		if (user_name == "yassir" && pass_word == "0123")
		{
			std::cout << "\n\n\t\t\t\t*                  *";
			std::cout << "\n\t\t\t\t** Welcome Yassir **";
			std::cout << "\n\t\t\t\t*                  *";
			std::cin.get();
			access = true;       
			std::cin.get();
			
		}
		else
		{
			std::cout << "\n\t\t\t Invalid username or password !!\n";
			std::cin.get();
			std::cout << "\n\t\t\t Press [Enter] to continue";
			std::cin.get();
		}
	} while (!access);
	system("cls");
	R.main_menu();
	return 0;
}
