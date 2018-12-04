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
		//send class 랑 recv 클래스 만들기
		if (byteIn <= 0) {
			break;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {//000 yymmdd 요일string recv client의 일일 시간표 확인 요청 해당 시간표를 보낸다
				DailySchedule Daily;
				strtok(buf, " ");
				char* ptr = strtok(NULL, " ");
				FileToDailyScheduleClass(Daily, id, ptr);

				ptr = strtok(NULL, " ");
				//주간 bin file 불러오기
				//yymmdd.bin file 불러오기
				//Send 주간class 일간class 붙이기
			}
			else if (strcmp(code.c_str(), "001") == 0) {
				//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {//002 yymmdd 요일 00:00~00:00 일정 recv /client의 일정 추가 요청 자신의 일정을 확인하고 추가 가능 불가 여부를 보낸다.
				//토큰분활
				//주간 bin file 불러오기
				//yymmdd.bin file 불러오기
				//합체
				//해당일자 일정이 추가 가능 여부 검사
				//가능하면 000 + 일정추가 불가능하면 001

			}
			else if (strcmp(code.c_str(), "003") == 0) {//003 yymmdd 일정 // 해당 날짜의 일정 삭제
				//토큰분활
				//해당 일정 삭제
			}
			else if (strcmp(code.c_str(), "004") == 0) {//004 요일 일정 // 해당 요일의 일정 삭제
				// 해당 일정 삭제
			}
			else if (strcmp(code.c_str(), "005") == 0) {//005 요일 일정 시간표 추가 
				//while 해당 요일 앞으로 일정 폴더를 전부 검색 할 때까지{
				//중복검사후 중복이면 불가 날짜;
				//}
				//가능하면 000 + 일정추가 불가능하면 001 +  불가 날짜
			}
		}
	}
	return 0;
}