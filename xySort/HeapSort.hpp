#ifndef XY_HEAP_SORT
#define XY_HEAP_SORT

//为了避免频繁调用函数，此处将函数 sinkDown 写成宏函数的形式
//大顶堆需要小元素下沉
#define sinkDown(datas, Subscript, maxSubscript)					\
		int sinkDownParent = Subscript;								\
		int sinkDownChild = 2 * sinkDownParent + 1;					\
		auto sinkTempData = datas[sinkDownParent];/*使用临时变量保存要下沉的元素*/	\
		/*开始下沉*/												\
		while(sinkDownChild <= maxSubscript)						\
		{															\
			/*如果右子节点比左子节点小，则定位到右子节点*/			\
			if(sinkDownChild+1 <= maxSubscript && datas[sinkDownChild + 1] > datas[sinkDownChild])	\
			{														\
				++sinkDownChild;									\
			}														\
			/*	如果父节点 >= 子节点，则下沉结束。
				下沉过程中，为了节省赋值操作的时间，先假定tempData存放在父节点处，
				而不对其完成实际的赋值，直到下沉结束后再进行赋值
				可以想象，在下沉途中，将tempData赋值给父节点。
				然后使用父节点和子节点进行比较，比较完了如果父节点需要再次下沉。
				那么此时的赋值是没有意义的，因此这个实际的赋值操作留到下沉结束后再进行
			*/														\
			if (sinkTempData >= datas[sinkDownChild])				\
			{														\
				break;												\
			}														\
			/*父节点可以下沉*/										\
			datas[sinkDownParent] = datas[sinkDownChild];			\
			sinkDownParent = sinkDownChild;							\
			sinkDownChild = 2 * sinkDownParent + 1;					\
		}															\
		datas[sinkDownParent] = sinkTempData


template<class datasType>
void heapSort(datasType& datas)
{
	//由小到大排序需要构建大顶堆
	//由无序二叉堆变为有序二叉堆，需要执行下沉策略
	//将无序二叉堆的每一个非叶子节点依次下沉（从下往上,从后往前）
	auto tempData = datas[0];
	int maxSubscript = datas.size() - 1;

	for (int nonLeafNode = (maxSubscript - 1) / 2; nonLeafNode >= 0; --nonLeafNode)
	{
		sinkDown(datas, nonLeafNode, maxSubscript);
	}
	//开始进行堆排序
	//依次取出堆顶元素放在数组的最后面，然后将最后面的元素存放在堆顶
	//接着对堆顶元素执行下沉策略，直至二叉堆重新成立
	for (int curMaxSubscript = maxSubscript; curMaxSubscript >= 1; --curMaxSubscript)//取到二叉堆仅剩一个元素时，已经排好序了，因此 i == 0 不需要
	{
		tempData = datas[0];
		datas[0] = datas[curMaxSubscript];
		datas[curMaxSubscript] = tempData;
		//下沉调整
		sinkDown(datas, 0, (curMaxSubscript - 1));
	}
}
#endif	//!XY_HEAP_SORT