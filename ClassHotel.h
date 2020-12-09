#pragma once

//class hotel
class hotel
{
private:
	int roomNo;
	std::string Name;
	std::string roomType;
	std::string arrangement_type;     // bad & breakfats(BB) or bad only (BO)
	int day1, mon1, year1;           // check -in or arrival Date
	int day2, mon2, year2;           // check-out or daparture Date
	int phoneNo;
	int creditCardNo;
public:
	void main_menu();  

    int check_room_status(int);

	void display_reserved_rooms();

	void display_guest_record();

	void book_a_room();

	void add_guest_record(int);

	void modify_guest_record(int);

	void delete_record(int);
	
	void view_bill();

	void calculTheBill(int);
	
};














