/*
 * @Author       : yaowenzhou
 * @Date         : 2021-01-17 14:31:10
 * @LastEditors  : yaowenzhou
 * @LastEditTime : 2021-01-17 14:35:10
 * @version      : 
 * @Description  : 
 */
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
	//以下是在 数据量 100000 的情况下做的测试
	//Intel i7 8700 CPU；16G内存；Win10 64位 操作做系统；没有打开很占用内存的软件；执行方式为 VS2019 调试
	shellSort(vArr2);//0.2s 级别
	bubbleSort(vArr2);//330s 左右
	bubbleSortEx(vArr2);//330s 级别
	mergeSort<vector<int>, int>(vArr2, 0, vArr2.size() - 1);//1s 级别
	mergeSort<vector<int>, int>(vArr2);//0.5s 级别
	quickSort(vArr2, 0, vArr2.size() - 1);//0.15s 级别
	quickSortEX(vArr2, 0, vArr2.size() - 1);//0.1s 级别
	quickSortNR(vArr2, 0, vArr2.size() - 1);//0.3s 级别
	selectSort(vArr2);//150s 级别
	insertSort(vArr2);//122s 级别
	binaryInsertSort(vArr2);//80s 级别
	heapSort(vArr2);//0.15s 级别
	countSort<vector<int>, int>(vArr2);//17s 级别，很稳定，数据量为 1000000 时，依旧为 17s 左右
	//经实测本例中的 countSort 在调试状态下需要很长时间原因是 try catch 的 C++ 错误处理占用了大量时间
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