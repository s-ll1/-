#pragma once
#include "Common.h"

class FlightSystem
{
	
public:
	FlightSystem();
	~FlightSystem();
	
public:
	
	// 1. ���غ�������
	bool LoadFromFile();
	// 2. ���溽������
	bool SaveToFile();
	
	// 3. ��Ӻ���
	void AddFlight();
	// 4. ɾ������
	void DelFlight();
	// 5. �޸ĺ���
	void ModFlight();
	
	// 6. ��������ȡ��֪ͨ
	void Delay();
	
	// 7. ��Ʊ����
	void BuyTicket();
	// 8. ��Ʊ����
	void RefundTicket();
	
	// 9. ������Ų�ѯ
	void SearchByFlight();
	// 10. ���𽵵ص��ѯ
	void SearchByAddress();
	// 11. ��ѯ���к���
	void SearchAllFlights();
	// 12. ��ѯ���й�Ʊ��Ϣ
	void SearchAllTickets();
	
protected:
	
	// ��麽�������Ƿ���Ч
	bool CheckFlightData();
	
	// ����ָ���ĺ���Ż�ȡ���������
	int GetFlightIndexByID(const char* pID);
	
	// ����˳���
	vector<FLIGHT>					m_Flights;
	
};

