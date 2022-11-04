
#include "ads1110.h"

/***************************************************************************************************************/
bool ads1110_read(ads1110_t *handle, uint8_t *data)
{
  if (HAL_I2C_Master_Receive(handle->i2c_handle, handle->address | 0x01, data, 3, 100) == HAL_OK)
  {
    memcpy(&handle->config ,&data[2], 1);
    return true;
  }
  return false; 
}
/***************************************************************************************************************/
bool ads1110_write(ads1110_t *handle, uint8_t data)
{
  if (HAL_I2C_Master_Transmit(handle->i2c_handle, handle->address, &data, 1, 100) == HAL_OK)
  {
    memcpy(&handle->config ,&data, 1);
    return true;
  }
  return false;
}
/***************************************************************************************************************/
bool ads1110_init(ads1110_t *handle, I2C_HandleTypeDef *i2c_handle, ads1110_address_t address)
{
  uint8_t data[3];
  handle->i2c_handle = i2c_handle;
  if (address != ads1110_address_auto)
  {
    handle->address = address; 
    return ads1110_read(handle, data);
  }
  else
  {
    for (int i=ads1110_address_A0; i<= ads1110_address_A7; i++)
    {
      if (ads1110_read(handle, data))
      {
        handle->address = (ads1110_address_t)i;       
        memcpy(&handle->config ,&data[2], 1);
        return true;
      }      
    }    
  }
  return false;  
}
/***************************************************************************************************************/
bool ads1110_set_gain(ads1110_t *handle, ads1110_gain_t gain)
{
  uint8_t data;
  handle->config.PGA = gain;
  memcpy (&data, &handle->config, 1);
  return ads1110_write(handle, data);
}
/***************************************************************************************************************/
bool ads1110_set_rate(ads1110_t *handle, ads1110_rate_t rate)
{
  uint8_t data;
  handle->config.DR = rate;
  memcpy (&data, &handle->config, 1);
  return ads1110_write(handle, data);
}
/***************************************************************************************************************/
bool ads1110_set_single_mode(ads1110_t *handle)
{
  uint8_t data;
  handle->config.SC = 1;
  memcpy (&data, &handle->config, 1);
  return ads1110_write(handle, data);
}
/***************************************************************************************************************/
bool ads1110_set_continues_mode(ads1110_t *handle)
{
  uint8_t data;
  handle->config.SC = 0;
  memcpy (&data, &handle->config, 1);
  return ads1110_write(handle, data);
}
/***************************************************************************************************************/
bool ads1110_start_conversion(ads1110_t *handle)
{
  uint8_t data;
  handle->config.ST_DRDY = 1;
  memcpy (&data, &handle->config, 1);
  return ads1110_write(handle, data);
}
/***************************************************************************************************************/
bool ads1110_available(ads1110_t *handle)
{
  uint8_t data[3];    
  if (ads1110_read(handle, data))
  {
    if (handle->config.ST_DRDY == 0)
      return true;
  }
  return false;
}
/***************************************************************************************************************/
bool ads1110_read_raw(ads1110_t *handle, int16_t *adc_raw)
{
  uint8_t data[3];    
  if (ads1110_read(handle, data))
  {
    *adc_raw = data[0] << 8;
    *adc_raw |= data[1];
    return true;    
  }
  return false; 
}
/***************************************************************************************************************/
bool ads1110_read_mv(ads1110_t *handle, float *adc_mv)
{
  int16_t adc_raw;
  float res_div;
  float gain;
  if (ads1110_read_raw(handle, &adc_raw) == false)
    return false; 
  if (handle->config.PGA == ads1110_gain_1)
    gain = 1.0f;
  else if (handle->config.PGA == ads1110_gain_2)
    gain = 2.0f;
  else if (handle->config.PGA == ads1110_gain_4)
    gain = 4.0f;
  else
    gain = 8.0f; 
  if (handle->config.DR == ads1110_rate_15)
    res_div = 32768.0f;
  else if (handle->config.DR == ads1110_rate_30)
    res_div = 16384.0f;
  else if (handle->config.DR == ads1110_rate_60)
    res_div = 8192.0f;
  else
    res_div = 2048.0f;    
  *adc_mv = ((float)adc_raw * (ADS1110_REF / res_div)) / gain;
  return true;
}
/***************************************************************************************************************/
