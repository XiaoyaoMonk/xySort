#ifndef XY_MERGE_SORT
#define XY_MERGE_SORT

#include <vector>

//先写一个递归调用的归并排序算法
//First write a merge sort algorithm called recursively
template<class datasType, class dataType>
void mergeSort(datasType& datas, size_t left, size_t right)
{
	if (left >= right)
		return;

	size_t mid = (left + right) / 2;
	mergeSort<datasType, dataType>(datas, left, mid);
	mergeSort<datasType, dataType>(datas, mid + 1, right);

	//定义一个新的数据集合 tempDatas
	//Define a new data collection tempDatas
	vector<dataType> tempDatas;
	
	//将当前操作的元素拷贝到这个新的集合中
	//此过程中会将它们排好序
	//Copy the elements of the current operation into this new collection
	//Datas will be sorted in the copy process.
	size_t iLeft	= left;
	size_t iRight	= mid + 1;
	while (iLeft <= mid && iRight <= right)
	{
		if (datas[iLeft] <= datas[iRight])
			tempDatas.push_back(datas[iLeft++]);
		else
			tempDatas.push_back(datas[iRight++]);
	}

	while(iLeft <= mid) tempDatas.push_back(datas[iLeft++]);
	while(iRight <= right) tempDatas.push_back(datas[iRight++]);

	//将新的数据集合重新赋值给 datas
	//Reassign the new data set to datas
	for (int i = 0; i <= right - left; ++i)
	{
		datas[left + i] = tempDatas[i];
	}
}

//接下来再写一个非递归的版本
//Next write a non-recursive version
template<class datasType, class dataType>
void mergeSort(datasType& datas)
{
	size_t datasSize = datas.size();
	vector<dataType> tempDatas;
	size_t left = 0, right = 0, mid = 0;
	size_t tempLeft = 0, tempRight = 0;
	
	//外层循环（i 分别为 1,2,4,8 ...）
	for (size_t mergeSize = 1; mergeSize < (datasSize + 1); mergeSize += mergeSize)
	{

		//内层循环，遍历小分组，这些小分组分别是
		//[0, 2 * mergeSize)、[2 * mergeSize, 4 * mergeSize)、[4 * mergeSize, 6 * mergeSize) ...
		for (left = 0;	left < datasSize; left += 2*mergeSize)
		{
			mid		= left + mergeSize - 1;
			right	= left + 2 * mergeSize - 1;
			//先清空临时的元素集合，并且设置用于分别表示左右分区中循环的变量 tempLeft 和 tempRight
			tempDatas.clear();
			tempLeft	= left;
			tempRight	= mid + 1;
			//将左右分区的数据拷贝到临时的数据集合，此过程会完成排序
			//因为循环控制条件中：left < datasSize，因此左分区的起点永远 小于datasSize，此处可不必判断
			//右分区的起点如果大于或者等于 datasSize，则只需要直接将左分区的内容拷贝至临时元素集合即可
			if (mid + 1 >= datasSize)
			{
				while (tempLeft < datasSize) tempDatas.push_back(datas[tempLeft++]);
			}
			else
			{
				//由于存在 tempLeft <= mid < mid+1 <= tempRight的关系
				//而 mid + 1 >= datasSize 的情况下已被排除，因此此处只需判断 tempRight 和 datasSize的关系 
				while (tempLeft <= mid && tempRight <= right && tempRight < datasSize)
				{
					if (datas[tempLeft] <= datas[tempRight])
					{
						tempDatas.push_back(datas[tempLeft++]);
					}
					else
					{
						tempDatas.push_back(datas[tempRight++]);
					}
				}
				//终结循环的条件是左右分区有一个已经达到了其右边界
				//此时用一个循环直接将没有达到边界的分组的数据依次拷贝到 tempDatas 中。
				while (tempLeft <= mid)
				{
					tempDatas.push_back(datas[tempLeft++]);
				}
				while (tempRight <= right && tempRight < datasSize)
				{
					tempDatas.push_back(datas[tempRight++]);
				}
			}
			//将所有临时数据集合中的元素依次拷贝到datas中
			for (int i = 0; i < tempDatas.size(); ++i)
				datas[left + i] = tempDatas[i];
		}
	}
}

#endif // !XY_MERGE_SORT
