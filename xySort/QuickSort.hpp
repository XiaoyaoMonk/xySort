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

	//���ּ��������ÿ�ηָ�ʱ������һ�ߵ�Ԫ������Ϊ0
	//Ϊ�˾����ų����ּ������
	//����λ�� left �� right ֮����������������Ϊ����Ԫ�ص��±�
	//Ȼ������ datas[left]����
	srand((int)time(0));
	int parten = left + rand() % (right - left + 1);
	tempData = datas[left];
	datas[left] = datas[parten];
	datas[parten] = tempData;
	
	//iLeft �� iRight���������Һʹ��ҵ�����б���
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
	//ѭ���˳�������
	//1��û�з����������˳���
	//		��ʱ��� iLeft == right + 1����˵������Ԫ�ؾ� <= datas[left]
	//			��Ҫ�� datas[left]�������ұߣ�right(��ʱiRight == right����λ���ϣ�
	//				exchange(datas[left], datas[iRight])
	//		��ʱ��� iRight == left����˵������Ԫ�ؾ� >= datas[left]
	//			����Ҫ�ƶ����ݣ�����exchange(datas[left], datas[iRight])��Ȼû����
	//2�������˽������˳���
	//		���˳�ǰһ��ѭ���У�һ�����������ݽ�������ʱ�ڽ������һ��ѭ���У������ڲ� while ��������������
	//	��ע�⣬�������һ��ѭ������ˣ�һ������� iLeft >= iRight �������
	//	������ iLeft �����Ƶ����� iLeft >= iRight������ iRight �����Ƶ����� iLeft >= iRight
	//	�����������Ĺ�ϵ��datas[iRight] >= datas[left]��
	//	��� exchange(datas[left], datas[iRight]) ��OK�ġ�
	tempData = datas[left];
	datas[left] = datas[iRight];
	datas[iRight] = tempData;//iRight��λ�����ź���

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

	//���ּ��������ÿ�ηָ�ʱ������һ�ߵ�Ԫ������Ϊ0
	//Ϊ�˾����ų����ּ������
	//����λ�� left �� right ֮����������������Ϊ����Ԫ�ص��±�
	//Ȼ������ datas[left]����
	srand((int)time(0));
	int parten = left + rand() % (right - left + 1);
	auto tempData = datas[left];
	datas[left] = datas[parten];
	datas[parten] = tempData;

	int iLeft = left;
	int iRight = right;

	//�Ż��㷨
	//��ʹ�� tempData ���� datas[left]����left��λ�����
	//Step1����������ʼ���������� < tempData ��Ԫ�أ������Ƶ���ߡ���ֵ�� iLeft����ʼֵΪleft����
	//Step2���������ҿ�ʼ���������� > tempData ��Ԫ�أ������Ƶ��ұߡ���ֵ�� iRight����ʶֵΪ right����
	//		Step1�еĶ�����Ȼ�Ὣ iRight ��λ�����ڳ�����Step2 �еĶ�����Ȼ�Ὣ iLeft ��λ���ڳ���
	//�ظ�Step1 �� Step2��ֱ�� iLeft == iRight

	//���������iRight == right == iLeft ���� iLeft == left == iRight
	//��ʱ��	tempData��������С�����丳ֵ�� iLeft��OK
	tempData = datas[left];
	while (iLeft < iRight)
	{
		while (iRight > iLeft&& datas[iRight] >= tempData)
		{
			--iRight;
		}
		datas[iLeft] = datas[iRight];
		//1���� iRight > iLeft,�˲����ᵼ��iLeft�ĵ�һ��ѭ����iLeft+1
		//2.2.2��iRight > iLeft��תע�͡�1����iRight == iLeft��������һ��ѭ�������iLeft ��λ�ñ��ڿգ�
		//���ڵ�Ԫ�ر���������һ��ѭ������ʱ��iRight�У��˸�ֵ���û�����壬������һ����ֵ���Ҳû������
		//�˳�ѭ���󣬽��ʼ��datas[left](tempData)������ datas[iLeft]��������λ���Ѿ����ź���

		while (iLeft < iRight && datas[iLeft] <= tempData)
		{
			++iLeft;
		}
		datas[iRight] = datas[iLeft];
		//2.1����ʱ���iLeft == iRight��������û���κ�����
		//2.1.1����ΪiLeft(==iRight)��ֵ�Ѿ������� "iLeft-1"�д�ʱ�˳�ѭ����datas[iLeft]λ�ñ��ڳ����ˣ�����ߵ�Ԫ��ȫ�� <=tempData���ұߵ�Ԫ�ض� >=tempData
		//2.1.2��������ó�����datas[left](tempData)�����ڴ�λ�ã�������λ���Ѿ��ź���
		//2.2.1����ʱ��� iLeft > iRight����ض�������һ����ѭ��ʱ iRight -1
	}
	datas[iLeft] = tempData;
	quickSortEX(datas, left, iLeft - 1);
	quickSortEX(datas, iLeft + 1, right);
}

//quickSortNR��quickSortN0-Recursion
//��������ķǵݹ���ʽ����ȡ���е���ʽ
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

	//�Ե�ǰҪ������Ԫ�ص� left �� right ���촴��pair����Ȼ��ѹ���
	//pair�� first Ԫ��Ϊ ��ǰѭ���ķ�Χ����߽磬second Ԫ��Ϊ�ұ߽�
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

		//��ȡ������߽���ұ߽�֮���Ԫ�ؽ��п���
		//��start �� end �������ұ߽�
		start = tempPair.first;
		end = tempPair.second;

		//�����������һ���������ڱ�ʾ����Ԫ�ص��±꣬Ȼ������start��λ
		parten = start + rand() % (end - start + 1);
		tempData = datas[start];
		datas[start] = datas[parten];
		datas[parten] = tempData;

		//��ʼ����
		//ʹ����ʱ�������� datas[start];
		tempData = datas[start];
		//��ѭ����������Ϊ start �� end
		iLeft = start;
		iRight = end;
		//��ʼ����Ԫ�ص�ѭ��
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
		datas[iLeft] = tempData;//iLeft ��λ�����ź���

		//����Ϊ iLeft ������������µ�Ԫ�ؼ��ϵ����ұ߽���� pair<int, int>���͵Ķ��󣬲������
		tempPair = { start, iLeft - 1 };
		quickSortQueue.push(tempPair);
		tempPair = { iLeft + 1,end };
		quickSortQueue.push(tempPair);
	}
}
#endif	//!XY_QUICK_SORT