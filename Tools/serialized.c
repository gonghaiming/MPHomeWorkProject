
#include "common.h"
#include <string.h>
#include <arpa/inet.h>
/*****************************************************************
 * DESCRIPTION:
 *
 * INPUTS:
 *        pktdata-UPD网络数据包（大端）
 *        package UPD数据包结构体数据
 * OUTPUTS:
 *        pktdata-网络流后的序列化数据
 * RETURNS:
 *        NULL
 *****************************************************************/
INT16 Serialized(char *pktdata, pkt *package)
{
    INT16 pktLength = package->head.lengthPkt;
    package->head.lengthPkt = htons(package->head.lengthPkt);
    memcpy(pktdata, package, pktLength);
    return pktLength;
    
}

