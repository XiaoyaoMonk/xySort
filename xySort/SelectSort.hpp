#ifndef XY_SELECT_SORT
#define XY_SELECT_SORT
template<class datasType>
void selectSort(datasType& datas)
{
	size_t datasSize	= datas.size();
	size_t min		= 0;
	auto tempData = datas[0];
	//���ѭ����ÿ��ѭ��������ǰ������Χ�ڵ���СԪ���ƶ���������Χ����ǰ���λ��
	//���磺��һ�β������� datas[min] �� datas[0] ����
	//		�ڶ��β�������ʣ��Ԫ�ص� datas[min] �� datas[1] ����
	//		......
	//�� i = datasSize-1 ʱ��ֻʣdatas�����һ��Ԫ�� datas[datasSize-1] ʱ
	//��������Ԫ�ؾ����ź������Դ�ʱ datas[datasSize-1] �������ֵ
	//���ѭ�����˳������� i < datasSize-1;  i = datasSize-1ʱ��ѭ�����ؽ�����
	for (size_t i = 0; i < datasSize-1; ++i)
	{
		min = i;
		//�ڲ�ѭ��
		//�ٶ���ǰ������Χ�ĵ�һ��Ԫ�� datas[i] �ٶ�Ϊ��СԪ��
		//�� size_t min = i;
		//�� datas[min] �� datas[i+1, datasSize-1] �е�Ԫ�ؽ��бȽϣ�
		//������� datas[j] < datas[min]���� min = j��Ȼ������Ƚϣ�
		//ֱ���˴�ѭ����ɣ����ɵõ���ǰ��Χ�ڵ���СԪ�� datas[min]
		//Ȼ�� datas[i] �� datas[min]������
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