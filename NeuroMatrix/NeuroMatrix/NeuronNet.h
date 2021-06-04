#include<iostream>
#include "NeuronLayer.h"

#pragma once

class NeuronNet
{	
	//Количество слоёв
	int AmountOfLayers = 0;
	//Слои
	NeuronLayer* NetNeuronLayers;
	//Константа а и скорость обучения
	float LearnSpeed = 0;
	float A = 0;
	//Результат выходных нейронов
	float *Result;

public:
	//Конструктор сети
	NeuronNet(int NeuronLayerAmount, int* ConnectionsAmounts, int a, float speed, int* LayerNeuronAmount);

	//Вывод данных о вершинах
	void OutputGraph();
	void OutputGraphError(); 
	void OutputGraphData();
	void OutputGraphB();
	void OutputResult();
	//Запись результата
	void WriteData();
	float GetResultAtIndex(int i);

	//Ввод в входной слой
	void InputStartData(bool num[7][5]);
	//Проход эпохи
	void CalcGeneration();
	//Просчёт ошибок нейронов(обучение)
	void CalcErrorDelta(bool DesiredResult[10]);
};

