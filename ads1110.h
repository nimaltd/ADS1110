#ifndef _ADS1110_H_
#define _ADS1110_H_

/*
  Author:     Nima Askari
  WebSite:    http://www.github.com/NimaLTD
  Instagram:  http://instagram.com/github.NimaLTD
  Youtube:    https://www.youtube.com/channel/UCUhY7qY1klJm1d2kulr9ckw
  
  Version:    1.0.0
  
  Reversion History:
  (1.0.0)
  First release.
  
*/

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "main.h"

/***************************************************************************************************************/

#define ADS1110_REF           2048.0f

typedef enum
{
  ads1110_address_A0 = 0x48 << 1,
  ads1110_address_A1, 
  ads1110_address_A2, 
  ads1110_address_A3, 
  ads1110_address_A4, 
  ads1110_address_A5, 
  ads1110_address_A6, 
  ads1110_address_A7,  
  ads1110_address_auto = 0xFF
  
}ads1110_address_t;

typedef enum
{
  ads1110_gain_1 = 0,
  ads1110_gain_2 = 1,
  ads1110_gain_4 = 2,
  ads1110_gain_8 = 3
  
}ads1110_gain_t;

typedef enum
{
  ads1110_rate_240 = 0,
  ads1110_rate_60 = 1,
  ads1110_rate_30 = 2,
  ads1110_rate_15 = 3
  
}ads1110_rate_t;

typedef struct
{
  uint8_t   PGA:2;
  uint8_t   DR:2;
  uint8_t   SC:1;
  uint8_t   reserved:2;
  uint8_t   ST_DRDY:1;    
  
}ads1110_config_t;

typedef struct
{
  I2C_HandleTypeDef*  i2c_handle;
  ads1110_address_t   address;
  ads1110_config_t    config;
     
}ads1110_t;

/***************************************************************************************************************/
bool    ads1110_init(ads1110_t *handle, I2C_HandleTypeDef *i2c_handle, ads1110_address_t address);
bool    ads1110_set_gain(ads1110_t *handle, ads1110_gain_t gain);
bool    ads1110_set_rate(ads1110_t *handle, ads1110_rate_t rate);
bool    ads1110_set_single_mode(ads1110_t *handle);
bool    ads1110_set_continues_mode(ads1110_t *handle);
bool    ads1110_start_conversion(ads1110_t *handle);
bool    ads1110_available(ads1110_t *handle);
bool    ads1110_read_raw(ads1110_t *handle, int16_t *adc_raw);
bool    ads1110_read_mv(ads1110_t *handle, float *adc_mv);

/***************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif

