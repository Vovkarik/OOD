#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [] (IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage = 
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage = 
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

void DialogWithUser()
{
	cout << "Enter the number of the position in menu.\nMenu:\n1.Coffe\n2.Capuccino\n3.Double capuccino\n4.Latte\n5.Double latte\n6.Oolong tea\n7.Erl Grey tea\n8.Jasmine tea\n9.Fruit tea\n10.Small milkshake\n11.Medium milkshake\n12.Big milkshake\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		beverage = make_unique<CCoffee>();
	}
	else if (beverageChoice == 2)
	{
		beverage = make_unique<CCapuccino>();
	}
	else if (beverageChoice == 3)
	{
		beverage = make_unique<CDoubleCapuccino>();
	}
	else if (beverageChoice == 4)
	{
		beverage = make_unique<CLatte>();
	}
	else if (beverageChoice == 5)
	{
		beverage = make_unique<CDoubleLatte>();
	}
	else if (beverageChoice == 6)
	{
		beverage = make_unique<COolongTea>();
	}
	else if (beverageChoice == 7)
	{
		beverage = make_unique<CErlGreyTea>();
	}
	else if (beverageChoice == 8)
	{
		beverage = make_unique<CJasmineTea>();
	}
	else if (beverageChoice == 9)
	{
		beverage = make_unique<CFruitTea>();
	}
	else if (beverageChoice == 10)
	{
		beverage = make_unique<CSmallMilkshake>();
	}
	else if (beverageChoice == 11)
	{
		beverage = make_unique<CMediumMilkshake>();
	}
	else if (beverageChoice == 12)
	{
		beverage = make_unique<CBigMilkshake>();
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		cout << "1 - Lemon, 2 - Cinnamon, 0 - Checkout" << endl;
		cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			beverage = move(beverage) << MakeCondiment<CLemon>(2);
		}
		else if (condimentChoice == 2)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == 0)
		{
			break;
		}
		else
		{
			return;
		}
	}



	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}


int main()
{
	DialogWithUser();
	cout << endl;
}
