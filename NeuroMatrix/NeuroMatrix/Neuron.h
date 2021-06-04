#include <cmath>

#pragma once
class Neuron
{
	int index;
	float b = 0;
	float Data = -1;
	float* ConnecitonsWeight;
	float ErrorDelta = 0;

public:
	//Начальные значения нейрона
	void SetData(int i, int CAmount, int Dat);
	//Использование функции активации
	void CalcData(float S, float a);
	//Задание даты без функции
	void SetDataS(float data);
	//Индекс нейрона
	int GetIndex();
	//Получение веса i-ой связи нейрона
	float GetConnectedWeight(int i);
	//Задание веса i-ой связи нейрона
	void SetConnectionWeight(int index, float value);
	//Получение значения
	float GetData();
	//Получение значения b
	float GetB();
	//Задание значения b
	void SetB(float B);
	//Задание ошибки
	void SetError(float error);
	//Получение ошибки
	float GetError();
};

