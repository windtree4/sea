/* ==========================================================================
* checksum.h —— 校验值计算模块
*
* 本模块只做计算，返回值就是校验值本身。
*
* 长度约定：长度由调用者单独用 uint32_t 传进来。
* 形参 data 是指针，函数里 sizeof(data) 得到的是指针大小，不是缓冲区长度。
*
* 参数约定：写成 const uint8_t *，表示本函数只读，不修改调用者的数据。
*
* data == NULL 或 len == 0 时返回 0。
* ========================================================================== */
#ifndef CHECKSUM_H
#define CHECKSUM_H
#include <stdint.h>
/* 累加和：所有字节相加后取低 8 位（对 256 取模）。 */
uint8_t cksum_sum8(const uint8_t *data, uint32_t len);
/* 异或校验：所有字节逐字节异或，初值 0。 */
uint8_t cksum_xor8(const uint8_t *data, uint32_t len);
/* ★ 延伸：CRC8
* 多项式 0x07，初值 0x00，不反转，异或输出 0x00。
* 标准值：crc8("123456789", 9) == 0xF4 */
uint8_t crc8(const uint8_t *data, uint32_t len);
/* ★ 延伸：CRC16
* 多项式 0xA001（反射写法），初值 0xFFFF，异或输出 0x0000。
* 标准值：crc16("123456789", 9) == 0x4B37 */
uint16_t crc16(const uint8_t *data, uint32_t len);
#endif /* CHECKSUM_H */
