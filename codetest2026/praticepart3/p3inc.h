#ifndef STATUS_WORD_H
#define STATUS_WORD_H

#include <stdint.h>

/* 第1步：定义枚举（status_err_t） */
typedef enum {
    STATUS_OK        =  0,
    STATUS_ERR_NULL  = -1,
    STATUS_ERR_PARAM = -2
} status_err_t;

/* 第2步：定义结构体（status_fields_t） */
typedef struct {
    uint8_t  enable;
    uint8_t  error;
    uint8_t  temp_c;
    uint8_t  mode;
    uint16_t volt_mv;
} status_fields_t;

/* 第3步：定义宏 */
#define STATUS_ENABLE_POS   0u
#define STATUS_ERROR_POS    1u
#define STATUS_TEMP_POS     4u
#define STATUS_MODE_POS     12u
#define STATUS_VOLT_POS     16u

#define STATUS_ENABLE_MSK   (1u     << STATUS_ENABLE_POS)
#define STATUS_ERROR_MSK    (0x7u   << STATUS_ERROR_POS)
#define STATUS_TEMP_MSK     (0xFFu  << STATUS_TEMP_POS)
#define STATUS_MODE_MSK     (0xFu   << STATUS_MODE_POS)
#define STATUS_VOLT_MSK     (0xFFFFu << STATUS_VOLT_POS)

/* 第4步：函数声明（放在最后） */
void status_decode(uint32_t raw, status_fields_t *fields);
status_err_t status_encode(const status_fields_t *fields, uint32_t *raw);
status_err_t status_fields_check(const status_fields_t *fields);
void status_set_enable(uint32_t *raw, uint8_t on);
void status_print(uint32_t raw);

#endif /* STATUS_WORD_H */