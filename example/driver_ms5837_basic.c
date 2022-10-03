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
 * @file      driver_ms5837_basic.c
 * @brief     driver ms5837 basic source file
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

#include "driver_ms5837_basic.h"

static ms5837_handle_t gs_handle;        /**< ms5837 handle */

/**
 * @brief     basic example init
 * @param[in] type is the device type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ms5837_basic_init(ms5837_type_t type)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_MS5837_LINK_INIT(&gs_handle, ms5837_handle_t);
    DRIVER_MS5837_LINK_IIC_INIT(&gs_handle, ms5837_interface_iic_init);
    DRIVER_MS5837_LINK_IIC_DEINIT(&gs_handle, ms5837_interface_iic_deinit);
    DRIVER_MS5837_LINK_IIC_READ(&gs_handle, ms5837_interface_iic_read);
    DRIVER_MS5837_LINK_IIC_WRITE(&gs_handle, ms5837_interface_iic_write);
    DRIVER_MS5837_LINK_DELAY_MS(&gs_handle, ms5837_interface_delay_ms);
    DRIVER_MS5837_LINK_DEBUG_PRINT(&gs_handle, ms5837_interface_debug_print);
    
    /* ms5837 init */
    res = ms5837_init(&gs_handle);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: init failed.\n");
       
        return 1;
    }
    
    /* set the type */
    res = ms5837_set_type(&gs_handle, type);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set type failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set temperature osr */
    res = ms5837_set_temperature_osr(&gs_handle, MS5837_BASIC_DEFAULT_TEMPERATURE_OSR);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set temperature osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pressure osr */
    res = ms5837_set_pressure_osr(&gs_handle, MS5837_BASIC_DEFAULT_PRESSURE_OSR);
    if (res != 0)
    {
        ms5837_interface_debug_print("ms5837: set pressure osr failed.\n");
        (void)ms5837_deinit(&gs_handle);
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature_c points to a converted temperature buffer
 * @param[out] *pressure_mbar points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ms5837_basic_read(float *temperature_c, float *pressure_mbar)
{
    uint32_t temperature_raw;
    uint32_t pressure_raw;
    
    /* read temperature and pressure */
    if (ms5837_read_temperature_pressure(&gs_handle, &temperature_raw, temperature_c, &pressure_raw, pressure_mbar) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ms5837_basic_deinit(void)
{
    /* close ms5837 */
    if (ms5837_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
