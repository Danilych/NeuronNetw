#include "Neuron.h"

void Neuron::SetData(int i, int CAmount, int Dat)
{
	//�������� �������
	//����������� ��������
	b = (float)(rand() % 201 - 100) / 1000.f;
	//������ �������
	index = i;
	//�������� �������
	Data = Dat;
	//��� ������ ������� � ���������� ���������
	ConnecitonsWeight = new float[CAmount];

	for (int i = 0; i < CAmount; i++)
		ConnecitonsWeight[i] =  (float)(rand() % 201 - 100) / 100.f;
}

void Neuron::CalcData(float S, float a)
{
	//������������� ������� ���������
	float t = (-a * (S+b));
	Data = 1.f/(1.f+exp(t));
}

void Neuron::SetDataS(float data)
{
	//���� ������ � ����� �������
	Data = data;
}

int Neuron::GetIndex()
{
	return index;
}

float Neuron::GetConnectedWeight(int i)
{
	return ConnecitonsWeight[i];
}

void Neuron::SetConnectionWeight(int index, float value)
{
	ConnecitonsWeight[index] = value;
}

float Neuron::GetData()
{
	return Data;
}

float Neuron::GetB()
{
	return b;
}

void Neuron::SetB(float B)
{
	//�������� b
	b = B;
}

void Neuron::SetError(float error)
{
	ErrorDelta = error;
}

float Neuron::GetError()
{
	return ErrorDelta;
}
