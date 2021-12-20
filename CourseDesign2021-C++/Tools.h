#pragma once
#include<iostream>
#include<string>
#include<stdbool.h>
#include<vector>
using namespace std;

//工具类：提供一些工具函数

class Tools {
public:
	static int getStringChoice(string key);		//在各个菜单的选项部分，从用户的输入中获取数字选项
	static bool isBirthFormat(string key);		//验证用户输入是否满足生日格式
	static bool isEmptyString(string key);		//验证是否为空字符串
	static vector<string> splitString(string key, char ch);		//依照某个字符对字符串分割
};
