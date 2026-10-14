#include <stdio.h>
#include<stdint.h>
#include "p10inc.h"
/* 函数1描述：解析一帧。❓buf 指向帧首，buf_len 是从帧首开始剩余的字节数。❓
 * 判断顺序：
 *   buf 或 out 为 NULL              -> FRAME_ERR_NULL
 *   buf_len < FRAME_OVERHEAD (这是宏定义)       -> FRAME_ERR_LEN
 *   buf[0] != FRAME_SOF             -> FRAME_ERR_SOF
 *   LEN 超出 0 ~ FRAME_DATA_MAX     -> FRAME_ERR_LEN
 *   buf_len < LEN + FRAME_OVERHEAD  -> FRAME_ERR_LEN
 *   CRC8 不匹配                     -> FRAME_ERR_CRC
 *   全部通过                        -> FRAME_OK，填好 *out
 * 成功时填 out->len、out->cmd、out->data[0..len-1]；失败时不修改 *out。 */
frame_err_t frame_parse(const uint8_t *buf, uint32_t buf_len, frame_t *out)
{

    if (buf == NULL || out == NULL) {
        return FRAME_ERR_NULL;
    }

    
    if (buf_len < FRAME_OVERHEAD) {
        return FRAME_ERR_LEN;
    }

    
    if (buf[0] != FRAME_SOF) {
        return FRAME_ERR_SOF;
    }

    
    uint8_t data_len = buf[1];
    if (data_len > FRAME_DATA_MAX) {
        return FRAME_ERR_LEN;
    }
    if (buf_len < data_len + FRAME_OVERHEAD) {
        return FRAME_ERR_LEN;
    }
    out->len = data_len;
    out->cmd = buf[2];
    if (data_len > 0) {
        memcpy(out->data, &buf[3], data_len);
    }
    if (crc8(&buf[1], 2 + data_len) != buf[3 + data_len]) {
        return FRAME_ERR_CRC;
    }
    return FRAME_OK; /*framephase结束*/
}















/* 打包一帧，写入的字节数（LEN + 4）写到 *out_len。
 *   frame、buf、out_len 任一为 NULL        -> FRAME_ERR_NULL
 *   frame->len > FRAME_DATA_MAX            -> FRAME_ERR_LEN
 *   buf_size < frame->len + FRAME_OVERHEAD -> FRAME_ERR_LEN
 *   成功                                   -> FRAME_OK
 * 失败时不写 buf，也不修改 *out_len。 */
/*frame_build
1. 判空、
判frame->len > FRAME_DATA_MAX
、判
 buf_size 
是否⾜够，任⼀不满⾜返回对应错误码
2. 
写
 buf[0] = FRAME_SOF
、
buf[1] = len
、
buf[2] = cmd
，
memcpy 
数据到
 &buf[3]
3. buf[3 + len] = crc8(&buf[1], 2 + len)
；
*out_len = len + 4
；返回FRAME_OK*/
frame_err_t frame_build(const frame_t *frame, uint8_t *buf, uint32_t buf_size,
                        uint32_t *out_len)
{
    
    if (frame == NULL || buf == NULL || out_len == NULL) {
        return FRAME_ERR_NULL;
    }

    
    if (frame->len > FRAME_DATA_MAX) {
        return FRAME_ERR_LEN;
    }

    
    if (buf_size < frame->len + FRAME_OVERHEAD) {
        return FRAME_ERR_LEN;
    }

    
    buf[0] = FRAME_SOF;
    buf[1] = frame->len;
    buf[2] = frame->cmd;

    
    if (frame->len > 0) {
        memcpy(&buf[3], frame->data, frame->len);
    }

    
    buf[3 + frame->len] = crc8(&buf[1], 2 + frame->len);

    
    *out_len = frame->len + FRAME_OVERHEAD;   /* FRAME_OVERHEAD = 4 */

    
    return FRAME_OK;/*函数2frame build结束*/
}




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
uint32_t *out_offset, frame_t *out)/*函数3开始*/
{
   
   const uint8_t *p;      /* 当前检查的位置 */
   const uint8_t *end;    /* buf + buf_len */
   if(buf==NULL || out==NULL || out_offset== NULL){
return FRAME_ERR_NULL;
   }   
   end = buf + buf_len;/*end is a vary?*/
for (p = buf; p + FRAME_OVERHEAD /*?*/<= end; p++) {
if (*p != FRAME_SOF) {
continue;
}
if (frame_parse(p, (uint32_t)(end - p), out) == FRAME_OK/*?*/) {
*out_offset = (uint32_t)(p - buf);
return FRAME_OK;
}
}
return FRAME_ERR_EMPTY;
}



/* 按下面格式打印一帧（每个数据字节 %02X 后跟一个空格）：
*   cmd=0x01 len=3 data=11 22 33
* 调用者保证 frame 不是空指针。 */
void frame_print(const frame_t *frame)
{
    uint8_t i=0;
   return( "data[i]=0x%02X ",data*buf +data*buf len);
}