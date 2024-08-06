[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MS5837

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ms5837/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MS5837 consists of a piezo-resistive sensor and a sensor interface integrated circuit. The main function of the MS5837 is to convert the uncompensated analogue output voltage from the piezo-resistive pressure sensor to a 24-bit digital value, as well as providing a 24-bit digital value for the temperature of the sensor.It can be used in fitness trackers, drones, bike computers and so on.

LibDriver MS5837 is the MS5837 full function driver launched by LibDriver.It provides temperature reading, pressure reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MS5837 source files.

/interface includes LibDriver MS5837 IIC platform independent template.

/test includes LibDriver MS5837 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MS5837 sample code.

/doc includes LibDriver MS5837 offline document.

/datasheet includes MS5837 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_ms5837_basic.h"

uint8_t res;
uint32_t i;
uint32_t times;

/* basic init */
res = ms5837_basic_init(MS5837_TYPE_02BA01);
if (res != 0)
{
    return 1;
}

...
    
times = 3;

...
    
for (i = 0; i < times; i++)
{
    float temperature_c;
    float pressure_mbar;

    /* read data */
    res = ms5837_basic_read(&temperature_c, &pressure_mbar);
    if (res != 0)
    {
        (void)ms5837_basic_deinit();

        return 1;
    }

    /* output */
    ms5837_interface_debug_print("ms5837: %d/%d.\n", i + 1, times);
    ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
    ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);

    /* delay 1000ms */
    ms5837_interface_delay_ms(1000);
    
    ...
}

...
    
/* deinit */
(void)ms5837_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/ms5837/index.html](https://www.libdriver.com/docs/ms5837/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.