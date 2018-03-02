#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class Stats
{
public:
	Stats(const std::string & description)
		: m_description(description)
	{}
	double GetMin()
	{
		return m_min;
	}
	void SetMin(double const& min)
	{
		m_min = min;
	}
	double GetMax()
	{
		return m_max;
	}
	void SetMax(double const& max)
	{
		m_max = max;
	}
	double GetAcc()
	{
		return m_acc;
	}
	void UpdateAcc(double const& measurment)
	{
		m_acc += measurment;
	}
	unsigned GetCount()
	{
		return m_count;
	}
	void UpdateCount()
	{
		m_count++;
	}
	std::string GetDescription()
	{
		return m_description;
	}
private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_count = 0;
	std::string m_description;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void UpdateMeasurment(Stats & stats, double const& current)
	{
		if (stats.GetMin() > current)
		{
			stats.SetMin(current);
		}
		if (stats.GetMax() < current)
		{
			stats.SetMax(current);
		}
		stats.UpdateAcc(current);
		stats.UpdateCount();

		std::cout << "Max " << stats.GetDescription() << ": " << stats.GetMax() << std::endl;
		std::cout << "Min " << stats.GetDescription() << ": " <<stats.GetMin() << std::endl;
		std::cout << "Average " << stats.GetDescription() << ": " << (stats.GetAcc() / stats.GetCount()) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void Update(SWeatherInfo const& data) override
	{
		UpdateMeasurment(tempStat, data.temperature);
		UpdateMeasurment(humidityStat, data.humidity);
		UpdateMeasurment(pressureStat, data.pressure);
	}
	Stats tempStat{ "Temperature" }, humidityStat{ "Humidity" }, pressureStat{ "Pressure" };
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
