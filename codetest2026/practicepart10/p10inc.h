/* ==========================================================================
* frame.h —— 通信帧的解析与打包
*
* 帧格式（LEN 是 DATA 的字节数，取值 0 ~ 8）：
*
*   
字节偏移:   0      1      2      3              3+LEN      3+LEN+1
*             +------+------+------+--------------+----------+
*             | SOF  | LEN  | CMD  |   DATA[0..]  |   CRC    |
*             | 0xAA | 1 B  | 1 B  |    LEN B     |   1 B    |
*             +------+------+------+--------------+----------+
*
*   
总长度 = LEN + 4
*   CRC8 的计算范围 = LEN、CMD、DATA，即从字节 1 开始的 (2 + LEN) 个字节
*
19 / 25
 * 解析、打包、扫描都要做长度和校验判断，失败原因需要区分，所以返回错误码。
 * 解析时必须逐字段搬运（memcpy），不得把字节流强转成 frame_t *。
 * ========================================================================== */
#ifndef FRAME_H
#define FRAME_H
#include <stdint.h>
#define FRAME_SOF        0xAA                        /* 帧头字节 */
#define FRAME_DATA_MAX   8u                          /* DATA 字段最多 8 字节 */
#define FRAME_OVERHEAD   4u                          /* SOF + LEN + CMD + CRC */
#define FRAME_BUF_MAX    (FRAME_DATA_MAX + FRAME_OVERHEAD)
/* 返回码 */
typedef enum {
    FRAME_OK        =  0,   /* 成功 */
    FRAME_ERR_NULL  = -1,   /* 指针是空指针 */
    FRAME_ERR_SOF   = -2,   /* 帧头不是 0xAA */
    FRAME_ERR_LEN   = -3,   /* 长度字段非法，或缓冲区装不下这一帧 */
    FRAME_ERR_CRC   = -4,   /* 校验不通过 */
    FRAME_ERR_EMPTY = -5    /* 扫描结束仍未找到完整帧 */
} frame_err_t;
typedef struct {
    uint8_t cmd;                  /* CMD 字段：命令码 */
    uint8_t len;                  /* LEN 字段：data 里有效的字节数，0 ~ 8 */
    uint8_t data[FRAME_DATA_MAX]; /* DATA 字段：只有前 len 个字节有效 */
} frame_t;
/* 解析一帧。buf 指向帧首，buf_len 是从帧首开始剩余的字节数。
 * 判断顺序：
 *   buf 或 out 为 NULL              -> FRAME_ERR_NULL
 *   buf_len < FRAME_OVERHEAD        -> FRAME_ERR_LEN
 *   buf[0] != FRAME_SOF             -> FRAME_ERR_SOF
 *   LEN 超出 0 ~ FRAME_DATA_MAX     -> FRAME_ERR_LEN
 *   buf_len < LEN + FRAME_OVERHEAD  -> FRAME_ERR_LEN
 *   CRC8 不匹配                     -> FRAME_ERR_CRC
 *   全部通过                        -> FRAME_OK，填好 *out
 * 成功时填 out->len、out->cmd、out->data[0..len-1]；失败时不修改 *out。 */
frame_err_t frame_parse(const uint8_t *buf, uint32_t buf_len, frame_t *out);
/* 打包一帧，写入的字节数（LEN + 4）写到 *out_len。
 *   frame、buf、out_len 任一为 NULL        -> FRAME_ERR_NULL
 *   frame->len > FRAME_DATA_MAX            -> FRAME_ERR_LEN
 *   buf_size < frame->len + FRAME_OVERHEAD -> FRAME_ERR_LEN
 *   成功                                   -> FRAME_OK
 * 失败时不写 buf，也不修改 *out_len。 */
frame_err_t frame_build(const frame_t *frame, uint8_t *buf, uint32_t buf_size,
                        uint32_t *out_len);
/* 在缓冲区里从头找第一帧能成功解析的数据。
 *   buf、out、out_offset 任一为 NULL -> FRAME_ERR_NULL
 *   找到                             -> FRAME_OK，*out_offset 为帧首相对 buf 的字节
偏移，*out 填好
扫描结束仍未找到-> FRAME_ERR_EMPTY
* 实现要求：
*   - 用两个指针 p / end 控制循环边界，用指针比较判断是否走到头；
*   - 当前位置不是帧头时用 continue 跳过，往后挪一个字节继续找；
*   - 某个 0xAA 后面这一帧不合格时也继续往后找，不得直接返回失败；
*   - *out_offset 只在成功时写。 */
frame_err_t frame_scan(const uint8_t *buf, uint32_t buf_len,
uint32_t *out_offset, frame_t *out);
/* 按下面格式打印一帧（每个数据字节 %02X 后跟一个空格）：
*   cmd=0x01 len=3 data=11 22 33
* 调用者保证 frame 不是空指针。 */
void frame_print(const frame_t *frame);
#endif /* FRAME_H*/