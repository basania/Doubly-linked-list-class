// List.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "List_class.h"

void list_insert(List<int>& lst)
{

	std::cout << "Inserting first five even numbers at the end of the list.\n";

	for (int i = 1; i <= 10; ++i)
		lst.push_back(i + 1);
}

void print_list(List<int>& lst)
{
	List<int>::iterator q = lst.begin();
	List<int>::iterator qq = lst.end();

	for (; q != qq; q++)
		std::cout << *q << std::endl;
}

void printLots(List<int>& p, List<int>& q)
{
	List<int>::iterator pp = p.begin();
	List<int>::iterator pp_end = p.end();

	List<int>::iterator qq = q.begin();
	List<int>::iterator qq_end = q.end();
}


int main()
{
	List<int> list1;
	list_insert(list1);

	List<int> list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);

	printLots(list1, list2);

	List<int>::iterator q = list1.begin();
	auto s = q;
	s++;
	List<int>::iterator qq = s;

	list1.swap_adj(q, qq);

	print_list(list1);
}

