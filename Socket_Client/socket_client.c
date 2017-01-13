#include <stdio.h>  
#include <Windows.h>  
   
#pragma comment(lib,"ws2_32.lib")  
#define  PORT 8000  
//#define  IP_ADDRESS "169.254.6.208"  
#define IP_ADDRESS "192.168.1.118"
   
void help() {
	printf("0/*�������ڿ���*/, 1/*ǰ*/, 2/*��*/, 3/*��*/,4/*��*/, 5/*ͣ*/, 6/*�رմ��ڿ���*/, 7/*�ر�socket����*/\n");
	printf("please enter your choice: ");
}

int main(int argc, char* argv[])  
{  
    WSADATA  Ws;  
    SOCKET ClientSocket;  
    struct sockaddr_in ClientAddr;  
    int ret = 0;  
    //unsigned char SendBuffer[MAX_PATH];
	
	unsigned char SendBuffer[] = {0xc0/*�������ڿ���*/, 0xc8/*ǰ*/, 0xc9/*��*/, 0xca/*��*/,
								0xcb/*��*/, 0xcc/*ͣ*/, 0x80/*�رմ��ڿ���*/, 0xff/*�ر�socket����*/};
    
    /* Init Windows Socket */  
    if(WSAStartup(MAKEWORD(2, 2), &Ws) != 0)  
    {  
        printf("Init Windows Socket Failed::%d\n", GetLastError());  
        return -1;  
    }  
   
    /* Create Socket */  
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(ClientSocket == INVALID_SOCKET)  
    {  
        printf("Create Socket Failed:%d\n", GetLastError());  
        return -1;  
    }  
  
    ClientAddr.sin_family = AF_INET;  
    ClientAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);  
    ClientAddr.sin_port = htons(PORT);  
    memset(ClientAddr.sin_zero, 0x00, 8);  
  
    /* connect socket */  
	printf("Connecting to Server...\n");
    ret = connect(ClientSocket,(struct sockaddr*)&ClientAddr, sizeof(ClientAddr));  
    if(ret == SOCKET_ERROR)  
    {  
        printf("Connect Error::%d\n", GetLastError());  
        return -1;  
    }  
    else  
    {  
        printf("Connect succeed!\n");  
    }  
	help();
    while(1)  
    {  
		int cmd;
        scanf("%d", &cmd);  
  
        /* send data to server */  
		if(cmd == 0 || cmd == 1 || cmd == 2 || cmd == 3 || cmd == 4 || cmd == 5 || cmd == 6 || cmd == 7){
			ret = send(ClientSocket, (char*) &SendBuffer[cmd], (int)strlen((char*)&SendBuffer[cmd]), 0);
		}
		else
			printf("command error, please input again: \n");
		if(cmd == 7){  
			break;  
		}
        if (ret == SOCKET_ERROR){  
            printf("Send Info Error::%d\n", GetLastError());  
            break;  
        }             
    }  
      
    /* close socket */  
    closesocket(ClientSocket);  
    WSACleanup();  
   
    return 0;  
 }  
