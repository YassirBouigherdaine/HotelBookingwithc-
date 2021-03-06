#include "ClassHotel.h"

time_t now = time(NULL);

tm lt = {};

char dt[26] = {};


Hotel::Hotel()
{
	roomNo = 0;

	Name = "Unkown";

	roomType = "Unkown";

	arrangement_type = "Unkown";

	day1 = 00, mon1 = 00, year1 = 00;

	day2 = 00, mon2 = 00, year2 = 00;

	is_present = "no";

	phoneNo = 00;

	creditCardNo = 00;
}


void Hotel::home_func()
{
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


		std::cout << "\n\n\t\t\t\t username: ";
		std::cin >> user_name;

		std::cout << "\t\t\t\t password: ";
		std::cin >> pass_word;

		if (user_name == "yassir" && pass_word == "0123")
		{
			system("cls");

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
			std::cout << "\n\n\t\t\t Press [Enter] to continue";
			std::cin.get();
		}

	} while (!access);

	system("cls");

	main_menu();

}

void Hotel::main_menu()
{
	int choice;

	do {
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**                                              **\n";
		std::cout << "\t\t*              Hotel booking service             *\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**                      Home                    **\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\n\n\t\t\t [1] Add new guest\n";
		std::cout << "\t\t\t [2] Display booked rooms\n";
		std::cout << "\t\t\t [3] Display guest record\n";
		std::cout << "\t\t\t [4] Display departures list\n";    
		std::cout << "\t\t\t [5] Display arrivals list\n";
		std::cout << "\t\t\t [6] Exit\n";

		std::cout << "\n\t\t\t Your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1: book_a_room();
			break;

		case 2: display_reserved_rooms();
			break;

		case 3: display_guest_record();
			break;

		case 4: display_departures_list();
			break;

		case 5: display_arrivals_list();
			break;

		case 6: exit(1);

		default: std::cout << "\n\t\t\t Invalid choice !!\n";
			std::cout << "\n\t\t\tPress [Enter] to try again\n";
			std::cin.get();
			break;
		}

		std::cin.get();
		system("cls");

	} while (true);
}


void Hotel::book_a_room()
{
	system("cls");

	int room_status, new_room_no;

	std::ifstream readFromFile;
	readFromFile.open("guestRecord.txt", std::ios::in | std::ios::binary);

	std::ofstream writeToFile;
	writeToFile.open("guestRecord.txt", std::ios::app | std::ios::binary);

	std::cout << "\n\t\t Enter room number to check availibalaty : ";
	std::cin >> new_room_no;

	//check if this room is vacant or not

	room_status = check_room_status(new_room_no);

	if (room_status)
	{
		std::cout << "\n\t\t Room is already booked\n";
	}

	else
	{
		system("cls");

		add_guest_record(new_room_no);
	}

	readFromFile.close();
	writeToFile.close();

	std::cout << "\n\n\t\t Press [ENTER] to continue";
	std::cin.get();
}

void Hotel::display_reserved_rooms()
{
	system("cls");
	std::ifstream readFromFile;

	readFromFile.open("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(Hotel));

	ctime_s(dt, 26, &now);

	localtime_s(&lt, &now);

	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;

	if (!readFromFile)
	{
		std::cout << "\n\t\t\t File not found\n";
	}

	else
	{
		std::cout << "\n----------------------------------LIST OF PRESENTS GUESTS------------------------------";
		std::cout << "\n---------------------------------------------------------------------------------------\n";

		while (!readFromFile.eof())
		{
			if (day2 > d && mon2 >= m && year2 >= y && is_present == "yes")
			{
				std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrangement_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\n";
				std::cout << "---------------------------------------------------------------------------------------";
			}
			
			readFromFile.read((char*)this, sizeof(Hotel));
		}

	}

	readFromFile.close();

	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


void Hotel::display_departures_list()
{
	system("cls");
	std::ifstream readFromFile;

	readFromFile.open("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(Hotel));

	ctime_s(dt, 26, &now);

	localtime_s(&lt, &now);

	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;

	if (!readFromFile)
	{
		std::cout << "\n\t\t\t File not found\n";
	}

	else
	{
		std::cout << "\n----------------------------------LIST OF DEPARTURES-------------------------------------";
		std::cout << "\n-----------------------------------------------------------------------------------------\n";
		while (!readFromFile.eof())
		{
			if (d == day2 && m == mon2 && y == year2)
			{
				std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrangement_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\n";
				std::cout << "---------------------------------------------------------------------------------------";
			}
			
			readFromFile.read((char*)this, sizeof(Hotel));
		}

	}

	readFromFile.close();

	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

void Hotel::display_arrivals_list()
{
	system("cls");
	std::ifstream readFromFile;

	readFromFile.open("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(Hotel));

	ctime_s(dt, 26, &now);

	localtime_s(&lt, &now);

	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;

	if (!readFromFile)
	{
		std::cout << "\n\t\t\t File not found\n";
	}

	else
	{
		std::cout << "\n----------------------------------LIST OF ARRIVALS-------------------------------------";
		std::cout << "\n---------------------------------------------------------------------------------------\n";

		while (!readFromFile.eof())
		{
			if (d == day1 && m == mon1 && y == year1 && is_present == "no")
			{
				std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrangement_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\n";
				std::cout << "---------------------------------------------------------------------------------------";
			}

			readFromFile.read((char*)this, sizeof(Hotel));
		}

	}

	readFromFile.close();

	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

void Hotel::display_guest_record()
{
	system("cls");

	int room_no, room_status;

	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(Hotel));

	if (!readFromFile)
	{
		std::cout << "\n\t\t File not found\n";
	}

	else
	{
		std::cout << "\n\t\t Please Enter the room number: ";
		std::cin >> room_no;

		system("cls");

		while (!readFromFile.eof())
		{
			readFromFile.read((char*)this, sizeof(Hotel));
			room_status = check_room_status(room_no);

			if (!room_status)
			{
				std::cout << "\n\t\t\t Room not found-\n";
				break;
			}

			else
			{
				std::cout << "--------------------------------Guest record---------------------------------";
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\n\t\t\t Room number: " << roomNo;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Room type: " << roomType;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Name: " << Name;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Arrangement type: " << arrangement_type;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Check-in: " << day1 << "/" << mon1 << "/" << year1;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Check-out: " << day2 << "/" << mon2 << "/" << year2;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Phone no: " << phoneNo;
				std::cout << "\n-----------------------------------------------------------------------------";
				std::cout << "\n\t\t\t Credit card no: " << creditCardNo;
				std::cout << "\n-----------------------------------------------------------------------------";

				readFromFile.read((char*)this, sizeof(Hotel));
				readFromFile.close();

				//editing the record
				std::cout << "\n\n\t [1] Add to presents \t [2] Modify the record \t [3] Delete \t [4] Bill \t [5] Exit: \n";

				int option;
				std::cout << "\n\t\t\t Your choice: ";
				std::cin >> option;

				switch (option)
				{

				case 1: add_to_presents(room_no);
					break;

				case 2: modify_guest_record(room_no);
					break;

				case 3: delete_record(room_no);
					std::cout << "\n\t\t\t Room was deleted\n";
					break;

				case 4: calculTheBill(room_no);
					break;

				case 5: break;
					break;

				default: std::cout << "\n\t\t\t Invalid choice !!\n";
					break;
				}

				break;
			}
		}
	}

	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}



int Hotel::check_room_status(int new_room_no)
{
	int room_status = 0;
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);

	while (!readFromFile.eof())
	{
		readFromFile.read((char*)this, sizeof(Hotel));

		if (new_room_no == roomNo)
		{
			//room is reserved
			room_status = 1;
			break;
		}
	}

	readFromFile.close();

	return room_status;
}

void Hotel::add_guest_record(int new_room_no)
{
	ctime_s(dt, 26, &now);

	localtime_s(&lt, &now);

	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;

	std::ofstream writeToFile;
	writeToFile.open("guestRecord.txt", std::ios::app | std::ios::binary);

	std::cout << "\n\t\tPlease enter guest details: \n";
	roomNo = new_room_no;
	std::cout << "\n\t\t Name: ";
	std::cin >> Name;
	std::cout << "\n\t\t Room type: ";
	std::cin >> roomType;
	std::cout << "\n\t\t Arrangement type: ";        // BB(bad&breakfast) or BO(bad only)
	std::cin >> arrangement_type;
	std::cout << "\n\t\t check-in: ";
	std::cin >> day1 >> mon1 >> year1;

	if (day1 < d || mon1 < m || year1 < y)
	{
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	std::cout << "\n\t\t check-out: ";
	std::cin >> day2 >> mon2 >> year2;

	if (year2 < y)
	{
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	is_present;

	std::cout << "\n\t\t Phone no: ";
	std::cin >> phoneNo;
	std::cout << "\n\t\t credit card no: ";
	std::cin >> creditCardNo;

	std::cout << "\n\t\t Room is booked successfuly\n";

	writeToFile.write((char*)this, sizeof(Hotel));
	writeToFile.close();
}

void Hotel::add_to_presents(int room_no)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	while (file.read((char*)this, sizeof(Hotel)))
	{
		if (roomNo == room_no)
		{
			is_present = "yes";

			unsigned __int64 pos = file.tellg();

			file.seekp(pos - sizeof(Hotel), std::ios::beg);
			file.write((char*)this, sizeof(Hotel));

			break;
		}
	}

}


void Hotel::modify_guest_record(int room_no)
{
	//deleting the old record
	delete_record(room_no);

	system("cls");

	//adding the the new record
	add_guest_record(room_no);
	std::cout << "\n\t\t\t Record was modified\n";
}


void Hotel::delete_record(int room_no)
{
	std::fstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	std::fstream newFile("tempFile.txt", std::ios::out | std::ios::binary);


	while (readFromFile.read((char*)this, sizeof(Hotel)))
	{
		if (room_no != roomNo)
		{
			newFile.write((char*)this, sizeof(Hotel));
		}
	}

	readFromFile.close();
	newFile.close();

	remove("guestRecord.txt");
	rename("tempFile.txt", "guestRecord.txt");
}


void Hotel::calculTheBill(int room_no)
{
	system("cls");

	int nights;

	// this function works for dates with same year

	struct std::tm a = { 0,0,0,day1,mon1,120 };            //check-in date
	struct std::tm b = { 0,0,0,day2,mon2,120 };            //check-out date

	std::time_t x = std::mktime(&a);
	std::time_t y = std::mktime(&b);

	nights = (std::difftime(y, x) / 86400);                //we have 86400s in a day (60*60*24)

	//months with 30 days
	if (mon1 == 4 && mon2 == 5 || mon1 == 6 && mon2 == 7 || mon1 == 9 && mon2 == 10 || mon1 == 11 && mon2 == 12)
	{
		nights -= 1;
	}

	//months with 31 days
	if (mon1 == 3 && mon2 == 4 || mon1 == 5 && mon2 == 6 || mon1 == 8 && mon2 == 9 || mon1 == 10 && mon2 == 11 || mon1 == 12 && mon2 == 1)
	{
		nights += 1;
	}

	else if (mon1 == 1 && mon2 == 2)
	{
		nights += 2;
	}

	// leap year
	if (mon1 == 2 && mon2 == 3)
	{
		if (year1 % 400 == 0 && year1 % 100 == 0 && year1 % 4 == 0)
		{
			//it's a leap year
			nights -= 1;
		}

		else
		{
			nights -= 2;
		}

	}

	int sum1 = 0, sum2 = 0, sum3 = 0;
	int room_charge = 0;


	if (roomType == "single")
	{
		room_charge = SINGLE_ROOM_PRICE;
		sum1 = nights * SINGLE_ROOM_PRICE;
		sum2 = TAXE * nights;
		sum3 = BREAKFAST_PRICE * nights;
	}

	if (roomType == "double")
	{
		room_charge = DOUBLE_ROOM_PRICE;
		sum1 = nights * DOUBLE_ROOM_PRICE;
		sum2 = TAXE * 2 * nights;
		sum3 = BREAKFAST_PRICE * 2 * nights;
	}

	if (roomType == "triple")
	{
		room_charge = TRIPLE_ROOM_PRICE;
		sum1 = nights * TRIPLE_ROOM_PRICE;
		sum2 = TAXE * 3 * nights;
		sum3 = BREAKFAST_PRICE * 3 * nights;
	}

	if (arrangement_type == "BO")
	{
		sum3 = 0;
	}

	int total = sum1 + sum2 + sum3;

	std::cout << "\n --------\n";
	std::cout << "| HOTELO |";
	std::cout << "\n --------\n";
	std::cout << "\n                                                   Date: " << day2 << "/" << mon2 << "/" << year2;
	std::cout << "\n                                                   Room number: " << roomNo;
	std::cout << "\n                                                   Room type: " << roomType;
	std::cout << "\n                                                   Name: " << Name;
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << "\n-----------------------------------Bill no: ------------------------------------\n";
	std::cout << " Service:    \t\tPrice: \t\t Amount: \t\tSum:          \n";
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << " Room charge:\t\t" << room_charge << " \t\t   " << nights << " \t\t        " << sum1 << "     \n\n";
	std::cout << " Taxes:      \t\t" << TAXE << "                                      " << sum2 << "    \n\n";   //pax is person 
	std::cout << " Breakfast:  \t\t" << BREAKFAST_PRICE << "                                      " << sum3 << "    \n\n";
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << "                                            Toltal:             " << total << "      \n\n";
	std::cout << "                                            TVA:10%             " << total * 0.1 << "\n\n";
	std::cout << "                                            NET:                " << total + (total * 0.1) << "  \n\n";


	std::cout << "\n\t\t\t Press [D] to delete the record\n";

	if (_kbhit())
	{
		char c = _getch();

		if (c == 'd')
		{
			delete_record(room_no);
		}
	}
	
}