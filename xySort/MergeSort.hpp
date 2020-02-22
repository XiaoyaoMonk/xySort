#ifndef XY_MERGE_SORT
#define XY_MERGE_SORT

#include <vector>

//��дһ���ݹ���õĹ鲢�����㷨
//First write a merge sort algorithm called recursively
template<class datasType, class dataType>
void mergeSort(datasType& datas, size_t left, size_t right)
{
	if (left >= right)
		return;

	size_t mid = (left + right) / 2;
	mergeSort<datasType, dataType>(datas, left, mid);
	mergeSort<datasType, dataType>(datas, mid + 1, right);

	//����һ���µ����ݼ��� tempDatas
	//Define a new data collection tempDatas
	vector<dataType> tempDatas;
	
	//����ǰ������Ԫ�ؿ���������µļ�����
	//�˹����лὫ�����ź���
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

	//���µ����ݼ������¸�ֵ�� datas
	//Reassign the new data set to datas
	for (int i = 0; i <= right - left; ++i)
	{
		datas[left + i] = tempDatas[i];
	}
}

//��������дһ���ǵݹ�İ汾
//Next write a non-recursive version
template<class datasType, class dataType>
void mergeSort(datasType& datas)
{
	size_t datasSize = datas.size();
	vector<dataType> tempDatas;
	size_t left = 0, right = 0, mid = 0;
	size_t tempLeft = 0, tempRight = 0;
	
	//���ѭ����i �ֱ�Ϊ 1,2,4,8 ...��
	for (size_t mergeSize = 1; mergeSize < (datasSize + 1); mergeSize += mergeSize)
	{

		//�ڲ�ѭ��������С���飬��ЩС����ֱ���
		//[0, 2 * mergeSize)��[2 * mergeSize, 4 * mergeSize)��[4 * mergeSize, 6 * mergeSize) ...
		for (left = 0;	left < datasSize; left += 2*mergeSize)
		{
			mid		= left + mergeSize - 1;
			right	= left + 2 * mergeSize - 1;
			//�������ʱ��Ԫ�ؼ��ϣ������������ڷֱ��ʾ���ҷ�����ѭ���ı��� tempLeft �� tempRight
			tempDatas.clear();
			tempLeft	= left;
			tempRight	= mid + 1;
			//�����ҷ��������ݿ�������ʱ�����ݼ��ϣ��˹��̻��������
			//��Ϊѭ�����������У�left < datasSize�����������������Զ С��datasSize���˴��ɲ����ж�
			//�ҷ��������������ڻ��ߵ��� datasSize����ֻ��Ҫֱ�ӽ�����������ݿ�������ʱԪ�ؼ��ϼ���
			if (mid + 1 >= datasSize)
			{
				while (tempLeft < datasSize) tempDatas.push_back(datas[tempLeft++]);
			}
			else
			{
				//���ڴ��� tempLeft <= mid < mid+1 <= tempRight�Ĺ�ϵ
				//�� mid + 1 >= datasSize ��������ѱ��ų�����˴˴�ֻ���ж� tempRight �� datasSize�Ĺ�ϵ 
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
				//�ս�ѭ�������������ҷ�����һ���Ѿ��ﵽ�����ұ߽�
				//��ʱ��һ��ѭ��ֱ�ӽ�û�дﵽ�߽�ķ�����������ο����� tempDatas �С�
				while (tempLeft <= mid)
				{
					tempDatas.push_back(datas[tempLeft++]);
				}
				while (tempRight <= right && tempRight < datasSize)
				{
					tempDatas.push_back(datas[tempRight++]);
				}
			}
			//��������ʱ���ݼ����е�Ԫ�����ο�����datas��
			for (int i = 0; i < tempDatas.size(); ++i)
				datas[left + i] = tempDatas[i];
		}
	}
}

#endif // !XY_MERGE_SORT
