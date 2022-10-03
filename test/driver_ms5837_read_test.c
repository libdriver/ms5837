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
 * @file      driver_ms5837_read_test.c
 * @brief     driver ms5837 read test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-09-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/09/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_ms5837_read_test.h"

static ms5837_handle_t gs_handle;        /**< ms5837 handle */

/**
 * @brief     read test
 * @param[in] type is the device type
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ms5837_read_test(ms5837_type_t type, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    ms5837_info_t info;
    ms5837_osr_t osr;
    
    /* link interface function */
    DRIVER_MS5837_LINK_INIT(&gs_handle, ms5837_handle_t);
    DRIVER_MS5837_LINK_IIC_INIT(&gs_handle, ms5837_interface_iic_init);
    DRIVER_MS5837_LINK_IIC_DEINIT(&gs_handle, ms5837_interface_iic_deinit);
    DRIVER_MS5837_LINK_IIC_READ(&gs_handle, ms5837_interface_iic_read);
    DRIVER_MS5837_LINK_IIC_WRITE(&gs_handle, ms5837_interface_iic_write);
    DRIVER_MS5837_LINK_DELAY_MS(&gs_handle, ms5837_interface_delay_ms);
    DRIVER_MS5837_LINK_DEBUG_PRINT(&gs_handle, ms5837_interface_debug_print);
    
    /* get chip information */
    res = ms5837_info(&info);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        ms5837_interface_debug_print("ms5837: chip is %s.\n", info.chip_name);
        ms5837_interface_debug_print("ms5837: manufacturer is %s.\n", info.manufacturer_name);
        ms5837_interface_debug_print("ms5837: interface is %s.\n", info.interface);
        ms5837_interface_debug_print("ms5837: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ms5837_interface_debug_print("ms5837: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ms5837_interface_debug_print("ms5837: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ms5837_interface_debug_print("ms5837: max current is %0.2fmA.\n", info.max_current_ma);
        ms5837_interface_debug_print("ms5837: max temperature is %0.1fC.\n", info.temperature_max);
        ms5837_interface_debug_print("ms5837: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* ms5837 init */
    res = ms5837_init(&gs_handle);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    ms5837_interface_debug_print("ms5837: start read test.\n");
    
    /* set the type */
    res = ms5837_set_type(&gs_handle, type);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set type failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* osr 256 */
    ms5837_interface_debug_print("ms5837: osr 256.\n");
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_256);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get temperature osr */
    res = ms5837_get_temperature_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_256)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_256);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get pressure osr */
    res = ms5837_get_pressure_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_256)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_mbar;
        
        /* read temperature pressure */
        res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read pressure */
        res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read temperature */
        res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
    }
    
    /* osr 512 */
    ms5837_interface_debug_print("ms5837: osr 512.\n");
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_512);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get temperature osr */
    res = ms5837_get_temperature_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_512)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_512);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get pressure osr */
    res = ms5837_get_pressure_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_512)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_mbar;
        
        /* read temperature pressure */
        res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read pressure */
        res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read temperature */
        res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
    }
    
    /* osr 1024 */
    ms5837_interface_debug_print("ms5837: osr 1024.\n");
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_1024);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get temperature osr */
    res = ms5837_get_temperature_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_1024)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_1024);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get pressure osr */
    res = ms5837_get_pressure_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_1024)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_mbar;
        
        /* read temperature pressure */
        res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read pressure */
        res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read temperature */
        res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
    }
    
    /* osr 2048 */
    ms5837_interface_debug_print("ms5837: osr 2048.\n");
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_2048);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get temperature osr */
    res = ms5837_get_temperature_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_2048)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_2048);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get pressure osr */
    res = ms5837_get_pressure_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_2048)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_mbar;
        
        /* read temperature pressure */
        res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read pressure */
        res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read temperature */
        res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
    }
    
    /* osr 4096 */
    ms5837_interface_debug_print("ms5837: osr 4096.\n");
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_4096);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get temperature osr */
    res = ms5837_get_temperature_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_4096)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_4096);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* get pressure osr */
    res = ms5837_get_pressure_osr(&gs_handle, &osr);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* check the osr */
    if (osr != MS5837_OSR_4096)
    {
        ms5837_interface_debug_print("ms5837: osr is error.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        uint32_t temperature_raw;
        float temperature_c;
        uint32_t pressure_raw;
        float pressure_mbar;
        
        /* read temperature pressure */
        res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read pressure */
        res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read pressure failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
        
        /* read temperature */
        res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: read temperature failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* output */
        ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
        
        /* delay 1000ms */
        ms5837_interface_delay_ms(1000);
    }
    if (type != MS5837_TYPE_30BA26)
    {
        /* osr 8192 */
        ms5837_interface_debug_print("ms5837: osr 8192.\n");
        
        /* set temperature osr */
        res = ms5837_set_temperature_osr(&gs_handle, MS5837_OSR_8192);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* get temperature osr */
        res = ms5837_get_temperature_osr(&gs_handle, &osr);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: get temperature osr failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* check the osr */
        if (osr != MS5837_OSR_8192)
        {
            ms5837_interface_debug_print("ms5837: osr is error.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* set pressure osr */
        res = ms5837_set_pressure_osr(&gs_handle, MS5837_OSR_8192);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* get pressure osr */
        res = ms5837_get_pressure_osr(&gs_handle, &osr);
        if (res != 0)
        {
            ms5837_interface_debug_print("ms5837: get pressure osr failed.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        /* check the osr */
        if (osr != MS5837_OSR_8192)
        {
            ms5837_interface_debug_print("ms5837: osr is error.\n");
            (void)ms5837_deinit(&gs_handle);
           
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            uint32_t temperature_raw;
            float temperature_c;
            uint32_t pressure_raw;
            float pressure_mbar;
            
            /* read temperature pressure */
            res = ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, &temperature_c, &pressure_raw, &pressure_mbar);
            if (res != 0)
            {
                ms5837_interface_debug_print("ms5837: read temperature pressure failed.\n");
                (void)ms5837_deinit(&gs_handle);
               
                return 1;
            }
            
            /* output */
            ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
            ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
            
            /* delay 1000ms */
            ms5837_interface_delay_ms(1000);
            
            /* read pressure */
            res = ms5837_read_pressure(&gs_handle, &pressure_raw, &pressure_mbar);
            if (res != 0)
            {
                ms5837_interface_debug_print("ms5837: read pressure failed.\n");
                (void)ms5837_deinit(&gs_handle);
               
                return 1;
            }
            
            /* output */
            ms5837_interface_debug_print("ms5837: pressure is %0.2fmbar.\n", pressure_mbar);
            
            /* delay 1000ms */
            ms5837_interface_delay_ms(1000);
            
            /* read temperature */
            res = ms5837_read_temperature(&gs_handle, &temperature_raw, &temperature_c);
            if (res != 0)
            {
                ms5837_interface_debug_print("ms5837: read temperature failed.\n");
                (void)ms5837_deinit(&gs_handle);
               
                return 1;
            }
            
            /* output */
            ms5837_interface_debug_print("ms5837: temperature is %0.2fC.\n", temperature_c);
            
            /* delay 1000ms */
            ms5837_interface_delay_ms(1000);
        }
    }
    
    /* finish read test */
    ms5837_interface_debug_print("ms5837: finish read test.\n");
    (void)ms5837_deinit(&gs_handle);
    
    return 0;
}
