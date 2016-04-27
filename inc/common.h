/*****************************************************************
 * Copyright (C) 2010 Maipu Communication Technology Co.,Ltd.*
 ******************************************************************
 * commmon.h
 *
 * DESCRIPTION:
 * 报文结构和数据类型头文件
 * AUTHOR:
 * MR_GONG
 * CREATED DATE:
 * 2016-4.27
 * REVISION:
 * 1.0
 *
 * MODIFICATION HISTORY
 * --------------------
 * $Log:$
 * *****************************************************************/

#ifndef __COMMON_H
#define __COMMON_H
typedef char INT8; 
typedef short INT16; 
typedef int INT32; 
typedef unsigned char UCHAR; 
typedef signed char CHAR; 
typedef unsigned short UINT16; 
typedef unsigned int UINT32; 
typedef signed int INT32; 
typedef signed long long INT64; 
typedef unsigned long long UINT64; 
typedef int BOOL

/*报文头部*/
struct pktHeader
{
    INT8 code;
    INT8 id;
    INT16 lengthPkt;
    INT8 md5Auth[16];
}

/*报文正文内容*/
Struct content
{
    INT8 type;
    INT8 lengthItem;
    INT8 value[20];
}

/*报文*/
struct pkt
{
    Struct pktHeader head;
    INT8 content[1500];
}
#endif