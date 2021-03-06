// SPIRemove.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "conductor.h"


/*
LSP list would be initialized in WSAStartup,
and would be loaded in WSASocketW.
LSP list would be updated if LSP registry changed.
*/

int main() {
  printf("Any key to start...\r\n");
  _getch();

  Conductor* conductor = Conductor::CreateInstance();
  if (conductor == NULL) {
    printf("Not enough memory!\r\n");
    return 0;
  }

  if (!conductor->TakeoverControl()) {
    printf("Fail to take over control, unsupported ws2_32.dll\r\n");
    return 0;
  }

  conductor->ListAllCatalog();

  printf("Any key to process SPI list...\r\n");
  _getch();

  conductor->RepairProtocols();
  if (!conductor->RefineCatalog()) {
    printf("Failed to refine!\r\n");
    return false;
  }
  printf("\r\nAfter refine: \r\n");
  conductor->ListAllCatalog();

  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  printf("Any key to exit...\r\n");
  _getch();
  return 0;
}

