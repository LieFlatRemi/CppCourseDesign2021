#pragma once
#include"Data.h"
#include"Group.h"
#include"User.h"
#include<fstream>

//文件读写类

class FileLYC {
protected:
	ofstream ofs;
	ifstream ifs;
public:
	FileLYC();
	~FileLYC();
	virtual void readUser() = 0;					//读取User信息
	virtual void readGroup() = 0;					//读取群聊信息
	virtual void writeUser() = 0;					//写入用户信息
	virtual void writeGroup() = 0;					//写入群聊信息
};

class QQFile : public FileLYC {
public:
	QQFile();
	~QQFile();
	void readUser();								//读取User信息
	void readGroup();								//读取群聊信息
	void writeUser();								//写入用户信息
	void writeGroup();								//写入群聊信息
};

class WechatFile : public FileLYC {
public:
	WechatFile();
	~WechatFile();
	void readUser();								//读取User信息
	void readGroup();								//读取群聊信息
	void writeUser();								//写入用户信息
	void writeGroup();								//写入群聊信息
};

class WeiboFile : public FileLYC {
public:
	WeiboFile();
	~WeiboFile();
	void readUser();								//读取User信息
	void readGroup();								//读取群聊信息
	void writeUser();								//写入用户信息
	void writeGroup();								//写入群聊信息
};