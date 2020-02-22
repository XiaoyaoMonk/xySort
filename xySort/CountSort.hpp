#ifndef XY_COUNT_SORT
#define XY_COUNT_SORT

#include <unordered_map>
#include <vector>
#include <exception>

#include "HeapSort.hpp"

template <class datasType, class dataType>
void countSort(datasType& datas)
{
	//����˼·��
	//���������Ǻܺ�д����� int��char��long ֮��������ȽϺ�д
	//��������Զ�����������ͣ���������ͨ���Զ���ıȽϹ��������д�С�Ƚϵ����򣩣����Ǻܺ�д
	//Ϊ���ܹ��ﵽ���͵�Ŀ�ģ��˴���Ҫʹ�� unorder_map<dataType, int> datasMap ����ÿһ������Ԫ�ص�����
	/************
		ʹ�� unorder_map ��Ҫ�õ� hash_value() ��������������Ͷ����Դ��� hash_value() ����
		����Զ����������ͱ������� hash_value() ����
		���⣬�漰���Ƚϲ��������Ի���Ҫ�������в���������
		operator< �� operator<= �� operator> ��operator>= �� operator==
	*************/
	//����Ҫ����� datas �е�Ԫ����Ϊ��ֵ����Ԫ�س��ֵĴ�����Ϊ value ���� datasMap
	//�� datas �е����� ����Ԫ�� �洢�� dataVector ��
	//�� dataVector ��������Ȼ���ٱ��� dataVector
	//ͨ�� dataVector ��Ԫ����Ϊ��ֵ����ѯ datasMap �иü�ֵ��Ӧ�� ��value������Դ����Ԫ�ؼ��������½��и���

	//����������Ҫ�õ� unordered_map ���͵����ݽṹ
	unordered_map<dataType, size_t> datasMap = { {datas[0], 1} };
	vector<dataType> dataVector(1, datas[0]);

	size_t datasSize = datas.size();
	for (size_t i = 1; i < datasSize; ++i)
	{
		//���Խ���ֵ datas[i] datasMap �ж�Ӧ�� value + 1
		try
		{
			datasMap.at(datas[i]) += 1;
		}
		//�����ֵ "datas[i]" �� datasMap ����δ���ڣ�try �е����齫���׳� out_of_range ���͵��쳣
		//��������쳣�����µĶ���Ԫ����Ϊ��ֵ���� value ����Ϊ1��Ȼ����� datasMap
		//ͬʱ��ִ�� dataVector.push_back(datas[i]); �������� datas ������֮�������еĶ���Ԫ�ؾ��Ѵ洢�� dataVector ��
		catch (std::out_of_range& exc)
		{
			datasMap.insert({ datas[i], 1 });
			dataVector.push_back(datas[i]);
		}
	}
	
	//�� dataVector ���򣬴˴���Ҫ�õ��������򷽷����˰�����ѡ�õ��� HeapSort ������
	heapSort(dataVector);
	//Ȼ����� dataVector������ ���е�Ԫ���� Դ���ݼ��� datas �г��ֵĴ���(�� dataVector[i] �� datasMap �е� value)���ζ� Դ���ݼ��� datas �������
	//���� dataVector[0] �� datasMap �е�ֵΪ 2��˵�� dataVector[0] Ӧ���� datas ���������
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
