### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MS5837

#### 3.1 Command Instruction

1. Show ms5837 chip and driver information.

   ```shell
   ms5837 (-i | --information)
   ```

2. Show ms5837  help.

   ```shell
   ms5837 (-h | --help)
   ```

3. Show ms5837 pin connections of the current board.

   ```shell
   ms5837 (-p | --port)
   ```

4. Run ms5837  read test, num is the test times.

   ```shell
   ms5837 (-t read | --test=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]
   ```

5. Run ms5837 read function, num is the read times.

   ```shell
   ms5837 (-e read | --example=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
ms5837 -i

ms5837: chip is TE MS5837.
ms5837: manufacturer is TE.
ms5837: interface is IIC.
ms5837: driver version is 1.0.
ms5837: min supply voltage is 1.5V.
ms5837: max supply voltage is 3.6V.
ms5837: max current is 1.25mA.
ms5837: max temperature is 85.0C.
ms5837: min temperature is -40.0C.
```

```shell
ms5837 -p

ms5837: SCL connected to GPIOB PIN8.
ms5837: SDA connected to GPIOB PIN9.
```

```shell
ms5837 -t read --type=02BA01 --times=3

ms5837: chip is TE MS5837.
ms5837: manufacturer is TE.
ms5837: interface is IIC.
ms5837: driver version is 1.0.
ms5837: min supply voltage is 1.5V.
ms5837: max supply voltage is 3.6V.
ms5837: max current is 1.25mA.
ms5837: max temperature is 85.0C.
ms5837: min temperature is -40.0C.
ms5837: start read test.
ms5837: osr 256.
ms5837: temperature is 27.84C.
ms5837: pressure is 1018.66mbar.
ms5837: pressure is 1018.83mbar.
ms5837: temperature is 27.84C.
ms5837: temperature is 27.82C.
ms5837: pressure is 1018.62mbar.
ms5837: pressure is 1018.59mbar.
ms5837: temperature is 27.79C.
ms5837: temperature is 27.79C.
ms5837: pressure is 1018.55mbar.
ms5837: pressure is 1018.55mbar.
ms5837: temperature is 27.79C.
ms5837: osr 512.
ms5837: temperature is 27.77C.
ms5837: pressure is 1018.71mbar.
ms5837: pressure is 1018.71mbar.
ms5837: temperature is 27.75C.
ms5837: temperature is 27.74C.
ms5837: pressure is 1018.64mbar.
ms5837: pressure is 1018.60mbar.
ms5837: temperature is 27.72C.
ms5837: temperature is 27.72C.
ms5837: pressure is 1018.80mbar.
ms5837: pressure is 1018.77mbar.
ms5837: temperature is 27.69C.
ms5837: osr 1024.
ms5837: temperature is 27.68C.
ms5837: pressure is 1018.72mbar.
ms5837: pressure is 1018.76mbar.
ms5837: temperature is 27.66C.
ms5837: temperature is 27.66C.
ms5837: pressure is 1018.67mbar.
ms5837: pressure is 1018.77mbar.
ms5837: temperature is 27.64C.
ms5837: temperature is 27.64C.
ms5837: pressure is 1018.68mbar.
ms5837: pressure is 1018.70mbar.
ms5837: temperature is 27.62C.
ms5837: osr 2048.
ms5837: temperature is 27.62C.
ms5837: pressure is 1018.85mbar.
ms5837: pressure is 1018.83mbar.
ms5837: temperature is 27.60C.
ms5837: temperature is 27.60C.
ms5837: pressure is 1018.70mbar.
ms5837: pressure is 1018.82mbar.
ms5837: temperature is 27.59C.
ms5837: temperature is 27.57C.
ms5837: pressure is 1018.79mbar.
ms5837: pressure is 1018.66mbar.
ms5837: temperature is 27.56C.
ms5837: osr 4096.
ms5837: temperature is 27.56C.
ms5837: pressure is 1018.84mbar.
ms5837: pressure is 1018.88mbar.
ms5837: temperature is 27.55C.
ms5837: temperature is 27.54C.
ms5837: pressure is 1018.91mbar.
ms5837: pressure is 1018.96mbar.
ms5837: temperature is 27.53C.
ms5837: temperature is 27.52C.
ms5837: pressure is 1018.88mbar.
ms5837: pressure is 1018.93mbar.
ms5837: temperature is 27.51C.
ms5837: osr 8192.
ms5837: temperature is 27.50C.
ms5837: pressure is 1018.84mbar.
ms5837: pressure is 1018.91mbar.
ms5837: temperature is 27.50C.
ms5837: temperature is 27.48C.
ms5837: pressure is 1018.87mbar.
ms5837: pressure is 1018.89mbar.
ms5837: temperature is 27.48C.
ms5837: temperature is 27.47C.
ms5837: pressure is 1018.86mbar.
ms5837: pressure is 1018.84mbar.
ms5837: temperature is 27.46C.
ms5837: finish read test.
```

```shell
ms5837 -e read --type=02BA01 --times=3

ms5837: 1/3.
ms5837: temperature is 27.31C.
ms5837: pressure is 1018.89mbar.
ms5837: 2/3.
ms5837: temperature is 27.32C.
ms5837: pressure is 1018.88mbar.
ms5837: 3/3.
ms5837: temperature is 27.31C.
ms5837: pressure is 1018.86mbar.
```

```shell
ms5837 -h

Usage:
  ms5837 (-i | --information)
  ms5837 (-h | --help)
  ms5837 (-p | --port)
  ms5837 (-t read | --test=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]
  ms5837 (-e read | --example=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]

Options:
  -e <read>, --example=<read>
                       Run the driver example.
  -h, --help           Show the help.
  -i, --information    Show the chip information.
  -p, --port           Display the pin connections of the current board.
  -t <read>, --test=<read>
                       Run the driver test.
      --times=<num>    Set the running times.([default: 3])
      --type=<02BA01 | 02BA21 | 30BA26>
                       Set the chip type.([default: 02BA01])
```

