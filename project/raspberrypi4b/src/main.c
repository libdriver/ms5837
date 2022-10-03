/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-09-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/09/30  <td>1.0      <td>Shifeng Li  <td>format the code
 * </table>
 */

#include "driver_ms5837_read_test.h"
#include "driver_ms5837_basic.h"
#include <stdlib.h>

/**
 * @brief     ms5837 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ms5837(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ms5837_info_t info;
            
            /* print ms5837 info */
            ms5837_info(&info);
            ms5837_interface_debug_print("ms5837: chip is %s.\n", info.chip_name);
            ms5837_interface_debug_print("ms5837: manufacturer is %s.\n", info.manufacturer_name);
            ms5837_interface_debug_print("ms5837: interface is %s.\n", info.interface);
            ms5837_interface_debug_print("ms5837: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000 ) / 100);
            ms5837_interface_debug_print("ms5837: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            ms5837_interface_debug_print("ms5837: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            ms5837_interface_debug_print("ms5837: max current is %0.2fmA.\n", info.max_current_ma);
            ms5837_interface_debug_print("ms5837: max temperature is %0.1fC.\n", info.temperature_max);
            ms5837_interface_debug_print("ms5837: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ms5837_interface_debug_print("ms5837: SCL connected to GPIO3.\n");
            ms5837_interface_debug_print("ms5837: SDA connected to GPIO2.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ms5837 help */
            
            help:
            ms5837_interface_debug_print("ms5837 -i\n\tshow ms5837 chip and driver information.\n");
            ms5837_interface_debug_print("ms5837 -h\n\tshow ms5837 help.\n");
            ms5837_interface_debug_print("ms5837 -p\n\tshow ms5837 pin connections of the current board.\n");
            ms5837_interface_debug_print("ms5837 -t read <times> -type (02BA01 | 02BA21 | 30BA26)\n\trun ms5837 read test.times is the test times.\n");
            ms5837_interface_debug_print("ms5837 -c read <times> -type (02BA01 | 02BA21 | 30BA26)\n\trun ms5837 read function.times is the read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                ms5837_type_t type;
                
                if (strcmp("-type", argv[4]) != 0)
                {
                    ms5837_interface_debug_print("ms5837: no type.\n");
                    
                    return 1;
                }
                if (strcmp("02BA01", argv[5]) == 0)
                {
                    type = MS5837_TYPE_02BA01;
                    ms5837_interface_debug_print("ms5837: 02BA01 type.\n");
                }
                else if (strcmp("02BA21", argv[5]) == 0)
                {
                    type = MS5837_TYPE_02BA21;
                    ms5837_interface_debug_print("ms5837: 02BA21 type.\n");
                }
                else if (strcmp("30BA26", argv[5]) == 0)
                {
                    type = MS5837_TYPE_30BA26;
                    ms5837_interface_debug_print("ms5837: 30BA26 type.\n");
                }
                else
                {
                    ms5837_interface_debug_print("ms5837: unknown type.\n");
                    
                    return 1;
                }
                
                /* run the read test */
                res = ms5837_read_test(type, atoi(argv[3]));
                if (res != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i, times;
                ms5837_type_t type;
                
                if (strcmp("-type", argv[4]) != 0)
                {
                    ms5837_interface_debug_print("ms5837: no type.\n");
                    
                    return 1;
                }
                if (strcmp("02BA01", argv[5]) == 0)
                {
                    type = MS5837_TYPE_02BA01;
                    ms5837_interface_debug_print("ms5837: 02BA01 type.\n");
                }
                else if (strcmp("02BA21", argv[5]) == 0)
                {
                    type = MS5837_TYPE_02BA21;
                    ms5837_interface_debug_print("ms5837: 02BA21 type.\n");
                }
                else if (strcmp("30BA26", argv[5]) == 0)
                {
                    type = MS5837_TYPE_30BA26;
                    ms5837_interface_debug_print("ms5837: 30BA26 type.\n");
                }
                else
                {
                    ms5837_interface_debug_print("ms5837: unknown type.\n");
                    
                    return 1;
                }
                
                times =  atoi(argv[3]);
                
                /* basic init */
                res = ms5837_basic_init(type);
                if (res != 0)
                {
                    return 1;
                }
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
                }
                
                /* deinit */
                (void)ms5837_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = ms5837(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        ms5837_interface_debug_print("ms5837: run failed.\n");
    }
    else if (res == 5)
    {
        ms5837_interface_debug_print("ms5837: param is invalid.\n");
    }
    else
    {
        ms5837_interface_debug_print("ms5837: unknow status code.\n");
    }

    return 0;
}
