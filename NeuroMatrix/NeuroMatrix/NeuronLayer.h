#include "Neuron.h"

#pragma once
class NeuronLayer
{
	//������� � ����
	Neuron* LayerNeurons;
	//���������� ��������
	int NeuronAmount;

public:
	//������� ����
	void SetLayer(int NAmount, int* IndexCounter, int CAmount);
	//�������� ���������� �������� � ����
	int GetNeuronsAmount();
	//��������� � ������� �� �������
	Neuron& operator[](int i);
	
};

