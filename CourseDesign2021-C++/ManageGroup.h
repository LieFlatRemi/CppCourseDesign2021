#pragma once
#include"Data.h"
//����Ⱥ

class ManageGroupLYC {
protected:
	UserLYC* user;							//ʹ�ù��ܵ��û�ָ��
	UserLYC* cur = NULL;					//Ⱥ���ҽ�����û�ָ��
	string key;
public:
	ManageGroupLYC(UserLYC*);
	~ManageGroupLYC();
	virtual void addGroup() = 0;			//����Ⱥ��
	virtual void dropGroup() = 0;			//�˳�Ⱥ��
	virtual void administerGroup() = 0;		//����Ⱥ��
	virtual void createGroup() = 0;			//����Ⱥ��
};

//QQ���е���Ⱥ��
class ManageChildGroupLYC : public ManageGroupLYC {
private:
	QQGroupLYC* father;
public:
	ManageChildGroupLYC(UserLYC* ,QQGroupLYC* );
	~ManageChildGroupLYC();
	void addGroup();						//����Ⱥ��Ա������Ⱥ
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//QQȺ��
class QQManageGroupLYC : public ManageGroupLYC {
private:
	ManageChildGroupLYC* manageChildGroup = NULL;
public:
	QQManageGroupLYC(UserLYC *);
	~QQManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//΢��Ⱥ��
class WechatManageGroupLYC : public ManageGroupLYC {
private:
	WechatUserLYC* w_user = NULL;
public:
	WechatManageGroupLYC(UserLYC*);
	~WechatManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//΢��Ⱥ��
class WeiboManageGroupLYC : public ManageGroupLYC {
public:
	WeiboManageGroupLYC(UserLYC*);
	~WeiboManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};