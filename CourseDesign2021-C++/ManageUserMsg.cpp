#include"ManageUserMsg.h"
#include"Tools.h"
ManageUserMsgLYC::ManageUserMsgLYC(UserLYC* user) {
	this->user = user;
}

ManageUserMsgLYC::~ManageUserMsgLYC() {}

void ManageUserMsgLYC::showDetailedData() {
	cout << "�û���ϸ��Ϣ��" << endl;
	user->printDetailInfo();
}

void ManageUserMsgLYC::changeUserData() {
	cout << endl;
	cout << "== ѡ�������޸ĵ����ݣ�==" << endl;
	cout << endl;
	cout << "======== 1.�ǳ� ========" << endl;
	cout << endl;
	cout << "====== 2.�������� ======" << endl;
	cout << endl;
	cout << "======= 3.���ڵ� =======" << endl;
	cout << endl;
	cout << "====== 0.�����ϼ� ======" << endl;
	cout << endl;
	cout << "����������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << "�������޸ĺ���ǳƣ�" << endl;
		getline(cin, key);
		if (key.compare("") == 0) {
			cout << endl;
			cout << "�ǳƲ���Ϊ�գ�" << endl;
			return;
		}
		else user->setNickName(key);
		break;
	case 2:
		cout << "�������޸ĺ������(������ʽ:xxxx.xx.xx)��" << endl;
		getline(cin, key);
		//�������Ϸ�
		if (!Tools::isBirthFormat(key)) {
			cout << "���벻���ϸ�ʽ���޸�ʧ�ܣ�" << endl;
			return;
		}
		user->setBirth(key);
		break;
	case 3:
		cout << "�������޸ĺ�ĵ�ַ��" << endl;
		getline(cin, key);
		user->setAddress(key);
		break;
	default:
		cout << "�Բ���������������" << endl;
		return;
	}
	cout << "�޸ĳɹ���" << endl;
}

void ManageUserMsgLYC::changePasswd() {
	string oldPasswd;
	cout << "��������룺";
	getline(cin, oldPasswd);
	cout << "���������룺";
	getline(cin, key);
	if (oldPasswd.compare(user->getPasswd()) != 0) {
		cout << "��������������޸�ʧ�ܣ�" << endl;
	}
	else if (Tools::isEmptyString(key)) {
		cout << "�����벻��Ϊ�գ��޸�ʧ�ܣ�" << endl;
	}
	else {
		user->setPasswd(key);
		cout << "�����޸ĳɹ���" << endl;
	}
}

//��ͨ����ƽ̨�û�
void ManageUserMsgLYC::registerOtherUser() {
	string name;
	string pwd;
	WechatUserLYC* w_user = NULL;
	QQUserLYC* q_user = NULL;
	cout << endl;
	cout << "ѡ��ͨƽ̨��" << endl;
	cout << endl;
	cout << "1.QQ\t2.΢��\t3.΢��\t0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	cout << endl;
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		//��id�Ѿ���ͨ
		if (QQUserCollections::getUser(user->getUserId()) != NULL) {
			cout << "��id�ѿ�ͨQQ�˺ţ�" << endl;
		}
		else {
			cout << "��ͨQQ�û�" << endl;
			cout << "����QQ�˺ŵ��û�����";
			getline(cin, name);
			cout << "����QQ�˺ŵ����룺";
			getline(cin, pwd);
			cout << endl;
			//�жϺϷ��ԣ���ע�Ჿ����ͬ
			if (name.compare("") == 0) {
				cout << "�û�������Ϊ�գ�" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "���벻��Ϊ�գ�" << endl;
				return;
			}
			QQUserCollections::addUserFromFile(name, pwd, user->getUserId());
			cout << "��ͨQQ�˺ųɹ���" << endl;
		}
		break;
	case 2:
		//���ȿ�ͨ��ǰid��QQ�˺ţ�֮����ܿ�ͨ΢���˺�
		//�жϵ�ǰid�Ƿ����΢�ţ����������Ϊ�Ѿ���ͨ��΢���˺�
		q_user = (QQUserLYC*)QQUserCollections::getUser(user->getUserId());
		if (q_user == NULL) {								//qq�˺Ų�����
			cout << "���ȿ�ͨ��id��QQ�˺ţ�" << endl;
		}
		else if (q_user->getIsBind()) {						//qq�˺��Ѿ���΢�ź�
			cout << "��ǰid�Ѿ�����΢���˺ţ�" << endl;
		}
		else {
			cout << "��ͨ΢���û�" << endl;
			cout << "����΢���˺ŵ��û�����";
			getline(cin, name);
			cout << "����΢���˺ŵ����룺";
			getline(cin, pwd);
			cout << endl;
			//�жϺϷ��ԣ���ע�Ჿ����ͬ
			if (name.compare("") == 0) {
				cout << "�û�������Ϊ�գ�" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "���벻��Ϊ�գ�" << endl;
				return;
			}
			WechatUserCollections::addUser(name, pwd);
			//���ð����
			string wid = to_string(WechatUserCollections::nextWcId - 1);
			w_user = (WechatUserLYC*)WechatUserCollections::getUser(wid);
			w_user->bindWithQQ(q_user->getUserId());
			cout << "��ͨ΢���˺ųɹ���" << endl;
			cout << "΢��id��" << wid << endl;
		}
		break;
	case 3:
		if (WeiboUserCollections::getUser(user->getUserId()) != NULL) {
			cout << "��id�ѿ�ͨ΢���˺ţ�" << endl;
		}
		else {
			cout << "��ͨ΢���û�" << endl;
			cout << "����΢���˺ŵ��û�����";
			getline(cin, name);
			cout << "����΢���˺ŵ����룺";
			getline(cin, pwd);
			cout << endl;
			//�жϺϷ��ԣ���ע�Ჿ����ͬ
			if (name.compare("") == 0) {
				cout << "�û�������Ϊ�գ�" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "���벻��Ϊ�գ�" << endl;
				return;
			}
			WeiboUserCollections::addUserFromFile(name, pwd, user->getUserId());
			cout << "��ͨ΢���˺ųɹ���" << endl;
		}
		break;
	default:
		cout << "���������д������������룡" << endl;
		break;
	}
}

WechatManageUserMsgLYC::WechatManageUserMsgLYC(UserLYC* user) : ManageUserMsgLYC(user) {}

WechatManageUserMsgLYC::~WechatManageUserMsgLYC() {}

void WechatManageUserMsgLYC::registerOtherUser() {
	string name;
	string pwd;
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << endl;
	cout << "ѡ��ͨƽ̨��" << endl;
	cout << endl;
	cout << "1.QQ\t2.΢��\t0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	cout << endl;
	//�а��˺ŵ������ֱ���ð�idȥע�ᣬ��ʱ���Կ�ͨ΢��
	//�ް��˺ŵ�������൱��ע�����˺ţ���ʱֻ���ȿ�ͨQQ
	string id = user->getUserId();
	if (id.compare("") != 0) {			//�Ѿ�����qq�˺�
		switch (Tools::getStringChoice(key))
		{
		case 0:
			return;
		case 1:
			//�����˺ŵ�����£��ض��Ѿ���ͨQQ�˺�
			cout << "��΢���˺��Ѱ󶨶�ӦQQ�˺ţ�" << endl;
			break;
		case 2:
			if (WeiboUserCollections::getUser(id) != NULL) {
				cout << "��Ӧ��id�Ѿ���ͨ΢���˺ţ�" << endl;
			}
			else {
				//��ͨ΢���˺�
				cout << "��ͨ΢���û�" << endl;
				cout << "����΢���˺ŵ��û�����";
				getline(cin, name);
				cout << "����΢���˺ŵ����룺";
				getline(cin, pwd);
				cout << endl;
				//�жϺϷ��ԣ���ע�Ჿ����ͬ
				if (name.compare("") == 0) {
					cout << "�û�������Ϊ�գ�" << endl;
					return;
				}
				if (pwd.compare("") == 0) {
					cout << "���벻��Ϊ�գ�" << endl;
					return;
				}
				WeiboUserCollections::addUserFromFile(name, pwd, id);
				cout << "��ͨ΢���˺ųɹ���" << endl;
			}
			break;
		default:
			cout << "���������д������������룡" << endl;
			break;
		}
	}
	else {								//û�а�qq�˺�
		switch (Tools::getStringChoice(key))
		{
		case 0:
			return;
		case 1:
			cout << "��ͨQQ�û�" << endl;
			cout << "����QQ�˺ŵ��û�����";
			getline(cin, name);
			cout << "����QQ�˺ŵ����룺";
			getline(cin, pwd);
			cout << endl;
			//�жϺϷ��ԣ���ע�Ჿ����ͬ
			if (name.compare("") == 0) {
				cout << "�û�������Ϊ�գ�" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "���벻��Ϊ�գ�" << endl;
				return;
			}
			QQUserCollections::addUser(name, pwd);
			//��
			w_user->bindWithQQ(to_string(QQUserCollections::nextRegisterId - 1));
			cout << "��ͨQQ�˺ųɹ���" << endl;
			cout << "��΢�ź��Ѿ�����ע���QQ�˺ţ�" << w_user->getUserId() << "����" << endl;
			break;
		case 2:
			//û�а��˺ŵ�����£�ֻ���ȿ�ͨQQ�˺�
			cout << "���ȿ�ͨ��QQ�˺Ż����ע���QQ�˺ţ�" << endl;
			break;
		default:
			cout << "���������д������������룡" << endl;
			break;
		}
	}
	
}

void WechatManageUserMsgLYC::manageBind() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;				//����ת��
	QQUserLYC* bindUser = NULL;
	cout << endl;
	cout << "==== ���˺Ź��� ====" << endl;
	cout << endl;
	cout << "Ŀǰ��״̬��" << endl;
	cout << endl;
	if (user->getUserId().compare("") == 0) {
		cout << "��ǰ�˺���δ���κ�QQ�˺Ű�" << endl;
	}
	else cout << "��ǰ�˺Ű�QQ ID��" << user->getUserId() << endl;
	cout << endl;
	cout << "1.����QQ ID\t2.�뵱ǰQQ ID���\t0.����";
	cout << endl;
	cout << "���������ѡ��" << endl;
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		cout << "����������󶨵�QQ ID��";
		getline(cin, key);
		cout << endl;
		bindUser = (QQUserLYC*)QQUserCollections::getUser(key);
		if (bindUser == NULL) {
			cout << "δ���ҵ����û���" << endl;
			return;
		}
		else if (bindUser->getIsBind()) {
			cout << "��QQ ID��������΢���˺Ű󶨣�" << endl;
		}
		else {
			w_user->resetBind();
			w_user->bindWithQQ(key);
			cout << "��QQ�ɹ���" << endl;
		}
		break;
	case 2:
		if (w_user->getUserId().compare("") == 0) {
			cout << "��ǰδ��QQ ID�󶨣�" << endl;
		}
		else {
			cout << "�뵱ǰQQ ID���ɹ���" << endl;
			w_user->resetBind();
		}
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}