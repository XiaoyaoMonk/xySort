#ifndef XY_QUICK_SORT
#define XY_QUICK_SORT

#include <ctime>
#include <cstdlib>
template<class datasType>
void quickSort(datasType& datas, int left, int right)
{

	if (left >= right)
	{
		return;
	}
	
	auto tempData = datas[0];

	//有种极端情况，每次分割时，都有一边的元素数量为0
	//为了尽量排除这种极端情况
	//产生位于 left 和 right 之间的随机数，用来作为中轴元素的下标
	//然后将其与 datas[left]互换
	srand((int)time(0));
	int parten = left + rand() % (right - left + 1);
	tempData = datas[left];
	datas[left] = datas[parten];
	datas[parten] = tempData;
	
	//iLeft 和 iRight用来从左到右和从右到左进行遍历
	int iLeft = left + 1;
	int iRight = right;
	int center = 0;
	while (true)
	{
		while (iLeft <= iRight && datas[iLeft] <= datas[left])
		{
			++iLeft;
		}

		while (iLeft <= iRight && datas[iRight] >= datas[left])
		{
			--iRight;
		}

		if (iLeft >= iRight)
		{
			break;
		}

		tempData = datas[iLeft];
		datas[iLeft] = datas[iRight];
		datas[iRight] = tempData;
	}
	//循环退出的条件
	//1、没有发生交换而退出：
	//		此时如果 iLeft == right + 1，则说明所有元素均 <= datas[left]
	//			需要将 datas[left]放在最右边（right(此时iRight == right）的位置上）
	//				exchange(datas[left], datas[iRight])
	//		此时如果 iRight == left，则说明所有元素均 >= datas[left]
	//			不需要移动数据，但是exchange(datas[left], datas[iRight])依然没问题
	//2、发生了交换而退出：
	//		在退出前一次循环中，一定发生了数据交换，此时在进行最后一次循环中，两个内部 while 的条件均成立，
	//	请注意，这是最后一次循环，因此，一定会出现 iLeft >= iRight 的情况。
	//	不管是 iLeft 的右移导致了 iLeft >= iRight，还是 iRight 的左移导致了 iLeft >= iRight
	//	都存在这样的关系：datas[iRight] >= datas[left]，
	//	因此 exchange(datas[left], datas[iRight]) 是OK的。
	tempData = datas[left];
	datas[left] = datas[iRight];
	datas[iRight] = tempData;//iRight的位置已排好序

	quickSort(datas, left, iRight - 1);
	quickSort(datas, iRight + 1, right);
}

template<class datasType>
void quickSortEX(datasType& datas, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	//有种极端情况，每次分割时，都有一边的元素数量为0
	//为了尽量排除这种极端情况
	//产生位于 left 和 right 之间的随机数，用来作为中轴元素的下标
	//然后将其与 datas[left]互换
	srand((int)time(0));
	int parten = left + rand() % (right - left + 1);
	auto tempData = datas[left];
	datas[left] = datas[parten];
	datas[parten] = tempData;

	int iLeft = left;
	int iRight = right;

	//优化算法
	//先使用 tempData 保存 datas[left]，将left的位置清空
	//Step1、从右向左开始遍历，遇到 < tempData 的元素，则将其移到左边【赋值给 iLeft（初始值为left）】
	//Step2、从左向右开始遍历，遇到 > tempData 的元素，则将其移到右边【赋值给 iRight（初识值为 right）】
	//		Step1中的动作必然会将 iRight 的位置上腾出来。Step2 中的动作必然会将 iLeft 的位置腾出来
	//重复Step1 和 Step2，直到 iLeft == iRight

	//特殊情况：iRight == right == iLeft 或者 iLeft == left == iRight
	//此时：	tempData最大或者最小，将其赋值给 iLeft，OK
	tempData = datas[left];
	while (iLeft < iRight)
	{
		while (iRight > iLeft&& datas[iRight] >= tempData)
		{
			--iRight;
		}
		datas[iLeft] = datas[iRight];
		//1、当 iRight > iLeft,此操作会导致iLeft的第一次循环中iLeft+1
		//2.2.2、iRight > iLeft则转注释“1”；iRight == iLeft，则在上一次循环的最后，iLeft 的位置被腾空，
		//其内的元素被保存在上一次循环结束时的iRight中，此赋值语句没有意义，并且下一条赋值语句也没有意义
		//退出循环后，将最开始的datas[left](tempData)保存在 datas[iLeft]，并且其位置已经被排好序

		while (iLeft < iRight && datas[iLeft] <= tempData)
		{
			++iLeft;
		}
		datas[iRight] = datas[iLeft];
		//2.1、此时如果iLeft == iRight，则此语句没有任何意义
		//2.1.1、因为iLeft(==iRight)的值已经保存在 "iLeft-1"中次时退出循环，datas[iLeft]位置被腾出来了，其左边的元素全部 <=tempData，右边的元素都 >=tempData
		//2.1.2、将最初拿出来的datas[left](tempData)保存在此位置，并且其位置已经排好序
		//2.2.1、此时如果 iLeft > iRight，则必定导致下一次外循环时 iRight -1
	}
	datas[iLeft] = tempData;
	quickSortEX(datas, left, iLeft - 1);
	quickSortEX(datas, iLeft + 1, right);
}

//quickSortNR：quickSortN0-Recursion
//快速排序的非递归形式，采取队列的形式
#include <utility>
#include <queue>
template<class datasType>
void quickSortNR(datasType& datas, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	srand((int)time(0));
	int parten = 0;
	auto tempData = datas[left];

	//以当前要操作的元素的 left 和 right 构造创建pair对象，然后压入队
	//pair的 first 元素为 当前循环的范围的左边界，second 元素为右边界
	queue<pair<int, int> > quickSortQueue;
	pair<int, int> tempPair(left, right);
	quickSortQueue.push(tempPair);

	int start = 0;
	int end = 0;
	int iLeft = 0, iRight = 0;

	while (!quickSortQueue.empty())
	{
		tempPair = quickSortQueue.front();
		quickSortQueue.pop();
		if (tempPair.first >= tempPair.second)
			continue;

		//对取出的左边界和右边界之间的元素进行快排
		//用start 和 end 保存左右边界
		start = tempPair.first;
		end = tempPair.second;

		//首先随机生成一个数，用于表示中轴元素的下标，然后将其与start换位
		parten = start + rand() % (end - start + 1);
		tempData = datas[start];
		datas[start] = datas[parten];
		datas[parten] = tempData;

		//开始快排
		//使用临时变量保存 datas[start];
		tempData = datas[start];
		//将循环变量重置为 start 和 end
		iLeft = start;
		iRight = end;
		//开始交换元素的循环
		while (iLeft < iRight)
		{
			while (iRight > iLeft && datas[iRight] >= tempData)
			{
				--iRight;
			}
			datas[iLeft] = datas[iRight];

			while (iLeft < iRight && datas[iLeft] <= tempData)
			{
				++iLeft;
			}
			datas[iRight] = datas[iLeft];
		}
		datas[iLeft] = tempData;//iLeft 的位置已排好序

		//将因为 iLeft 排序而产生的新的元素集合的左右边界组成 pair<int, int>类型的对象，并且入队
		tempPair = { start, iLeft - 1 };
		quickSortQueue.push(tempPair);
		tempPair = { iLeft + 1,end };
		quickSortQueue.push(tempPair);
	}
}
#endif	//!XY_QUICK_SORT