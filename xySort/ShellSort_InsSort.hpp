#ifndef XY_SHELL_SORT
#define	XY_SHELL_SORT

//使用此函数时第一个参数必须是支持随机迭代器，并且其迭代器必须支持“+”操作符重载
//The first parameter to use this function must be support for random iterators, and its iterator must support "+" operator overloading

//本模板中使用的增量序列是 Hibbard 提出的 2^k - 1
//The incremental sequence used in this template is 2^k - 1 proposed by Hibbard

//insertMem 函数：
//在数据量超大的情况下，函数的出入栈将占用很多资源
//因此此处将其一个宏函数 insertMem
//insertMem function
//In the case of a large amount of data, the pushing and popping of functions will occupy a lot of resources
//So here is one of its macro functions, insertMem
#define insertMem(datas, Step, memCur)				\
	auto	temp	= datas[memCur];				\
	int		comCur	= memCur - Step;				\
	for (	comCur;									\
			comCur >= 0 && temp < datas[comCur];	\
			comCur -= Step)							\
		datas[comCur + Step] = datas[comCur];		\
		datas[comCur + Step] = temp
		
template <class datasType>
void shellSort(datasType& datas)
{
	size_t datasSize= datas.size();
	if (datasSize == 0 || datasSize == 1)
		return;
	
	//一般情况下，我们保证最大增量时，每个分组有两个元素，此处先确定最大增量
	//因为最大增量 Step_max > datas.size()/2 时，意义不大。
	//另外，采取 Hibbard 提出的 2^k - 1 增量时，增量缩减公式为：Step=(Step+1)/2-1 
	//不同于 Step = Step / 2 总能有Step = 1 的时候，但是 Step=(Step+1)/2-1 没有。
	//执行前 Step = 2 时，Step=(Step+1)/2-1 的结果为 0 ，直接结束了循环
	//此时数据有可能还没有排好序，所以必须使用公式先确定好最大增量，然后将该增量带入循环。
	//In general, when we guarantee the maximum increment, each group has two elements. Here we determine the maximum increment first.
	//Because the maximum increment 'Step_max> datas.size () / 2' is not significant.
	//Unlike 'Step = Step / 2' there can always be 'Step = 1', but 'Step = (Step + 1) / 2-1' does not.
	//When 'Step = 2' before execution, the result of 'Step = (Step + 1) / 2-1' is 0, which directly ends the loop.
	//At this time, the data may not be sorted yet, so you must first determine the maximum increment using a formula, and then bring the increment into the loop.
	int Step = 1;
	while ((Step + 1) * 2 - 1 < datasSize)
	{
		Step = (Step + 1) * 2 - 1;
	}

	//开始增量缩减的循环
	//Start the cycle of incremental reduction
	for (Step; Step > 0; Step = (Step + 1) / 2 - 1)
	{
		//遍历分组，对每个分组进行排序
		//此处采取的方法是，将 datas[Step] 到最后一个元素进行遍历
		//对于每个元素在其所在分组内进行性排序
		//Iterate through the groups and sort each group
		//The approach taken here is to iterate through datas [Step] to the last element
		//Sort each element sexually within its group

		//为了便于理解，如果对于 for (int memCur = Step; memCur < datasSize; ++memCur) 这句话比较疑惑，请详细阅读下面的注释
		//希尔排序中对于每一个分组内的排序使用的都是插入排序方法
		//插入排序的操作元素是从 编号为 1 的元素开始的
		//而从 Step 开始，其后的每一个元素在其分组内的编号都 >=1。
		//For the sake of understanding, if you are confused about the sentence ------
		//"for (int memCur = Step; memCur <datasSize; ++ memCur)", please read the comments below
		//In Shell sort, the sorting method in each group uses the insert sort method.
		//The elements of the insert sort operation start at element number 1.
		//Starting from Step, each element after it is numbered in its group '> = 1'
		for (int memCur = Step; memCur < datasSize; memCur++)
		{
			//插入函数，用于将 datas[memCur] 插入到所在分组的正确位置
			//Insert function to insert 'datas[memCur]' into the correct position of the group
			insertMem(datas, Step, memCur);
		}
	}
}

template<class datasType>
void insertSort(datasType& datas)
{
	auto tempData = datas[0];
	int datasSize = datas.size();
	int i = 0;
	int j = 0;

	//外层循环：遍历 datas[1] ～ datas[datas.size() - 1]
	//例如:	第一次操作，将 datas[1] 取出，然后用它和 datas[0] 比较并完成插入动作
	//		第二次操作，将 datas[2] 取出，然后用它和 datas[0]、datas[1]比较，并完成插入动作
	for (i = 1; i < datasSize; ++i)
	{
		//使用临时变量保存 datas[i]
		tempData = datas[i];

		//使用 tempData 和 datas[0]～datas[i-1]比较（从右至左）
		//如果 tempData < datas[j]时，datas[j+1] = datas[j];元素向右移动一个位置
		for (j = i-1; j >= 0 && tempData < datas[j]; --j)
		{
			datas[j + 1] = datas[j];
		}
		datas[j + 1] = tempData;
	}
}

//二分插入排序
template<class datasType>
void binaryInsertSort(datasType& datas)
{
	auto tempData = datas[0];
	//保存元素集合的数量
	size_t datasSize = datas.size();
	
	size_t i = 0;
	size_t j = 0;
	size_t left = 0;
	size_t right = 0;
	//与直接插入排序有点不同，前者可以一边比较一边移动元素
	//比较一次，移动一次元素，直到找到datas[i]的正确位置再将datas[i] 放置到该位置。
	//也可以先查找，再一次性完成元素的移动和插入。
	//但是二分插入排序的做法的优化点在于直接和前面已排好序的元素的中值进行比较，一次排除一半的元素
	//因此二分插入排序必须先查找再进行元素的移动和插入
	
	//外层循环：当前需要进行插入的元素在插入前的位置 i
	for (i = 1; i < datasSize; ++i)
	{
		//先用临时变量保存当前待插入的元素 datas[i]
		tempData = datas[i];

		//查找循环
		left = 0;
		//为了考虑当前最特殊的情况，即 tempData 应当插在 i 的位置上
		//即此次插入动作没有发生元素的移动时，应当将 right 初始值设为 i
		right = i;
		while (left != right)
		{
			//tempData应该落在右半区间，则提升下限
			//假如 tempData = datas[(left + right) / 2])
			//tempData 的插入位置一定在 (left+right)/2 的后面，因此：
			if (tempData >= datas[(left + right) / 2])
				left = (left + right) / 2 + 1;
			//tempData应该落在左半区间，则降低上限
			//当 tempData < datas[(left + right) / 2]时
			//tempData 的插入位置依然有可能是 (left+right)/2（不可能是 (left+right)/2 的右边）
			//因此，右边界设为（left + right) / 2;
			else
				right = (left + right)/ 2;
		}//当 left == right 时退出循环。
		j = left;
		//插入循环
		//将 datas[j]～datas[i - 1] 的元素整体右移
		size_t cur = i;
		for (cur; cur > j; --cur)
		{
			datas[cur] = datas[cur - 1];
		}
		datas[j] = tempData;
	}
}
#endif	//!XY_SHELL_SORT