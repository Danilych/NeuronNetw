#include "NeuronNet.h"

NeuronNet::NeuronNet(int NeuronLayerAmount, int *ConnectionsAmounts, int a, float speed,  int* LayerNeuronAmount)
{
	//�������� ����             
	//���������� ����
	AmountOfLayers = NeuronLayerAmount;
	NetNeuronLayers = new NeuronLayer[AmountOfLayers];
	//��������� � � �������� �����������
	LearnSpeed = speed;
	A = a;
	//��������� ����
	int IndCounter = 0;
	for (int i = 0; i < AmountOfLayers; i++)
		//������ ������ � ����
		NetNeuronLayers[i].SetLayer(LayerNeuronAmount[i], &IndCounter, ConnectionsAmounts[i]);
}

void NeuronNet::OutputGraph()
{
	for (int i = AmountOfLayers - 1; i >= 0; i--)
	{
		for (int j = 0; j < NetNeuronLayers[i].GetNeuronsAmount(); j++)
			std::cout <<"=" << NetNeuronLayers[i][j].GetIndex() <<"=" << "\t";
		
		std::cout << std::endl;
	}

	//std::cout << "Result = " << NetNeuronLayers[AmountOfLayers - 1][0].GetData();
}

void NeuronNet::OutputGraphError()
{
	for (int i = AmountOfLayers - 1; i >= 0; i--)
	{
		for (int j = 0; j < NetNeuronLayers[i].GetNeuronsAmount(); j++)
			std::cout << "=" << NetNeuronLayers[i][j].GetError() << "=" << "\t";

		std::cout << std::endl;
	}

	//std::cout << "Result = " << NetNeuronLayers[AmountOfLayers - 1][0].GetData();
}

void NeuronNet::OutputGraphData()
{
	for (int i = AmountOfLayers - 1; i >= 0; i--)
	{
		for (int j = NetNeuronLayers[i].GetNeuronsAmount(); j >= 0; j--)
			std::cout << "=" << NetNeuronLayers[i][j].GetData() << "=" << "\t";

		std::cout << std::endl;
	}
}

void NeuronNet::OutputGraphB()
{
	for (int i = AmountOfLayers - 1; i >= 0; i--)
	{
		for (int j = 0; j < NetNeuronLayers[i].GetNeuronsAmount(); j++)
			std::cout << "=" << NetNeuronLayers[i][j].GetB() << "=" << "\t";

		std::cout << std::endl;
	}
}

void NeuronNet::OutputResult()
{
	for (int i = 9; i >=0; i--)
	{
		
		std::cout << "=" << NetNeuronLayers[AmountOfLayers-1][i].GetData() << "=" << "\t";

		//std::cout << std::endl;
	}
	std::cout << std::endl;
}

void NeuronNet::WriteData()
{
	Result = new float[10];
	
	for (int j = NetNeuronLayers[AmountOfLayers - 1].GetNeuronsAmount()-1; j >= 0; j--)
		Result[j] = NetNeuronLayers[AmountOfLayers - 1][j].GetData();
}

float NeuronNet::GetResultAtIndex(int i)
{
	return Result[i];
}

void NeuronNet::InputStartData(bool num[7][5])
{
	//���� ������ �� ������� ����
	int count = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 5; j++)
			//���� �������� ��� ������� ������� � ������� ����
			NetNeuronLayers[0][count++].SetDataS(num[i][j]);
}

void NeuronNet::CalcGeneration()
{
	//������ ����� ����� ���� (�� ������� �������� �� ��������)(����� �������)
	for (int i = 0; i < AmountOfLayers - 1; i++)
	{
		//������ �������� S ��� ������ ����� ��������
		float **S;
		//���������� �������� � ����� ����, ������ ����, ������� ������ ������� �� ��������
		//���� �������
		int n = 0, m = 0, icn = 0;

		//���������� �������� � ����� ����
		n = NetNeuronLayers[i].GetNeuronsAmount();
		//���������� �������� � ������ ����
		m = NetNeuronLayers[i+1].GetNeuronsAmount()-1;
		//���� ���� ��������, ����� ���������� �� �������, �� �������� ������ ��������
		if (i + 1 == AmountOfLayers - 1) m = NetNeuronLayers[i + 1].GetNeuronsAmount();
		//���� � ���� ����� 1 ������
		else if (m == 0) m = 1;

		S = new float*[m];
		for (int mm = 0; mm < m; mm++)
		{
			//S ������ ������ �������� ��� �������� ����� ���� � ������,
			//������� �� ������� ������� (���� ���� �����) � ���������, ������� ����� ������������ �
			//������� ���������, � ���������� �������� b
			S[mm] = new float[3];
			S[mm][0] = NetNeuronLayers[i + 1][mm].GetIndex(); //������ �������
			S[mm][1] = 0; //�������� S
			S[mm][2] = 0; //�������� b
		}

		for (int in = 0; in < n; in++) //��� ������� ������� � ����� ����
			for (int ic = 0; ic < m; ic++) //��� ������ ����� ������� �������
			{
				//������� ���� �����
				if (in < n - 1)
				{
					//��� ������� ��������
					float d = NetNeuronLayers[i][in].GetData() * NetNeuronLayers[i][in].GetConnectedWeight(ic);
					S[ic][1] += d;
				}
				else
				{
					//��� ������� ��������
					float d = NetNeuronLayers[i][in].GetData() * NetNeuronLayers[i][in].GetConnectedWeight(ic);
					S[ic][2] += d;
				}
				
				
			}
		
		//�������� ����� �������� �������� � ������ ����
		for (int mm = 0; mm < m; mm++)
		{
			//�������� b
			NetNeuronLayers[i + 1][mm].SetB(S[mm][2]);
			//��������� ������ �������� �� ������� ���������
			NetNeuronLayers[i + 1][mm].CalcData(S[mm][1], A);
		}
		
		//������� ������
		for (int mm = m-1; mm >=0; mm--)
			delete[] S[mm];
		
		delete[] S;
	}
}

void NeuronNet::CalcErrorDelta(bool DesiredResult[10])
{
	//������� ������ ��������
	//������� ������ (������) ��� ��������� ���� (��������� ��������� - ���������� �����)
	for (int i = 0; i < 10; i++)
		NetNeuronLayers[AmountOfLayers - 1][i].SetError(DesiredResult[i] - NetNeuronLayers[AmountOfLayers - 1][i].GetData());

	//����� ������ (������) ��� ��������� ���� (�� ��������� �� �������� ����)(������ ������)
	for (int i = AmountOfLayers-2; i >= 0; i--)
	{
		//���������� �������� � ������ ����
		int n = NetNeuronLayers[i + 1].GetNeuronsAmount();
		//���������� �������� � ����� ����
		int m = NetNeuronLayers[i].GetNeuronsAmount();
		//������ �������
		float wsum = 0;

		//������� ������ ����
		for (int ii = 0; ii < m; ii++) 
		{
			//��� ������ ����� ������� � ������ �����
			for (int jj = 0; jj < n; jj++) 
				//������� � ������ ������ (������)
				wsum += NetNeuronLayers[i + 1][jj].GetError() * NetNeuronLayers[i][ii].GetConnectedWeight(jj);
			NetNeuronLayers[i][ii].SetError(wsum);
			wsum = 0;
		}
	}

	//������ ����� ����� �������� (����� �������)
	for (int i = 0; i < AmountOfLayers - 1; i++)
	{
		//���������� ������� � ����� ����
		int n = NetNeuronLayers[i].GetNeuronsAmount();
		//���������� �������� � ������ ����
		int m = NetNeuronLayers[i+1].GetNeuronsAmount();
		//����� ���
		float wnew = 0;
		//��� ������� ������� � ����� ����
		for (int ii = 0; ii < n; ii++) 
		{
			//��� ������ ����� ������� � ������ �����
			for (int jj = 0; jj < m; jj++)
			{
				//������� ������ ���� � ��� ������
				wnew = NetNeuronLayers[i][ii].GetConnectedWeight(jj) + 
					LearnSpeed * NetNeuronLayers[i + 1][jj].GetError() * (NetNeuronLayers[i + 1][jj].GetData() * 
						(1 - NetNeuronLayers[i + 1][jj].GetData())) * NetNeuronLayers[i][ii].GetData();
				NetNeuronLayers[i][ii].SetConnectionWeight(jj, wnew);
				wnew = 0;
			}
		}
	}
}
