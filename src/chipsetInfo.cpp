#include "chipsetInfo.h"


uint32_t getchipId()
{
        uint32_t chipId = 0;
        for (int i = 0; i < 17; i = i + 8)
        {
                //  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }
        return chipId;
}
String getMac()
{
        // 获取全球唯一的MAC地址     MAC地址，一共48 bit，即6个字节。
        uint8_t mac[6];
        char smac[100];
        char hex_str[3];
        esp_efuse_mac_get_default(mac);
        sprintf(hex_str, "%02X", mac[0]);
        strcpy(smac, hex_str);
        for (int i = 1; i < strlen((char *)mac); i++)
        {
                char hex_str1[3];
                sprintf(hex_str1, "%02X", mac[i]);
                strcat(smac, hex_str1);

                // printf("%2X", mac[i]); // DC5475626670    ---》DC-54-75-62-66-70
        }
        String str=smac;
        return str;
}
