#include"Tools.h"

int Tools::getStringChoice(string key) {
	if (key.length() != 1) {
		return -1;
	}
	return key.at(0) - 48;
}

bool Tools::isBirthFormat(string key) {
	//基本格式：xxxx.xx.xx
	//长度正好为10
	int len = key.length();
	if (len != 10)	return false;
	//相应位置为句号 (下标4，7)
	if (key.at(4) != '.' || key.at(7) != '.')
		return false;
	//其他位置只能是数字
	for (int i = 0; i < len; i++) {
		if (i == 4 || i == 7)	continue;
		if (key.at(i) > '9' || key.at(i) < '0') {
			return false;
		}
	}
	return true;
}

bool Tools::isEmptyString(string key) {
	if (key.compare("") == 0) {
		return true;
	}
	return false;
}

vector<string> Tools::splitString(string key, char ch) {
	vector<string> res;
	int start = 0, end = 0;
	for (int i = 0; i < key.length(); i++) {
		if (key.at(i) == ch) {
			res.push_back(key.substr(start, end));
			start = i + 1;
			end = 0;
		}
		else {
			end++;
		}
	}
	if (start < key.length())
		res.push_back(key.substr(start, end));
	return res;
}