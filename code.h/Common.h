#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;

// Ĭ�ϵĺ��������ļ���
#define FLIGHT_FILE							"flight_data.txt"

// �ַ����ĳ���
#define STR_LEN								0x20

// ÿ�˺����Ĭ��Ʊ��
#define DEFAULT_TICKET_COUNT				200

// ����״̬
typedef enum _tagFlightStatus
{
	STATUS_NORMAL,											// ����״̬����
		STATUS_DELAY,											// ����״̬����
		STATUS_CANCEL,											// ����״̬ȡ��
		STATUS_COUNT
		
} FLIGHT_STATUS;

// ��ѯ������������
typedef enum _tagSortType
{
	SORT_NORMAL,											// Ĭ������
		SORT_BY_PRICE,											// ��Ʊ������
		SORT_BY_TIME,											// ������ʱ������
		SORT_BY_TICKET,											// ����Ʊ������
		SORT_COUNT
		
} SORT_TYPE;

// �˿���Ϣ�ṹ��
typedef struct _tagGuest
{
	char			strID[STR_LEN];							// ��Ʊ�����֤
	char			strName[STR_LEN];						// ��Ʊ������
	
	int				nCount;
	
	_tagGuest()
	{
		memset(strID, 0, sizeof(strID));
		memset(strName, 0, sizeof(strName));
		
		nCount = 0;
	}
	
} GUEST, *LPGUEST;

// ������Ϣ�ṹ��
typedef vector<GUEST>			GUESTS;
typedef deque<GUEST>            WGUESTS;
typedef struct _tagFlight
{
	char			strFlightID[STR_LEN];					// �����
	char			strCompany[STR_LEN];					// ���չ�˾����
	char			strStartCity[STR_LEN];					// ���
	char			strEndCity[STR_LEN];					// �յ�
	char			strTransitCity[STR_LEN];				// ��ͣ
	
	struct tm       TakeoffTime;							// ���ʱ��
	struct tm       LandingTime;							// ���ʱ��
	
	int				nTicket;								// ����Ʊ��
	
	int				nPrice;									// Ʊ��
	
	GUESTS			Guests;									// ��Ʊ�˿�
	WGUESTS			WaitingGuests;							// ԤԼ�˿Ͷ���
	
	_tagFlight()
	{
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		
		memset(&TakeoffTime, 0, sizeof(TakeoffTime));
		memset(&LandingTime, 0, sizeof(LandingTime));
		
		nTicket = DEFAULT_TICKET_COUNT;
		
		nPrice = 0;
	}
	
} FLIGHT, *LPFLIGHT;