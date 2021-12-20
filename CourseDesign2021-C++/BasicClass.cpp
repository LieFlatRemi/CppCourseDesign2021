#pragma once
#pragma warning(disable:4996)		//防止localtime函数报warning
#include"Data.h"
#include<time.h>

//User、Group、Data等类方法的具体实现

//静态map成员需要再声明一次
map<string, UserLYC*> QQUserCollections::users;
map<string, GroupLYC*> QQGroupCollections::groups;
map<string, UserLYC*> WechatUserCollections::users;
map<string, GroupLYC*> WechatGroupCollections::groups;
map<string, UserLYC*> WeiboUserCollections::users;
map<string, GroupLYC*> WeiboGroupCollections::groups;

int QQUserCollections::nextRegisterId = 10000;
int QQGroupCollections::nextGroupId = 1007;
int WechatUserCollections::nextWcId = 20000;
int WechatGroupCollections::nextGroupId = 1007;
int WeiboGroupCollections::nextGroupId = 1007;


UserLYC::UserLYC(string nickName, string passwd) {
	this->passwd = passwd;
	this->nickName = nickName;
	//获取系统时间
	time_t nowtime = time(NULL);
	struct tm* gm = localtime(&nowtime);
	this->createYear = gm->tm_year + 1900;
	//地址和出生日期默认为未设置
	this->birthDate = "未设置";
	this->address = "未设置";
}

UserLYC::~UserLYC() {}

string UserLYC::getUserId() { return this->userId; }

string UserLYC::getNickName() { return this->nickName; }

string UserLYC::getBirth() { return this->birthDate; }

string UserLYC::getPasswd() { return this->passwd; }

string UserLYC::getAddress() { return this->address; }

int UserLYC::getTAge() {
	//获取系统时间
	time_t nowtime = time(NULL);
	struct tm* gm = localtime(&nowtime);
	int year = gm->tm_year + 1900;
	return year - this->createYear;
}

int UserLYC::getCreateYear() {
	return this->createYear;
}

void UserLYC::setUserId(string id) {
	this->userId = id;
}

void UserLYC::setCreateYear(int year) {
	this->createYear = year;
}

void UserLYC::setNickName(string nickName) {
	this->nickName = nickName;
}

void UserLYC::setBirth(string birthDate) {
	this->birthDate = birthDate;
}

void UserLYC::setAddress(string address) {
	this->address = address;
}

void UserLYC::setPasswd(string passwd) {
	this->passwd = passwd;
}

//获取好友信息map
map<string, string>& UserLYC::getFriendList() {
	return friendList;
}

void UserLYC::addFriend(string id, string remark) {
	this->friendList.insert(make_pair(id, remark));
}

bool UserLYC::deleteFriend(string id) {
	if (this->friendList.find(id) == this->friendList.end()) {
		cout << "该用户还不是你的好友" << endl;
		return false;
	}
	this->friendList.erase(id);
	return true;
}

void UserLYC::setFriendRemark(string id, string remark) {
	friendList.erase(id);
	friendList.insert(make_pair(id, remark));
}

//加入群
void UserLYC::addGroup(GroupLYC* group) {
	//该群不存在
	if (group == NULL) {
		return;
	}
	//该群存在，但用户已在群中
	if (group->searchMember(this->getUserId()) != NULL) {
		return;
	}
	group->addMember(this->getUserId());
}

void UserLYC::printBriefInfo() {
	cout << this->getUserId() << "\t" << this->getNickName() << endl;
}

void UserLYC::printDetailInfo() {
	cout << "ID：" << getUserId() << endl;
	cout << "昵称：" << getNickName() << endl;
	cout << "出生日期：" << getBirth() << endl;
	cout << "T龄：" << getTAge() << "年" << endl;
	cout << "所在地：" << getAddress() << endl;
}

GroupLYC::GroupLYC(string hostId, string name) {
	this->hostId = hostId;
	this->name = name;
	//群主加入群成员
	addMember(hostId);
}
GroupLYC::~GroupLYC() {}

string GroupLYC::getHostId() {
	return this->hostId;
}

string GroupLYC::getId() {
	return this->id;
}

void GroupLYC::setName(string name) {
	this->name = name;
}

string GroupLYC::getName() {
	return this->name;
}

void GroupLYC::addMember(string id) {
	members.insert(id);
}

void GroupLYC::removeMember(string id) {
	members.erase(id);
}

set<string>& GroupLYC::getMembersSet() {
	return members;
}

//打印群信息，顺序：群名-群号-群主
void GroupLYC::printInfo() {
	cout << "群名：" << this->getName() << endl; 
	cout << "群号：" << this->getId() << endl;
	cout<< "群主id："<< this->getHostId() << endl;
}

/*----------------------------------------QQ---------------------------------------------*/

void QQGroupCollections::deleteGroup(string id) {
	groups.erase(id);
}

map<string, GroupLYC*>& QQGroupCollections::getMap() {
	return groups;
}

//根据id查找群
GroupLYC* QQGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "未查找到此群！" << endl;
		return NULL;
	}
	else return it->second;
}

void QQGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new QQGroupLYC(hostId, name);
	//加入map
	groups.insert(make_pair(newGroup->getId(), newGroup));
}

void QQGroupCollections::addGroupFromFile(QQGroupLYC* group) {
	groups.insert(make_pair(group->getId(), group));
}

UserLYC* QQUserCollections::getUser(string id) {
	map<string, UserLYC*>::iterator it = users.find(id);
	if (it == users.end()) {
		return NULL;
	}
	else return it->second;
}

map<string, UserLYC*>& QQUserCollections::getMap() {
	return users;
}

void QQUserCollections::addUser(string name, string pwd) {
	UserLYC* user = new QQUserLYC(name, pwd);
	users.insert(make_pair(user->getUserId(), user));
}

void QQUserCollections::addUserFromFile(string name, string pwd, string id) {
	UserLYC* user = new QQUserLYC(name, pwd, id);
	users.insert(make_pair(user->getUserId(), user));
}

QQUserLYC::QQUserLYC(string nickName, string passwd) :UserLYC(nickName, passwd) {
	//用户id顺位
	this->userId = to_string(QQUserCollections::nextRegisterId++);
	this->isBind = false;
}

QQUserLYC::QQUserLYC(string nickName, string passwd, string id) :UserLYC(nickName, passwd) {
	this->userId = id;
	this->isBind = false;
}

QQUserLYC::~QQUserLYC() {}

//查询好友
//返回User对象指针，提供给接下来可能的操作（查询详细信息，删除好友等）
UserLYC* QQUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//未找到结果
		return NULL;
	}
	UserLYC* res = QQUserCollections::getUser(id);
	cout << "查询结果：" << endl;
	cout << " id\t昵称" << endl;
	res->printBriefInfo();
	//打印备注名
	if (it->second.compare("") != 0) {								//备注不为空
		cout << "备注名：" << it->second << endl;
	}
	else cout << "(无备注名)" << it->second << endl;
	return res;
}

//退出群
void QQUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getUserId()) == NULL) {
		return;
	}
	group->removeMember(this->getUserId());
	//如果你是群主，退出群后该群将解散
	string host = group->getHostId();
	if (host.compare(this->getUserId()) == 0) {
		cout << "由于你是群主，该群将解散" << endl;
		QQGroupCollections::deleteGroup(group->getId());
	}
}

void QQUserLYC::setIsBind(bool isBind) {
	this->isBind = isBind;
}
bool QQUserLYC::getIsBind() {
	return this->isBind;
}

//获取推荐好友
void QQUserLYC::getRecoFriend() {
	cout << "======== 微信推荐好友 =========" << endl;
	cout << endl;
	UserLYC* w_user = WechatUserCollections::getBindUser(userId);
	if (w_user == NULL) {											//无绑定微信账号的情况
		cout << "该QQ ID暂未与任何微信号绑定！" << endl;
		cout << endl;
	}
	else {
		map<string, string>& fris = w_user->getFriendList();
		bool flag = true;
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//检索在微信好友集合中，但不在qq集合中，且有qq绑定的用户
			string wid = it->first;										//微信id
			UserLYC* friUser = WechatUserCollections::getUser(wid);		//对应用户指针
			//无qq绑定
			if (friUser->getUserId().compare("") == 0)	continue;
			//已经是好友
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			//满足要求的用户
			friUser = QQUserCollections::getUser(friUser->getUserId());
			if (flag) {
				cout << "\tID\t昵称" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//没有用户满足条件的情况
		if (flag) {
			cout << "暂无微信推荐好友！" << endl;
			cout << endl;
		}
	}
	cout << "======== 微博推荐好友 =========" << endl;
	cout << endl;
	w_user = WeiboUserCollections::getUser(userId);
	//没有开通微博账号的情况
	if (w_user == NULL) {
		cout << "该ID未开通微博服务！" << endl;
		cout << endl;
	}
	else {
		bool flag = true;
		map<string, string>& fris = w_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//检索在微博好友集合中，但不在qq集合中，且开通了qq的用户
			string wid = it->first;										//微博id，即QQid
			UserLYC* friUser = QQUserCollections::getUser(wid);
			if (friUser == NULL)	continue;
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t昵称" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//没有用户满足条件的情况
		if (flag) {
			cout << "暂无微博推荐好友！" << endl;
			cout << endl;
		}
	}
}

QQGroupLYC::QQGroupLYC(string hostId, string name) : GroupLYC(hostId, name) {
	this->id = to_string(QQGroupCollections::nextGroupId++);
}

QQGroupLYC::QQGroupLYC(string id, string hostId, string name):GroupLYC(hostId, name) {
	this->id = id;
}

QQGroupLYC::~QQGroupLYC() {}

UserLYC* QQGroupLYC::searchMember(string id) {
	set<string>::iterator it = members.find(id);
	if (it == members.end()) {
		return NULL;
	}
	UserLYC* res = QQUserCollections::getUser(id);
	return res;
}

void QQGroupLYC::getMembers() {
	cout << "群用户信息：" << endl;
	cout << "\tID\t昵称" << endl;
	int index = 1;
	for (set<string>::iterator it = this->members.begin(); it != this->members.end(); it++) {
		UserLYC* user = QQUserCollections::getUser(*it);
		cout << index++ << ".\t";
		user->printBriefInfo();
	}
}

set<string>& QQGroupLYC::getManagersSet() {
	return managers;
}
set<string>& QQGroupLYC::getRequestsSet() {
	return requests;
}
map<string, QQChildGroupLYC*>& QQGroupLYC::getChildsMap() {
	return childs;
}

QQChildGroupLYC* QQGroupLYC::searchChilds(string id) {
	map<string, QQChildGroupLYC*>::iterator it = childs.find(id);
	if (it == childs.end()) {
		cout << "未查找到此群！" << endl;
		return NULL;
	}
	else return it->second;
}

void QQGroupLYC::createChilds(string hostId, string name) {
	QQChildGroupLYC* newGroup = new QQChildGroupLYC(hostId, name, this);
	childs.insert(make_pair(newGroup->getId(), newGroup));
}

void QQGroupLYC::addChildsFromFile(QQChildGroupLYC* group) {
	childs.insert(make_pair(group->getId(), group));
}

void QQGroupLYC::deleteChilds(string id) {
	childs.erase(id);
}

void QQGroupLYC::setChildId(int id) {
	this->childId = id;
}

int QQGroupLYC::getChildId() {
	return this->childId;
}

void QQGroupLYC::addManager(string id) {
	managers.insert(id);
}

void QQGroupLYC::deleteManager(string id) {
	managers.erase(id);
}

bool QQGroupLYC::searchManager(string id) {
	if (managers.find(id) != managers.end()) {
		return true;
	}
	return false;
}

void QQGroupLYC::passRequest(string id) {
	requests.erase(id);
	addMember(id);
}

void QQGroupLYC::addRequest(string id) {
	requests.insert(id);
}

void QQGroupLYC::handleRequest() {
	cout << endl;
	cout << "=======处理加群请求=======" << endl;
	if (requests.size() == 0) {
		cout << endl;
		cout << "==== 暂无加群请求！====" << endl;
		return;
	}
	//遍历set
	for (set<string>::iterator it = requests.begin(); it != requests.end();) {
		UserLYC* user = QQUserCollections::getUser(*it);
		cout << "用户：" << user->getNickName() << "(id：" << *it << ")请求加群" << endl;
		cout << endl;
		cout << "1.同意\t2.拒绝\t0.搁置" << endl;
		cout << endl;
		cout << "输入选项：";
		string key;
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 1:
			passRequest(*it++);
			cout << endl;
			cout << "请求通过" << endl;
			break;
		case 2:
			requests.erase(*it++);
			cout << endl;
			cout << "请求被拒绝" << endl;
			break;
		case 0:
			it++;
			continue;
		default:
			cout << "对不起，您的输入有误！" << endl;
			break;
		}
		cout << endl;
	}
}

UserLYC* QQChildGroupLYC::searchMember(string id) {
	set<string>::iterator it = members.find(id);
	if (it == members.end()) {
		return NULL;
	}
	UserLYC* res = QQUserCollections::getUser(id);
	return res;
}

QQChildGroupLYC::QQChildGroupLYC(string hostId, string name, QQGroupLYC* father) : GroupLYC(hostId, name) {
	this->father = father->getId();
	int gid = father->getChildId();
	this->id = to_string(gid);
	father->setChildId(++gid);
}

QQChildGroupLYC::QQChildGroupLYC(string id, string hostId, string name, QQGroupLYC* father) : GroupLYC(hostId, name) {
	this->father = father->getId();
	this->id = id;
}

QQChildGroupLYC::~QQChildGroupLYC() {}

void QQChildGroupLYC::getMembers() {
	cout << "群用户信息：" << endl;
	cout << "\tID\t昵称" << endl;
	int index = 1;
	for (set<string>::iterator it = this->members.begin(); it != this->members.end(); it++) {
		UserLYC* user = QQUserCollections::getUser(*it);
		cout << index++ << ".\t";
		user->printBriefInfo();
	}
}

string QQChildGroupLYC::getFather() {
	return father;
}

/*----------------------------------------WeChat---------------------------------------------*/

void WechatGroupCollections::deleteGroup(string id) {
	groups.erase(id);
}

map<string, GroupLYC*>& WechatGroupCollections::getMap() {
	return groups;
}

//根据id查找群
GroupLYC* WechatGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "未查找到此群！" << endl;
		return NULL;
	}
	else return it->second;
}

void WechatGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new WechatGroupLYC(hostId, name);
	//加入map
	groups.insert(make_pair(newGroup->getId(), newGroup));
}

void WechatGroupCollections::addGroupFromFile(WechatGroupLYC* group) {
	groups.insert(make_pair(group->getId(), group));
}

UserLYC* WechatUserCollections::getUser(string id) {			//查找只根据独立id查找
	map<string, UserLYC*>::iterator it = users.find(id);
	if (it == users.end()) {
		return NULL;
	}
	else return it->second;
}

UserLYC* WechatUserCollections::getBindUser(string id) {
	//遍历map
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		UserLYC* user = it->second;
		if (user->getUserId().compare(id) == 0) {
			return it->second;
		}
	}
	return NULL;
}

map<string, UserLYC*>& WechatUserCollections::getMap() {
	return users;
}

void WechatUserCollections::addUser(string name, string pwd) {
	WechatUserLYC* user = new WechatUserLYC(name, pwd);
	users.insert(make_pair(user->getWechatId(), user));
}

void WechatUserCollections::addUserFromFile(string name, string pwd, string id) {
	WechatUserLYC* user = new WechatUserLYC(name, pwd, id);
	users.insert(make_pair(user->getWechatId(), user));
}

WechatUserLYC::WechatUserLYC(string nickName, string pwd):UserLYC(nickName, pwd) {
	this->wcId = to_string(WechatUserCollections::nextWcId++);
	this->userId = "";
}

WechatUserLYC::WechatUserLYC(string nickName, string pwd, string id) : UserLYC(nickName, pwd) {
	this->wcId = id;
	this->userId = "";
}

WechatUserLYC::~WechatUserLYC() {}

void WechatUserLYC::printBriefInfo() {
	cout << this->getWechatId() << "\t" << this->getNickName() << endl;
}

void WechatUserLYC::printDetailInfo() {
	cout << "ID：" << getWechatId() << endl;
	cout << "昵称：" << getNickName() << endl;
	cout << "出生日期：" << getBirth() << endl;
	cout << "T龄：" << getTAge() << "年" << endl;
	cout << "所在地：" << getAddress() << endl;
}

//退出群
void WechatUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getWechatId()) == NULL) {
		return;
	}
	group->removeMember(this->getWechatId());
	//如果你是群主，退出群后该群将解散
	string host = group->getHostId();
	if (host.compare(this->getWechatId()) == 0) {
		cout << "由于你是群主，该群将解散" << endl;
		WechatGroupCollections::deleteGroup(group->getId());
	}
}

UserLYC* WechatUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//未找到结果
		return NULL;
	}
	WechatUserLYC* res = (WechatUserLYC*)WechatUserCollections::getUser(id);
	cout << "查询结果：" << endl;
	cout << "微信id\t昵称" << endl;
	res->printBriefInfo();
	//打印备注名
	if (it->second.compare("") != 0) {								//备注不为空
		cout << "备注名：" << it->second << endl;
	}
	else cout << "(无备注名)" << it->second << endl;
	return res;
}

//绑定QQ
void WechatUserLYC::bindWithQQ(string qid) {
	this->userId = qid;
	QQUserLYC* bindUser = (QQUserLYC*)QQUserCollections::getUser(qid);
	bindUser->setIsBind(true);
}

//解绑
void WechatUserLYC::resetBind() {
	string qid = this->userId;
	this->userId = "";
	QQUserLYC* bindUser = (QQUserLYC*)QQUserCollections::getUser(qid);
	if(bindUser != NULL)	bindUser->setIsBind(false);
}

void WechatUserLYC::getRecoFriend() {
	//未绑定QQ ID的，无法查询
	if (userId.compare("") == 0) {
		cout << endl;
		cout << "未绑定QQ ID，无法查询推荐好友！" << endl;
		cout << endl;
		return;
	}
	cout << "========= QQ推荐好友 ==========" << endl;
	cout << endl;
	UserLYC* q_user = QQUserCollections::getUser(userId);
	map<string, string>& fris = q_user->getFriendList();
	//检索在QQ好友集合中，但不在微信集合中，且有微信账号的用户
	bool flag = true;
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		string qid = it->first;
		WechatUserLYC* friUser = (WechatUserLYC*)WechatUserCollections::getBindUser(qid);
		//无微信绑定
		if (friUser == NULL)	continue;
		//已经是好友
		if (friendList.find(friUser->getWechatId()) != friendList.end())	continue;
		//满足要求的用户
		if (flag) {
			cout << "\tID\t昵称" << endl;
			flag = false;
		}
		cout << "\t" << friUser->getWechatId() << "\t" << friUser->getNickName() << endl;
		cout << endl;
	}
	//没有用户满足条件的情况
	if (flag) {
		cout << "暂无QQ推荐好友！" << endl;
		cout << endl;
	}
	cout << "======== 微博推荐好友 =========" << endl;
	cout << endl;
	q_user = WeiboUserCollections::getUser(userId);
	//没有开通微博账号的情况
	if (q_user == NULL) {
		cout << "对应QQ ID未开通微博服务！" << endl;
		cout << endl;
	}
	else {
		flag = true;
		map<string, string>& fris = q_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//检索在微博好友集合中，但不在微信集合中，且有微信账号的用户
			string wid = it->first;
			WechatUserLYC* friUser = (WechatUserLYC*)WechatUserCollections::getBindUser(wid);
			if (friUser == NULL)	continue;
			if (this->friendList.find(friUser->getWechatId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t昵称" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getWechatId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//没有用户满足条件的情况
		if (flag) {
			cout << "暂无微博推荐好友！" << endl;
			cout << endl;
		}
	}
}

string WechatUserLYC::getWechatId() { return this->wcId; }

WechatGroupLYC::WechatGroupLYC(string hostId, string name) : GroupLYC(hostId, name) {
	this->id = to_string(WechatGroupCollections::nextGroupId++);
}

WechatGroupLYC::WechatGroupLYC(string id, string hostId, string name) : GroupLYC(hostId, name) {
	this->id = id;
}

WechatGroupLYC::~WechatGroupLYC() {}

void WechatGroupLYC::getMembers() {
	cout << "群用户信息：" << endl;
	cout << "\t微信ID\t昵称" << endl;
	int index = 1;
	for (set<string>::iterator it = this->members.begin(); it != this->members.end(); it++) {
		WechatUserLYC* user = (WechatUserLYC*)WechatUserCollections::getUser(*it);
		cout << index++ << ".\t";
		user->printBriefInfo();
	}
}

UserLYC* WechatGroupLYC::searchMember(string id) {
	set<string>::iterator it = members.find(id);
	if (it == members.end()) {
		return NULL;
	}
	UserLYC* res = WechatUserCollections::getUser(id);
	return res;
}

/*----------------------------------------WeiBo---------------------------------------------*/

void WeiboGroupCollections::deleteGroup(string id) {
	groups.erase(id);
}

map<string, GroupLYC*>& WeiboGroupCollections::getMap() {
	return groups;
}

//根据id查找群
GroupLYC* WeiboGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "未查找到此群！" << endl;
		return NULL;
	}
	else return it->second;
}

void WeiboGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new WeiboGroupLYC(hostId, name);
	//加入map
	groups.insert(make_pair(newGroup->getId(), newGroup));
}

void WeiboGroupCollections::addGroupFromFile(WeiboGroupLYC* group) {
	groups.insert(make_pair(group->getId(), group));
}

UserLYC* WeiboUserCollections::getUser(string id) {			//查找只根据独立id查找
	map<string, UserLYC*>::iterator it = users.find(id);
	if (it == users.end()) {
		return NULL;
	}
	else return it->second;
}

map<string, UserLYC*>& WeiboUserCollections::getMap() {
	return users;
}

void WeiboUserCollections::addUser(string name, string pwd) {
	UserLYC* user = new WeiboUserLYC(name, pwd);
	users.insert(make_pair(user->getUserId(), user));
}

void WeiboUserCollections::addUserFromFile(string name, string pwd, string id) {
	WeiboUserLYC* user = new WeiboUserLYC(name, pwd, id);
	users.insert(make_pair(user->getUserId(), user));
}

WeiboUserLYC::WeiboUserLYC(string nickName, string passwd) :UserLYC(nickName, passwd) {
	//用户id顺位，微博与QQ共用ID
	this->userId = to_string(QQUserCollections::nextRegisterId++);
}

WeiboUserLYC::WeiboUserLYC(string nickName, string passwd, string id) :UserLYC(nickName, passwd) {
	this->userId = id;
}

WeiboUserLYC::~WeiboUserLYC() {}

//查询好友
//返回User对象指针，提供给接下来可能的操作（查询详细信息，删除好友等）
UserLYC* WeiboUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//未找到结果
		return NULL;
	}
	UserLYC* res = WeiboUserCollections::getUser(id);
	cout << "查询结果：" << endl;
	cout << " id\t昵称" << endl;
	res->printBriefInfo();
	//打印备注名
	if (it->second.compare("") != 0) {								//备注不为空
		cout << "备注名：" << it->second << endl;
	}
	else cout << "(无备注名)" << it->second << endl;
	return res;
}

//退出群
void WeiboUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getUserId()) == NULL) {
		return;
	}
	group->removeMember(this->getUserId());
	//如果你是群主，退出群后该群将解散
	string host = group->getHostId();
	if (host.compare(this->getUserId()) == 0) {
		cout << "由于你是群主，该群将解散" << endl;
		WeiboGroupCollections::deleteGroup(group->getId());
	}
}

//获取推荐好友
void WeiboUserLYC::getRecoFriend() {
	QQUserLYC* q_user = (QQUserLYC*)QQUserCollections::getUser(userId);
	//没有开通QQ，无法推荐
	if (q_user == NULL) {
		cout << endl;
		cout << "该ID暂未开通QQ！" << endl;
		cout << endl;
		return;
	}
	cout << "========= QQ推荐好友 ==========" << endl;
	cout << endl;
	map<string, string>& fris = q_user->getFriendList();
	bool flag = true;
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		//检索在QQ好友集合中，但不在微博好友集合中的用户
		string qid = it->first;
		UserLYC* friUser = WeiboUserCollections::getUser(qid);
		//没开通微博
		if (friUser == NULL)	continue;
		//已经是好友
		if (this->friendList.find(qid) != friendList.end())	continue;
		//满足要求的用户
		if (flag) {
			cout << "\tID\t昵称" << endl;
			flag = false;
		}
		cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
		cout << endl;
	}
	//没有用户满足条件的情况
	if (flag) {
		cout << "暂无QQ推荐好友！" << endl;
		cout << endl;
	}
	cout << "======== 微信推荐好友 =========" << endl;
	cout << endl;
	UserLYC* w_user = WechatUserCollections::getBindUser(userId);
	//没有开通微信账号的情况
	if (w_user == NULL) {
		cout << "该ID未绑定微信账号！" << endl;
		cout << endl;
	}
	else {
		flag = true;
		map<string, string>& fris = w_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//检索在微信好友集合中，但不在微博集合中，且开通了微博的用户
			string wid = it->first;												//微信id
			string uid = WechatUserCollections::getUser(wid)->getUserId();		//总id
			UserLYC* friUser = WeiboUserCollections::getUser(uid);
			//未开通微博
			if (friUser == NULL)	continue;
			//已经是好友
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t昵称" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//没有用户满足条件的情况
		if (flag) {
			cout << "暂无微信推荐好友！" << endl;
			cout << endl;
		}
	}
}

WeiboGroupLYC::WeiboGroupLYC(string hostId, string name) : GroupLYC(hostId, name) {
	this->id = to_string(WeiboGroupCollections::nextGroupId++);
}

WeiboGroupLYC::WeiboGroupLYC(string id, string hostId, string name) : GroupLYC(hostId, name) {
	this->id = id;
}

WeiboGroupLYC::~WeiboGroupLYC() {}

void WeiboGroupLYC::getMembers() {
	cout << "群用户信息：" << endl;
	cout << "\tID\t昵称" << endl;
	int index = 1;
	for (set<string>::iterator it = this->members.begin(); it != this->members.end(); it++) {
		UserLYC* user = WeiboUserCollections::getUser(*it);
		cout << index++ << ".\t";
		user->printBriefInfo();
	}
}

UserLYC* WeiboGroupLYC::searchMember(string id) {
	set<string>::iterator it = members.find(id);
	if (it == members.end()) {
		return NULL;
	}
	UserLYC* res = WeiboUserCollections::getUser(id);
	return res;
}