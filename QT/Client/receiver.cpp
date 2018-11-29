#include "receiver.h"



Receiver::Receiver(SOCKET client, string Id)
{
}


Receiver::~Receiver()
{
}

int Receiver::Chat(SOCKET server, string Id) {
   char msg[MAX_BUFFER_SIZE];
   ZeroMemory(msg, MAX_BUFFER_SIZE);
   string filepath = Get(server, Id, msg);//get filename.txt
   //띄우기
   while (strcmp(msg, "endfile") != 0) {
      cout << filepath << endl;//fd.name 출력
      filepath = "c:/client/" + Id + "/" + filepath;
      Get(server, Id, msg);//total byte size
      int totalbytes = atoi(msg);
      FILE *fp = fopen(filepath.c_str(), "wb");
      int left = totalbytes;
      while (1) {
         if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
            Get(server, Id, msg);
            fwrite(msg, 1, left, fp);
            left = 0;
         }
         else if (left > MAX_BUFFER_SIZE) {
            Get(server, Id, msg);
            fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
            left -= MAX_BUFFER_SIZE;
         }
         if (left == 0) {
            break;
         }
      }
      fclose(fp);
      if (left == 0) {
         printf("filename %s 파일을 성공적으로 받았습니다.\r\n", msg);
      }
      else {
         printf("파일을 제대로 받지 못했습니다.\r\n");
      }
      filepath = Get(server, Id, msg);//get filename.txt
   }
   if (strcmp(msg, "endfile") == 0) {
      cout << "채팅 목록 불러오기 완료" << endl;
   }
   return 0;
}
int Receiver::Chatin(SOCKET server, string Id) {
   char msg[MAX_BUFFER_SIZE];
   ZeroMemory(msg, MAX_BUFFER_SIZE);
   string filepath = Get(server,Id, msg);//get filename.txt
   while (strcmp(msg, "endfile") != 0) {
      cout << filepath << endl;//fd.name 출력
      filepath = "c:/client/" + Id + "/ChatAlarm/" + filepath;
      Get(server, Id , msg);//total byte size
      int totalbytes = atoi(msg);
      FILE *fp = fopen(filepath.c_str(), "wb");
      int left = totalbytes;
      while (1) {
         if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
            Get(server,Id, msg);
            fwrite(msg, 1, left, fp);
            left = 0;
         }
         else if (left > MAX_BUFFER_SIZE) {
            Get(server, Id,msg);
            fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
            left -= MAX_BUFFER_SIZE;
         }
         if (left == 0) {
            break;
         }
      }
      fclose(fp);
      if (left == 0) {
         printf("filename %s 파일을 성공적으로 받았습니다.\r\n", msg);
      }
      else {
         printf("파일을 제대로 받지 못했습니다.\r\n");
      }
      filepath = Get(server,Id, msg);//get filename.txt
   }
   if (strcmp(msg, "endfile") == 0) {
      cout << "채팅 알람 목록 불러오기 완료" << endl;
   }
   return 0;
}
int Receiver::NewInvite(SOCKET server, string Id) {
   char msg[MAX_BUFFER_SIZE];
   ZeroMemory(msg, MAX_BUFFER_SIZE);
   string filepath = Get(server,Id, msg);//get filename.txt
   while (strcmp(msg, "endfile") != 0) {
      cout << filepath << endl;//fd.name 출력
      filepath = "c:/client/" + Id + "/InviteAlarm/" + filepath;
      Get(server, Id, msg);//total byte size
      int totalbytes = atoi(msg);
      FILE *fp = fopen(filepath.c_str(), "wb");
      int left = totalbytes;
      while (1) {
         if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
            Get(server, Id,msg);
            fwrite(msg, 1, left, fp);
            left = 0;
         }
         else if (left > MAX_BUFFER_SIZE) {
            Get(server,Id, msg);
            fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
            left -= MAX_BUFFER_SIZE;
         }
         if (left == 0) {
            break;
         }
      }
      fclose(fp);
      if (left == 0) {
         printf("filename %s 파일을 성공적으로 받았습니다.\r\n", msg);
      }
      else {
         printf("파일을 제대로 받지 못했습니다.");
      }
      filepath = Get(server,Id, msg);//get filename.txt
   }
   if (strcmp(msg, "endfile") == 0) {
      cout << "friend 알람 목록 불러오기 완료" << endl;
   }
   return 0;
}
int Receiver::NewFriends(SOCKET server, string Id) {
   char msg[MAX_BUFFER_SIZE];
   ZeroMemory(msg, MAX_BUFFER_SIZE);
   string filepath = Get(server,Id, msg);//get filename.txt
   while (strcmp(msg, "endfile") != 0) {
      cout << filepath << endl;//fd.name 출력
      //이 친구는 새친구입니다.
      filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
      Get(server, Id, msg);//total byte size
      int totalbytes = atoi(msg);
      FILE *fp = fopen(filepath.c_str(), "wb");
      int left = totalbytes;
      while (1) {
         if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
            Get(server, Id,msg);
            fwrite(msg, 1, left, fp);
            left = 0;
         }
         else if (left > MAX_BUFFER_SIZE) {
            Get(server, Id,msg);
            fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
            left -= MAX_BUFFER_SIZE;
         }
         if (left == 0) {
            break;
         }
      }
      fclose(fp);
      if (left == 0) {
         printf("filename %s 파일을 성공적으로 받았습니다.\r\n", msg);
      }
      else {
         printf("파일을 제대로 받지 못했습니다.");
      }
      filepath = Get(server,Id, msg);//get filename.txt
   }
   if (strcmp(msg, "endfile") == 0) {
      cout << "새로운 friend 목록 불러오기 완료" << endl;
   }
   return 0;
}
int Receiver::FriendsIndex(SOCKET server, string Id) {
   char msg[MAX_BUFFER_SIZE];
   ZeroMemory(msg, MAX_BUFFER_SIZE);
   string filepath = Get(server,Id, msg);//get filename.txt
   while (strcmp(msg, "endfile") != 0) {
      cout << filepath << endl;//fd.name 출력
      filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
      Get(server, Id, msg);//total byte size
      int totalbytes = atoi(msg);
      FILE *fp = fopen(filepath.c_str(), "wb");
      int left = totalbytes;
      while (1) {
         if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
            Get(server,Id, msg);
            fwrite(msg, 1, left, fp);
            left = 0;
         }
         else if (left > MAX_BUFFER_SIZE) {
            Get(server,Id, msg);
            fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
            left -= MAX_BUFFER_SIZE;
         }
         if (left == 0) {
            break;
         }
      }
      fclose(fp);
      if (left == 0) {
         printf("filename %s 파일을 성공적으로 받았습니다.\r\n", msg);
      }
      else {
         printf("파일을 제대로 받지 못했습니다.");
      }
      filepath = Get(server,Id, msg);//get filename.txt
   }
   if (strcmp(msg, "endfile") == 0) {
      cout << "friend 목록 불러오기 완료" << endl;
   }
   return 0;
}
int Receiver::Newmsg(SOCKET server, string Id, string file, string message) {
   string filepath = "c:/client/" + Id + "/ChatAlarm/" + file + ".txt";
   ofstream Write(filepath, ios::app);
   if (Write.is_open()) {
      cout << "writing file" << endl;
      Write << message << endl;
   }
   Write.close();
   return 0;
}
string Receiver::Get(SOCKET server, string Id, char* buf) {
   int Bytein = recv(server, buf, MAX_BUFFER_SIZE, 0);
   string code = buf;
   code = code.substr(0, 3);
   if (strcmp(code.c_str(), "001") == 0) {
      Chat(server, Id); return buf;
   }
   else if (strcmp(code.c_str(), "002") == 0) {
      Chatin(server, Id); return buf;
   }
   else if (strcmp(code.c_str(), "003") == 0) {
      FriendsIndex(server, Id); return buf;
   }
   else if (strcmp(code.c_str(), "004")==0) {
      NewInvite(server, Id); return buf;
   }
   else if (strcmp(code.c_str(), "005") == 0) {
      NewFriends(server, Id); return buf;
   }
   else if (strcmp(code.c_str(), "006") == 0) {//message 받음 //만약 현제 client가 해당 채팅창에 접속중
      strtok(buf, " ");
      char* ptr = strtok(NULL, " ");
      string file = (strcpy, ptr);
      ptr = strtok(NULL, " ");
      string sender = (strcpy, ptr);
      char Str[MAX_BUFFER_SIZE];
      string tokmsg;
      strcpy(Str, "");
      while (ptr != NULL) {
         strcat(Str,ptr);
         tokmsg = strcat(Str, " ");
         ptr = strtok(NULL, " ");
      }
      Newmsg(server, Id, file, tokmsg); return buf;
   }
   else if (strcmp(code.c_str(), "007") == 0) {//Invite 받음
      strtok(buf, " ");
      char* Invite_id = strtok(NULL, " ");
      string filepath = "c:/client/" + Id + "/InviteAlarm/" + Invite_id + ".txt";
      ofstream Write(filepath, ios::app);
      if (Write.is_open()) {
         cout << "writingfile:" + filepath << endl;
         Write << Invite_id <<endl;
      }
      Write.close();
   }
   else if (strcmp(code.c_str(), "008") == 0) {//새친구의 알람
      strtok(buf, " ");
      char* new_friend = strtok(NULL, " ");
      string filepath = "c:/client/" + Id + "/FriendsIndex/" + new_friend + ".txt";//friends Alarm으로 가지않음.
      //이 친구는 새친구입니다.
      ofstream Write(filepath, ios::app);
      if (Write.is_open()) {
         cout << "writingfile:" + filepath << endl;
         Write << new_friend << endl;
      }
      Write.close();
   }
   else if (Bytein <= 0) {
      exit(0);
      return "error";
   }
   else {
      return buf;
   }
}
