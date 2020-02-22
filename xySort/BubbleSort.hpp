#ifndef XY_BUBBLE_SORT
#define	XY_BUBBLE_SORT
template<class datasType>
void bubbleSort(datasType& datas)
{
	auto tempData = datas[0];
	for (int i = datas.size() - 1; i >= 1; --i)
	{
		//�ڴ�ѭ�����Ƚ������������Ĵ�С����� datas[j] > datas[j + 1]���򽻻�����
		//ѭ��ִ����Ϻ�����Ԫ���Ѿ��ƶ�����ǰ���������ұߡ�
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


//����ʵ��ð��������Ż�����
template<class datasType>
void bubbleSortEx(datasType& datas)
{
	auto tempData = datas[0];
	for (int i = datas.size() - 1; i >= 1; --i)
	{
		bool hasExchanged = false;//�ȼ���˴���ѭ���Ĺ����в��ᷢ�����ݽ���
		for (int j = 0; j < i; ++j)
		{
			if (datas[j] > datas[j + 1])
			{
				tempData = datas[j];
				datas[j] = datas[j + 1];
				datas[j + 1] = tempData;
				//һ�����������ݽ������� hasExchanged ��Ϊ �档
				hasExchanged = true;
			}
		}
		//������� hasExchanged ��ֵΪ flase
		//��˵��������ѭ���Ĺ�����û�з������ݽ�������break��ֹѭ��
		if (hasExchanged == false)
			break;
	}
}
#endif	//	!XY_BUBBLE_SORT
