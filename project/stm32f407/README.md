### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. MS5837

#### 3.1 Command Instruction

​           ms5837  is a basic command which can test all ms5837 driver function:

​           -i        show ms5837 chip and driver information.

​           -h       show ms5837  help.

​           -p       show ms5837 pin connections of the current board.

​           -t read <times>  -type (02BA01 | 02BA21 | 30BA26)        run ms5837  read test. times is the test times.

​           -c read <times>  -type (02BA01 | 02BA21 | 30BA26)        run ms5837 read function. times is the read times.

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
ms5837 -t read 3 -type 02BA01

ms5837: 02BA01 type.
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
ms5837: temperature is 27.29C.
ms5837: pressure is 1002.63mbar.
ms5837: pressure is 1002.63mbar.
ms5837: temperature is 27.31C.
ms5837: temperature is 27.27C.
ms5837: pressure is 1002.59mbar.
ms5837: pressure is 1002.59mbar.
ms5837: temperature is 27.27C.
ms5837: temperature is 27.25C.
ms5837: pressure is 1002.56mbar.
ms5837: pressure is 1002.76mbar.
ms5837: temperature is 27.25C.
ms5837: osr 512.
ms5837: temperature is 27.24C.
ms5837: pressure is 1002.72mbar.
ms5837: pressure is 1002.89mbar.
ms5837: temperature is 27.22C.
ms5837: temperature is 27.22C.
ms5837: pressure is 1002.48mbar.
ms5837: pressure is 1002.69mbar.
ms5837: temperature is 27.20C.
ms5837: temperature is 27.20C.
ms5837: pressure is 1002.85mbar.
ms5837: pressure is 1002.89mbar.
ms5837: temperature is 27.20C.
ms5837: osr 1024.
ms5837: temperature is 27.21C.
ms5837: pressure is 1002.92mbar.
ms5837: pressure is 1002.76mbar.
ms5837: temperature is 27.19C.
ms5837: temperature is 27.19C.
ms5837: pressure is 1002.84mbar.
ms5837: pressure is 1002.74mbar.
ms5837: temperature is 27.19C.
ms5837: temperature is 27.21C.
ms5837: pressure is 1002.67mbar.
ms5837: pressure is 1002.80mbar.
ms5837: temperature is 27.23C.
ms5837: osr 2048.
ms5837: temperature is 27.23C.
ms5837: pressure is 1002.81mbar.
ms5837: pressure is 1002.79mbar.
ms5837: temperature is 27.22C.
ms5837: temperature is 27.22C.
ms5837: pressure is 1002.80mbar.
ms5837: pressure is 1002.77mbar.
ms5837: temperature is 27.25C.
ms5837: temperature is 27.25C.
ms5837: pressure is 1002.76mbar.
ms5837: pressure is 1002.76mbar.
ms5837: temperature is 27.26C.
ms5837: osr 4096.
ms5837: temperature is 27.26C.
ms5837: pressure is 1002.91mbar.
ms5837: pressure is 1002.86mbar.
ms5837: temperature is 27.27C.
ms5837: temperature is 27.27C.
ms5837: pressure is 1002.96mbar.
ms5837: pressure is 1002.97mbar.
ms5837: temperature is 27.27C.
ms5837: temperature is 27.27C.
ms5837: pressure is 1002.90mbar.
ms5837: pressure is 1002.93mbar.
ms5837: temperature is 27.27C.
ms5837: osr 8192.
ms5837: temperature is 27.27C.
ms5837: pressure is 1003.00mbar.
ms5837: pressure is 1002.91mbar.
ms5837: temperature is 27.26C.
ms5837: temperature is 27.27C.
ms5837: pressure is 1002.94mbar.
ms5837: pressure is 1002.91mbar.
ms5837: temperature is 27.26C.
ms5837: temperature is 27.26C.
ms5837: pressure is 1002.96mbar.
ms5837: pressure is 1002.95mbar.
ms5837: temperature is 27.26C.
ms5837: finish read test.
```

```shell
ms5837 -c read 3 -type 02BA01

ms5837: 02BA01 type.
ms5837: 1/3.
ms5837: temperature is 27.06C.
ms5837: pressure is 1002.95mbar.
ms5837: 2/3.
ms5837: temperature is 27.04C.
ms5837: pressure is 1002.98mbar.
ms5837: 3/3.
ms5837: temperature is 27.04C.
ms5837: pressure is 1002.96mbar.
```

```shell
ms5837 -h

ms5837 -i
	show ms5837 chip and driver information.
ms5837 -h
	show ms5837 help.
ms5837 -p
	show ms5837 pin connections of the current board.
ms5837 -t read <times> -type (02BA01 | 02BA21 | 30BA26)
	run ms5837 read test.times is the test times.
ms5837 -c read <times> -type (02BA01 | 02BA21 | 30BA26)
	run ms5837 read function.times is the read times.
```

