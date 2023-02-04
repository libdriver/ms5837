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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     ms5837 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ms5837(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {"type", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    ms5837_type_t chip_type = MS5837_TYPE_02BA01;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* type */
            case 2 :
            {
                /* set the chip type */
                if (strcmp("02BA01", optarg) == 0)
                {
                    chip_type = MS5837_TYPE_02BA01;
                }
                else if (strcmp("02BA21", optarg) == 0)
                {
                    chip_type = MS5837_TYPE_02BA21;
                }
                else if (strcmp("30BA26", optarg) == 0)
                {
                    chip_type = MS5837_TYPE_30BA26;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = ms5837_read_test(chip_type, times);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = ms5837_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
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
    else if (strcmp("h", type) == 0)
    {
        help:
        ms5837_interface_debug_print("Usage:\n");
        ms5837_interface_debug_print("  ms5837 (-i | --information)\n");
        ms5837_interface_debug_print("  ms5837 (-h | --help)\n");
        ms5837_interface_debug_print("  ms5837 (-p | --port)\n");
        ms5837_interface_debug_print("  ms5837 (-t read | --test=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]\n");
        ms5837_interface_debug_print("  ms5837 (-e read | --example=read) [--type=<02BA01 | 02BA21 | 30BA26>] [--times=<num>]\n");
        ms5837_interface_debug_print("\n");
        ms5837_interface_debug_print("Options:\n");
        ms5837_interface_debug_print("  -e <read>, --example=<read>\n");
        ms5837_interface_debug_print("                       Run the driver example.\n");
        ms5837_interface_debug_print("  -h, --help           Show the help.\n");
        ms5837_interface_debug_print("  -i, --information    Show the chip information.\n");
        ms5837_interface_debug_print("  -p, --port           Display the pin connections of the current board.\n");
        ms5837_interface_debug_print("  -t <read>, --test=<read>\n");
        ms5837_interface_debug_print("                       Run the driver test.\n");
        ms5837_interface_debug_print("      --times=<num>    Set the running times.([default: 3])\n");
        ms5837_interface_debug_print("      --type=<02BA01 | 02BA21 | 30BA26>\n");
        ms5837_interface_debug_print("                       Set the chip type.([default: 02BA01])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ms5837_interface_debug_print("ms5837: SCL connected to GPIO3.\n");
        ms5837_interface_debug_print("ms5837: SDA connected to GPIO2.\n");
        
        return 0;
    }
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
        ms5837_interface_debug_print("ms5837: unknown status code.\n");
    }

    return 0;
}
