#include <stdio.h>
#include "p2inc.h"
int main()
{
    /*测试cksum_sum8*/
    uint8_t arr1[]={0x78,0x56,0x34,0x12};
    uint32_t sum1 =
cksum_sum8(arr1, 4);
    printf("cksum_sum8=0x%02X\n",
sum1);


/* 测试cksum_xor8*/
    uint8_t arr2[]={0x78,0x56,0x34,0x12};
    uint32_t sum2=
cksum_xor8(arr2, 4);
    printf("cksum_xor8=0x%02X\n",
sum2);



/*crc8*/
    uint8_t arr3[]={'1','2','3','4','5','6','7','8','9'};
    uint8_t result =
crc8(arr3, 9);
    printf("crc_crc8=0x%02X\n",
result );


/*测试crc16*/
    uint8_t arr4[]={'1','2','3','4','5','6','7','8','9'};
    uint16_t result2=
crc16(arr4,9);
printf ("crc16(123456789)=0x%04X\n",
result2);
return 0;
}