
#include "FlightSystem.h"

////////////////////////////////////////////////
//	��������

// ��ӭ����
void ShowWelCome();
// ������
int MainMenu();
// �˳�ϵͳ
void Quit();

// ����������
FlightSystem  fs;

int main()
{
	// ��ʾ��ӭ����
	ShowWelCome();

	// ѭ����ȡ�û����룬�����û�ѡ��ִ�в�ͬ�Ĳ���
	while (true)
	{
		int nSel = MainMenu();

		cout << endl;

		switch (nSel)
		{
		case 1:
			// 1. ��ȡ��������
			fs.LoadFromFile();
			break;
		case 2:
			// 2. ���溽������
			fs.SaveToFile();
			break;
		case 3:
			// 3. ��Ӻ���
			fs.AddFlight();
			break;
		case 4:
			// 4. ɾ������
			fs.DelFlight();
			break;
		case 5:
			// 5. �޸ĺ���
			fs.ModFlight();
			break;
		case 6:
			// 6. ��������ȡ��֪ͨ
			fs.Delay();
			break;
		case 7:
			// 7. ��Ʊ����
			fs.BuyTicket();
			break;
		case 8:
			// 8. ��Ʊ����
			fs.RefundTicket();
			break;
		case 9:
			// 9. ������Ų�ѯ
			fs.SearchByFlight();
			break;
		case 10:
			// 10. ���𽵵ص��ѯ
			fs.SearchByAddress();
			break;
		case 11:
			// 11. ��ʾ���к�����Ϣ
			fs.SearchAllFlights();
			break;
		case 12:
			// 12. ��ʾ���й�Ʊ��Ϣ
			fs.SearchAllTickets();
			break;
		case 0:
			// �˳�ϵͳ
			Quit();
			break;
		default:
		{
			cout << "\t\t��������ȷ��ָ�" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		break;
		}

		cout << endl;

		system("pause");
		system("cls");
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// ��ӭ����
void ShowWelCome()
{
	cout << ("\n\n");
	cout << ("\t\t****************************************************\n");
	cout << ("\t\t*          ��ӭʹ��       �ɻ�Ʊ����ϵͳ           *\n");
	cout << ("\t\t*                                                  *\n");
	cout << ("\t\t*            * *     *  *                          *\n");
	cout << ("\t\t*          *     * *      *                        *\n");
	cout << ("\t\t*          *              *      ���ߣ� XXX        *\n");
	cout << ("\t\t*           *           *                          *\n");
	cout << ("\t\t*              *      *                            *\n");
	cout << ("\t\t*                 *                                *\n");
	cout << ("\t\t****************************************************\n");
	cout << ("\n\n");

	system("pause");

	system("cls");
}

////////////////////////////////////////////////////////////////////////////////
// ���˵�
int MainMenu()
{
	cout << ("\n\t\t+==============================================================+\n");
	cout << ("\t\t+                  �ɻ�Ʊ����ϵ  ���˵�                        +\n");
	cout << ("\t\t+==============================================================+\n");
	cout << ("\t\t+ �����������Ϣ����                                         +\n");
	cout << ("\t\t+     1. ��ȡ�����ļ�       2. ���溽���ļ�                    +\n");
	cout << ("\t\t+     3. ��Ӻ���           4. ɾ������        5. �޸ĺ���     +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ �����ද̬����                                             +\n");
	cout << ("\t\t+     6. ��������ȡ��֪ͨ                                      +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ ��Ʊ�����                                                 +\n");
	cout << ("\t\t+     7. ��Ʊ����           8. ��Ʊ����                        +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ ��Ʊ���ѯ��                                                 +\n");
	cout << ("\t\t+     9. ������Ų�ѯ       10. ���𽵵ز�ѯ                   +\n");
	cout << ("\t\t+     11. ��ʾ���к���      12. ��ʾ���й�Ʊ��Ϣ               +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ 0. �˳�ϵͳ                                                  +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");

	cout << ("\t\t+ �������Ĺ���ѡ����ţ�");

	int nSel = 0;
	scanf("%d", &nSel);

	return nSel;
}

/////////////////////////////////////////////////
// �˳�ϵͳ
void Quit()
{
	int ch;

	while (1)
	{
		cout << ("\t\t���Ƿ�ȷ���˳���(1.�˳� 2.ȡ��):");

		cin >> ch;

		fflush(stdin);

		if (ch == 1)
		{
			cout << ("\t\tллʹ�ã�\n");
			system("pause");
			exit(0);
		}
		else if (ch == 2)
		{
			break;
		}
		else
		{
			cout << ("\t\t�������� ��\n");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}