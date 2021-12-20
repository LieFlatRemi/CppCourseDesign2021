#include"MenuView.h"

Client::Client() {
	menu = NULL;
	while (true) {
		system("cls");
		cout << "=========== 1.QQ ============" << endl;
		cout << endl;
		cout << "========= 2.Wechat ==========" << endl;
		cout << endl;
		cout << "========== 3.Weibo ==========" << endl;
		cout << endl;
		cout << "========== 0.�˳� ===========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << endl;
			cout << "��ӭ�´�ʹ�ã�" << endl;
			return;
		case 1:
			menu = new QQViewLYC("");
			break;
		case 2:
			menu = new WechatViewLYC("");
			break;
		case 3:
			menu = new WeiboViewLYC("");
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

Client::~Client() {}

MenuViewLYC::MenuViewLYC() {
	user = NULL;
	manageFriend = NULL;
	manageGroup = NULL;
	manageUserMsg = NULL;
}

MenuViewLYC::~MenuViewLYC() {}

void MenuViewLYC::showUserMsgMenu() {				//���������Ϣ
	while (true) {
		system("cls");
		cout << "======== ������Ϣ���� =========" << endl;
		cout << endl;
		cout << "======= 1.�鿴�������� ========" << endl;
		cout << endl;
		cout << "======= 2.�޸ĸ������� ========" << endl;
		cout << endl;
		cout << "======== 3.�޸����� ==========" << endl;
		cout << endl;
		cout << "===== 4.��ͨ����ƽ̨�˺� ======" << endl;
		cout << endl;
		cout << "========== 0.�˳� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳����˹������" << endl;
			return;
		case 1:
			cout << endl;
			manageUserMsg->showDetailedData();
			break;
		case 2:
			manageUserMsg->changeUserData();
			break;
		case 3:
			manageUserMsg->changePasswd();
			break;
		case 4:
			manageUserMsg->registerOtherUser();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

//���ѹ������
void MenuViewLYC::showFriendMenu() {
	while (true) {
		system("cls");
		cout << "========== ���ѹ��� ==========" << endl;
		cout << endl;
		cout << "======== 1.��Ӻ��� ==========" << endl;
		cout << endl;
		cout << "======== 2.�޸ı�ע ==========" << endl;
		cout << endl;
		cout << "======= 3.�鿴�����б� =======" << endl;
		cout << endl;
		cout << "======== 4.��ѯ���� ==========" << endl;
		cout << endl;
		cout << "======== 5.ɾ������ ==========" << endl;
		cout << endl;
		cout << "======= 6.��ȡ�Ƽ����� ========" << endl;
		cout << endl;
		cout << "========== 0.���� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳����ѹ�����档��" << endl;
			return;
		case 1:				//��Ӻ���
			manageFriend->addFriend();
			break;
		case 2:				//�޸ı�ע
			manageFriend->setFriendRemark();
			break;
		case 3:				//��ѯ���к���
			manageFriend->getAllFriends();
			break;
		case 4:				//��ѯ����
			manageFriend->searchFriend();
			break;
		case 5:				//ɾ������
			manageFriend->deleteFriend();
			break;
		case 6:
			user->getRecoFriend();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

/*--------------------------------QQ---------------------------------*/

QQViewLYC::QQViewLYC(string id) :MenuViewLYC() {
	//ͨ������Ӧ����֤��¼
	if (id.compare("") != 0) {
		user = QQUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	//�˺������¼
	while (true) {
		system("cls");
		cout << "============ QQ =============" << endl;
		cout << endl;
		cout << "======== 1.�û���¼ ==========" << endl;
		cout << endl;
		cout << "======== 2.�û�ע�� ==========" << endl;
		cout << endl;
		cout << "======== 0.�л�Ӧ�� ==========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== �˳�QQӦ�á��� ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

QQViewLYC::~QQViewLYC() {}

//�û�ע��
void QQViewLYC::registerMenu() {
	string name, pwd;
	cout << "�������û�����";
	getline(cin, name);
	cout << endl;
	cout << "���������룺";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "�û�������Ϊ�գ�" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "���벻��Ϊ�գ�" << endl;
		return;
	}
	QQUserCollections::addUser(name, pwd);
	cout << "�û�ע��ɹ���" << endl;
	cout << "�û�id��" << QQUserCollections::nextRegisterId - 1 << endl;
}

//�û���¼
bool QQViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "�������û�id��" ;
	getline(cin, id);
	cout << "���������룺" ;
	getline(cin, pwd);
	bool isCorrent = true;
	user = QQUserCollections::getUser(id);
	if (user == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "�������" << endl;
		isCorrent = false;
	}
	//��¼�ɹ�
	if (isCorrent) {	
		return userMenu(user);
	}
	return true;
}

bool QQViewLYC::userMenu(UserLYC* user) {
	cout << endl;
	cout << "��¼�ɹ���" << endl;
	cout << "��ӭ�û�:" << user->getNickName() <<
		"(id:" << user->getUserId() << ")��¼QQ" << endl;
	cout << endl;
	cout << "�밴�������������" << endl;
	getline(cin, key);
	//��ʼ���¼��˵�ָ��
	manageUserMsg = new ManageUserMsgLYC(user);
	manageFriend = new QQManageFriendLYC(user);
	manageGroup = new QQManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============== QQ ===============" << endl;
		cout << endl;
		cout << "========== �û�id:" + user->getUserId() + "==========" << endl;
		cout << endl;
		cout << "========== 1.������� ===========" << endl;
		cout << endl;
		cout << "========== 2.����Ⱥ�� ===========" << endl;
		cout << endl;
		cout << "========= 3.������Ϣ���� ========" << endl;
		cout << endl;
		cout << "========== 4.�л�Ӧ�� ===========" << endl;
		cout << endl;
		cout << "========== 0.�˳���¼ ===========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//�˳���¼
			cout << "=======�û� : " << user->getUserId() << "���˳���¼��=====" << endl;
			return true;
		case 1:				//������ѹ���˵�
			showFriendMenu();
			break;
		case 2:				//����Ⱥ�Ĺ���˵�
			showGroupMenu();
			break;
		case 3:				//�����û�������Ϣ����˵�
			showUserMsgMenu();
			break;
		case 4:				//�л�Ӧ��
			if (changeApp())	return false;
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
	return true;
}

//Ⱥ����
void QQViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "========== QQȺ���� ===========" << endl;
		cout << endl;
		cout << "========= 1.���Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 2.�˳�Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 3.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 4.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "==========  0.���� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳�Ⱥ�Ĺ�����档��" << endl;
			return;
		case 1:				//����Ⱥ��
			manageGroup->addGroup();
			break;
		case 2:				//�˳�Ⱥ��
			manageGroup->dropGroup();
			break;
		case 3:				//����Ⱥ��
			manageGroup->administerGroup();
			break;
		case 4:				//����Ⱥ��
			manageGroup->createGroup();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

//�л�Ӧ�ã�����Ӧ�ü�ȷ�Ϻ���Ϊ�Զ���¼
bool QQViewLYC::changeApp() {
	QQUserLYC* q_user = (QQUserLYC*)user;
	WechatUserLYC* w_user = NULL;
	cout << endl;
	cout << "ѡ���л�������Ӧ�ã�" << endl;
	cout << "1.΢��\t2.΢��\t0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		//û�а�΢��
		if (!q_user->getIsBind()) {
			cout << "��ǰQQ�˺Ų�δ��΢�ţ�" << endl;
		}
		else {
			w_user = (WechatUserLYC*)WechatUserCollections::getBindUser(q_user->getUserId());
			cout << "����¼΢��id��" << w_user->getWechatId() << "�˺Ų��л���΢�Ž���" << endl;
			cout << endl;
			cout << "\t1.ȷ��\t0.ȡ��" << endl;
			cout << endl;
			cout << "���������ѡ��";
			getline(cin, key);
			switch(Tools::getStringChoice(key))
			{
			case 0:
				cout << endl;
				cout << "��ȡ��Ӧ���л�" << endl;
				return false;
			case 1:
				new WechatViewLYC(w_user->getWechatId());
				return true;
			default:
				cout << endl;
				cout << "���������д������������룡" << endl;
				break;
			}
		}
		break;
	case 2:
		cout << endl;
		//û�п�ͨ΢��
		if (WeiboUserCollections::getUser(q_user->getUserId()) == NULL) {
			cout << "��idδ��ͨ΢���û���" << endl;
		}
		else {
			cout << "����¼΢��id��" << q_user->getUserId() << "�˺Ų��л���΢������" << endl;
			cout << "\t1.ȷ��\t0.ȡ��" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "��ȡ��Ӧ���л�" << endl;
				return false;
			case 1:
				new WeiboViewLYC(q_user->getUserId());
				return true;
			default:
				cout << "���������д������������룡" << endl;
				break;
			}
		}
		break;
	default:
		cout << "���������д������������룡" << endl;
		break;
	}
	return false;
}

/*--------------------------------Wechat---------------------------------*/

WechatViewLYC::WechatViewLYC(string id) :MenuViewLYC() {
	//ͨ������Ӧ����֤��¼
	if (id.compare("") != 0) {
		user = WechatUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	while (true) {
		system("cls");
		cout << "========== Wechat ===========" << endl;
		cout << endl;
		cout << "======== 1.�û���¼ ==========" << endl;
		cout << endl;
		cout << "======== 2.�û�ע�� ==========" << endl;
		cout << endl;
		cout << "======== 0.�л�Ӧ�� ==========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== �˳�WechatӦ�á��� ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

WechatViewLYC::~WechatViewLYC() {}

//�û�ע��
void WechatViewLYC::registerMenu() {
	string name, pwd;
	cout << "�������û�����";
	getline(cin, name);
	cout << endl;
	cout << "���������룺";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "�û�������Ϊ�գ�" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "���벻��Ϊ�գ�" << endl;
		return;
	}
	WechatUserCollections::addUser(name, pwd);
	cout << "�û�ע��ɹ���" << endl;
	cout << "�û�id��" << WechatUserCollections::nextWcId - 1 << endl;
}

//�û���¼
bool WechatViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "�������û�id��";
	getline(cin, id);
	cout << "���������룺";
	getline(cin, pwd);
	bool isCorrent = true;
	user = WechatUserCollections::getUser(id);
	if (user == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "�������" << endl;
		isCorrent = false;
	}
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	//��¼�ɹ�
	if (isCorrent) {
		return userMenu(user);
	}
	return true;
}

bool WechatViewLYC::userMenu(UserLYC* user) {
	WechatUserLYC* w_user = (WechatUserLYC*)user;			//����ת��
	cout << endl;
	cout << "��¼�ɹ���" << endl;
	cout << "��ӭ�û�:" << user->getNickName() <<
		"(id:" << w_user->getWechatId() << ")��¼΢��" << endl;
	cout << endl;
	cout << "�밴�������������" << endl;
	getline(cin, key);
	//��ʼ���¼��˵�ָ��
	manageUserMsg = new WechatManageUserMsgLYC(user);
	manageFriend = new WechatManageFriendLYC(user);
	manageGroup = new WechatManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============= Wechat =============" << endl;
		cout << endl;
		cout << "========== �û�id:" + w_user->getWechatId() + "===========" << endl;
		cout << endl;
		cout << "========== 1.������� ===========" << endl;
		cout << endl;
		cout << "========== 2.����Ⱥ�� ===========" << endl;
		cout << endl;
		cout << "======== 3.������Ϣ���� =========" << endl;
		cout << endl;
		cout << "========== 4.�л�Ӧ�� ===========" << endl;
		cout << endl;
		cout << "========== 0.�˳���¼ ===========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//�˳���¼
			cout << "=======�û� : " << w_user->getWechatId() << "���˳���¼��=====" << endl;
			return true;
		case 1:				//������ѹ���˵�
			showFriendMenu();
			break;
		case 2:				//����Ⱥ�Ĺ���˵�
			showGroupMenu();
			break;
		case 3:				//�����û�������Ϣ����˵�
			showUserMsgMenu();
			break;
		case 4:				//�л�Ӧ��
			if (changeApp())		return false;
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
	return true;
}

//Ⱥ����
void WechatViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "======== WechatȺ���� =========" << endl;
		cout << endl;
		cout << "====== 1.�����û�����Ⱥ�� ======" << endl;
		cout << endl;
		cout << "========= 2.�˳�Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 3.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 4.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "==========  0.���� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳�Ⱥ�Ĺ�����档��" << endl;
			return;
		case 1:				//����Ⱥ��
			manageGroup->addGroup();
			break;
		case 2:				//�˳�Ⱥ��
			manageGroup->dropGroup();
			break;
		case 3:				//����Ⱥ��
			manageGroup->administerGroup();
			break;
		case 4:				//����Ⱥ��
			manageGroup->createGroup();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

void WechatViewLYC::showUserMsgMenu() {				//���������Ϣ
	WechatManageUserMsgLYC* w_manageUserMsg = (WechatManageUserMsgLYC*)manageUserMsg;
	while (true) {
		system("cls");
		cout << "======== ������Ϣ���� =========" << endl;
		cout << endl;
		cout << "======= 1.�鿴�������� ========" << endl;
		cout << endl;
		cout << "======= 2.�޸ĸ������� ========" << endl;
		cout << endl;
		cout << "======== 3.�޸����� ==========" << endl;
		cout << endl;
		cout << "===== 4.��ͨ����ƽ̨�˺� ======" << endl;
		cout << endl;
		cout << "===== 5.��QQ�˺Ź��� ========" << endl;
		cout << endl;
		cout << "========== 0.�˳� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳����˹������" << endl;
			return;
		case 1:
			cout << endl;
			manageUserMsg->showDetailedData();
			break;
		case 2:
			manageUserMsg->changeUserData();
			break;
		case 3:
			manageUserMsg->changePasswd();
			break;
		case 4:
			manageUserMsg->registerOtherUser();
			break;
		case 5:				//��qq�˺Ź���
			w_manageUserMsg->manageBind();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

bool WechatViewLYC::changeApp() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << endl;
	//û�а�QQ���ܵ�¼����Ӧ��
	if (w_user->getUserId().compare("") == 0) {
		cout << "���˺���δ��QQ�󶨣��޷��л�Ӧ�ã�" << endl;
		return false;
	}
	cout << "ѡ���л�������Ӧ�ã�" << endl;
	cout << "1.QQ\t2.΢��\t0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		cout << "����¼QQ id��" << w_user->getUserId() << "�˺Ų��л���QQ����" << endl;
		cout << endl;
		cout << "\t1.ȷ��\t0.ȡ��" << endl;
		cout << endl;
		cout << "���������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 0:
			cout << endl;
			cout << "��ȡ��Ӧ���л�" << endl;
			return false;
		case 1:
			new QQViewLYC(w_user->getUserId());
			return true;
		default:
			cout << endl;
			cout << "���������д������������룡" << endl;
			break;
		}
		break;
	case 2:
		cout << endl;
		//û�п�ͨ΢��
		if (WeiboUserCollections::getUser(w_user->getUserId()) == NULL) {
			cout << "��idδ��ͨ΢���û���" << endl;
		}
		else {
			cout << "����¼΢��id��" << w_user->getUserId() << "�˺Ų��л���΢������" << endl;
			cout << "\t1.ȷ��\t0.ȡ��" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "��ȡ��Ӧ���л�" << endl;
				return false;
			case 1:
				new WeiboViewLYC(w_user->getUserId());
				return true;
			default:
				cout << "���������д������������룡" << endl;
				break;
			}
		}
		break;
	default:
		cout << "���������д������������룡" << endl;
		break;
	}
	return false;
}

/*--------------------------------Weibo---------------------------------*/

WeiboViewLYC::WeiboViewLYC(string id) :MenuViewLYC() {
	//ͨ������Ӧ����֤��¼
	if (id.compare("") != 0) {
		user = WeiboUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	while (true) {
		system("cls");
		cout << "=========== Weibo ===========" << endl;
		cout << endl;
		cout << "======== 1.�û���¼ ==========" << endl;
		cout << endl;
		cout << "======== 2.�û�ע�� ==========" << endl;
		cout << endl;
		cout << "======== 0.�л�Ӧ�� ==========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== �˳�΢��Ӧ�á��� ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

WeiboViewLYC::~WeiboViewLYC() {}

//�û�ע��
void WeiboViewLYC::registerMenu() {
	string name, pwd;
	cout << "�������û�����";
	getline(cin, name);
	cout << endl;
	cout << "���������룺";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "�û�������Ϊ�գ�" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "���벻��Ϊ�գ�" << endl;
		return;
	}
	WeiboUserCollections::addUser(name, pwd);
	cout << "�û�ע��ɹ���" << endl;
	cout << "�û�id��" << QQUserCollections::nextRegisterId - 1 << endl;
}

//�û���¼
bool WeiboViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "�������û�id��";
	getline(cin, id);
	cout << "���������룺";
	getline(cin, pwd);
	bool isCorrent = true;
	user = WeiboUserCollections::getUser(id);
	if (user == NULL) {
		cout << "δ���ҵ����û���" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "�������" << endl;
		isCorrent = false;
	}
	//��¼�ɹ�
	if (isCorrent) {
		return userMenu(user);
	}
	return true;
}

bool WeiboViewLYC::userMenu(UserLYC* user) {
	cout << endl;
	cout << "��¼�ɹ���" << endl;
	cout << "��ӭ�û�:" << user->getNickName() <<
		"(id:" << user->getUserId() << ")��¼Weibo" << endl;
	cout << endl;
	cout << "�밴�������������" << endl;
	getline(cin, key);
	//��ʼ���¼��˵�ָ��
	manageUserMsg = new ManageUserMsgLYC(user);
	manageFriend = new WeiboManageFriendLYC(user);
	manageGroup = new WeiboManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============= Weibo =============" << endl;
		cout << endl;
		cout << "========== �û�id:" + user->getUserId() + "==========" << endl;
		cout << endl;
		cout << "========== 1.������� ===========" << endl;
		cout << endl;
		cout << "========== 2.����Ⱥ�� ===========" << endl;
		cout << endl;
		cout << "========= 3.������Ϣ���� ========" << endl;
		cout << endl;
		cout << "========== 4.�л�Ӧ�� ===========" << endl;
		cout << endl;
		cout << "========== 0.�˳���¼ ===========" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//�˳���¼
			cout << "=======�û� : " << user->getUserId() << "���˳���¼��=====" << endl;
			return true;
		case 1:				//������ѹ���˵�
			showFriendMenu();
			break;
		case 2:				//����Ⱥ�Ĺ���˵�
			showGroupMenu();
			break;
		case 3:				//�����û�������Ϣ����˵�
			showUserMsgMenu();
			break;
		case 4:				//�л�Ӧ��
			if (changeApp())		return false;
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
	return true;
}

//Ⱥ����
void WeiboViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "========== ΢��Ⱥ���� ==========" << endl;
		cout << endl;
		cout << "====== 1.�����û�����Ⱥ�� ======" << endl;
		cout << endl;
		cout << "========= 2.�˳�Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 3.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "========= 4.����Ⱥ�� ==========" << endl;
		cout << endl;
		cout << "==========  0.���� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "�˳�Ⱥ�Ĺ�����档��" << endl;
			return;
		case 1:				//����Ⱥ��
			manageGroup->addGroup();
			break;
		case 2:				//�˳�Ⱥ��
			manageGroup->dropGroup();
			break;
		case 3:				//����Ⱥ��
			manageGroup->administerGroup();
			break;
		case 4:				//����Ⱥ��
			manageGroup->createGroup();
			break;
		default:
			cout << "�Բ������������д���" << endl;
			break;
		}
		cout << endl;
		cout << "�밴�������������" << endl;
		getline(cin, key);
	}
}

bool WeiboViewLYC::changeApp() {
	cout << endl;
	//δ��ͨQQ�����л�
	if (QQUserCollections::getUser(user->getUserId()) == NULL) {
		cout << "��΢��ID��δ��ͨQQ���޷������û��л���" << endl;
		return false;
	}
	WechatUserLYC* w_user = NULL;
	cout << "ѡ���л�������Ӧ�ã�" << endl;
	cout << "1.QQ\t2.΢��\t0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		cout << "����¼QQ id��" << user->getUserId() << "�˺Ų��л���QQ����" << endl;
		cout << endl;
		cout << "\t1.ȷ��\t0.ȡ��" << endl;
		cout << endl;
		cout << "���������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 0:
			cout << endl;
			cout << "��ȡ��Ӧ���л�" << endl;
			return false;
		case 1:
			new QQViewLYC(user->getUserId());
			return true;
		default:
			cout << endl;
			cout << "���������д������������룡" << endl;
			break;
		}
		break;
	case 2:
		cout << endl;
		w_user = (WechatUserLYC*)WechatUserCollections::getBindUser(user->getUserId());
		//û�а�΢��
		if (w_user == NULL) {
			cout << "��idδ��΢���˺ţ�" << endl;
		}
		else { 
			cout << "����¼΢��id��" << w_user->getWechatId() << "�˺Ų��л���΢�Ž���" << endl;
			cout << "\t1.ȷ��\t0.ȡ��" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "��ȡ��Ӧ���л�" << endl;
				return false;
			case 1:
				new WechatViewLYC(w_user->getWechatId());
				return true;
			default:
				cout << "���������д������������룡" << endl;
				break;
			}
		}
		break;
	default:
		cout << "���������д������������룡" << endl;
		break;
	}
	return false;
}