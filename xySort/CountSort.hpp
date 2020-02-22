#ifndef XY_COUNT_SORT
#define XY_COUNT_SORT

#include <unordered_map>
#include <vector>
#include <exception>

#include "HeapSort.hpp"

template <class datasType, class dataType>
void countSort(datasType& datas)
{
	//大致思路：
	//计数排序不是很好写，针对 int、char、long 之类的整数比较好写
	//但是针对自定义的数据类型（其排序是通过自定义的比较规则来进行大小比较的排序），则不是很好写
	//为了能够达到泛型的目的，此处需要使用 unorder_map<dataType, int> datasMap 保存每一个独特元素的数量
	/************
		使用 unorder_map 需要用到 hash_value() 函数，大多数类型都有自带的 hash_value() 函数
		因此自定义数据类型必须重载 hash_value() 函数
		另外，涉及到比较操作，所以还需要重载下列操作符函数
		operator< 、 operator<= 、 operator> 、operator>= 、 operator==
	*************/
	//以需要排序的 datas 中的元素作为键值，该元素出现的次数作为 value 存入 datasMap
	//将 datas 中的所有 独特元素 存储到 dataVector 中
	//将 dataVector 进行排序，然后再遍历 dataVector
	//通过 dataVector 的元素作为键值，查询 datasMap 中该键值对应到 “value”，在源来的元素集合中重新进行复制

	//计数排序需要用到 unordered_map 类型的数据结构
	unordered_map<dataType, size_t> datasMap = { {datas[0], 1} };
	vector<dataType> dataVector(1, datas[0]);

	size_t datasSize = datas.size();
	for (size_t i = 1; i < datasSize; ++i)
	{
		//尝试将键值 datas[i] datasMap 中对应的 value + 1
		try
		{
			datasMap.at(datas[i]) += 1;
		}
		//如果键值 "datas[i]" 在 datasMap 中尚未存在，try 中的语句块将会抛出 out_of_range 类型的异常
		//捕获这个异常，将新的独特元素作为键值，其 value 被设为1，然后插入 datasMap
		//同时，执行 dataVector.push_back(datas[i]); 操作，等 datas 遍历完之后，其所有的独特元素均已存储在 dataVector 中
		catch (std::out_of_range& exc)
		{
			datasMap.insert({ datas[i], 1 });
			dataVector.push_back(datas[i]);
		}
	}
	
	//将 dataVector 排序，此处需要用到其它排序方法，此案例中选用的是 HeapSort 堆排序
	heapSort(dataVector);
	//然后遍历 dataVector，根据 其中的元素在 源数据集合 datas 中出现的次数(键 dataVector[i] 在 datasMap 中的 value)依次对 源数据集合 datas 进行填充
	//例如 dataVector[0] 在 datasMap 中的值为 2，说明 dataVector[0] 应该在 datas 中填充两次
	size_t datasCur = 0;
	for (size_t dvCur = 0; dvCur < dataVector.size(); ++dvCur)
	{
		for (size_t dmCur = 0; dmCur < datasMap.at(dataVector[dvCur]); ++dmCur)
		{
			datas[datasCur++] = dataVector[dvCur];
		}
	}
}
#endif	//!XY_COUNT_SORT
