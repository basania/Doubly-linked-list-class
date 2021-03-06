// List.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "List_class.h"


template <typename Iterator, typename Object>
Iterator find2(Iterator first, Iterator last, const Object & x)
{
	for (; first != last; first++)
	{
		if (*first == x)
			return first;
	}
	return last;
}

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

	auto x = find2(list1.begin(), list1.end(), 10);
	auto xx = list1.end();

	auto xxx = 5 - *x;

	if (x != xx)
		std::cout << "x = " << *x << std::endl;
	else
		std::cout << "not found\n";

	auto qqq = --list1.end();
	std::cout << *qqq << std::endl;

	std::cout << "xxx = " << xxx << std::endl;

	auto ls1 = list1.begin();
	ls1++;
	ls1++;

	std::cout << "---- list1 ----\n";
	print_list(list1);
	std::cout << "---- list1 ----\n";

	std::cout << "---- list2 ----\n";
	print_list(list2);
	std::cout << "---- list2 ----\n";


	list1.splice(ls1, list2);

	print_list(list1);
}

