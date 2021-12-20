#include "ManageGroup.h"

ManageGroupLYC::ManageGroupLYC(UserLYC* user) {
	this->user = user;
}

ManageGroupLYC::~ManageGroupLYC() {}

/*===================================QQȺ=====================================*/
ManageChildGroupLYC::ManageChildGroupLYC(UserLYC* user, QQGroupLYC* father) :ManageGroupLYC(user) {
	this->father = father;
	while (true) {
		system("cls");
		cout << "========== QQ��Ⱥ���� ==========" << endl;
		cout << endl;
		cout << "====== 1.�����Ա������Ⱥ =======" << endl;
		cout << endl;
		cout << "========= 2.�˳���Ⱥ ==========" << endl;
		cout << endl;
		cout << "========= 3.������Ⱥ ==========" << endl;
		cout << endl;
		cout << "========= 4.������Ⱥ ==========" << endl;
		cout << endl;
		cout << "==========  0.���� ============" << endl;
		cout << endl;
		cout << "����������ѡ��";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			return;
		case 1:				
			addGroup();
			break;
		case 2:				
			dropGroup();
			break;
		case 3:				
			administerGroup();
			break;
		case 4:
			createGroup();
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

ManageChildGroupLYC::~ManageChildGroupLYC() {}

//QQ��Ⱥ�У�Ⱥ����������Ⱥ��Ա������Ⱥ
void ManageChildGroupLYC::addGroup() {
	cout << "��������ȺȺ�ţ�";
	getline(cin, key);
	cout << endl;
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�ڸ���Ⱥ�У�" << endl;
		return;
	}
	if (child->getHostId().compare(user->getUserId()) != 0) {
		cout << "��û�и���Ⱥ�Ĺ���Ȩ��" << endl;
		return;
	}
	else {
		cout << "���ҽ����" << endl;
		child->printInfo();
		cout << "�����������Ⱥ��Աid��";
		getline(cin, key);
		UserLYC* res = father->searchMember(key);
		if (res == NULL) {				//��ӵĳ�Ա�����Ѿ��Ǹ�Ⱥ�ĳ�Ա
			cout << "��Ⱥ���޸ó�Ա��" << endl;
		}
		else if (child->searchMember(res->getUserId()) != NULL) {
			cout << "���û��Ѿ��Ǵ���Ⱥ��Ա��" << endl;
		}
		else {
			child->addMember(res->getUserId());
			cout << "�ѳɹ�����id:" << res->getUserId() << "�û�������Ⱥ��" << endl;
		}
	}
}

void ManageChildGroupLYC::dropGroup() {
	cout << "���������˳���Ⱥ��Ⱥ�ţ�" << endl;
	getline(cin, key);
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ���ȺȺ��Ա" << endl;
		return;
	}
	cout << "ȷ���˳���Ⱥ��" << child->getName() << "?" << endl;
	cout << "1.�˳�" << endl;
	cout << "0.ȡ��" << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		child->removeMember(user->getUserId());
		if (user->getUserId().compare(child->getHostId()) == 0) {
			cout << "����������ȺȺ�����˳�����Ⱥ����ɢ" << endl;
			father->deleteChilds(child->getId());
		}
		cout << "��Ⱥ�ɹ���" << endl;
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}

void ManageChildGroupLYC::createGroup() {
	cout << "������Ⱥ����" << endl;
	getline(cin, key);
	cout << endl;
	father->createChilds(user->getUserId(),key);
	cout << "��Ⱥ�ɹ���" << endl;
	cout << "��Ⱥid��" << father->getChildId() - 1;
}

void ManageChildGroupLYC::administerGroup() {
	cout << "��������ȺȺ�ţ�";
	getline(cin, key);
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ���ȺȺ��Ա" << endl;
		return;
	}
	if (child->getHostId().compare(user->getUserId()) == 0) {
		//�鿴��Ա��������Ա��T�ˡ��޸���Ⱥ��
		while (true) {
			system("cls");
			cout << "Ⱥ������\t��Ⱥid��" << child->getId() << "\t��Ⱥ����" << child->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴��Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.������Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.�߳���Ⱥ��Ա" << endl;
			cout << endl;
			cout << "4.�޸���Ⱥ��" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				child->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = child->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id" << "\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T��
				cout << "����������T����Ⱥ��Աid��";
				getline(cin, key);
				if (child->searchMember(key) == NULL) {
					cout << "���û�������Ⱥ��" << endl;
				}
				else {
					//����T�Լ�
					if (child->getHostId().compare(key) == 0)	
						cout << "�����߳��Լ�������Ⱥ������" << endl;
					else {
						child->removeMember(key);
						cout << "�߳���Ⱥ��Ա�ɹ���" << endl;
					}
				}
				break;
			case 4:						//�޸�Ⱥ��
				cout << "�����µ���Ⱥ����";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "��Ⱥ������Ϊ�գ�" << endl;
				}
				else {
					child->setName(key);
					cout << "�޸���Ⱥ���ɹ���" << endl;
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
	else {
		cout << "���Ǹ���Ⱥ�ģ���ͨ��Ա" << endl;
		//�鿴��Ա��������Ա
		while (true) {
			system("cls");
			cout << "��ͨ��Ա����\t��Ⱥid��" << child->getId() << "\t��Ⱥ����" << child->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				child->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = child->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
}

QQManageGroupLYC::QQManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
	this->manageChildGroup = NULL;
}

QQManageGroupLYC::~QQManageGroupLYC() {}

void QQManageGroupLYC::addGroup() {			//QQȺ���������
	cout << "������Ⱥ�ţ�";
	getline(cin, key);
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	cout << "���ҽ����" << endl;
	group->printInfo();
	cout << endl;
	cout << "1.�����Ⱥ" << endl;
	cout << endl;
	cout << "0.����" << endl;
	cout << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	cout << endl;
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		//���ж��Ƿ��Ѿ���Ⱥ��Ա
		if (group->searchMember(user->getUserId()) != NULL) {
			cout << "���Ѿ���Ⱥ��Ա��" << endl;
			return;
		}
		group->addRequest(user->getUserId());
		cout << "�����Ⱥ�ɹ�����ȴ�����Ա��ˡ���" << endl;
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}

void QQManageGroupLYC::dropGroup() {
	cout << "���������˳�Ⱥ��Ⱥ�ţ�" << endl;
	getline(cin, key);
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	map<string, QQChildGroupLYC*>& childMap = group->getChildsMap();
	cout << "ȷ���˳�Ⱥ��" << group->getName() << "?" << endl;
	cout << "1.�˳�" << endl;
	cout << "0.ȡ��" << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		if (group->searchManager(user->getUserId()) != NULL) {		//������˳���Ⱥ���ǹ���Ա����ְ
			group->deleteManager(user->getUserId());
		}
		//��������Ⱥ���Ƴ��ó�Ա
		for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
			QQChildGroupLYC* child = it->second;
			child->removeMember(user->getUserId());
			//����ȺȺ�������
			if (child->getHostId().compare(user->getUserId()) == 0)
				childMap.erase(it++);
			else it++;
		}
		cout << "��Ⱥ�ɹ���" << endl;
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}

void QQManageGroupLYC::createGroup() {
	cout << "������Ⱥ����" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "Ⱥ��������Ϊ�գ�" << endl;
		return;
	}
	cout << endl;
	QQGroupCollections::addNewGroup(key, user->getUserId());
	cout << "��Ⱥ�ɹ���" << endl;
	cout << "��Ⱥ��id��" << QQGroupCollections::nextGroupId - 1 << endl;
}

void QQManageGroupLYC::administerGroup() {
	cout << "������Ⱥ�ţ�";
	getline(cin, key);
	cout << endl;
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);	//����ת��
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	map<string, QQChildGroupLYC*>& childMap = group->getChildsMap();	//��Ⱥmap
	//Ⱥ��
	if (group->getHostId().compare(user->getUserId()) == 0) {
		//�鿴��Ա��������Ա���������롢T�ˣ������Լ�������ӹ���Ա��ɾ������Ա���޸�Ⱥ����������Ⱥ
		while (true) {
			system("cls");
			cout << "Ⱥ������\tȺid��" << group->getId() << "\tȺ����"<< group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.������Ⱥ" << endl;
			cout << endl;
			cout << "4.�����Ⱥ����" << endl;
			cout << endl;
			cout << "5.�߳�Ⱥ��Ա" << endl;
			cout << endl;
			cout << "6.��ӹ���Ա" << endl;
			cout << endl;
			cout << "7.��������Ա" << endl;
			cout << endl;
			cout << "8.�޸�Ⱥ��" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//������Ⱥ
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			case 4:
				group->handleRequest();
				break;
			case 5:							//T��
				cout << "����������T����Ⱥ��Աid��";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "���û�����Ⱥ��" << endl;
				}
				else {
					//����T�Լ�
					if (group->getHostId().compare(key) == 0)	cout << "�����߳��Լ�������Ⱥ������" << endl;
					else {
						if (group->searchManager(key) != NULL) {		//���T�������ǹ���Ա����ְ
							group->deleteManager(key);
						}
						//��������Ⱥ���Ƴ��ó�Ա
						for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
							QQChildGroupLYC* child = it->second;
							child->removeMember(key);
							//����ȺȺ�������
							if (child->getHostId().compare(key) == 0)
								childMap.erase(it++);
							else it++;
						}
						group->removeMember(key);
						cout << "�߳���Ⱥ��Ա�ɹ���" << endl;
					}
				}
				break;
			case 6:						//��ӹ���Ա
				cout << "�����¹���Ա���û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else if (key.compare(user->getUserId()) == 0) {
					cout << "���Ǳ�ȺȺ�������ܳ�ΪȺ����Ա��" << endl;
				}
				else if (group->searchManager(key) != NULL) {
					cout << "���û��Ѿ���Ⱥ����Ա��" << endl;
				}
				else {
					group->addManager(key);
					cout << "�ѳɹ���id:" << key << "���û���Ϊ����Ա" << endl;
				}
				break;
			case 7:						//ɾ������Ա
				cout << "���������Ա�û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (group->searchManager(key) == NULL) {
					cout << "���û����Ǳ�Ⱥ�Ĺ���Ա" << endl;
				}
				else {
					group->deleteManager(key);
					cout << "�ѳɹ�����id:" << key << "�û��Ĺ���Ա�ʸ�" << endl;
				}
				break;
			case 8:						//�޸�Ⱥ��
				cout << "�����µ�Ⱥ����";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "��Ⱥ������Ϊ�գ�" << endl;
				}
				else {
					group->setName(key);
					cout << "�޸�Ⱥ���ɹ���" << endl;
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
	//����Ա
	else if (group->searchManager(user->getUserId())) {
		//�鿴��Ա��������Ա���������롢T�ˣ�ֻ��T��ͨ��Ա����������Ⱥ
		while (true) {
			system("cls");
			cout << "����Ա����\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.������Ⱥ" << endl;
			cout << endl;
			cout << "4.�����Ⱥ����" << endl;
			cout << endl;
			cout << "5.�߳�Ⱥ��Ա" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//������Ⱥ
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			case 4:							
				group->handleRequest();
				break;
			case 5:							//T��
				cout << "����������T����Ⱥ��Աid��";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "���û�����Ⱥ��" << endl;
				}
				else {
					//����TȺ������������Ա
					if (group->getHostId().compare(key) == 0)	cout << "�����߳�Ⱥ����" << endl;
					else if (user->getUserId().compare(key) == 0)	cout << "�����߳��Լ���" << endl;
					else if (group->searchManager(key))	cout << "�����߳���������Ա��" << endl;
					else {
						group->removeMember(key);
						//��������Ⱥ���Ƴ��ó�Ա
						for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
							QQChildGroupLYC* child = it->second;
							child->removeMember(key);
							//����ȺȺ�������
							if (child->getHostId().compare(key) == 0)
								childMap.erase(it++);
							else it++;
						}
						cout << "�߳���Ⱥ��Ա�ɹ���" << endl;
					}
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
	//��ͨ��Ա
	else {
		while (true) {
			system("cls");
			cout << "��ͨ��Ա����\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.������Ⱥ" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//������Ⱥ
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
}

/*-----------------------------Wechat-------------------------------------*/

WechatManageGroupLYC::WechatManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
	w_user = (WechatUserLYC*)user;
}

WechatManageGroupLYC::~WechatManageGroupLYC() {}

//΢��Ⱥ���������,���κ�Ⱥ��Ա�����������û���Ⱥ
void WechatManageGroupLYC::addGroup() {			
	cout << "������΢��ȺȺ�ţ�";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	else {
		cout << "���ҽ����" << endl;
		group->printInfo();
		if (group->searchMember(w_user->getWechatId()) == NULL) {
			cout << "�㲻�ڸ�΢��Ⱥ��" << endl;
			return;
		}
		cout << endl;
		cout << "������������û�id��";
		getline(cin, key);
		WechatUserLYC* res = (WechatUserLYC*)WechatUserCollections::getUser(key);
		if (res == NULL) {
			cout << "δ���ҵ����û���" << endl;
			return;
		}
		else if (group->searchMember(res->getWechatId()) != NULL) {
			cout << "���û��Ѿ��Ǵ�΢��Ⱥ��Ա��" << endl;
		}
		else {
			group->addMember(res->getWechatId());
			cout << "�ѳɹ�����id:" << res->getWechatId() << "�û�����΢��Ⱥ��" << endl;
		}
	}
}

void WechatManageGroupLYC::dropGroup() {
	cout << "���������˳�Ⱥ��Ⱥ�ţ�" << endl;
	getline(cin, key);
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(w_user->getWechatId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	cout << "ȷ���˳�Ⱥ��" << group->getName() << "?" << endl;
	cout << "1.�˳�" << endl;
	cout << "0.ȡ��" << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		cout << "��Ⱥ�ɹ���" << endl;
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}

void WechatManageGroupLYC::createGroup() {
	cout << "������Ⱥ����" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "Ⱥ��������Ϊ�գ�" << endl;
		return;
	}
	cout << endl;
	WechatGroupCollections::addNewGroup(key, w_user->getWechatId());
	cout << "��Ⱥ�ɹ���" << endl;
	cout << "��Ⱥ��id��" << WechatGroupCollections::nextGroupId - 1 << endl;
}

void WechatManageGroupLYC::administerGroup() {
	cout << "������Ⱥ�ţ�";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(w_user->getWechatId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	//Ⱥ��
	if (group->getHostId().compare(w_user->getWechatId()) == 0) {
		//�鿴��Ա��������Ա��T�ˣ������Լ������޸�Ⱥ��
		while (true) {
			system("cls");
			cout << "Ⱥ������\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.�߳�Ⱥ��Ա" << endl;
			cout << endl;
			cout << "4.�޸�Ⱥ��" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T��
				cout << "����������T����Ⱥ��Աid��";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "���û�����Ⱥ��" << endl;
				}
				else {
					//����T�Լ�
					if (group->getHostId().compare(key) == 0)	cout << "�����߳��Լ�������Ⱥ������" << endl;
					else {
						group->removeMember(key);
						cout << "�߳���Ⱥ��Ա�ɹ���" << endl;
					}
				}
				break;
			case 4:						//�޸�Ⱥ��
				cout << "�����µ�Ⱥ����";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "��Ⱥ������Ϊ�գ�" << endl;
				}
				else {
					group->setName(key);
					cout << "�޸�Ⱥ���ɹ���" << endl;
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
	//��ͨ��Ա
	else {
		while (true) {
			system("cls");
			cout << "��ͨ��Ա����\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
}

/*-----------------------------Weibo-------------------------------------*/

WeiboManageGroupLYC::WeiboManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
}

WeiboManageGroupLYC::~WeiboManageGroupLYC() {}

void WeiboManageGroupLYC::addGroup() {
	cout << "������΢��ȺȺ�ţ�";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	else {
		cout << "���ҽ����" << endl;
		group->printInfo();
		if (group->searchMember(user->getUserId()) == NULL) {
			cout << "�㲻�ڸ�΢��Ⱥ��" << endl;
			return;
		}
		if (group->getHostId().compare(user->getUserId()) != 0){
			cout << "�����Ǹ�ȺȺ�����������ԱȨ�ޣ�" << endl;
			return;
		}
		cout << endl;
		cout << "������������û�id��";
		getline(cin, key);
		UserLYC* res = WeiboUserCollections::getUser(key);
		if (res == NULL) {
			cout << "δ���ҵ����û���" << endl;
			return;
		}
		else if (group->searchMember(res->getUserId()) != NULL) {
			cout << "���û��Ѿ��Ǵ�΢��Ⱥ��Ա��" << endl;
		}
		else {
			group->addMember(res->getUserId());
			cout << "�ѳɹ�����id:" << res->getUserId() << "�û�����΢��Ⱥ��" << endl;
		}
	}
}

void WeiboManageGroupLYC::dropGroup() {
	cout << "���������˳�Ⱥ��Ⱥ�ţ�" << endl;
	getline(cin, key);
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	cout << "ȷ���˳�Ⱥ��" << group->getName() << "?" << endl;
	cout << "1.�˳�" << endl;
	cout << "0.ȡ��" << endl;
	cout << "���������ѡ��";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		cout << "��Ⱥ�ɹ���" << endl;
		break;
	default:
		cout << "�Բ������������д���" << endl;
		break;
	}
}

void WeiboManageGroupLYC::createGroup() {
	cout << "������Ⱥ����" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "Ⱥ��������Ϊ�գ�" << endl;
		return;
	}
	cout << endl;
	WeiboGroupCollections::addNewGroup(key, user->getUserId());
	cout << "��Ⱥ�ɹ���" << endl;
	cout << "��Ⱥ��id��" << WeiboGroupCollections::nextGroupId - 1 << endl;
}

void WeiboManageGroupLYC::administerGroup() {
	cout << "������Ⱥ�ţ�";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "�㲻�Ǹ�ȺȺ��Ա" << endl;
		return;
	}
	//Ⱥ��
	if (group->getHostId().compare(user->getUserId()) == 0) {
		//�鿴��Ա��������Ա��T�ˣ������Լ������޸�Ⱥ��
		while (true) {
			system("cls");
			cout << "Ⱥ������\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "3.�߳�Ⱥ��Ա" << endl;
			cout << endl;
			cout << "4.�޸�Ⱥ��" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T��
				cout << "����������T����Ⱥ��Աid��";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "���û�����Ⱥ��" << endl;
				}
				else {
					//����T�Լ�
					if (group->getHostId().compare(key) == 0)	cout << "�����߳��Լ�������Ⱥ������" << endl;
					else {
						group->removeMember(key);
						cout << "�߳���Ⱥ��Ա�ɹ���" << endl;
					}
				}
				break;
			case 4:						//�޸�Ⱥ��
				cout << "�����µ�Ⱥ����";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "��Ⱥ������Ϊ�գ�" << endl;
				}
				else {
					group->setName(key);
					cout << "�޸�Ⱥ���ɹ���" << endl;
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
	//��ͨ��Ա
	else {
		while (true) {
			system("cls");
			cout << "��ͨ��Ա����\tȺid��" << group->getId() << "\tȺ����" << group->getName() << endl;
			//�鿴��Ա��������Ա������Ⱥ
			cout << endl;
			cout << "1.�鿴Ⱥ��Ա" << endl;
			cout << endl;
			cout << "2.����Ⱥ��Ա" << endl;
			cout << endl;
			cout << "0.����" << endl;
			cout << endl;
			cout << "���������ѡ��" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//�鿴Ⱥ��Ա
				group->getMembers();
				cout << endl;
				break;
			case 2:							//����Ⱥ��Ա
				cout << "�����û�id��";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "Ⱥ���޴��û�" << endl;
				}
				else {
					cout << "���ҽ����" << endl;
					cout << "id\t�ǳ�" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "���������������������룡" << endl;
				break;
			}
			cout << endl;
			cout << "�밴�������������" << endl;
			getline(cin, key);
		}
	}
}