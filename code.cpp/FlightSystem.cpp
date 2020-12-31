#include "FlightSystem.h"



FlightSystem::FlightSystem()
{
}


FlightSystem::~FlightSystem()
{
}

////////////////////////////////////////////////
// 1. ���غ�������
bool FlightSystem::LoadFromFile()
{
	// ���ļ�׼����ȡ
	ifstream in(FLIGHT_FILE, ios::binary | ios::in);
	if (!in.is_open())
	{
		cout << ("\t\t���󣺶�ȡ���������ļ�ʧ�ܣ�\n");
		in.close();
		return false;
	}

	m_Flights.clear();

	// ���ȶ�ȡ�ܵ�����
	int nCount = 0;
	in >> nCount;

	// Ȼ��ѭ����ȡ���к�����Ϣ
	for (int i = 0; i < nCount; i++)
	{
		FLIGHT newFlight;

		in >> newFlight.strFlightID;
		in >> newFlight.strCompany;
		in >> newFlight.strStartCity;
		in >> newFlight.strEndCity;
		in >> newFlight.strTransitCity;
		in >> newFlight.TakeoffTime.tm_hour;
		in >> newFlight.TakeoffTime.tm_min;
		in >> newFlight.LandingTime.tm_hour;
		in >> newFlight.LandingTime.tm_min;
		in >> newFlight.nPrice; 
		in >> newFlight.nTicket;		

		// ��Ʊ�˿�
		int nGuest = 0;
		in >> nGuest;
		for (int j = 0; j < nGuest; j++)
		{
			GUEST newGuest;
			in >> newGuest.strID >> newGuest.strName >> newGuest.nCount;

			newFlight.Guests.push_back(newGuest);
		}
		
		// �Ⱥ�˿�
		int nWGuest = 0;
		in >> nWGuest;
		for (int k = 0; k < nWGuest; k++)
		{
			GUEST newWGuest;
			in >> newWGuest.strID >> newWGuest.strName >> newWGuest.nCount;

			newFlight.WaitingGuests.push_back(newWGuest);
		}

		m_Flights.push_back(newFlight);
	}

	in.close();
	cout << "\t\t��ȡ " << nCount << " ��������Ϣ���." << endl;

	return true;
}

////////////////////////////////////////////////
// 2. ���溽������
bool FlightSystem::SaveToFile()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return false;

	// ���ļ�׼��д��
	ofstream out(FLIGHT_FILE, ios::binary | ios::out | ios::trunc);
	if (!out.is_open())
	{
		cout << ("\t\t���������ļ�д��ʧ�ܣ�\n");
		out.close();
		return false;
	}

	// ����д���ܵ�����
	out << m_Flights.size() << endl;

	// Ȼ��ѭ��д�����к�����Ϣ
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		// ������Ϣ
		out << m_Flights[i].strFlightID << " " << m_Flights[i].strCompany << " " 
			<< m_Flights[i].strStartCity << " "	<< m_Flights[i].strEndCity << " "
			<< m_Flights[i].strTransitCity << " " 
			<< m_Flights[i].TakeoffTime.tm_hour << " " << m_Flights[i].TakeoffTime.tm_min << " "						
			<< m_Flights[i].LandingTime.tm_hour << " " << m_Flights[i].LandingTime.tm_min << " "
			<< m_Flights[i].nPrice << " " << m_Flights[i].nTicket
			<< endl;
		
		// ��Ʊ�˿�
		GUESTS& guests = m_Flights[i].Guests;
		out << guests.size() << endl;
		for (unsigned int j = 0; j < guests.size(); j++)
		{
			out << guests[j].strID << " " << guests[j].strName << " " << guests[j].nCount << endl;
		}

		// �Ⱥ�˿�
		WGUESTS& wguests = m_Flights[i].WaitingGuests;
		out << wguests.size() << endl;
		for (unsigned int k = 0; k < wguests.size(); k++)
		{
			out << wguests[k].strID << " " << wguests[k].strName << " " << wguests[k].nCount << endl;
		}
	}

	out.close();

	cout << "\t\t������Ϣͬ���� " << FLIGHT_FILE << " �����." << endl;

	return true;
}

////////////////////////////////////////////////
// 3. ��Ӻ���
void FlightSystem::AddFlight()
{
	FLIGHT newFlight;

	cout << "\t\t�����뺽��ţ�";
	cin >> newFlight.strFlightID;

	cout << "\t\t�����뺽�๫˾���ƣ�";
	cin >> newFlight.strCompany;

	cout << "\t\t�����뺽����ɳ��У�";
	cin >> newFlight.strStartCity;

	cout << "\t\t�����뺽�ൽ����У�";
	cin >> newFlight.strEndCity;

	cout << "\t\t�����뺽�ྭͣ�ص�(û�о�д���ޡ�)��";
	cin >> newFlight.strTransitCity;

	cout << "\t\t���������ʱ��(��ʽ 15:05 �֣�24Сʱ�ƣ�ע��һ��Ҫ��Ӣ�ĵ�ð��)��";
	scanf("%d:%d", &newFlight.TakeoffTime.tm_hour, &newFlight.TakeoffTime.tm_min);

	cout << "\t\t�����뵽��ʱ��(��ʽ 16:10 �֣�24Сʱ�ƣ�ע��һ��Ҫ��Ӣ�ĵ�ð��)��";
	scanf("%d:%d", &newFlight.LandingTime.tm_hour, &newFlight.LandingTime.tm_min);

	cout << "\t\t�����뺽��Ʊ�ۣ�";
	cin >> newFlight.nPrice;

	cout << "\t\t�����뺽�����Ʊ����";
	cin >> newFlight.nTicket;

	// ����µĺ�����Ϣ��˳�����
	m_Flights.push_back(newFlight);

	cout << "\t\t��Ӻ�����Ϣ�ɹ���" << endl;

	SaveToFile();
}

///////////////////////////////////////////////
// 4. ɾ������
void FlightSystem::DelFlight()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };

	cout << "\t\t��������Ҫɾ���ĺ����ţ�";
	cin >> strID;

	// ���Ҷ�Ӧ�Ŀγ̣�����ɾ��
	vector<FLIGHT>::iterator itr = m_Flights.begin();
	while (itr != m_Flights.end())
	{
		if (strcmp(strID, itr->strFlightID) == 0)
		{
			m_Flights.erase(itr);

			cout << "\t\tɾ��������Ϣ�ɹ���" << endl;

			SaveToFile();

			return;
		}
		else
		{
			++itr;
		}
	}

	cout << "\t\tû���ҵ��˼�¼��" << endl;
	return;
}

///////////////////////////////////////////////
// 5. �޸ĺ���
void FlightSystem::ModFlight()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t��������Ҫ�޸ĵĺ����ţ�";
	cin >> strID;

	// ���Ҷ�Ӧ�ĺ��࣬�����޸�
	int nIndex = GetFlightIndexByID(strID);

	if (nIndex < 0)
	{
		cout << "\t\t����û���ҵ��˼�¼��" << endl;
		return;
	}

	// ���м�¼�޸�
	FLIGHT& flight = m_Flights[nIndex];

	cout << "\t\t�����뺽��ţ�";
	cin >> flight.strFlightID;

	cout << "\t\t�����뺽�๫˾���ƣ�";
	cin >> flight.strCompany;

	cout << "\t\t�����뺽����ɳ��У�";
	cin >> flight.strStartCity;

	cout << "\t\t�����뺽�ൽ����У�";
	cin >> flight.strEndCity;

	cout << "\t\t�����뺽�ྭͣ�ص�(û�о�д���ޡ�)��";
	cin >> flight.strTransitCity;

	cout << "\t\t���������ʱ��(��ʽ 15:05 �֣�24Сʱ�ƣ�ע��һ��Ҫ��Ӣ�ĵ�ð��)��";
	scanf("%d:%d", &flight.TakeoffTime.tm_hour, &flight.TakeoffTime.tm_min);

	cout << "\t\t�����뵽��ʱ��(��ʽ 16:10 �֣�24Сʱ�ƣ�ע��һ��Ҫ��Ӣ�ĵ�ð��)��";
	scanf("%d:%d", &flight.LandingTime.tm_hour, &flight.LandingTime.tm_min);

	cout << "\t\t�����뺽��Ʊ�ۣ�";
	cin >> flight.nPrice;

	cout << "\t\t�����뺽�����Ʊ��";
	cin >> flight.nTicket;

	cout << "\t\t�޸ĺ�����Ϣ�ɹ���" << endl;

	SaveToFile();
}

///////////////////////////////////////////////
// 6. ��������ȡ��֪ͨ
void FlightSystem::Delay()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t����������Ҫ��������֪ͨ�ĺ���ţ�";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t����û���ҵ��˼�¼��" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	// �����Ƽ�����
	
	// ���ķ���ʱ��
	int nDiff = 9999;
	int nSelID = -1;
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		if (i == nFlightIndex 
			|| strcmp(flight.strStartCity,m_Flights[i].strStartCity)!=0
			|| strcmp(flight.strEndCity, m_Flights[i].strEndCity) != 0)
		{
			continue;
		}

		int nTemp = (m_Flights[i].TakeoffTime.tm_hour - flight.TakeoffTime.tm_hour) * 60 + (m_Flights[i].TakeoffTime.tm_min - flight.TakeoffTime.tm_min);
		if (nTemp > 0 && nTemp < nDiff)
		{
			nDiff = nTemp;
			nSelID = i;
		}
	}

	// ֪ͨ�������Ѿ���Ʊ�ĳ˿�
	GUESTS::iterator it = flight.Guests.begin();
	for (; it != flight.Guests.end();it++)
	{
		if (nSelID >= 0)
		{
			cout << "\n\t\t�𾴵� " << it->strName << " �˿ͣ��ܱ�Ǹ��֪ͨ����\n"
				<< " \t\t    �������� [" << flight.strFlightID << "] ���࣬�Ѿ�ȡ�����У��˴��Ƽ���������һ�� [" << m_Flights[nSelID].strFlightID << "]�� ����\n";
		}
		else
		{
			cout << "\n\t\t�𾴵� " << it->strName << " �˿ͣ��ܱ�Ǹ��֪ͨ����\n" 
				 << "\t\t    �������� [" << flight.strFlightID << "] ���࣬�Ѿ�ȡ�����У����ҽ����������������Ƽ����ǳ���Ǹ��\n";
		}
	}
}

//////////////////////////////////////////////
// 7. ��Ʊ����
void FlightSystem::BuyTicket()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t��������Ҫ��Ʊ�ĺ���ţ�";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t����û���ҵ��˼�¼��" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	int nBuyCount = 0;
	cout << "\t\t��������Ҫ��Ʊ��������";
	cin >> nBuyCount;

	// ��Ʊ������ֱ�ӹ���
	if (flight.nTicket > nBuyCount)
	{
		flight.nTicket -= nBuyCount;
		
		// ����ǰ�û���Ϣ����
		GUEST newGuest;
		newGuest.nCount = nBuyCount;
		cout << "\t\t���չ�˾��Ʊ�ɹ���" << endl;
		
		cout << "\t\t����������������";
		cin >> newGuest.strName;

		cout << "\t\t�������������֤�ţ�";
		cin >> newGuest.strID;

		flight.Guests.push_back(newGuest);

		// cout << "\t\t���Ѿ��ɹ�Ԥ�� [" << flight.strFlightID << "] ����� " << nBuyCount << " ��Ʊ��\n" << endl;

		cout << "\t\tԤ���ɹ�����Ʊ��Ϣ���£�" << endl;
		cout << "\t\t    ����ţ�" << flight.strFlightID << endl;
		cout << "\t\t    ��  ����" << newGuest.strName << endl;
		cout << "\t\t    ���֤��" << newGuest.strID << endl << endl;

		SaveToFile();

	}
	// ��Ʊ���������ԤԼ�Ŷ�
	else
	{
		int nWait = 0;

		cout << "\t\t�ú���ֻʣ�� " << flight.nTicket << " ��Ʊ�����Ƿ�ҪԤԼ�ȴ���(0.��  1.��)��";
		cin >> nWait;

		if (nWait == 0)
		{
			cout << "\t\tлл���Ļݹˣ�" << endl;
			return;
		}

		// ����ȴ�����

		GUEST newGuest;
		newGuest.nCount = nBuyCount;

		cout << "\t\t����������������";
		cin >> newGuest.strName;

		cout << "\t\t�������������֤�ţ�";
		cin >> newGuest.strID;

		flight.WaitingGuests.push_back(newGuest);

		cout << "\t\t���Ѿ��ɹ�ԤԼ [" << flight.strFlightID << "] ���࣬һ������Ʊ���Զ������µ�.\n" << endl;

		SaveToFile();
	}

}

//////////////////////////////////////////////
// 8. ��Ʊ����
void FlightSystem::RefundTicket()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t��������Ҫ��Ʊ�ĺ���ţ�";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t����û���ҵ��˼�¼��" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	int nRefCount = 0;
	char strGuestID[STR_LEN] = { 0 };
	cout << "\t\t�������������֤��Ϣ��";
	cin >> strGuestID;

	// �ӵ�ǰ����Ķ�Ʊ�������Ƴ��˿���
	bool bFind = false;
	GUESTS::iterator it = flight.Guests.begin();
	for (; it!= flight.Guests.end();)
	{
		if (strcmp(it->strID, strGuestID) == 0)
		{
			cout << "\t\t�𾴵� " << it->strName << "���ˣ�������Ʊ�Ѿ���������ɹ���\n" << endl;

			// �޸ĺ���ʣ��Ʊ��
			flight.nTicket += it->nCount;
			it = flight.Guests.erase(it);

			bFind = true;

			break;
		}
		else
		{
			++it;
		}
	}

	if (!bFind)
	{
		cout << "\t\t����û���ҵ��˿��˵Ķ�Ʊ��Ϣ.\n" << endl;
		return;
	}

	// Ϊ�ȴ��Ŀ����Զ���Ʊ
	while (flight.WaitingGuests.size()>0)
	{
		GUEST& wguest = flight.WaitingGuests.front();

		cout << "\t\t����Ϊ��һλԤԼ���� " << wguest.strName << " �Զ���Ʊ............\n\n";

		// ��ѯ��Ʊ�Ƿ��㹻
		cout << "\t\tĿǰ����ʣ�� " << flight.nTicket << " ��Ʊ��������Ҫ���� " << wguest.nCount << "��." << endl;
		if (flight.nTicket >= wguest.nCount)
		{
			flight.nTicket -= wguest.nCount;

			cout << "\t\t��Ʊ�ɹ�����Ʊ��Ϣ���£�" << endl;
			cout << "\t\t    ����ţ�" << flight.strFlightID << endl;
			cout << "\t\t    ��  ����" << wguest.strName << endl;
			cout << "\t\t    ���֤��" << wguest.strID << endl << endl;

			// �����˼��빺Ʊ�б���
			GUEST newGuest;
			newGuest.nCount = wguest.nCount;
			strcpy(newGuest.strID, wguest.strID);
			strcpy(newGuest.strName, wguest.strName);

			flight.Guests.push_back(newGuest);

			// �ӵȴ��������Ƴ��˿���
			flight.WaitingGuests.pop_front();
		}
		else
		{
			cout << "\t\t�ú���ֻʣ�� " << flight.nTicket << " ��Ʊ���޷������Զ���Ʊ.\n\n";
			break;
		}
	}

	SaveToFile();

}

/////////////////////////////////////////////
// 9. ������Ų�ѯ
void FlightSystem::SearchByFlight()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	// ��ѯ����
	char strID[STR_LEN] = { 0 };
	cout << "\t\t��������Ҫ��ѯ�ĺ���ţ�";
	cin >> strID;

	// ��ʾ������
	cout << ("\t\t��ѯ������£�") << endl << endl;

	// ����ʾ����
	cout << "\t\t";
	cout << setw(15) << "�����";
	cout << setw(15) << "������";
	cout << setw(15) << "�յ����";
	cout << setw(15) << "���ʱ��";
	cout << setw(15) << "����ʱ��";
	cout << setw(10) << "Ʊ��";
	cout << setw(10) << "��Ʊ";
	cout << endl;

	// ���ݲ�ѯ�������в���
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strID, flight.strFlightID) == 0)
		{
			cout << "\t\t";
			cout << setw(15) << flight.strFlightID;
			cout << setw(15) << flight.strStartCity;
			cout << setw(15) << flight.strEndCity;
			cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
			cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
			cout << setw(10) << flight.nPrice;
			cout << setw(10) << flight.nTicket;
			cout << endl;
		}
	}

}

/////////////////////////////////////////////
// 10. ���𽵵ص��ѯ
void FlightSystem::SearchByAddress()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	// ��ѯ����
	char strStart[STR_LEN] = { 0 };
	char strEnd[STR_LEN] = { 0 };
	
	cout << "\t\t��������Ҫ��ѯ�ĳ������У�";
	cin >> strStart;

	cout << "\t\t��������Ҫ��ѯ���յ���У�";
	cin >> strEnd;

	// �Ȼ�ȡ��ѯ�������
	int nResultCount = 0;
	unsigned int i = 0, j = 0;
	for (i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strStart, flight.strStartCity) == 0
			&& strcmp(strEnd, flight.strEndCity) == 0)
		{
			nResultCount++;
		}
	}

	// ѡ������ʽ
	SORT_TYPE SortType = SORT_NORMAL;
	if (nResultCount < 0)
	{
		cout << "\t\tû���ҵ���Ӧ�ĺ��࣡" << endl;
		return;
	}
	else if (nResultCount == 0)
	{
		SortType = SORT_NORMAL;
	}
	else
	{
		cout << "\t\t��ѯ�������������ѡ������ʽ (0.Ĭ��  1.��Ʊ��  2.������ʱ��  3.����Ʊ����)��";
		cin >> (int&)SortType;
	}

	// ���ݲ�ͬ������ʽ��������
	for (j = 0; j < m_Flights.size(); j++)
	{
		for (unsigned int k = 0; k < m_Flights.size(); k++)
		{
			bool bNeedExchange = false;

			if (SortType == SORT_BY_PRICE)
			{
				if (m_Flights[k].nPrice > m_Flights[j].nPrice)
				{
					bNeedExchange = true;
				}
			}
			else if(SortType==SORT_BY_TIME)
			{
				// �������ʱ��
				int nTimeK = (m_Flights[k].LandingTime.tm_hour - m_Flights[k].TakeoffTime.tm_hour) * 60 +
					(m_Flights[k].LandingTime.tm_min - m_Flights[k].TakeoffTime.tm_min);

				int nTimeJ = (m_Flights[j].LandingTime.tm_hour - m_Flights[j].TakeoffTime.tm_hour) * 60 +
					(m_Flights[j].LandingTime.tm_min - m_Flights[j].TakeoffTime.tm_min);

				if (nTimeK > nTimeJ)
				{
					bNeedExchange = true;
				}

			}
			else if( SortType==SORT_BY_TICKET)
			{
				if (m_Flights[k].nTicket > m_Flights[j].nTicket)
				{
					bNeedExchange = true;
				}
			}

			if (bNeedExchange)
			{
				FLIGHT temp;

				temp = m_Flights[j];
				m_Flights[j] = m_Flights[k];
				m_Flights[k] = temp;
			}
		}
	}

	// ��ʾ������
	cout << ("\t\t��ѯ������£�") << endl << endl;

	// ����ʾ����
	cout << "\t\t";
	cout << setw(15) << "�����";
	cout << setw(15) << "������";
	cout << setw(15) << "�յ����";
	cout << setw(15) << "���ʱ��";
	cout << setw(15) << "����ʱ��";
	cout << setw(10) << "Ʊ��";
	cout << setw(10) << "��Ʊ";
	cout << endl;	

	// ���ݲ�ѯ�������в���
	for (i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strStart, flight.strStartCity) == 0
			&& strcmp(strEnd, flight.strEndCity) == 0)
		{
			cout << "\t\t";
			cout << setw(15) << flight.strFlightID;
			cout << setw(15) << flight.strStartCity;
			cout << setw(15) << flight.strEndCity;
			cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
			cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
			cout << setw(10) << flight.nPrice;
			cout << setw(10) << flight.nTicket;
			cout << endl;
		}
	}
}

/////////////////////////////////////////////
// 11. ��ѯ���к���
void FlightSystem::SearchAllFlights()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	cout << "\t\t" << "���к�����Ϣ���£�\n" << endl;

	// ����ʾ����
	cout << "\t\t-------------------------------------------------------------------------------------\n";
	cout << "\t";
	cout << setw(15) << "�����";
	cout << setw(15) << "������";
	cout << setw(15) << "�յ����";
	cout << setw(15) << "���ʱ��";
	cout << setw(15) << "����ʱ��";
	cout << setw(10) << "Ʊ��";
	cout << setw(10) << "��Ʊ";
	cout << endl;

	// ��ʾ���к����¼
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		cout << "\t";
		cout << setw(15) << flight.strFlightID;
		cout << setw(15) << flight.strStartCity;
		cout << setw(15) << flight.strEndCity;
		cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
		cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
		cout << setw(10) << flight.nPrice;
		cout << setw(10) << flight.nTicket;
		cout << endl;
	}
	cout << "\t\t-------------------------------------------------------------------------------------\n\n";
}

///////////////////////////////////////////////
// 12. ��ѯ���й�Ʊ��Ϣ
void FlightSystem::SearchAllTickets()
{
	// ���û�м�¼�򲻽��д���
	if (!CheckFlightData()) return;

	cout << "\t\t" << "���й�Ʊ��Ϣ���£�\n" << endl;

	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		cout << "\t\t���� [" << m_Flights[i].strFlightID << "] ��Ʊ��Ϣ" << endl;		

		// ��Ʊ�˿�
		GUESTS& guests = m_Flights[i].Guests;
		cout << "\t\t  �ѹ�Ʊ�˿ͣ��� " << guests.size() << " ��" << endl;		
		for (unsigned int j = 0; j < guests.size(); j++)
		{
			cout << "\t\t\t���֤�ţ�" << guests[j].strID << "\t������" << guests[j].strName << "\t��Ʊ����" << guests[j].nCount << "��"<< endl;
		}
		
		// �Ⱥ�˿�
		WGUESTS& wguests = m_Flights[i].WaitingGuests;
		cout << "\t\t  ԤԼ�˿ͣ��� " << wguests.size() << " ��" << endl;
		for (j = 0; j < wguests.size(); j++)
		{
			cout << "\t\t\t���֤�ţ�" << wguests[j].strID << "\t������" << wguests[j].strName << "\t��Ʊ����" << wguests[j].nCount << "��" << endl;
		}

		cout << endl;
	}
}

///////////////////////////////////////////////
// ��麽�������Ƿ���Ч
bool FlightSystem::CheckFlightData()
{
	if (m_Flights.size() <= 0)
	{
		cout << "\t\t�������޺������ݣ�" << endl;
		return false;
	}

	return true;
}

//////////////////////////////////////////////
// ����ָ���ĺ���Ż�ȡ���������
int FlightSystem::GetFlightIndexByID(const char* pID)
{
	int nIndex = -1;

	// ���ݲ�ѯ�������в���
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(pID, flight.strFlightID) == 0)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
