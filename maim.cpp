#include <iostream>
#include <Windows.h>
#include <locale>
#include <random>
#include <iomanip>

void Start();
std::vector<std::pair<int, std::string>> CreateJuceDrink();
std::vector<std::pair<int, std::string>> CreateVegetableDrink();
std::vector<std::pair<int, std::string>> CreateTeaDrink();

std::vector<std::pair<int, std::pair<int, std::string>>> ShopPage(std::vector<std::pair<int, std::string>> juiceList);

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));
	{
	int Capcha = rand() % 10000;
	std::cout << "КАПЧА: " << Capcha << std::endl;
	int Inp;
	std::cout << "ВВЕДИТЕ: ";
	std::cin >> Inp;

	if (Capcha != Inp)
	{
		std::cout << "НЕТ ВЫ РОБОТ" << std::endl;
		return 0;
	}
	}

	system("cls");
	
	bool bIsRunning = true;

	while (bIsRunning)
	{
		system("cls");
		int Inp;
		std::cout << "Выборк" << std::endl;
		std::cout << "0.Выход" << std::endl;
		std::cout << "1.Вход" << std::endl;

		std::cin >> Inp;

		switch (Inp)
		{
		case 0:
			bIsRunning = false;
			break;

		case 1:
			Start();
			int i;
			std::cout << "Продолжить тык" << std::endl;
			std::cin >> i;
			break;

		default:
			std::cout << "Ошибка" << std::endl;
		}
	}
	

	return 0;
}

void Start()
{
	bool bIsRunning = true;

	std::vector<std::pair<int, std::string>> JuiceList = CreateJuceDrink();
	std::vector<std::pair<int, std::string>> VegetableList = CreateVegetableDrink();
	std::vector<std::pair<int, std::string>> TeaList = CreateTeaDrink();

	std::vector<std::pair<int, std::pair<int, std::string>>> List;

	while (bIsRunning)
	{
		std::cout << "Соки севы" << std::endl;
		std::cout << "===Menu===" << std::endl;
		std::cout << "1.Соки" << std::endl;
		std::cout << "2.Фруктовые" << std::endl;
		std::cout << "3.Чаи" << std::endl;
		std::cout << "0.Выйти" << std::endl;


		std::cout << std::endl << "Input Action" << std::endl;

		int Inp;
		while (true)
		{
			if (std::cin >> Inp)
			{
				if (Inp >= 0 && Inp <= 3)
				{
					break;
				}
			}

			std::cout << "error" << std::endl << std::endl;
		}

		std::vector<std::pair<int, std::pair<int, std::string>>> result;

		switch (Inp)
		{
		case 0:
			bIsRunning = false;
			break;
		case 1:
			result = ShopPage(JuiceList);
			List.insert(List.end(), result.begin(), result.end());
			break;
		case 2:
			result = ShopPage(VegetableList);
			List.insert(List.end(), result.begin(), result.end());
			break;
		case 3:
			result = ShopPage(TeaList);
			List.insert(List.end(), result.begin(), result.end());
			break;
		}

		system("cls");
	}

	int Sum = 0;
	int TotalDisc = 0;
	int GiftOnionCount = 0;
	int OnionCost = 0;

	{
		int Count = 0;
		for (auto& object : List)
		{
			if (object.second.second == "Луковый сок")
			{
				OnionCost = object.first;
				Count += object.second.first;
			}
		}

		GiftOnionCount = Count / 4;
	}
	
	std::cout << "Корзина:" << std::endl;


	for (auto& object : List)
	{
		Sum += object.first * object.second.first;
		std::cout << object.second.second << "\t" << "Цена: " << object.first << " Количесвто: " << object.second.first << std::endl;
	}

	Sum -= GiftOnionCount * OnionCost;

	{
		int Count = 0;
		int Cost = 0;
		for (auto& object : List)
		{
			if (object.second.second == "Петрушковый чай")
			{
				Cost = object.first;
				Count += object.second.first;
			}
		}

		if (Count == 3)
		{
			int Disc = (Cost * Count) / 100 * 5;
			Sum -= Disc;
			TotalDisc += Disc;
		}
	}

	if (Sum > 999)
	{
		int Disc = Sum / 100 * 13;
		Sum -= Disc;
		TotalDisc += Disc;
	}

	std::cout << "Sum: " << Sum << std::endl;
	std::cout << "Луковый сок в подарок: " << GiftOnionCount << std::endl;
	std::cout << "Скидка: " << TotalDisc << std::endl;

}

std::vector<std::pair<int, std::string>> CreateJuceDrink()
{
	std::vector<std::pair<int, std::string>> List;

	List.push_back(std::pair<int, std::string>(100, "Яблочеый сок"));
	List.push_back(std::pair<int, std::string>(200, "Персиковый сок"));
	List.push_back(std::pair<int, std::string>(100, "Апельсиновый сок"));
	List.push_back(std::pair<int, std::string>(100, "Абрикосовый сок"));
	List.push_back(std::pair<int, std::string>(100, "Грушевый сок"));

	return List;
}

std::vector<std::pair<int, std::string>> CreateVegetableDrink()
{
	std::vector<std::pair<int, std::string>> List;

	List.push_back(std::pair<int, std::string>(100, "Томатный сок"));
	List.push_back(std::pair<int, std::string>(200, "Луковый сок"));
	List.push_back(std::pair<int, std::string>(100, "Огуречный сок"));

	return List;
}

std::vector<std::pair<int, std::string>> CreateTeaDrink()
{
	std::vector<std::pair<int, std::string>> List;

	List.push_back(std::pair<int, std::string>(100, "Чесночный чай"));
	List.push_back(std::pair<int, std::string>(200, "Петрушковый чай"));

	return List;
}

std::vector<std::pair<int, std::pair<int, std::string>>> ShopPage(std::vector<std::pair<int, std::string>> shopList)
{

	std::vector <std::pair<int, std::pair<int, std::string>>> List;
	std::cout << "Page" << std::endl;

	
	for (int i = 1; i < shopList.size() + 1; ++i)
	{
		std::cout << i << "." << shopList[i - 1].second << std::endl;
	}

	std::cout << "0.Выйти" << std::endl;

	int Inp;
	while (true)
	{
		std::cout << std::endl << "ВЫБЕРЕТЕ КАТЕГРОИЮ" << std::endl;

		if (std::cin >> Inp)
		{
			if (Inp == 0)
			{
				break;
			}

			if (Inp < 0 || Inp > shopList.size())
			{
				std::cout << "error input value" << std::endl << std::endl;
				continue;
			}

			int Inp_;
			std::cout << "Количество" << std::endl;
			std::cin >> Inp_;

			if (Inp_ < 0)
			{
				std::cout << "БОЛЬШЕ НУЛЯ" << std::endl;
				continue;
			}

			
			std::pair<int, std::pair<int, std::string>> Select;
			Select.first = shopList[Inp - 1].first;
			Select.second.second = shopList[Inp - 1].second;
			Select.second.first = Inp_;


			List.push_back(Select);
			std::cout << "Добавленно в корзину" << std::endl;
		}
	}

	return List;
}
