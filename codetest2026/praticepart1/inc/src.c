#include "inc.h"
/* 把 word 的第 pos 位置 1，返回结果。 */
uint32_t bit_set(uint32_t word, uint8_t pos)
{
    if(pos>31){
        return word;
    }
    return word|1u<<pos;
}

/* 把 word 的第 pos 位清 0，返回结果。 */
uint32_t bit_clear(uint32_t word, uint8_t pos)
{
    if (pos>31){
        return word;
    }
    return word & ~(1u<<pos);
}

/* 把 word 的第 pos 位取反，返回结果。 */
uint32_t bit_toggle(uint32_t word, uint8_t pos)
{
    if (pos>31){  /*why can pos >31???*/
        return word;
    }
    return word ^ ~(1u<<pos);/*计算顺序？？？*/

    /*0000 0001
      0000 0100
      1111 1000
      */
}

/* 读出 word 的第 pos 位，返回 0 或 1。 */
uint8_t bit_get(uint32_t word, uint8_t pos)
{
    if (pos>31){
        return 0;
    }
    
}

/* 用 while 循环统计 word 里 1 的个数。 */
uint8_t bit_count(uint32_t word)
/* 用 while 循环统计 word 里 1 的个数。
 *
 * 参数：
 *   word - 要统计的32位数据。
 *
 * 返回值：
 *   word 的二进制表示中 1 的个数，范围 0~32。
 */
{
    uint8_t count = 0;  /* 计数器 */

    while (word != 0) {
        count += word & 1u;  /* 如果最低位是1，count加1 */
        word >>= 1;          /* 右移一位，丢弃最低位 */
    }

    return count;
}
    



/* 用 do...while 循环统计 word 里 1 的个数。 */
uint8_t bit_count_do_while(uint32_t word)
{
    uint8_t count = 0;/*计数器*/
    do {
        count += word & 1u;
        word >>=1;
    }while (word!=0);
return count;
}

/* 生成 [hi:lo] 这一段全为 1 的掩码。 */
 
/* 参数：
   hi - 高位号，合法范围 0~31
   lo - 低位号，合法范围 0~31，且必须 hi >= lo。

 返回值：
  [hi:lo] 全为1的掩码；hi < lo 或 hi > 31 时返回 0。
 */
uint32_t bit_mask_make(uint8_t hi, uint8_t lo)
{
    uint32_t width;

    /* 非法情况：hi < lo，或 hi > 31 */
    if (hi < lo || hi > 31) {
        return 0;
    }

    width = (uint32_t)(hi - lo + 1);  /* 计算宽度 */

    if (width >= 32) {
        return 0xFFFFFFFFu;  /* 宽度达到32，全1掩码 */
    }

    return ((1u << width) - 1u) << lo;
}

/* 读取 word 的 [hi:lo] 字段，返回该段的值。 */
 
 /* 参数：
 *   word - 要操作的32位数据。
 *   hi   - 高位号，合法范围 0~31。
 *   lo   - 低位号，合法范围 0~31，且必须 hi >= lo。
 *
 * 返回值：
 *   [hi:lo] 这一段的值；非法输入时返回 0。
 */
uint32_t bit_field_get(uint32_t word, uint8_t hi, uint8_t lo)
{
    uint32_t width;

    /* 非法情况：hi < lo，或 hi > 31 */
    if (hi < lo || hi > 31) {
        return 0;
    }

    width = (uint32_t)(hi - lo + 1);  /* 计算字段宽度 */

    /* 先右移 lo 位，把目标段移到最低位；再与掩码，取出低 width 位 */
    return (word >> lo) & ((1u << width) - 1u);
}


/* 把 word 的 [hi:lo] 字段设置为 value。 */
 /*
 * 参数：
 *   word  - 要操作的32位数据。
 *   hi    - 高位号，合法范围 0~31。
 *   lo    - 低位号，合法范围 0~31，且必须 hi >= lo。
 *   value - 要写入的数值（只取低 width 位有效）。
 *
 * 返回值：
 *   修改后的word；非法输入（hi<lo 或 hi>31）时返回 word 原值。
 */
uint32_t bit_field_set(uint32_t word, uint8_t hi, uint8_t lo, uint32_t value)
{
    uint32_t width;
    uint32_t mask;
    uint32_t field_mask;

    /* 非法情况：hi < lo，或 hi > 31 */
    if (hi < lo || hi > 31) {
        return word;  /* 非法时返回原值 */
    }

    width = (uint32_t)(hi - lo + 1);         /* 字段宽度 */
    mask = ((1u << width) - 1u) << lo;        /* 目标段的掩码 */
    field_mask = (1u << width) - 1u;          /* 低width位全1的掩码 */

    /* 先清空目标段，再写入value的有效位 */
    return (word & ~mask) | ((value & field_mask) << lo);
}


/* 把 8 位数据按位翻转。 */
 /*
 * 参数：
 *   byte - 要翻转的8位数据。
 *
 * 返回值：
 *   翻转后的8位数据。
 */
uint8_t bit_reverse8(uint8_t byte)
{
    uint8_t result = 0;
    uint8_t i;

    for (i = 0; i < 8; i++) {
        result <<= 1;              /* result 左移一位，腾出最低位 */
        result |= (byte & 1u);     /* 取 byte 的最低位，放到 result 的最低 */
        byte >>= 1;                /* byte 右移一位，丢掉已处理的最低位 */
    }

    return result;
}
