#include "Neuron.h"

#pragma once
class NeuronLayer
{
	//Нейрона в слое
	Neuron* LayerNeurons;
	//Количество нейронов
	int NeuronAmount;

public:
	//Задание слоя
	void SetLayer(int NAmount, int* IndexCounter, int CAmount);
	//Получить количество нейронов в слое
	int GetNeuronsAmount();
	//Обращение к нейрону по индексу
	Neuron& operator[](int i);
	
};

