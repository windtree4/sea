#include <stdio.h>
#include "p3inc.h"

int main()
{
    
    status_fields_t f;

    /* 调用decode*/
    status_decode(0x12345678, &f);
    printf("en=%u err=%u temp=%u mode=%u mv=%u\n",
           (uint32_t)f.enable,
           (uint32_t)f.error,
           (uint32_t)f.temp_c,
           (uint32_t)f.mode,
           (uint32_t)f.volt_mv);



    /*encode*/
uint32_t raw;

f.enable  = 0;
f.error   = 4;
f.temp_c  = 103;
f.mode    = 5;
f.volt_mv = 4660;

status_err_t ret = status_encode(&f, &raw);

if (ret == STATUS_OK) {
    printf("STATUS_OK, raw = 0x%08X\n", raw);
} else {
    printf("ERROR, ret = %d\n", ret);
}  

/*测试check*/
status_err_t  return2=status_fields_check(&f);
{
     if (return2== STATUS_ERR_NULL){
printf ("STATUS_ERR_NULL");
    }
    if(return2==STATUS_ERR_PARAM){
printf("STATUS_ERR_PARAM");
    }
printf("STATUS_OK\n") ;
}

/*置位*/

raw =0x00000000;
status_set_enable(&raw, 1);
printf("raw=0x%08X\n", raw);




/*打印测试*/
status_print(0x12345678);

    }