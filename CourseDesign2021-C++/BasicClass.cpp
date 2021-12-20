#pragma once
#pragma warning(disable:4996)		//��ֹlocaltime������warning
#include"Data.h"
#include<time.h>

//User��Group��Data���෽���ľ���ʵ��

//��̬map��Ա��Ҫ������һ��
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
	//��ȡϵͳʱ��
	time_t nowtime = time(NULL);
	struct tm* gm = localtime(&nowtime);
	this->createYear = gm->tm_year + 1900;
	//��ַ�ͳ�������Ĭ��Ϊδ����
	this->birthDate = "δ����";
	this->address = "δ����";
}

UserLYC::~UserLYC() {}

string UserLYC::getUserId() { return this->userId; }

string UserLYC::getNickName() { return this->nickName; }

string UserLYC::getBirth() { return this->birthDate; }

string UserLYC::getPasswd() { return this->passwd; }

string UserLYC::getAddress() { return this->address; }

int UserLYC::getTAge() {
	//��ȡϵͳʱ��
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

//��ȡ������Ϣmap
map<string, string>& UserLYC::getFriendList() {
	return friendList;
}

void UserLYC::addFriend(string id, string remark) {
	this->friendList.insert(make_pair(id, remark));
}

bool UserLYC::deleteFriend(string id) {
	if (this->friendList.find(id) == this->friendList.end()) {
		cout << "���û���������ĺ���" << endl;
		return false;
	}
	this->friendList.erase(id);
	return true;
}

void UserLYC::setFriendRemark(string id, string remark) {
	friendList.erase(id);
	friendList.insert(make_pair(id, remark));
}

//����Ⱥ
void UserLYC::addGroup(GroupLYC* group) {
	//��Ⱥ������
	if (group == NULL) {
		return;
	}
	//��Ⱥ���ڣ����û�����Ⱥ��
	if (group->searchMember(this->getUserId()) != NULL) {
		return;
	}
	group->addMember(this->getUserId());
}

void UserLYC::printBriefInfo() {
	cout << this->getUserId() << "\t" << this->getNickName() << endl;
}

void UserLYC::printDetailInfo() {
	cout << "ID��" << getUserId() << endl;
	cout << "�ǳƣ�" << getNickName() << endl;
	cout << "�������ڣ�" << getBirth() << endl;
	cout << "T�䣺" << getTAge() << "��" << endl;
	cout << "���ڵأ�" << getAddress() << endl;
}

GroupLYC::GroupLYC(string hostId, string name) {
	this->hostId = hostId;
	this->name = name;
	//Ⱥ������Ⱥ��Ա
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

//��ӡȺ��Ϣ��˳��Ⱥ��-Ⱥ��-Ⱥ��
void GroupLYC::printInfo() {
	cout << "Ⱥ����" << this->getName() << endl; 
	cout << "Ⱥ�ţ�" << this->getId() << endl;
	cout<< "Ⱥ��id��"<< this->getHostId() << endl;
}

/*----------------------------------------QQ---------------------------------------------*/

void QQGroupCollections::deleteGroup(string id) {
	groups.erase(id);
}

map<string, GroupLYC*>& QQGroupCollections::getMap() {
	return groups;
}

//����id����Ⱥ
GroupLYC* QQGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "δ���ҵ���Ⱥ��" << endl;
		return NULL;
	}
	else return it->second;
}

void QQGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new QQGroupLYC(hostId, name);
	//����map
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
	//�û�id˳λ
	this->userId = to_string(QQUserCollections::nextRegisterId++);
	this->isBind = false;
}

QQUserLYC::QQUserLYC(string nickName, string passwd, string id) :UserLYC(nickName, passwd) {
	this->userId = id;
	this->isBind = false;
}

QQUserLYC::~QQUserLYC() {}

//��ѯ����
//����User����ָ�룬�ṩ�����������ܵĲ�������ѯ��ϸ��Ϣ��ɾ�����ѵȣ�
UserLYC* QQUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//δ�ҵ����
		return NULL;
	}
	UserLYC* res = QQUserCollections::getUser(id);
	cout << "��ѯ�����" << endl;
	cout << " id\t�ǳ�" << endl;
	res->printBriefInfo();
	//��ӡ��ע��
	if (it->second.compare("") != 0) {								//��ע��Ϊ��
		cout << "��ע����" << it->second << endl;
	}
	else cout << "(�ޱ�ע��)" << it->second << endl;
	return res;
}

//�˳�Ⱥ
void QQUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getUserId()) == NULL) {
		return;
	}
	group->removeMember(this->getUserId());
	//�������Ⱥ�����˳�Ⱥ���Ⱥ����ɢ
	string host = group->getHostId();
	if (host.compare(this->getUserId()) == 0) {
		cout << "��������Ⱥ������Ⱥ����ɢ" << endl;
		QQGroupCollections::deleteGroup(group->getId());
	}
}

void QQUserLYC::setIsBind(bool isBind) {
	this->isBind = isBind;
}
bool QQUserLYC::getIsBind() {
	return this->isBind;
}

//��ȡ�Ƽ�����
void QQUserLYC::getRecoFriend() {
	cout << "======== ΢���Ƽ����� =========" << endl;
	cout << endl;
	UserLYC* w_user = WechatUserCollections::getBindUser(userId);
	if (w_user == NULL) {											//�ް�΢���˺ŵ����
		cout << "��QQ ID��δ���κ�΢�źŰ󶨣�" << endl;
		cout << endl;
	}
	else {
		map<string, string>& fris = w_user->getFriendList();
		bool flag = true;
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//������΢�ź��Ѽ����У�������qq�����У�����qq�󶨵��û�
			string wid = it->first;										//΢��id
			UserLYC* friUser = WechatUserCollections::getUser(wid);		//��Ӧ�û�ָ��
			//��qq��
			if (friUser->getUserId().compare("") == 0)	continue;
			//�Ѿ��Ǻ���
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			//����Ҫ����û�
			friUser = QQUserCollections::getUser(friUser->getUserId());
			if (flag) {
				cout << "\tID\t�ǳ�" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//û���û��������������
		if (flag) {
			cout << "����΢���Ƽ����ѣ�" << endl;
			cout << endl;
		}
	}
	cout << "======== ΢���Ƽ����� =========" << endl;
	cout << endl;
	w_user = WeiboUserCollections::getUser(userId);
	//û�п�ͨ΢���˺ŵ����
	if (w_user == NULL) {
		cout << "��IDδ��ͨ΢������" << endl;
		cout << endl;
	}
	else {
		bool flag = true;
		map<string, string>& fris = w_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//������΢�����Ѽ����У�������qq�����У��ҿ�ͨ��qq���û�
			string wid = it->first;										//΢��id����QQid
			UserLYC* friUser = QQUserCollections::getUser(wid);
			if (friUser == NULL)	continue;
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t�ǳ�" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//û���û��������������
		if (flag) {
			cout << "����΢���Ƽ����ѣ�" << endl;
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
	cout << "Ⱥ�û���Ϣ��" << endl;
	cout << "\tID\t�ǳ�" << endl;
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
		cout << "δ���ҵ���Ⱥ��" << endl;
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
	cout << "=======�����Ⱥ����=======" << endl;
	if (requests.size() == 0) {
		cout << endl;
		cout << "==== ���޼�Ⱥ����====" << endl;
		return;
	}
	//����set
	for (set<string>::iterator it = requests.begin(); it != requests.end();) {
		UserLYC* user = QQUserCollections::getUser(*it);
		cout << "�û���" << user->getNickName() << "(id��" << *it << ")�����Ⱥ" << endl;
		cout << endl;
		cout << "1.ͬ��\t2.�ܾ�\t0.����" << endl;
		cout << endl;
		cout << "����ѡ�";
		string key;
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 1:
			passRequest(*it++);
			cout << endl;
			cout << "����ͨ��" << endl;
			break;
		case 2:
			requests.erase(*it++);
			cout << endl;
			cout << "���󱻾ܾ�" << endl;
			break;
		case 0:
			it++;
			continue;
		default:
			cout << "�Բ���������������" << endl;
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
	cout << "Ⱥ�û���Ϣ��" << endl;
	cout << "\tID\t�ǳ�" << endl;
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

//����id����Ⱥ
GroupLYC* WechatGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "δ���ҵ���Ⱥ��" << endl;
		return NULL;
	}
	else return it->second;
}

void WechatGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new WechatGroupLYC(hostId, name);
	//����map
	groups.insert(make_pair(newGroup->getId(), newGroup));
}

void WechatGroupCollections::addGroupFromFile(WechatGroupLYC* group) {
	groups.insert(make_pair(group->getId(), group));
}

UserLYC* WechatUserCollections::getUser(string id) {			//����ֻ���ݶ���id����
	map<string, UserLYC*>::iterator it = users.find(id);
	if (it == users.end()) {
		return NULL;
	}
	else return it->second;
}

UserLYC* WechatUserCollections::getBindUser(string id) {
	//����map
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
	cout << "ID��" << getWechatId() << endl;
	cout << "�ǳƣ�" << getNickName() << endl;
	cout << "�������ڣ�" << getBirth() << endl;
	cout << "T�䣺" << getTAge() << "��" << endl;
	cout << "���ڵأ�" << getAddress() << endl;
}

//�˳�Ⱥ
void WechatUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getWechatId()) == NULL) {
		return;
	}
	group->removeMember(this->getWechatId());
	//�������Ⱥ�����˳�Ⱥ���Ⱥ����ɢ
	string host = group->getHostId();
	if (host.compare(this->getWechatId()) == 0) {
		cout << "��������Ⱥ������Ⱥ����ɢ" << endl;
		WechatGroupCollections::deleteGroup(group->getId());
	}
}

UserLYC* WechatUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//δ�ҵ����
		return NULL;
	}
	WechatUserLYC* res = (WechatUserLYC*)WechatUserCollections::getUser(id);
	cout << "��ѯ�����" << endl;
	cout << "΢��id\t�ǳ�" << endl;
	res->printBriefInfo();
	//��ӡ��ע��
	if (it->second.compare("") != 0) {								//��ע��Ϊ��
		cout << "��ע����" << it->second << endl;
	}
	else cout << "(�ޱ�ע��)" << it->second << endl;
	return res;
}

//��QQ
void WechatUserLYC::bindWithQQ(string qid) {
	this->userId = qid;
	QQUserLYC* bindUser = (QQUserLYC*)QQUserCollections::getUser(qid);
	bindUser->setIsBind(true);
}

//���
void WechatUserLYC::resetBind() {
	string qid = this->userId;
	this->userId = "";
	QQUserLYC* bindUser = (QQUserLYC*)QQUserCollections::getUser(qid);
	if(bindUser != NULL)	bindUser->setIsBind(false);
}

void WechatUserLYC::getRecoFriend() {
	//δ��QQ ID�ģ��޷���ѯ
	if (userId.compare("") == 0) {
		cout << endl;
		cout << "δ��QQ ID���޷���ѯ�Ƽ����ѣ�" << endl;
		cout << endl;
		return;
	}
	cout << "========= QQ�Ƽ����� ==========" << endl;
	cout << endl;
	UserLYC* q_user = QQUserCollections::getUser(userId);
	map<string, string>& fris = q_user->getFriendList();
	//������QQ���Ѽ����У�������΢�ż����У�����΢���˺ŵ��û�
	bool flag = true;
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		string qid = it->first;
		WechatUserLYC* friUser = (WechatUserLYC*)WechatUserCollections::getBindUser(qid);
		//��΢�Ű�
		if (friUser == NULL)	continue;
		//�Ѿ��Ǻ���
		if (friendList.find(friUser->getWechatId()) != friendList.end())	continue;
		//����Ҫ����û�
		if (flag) {
			cout << "\tID\t�ǳ�" << endl;
			flag = false;
		}
		cout << "\t" << friUser->getWechatId() << "\t" << friUser->getNickName() << endl;
		cout << endl;
	}
	//û���û��������������
	if (flag) {
		cout << "����QQ�Ƽ����ѣ�" << endl;
		cout << endl;
	}
	cout << "======== ΢���Ƽ����� =========" << endl;
	cout << endl;
	q_user = WeiboUserCollections::getUser(userId);
	//û�п�ͨ΢���˺ŵ����
	if (q_user == NULL) {
		cout << "��ӦQQ IDδ��ͨ΢������" << endl;
		cout << endl;
	}
	else {
		flag = true;
		map<string, string>& fris = q_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//������΢�����Ѽ����У�������΢�ż����У�����΢���˺ŵ��û�
			string wid = it->first;
			WechatUserLYC* friUser = (WechatUserLYC*)WechatUserCollections::getBindUser(wid);
			if (friUser == NULL)	continue;
			if (this->friendList.find(friUser->getWechatId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t�ǳ�" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getWechatId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//û���û��������������
		if (flag) {
			cout << "����΢���Ƽ����ѣ�" << endl;
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
	cout << "Ⱥ�û���Ϣ��" << endl;
	cout << "\t΢��ID\t�ǳ�" << endl;
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

//����id����Ⱥ
GroupLYC* WeiboGroupCollections::getGroup(string id) {
	map<string, GroupLYC*>::iterator it = groups.find(id);
	if (it == groups.end()) {
		cout << "δ���ҵ���Ⱥ��" << endl;
		return NULL;
	}
	else return it->second;
}

void WeiboGroupCollections::addNewGroup(string name, string hostId) {
	GroupLYC* newGroup = new WeiboGroupLYC(hostId, name);
	//����map
	groups.insert(make_pair(newGroup->getId(), newGroup));
}

void WeiboGroupCollections::addGroupFromFile(WeiboGroupLYC* group) {
	groups.insert(make_pair(group->getId(), group));
}

UserLYC* WeiboUserCollections::getUser(string id) {			//����ֻ���ݶ���id����
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
	//�û�id˳λ��΢����QQ����ID
	this->userId = to_string(QQUserCollections::nextRegisterId++);
}

WeiboUserLYC::WeiboUserLYC(string nickName, string passwd, string id) :UserLYC(nickName, passwd) {
	this->userId = id;
}

WeiboUserLYC::~WeiboUserLYC() {}

//��ѯ����
//����User����ָ�룬�ṩ�����������ܵĲ�������ѯ��ϸ��Ϣ��ɾ�����ѵȣ�
UserLYC* WeiboUserLYC::searchFriend(string id) {
	map<string, string>::iterator it = this->friendList.find(id);
	if (it == this->friendList.end()) {									//δ�ҵ����
		return NULL;
	}
	UserLYC* res = WeiboUserCollections::getUser(id);
	cout << "��ѯ�����" << endl;
	cout << " id\t�ǳ�" << endl;
	res->printBriefInfo();
	//��ӡ��ע��
	if (it->second.compare("") != 0) {								//��ע��Ϊ��
		cout << "��ע����" << it->second << endl;
	}
	else cout << "(�ޱ�ע��)" << it->second << endl;
	return res;
}

//�˳�Ⱥ
void WeiboUserLYC::exitGroup(GroupLYC* group) {
	if (group == NULL) {
		return;
	}
	if (group->searchMember(this->getUserId()) == NULL) {
		return;
	}
	group->removeMember(this->getUserId());
	//�������Ⱥ�����˳�Ⱥ���Ⱥ����ɢ
	string host = group->getHostId();
	if (host.compare(this->getUserId()) == 0) {
		cout << "��������Ⱥ������Ⱥ����ɢ" << endl;
		WeiboGroupCollections::deleteGroup(group->getId());
	}
}

//��ȡ�Ƽ�����
void WeiboUserLYC::getRecoFriend() {
	QQUserLYC* q_user = (QQUserLYC*)QQUserCollections::getUser(userId);
	//û�п�ͨQQ���޷��Ƽ�
	if (q_user == NULL) {
		cout << endl;
		cout << "��ID��δ��ͨQQ��" << endl;
		cout << endl;
		return;
	}
	cout << "========= QQ�Ƽ����� ==========" << endl;
	cout << endl;
	map<string, string>& fris = q_user->getFriendList();
	bool flag = true;
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		//������QQ���Ѽ����У�������΢�����Ѽ����е��û�
		string qid = it->first;
		UserLYC* friUser = WeiboUserCollections::getUser(qid);
		//û��ͨ΢��
		if (friUser == NULL)	continue;
		//�Ѿ��Ǻ���
		if (this->friendList.find(qid) != friendList.end())	continue;
		//����Ҫ����û�
		if (flag) {
			cout << "\tID\t�ǳ�" << endl;
			flag = false;
		}
		cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
		cout << endl;
	}
	//û���û��������������
	if (flag) {
		cout << "����QQ�Ƽ����ѣ�" << endl;
		cout << endl;
	}
	cout << "======== ΢���Ƽ����� =========" << endl;
	cout << endl;
	UserLYC* w_user = WechatUserCollections::getBindUser(userId);
	//û�п�ͨ΢���˺ŵ����
	if (w_user == NULL) {
		cout << "��IDδ��΢���˺ţ�" << endl;
		cout << endl;
	}
	else {
		flag = true;
		map<string, string>& fris = w_user->getFriendList();
		for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
			//������΢�ź��Ѽ����У�������΢�������У��ҿ�ͨ��΢�����û�
			string wid = it->first;												//΢��id
			string uid = WechatUserCollections::getUser(wid)->getUserId();		//��id
			UserLYC* friUser = WeiboUserCollections::getUser(uid);
			//δ��ͨ΢��
			if (friUser == NULL)	continue;
			//�Ѿ��Ǻ���
			if (this->friendList.find(friUser->getUserId()) != friendList.end())	continue;
			if (flag) {
				cout << "\tID\t�ǳ�" << endl;
				flag = false;
			}
			cout << "\t" << friUser->getUserId() << "\t" << friUser->getNickName() << endl;
			cout << endl;
		}
		//û���û��������������
		if (flag) {
			cout << "����΢���Ƽ����ѣ�" << endl;
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
	cout << "Ⱥ�û���Ϣ��" << endl;
	cout << "\tID\t�ǳ�" << endl;
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