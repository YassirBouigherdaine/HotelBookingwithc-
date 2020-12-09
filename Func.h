#pragma once

#include"ClassHotel.h"

constexpr auto SINGLE_ROOM_PRICE = 500;
constexpr auto DOUBLE_ROOM_PRICE = 600;
constexpr auto TRIPLE_ROOM_PRICE = 800;
constexpr auto BREAKFAST_PRICE = 60;
constexpr auto TAXE = 10;


//main menu function
void hotel::main_menu()
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
		std::cout << "\n\n\t\t\t -Press [1] to display booked rooms\n";
		std::cout << "\t\t\t -Press [2] to add new guest\n";
		std::cout << "\t\t\t -Press [3] to display guest record\n";
		std::cout << "\t\t\t -Press [4] to check bill\n";
	
		std::cout << "\n\t\t\t *Please enter your choice: ";

		std::cin >> choice;
		switch (choice)
		{
		case 1: display_reserved_rooms();
			break;
		case 2: book_a_room();
			break;
		case 3: display_guest_record();
			break;
		case 4: view_bill();
			break;
	
		default: std::cout << "\n\t\t\t Invalid choice !!\n";
			std::cout << "\n\t\t\tPress [Enter] to try again\n";
			std::cin.get();
			break;
		}
		std::cin.get();
		system("cls");
	} while (true);
}

// display list of reserved room
void hotel::display_reserved_rooms()
{
	system("cls");
	std::ifstream readFromFile;
	readFromFile.open("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(hotel));
	if (!readFromFile)
	{
		std::cout << "\n\t\t\t File not found\n";
	}
	else
	{
		std::cout << "\n----------------------------------List of rooms-------------------------------------";
		while (!readFromFile.eof())
		{
			std::cout << "\n Room number: " << roomNo << "\t\t" << "Room type: " << roomType << "\t\t" << "Name: " << Name << "\n" <<" Arrangement_type:"<<arrangement_type<< "\t\t"
				"Check-in: " << day1<<"/"<<mon1 << "/" << year1 << "\t\t" << "Check-out: " << day2 << "/" << mon2 << "/" << year2 << "\n" << " Phone no: " << phoneNo << "\t\t" <<
				"Credit card no: " << creditCardNo << "\n";
			std::cout << "------------------------------------------------------------------------------------";
			readFromFile.read((char*)this, sizeof(hotel));
		}
		
	}
	readFromFile.close();
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

//to book a rooom
void hotel::book_a_room()
{
	system("cls");
	int room_status;
	int new_room_no;
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
		std::cout << "\n\t\t-Room is already booked-\n";
	}
	else
	{
		std::cout << "\n\t\t\t -Room is vacant- \n";
		add_guest_record(new_room_no);
		std::cout << "\n\t\t Room is booked successfuly\n";
	}
	readFromFile.close();
	writeToFile.close();
	std::cout << "\n\t\t Press [ENTER] to continue";
	std::cin.get();
}

//view specific guest record
void hotel::display_guest_record()
{
	system("cls");
	int room_no;
	int room_status;
	
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	readFromFile.read((char*)this, sizeof(hotel));
	if (!readFromFile)
	{
		std::cout << "\n\t\t File not found\n";
	}
	else
	{
		std::cout << "\n\t\tPlease Enter the room number: ";
		std::cin >> room_no;
		system("cls");
	  while (!readFromFile.eof())
	  {
		  readFromFile.read((char*)this, sizeof(hotel));
		  room_status=check_room_status(room_no);
	      if (!room_status)
	      {
			  std::cout << "\n\t\t\t -Room not found-\n";
			  break;
	      }
		  else
		  {
			  std::cout << "--------------------------------Guest record---------------------------------";
			  std::cout << "\n\n\t\t\t-Room number: " << roomNo;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Room type: " << roomType;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Name: " << Name;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Arrangement type: " << arrangement_type;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Check-in: " << day1 << "/" << mon1 << "/" << year1;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Check-out: " << day2 << "/" << mon2 << "/" << year2;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Phone no: " << phoneNo;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  std::cout << "\n\t\t\t-Credit card no: " << creditCardNo;
			  std::cout << "\n-----------------------------------------------------------------------------";
			  readFromFile.read((char*)this, sizeof(hotel));
			  readFromFile.close();
			  //editing the record
			  std::cout << "\n\n\t\t\t\t options: ";
			  std::cout << "\n\n\t\t\t -Press [1] to modify the record: \n";
			  std::cout << "\t\t\t -Press [2] to delete the record: \n";
			  std::cout << "\t\t\t -Press [3] exit: \n";
			  int option;
			  std::cout << "\n\t\t\t *Please enter your choice: ";
			  std::cin >> option;
			  switch (option)
			  {

			  case 1: modify_guest_record(room_no);
				  break;

			  case 2: delete_record(room_no);
				  std::cout << "\n\t\t\t Room was deleted\n";
				  break;

			  case 3: break;
				  break;

			  default: std::cout << "\n\t\t\t Invalid choice !!\n";
				  break;
			  }
			  break;
		  }
	  }
	}
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


//check room availability 
int hotel::check_room_status(int new_room_no)
{
	int room_status = 0;
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	while (!readFromFile.eof())
	{
		readFromFile.read((char*)this, sizeof(hotel));
		if (new_room_no == roomNo)
		{
			//room is reserved
			room_status = 1;
			break;
		}
	}
	readFromFile.close();
	return (room_status);
}

 //adding a new guest 
void hotel::add_guest_record(int new_room_no)
{
	std::ofstream writeToFile;
	writeToFile.open("guestRecord.txt", std::ios::app | std::ios::binary);

	std::cout << "\n\t\tPlease enter guest details: \n";
	roomNo = new_room_no;
	std::cout << "\n\t\t-Name: ";
	std::cin >> Name;
	std::cout << "\n\t\t-Room type: ";
	std::cin >> roomType;
	std::cout << "\n\t\t-Arrangement type: ";        // BB(bad&breakfast) or BO(bad only)
	std::cin >> arrangement_type;
	std::cout << "\n\t\t-check-in: ";
	std::cin >> day1 >> mon1 >> year1;
	std::cout << "\n\t\t-check-out: ";
	std::cin >> day2 >> mon2 >> year2;
	std::cout << "\n\t\t-Phone no: ";
	std::cin >> phoneNo;
	std::cout << "\n\t\t-credit card no: ";
	std::cin >> creditCardNo;

	writeToFile.write((char*)this, sizeof(hotel));
	writeToFile.close();
}

//editing a guest record
void hotel::modify_guest_record(int room_no)
{
	//deleting the old record
	delete_record(room_no);

	system("cls");

	//adding the the new record
	add_guest_record(room_no);
	std::cout << "\n\t\t\t Record was modified\n";
}

//deleting a guest record
void hotel::delete_record(int room_no)
{
	std::fstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	std::fstream newFile("tempFile.txt", std::ios::out | std::ios::binary);
	
	
	while (readFromFile.read((char*)this, sizeof(hotel)))
	{	
		if (room_no!=roomNo)
		{
			newFile.write((char*)this, sizeof(hotel));	
		}
	}
	readFromFile.close();
	newFile.close();
	remove("guestRecord.txt");
	rename("tempFile.txt","guestRecord.txt");
}

//check the bill
void hotel::view_bill()
{
	int room_no;
	int room_status;
	std::ifstream readFromFile("guestRecord.txt", std::ios::in | std::ios::binary);
	
	if (!readFromFile)
	{
		std::cout << "\n\t\t File not found\n";
	}
	else
	{
		std::cout << "\n\t\tPlease Enter the room number: ";
		std::cin >> room_no;
		system("cls");
		readFromFile.read((char*)this, sizeof(hotel));
		while (!readFromFile.eof())
		{
			readFromFile.read((char*)this, sizeof(hotel));
			room_status = check_room_status(room_no);
			if (!room_status)
			{
				std::cout << "\n\t\t\t -Room not found-\n";
				break;
			}
			else
			{
				calculTheBill(room_no);
				readFromFile.read((char*)this, sizeof(hotel));
				break;
			}
		} 
	}
	readFromFile.close();
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();	
}

//calculate the bill of the guest 
void hotel::calculTheBill(int room_no)
{
	int nights;
	// this function works for dates with same year
	struct std::tm a = { 0,0,0,day1,mon1,120 };            //check-in date
	struct std::tm b = { 0,0,0,day2,mon2,120 };            //check-out date

	std::time_t x = std::mktime(&a);
	std::time_t y = std::mktime(&b);
	
	nights = (std::difftime(y, x) / 86400);                //we have 86400 in a day (60*60*24)
	
	//months with 30 days
	 if (mon1==4&&mon2==5||mon1==6&&mon2==7||mon1==9&&mon2==10||mon1==11&&mon2==12)
	 {
		nights -= 1;
  	 }
	 //months with 31 days
     if ( mon1 == 3 && mon2 == 4 || mon1 == 5 && mon2 == 6 || mon1 == 8 && mon2 == 9 || mon1 == 10 && mon2 == 11 || mon1 == 12 && mon2 == 1  )	 
     {
	  nights += 1;
     }
     else if (mon1 == 1 && mon2 == 2)
     {
	  nights += 2;
     }
	
     // leap year
     if ( mon1 == 2 && mon2==3 )
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
		 
	int sum1,sum2,sum3;
	int room_charge; 
	int total;
	
	if (roomType == "single")
	{
		room_charge = SINGLE_ROOM_PRICE;
		sum1 = nights * SINGLE_ROOM_PRICE;
		sum2 = TAXE*nights;
		sum3 = BREAKFAST_PRICE*nights;
	}
	if (roomType == "double")
	{
		room_charge = DOUBLE_ROOM_PRICE;
		sum1 = nights * DOUBLE_ROOM_PRICE;
		sum2 = TAXE*2 *nights;
		sum3 = BREAKFAST_PRICE*2*nights;
	}
	if (roomType == "triple")
	{
		room_charge = TRIPLE_ROOM_PRICE;
		sum1 = nights * TRIPLE_ROOM_PRICE;
		sum2 = TAXE*3 * nights;
		sum3 = BREAKFAST_PRICE*3 * nights;
	}
	if (arrangement_type == "BO")
	{
		sum3 = 0;
	}
	total = sum1 + sum2 + sum3;
	std::cout << "\n --------\n";
	std::cout << "| Hotelo |";
	std::cout << "\n --------\n";
	std::cout << "\n                                                   Date: " << day2 << "/" << mon2 << "/" << year2;
	std::cout << "\n                                                   Room number: " << roomNo;
        std::cout << "\n                                                   Room type: " << roomType;
	std::cout << "\n                                                   Name: " << Name;
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << "\n-----------------------------------Bill no: ------------------------------------\n";
	std::cout << " Service:    \t\tPrice: \t\t Amount: \t\tSum:          \n";
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << " Room charge:\t\t"<< room_charge <<" \t\t   "<<nights<<" \t\t        "<< sum1 <<"     \n\n";
	std::cout << " Taxes:      \t\t"<< TAXE << "                                      "<< sum2 <<"    \n\n";   //pax is person 
	std::cout << " Breakfast:  \t\t"<< BREAKFAST_PRICE<<"                                      "<< sum3 <<"    \n\n";
	std::cout << "\n--------------------------------------------------------------------------------\n";
	std::cout << "                                            Toltal:             "<<total<<"      \n\n";
	std::cout << "                                            TVA:10%             "<<total*0.1<< "\n\n";
	std::cout << "                                            NET:                "<<total+(total*0.1)<<"  \n\n";
}




























































































































