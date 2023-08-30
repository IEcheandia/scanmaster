/**************************************************************************************
 This software is developed by NEWSON NV
 Redistribution and use, with or without modification, are permitted
 
 THIS SOFTWARE IS PROVIDED BY NEWSON AS IS.
 ANY EXPRESS OR IMPLIED WARRANTIES ARE DISCLAIMED.
 IN NO EVENT SHALL NEWSON BE LIABLE FOR ANY DAMAGES ARISING
 OUT OF THE USE OF THIS SOFTWARE.
 **************************************************************************************/

//#include "stdafx.h"
#if NEWSON_LEGACY
#include "..\Sw01 [dll]\All.h"
#else
#include "All.h"
#endif


CHardwareUDP32::CHardwareUDP32()
{
	memset(&m_sa, 0, sizeof(m_sa));
	m_sa.sin_family=PF_INET;
  h_Socket=INVALID_SOCKET;

#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)==0)
	{
		if (LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
    {
     	m_sa.sin_family=PF_UNSPEC;
			WSACleanup();
    }
	}
  else m_sa.sin_family=PF_UNSPEC;
#endif
}


CHardwareUDP32::~CHardwareUDP32()
{
	DisConnect();

#ifdef _WIN32
  if (m_sa.sin_family!=PF_UNSPEC)	WSACleanup();
#endif
}


int32_t CHardwareUDP32::CommType()
{ 
  return CUA32_UDP;
}


int32_t CHardwareUDP32::ConnectDSP()
{
	if (m_sa.sin_family!=PF_INET) return ERR_HARDWARE; // failed
  if (h_Socket!=INVALID_SOCKET) DisConnect();

  h_Socket=socket(PF_INET, SOCK_DGRAM, 0);
	m_sa.sin_port=htons(10002);
  if (connect(h_Socket, (sockaddr*)&m_sa, sizeof(m_sa))!=0) return ERR_HARDWARE; // failed
  int timeout=5000;
  setsockopt(h_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
  setsockopt(h_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
  return ERR_OK;
}


void CHardwareUDP32::DisConnect()
{
#ifdef _WIN32
  if (h_Socket!=INVALID_SOCKET) closesocket(h_Socket);
#else
  if (h_Socket!=INVALID_SOCKET) close(h_Socket);
#endif
	h_Socket=INVALID_SOCKET;
}


int32_t CHardwareUDP32::Exchange(char* OutBytes, char* InBytes, int32_t BytesToWrite, int32_t BytesToRead, int32_t trials)
{ 
  int i,j;
  
  while (true)
  {
    for (j=0;j<BytesToWrite;)
    {
      i=send(h_Socket, &OutBytes[j], std::min(512,BytesToWrite-j), 0);
      j+=i;
    }
    for (j=0;j<BytesToRead;)
    {
      i=recv(h_Socket, &InBytes[j], BytesToRead-j, 0);
      if (i<=0)
      {
        if (trials==1) return ERR_HARDWARE;
        j=BytesToRead+1;
      }
      else j+=i;
    }
    if (j==BytesToRead) return ERR_OK;
    else if (trials>0) trials--;
  }
}


void CHardwareUDP32::SetAddress(const char* IP)
{
  DisConnect();
  m_sa.sin_addr.s_addr= inet_addr(IP);
}

















































































































































































