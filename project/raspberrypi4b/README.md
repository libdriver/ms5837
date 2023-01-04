### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ms5837 REQUIRED)
```

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
./ms5837 -i

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
./ms5837 -p

ms5837: SCL connected to GPIO3.
ms5837: SDA connected to GPIO2.
```

```shell
./ms5837 -t read --type=02BA01 --times=3

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
ms5837: temperature is 30.02C.
ms5837: pressure is 1018.89mbar.
ms5837: pressure is 1019.13mbar.
ms5837: temperature is 30.02C.
ms5837: temperature is 30.02C.
ms5837: pressure is 1019.10mbar.
ms5837: pressure is 1019.26mbar.
ms5837: temperature is 30.00C.
ms5837: temperature is 30.00C.
ms5837: pressure is 1019.06mbar.
ms5837: pressure is 1019.02mbar.
ms5837: temperature is 30.00C.
ms5837: osr 512.
ms5837: temperature is 30.02C.
ms5837: pressure is 1019.10mbar.
ms5837: pressure is 1019.06mbar.
ms5837: temperature is 29.98C.
ms5837: temperature is 29.98C.
ms5837: pressure is 1019.02mbar.
ms5837: pressure is 1019.19mbar.
ms5837: temperature is 29.95C.
ms5837: temperature is 29.95C.
ms5837: pressure is 1019.15mbar.
ms5837: pressure is 1019.15mbar.
ms5837: temperature is 29.95C.
ms5837: osr 1024.
ms5837: temperature is 29.91C.
ms5837: pressure is 1019.17mbar.
ms5837: pressure is 1019.25mbar.
ms5837: temperature is 29.87C.
ms5837: temperature is 29.86C.
ms5837: pressure is 1019.16mbar.
ms5837: pressure is 1019.20mbar.
ms5837: temperature is 29.85C.
ms5837: temperature is 29.85C.
ms5837: pressure is 1019.14mbar.
ms5837: pressure is 1019.25mbar.
ms5837: temperature is 29.86C.
ms5837: osr 2048.
ms5837: temperature is 29.85C.
ms5837: pressure is 1019.19mbar.
ms5837: pressure is 1019.19mbar.
ms5837: temperature is 29.85C.
ms5837: temperature is 29.82C.
ms5837: pressure is 1019.24mbar.
ms5837: pressure is 1019.09mbar.
ms5837: temperature is 29.83C.
ms5837: temperature is 29.82C.
ms5837: pressure is 1019.23mbar.
ms5837: pressure is 1019.16mbar.
ms5837: temperature is 29.81C.
ms5837: osr 4096.
ms5837: temperature is 29.81C.
ms5837: pressure is 1019.33mbar.
ms5837: pressure is 1019.29mbar.
ms5837: temperature is 29.79C.
ms5837: temperature is 29.79C.
ms5837: pressure is 1019.33mbar.
ms5837: pressure is 1019.33mbar.
ms5837: temperature is 29.78C.
ms5837: temperature is 29.77C.
ms5837: pressure is 1019.29mbar.
ms5837: pressure is 1019.33mbar.
ms5837: temperature is 29.77C.
ms5837: osr 8192.
ms5837: temperature is 29.75C.
ms5837: pressure is 1019.31mbar.
ms5837: pressure is 1019.21mbar.
ms5837: temperature is 29.74C.
ms5837: temperature is 29.73C.
ms5837: pressure is 1019.27mbar.
ms5837: pressure is 1019.25mbar.
ms5837: temperature is 29.70C.
ms5837: temperature is 29.69C.
ms5837: pressure is 1019.33mbar.
ms5837: pressure is 1019.31mbar.
ms5837: temperature is 29.66C.
ms5837: finish read test.
```

```shell
./ms5837 -e read --type=02BA01 --times=3

ms5837: 1/3.
ms5837: temperature is 29.52C.
ms5837: pressure is 1019.23mbar.
ms5837: 2/3.
ms5837: temperature is 29.52C.
ms5837: pressure is 1019.22mbar.
ms5837: 3/3.
ms5837: temperature is 29.52C.
ms5837: pressure is 1019.22mbar.
```

```shell
./ms5837 -h

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

