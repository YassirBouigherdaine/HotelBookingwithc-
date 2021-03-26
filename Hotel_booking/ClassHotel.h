#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<conio.h>


constexpr auto SINGLE_ROOM_PRICE = 500;
constexpr auto DOUBLE_ROOM_PRICE = 600;
constexpr auto TRIPLE_ROOM_PRICE = 800;
constexpr auto BREAKFAST_PRICE = 60;
constexpr auto TAXE = 10;



//class hotel

class Hotel
{
	int roomNo;

	std::string Name;

	std::string roomType;

	std::string arrang_type;     // bad & breakfats(BB) or bad only (BO)

	int day1, mon1, year1;           // check-in or arrival Date

	int day2, mon2, year2;           // check-out or daparture Date

	int phoneNo;

	int creditCardNo;

public:

	Hotel();

	void home_func();

	void main_menu();                      // main menu function

	int check_room_status(int);            // check room availability 

	int is_exist(std::string);

	void add_to_presents(std::string);

	void display_reserved_rooms();         // display list of reserved room

	void display_departures_list();

	void display_arrivals_list();

	void display_guest_record();           // view specific guest record

	void add_guest_record();           // adding a new guest 

	void modify_guest_record(std::string);        // editing a guest record

	void delete_record(std::string);              //deleting a guest record

	void calculTheBill(std::string);             //calculate the bill of the guest 

};


