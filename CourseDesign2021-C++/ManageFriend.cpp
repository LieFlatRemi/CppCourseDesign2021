#include"ManageFriend.h"

ManageFriendLYC::ManageFriendLYC(UserLYC* user) {
	this->user = user;
}

ManageFriendLYC::~ManageFriendLYC() {}

void ManageFriendLYC::setFriendRemark() {
	cout << "���������id��";
	getline(cin, key);
	//��ѯ
	if (user->searchFriend(key) == NULL) {
		cout << "����û�������ĺ��ѣ�" << endl;
		return;
	}
	cout << endl;
	cout << "�������޸ĺ�ı�ע��:(�������ʾ�ޱ�ע)";
	string remark; 
	getline(cin, remark);
	user->setFriendRemark(key, remark);
	cout << endl;
	cout << "�޸ĳɹ���" << endl;
}

void ManageFriendLYC::deleteFriend() {
	cout << "���������id��";
	getline(cin, key);
	if (user->deleteFriend(key)) {
		cout << "ɾ�����ѳɹ���" << endl;
	}
	else cout << "ɾ������ʧ�ܣ�" << endl;
}

/*----------------------------------QQ------------------------------------------*/

QQManageFriendLYC::QQManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

QQManageFriendLYC::~QQManageFriendLYC() {}

void QQManageFriendLYC::addFriend() {
	cout << "������������ӵĺ���id��";
	getline(cin, key);
	//��������Լ�Ϊ����
	if (key.compare(user->getUserId()) == 0) {
		cout << "�㲻������Լ�Ϊ���ѣ�" << endl;
		return;
	}
	if (QQUserCollections::getUser(key) == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "���û��Ѿ�����ĺ�����" << endl;
	}
	else {
		string remark;
		cout << "������ѵı�ע������Ҳ���Բ����룬���ޱ�ע����";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "��Ӻ��ѳɹ���" << endl;
	}
}

void QQManageFriendLYC::searchFriend() {
	cout << "���������id��";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "����û�������ĺ��ѣ�" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "��������ϣ��ִ�еĲ�����" << endl;
	cout << endl;
	cout << "====1.��ѯ��ϸ��Ϣ====" << endl;
	cout << endl;
	cout << "=====2.�޸ı�ע��=====" << endl;
	cout << endl;
	cout << "=====3.ɾ���ú���=====" << endl;
	cout << endl;
	cout << "======= 0.���� =======" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "������ϸ��Ϣ��" << endl;
		fri = QQUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "�����±�ע����";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "�޸ĳɹ���" << endl;
		break;
	case 3:
		cout << "ȷ��Ҫɾ���ú�����" << endl;
		cout << "1.ɾ��\t0.�ٿ���һ�¡���" << endl;
		cout << "���������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "ɾ�����ѳɹ���" << endl;
			}
			break;
		default:
			cout << "�Բ������������д���" << endl;
		}
		break;
	default:
		cout << "�Բ������������д���" << endl;
	}
}

void QQManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "����δ����κκ���" << endl;
		return;
	}
	cout << "========�����б�========" << endl;
	cout << endl;
	cout << "\tid\t�ǳ�" << endl;
	//����map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = QQUserCollections::getUser(it->first);
		cout << "\t" << fri->getUserId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(�ޱ�ע��)" << endl;
		}
		else cout <<"(��ע����"<< it->second << ")" << endl;
		cout << endl;
	}
}

/*----------------------------------Wechat------------------------------------------*/

WechatManageFriendLYC::WechatManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

WechatManageFriendLYC::~WechatManageFriendLYC() {}

void WechatManageFriendLYC::addFriend() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << "������������ӵĺ���΢��id��";
	getline(cin, key);
	//��������Լ�Ϊ����
	if (key.compare(w_user->getWechatId()) == 0) {
		cout << "�㲻������Լ�Ϊ���ѣ�" << endl;
		return;
	}
	if (WechatUserCollections::getUser(key) == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "���û��Ѿ�����ĺ�����" << endl;
	}
	else {
		string remark;
		cout << "������ѵı�ע������Ҳ���Բ����룬���ޱ�ע����";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "��Ӻ��ѳɹ���" << endl;
	}
}

void WechatManageFriendLYC::searchFriend() {
	cout << "���������΢��id��";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "����û�������ĺ��ѣ�" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "��������ϣ��ִ�еĲ�����" << endl;
	cout << endl;
	cout << "====1.��ѯ��ϸ��Ϣ====" << endl;
	cout << endl;
	cout << "=====2.�޸ı�ע��=====" << endl;
	cout << endl;
	cout << "=====3.ɾ���ú���=====" << endl;
	cout << endl;
	cout << "======= 0.���� =======" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "������ϸ��Ϣ��" << endl;
		fri = (WechatUserLYC*)WechatUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "�����±�ע����";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "�޸ĳɹ���" << endl;
		break;
	case 3:
		cout << "ȷ��Ҫɾ���ú�����" << endl;
		cout << "1.ɾ��\t0.�ٿ���һ�¡���" << endl;
		cout << "���������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "ɾ�����ѳɹ���" << endl;
			}
			break;
		default:
			cout << "�Բ������������д���" << endl;
		}
		break;
	default:
		cout << "�Բ������������д���" << endl;
	}
}

void WechatManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "����δ����κκ���" << endl;
		return;
	}
	cout << "========�����б�========" << endl;
	cout << endl;
	cout << "\tid\t�ǳ�" << endl;
	//����map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = (WechatUserLYC*)WechatUserCollections::getUser(it->first);
		cout << "\t" << fri->getWechatId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(�ޱ�ע��)" << endl;
		}
		else cout << "(��ע����" << it->second << ")" << endl;
		cout << endl;
	}
}

/*----------------------------------Weibo-----------------------------------------*/

WeiboManageFriendLYC::WeiboManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

WeiboManageFriendLYC::~WeiboManageFriendLYC() {}

void WeiboManageFriendLYC::addFriend() {
	cout << "������������ӵĺ���id��";
	getline(cin, key);
	//��������Լ�Ϊ����
	if (key.compare(user->getUserId()) == 0) {
		cout << "�㲻������Լ�Ϊ���ѣ�" << endl;
		return;
	}
	if (WeiboUserCollections::getUser(key) == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "���û��Ѿ�����ĺ�����" << endl;
	}
	else {
		string remark;
		cout << "������ѵı�ע������Ҳ���Բ����룬���ޱ�ע����";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "��Ӻ��ѳɹ���" << endl;
	}
}

void WeiboManageFriendLYC::searchFriend() {
	cout << "���������id��";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "����û�������ĺ��ѣ�" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "��������ϣ��ִ�еĲ�����" << endl;
	cout << endl;
	cout << "====1.��ѯ��ϸ��Ϣ====" << endl;
	cout << endl;
	cout << "=====2.�޸ı�ע��=====" << endl;
	cout << endl;
	cout << "=====3.ɾ���ú���=====" << endl;
	cout << endl;
	cout << "======= 0.���� =======" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "������ϸ��Ϣ��" << endl;
		fri = WeiboUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "�����±�ע����";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "�޸ĳɹ���" << endl;
		break;
	case 3:
		cout << "ȷ��Ҫɾ���ú�����" << endl;
		cout << "1.ɾ��\t0.�ٿ���һ�¡���" << endl;
		cout << "���������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "ɾ�����ѳɹ���" << endl;
			}
			break;
		default:
			cout << "�Բ������������д���" << endl;
		}
		break;
	default:
		cout << "�Բ������������д���" << endl;
	}
}

void WeiboManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "����δ����κκ���" << endl;
		return;
	}
	cout << "========�����б�========" << endl;
	cout << endl;
	cout << "\tid\t�ǳ�" << endl;
	//����map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = WeiboUserCollections::getUser(it->first);
		cout << "\t" << fri->getUserId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(�ޱ�ע��)" << endl;
		}
		else cout << "(��ע����" << it->second << ")" << endl;
		cout << endl;
	}
}