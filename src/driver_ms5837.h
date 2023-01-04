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
 * @file      driver_ms5837.h
 * @brief     driver ms5837 header file
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

#ifndef DRIVER_MS5837_H
#define DRIVER_MS5837_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ms5837_driver ms5837 driver function
 * @brief    ms5837 driver modules
 * @{
 */

/**
 * @addtogroup ms5837_base_driver
 * @{
 */

/**
 * @brief ms5837 type enumeration definition
 */
typedef enum
{
    MS5837_TYPE_02BA01 = 0x00,        /**< ms5837 02ba01 */
    MS5837_TYPE_02BA21 = 0x01,        /**< ms5837 02ba21 */
    MS5837_TYPE_30BA26 = 0x02,        /**< ms5837 30ba26 */
} ms5837_type_t;

/**
 * @brief ms5837 osr enumeration definition
 */
typedef enum
{
    MS5837_OSR_256  = 0x00,        /**< max 0.6ms */
    MS5837_OSR_512  = 0x01,        /**< max 1.17ms */
    MS5837_OSR_1024 = 0x02,        /**< max 2.28ms */
    MS5837_OSR_2048 = 0x03,        /**< max 4.54ms */
    MS5837_OSR_4096 = 0x04,        /**< max 9.04ms */
    MS5837_OSR_8192 = 0x05,        /**< max 18.08ms */
} ms5837_osr_t;

/**
 * @brief ms5837 handle structure definition
 */
typedef struct ms5837_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t prom[16];                                                                   /**< prom */
    uint16_t c[6];                                                                      /**< c1 - c6 */
    uint8_t temp_osr;                                                                   /**< temperature osr */
    uint8_t press_osr;                                                                  /**< pressure osr */
    uint8_t type;                                                                       /**< type */
    uint8_t inited;                                                                     /**< inited flag */
} ms5837_handle_t;

/**
 * @brief ms5837 information structure definition
 */
typedef struct ms5837_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ms5837_info_t;

/**
 * @}
 */

/**
 * @defgroup ms5837_link_driver ms5837 link driver function
 * @brief    ms5837 link driver modules
 * @ingroup  ms5837_driver
 * @{
 */

/**
 * @brief     initialize ms5837_handle_t structure
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] STRUCTURE is ms5837_handle_t
 * @note      none
 */
#define DRIVER_MS5837_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_IIC_INIT(HANDLE, FUC)             (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_IIC_DEINIT(HANDLE, FUC)           (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_IIC_READ(HANDLE, FUC)             (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_IIC_WRITE(HANDLE, FUC)            (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ms5837 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_MS5837_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ms5837_base_driver ms5837 base driver function
 * @brief    ms5837 base driver modules
 * @ingroup  ms5837_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ms5837 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ms5837_info(ms5837_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ms5837 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 *            - 5 read prom failed
 *            - 6 crc is error
 *            - 7 type is invalid
 * @note      none
 */
uint8_t ms5837_init(ms5837_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ms5837 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 reset failed
 * @note      none
 */
uint8_t ms5837_deinit(ms5837_handle_t *handle);

/**
 * @brief      read the temperature and pressure
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_c points to a converted temperature buffer
 * @param[out] *pressure_raw points to a raw pressure buffer
 * @param[out] *pressure_mbar points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature pressure failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_read_temperature_pressure(ms5837_handle_t *handle, uint32_t *temperature_raw, float *temperature_c, 
                                         uint32_t *pressure_raw, float *pressure_mbar);

/**
 * @brief      read the pressure
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *pressure_raw points to a raw pressure buffer
 * @param[out] *pressure_mbar points to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 read pressure failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_read_pressure(ms5837_handle_t *handle, uint32_t *pressure_raw, float *pressure_mbar);

/**
 * @brief      read the temperature
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_c points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_read_temperature(ms5837_handle_t *handle, uint32_t *temperature_raw, float *temperature_c);

/**
 * @brief     set the device type
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] type is the device type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ms5837_set_type(ms5837_handle_t *handle, ms5837_type_t type);

/**
 * @brief      get the device type
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *type points to a type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_get_type(ms5837_handle_t *handle, ms5837_type_t *type);

/**
 * @brief     set the adc temperature osr
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] osr is the adc osr
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 30ba26 can't support osr 8192
 * @note      none
 */
uint8_t ms5837_set_temperature_osr(ms5837_handle_t *handle, ms5837_osr_t osr);

/**
 * @brief      get the adc temperature osr
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *osr points to an osr buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_get_temperature_osr(ms5837_handle_t *handle, ms5837_osr_t *osr);

/**
 * @brief     set the adc pressure osr
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] osr is the adc osr
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 30ba26 can't support osr 8192
 * @note      none
 */
uint8_t ms5837_set_pressure_osr(ms5837_handle_t *handle, ms5837_osr_t osr);

/**
 * @brief      get the adc pressure osr
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[out] *osr points to an osr buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_get_pressure_osr(ms5837_handle_t *handle, ms5837_osr_t *osr);

/**
 * @brief     reset the device
 * @param[in] *handle points to an ms5837 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ms5837_reset(ms5837_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup ms5837_extend_driver ms5837 extend driver function
 * @brief    ms5837 extend driver modules
 * @ingroup  ms5837_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ms5837_set_reg(ms5837_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ms5837_get_reg(ms5837_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
