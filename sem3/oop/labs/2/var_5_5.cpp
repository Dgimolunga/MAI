#include <iostream>
#include <string>
#include "../../data_structures/vector.h"
#include "../../data_structures/queue.h"
#include "factory.h"

typedef std::pair<std::string, size_t> Item;

struct Figure
{
	Item key;
	Shape* shape;
};

typedef ds::Queue<Figure> Cont;
typedef ds::Queue<Figure>::iterator ContIt;

void addFigure(Cont& cont, const Figure& figure);
void deleteFigure(Cont& cont, const Figure& figure);

int main()
{
	size_t action;
	ds::Vector<Cont> arr;

	while (true)
	{
		std::cout << "Menu" << std::endl;
		std::cout << "1) Add item" << std::endl;
		std::cout << "2) Find item" << std::endl;
		std::cout << "3) Remove item" << std::endl;
		std::cout << "4) Print all items" << std::endl;
		std::cout << "5) Calculate square" << std::endl;
		std::cout << "6) Exit" << std::endl;

		std::cout << "Choose action: ";
		std::cin >> action;
		std::cin.ignore();

		if (action == 6)
			break;

		if (action == 0 || action > 5)
		{
			std::cout << "Error. No such action in menu" << std::endl;

			continue;
		}

		switch (action)
		{
			case 1:
			{
				size_t var;
				Figure figure;
				Factory factory;

				std::cout << "Name: ";
				std::getline(std::cin, figure.key.first);
				std::cout << "Id: ";
				std::cin >> figure.key.second;

				std::cout << "Figure type:" << std::endl;
				std::cout << "1) Romb" << std::endl;
				std::cout << "2) Side5" << std::endl;
				std::cout << "3) Side6" << std::endl;
				std::cin >> var;
				std::cin.ignore();

				if (var == 0 || var > 3)
				{
					std::cout << "Error. No such type of shape in menu" << std::endl;

					continue;
				}

				figure.shape = factory.makeShape(var);
				figure.shape->input();

				if (arr.empty() || arr[arr.size() - 1].size() == 5)
					arr.push_back(Cont());

				addFigure(arr[arr.size() - 1], figure);

				break;
			}

			case 2:
			{
				bool isFound = false;
				Item item;

				std::cout << "Name: ";
				std::getline(std::cin, item.first);
				std::cout << "Id: ";
				std::cin >> item.second;
				std::cin.ignore();

				for (size_t i = 0; i < arr.size(); ++i)
				{
					for (ContIt it = arr[i].begin(); it != arr[i].end(); ++it)
					{
						if (it->key == item)
						{
							std::cout << "================================" << std::endl;
							std::cout << "Container #" << (i + 1) << ":" << std::endl;
							std::cout << "Name: " << it->key.first << std::endl;
							std::cout << "Id: " << it->key.second << std::endl;

							it->shape->printInfo();

							std::cout << "================================" << std::endl;

							isFound = true;
						}
					}
				}

				if (!isFound)
				{
					std::cout << "================================" << std::endl;
					std::cout << "Not found" << std::endl;
					std::cout << "================================" << std::endl;
				}

				break;
			}

			case 3:
			{
				bool isRemoved = false;
				Item item;

				std::cout << "Name: ";
				std::getline(std::cin, item.first);
				std::cout << "Id: ";
				std::cin >> item.second;
				std::cin.ignore();

				for (size_t i = 0; i < arr.size(); ++i)
				{
					for (ContIt it = arr[i].begin(); it != arr[i].end(); ++it)
					{
						if (it->key == item)
						{
							std::cout << "================================" << std::endl;
							std::cout << "Object was deleted" << std::endl << std::endl;
							std::cout << "Container #" << (i + 1) << ":" << std::endl;
							std::cout << "Name: " << it->key.first << std::endl;
							std::cout << "Id: " << it->key.second << std::endl;

							it->shape->printInfo();

							std::cout << "================================" << std::endl;

							delete it->shape;

							deleteFigure(arr[i], *it);

							if (arr[i].empty())
								arr.erase(i);

							isRemoved = true;

							break;
						}
					}

					if (isRemoved)
						break;
				}
				
				break;
			}

			case 4:
			{
				std::cout << "================================" << std::endl;

				for (size_t i = 0; i < arr.size(); ++i)
				{
					std::cout << "----Container #" << (i + 1) << ":" << std::endl;

					for (ContIt it = arr[i].begin(); it != arr[i].end(); ++it)
					{
						std::cout << std::endl;
						std::cout << "Name: " << it->key.first << std::endl;
						std::cout << "Id: " << it->key.second << std::endl;

						it->shape->printInfo();
					}

					if (i + 1 < arr.size())
						std::cout << std::endl;
				}

				std::cout << "================================" << std::endl;

				break;
			}

			case 5:
			{
				double square = 0;
				Visitor visitor;

				for (size_t i = 0; i < arr.size(); ++i)
				{
					for (ContIt it = arr[i].begin(); it != arr[i].end(); ++it)
					{
						square += it->shape->accept(&visitor);
					}
				}

				std::cout << "================================" << std::endl;
				std::cout << "Sum of squares: " << square << std::endl;
				std::cout << "================================" << std::endl;

				break;
			}
		}
	}

	return 0;
}

void addFigure(Cont& cont, const Figure& figure)
{
	Cont q;

	while (!cont.empty() && cont.front().key <= figure.key)
	{
		q.push(cont.front());
		cont.pop();
	}

	q.push(figure);

	while (!cont.empty())
	{
		q.push(cont.front());
		cont.pop();
	}
	
	std::swap<Cont>(cont, q);
}

void deleteFigure(Cont& cont, const Figure& figure)
{
	Cont q;

	while (!cont.empty() && cont.front().key != figure.key)
	{
		q.push(cont.front());
		cont.pop();
	}
	
	if (!cont.empty())
		cont.pop();

	while (!cont.empty())
	{
		q.push(cont.front());
		cont.pop();	
	}

	std::swap<Cont>(cont, q);
}
