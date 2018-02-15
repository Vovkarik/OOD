#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino() 
		:CCoffee("Capuccino") 
	{}

	double GetCost() const override 
	{
		return 80; 
	}
};

// Двойной капуччино
class CDoubleCapuccino : public CCoffee
{
public:
	CDoubleCapuccino()
		:CCoffee("Capuccino")
	{}

	double GetCost() const override
	{
		return 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte() 
		:CCoffee("Latte") 
	{}

	double GetCost() const override 
	{
		return 90; 
	}
};

// Двойной латте
class CDoubleLatte : public CCoffee
{
public:
	CDoubleLatte()
		:CCoffee("Double latte")
	{}

	double GetCost() const override
	{
		return 130;
	}
};

// Чай улун
class COolongTea : public CBeverage
{
public:
	COolongTea()
		:CBeverage("Oolong tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Чай эрл грей
class CErlGreyTea : public CBeverage
{
public:
	CErlGreyTea()
		:CBeverage("Erl Grey tea")
	{}

	double GetCost() const override
	{
		return 30;
	}
};

// Жасминовый чай
class CJasmineTea : public CBeverage
{
public:
	CJasmineTea()
		:CBeverage("Jasmine tea")
	{}

	double GetCost() const override
	{
		return 30;
	}
};

// Фруктовый
class CFruitTea : public CBeverage
{
public:
	CFruitTea()
		:CBeverage("Fruit tea")
	{}

	double GetCost() const override
	{
		return 30;
	}
};

// Молочный коктейль маленький
class CSmallMilkshake : public CBeverage
{
public:
	CSmallMilkshake() 
		:CBeverage("Small milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 50; 
	}
};

// Молочный коктейль средний
class CMediumMilkshake : public CBeverage
{
public:
	CMediumMilkshake()
		:CBeverage("Medium milkshake")
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Молочный коктейль большой
class CBigMilkshake : public CBeverage
{
public:
	CBigMilkshake()
		:CBeverage("Big milkshake")
	{}

	double GetCost() const override
	{
		return 80;
	}
};
