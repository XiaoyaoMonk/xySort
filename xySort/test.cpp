#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <array>
#include <utility>
#include <queue>
#include <cstdlib>
#include <ctime>

#include "BubbleSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "SelectSort.hpp"
#include "ShellSort_InsSort.hpp"
#include "CountSort.hpp"

using namespace std;

int main()
{
	srand((int)time(0));
	int tempInt = 0;
	vector<int> vArr1;
	vector<int> vArr2;
	for (int i = 0; i < 100000; ++i)
	{
		tempInt = rand();
		vArr1.push_back(tempInt);
		vArr2.push_back(tempInt);
	}

	sort(vArr1.begin(), vArr1.end());

	clock_t start_time = clock();
	//�������� ������ 100000 ����������Ĳ���
	//Intel i7 8700 CPU��16G�ڴ棻Win10 64λ ������ϵͳ��û�д򿪺�ռ���ڴ�������ִ�з�ʽΪ VS2019 ����
	shellSort(vArr2);//0.2s ����
	bubbleSort(vArr2);//330s ����
	bubbleSortEx(vArr2);//330s ����
	mergeSort<vector<int>, int>(vArr2, 0, vArr2.size() - 1);//1s ����
	mergeSort<vector<int>, int>(vArr2);//0.5s ����
	quickSort(vArr2, 0, vArr2.size() - 1);//0.15s ����
	quickSortEX(vArr2, 0, vArr2.size() - 1);//0.1s ����
	quickSortNR(vArr2, 0, vArr2.size() - 1);//0.3s ����
	selectSort(vArr2);//150s ����
	insertSort(vArr2);//122s ����
	binaryInsertSort(vArr2);//80s ����
	heapSort(vArr2);//0.15s ����
	countSort<vector<int>, int>(vArr2);//17s ���𣬺��ȶ���������Ϊ 1000000 ʱ������Ϊ 17s ����
	//��ʵ�Ȿ���е� countSort �ڵ���״̬����Ҫ�ܳ�ʱ��ԭ���� try catch �� C++ ������ռ���˴���ʱ��
	clock_t end_time = clock();

	for (int i = 0; i < vArr2.size(); ++i)
	{
		if (vArr1[i] != vArr2[i])
		{
			cout << "Sort has error..." << endl;
			break;
		}
	}
	double burningTime = ((double)end_time - (double)start_time) / 1000;
	cout << "The sorting algorithm uses " << burningTime << "s." << endl;
	return 0;
}