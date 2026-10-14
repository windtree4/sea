#include <stdio.h>
#include <stdint.h>
#include "p3inc.h"












/* 解码：把 raw 拆成 5 个字段写到 *fields。纯计算，直接返回 void。
* 调用者保证 fields 不是空指针。 */
void status_decode(uint32_t raw, status_fields_t *fields)
{
    fields->enable  = (raw >> 0)  & 0x1;
    fields->error   = (raw >> 1)  & 0x7;
    fields->temp_c  = (raw >> 4)  & 0xFF;
    fields->mode    = (raw >> 12) & 0xF;
    fields->volt_mv = (raw >> 16) & 0xFFFF;
}

    
    

/* ⭐打包：把 *fields 的 5 个字段拼成一个 32 位状态字写到 *raw。
*   fields 或 raw 为 NULL -> STATUS_ERR_NULL
*   
字段超出取值范围-> STATUS_ERR_PARAM，且不修改 *raw
      全部合法        -> STATUS_OK */
status_err_t status_encode(const status_fields_t *fields, uint32_t *raw)
{
    /* 1. 判空 */
    if (fields == NULL || raw == NULL) {
        return STATUS_ERR_NULL;
    }

    /* 2. 检查字段是否越界 */
    if (status_fields_check(fields) != STATUS_OK) {
        return STATUS_ERR_PARAM;
    }

    /* 3. 拼装 *//*⭐*/
    *raw = 0;
    *raw |= (uint32_t)(fields->enable   & 0x1)    << 0;
    *raw |= (uint32_t)(fields->error    & 0x7)    << 1;
    *raw |= (uint32_t)(fields->temp_c   & 0xFF)   << 4;
    *raw |= (uint32_t)(fields->mode     & 0xF)    << 12;
    *raw |= (uint32_t)(fields->volt_mv  & 0xFFFF) << 16;

    return STATUS_OK;
}



/* 检查 5 个字段是否都在取值范围内。
*   fields == NULL -> STATUS_ERR_NULL
*   
有字段越界     -> STATUS_ERR_PARAM
*   
全部合法
      -> STATUS_ERR_PARAM，且不修改 *raw
              -> STATUS_OK */
       
/* 范围：enable 0~1、error 0~7、mode 0~15；temp_c 和 volt_mv 的类型已限定范围。 */
status_err_t status_fields_check(const status_fields_t *fields)
{
     if (fields == NULL) {
        return STATUS_ERR_NULL;
    }
    if(fields->enable>1|fields->error>7|fields->mode>15){
return  STATUS_ERR_PARAM;
    }
return STATUS_OK;
}



/* 把 *raw 的 bit0 置 1（on 非 0）或清 0（on 为 0），其他 31 位保持原值。
* 调用者保证 raw 不是空指针。 */
void status_set_enable(uint32_t *raw, uint8_t on)
{
    if (on != 0) {
        *raw |= STATUS_ENABLE_MSK;        /* 置1 */
    } else {
        *raw &= ~STATUS_ENABLE_MSK;       /* 清0 */
    }
}


/* 按下面格式打印，调用者保证输出可用。 */
void status_print(uint32_t raw)
{

    /* 第1步：定义一个结构体变量，用来接收解码后的字段 */
    status_fields_t f;

    /* 第2步：调用 status_decode，把 raw 拆成5个字段 */
    status_decode(raw, &f);

    /* 第3步：按题目要求的格式打印 */
    printf("raw=0x%08X en=%u err=%u temp=%u mode=%u mv=%u\n",
           raw,
           (uint32_t)f.enable,
           (uint32_t)f.error,
           (uint32_t)f.temp_c,
           (uint32_t)f.mode,
           (uint32_t)f.volt_mv);


}