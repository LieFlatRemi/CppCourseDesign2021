#pragma once
#include"User.h"

//群抽象类
class GroupLYC
{
protected:
	string id;											//群号
	string hostId;										//群主id
	set<string> members;								//群成员
	string name;										//群名
public:
	GroupLYC(string hostId, string name);
	~GroupLYC();
	string getId();
	string getHostId();
	void setName(string name);							//设置群名
	string getName();									//获取群名
	set<string>& getMembersSet();						//获取members的Set	
	virtual void getMembers() = 0;						//打印全部群成员
	void addMember(string id);							//添加群成员
	void removeMember(string id);						//删除群成员
	virtual UserLYC* searchMember(string id) = 0;		//根据id查询群成员
	void printInfo();									//打印群信息
};

//=====================QQ群：有管理员制度；有临时讨论组（子群）；加群申请审核制度==========================

class QQChildGroupLYC;									//预先声明

//QQ群
class QQGroupLYC : public GroupLYC {
private:
	set<string> managers;								//管理员
	set<string> requests;								//加群请求
	map<string, QQChildGroupLYC*> childs;				//子群
	int childId = 101;									//子群号
public:
	QQGroupLYC(string, string);
	QQGroupLYC(string, string, string);
	~QQGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
	void setChildId(int id);
	int getChildId();
	QQChildGroupLYC* searchChilds(string id);			//查找子群
	void createChilds(string hostId, string name);		//新建子群
	void deleteChilds(string id);						//解散子群
	void addChildsFromFile(QQChildGroupLYC* group);		//从文件录入子群
	set<string>& getManagersSet();
	set<string>& getRequestsSet();
	map<string, QQChildGroupLYC*>& getChildsMap();
	void addManager(string id);							//添加管理员
	void deleteManager(string id);						//删除管理员
	bool searchManager(string id);						//验证一个用户是否为管理员
	void passRequest(string id);						//通过加群请求
	void addRequest(string id);							//添加加群请求
	void handleRequest();								//处理加群请求
};

//QQ子群
class QQChildGroupLYC : public GroupLYC {
private:
	string father;					//父群
public:
	QQChildGroupLYC(string, string, QQGroupLYC*);
	QQChildGroupLYC(string, string, string, QQGroupLYC*);
	~QQChildGroupLYC();
	void getMembers();
	string getFather();
	UserLYC* searchMember(string id);
}; 

/*=====================微信群：仅有群主特权；只能邀请入群==========================*/

class WechatGroupLYC : public GroupLYC {
public:
	WechatGroupLYC(string, string);
	WechatGroupLYC(string, string, string);
	~WechatGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
};

/*=====================微博群：仅有群主特权；群主邀请入群==========================*/

class WeiboGroupLYC :public GroupLYC {
public:
	WeiboGroupLYC(string, string);
	WeiboGroupLYC(string, string, string);
	~WeiboGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
};