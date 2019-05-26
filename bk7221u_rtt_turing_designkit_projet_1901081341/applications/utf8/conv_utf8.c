#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include "typedef.h"
#include <rtthread.h>

#if RT_SUPPORT_UTF8_TO_GBL
#include "conv_utf8_gb2312_table.h"
#include "conv_utf8_pub.h"

static int conv_utf8_for_gb2312(unsigned char *pin, unsigned char *pout)
{
    unsigned char hi_bits, low_bit;
    const unsigned char *utf8;
    unsigned short gb_code, dist_cnt;

    hi_bits = *pin & 0xff;
    low_bit = *(pin+1) & 0xff;

    // chinese char start from 0xB0A1 to 0xF7FE
    if((hi_bits < 0xB0) || (hi_bits > 0xF7))
        return 0;
    if((low_bit < 0xA1) || (low_bit > 0xFE))
        return 0;

    gb_code = (hi_bits<<8) + low_bit;

    // there are 0xa2 banks between two district
    dist_cnt = hi_bits - 0xB0;
    dist_cnt = dist_cnt * (0xA1 + 0x01);

    // shift pos in table
    gb_code = gb_code - 0xB0A1 - dist_cnt;
    utf8 = t_gb2312_utf8[gb_code];

    memcpy(pout, utf8, 3);

    return 1;
}

unsigned char *conv_utf8(unsigned char *input)
{
    int len, i;
    unsigned char *ptr, *out_bak, *out;

    len = strlen(input);
 	len = (len / 2)*3 + 1;   

    out_bak = (unsigned char *)malloc(len);
    if(!out_bak) 
        return NULL;
    
    ptr = input;
    out = out_bak;

    while(*ptr) 
    {
        if(conv_utf8_for_gb2312(ptr, out)) 
        {
            out += 3;
            ptr += 2;
        } else {
            *out = *ptr;
            out++;
            ptr++;
        }
    }
    *out = 0;

    
    for(i=0; out_bak[i] != 0; i++)
        printf("%02x", out_bak[i]);
    
    printf("\r\n");

    return out_bak;
}

unsigned short SearchCodeTable(unsigned short unicodeKey)
{
    int first = 0;
    int end = sizeof(unicode_to_gb2312) / (2 * sizeof(uint16_t)) - 1;
    int mid = 0;

    while (first <= end)
    {
        mid = (first + end) / 2;

        if (unicode_to_gb2312[mid][0] == unicodeKey)
        {
            return unicode_to_gb2312[mid][1];
        }
        else if (unicode_to_gb2312[mid][0] > unicodeKey)
        {
            end = mid - 1;
        }
        else 
        {
            first = mid + 1;
        }
    }
    return 0;
}


int GetUtf8ByteNumForWord(uint8_t firstCh)
{
    uint8_t temp = 0x80;
    int num = 0;

    while (temp & firstCh)
    {
        num++;
        temp = (temp >> 1);
    }
    return num;
}

char* Utf8ToGb2312(char* utf8)
{
    char *temp = NULL;
    int byteCount = 0;
    int len, i = 0, j = 0;

    uint16_t unicodeKey = 0;
    uint16_t gbKey = 0;

    if(!utf8)
        return NULL;
        
    len = strlen(utf8);
    if(len <= 0)
        return NULL;

    temp = malloc(len * sizeof(char)  +  4);
    if(!temp) {
        return NULL;
    }
    
    while (i < len)
    {   
        int nbyte = GetUtf8ByteNumForWord((uint8_t)utf8[i]);
        switch(nbyte)
        {
            case 0:
                temp[j] = utf8[i];
                byteCount = 1;
                j += 1;
            break;

            case 2:
                temp[j] = utf8[i];
                temp[j + 1] = utf8[i + 1];
                byteCount = 2;
                j += 2;
            break;

            case 3:
                temp[j + 1] = ((utf8[i] & 0x0F) << 4) | ((utf8[i + 1] >> 2) & 0x0F);
                temp[j] = ((utf8[i + 1] & 0x03) << 6) + (utf8[i + 2] & 0x3F);

                memcpy(&unicodeKey, (temp + j), 2);

                gbKey = SearchCodeTable(unicodeKey);
                temp[j] = (gbKey & 0xff00)>>8;
                temp[j + 1] = (gbKey & 0x00ff);  

                byteCount = 3;
                j += 2;
            break;

            case 4:
            case 5:
            case 6:
                byteCount = nbyte;
                printf("4-6 utf8 no process, copy them\n");
            break;

            default:
                printf("err! the len is more than 6\n");
                byteCount = 1;
            break;    
        }

        i += byteCount;
    }

    temp[j++] = '\0';
    memcpy(utf8, temp, j);
    
    free(temp);

    return utf8;
}


#endif // CONFIG_USE_CONV_UTF8

