#include "NeuronNet.h"

NeuronNet::NeuronNet(int NeuronLayerAmount, int *ConnectionsAmounts, int a, float speed,  int* LayerNeuronAmount)
{
	//Создание сети             
	//Количество слоёв
	AmountOfLayers = NeuronLayerAmount;
	NetNeuronLayers = new NeuronLayer[AmountOfLayers];
	//Константа а и скорость обучаемости
	LearnSpeed = speed;
	A = a;
	//Генерация слоёв
	int IndCounter = 0;
	for (int i = 0; i < AmountOfLayers; i++)
		//Подача данных о слое
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
	//Ввод данных во входной слой
	int count = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 5; j++)
			//Ввод значения для каждого нейрона в входном слое
			NetNeuronLayers[0][count++].SetDataS(num[i][j]);
}

void NeuronNet::CalcGeneration()
{
	//Проход одной эпохи сети (от входным нейронов до выходных)(слева направо)
	for (int i = 0; i < AmountOfLayers - 1; i++)
	{
		//Хранит значение S для каждой связи нейронов
		float **S;
		//Количество нейронов в левом слое, правом слое, текущий индекс нейрона от которого
		//идут расчёты
		int n = 0, m = 0, icn = 0;

		//Количество нейронов в левом слое
		n = NetNeuronLayers[i].GetNeuronsAmount();
		//Количество нейронов в правом слое
		m = NetNeuronLayers[i+1].GetNeuronsAmount()-1;
		//Если слой выходной, чтобы подсчитать всё нейроны, не исключая нейрон смещения
		if (i + 1 == AmountOfLayers - 1) m = NetNeuronLayers[i + 1].GetNeuronsAmount();
		//Если в слое всего 1 нейрон
		else if (m == 0) m = 1;

		S = new float*[m];
		for (int mm = 0; mm < m; mm++)
		{
			//S массив связей нейронов для текущего левая слоя с правым,
			//состоит из индекса нейрона (куда идет свзяь) и значением, которое будет использовано в
			//формуле активаций, и коэффицент смещения b
			S[mm] = new float[3];
			S[mm][0] = NetNeuronLayers[i + 1][mm].GetIndex(); //индекс нейрона
			S[mm][1] = 0; //значение S
			S[mm][2] = 0; //Значение b
		}

		for (int in = 0; in < n; in++) //Для каждого нейрона в левом слое
			for (int ic = 0; ic < m; ic++) //Для каждой связи данного нейрона
			{
				//Подсчёт даты сязей
				if (in < n - 1)
				{
					//Для обычных нейронов
					float d = NetNeuronLayers[i][in].GetData() * NetNeuronLayers[i][in].GetConnectedWeight(ic);
					S[ic][1] += d;
				}
				else
				{
					//Для нейрона смещения
					float d = NetNeuronLayers[i][in].GetData() * NetNeuronLayers[i][in].GetConnectedWeight(ic);
					S[ic][2] += d;
				}
				
				
			}
		
		//Получаем новые значения нейронов в правом слое
		for (int mm = 0; mm < m; mm++)
		{
			//Значение b
			NetNeuronLayers[i + 1][mm].SetB(S[mm][2]);
			//Получение нового значения по функции активации
			NetNeuronLayers[i + 1][mm].CalcData(S[mm][1], A);
		}
		
		//Очистка памяти
		for (int mm = m-1; mm >=0; mm--)
			delete[] S[mm];
		
		delete[] S;
	}
}

void NeuronNet::CalcErrorDelta(bool DesiredResult[10])
{
	//Подсчёт ошибки нейронов
	//Подсчёт ошибки (дельта) для выходного слоя (ожидаемый результат - полученный сетью)
	for (int i = 0; i < 10; i++)
		NetNeuronLayers[AmountOfLayers - 1][i].SetError(DesiredResult[i] - NetNeuronLayers[AmountOfLayers - 1][i].GetData());

	//Подсёт ошибки (дельта) для остальных слоёв (от выходного до входного слоя)(справа налево)
	for (int i = AmountOfLayers-2; i >= 0; i--)
	{
		//количество нейронов в правом слое
		int n = NetNeuronLayers[i + 1].GetNeuronsAmount();
		//Количество нейронов в левом слое
		int m = NetNeuronLayers[i].GetNeuronsAmount();
		//Ошибка нейрона
		float wsum = 0;

		//Нейрона левого слоя
		for (int ii = 0; ii < m; ii++) 
		{
			//Для каждой свзяи нейрона с правым слоем
			for (int jj = 0; jj < n; jj++) 
				//Подсчёт и запись ошибки (дельта)
				wsum += NetNeuronLayers[i + 1][jj].GetError() * NetNeuronLayers[i][ii].GetConnectedWeight(jj);
			NetNeuronLayers[i][ii].SetError(wsum);
			wsum = 0;
		}
	}

	//Запись новых весов нейронов (слева направо)
	for (int i = 0; i < AmountOfLayers - 1; i++)
	{
		//Количество нейроно в левом слое
		int n = NetNeuronLayers[i].GetNeuronsAmount();
		//Количество нейронов в правом слое
		int m = NetNeuronLayers[i+1].GetNeuronsAmount();
		//Новый вес
		float wnew = 0;
		//Для каждого нейрона в левом слое
		for (int ii = 0; ii < n; ii++) 
		{
			//Для каждой свзяи нейрона с правым слоем
			for (int jj = 0; jj < m; jj++)
			{
				//Подсчёт нового веса и его запись
				wnew = NetNeuronLayers[i][ii].GetConnectedWeight(jj) + 
					LearnSpeed * NetNeuronLayers[i + 1][jj].GetError() * (NetNeuronLayers[i + 1][jj].GetData() * 
						(1 - NetNeuronLayers[i + 1][jj].GetData())) * NetNeuronLayers[i][ii].GetData();
				NetNeuronLayers[i][ii].SetConnectionWeight(jj, wnew);
				wnew = 0;
			}
		}
	}
}
