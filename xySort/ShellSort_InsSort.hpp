#ifndef XY_SHELL_SORT
#define	XY_SHELL_SORT

//ʹ�ô˺���ʱ��һ������������֧����������������������������֧�֡�+������������
//The first parameter to use this function must be support for random iterators, and its iterator must support "+" operator overloading

//��ģ����ʹ�õ����������� Hibbard ����� 2^k - 1
//The incremental sequence used in this template is 2^k - 1 proposed by Hibbard

//insertMem ������
//�����������������£������ĳ���ջ��ռ�úܶ���Դ
//��˴˴�����һ���꺯�� insertMem
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
	
	//һ������£����Ǳ�֤�������ʱ��ÿ������������Ԫ�أ��˴���ȷ���������
	//��Ϊ������� Step_max > datas.size()/2 ʱ�����岻��
	//���⣬��ȡ Hibbard ����� 2^k - 1 ����ʱ������������ʽΪ��Step=(Step+1)/2-1 
	//��ͬ�� Step = Step / 2 ������Step = 1 ��ʱ�򣬵��� Step=(Step+1)/2-1 û�С�
	//ִ��ǰ Step = 2 ʱ��Step=(Step+1)/2-1 �Ľ��Ϊ 0 ��ֱ�ӽ�����ѭ��
	//��ʱ�����п��ܻ�û���ź������Ա���ʹ�ù�ʽ��ȷ�������������Ȼ�󽫸���������ѭ����
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

	//��ʼ����������ѭ��
	//Start the cycle of incremental reduction
	for (Step; Step > 0; Step = (Step + 1) / 2 - 1)
	{
		//�������飬��ÿ�������������
		//�˴���ȡ�ķ����ǣ��� datas[Step] �����һ��Ԫ�ؽ��б���
		//����ÿ��Ԫ���������ڷ����ڽ���������
		//Iterate through the groups and sort each group
		//The approach taken here is to iterate through datas [Step] to the last element
		//Sort each element sexually within its group

		//Ϊ�˱�����⣬������� for (int memCur = Step; memCur < datasSize; ++memCur) ��仰�Ƚ��ɻ�����ϸ�Ķ������ע��
		//ϣ�������ж���ÿһ�������ڵ�����ʹ�õĶ��ǲ������򷽷�
		//��������Ĳ���Ԫ���Ǵ� ���Ϊ 1 ��Ԫ�ؿ�ʼ��
		//���� Step ��ʼ������ÿһ��Ԫ����������ڵı�Ŷ� >=1��
		//For the sake of understanding, if you are confused about the sentence ------
		//"for (int memCur = Step; memCur <datasSize; ++ memCur)", please read the comments below
		//In Shell sort, the sorting method in each group uses the insert sort method.
		//The elements of the insert sort operation start at element number 1.
		//Starting from Step, each element after it is numbered in its group '> = 1'
		for (int memCur = Step; memCur < datasSize; memCur++)
		{
			//���뺯�������ڽ� datas[memCur] ���뵽���ڷ������ȷλ��
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

	//���ѭ�������� datas[1] �� datas[datas.size() - 1]
	//����:	��һ�β������� datas[1] ȡ����Ȼ�������� datas[0] �Ƚϲ���ɲ��붯��
	//		�ڶ��β������� datas[2] ȡ����Ȼ�������� datas[0]��datas[1]�Ƚϣ�����ɲ��붯��
	for (i = 1; i < datasSize; ++i)
	{
		//ʹ����ʱ�������� datas[i]
		tempData = datas[i];

		//ʹ�� tempData �� datas[0]��datas[i-1]�Ƚϣ���������
		//��� tempData < datas[j]ʱ��datas[j+1] = datas[j];Ԫ�������ƶ�һ��λ��
		for (j = i-1; j >= 0 && tempData < datas[j]; --j)
		{
			datas[j + 1] = datas[j];
		}
		datas[j + 1] = tempData;
	}
}

//���ֲ�������
template<class datasType>
void binaryInsertSort(datasType& datas)
{
	auto tempData = datas[0];
	//����Ԫ�ؼ��ϵ�����
	size_t datasSize = datas.size();
	
	size_t i = 0;
	size_t j = 0;
	size_t left = 0;
	size_t right = 0;
	//��ֱ�Ӳ��������е㲻ͬ��ǰ�߿���һ�߱Ƚ�һ���ƶ�Ԫ��
	//�Ƚ�һ�Σ��ƶ�һ��Ԫ�أ�ֱ���ҵ�datas[i]����ȷλ���ٽ�datas[i] ���õ���λ�á�
	//Ҳ�����Ȳ��ң���һ�������Ԫ�ص��ƶ��Ͳ��롣
	//���Ƕ��ֲ���������������Ż�������ֱ�Ӻ�ǰ�����ź����Ԫ�ص���ֵ���бȽϣ�һ���ų�һ���Ԫ��
	//��˶��ֲ�����������Ȳ����ٽ���Ԫ�ص��ƶ��Ͳ���
	
	//���ѭ������ǰ��Ҫ���в����Ԫ���ڲ���ǰ��λ�� i
	for (i = 1; i < datasSize; ++i)
	{
		//������ʱ�������浱ǰ�������Ԫ�� datas[i]
		tempData = datas[i];

		//����ѭ��
		left = 0;
		//Ϊ�˿��ǵ�ǰ�������������� tempData Ӧ������ i ��λ����
		//���˴β��붯��û�з���Ԫ�ص��ƶ�ʱ��Ӧ���� right ��ʼֵ��Ϊ i
		right = i;
		while (left != right)
		{
			//tempDataӦ�������Ұ����䣬����������
			//���� tempData = datas[(left + right) / 2])
			//tempData �Ĳ���λ��һ���� (left+right)/2 �ĺ��棬��ˣ�
			if (tempData >= datas[(left + right) / 2])
				left = (left + right) / 2 + 1;
			//tempDataӦ������������䣬�򽵵�����
			//�� tempData < datas[(left + right) / 2]ʱ
			//tempData �Ĳ���λ����Ȼ�п����� (left+right)/2���������� (left+right)/2 ���ұߣ�
			//��ˣ��ұ߽���Ϊ��left + right) / 2;
			else
				right = (left + right)/ 2;
		}//�� left == right ʱ�˳�ѭ����
		j = left;
		//����ѭ��
		//�� datas[j]��datas[i - 1] ��Ԫ����������
		size_t cur = i;
		for (cur; cur > j; --cur)
		{
			datas[cur] = datas[cur - 1];
		}
		datas[j] = tempData;
	}
}
#endif	//!XY_SHELL_SORT