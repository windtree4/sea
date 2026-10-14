/* =======================================================================
 * bitops.h —— 位操作工具模块
 *
 * 本模块只做计算，不保存状态，返回值就是计算结果本身。
 *
 * 位号约定：pos / hi / lo 都从 0 开始计数，合法范围 0 ~ 31。
 * 位号或位域范围非法（pos > 31；hi < lo；hi > 31）时的返回值：
 *   - 返回 word 的函数（bit_set / bit_clear / bit_toggle / bit_field_set）：返回 word 原值
 *   - 取值的函数（bit_get / bit_field_get / bit_mask_make）：返回 0
 * ======================================================================= */

#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

/* 把 word 的第 pos 位置 1，返回结果。 */
uint32_t bit_set(uint32_t word, uint8_t pos);

/* 把 word 的第 pos 位清 0，返回结果。 */
uint32_t bit_clear(uint32_t word, uint8_t pos);

/* 把 word 的第 pos 位取反，返回结果。 */
uint32_t bit_toggle(uint32_t word, uint8_t pos);

/* 读出 word 的第 pos 位，返回 0 或 1。 */
uint8_t bit_get(uint32_t word, uint8_t pos);

/* 用 while 循环统计 word 里 1 的个数。 */
uint8_t bit_count(uint32_t word);

/* 用 do...while 循环统计 word 里 1 的个数。 */
uint8_t bit_count_do_while(uint32_t word);

/* 生成 [hi:lo] 这一段全为 1 的掩码。 */
uint32_t bit_mask_make(uint8_t hi, uint8_t lo);

/* 读取 word 的 [hi:lo] 字段，返回该段的值。 */
uint32_t bit_field_get(uint32_t word, uint8_t hi, uint8_t lo);

/* 把 word 的 [hi:lo] 字段设置为 value。 */
uint32_t bit_field_set(uint32_t word, uint8_t hi, uint8_t lo, uint32_t value);

/* 把 8 位数据按位翻转。 */
uint8_t bit_reverse8(uint8_t byte);

#endif /* BITOPS_H */