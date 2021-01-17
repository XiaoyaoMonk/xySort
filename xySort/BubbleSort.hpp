/*
 * @Author       : yaowenzhou
 * @Date         : 2021-01-17 14:31:10
 * @LastEditors  : yaowenzhou
 * @LastEditTime : 2021-01-17 14:32:17
 * @version      : 
 * @Description  : 
 */
#ifndef XY_BUBBLE_SORT
#define	XY_BUBBLE_SORT
template<class datasType>
void bubbleSort(datasType& datas)
{
	auto tempData = datas[0];
	for (int i = datas.size() - 1; i >= 1; --i)
	{
		//内存循环，比较相邻两个数的大小，如果 datas[j] > datas[j + 1]，则交换二者
		//循环执行完毕后，最大的元素已经移动到当前操作的最右边。
		for (int j = 0; j < i; ++j)
		{
			if (datas[j] > datas[j + 1])
			{
				tempData		= datas[j];
				datas[j]		= datas[j + 1];
				datas[j + 1]	= tempData;
			}
		}
	}
}


//下面实现冒泡排序的优化代码
template<class datasType>
void bubbleSortEx(datasType& datas)
{
	auto tempData = datas[0];
	for (int i = datas.size() - 1; i >= 1; --i)
	{
		bool hasExchanged = false;//先假设此次外循环的过程中不会发生数据交换
		for (int j = 0; j < i; ++j)
		{
			if (datas[j] > datas[j + 1])
			{
				tempData = datas[j];
				datas[j] = datas[j + 1];
				datas[j + 1] = tempData;
				//一旦发生了数据交换，则将 hasExchanged 设为 真。
				hasExchanged = true;
			}
		}
		//如果变量 hasExchanged 的值为 flase
		//这说明这次外层循环的过程中没有发生数据交换，则break终止循环
		if (hasExchanged == false)
			break;
	}
}
#endif	//	!XY_BUBBLE_SORT
