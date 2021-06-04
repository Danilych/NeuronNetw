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
	//��������� �������� �������
	void SetData(int i, int CAmount, int Dat);
	//������������� ������� ���������
	void CalcData(float S, float a);
	//������� ���� ��� �������
	void SetDataS(float data);
	//������ �������
	int GetIndex();
	//��������� ���� i-�� ����� �������
	float GetConnectedWeight(int i);
	//������� ���� i-�� ����� �������
	void SetConnectionWeight(int index, float value);
	//��������� ��������
	float GetData();
	//��������� �������� b
	float GetB();
	//������� �������� b
	void SetB(float B);
	//������� ������
	void SetError(float error);
	//��������� ������
	float GetError();
};

