## ADS1110 ADC library for STM32 HAL
*	Author:     Nima Askari
*	WebSite:    https://www.github.com/NimaLTD
*	Instagram:  https://www.instagram.com/github.NimaLTD
*	LinkedIn:   https://www.linkedin.com/in/NimaLTD
*	Youtube:    https://www.youtube.com/@nimaltd
--------------------------------------------------------------------------------   
* Enable a configure I2C in CubeMX.
* Add library to your project.
* Create a struct.
* Call `ads1110_init()`.
* If you are using single conversion mode, do not forget call 'ads1110_start_conversion'.
--------------------------------------------------------------------------------
## example:

```
#include "ads1110.h"

ads1110_t ads;
float adc_mv;

int main()
{
  ads1110_init(&ads, &hi2c1, ads1110_address_A0);
  ads1110_set_gain(&ads, ads1110_gain_2);
  ads1110_set_rate(&ads, ads1110_rate_15);
  ads1110_set_single_mode(&ads);
  while (1)
  {
    ads1110_start_conversion(&ads);
    HAL_Delay(10);
    ads1110_read_mv(&ads, &adc_mv);
    .
    .
    .
  }  
}
```
