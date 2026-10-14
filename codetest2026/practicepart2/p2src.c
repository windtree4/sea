
#define CHECKSUM_H
#include <stdint.h>
/* 累加和：所有字节相加后取低 8 位（对 256 取模）。
 *
 * 参数：
 *   data - 指向要计算的字节数组，不能为 NULL。
 *   len  - 字节数组的长度（字节数）。
 *
 * 返回值：
 *   所有字节累加后取低8位的结果；data为NULL或len为0时返回0。
 */
uint8_t cksum_sum8(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0) {
        return 0;
    }

    uint32_t sum = 0;
    for (uint32_t i = 0; i < len; i++) {
        sum += data[i];   /* 把第 i 个字节加到 sum 里 */
    }

    return (uint8_t)(sum & 0xFF);   /* 取低8位 */
}



/* 异或校验：所有字节逐字节异或，初值 0。 */
uint8_t cksum_xor8(const uint8_t *data, uint32_t len)
{
    if(data==NULL|| len==0){
return 0;
    }
uint8_t result =0;
for(uint32_t i=0;i<len;i++){
    result  ^=data[i];
}
return result ;
}


/* ★ 延伸：CRC8
* 多项式 0x07，初值 0x00，不反转，异或输出 0x00。
* 标准值：crc8("123456789", 9) == 0xF4 */
/* 
 * 参数：
 *   data - 指向要计算的字节数组，不能为 NULL。
 *   len  - 字节数组的长度（字节数）。
 *
 * 返回值：
 *   CRC8 校验结果；data为NULL或len为0时返回0。
 */
uint8_t crc8(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0) {
        return 0;
    }

    uint8_t crc = 0x00;   /* 初值 0x00 */

    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];   /* 先和当前字节异或 */

        for (uint8_t bit = 0; bit < 8; bit++) {   /* 处理 8 个位 */
            if (crc & 0x80) {                     /* 最高位是 1 */
                crc = (crc << 1) ^ 0x07;
            } else {                              /* 最高位是 0 */
                crc = crc << 1;
            }
        }
    }

    return crc;
}
/* ★ 延伸：CRC16
* 多项式 0xA001（反射写法），初值 0xFFFF，异或输出 0x0000。
* 标准值：crc16("123456789", 9) == 0x4B37 */
uint16_t crc16(const uint8_t *data, uint32_t len)
{
    if(data==NULL||len==0){
return 0;
    }
    uint16_t crc=0xFFFF;  /*初始值*/
for (uint32_t i =0;i<len;i++){
    crc^=data[i];   /*异或*/

    for (uint8_t bit =0;bit <8;bit++){    /*处理8个位*/  
        if(crc & 0x0001){
            crc = (crc >>1)^0xA001;
        }
        else {
            crc>>=1;
        }
        
    }
   }
   return crc; 
}

