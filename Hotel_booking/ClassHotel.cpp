#include "ClassHotel.h"



time_t now = time(NULL);

tm lt = {};

char dt[26] = {};

void bill_report();



Hotel::Hotel()
{
	roomNo = 0;

	Name = "Unkown";

	roomType = "Unkown";

	arrang_type = "Unkown";

	day1 = 00, mon1 = 00, year1 = 00;

	day2 = 00, mon2 = 00, year2 = 00;

	phoneNo = "Unkown";

	creditCardNo = "Unkown";

	paid = "NO";
}

bool checklogin(std::string userName, std::string passWord)
{
	int access = 0;
	std::string user_name;
	std::string pass_word;

	std::ifstream fin;
	fin.open("login.txt", std::ios::in | std::ios::binary);

	fin >> user_name >> pass_word;

	if (userName == user_name && passWord == pass_word)
	{
		access = 1;
	}
	
	fin.close();
	return access;
}


void Hotel::home_func()
{
	std::string user_name, pass_word;          
	bool access = false;

	do
	{
		system("cls");
		std::cout << "\n\t\t***************************************************\n";
		std::cout << "\t\t***************************************************\n";
		std::cout << "\t\t**                                               **\n";
		std::cout << "\t\t*                      HOTELO                     *\n";
		std::cout << "\t\t*                                                 *\n";
		std::cout << "\t\t*             HOTEL MANAGEMENT SYSTEM             *\n";
		std::cout << "\t\t**                                               **\n";
		std::cout << "\t\t***************************************************\n";
		std::cout << "\t\t***************************************************\n";
		std::cout << "\n\n\t\t\t\t username: ";
		std::cin >> user_name;

		std::cout << "\t\t\t\t password: ";
		std::cin >> pass_word;

		if (checklogin(user_name, pass_word))
		{
			system("cls");

			user_name[0] = toupper(user_name[0]);
			std::cout << "\n\n\t\t\t\t*                    *";
			std::cout << "\n\t\t\t\t**  Welcome, "<<user_name<<"  **";
			std::cout << "\n\t\t\t\t*                    *";

			std::cin.get();
			access = true;
			std::cin.get();
		}
		else
		{
			system("cls");
			std::cout << "\n\n\t\t\t Invalid username or password !!\n";
			std::cout << "\n\n\t\t\t Press [Enter] to continue";
			_getch();
		}

	} while (!access);

	system("cls");
	main_menu();
}


void Hotel::main_menu()
{
	int op;

	do {
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t*                                                *\n";
		std::cout << "\t\t*                    HOTELEO                     *\n";
		std::cout << "\t\t*              HOTEL MANAGEMENT SYSTEM           *\n";
		std::cout << "\t\t*                                                *\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t*                       HOME                     *\n";
		std::cout << "\t\t**                                              **\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\n\t\t* \t [1] Add new guest                       *\n";
		std::cout << "\t\t* \t [2] Display booked rooms                *\n";
		std::cout << "\t\t* \t [3] Display guest record                *\n";
		std::cout << "\t\t* \t [4] Display departures list             *\n";
		std::cout << "\t\t* \t [5] Display arrivals list               *\n";
		std::cout << "\t\t* \t [6] Billing report                      *\n";
		std::cout << "\t\t* \t [7] Exit                                *\n";
		std::cout << "\n\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";

		std::cout << "\n\t\t\t Your choice: ";
		std::cin >> op;

		switch (op)
		{
		case 1: add_guest_record();
			break;

		case 2: display_reserved_rooms();
			break;

		case 3: display_guest_record();
			break;

		case 4: display_departures_list();
			break;

		case 5: display_arrivals_list();
			break;

		case 6: bill_report();
			break;

		case 7: exit(1);

		default: std::cout << "\n\t\t\t Invalid choice\n";
			std::cout << "\n\t\t\tPress [Enter] to try again\n";
			std::cin.get();
			break;
		}

		std::cin.get();
		system("cls");

	} while (true);
}


int Hotel::check_room_status(int new_room_no)
{
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	int room_status = 0;

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


void Hotel::add_guest_record()
{
	ctime_s(dt, 26, &now);

	localtime_s(&lt, &now);

	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;

	std::ofstream writeToFile;
	writeToFile.open("guestRecord.txt", std::ios::app | std::ios::binary);

	system("cls");

	std::string tmpName;

	std::cout << "\n\t\t\t\t Name: ";
	std::cin >> tmpName;

	if (is_exist(tmpName))
	{
		system("cls");
		std::cout << "\n\t\t\t Name is already exist\n";
		_getch();
		return;
	}

	Name = tmpName;

	std::cout << "\n\t\t\t\t Room type: ";
	std::cin >> roomType;
	std::cout << "\n\t\t\t\t Arrangement type (BB/BO): ";        // bad&breakfast or bad only
	std::cin >> arrang_type;
	std::cout << "\n\t\t\t\t check-in: ";
	std::cin >> day1 >> mon1 >> year1;

	if ((day1 < d && mon1 == m) || (day1 >= d && mon1 < m) || (year1 < y))
	{
		system("cls");
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	std::cout << "\n\t\t\t\t check-out: ";
	std::cin >> day2 >> mon2 >> year2;

	if ((day2 <= d && mon2 == m && year2 == y) || (mon2 < m) || (year2 < y))
	{
		system("cls");
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	std::cout << "\n\t\t\t\t Phone no: ";
	std::cin >> phoneNo;
	std::cout << "\n\t\t\t\t credit card no: ";
	std::cin >> creditCardNo;

	paid;
	roomNo = 0;

	writeToFile.write((char*)this, sizeof(Hotel));
	writeToFile.close();
	system("cls");
	std::cout << "\n\n\t\t Room is booked successfuly\n";
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
		std::cout << "\n----------------------------------LIST OF GUESTS PRESENT------------------------------";
		std::cout << "\n---------------------------------------------------------------------------------------\n";

		while (!readFromFile.eof())
		{
			if ((roomNo != 0 && day2 > d && mon2 == m && year2 == y) || (roomNo != 0 && mon2 > m || year2 > y))			
			{
				Name[0] = toupper(Name[0]);
				std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrang_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\tPayment: "<< paid <<"\n";
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
				Name[0] = toupper(Name[0]);
				std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrang_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\tPayment: " << paid << "\n";
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
			if (d == day1 && m == mon1 && y == year1 && roomNo == 0)
			{
				Name[0] = toupper(Name[0]);
				std::cout << "\n Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" << " Arrangement_type:" << arrang_type << "\t\t"
					"Check-in: " << day1 << "/" << mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
					"Credit card no: " << creditCardNo << "\tPayment: " << paid << "\n";
				std::cout << "---------------------------------------------------------------------------------------";
			}

			readFromFile.read((char*)this, sizeof(Hotel));
		}
	}

	readFromFile.close();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


void bill_report()
{
	std::ifstream fin("bills.txt", std::ios::in | std::ios::binary);
	if (fin.is_open())
	{
		system("cls");
		int d, m, y, h, min, room_n;
		std::string room_t, name, payMode;
		// Fout << day2 << "\t" << mon2 << year2 << h << m << roomNo << roomType << Name << pay_mode 
		std::cout << "\n----------------------------------BILLING REPORT--------------------------------------------\n";
		std::cout << "-------------------------------------------------------------------------------------------\n";
		std::cout << "\tDATE \t\tTIME \t ROOM NO \tROOM TYPE \t NAME \t PAYMENT MODE \n";
		std::cout << "-------------------------------------------------------------------------------------------\n";

		fin >> d >> m >> y >> h >> min >> room_n >> room_t >> name >> payMode;

		while (!fin.eof())
		{
			std::cout << "\t" << d << "-" << m << "-" << y << "\t" << h << ":" << min << "\t  " << room_n << "  \t     " << room_t <<"   \t  "<< name <<"\t  "<< payMode << std::endl;
			std::cout << "-------------------------------------------------------------------------------------------\n";
			fin >> d >> m >> y >> h >> min >> room_n >> room_t >> name >> payMode;
		}
	}
	else
	{
		system("cls");
		std::cout << "\n\t\tError occurred in opening the file\n";
	}

	_getch();
	fin.close();
}


int Hotel::is_exist(std::string tmpName)
{
	int exist = 0;

	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);

	while (!readFromFile.eof())
	{
		readFromFile.read((char*)this, sizeof(Hotel));

		if (tmpName == Name)
		{
			exist = 1;
			break;
		}
	}

	readFromFile.close();
	return exist;
}


void Hotel::display_guest_record()
{
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);

	if (readFromFile.good())
	{
		std::string tmpName;

		system("cls");
		std::cout << "\n\t\t Name of the guest: ";
		std::cin >> tmpName;
	
		if (is_exist(tmpName))
		{
			while (readFromFile.read((char*)this, sizeof(Hotel)))
			{
				if (Name == tmpName)
				{
					system("cls");
					std::cout << "\n\n\t--------------------------------GUEST RECORD---------------------------------";
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Room number: " << roomNo;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Room type: " << roomType;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					Name[0] = toupper(Name[0]);
					std::cout << "\n\t\t\t\t Name: " << Name;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Arrangement type: " << arrang_type;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Check-in: " << day1 << "/" << mon1 << "/" << year1;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Check-out: " << day2 << "/" << mon2 << "/" << year2;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Phone no: " << phoneNo;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Credit card no: " << creditCardNo;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					std::cout << "\n\t\t\t\t Payment: " << paid;
					std::cout << "\n\t-----------------------------------------------------------------------------";
					readFromFile.close();

					//editing the record
					std::cout << "\n\n\t[1] Add to presents\t[2] Modify\t[3] Delete\t[4] Bill\t[5] Exit: \n";

					int option;
					std::cout << "\n\t\t\t Your choice: ";
					std::cin >> option;

					switch (option)
					{
					case 1: add_to_presents(tmpName);
						break;

					case 2: modify_guest_record(tmpName);
						break;

					case 3: delete_record(tmpName);
						break;

					case 4: calculTheBill(tmpName);
						break;

					case 5: break;

					default: std::cout << "\n\t\t\t Invalid choice\n";
						break;
					}
				}
			}
			
		}
		else
		{
			std::cout << "\n\t\t\t Record not found\n";
			_getch();
		}
	}
	else
	{
		std::cout << "\n\t\t File not found\n";
	}
}


void Hotel::add_to_presents(std::string tmpName)
{
	int room_no;
	system("cls");
	std::cout << "\n\n\t\t\t\t Room number: ";
	std::cin >> room_no;

	if (check_room_status(room_no))
	{
		system("cls");
		std::cout << "\n\n\t\t\t Operation can't be completed\n";
		_getch();
	}
	else
	{
		std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

		ctime_s(dt, 26, &now);
		localtime_s(&lt, &now);
		asctime_s(dt, 26, &lt);

		int d = lt.tm_mday;
		int m = lt.tm_mon + 1;
		int y = 1900 + lt.tm_year;

		system("cls");
		while (!file.eof())
		{
			file.read((char*)this, sizeof(Hotel));

			if (Name == tmpName)
			{
				if (day1 != d && mon1 == m && year1 == y || roomNo != 0)
				{
					system("cls");
					std::cout << "\n\n\t\t\t Operation can't be completed\n";
					_getch();
					break;
				}
				else
				{
					roomNo = room_no;

					unsigned __int64 pos = file.tellg();
					file.seekp(pos - sizeof(Hotel), std::ios::beg);
					file.write((char*)this, sizeof(Hotel));

					std::cout << "\n\n\t\t\t Record was added to guests present\n";
					_getch();
					break;
				}
			}
		}

		file.close();
	}	
}

void Hotel::edit_roomNo(std::string tmpName)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	int room_no;
	system("cls");
	std::cout << "\n\n\t\t\t\t Room number: ";
	std::cin >> room_no;

	if (check_room_status(room_no))
	{
		system("cls");
		std::cout << "\n\n\t\t\t Room is not vacant\n";
	}
	else
	{
		while (file.read((char*)this, sizeof(Hotel)))
		{
			if (Name == tmpName)
			{
				roomNo = room_no;

				unsigned __int64 pos = file.tellg();
				file.seekp(pos - sizeof(Hotel), std::ios::beg);
				file.write((char*)this, sizeof(Hotel));

				break;
			}
		}

		file.close();
		system("cls");
		std::cout << "\n\n\t\t\t Record was modified successfuly\n";
		_getch();
	}
}

void Hotel::edit_guest_name(std::string tmpName)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	int exist;
	std::string newName;
	system("cls");
	std::cout << "\n\n\t\t\t\t Name: ";
	std::cin >> newName;

	exist = is_exist(newName);

	if (exist)
	{
		system("cls");
		std::cout << "\n\n\t\t Name is already exist\n";
	}
	else
	{
		while (file.read((char*)this, sizeof(Hotel)))
		{
			if (Name == tmpName)
			{
				Name = newName;

				unsigned __int64 pos = file.tellg();
				file.seekp(pos - sizeof(Hotel), std::ios::beg);
				file.write((char*)this, sizeof(Hotel));

				break;
			}
		}
	}

	file.close();
	system("cls");
	std::cout << "\n\n\t\t\t Record was modified successfuly\n";
	_getch();
}

void Hotel::edit_date(std::string tmpName)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	ctime_s(dt, 26, &now);
	localtime_s(&lt, &now);
	asctime_s(dt, 26, &lt);

	int d = lt.tm_mday;
	int m = lt.tm_mon + 1;
	int y = 1900 + lt.tm_year;
	int D1, M1, Y1, D2, M2, Y2;

	system("cls");
	std::cout << "\n\t\t\t\t check-in: ";
	std::cin >> D1 >> M1 >> Y1;

	if ((D1 < d && M1 == m) || (D1 <= d && M1 < m) || (Y1 < y))       
	{
		system("cls");
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	std::cout << "\n\t\t\t\t check-out: ";           
	std::cin >> D2 >> M2 >> Y2;

	if ((D2 < d && M2 == m && Y2 == y) || (M2 < m) || (Y2 < y))
	{
		system("cls");
		std::cout << "\n\t\t\t Invalid input\n";
		_getch();
		return;
	}

	while (file.read((char*)this, sizeof(Hotel)))
	{
		if (Name == tmpName)
		{
			day1 = D1; mon1 = M1; year1 = Y1;
			day2 = D2; mon2 = M2; year2 = Y2;

			unsigned __int64 pos = file.tellg();
			file.seekp(pos - sizeof(Hotel), std::ios::beg);
			file.write((char*)this, sizeof(Hotel));

			break;
		}
	}

	file.close();
	system("cls");
	std::cout << "\n\n\t\t\t Record was modified successfuly\n";
	_getch();
}

void Hotel::edit_phone_n(std::string tmpName)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	std::string newPhoneN;
	system("cls");
	std::cout << "\n\n\t\t\t\t Phone number: ";
	std::cin >> newPhoneN;

	while (file.read((char*)this, sizeof(Hotel)))
	{
		if (Name == tmpName)
		{
			phoneNo = newPhoneN;

			unsigned __int64 pos = file.tellg();
			file.seekp(pos - sizeof(Hotel), std::ios::beg);
			file.write((char*)this, sizeof(Hotel));
			break;
		}
	}

	file.close();
	system("cls");
	std::cout << "\n\n\t\t\t Record was modified successfuly\n";
	_getch();
}


void Hotel::edit_creditCardNo(std::string tmpName)
{
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	std::string newCreditCardN;
	system("cls");
	std::cout << "\n\n\t\t\t\t Credit card number: ";
	std::cin >> newCreditCardN;

	while (file.read((char*)this, sizeof(Hotel)))
	{
		if (Name == tmpName)
		{
			creditCardNo = newCreditCardN;

			unsigned __int64 pos = file.tellg();
			file.seekp(pos - sizeof(Hotel), std::ios::beg);
			file.write((char*)this, sizeof(Hotel));
			break;
		}
	}

	file.close();
	system("cls");
	std::cout << "\n\n\t\t\t Record was modified successfuly\n";
	_getch();
}

void Hotel::modify_guest_record(std::string tmpName)
{
	int op;

	system("cls");
	std::cout << "\n\n\t\t\t Press [1] to edit room number";
	std::cout << "\n\n\t\t\t Press [2] to edit guest name";
	std::cout << "\n\n\t\t\t Press [3] to edit date";
	std::cout << "\n\n\t\t\t Press [4] to edit phone number";
	std::cout << "\n\n\t\t\t Press [5] to edit credit card number";
	std::cout << "\n\n\t\t\t Press [6] to exit";
	std::cout << "\n\n\t\t\t Your choice: ";
	std::cin >> op;

	switch (op)
	{
	case 1: edit_roomNo(tmpName);
		break;

	case 2: edit_guest_name(tmpName);
		break;

	case 3:edit_date(tmpName);
		break;

	case 4:edit_phone_n(tmpName);
		break;

	case 5:edit_creditCardNo(tmpName);
		break;

	case 6: break;

	default:std::cout << "\n\t\t\t Invalid choice\n";
		break;
	}
}


void Hotel::delete_record(std::string tmpName)
{
	std::fstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	std::fstream newFile("tempFile.txt", std::ios::out | std::ios::binary);

	while (readFromFile.read((char*)this, sizeof(Hotel)))
	{
		if (Name != tmpName)
		{
			newFile.write((char*)this, sizeof(Hotel));
		}
	}

	readFromFile.close();
	newFile.close();
	remove("guestRecord.txt");
	rename("tempFile.txt", "guestRecord.txt");

	system("cls");
	std::cout << "\n\n\t\t\t Record was deleted\n";
	_getch();
}


void Hotel::calculTheBill(std::string tmpName)
{
	system("cls");
	std::fstream file("guestRecord.txt", std::ios::out | std::ios::in | std::ios::binary);

	while (file.read((char*)this, sizeof(Hotel)))
	{
		if (Name == tmpName)
		{
			int nights;

			struct std::tm a = { 0,0,0,day1,mon1,120 };            //check-in date
			struct std::tm b = { 0,0,0,day2,mon2,120 };            //check-out date

			std::time_t x = std::mktime(&a);
			std::time_t y = std::mktime(&b);

			nights = (std::difftime(y, x) / 86400);                //we have 86400s in a day (60*60*24)

			if (mon1 == 1 && mon2 == 2)
			{
				nights += 2;
			}

			// leap year

			else if (mon1 == 2 && mon2 == 3)
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

			//months with 30 days

			else if (mon1 == 4 && mon2 == 5 || mon1 == 6 && mon2 == 7 || mon1 == 9 && mon2 == 10 || mon1 == 11 && mon2 == 12)
			{
				nights -= 1;
			}

			//months with 31 days

			else if (mon1 == 3 && mon2 == 4 || mon1 == 5 && mon2 == 6 || mon1 == 8 && mon2 == 9 || mon1 == 10 && mon2 == 11 || mon1 == 12 && mon2 == 1)
			{
				nights += 1;
			}

			// the bill
			
			int sum1 = 0, sum2 = 0, sum3 = 0;
			int room_charge = 0;

			if (roomType == "single")
			{
				room_charge = SINGLE_ROOM_PRICE;
				sum1 = nights * SINGLE_ROOM_PRICE;
				sum2 = TAXE * nights;
				sum3 = BREAKFAST_PRICE * nights;
			}

			else if (roomType == "double")
			{
				room_charge = DOUBLE_ROOM_PRICE;
				sum1 = nights * DOUBLE_ROOM_PRICE;
				sum2 = TAXE * 2 * nights;
				sum3 = BREAKFAST_PRICE * 2 * nights;
			}

			else if (roomType == "triple")
			{
				room_charge = TRIPLE_ROOM_PRICE;
				sum1 = nights * TRIPLE_ROOM_PRICE;
				sum2 = TAXE * 3 * nights;
				sum3 = BREAKFAST_PRICE * 3 * nights;
			}

			if (arrang_type == "BO")
			{
				sum3 = 0;
			}

			int total = sum1 + sum2 + sum3;

			std::cout << "\n --------\n";
			std::cout << " --------\n";
			std::cout << "  HOTELO ";
			std::cout << "\n --------";
			std::cout << "\n --------\n";
			std::cout << "\n                                                   Date: " << day2 << "/" << mon2 << "/" << year2;
			std::cout << "\n                                                   Room number: " << roomNo;
			std::cout << "\n                                                   Room type: " << roomType;
			std::cout << "\n                                                   Name: " << Name;
			std::cout << "\n\n--------------------------------------------------------------------------------\n";
			std::cout << "\n-----------------------------------Bill no: ------------------------------------\n";
			std::cout << "\n Service:    \t\tPrice: \t\t Amount: \t\tSum:          \n";
			std::cout << "\n--------------------------------------------------------------------------------\n";
			std::cout << " Room charge:\t\t" << room_charge << " \t\t   " << nights << " \t\t        " << sum1 << "     \n\n";
			std::cout << " Taxes:      \t\t" << TAXE << "                                      " << sum2 << "    \n\n";
			std::cout << " Breakfast:  \t\t" << BREAKFAST_PRICE << "                                      " << sum3 << "    \n\n";
			std::cout << "\n--------------------------------------------------------------------------------\n";
			std::cout << "                                            Toltal:             " << total << "      \n\n";
			std::cout << "                                            TVA:10%             " << total * 0.1 << "\n\n";
			std::cout << "                                            NET:                " << total + (total * 0.1) << "  \n\n";

			// payment

			char ch;
			std::string pay_mode = "";

			std::cout << "\n\n\t\t [P] Payment \t\t [E] Exit\n";
			std::cout << "\n\t\t >choice: ";
			std::cin >> ch;

			if (ch == 'p' || ch == 'P')
			{
				ctime_s(dt, 26, &now);
				localtime_s(&lt, &now);
				asctime_s(dt, 26, &lt);

				int h = lt.tm_hour;
				int m = lt.tm_min;

				int p;

				do
				{
					system("cls");
					std::cout << "\n\n\t\t Payment mode:    [1] Cash \t [2] Credit card \t [3] Check";
					std::cout << "\n\n\t\t\t >choice :";
					std::cin >> p;

					switch (p)
					{
					case 1: pay_mode = "Cash";
						break;
					case 2: pay_mode = "C.C";
						break;
					case 3: pay_mode = "Check";
						break;
					default:std::cout << "\n\t\t\t Invalid choice\n";
						std::cin.get();
						break;
					}

				} while (p < 1 && p > 3);

				std::ofstream Fout("bills.txt", std::ios::app | std::ios::binary);
				Fout << day2 << "\t" << mon2 << "\t" << year2 << "\t" << h << "\t" << m << "\t" << roomNo << "\t" << roomType << "\t" << Name << "\t" << pay_mode << std::endl;
				Fout.close();

				paid = pay_mode;

				unsigned __int64 pos = file.tellg();
				file.seekp(pos - sizeof(Hotel), std::ios::beg);
				file.write((char*)this, sizeof(Hotel));
				break;
			}
		}
	}

	file.close();
}
