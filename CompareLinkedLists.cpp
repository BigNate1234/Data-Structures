//
//  main.cpp
//  Comparing Linked Lists
//
//  Created by Nathan Furman on 1/26/17.
//  Copyright © 2017 Nathan Furman. All rights reserved.
//

#include <string>
#include <iostream>

using namespace std;

struct people
{ string name;
	int age;
	people * next;
	
	people(string n, int a, people * o)
	{ name = n;
		age = a;
		next = o; }
	
	void printone()
	{ cout << name << ", age " << age << "\n"; }
};

people * make_list(people * all)
{
	while (true)
	{ string n;
		int a;
		
		cout << "Enter name, or **** to end: ";
		cin >> n;
		if (n == "****")
			break;
		cout << "Enter age: ";
		cin >> a;
		all = new people(n, a, all); }
	return all;
}

int main() {
	cout << "Entering list one\n";
	people * L1 = make_list(NULL);
	cout << endl;
	cout << "Entering list two\n";
	people * L2 = make_list(NULL);
	cout << endl << endl;
	
	cout << "L1 includes:\n";
	people * temp = L1;
	while (temp != NULL)
	{ temp->printone();
		temp = temp->next; }
	
	cout << endl << endl;
	
	cout << "L2 includes:\n";
	people * temp2 = L2;
	while (temp2 != NULL)
	{ temp2->printone();
		temp2 = temp2->next; }
	
	cout << endl;
	
	temp = L1;
	temp2 = L2;
	while((temp->name == temp2->name) && (temp->age == temp2->age)){
		if (temp->next == NULL) { // nothing else after
			cout << "Lists are the same!\n";
			exit(0);
		}
		temp = temp->next;
		temp2 = temp2->next;
	}
	cout << "Lists are not the same!\n";
}
