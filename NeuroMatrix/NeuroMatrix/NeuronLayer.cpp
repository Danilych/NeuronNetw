#include "NeuronLayer.h"

void NeuronLayer::SetLayer(int NAmount, int *IndexCounter, int CAmount)
{
	//�������� ����
	//���������� �������� � ����
	NeuronAmount = NAmount;
	LayerNeurons = new Neuron[NeuronAmount];
	//�������� �������� � ����, ������� ������ ��������
	for (int i = 0; i < NeuronAmount; i++)
	{
		//������ ��������
		if(i==NeuronAmount-1) LayerNeurons[i].SetData(*IndexCounter, CAmount, 1);
		//��������� �������
		else LayerNeurons[i].SetData(*IndexCounter, CAmount, -1);
		*IndexCounter = *IndexCounter + 1;
	}
}

int NeuronLayer::GetNeuronsAmount()
{
	return NeuronAmount;
}

Neuron& NeuronLayer::operator[](int i)
{
	if (i < NeuronAmount) return LayerNeurons[i];
	else throw "Out of size bounds!";
}
