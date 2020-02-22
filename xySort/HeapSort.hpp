#ifndef XY_HEAP_SORT
#define XY_HEAP_SORT

//Ϊ�˱���Ƶ�����ú������˴������� sinkDown д�ɺ꺯������ʽ
//�󶥶���ҪСԪ���³�
#define sinkDown(datas, Subscript, maxSubscript)					\
		int sinkDownParent = Subscript;								\
		int sinkDownChild = 2 * sinkDownParent + 1;					\
		auto sinkTempData = datas[sinkDownParent];/*ʹ����ʱ��������Ҫ�³���Ԫ��*/	\
		/*��ʼ�³�*/												\
		while(sinkDownChild <= maxSubscript)						\
		{															\
			/*������ӽڵ�����ӽڵ�С����λ�����ӽڵ�*/			\
			if(sinkDownChild+1 <= maxSubscript && datas[sinkDownChild + 1] > datas[sinkDownChild])	\
			{														\
				++sinkDownChild;									\
			}														\
			/*	������ڵ� >= �ӽڵ㣬���³�������
				�³������У�Ϊ�˽�ʡ��ֵ������ʱ�䣬�ȼٶ�tempData����ڸ��ڵ㴦��
				�����������ʵ�ʵĸ�ֵ��ֱ���³��������ٽ��и�ֵ
				�����������³�;�У���tempData��ֵ�����ڵ㡣
				Ȼ��ʹ�ø��ڵ���ӽڵ���бȽϣ��Ƚ�����������ڵ���Ҫ�ٴ��³���
				��ô��ʱ�ĸ�ֵ��û������ģ�������ʵ�ʵĸ�ֵ���������³��������ٽ���
			*/														\
			if (sinkTempData >= datas[sinkDownChild])				\
			{														\
				break;												\
			}														\
			/*���ڵ�����³�*/										\
			datas[sinkDownParent] = datas[sinkDownChild];			\
			sinkDownParent = sinkDownChild;							\
			sinkDownChild = 2 * sinkDownParent + 1;					\
		}															\
		datas[sinkDownParent] = sinkTempData


template<class datasType>
void heapSort(datasType& datas)
{
	//��С����������Ҫ�����󶥶�
	//���������ѱ�Ϊ�������ѣ���Ҫִ���³�����
	//���������ѵ�ÿһ����Ҷ�ӽڵ������³�����������,�Ӻ���ǰ��
	auto tempData = datas[0];
	int maxSubscript = datas.size() - 1;

	for (int nonLeafNode = (maxSubscript - 1) / 2; nonLeafNode >= 0; --nonLeafNode)
	{
		sinkDown(datas, nonLeafNode, maxSubscript);
	}
	//��ʼ���ж�����
	//����ȡ���Ѷ�Ԫ�ط������������棬Ȼ��������Ԫ�ش���ڶѶ�
	//���ŶԶѶ�Ԫ��ִ���³����ԣ�ֱ����������³���
	for (int curMaxSubscript = maxSubscript; curMaxSubscript >= 1; --curMaxSubscript)//ȡ������ѽ�ʣһ��Ԫ��ʱ���Ѿ��ź����ˣ���� i == 0 ����Ҫ
	{
		tempData = datas[0];
		datas[0] = datas[curMaxSubscript];
		datas[curMaxSubscript] = tempData;
		//�³�����
		sinkDown(datas, 0, (curMaxSubscript - 1));
	}
}
#endif	//!XY_HEAP_SORT