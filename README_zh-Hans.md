[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MS5837

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ms5837/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MS5837由一个压阻式传感器和一个传感器接口集成电路组成。MS5837的主要功能是将压阻式压力传感器的无补偿模拟输出电压转换为24位数字值，并为传感器的温度提供24位数字数值。它可以用于健身跟踪器、无人机、自行车电脑等。

LibDriver MS5837是LibDriver推出的MS5837全功能驱动，该驱动提供压力读取、温度读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MS5837的源文件。

/interface目录包含了LibDriver MS5837与平台无关的IIC总线模板。

/test目录包含了LibDriver MS5837驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MS5837编程范例。

/doc目录包含了LibDriver MS5837离线文档。

/datasheet目录包含了MS5837数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/ms5837/index.html](https://www.libdriver.com/docs/ms5837/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。