#pragma once
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<dos.h>
#include<conio.h>
#include<ctime>


constexpr auto SINGLE_ROOM_PRICE = 500;
constexpr auto DOUBLE_ROOM_PRICE = 600;
constexpr auto TRIPLE_ROOM_PRICE = 800;
constexpr auto BREAKFAST_PRICE = 60;
constexpr auto TAXE = 10;

//class hotel

class Hotel
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

	Hotel();

	void home_func();

	void main_menu();                      // main menu function

    int check_room_status(int);            // check room availability 

	void display_reserved_rooms();         // display list of reserved room

	void display_guest_record();           // view specific guest record

	void book_a_room();                   // to book a rooom

	void add_guest_record(int);           // adding a new guest 

	void modify_guest_record(int);        // editing a guest record

	void delete_record(int);              //deleting a guest record
	
	void view_bill();                    // billing function

	void calculTheBill(int);             //calculate the bill of the guest 
	
};














