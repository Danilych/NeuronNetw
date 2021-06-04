#include<iostream>
#include "NeuronLayer.h"

#pragma once

class NeuronNet
{	
	//���������� ����
	int AmountOfLayers = 0;
	//����
	NeuronLayer* NetNeuronLayers;
	//��������� � � �������� ��������
	float LearnSpeed = 0;
	float A = 0;
	//��������� �������� ��������
	float *Result;

public:
	//����������� ����
	NeuronNet(int NeuronLayerAmount, int* ConnectionsAmounts, int a, float speed, int* LayerNeuronAmount);

	//����� ������ � ��������
	void OutputGraph();
	void OutputGraphError(); 
	void OutputGraphData();
	void OutputGraphB();
	void OutputResult();
	//������ ����������
	void WriteData();
	float GetResultAtIndex(int i);

	//���� � ������� ����
	void InputStartData(bool num[7][5]);
	//������ �����
	void CalcGeneration();
	//������� ������ ��������(��������)
	void CalcErrorDelta(bool DesiredResult[10]);
};

