#pragma once
#include<iostream>
#include<string>
#include<stdbool.h>
#include<vector>
using namespace std;

//�����ࣺ�ṩһЩ���ߺ���

class Tools {
public:
	static int getStringChoice(string key);		//�ڸ����˵���ѡ��֣����û��������л�ȡ����ѡ��
	static bool isBirthFormat(string key);		//��֤�û������Ƿ��������ո�ʽ
	static bool isEmptyString(string key);		//��֤�Ƿ�Ϊ���ַ���
	static vector<string> splitString(string key, char ch);		//����ĳ���ַ����ַ����ָ�
};
