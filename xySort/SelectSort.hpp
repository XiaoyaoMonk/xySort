/*
 * @Author       : yaowenzhou
 * @Date         : 2021-01-17 14:31:10
 * @LastEditors  : yaowenzhou
 * @LastEditTime : 2021-01-17 14:34:36
 * @version      : 
 * @Description  : 
 */
#ifndef XY_SELECT_SORT
#define XY_SELECT_SORT
template<class datasType>
void selectSort(datasType& datas)
{
	size_t datasSize	= datas.size();
	size_t min		= 0;
	auto tempData = datas[0];
	//外层循环，每次循环都将当前操作范围内的最小元素移动到操作范围的最前面的位置
	//例如：第一次操作，将 datas[min] 和 datas[0] 交换
	//		第二次操作，将剩余元素的 datas[min] 和 datas[1] 交换
	//		......
	//当 i = datasSize-1 时，只剩datas的最后一个元素 datas[datasSize-1] 时
	//其它所有元素均已排好序，所以此时 datas[datasSize-1] 就是最大值
	//因此循环的退出条件是 i < datasSize-1;  i = datasSize-1时，循环不必进行了
	for (size_t i = 0; i < datasSize-1; ++i)
	{
		min = i;
		//内层循环
		//假定当前操作范围的第一个元素 datas[i] 假定为最小元素
		//记 size_t min = i;
		//将 datas[min] 与 datas[i+1, datasSize-1] 中的元素进行比较，
		//如果遇到 datas[j] < datas[min]，则 min = j，然后继续比较，
		//直到此次循环完成，即可得到当前范围内的最小元素 datas[min]
		//然后将 datas[i] 与 datas[min]交换。
		for (size_t j = i+1; j < datasSize; ++j)
		{
			if (datas[j] < datas[min])
			{
				min = j;
			}
		}
		tempData = datas[i];
		datas[i] = datas[min];
		datas[min] = tempData;
	}
}
#endif	//!XY_SELECT_SORT