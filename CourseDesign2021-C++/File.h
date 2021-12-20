#pragma once
#include"Data.h"
#include"Group.h"
#include"User.h"
#include<fstream>

//�ļ���д��

class FileLYC {
protected:
	ofstream ofs;
	ifstream ifs;
public:
	FileLYC();
	~FileLYC();
	virtual void readUser() = 0;					//��ȡUser��Ϣ
	virtual void readGroup() = 0;					//��ȡȺ����Ϣ
	virtual void writeUser() = 0;					//д���û���Ϣ
	virtual void writeGroup() = 0;					//д��Ⱥ����Ϣ
};

class QQFile : public FileLYC {
public:
	QQFile();
	~QQFile();
	void readUser();								//��ȡUser��Ϣ
	void readGroup();								//��ȡȺ����Ϣ
	void writeUser();								//д���û���Ϣ
	void writeGroup();								//д��Ⱥ����Ϣ
};

class WechatFile : public FileLYC {
public:
	WechatFile();
	~WechatFile();
	void readUser();								//��ȡUser��Ϣ
	void readGroup();								//��ȡȺ����Ϣ
	void writeUser();								//д���û���Ϣ
	void writeGroup();								//д��Ⱥ����Ϣ
};

class WeiboFile : public FileLYC {
public:
	WeiboFile();
	~WeiboFile();
	void readUser();								//��ȡUser��Ϣ
	void readGroup();								//��ȡȺ����Ϣ
	void writeUser();								//д���û���Ϣ
	void writeGroup();								//д��Ⱥ����Ϣ
};