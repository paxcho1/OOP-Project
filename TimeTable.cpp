#include "TimeTable.h"
TimeTable::TimeTable(SOCKET client, string id) :tool(client)
{
}
TimeTable::~TimeTable()
{
}

int TimeTable::table(SOCKET client, string id) {
	while (1) {
		char buf[MAX_BUFFER_SIZE];
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		int byteIn = recv(client, buf, MAX_BUFFER_SIZE, 0);
		string code = buf;
		code = code.substr(0, 3);
		//send class �� recv Ŭ���� �����
		if (byteIn <= 0) {
			break;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {//000 yymmdd ����string recv client�� ���� �ð�ǥ Ȯ�� ��û �ش� �ð�ǥ�� ������
				DailySchedule Daily;
				strtok(buf, " ");
				char* ptr = strtok(NULL, " ");
				FileToDailyScheduleClass(Daily, id, ptr);

				ptr = strtok(NULL, " ");
				//�ְ� bin file �ҷ�����
				//yymmdd.bin file �ҷ�����
				//Send �ְ�class �ϰ�class ���̱�
			}
			else if (strcmp(code.c_str(), "001") == 0) {
				//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {//002 yymmdd ���� 00:00~00:00 ���� recv /client�� ���� �߰� ��û �ڽ��� ������ Ȯ���ϰ� �߰� ���� �Ұ� ���θ� ������.
				//��ū��Ȱ
				//�ְ� bin file �ҷ�����
				//yymmdd.bin file �ҷ�����
				//��ü
				//�ش����� ������ �߰� ���� ���� �˻�
				//�����ϸ� 000 + �����߰� �Ұ����ϸ� 001

			}
			else if (strcmp(code.c_str(), "003") == 0) {//003 yymmdd ���� // �ش� ��¥�� ���� ����
				//��ū��Ȱ
				//�ش� ���� ����
			}
			else if (strcmp(code.c_str(), "004") == 0) {//004 ���� ���� // �ش� ������ ���� ����
				// �ش� ���� ����
			}
			else if (strcmp(code.c_str(), "005") == 0) {//005 ���� ���� �ð�ǥ �߰� 
				//while �ش� ���� ������ ���� ������ ���� �˻� �� ������{
				//�ߺ��˻��� �ߺ��̸� �Ұ� ��¥;
				//}
				//�����ϸ� 000 + �����߰� �Ұ����ϸ� 001 +  �Ұ� ��¥
			}
		}
	}
	return 0;
}