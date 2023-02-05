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
 * @file      driver_ms5837.c
 * @brief     driver ms5837 source file
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

#include "driver_ms5837.h" 

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "TE MS5837"        /**< chip name */
#define MANUFACTURER_NAME         "TE"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.5f               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f               /**< chip max supply voltage */
#define MAX_CURRENT               1.25f              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f             /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f              /**< chip max operating temperature */
#define DRIVER_VERSION            1000               /**< driver version */

/**
 * @brief chip address definition
 */
#define MS5837_ADDRESS            0xEC        /**< iic device address */

/**
 * @brief chip command definition
 */
#define MS5837_CMD_RESET        0x1E        /**< command reset */
#define MS5837_CMD_D1           0x40        /**< command convert d1 */
#define MS5837_CMD_D2           0x50        /**< command convert d2 */
#define MS5837_CMD_ADC_READ     0x00        /**< command adc read */
#define MS5837_CMD_PROM_READ    0xA0        /**< command prom read */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an ms5837 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ms5837_iic_read(ms5837_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read(MS5837_ADDRESS, reg, data, len) != 0)        /* read the register */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ms5837_iic_write(ms5837_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(MS5837_ADDRESS, reg, data, len) != 0)       /* write the register */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief     get the crc4
 * @param[in] *n_prom points to a prom buffer
 * @return    crc code
 * @note      none
 */
static uint8_t a_ms5837_crc4(uint16_t n_prom[8])
{
    uint16_t cnt;
    uint16_t n_rem = 0;
    uint16_t n_bit;
    
    n_prom[0] = ((n_prom[0]) & 0x0FFF);                              /* crc byte is replaced by 0 */
    n_prom[7] = 0;                                                   /* subsidiary value and set to 0 */
    for (cnt = 0; cnt < 16; cnt++)                                   /* operation is performed on bytes */
    {
        if ((cnt% 2) == 1)                                           /* 16 bits progress */
        {
            n_rem ^= (uint16_t)((n_prom[cnt >> 1]) & 0x00FF);        /* low part */
        }
        else
        {
            n_rem ^= (uint16_t)(n_prom[cnt >> 1] >> 8);              /* high part */
        }
        for (n_bit = 8; n_bit > 0; n_bit--)                          /* 8 times */
        {
            if ((n_rem & (0x8000U)) != 0)                            /* check msb */
            {
                n_rem = (n_rem << 1) ^ 0x3000;                       /* xor */
            }
            else
            {
                n_rem = (n_rem << 1);                                /* do nothing */
            }
        }
    }
    n_rem= ((n_rem >> 12) & 0x000F);                                 /* final 4-bit remainder is crc code */
    
    return (n_rem ^ 0x00);                                           /* return the crc */
}

/**
 * @brief     calculate temperature and pressure
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] d2_temp is the temperature raw data
 * @param[in] *temperature_c points to a temperature buffer
 * @param[in] d1_press is the pressure raw data
 * @param[in] *pressure_mbar points to a pressure buffer
 * @note      none
 */
static void a_ms5837_calculate_temperature_pressure(ms5837_handle_t *handle, uint32_t d2_temp, float *temperature_c, 
                                                    uint32_t d1_press, float *pressure_mbar)
{
    int32_t dt = 0;
    int64_t sens = 0;
    int64_t off = 0;
    int32_t sensi = 0;
    int32_t offi = 0;
    int32_t ti = 0;
    int64_t off2 = 0;
    int64_t sens2 = 0;
    int32_t p;
    int32_t temp;

    dt = d2_temp - (uint32_t)(handle->c[4]) * 256;                                            /* get the dt */
    if ((handle->type == MS5837_TYPE_02BA01) || (handle->type == MS5837_TYPE_02BA21))         /* 02ba01 and 02ba21 */
    {
        sens = (int64_t)(handle->c[0]) * 65536 + ((int64_t)(handle->c[2]) * dt) / 128;        /* get the sens */
        off = (int64_t)(handle->c[1]) * 131072 + ((int64_t)(handle->c[3]) * dt) / 64;         /* get the off */
        p = (int32_t)((d1_press * sens / 2097152 - off) / 32768);                             /* get the p  */
    }
    else                                                                                      /* 30ba26 */
    {
        sens = (int64_t)(handle->c[0]) * 32768 + ((int64_t)(handle->c[2]) * dt) / 256;        /* get the sens */
        off = (int64_t)(handle->c[1]) * 65536 + ((int64_t)(handle->c[3]) *  dt) / 128;        /* get the off */
        p = (int32_t)((d1_press * sens / 2097152 - off) / 8192);                              /* get the p */
    }
    temp = 2000 + (int64_t)(dt) * handle->c[5] / 8388608;                                     /* get the temp */
    if ((handle->type == MS5837_TYPE_02BA01) || (handle->type == MS5837_TYPE_02BA21))         /* 02ba01 and 02ba21 */
    {
        if ((temp / 100) < 20)                                                                /* if < 20 */
        {
            ti = (int32_t)((11 * (int64_t)(dt) * (int64_t)(dt)) / 34359738368U);              /* get the ti */
            offi = (31 * (temp - 2000) * (temp - 2000)) / 8;                                  /* get the offi */
            sensi = (63 * (temp - 2000) * (temp - 2000)) / 32;                                /* get the sensi */
        }
    }
    else
    {
        if ((temp / 100) < 20)                                                                /* if < 20 */
        {
            ti = (int32_t)((3 * (int64_t)(dt) * (int64_t)(dt)) / 8589934592U);                /* get the ti */
            offi = (3 * (temp - 2000) * (temp - 2000)) / 2;                                   /* get the offi */
            sensi = (5 * (temp - 2000) * (temp - 2000)) / 8;                                  /* get the sensi */
            if ((temp / 100) < -15)                                                           /* if < -15 */
            {
                offi = offi + 7 * (temp + 1500) * (temp + 1500);                              /* get the offi */
                sensi = sensi + 4 * (temp + 1500) * (temp + 1500);                            /* get the sensi */
            }
        }
        else
        {
            ti = (int32_t)(2 * (dt * dt) / 137438953472U);                                    /* get the ti */
            offi = (1 * (temp - 2000) * (temp - 2000)) / 16;                                  /* get the offi */
            sensi = 0;                                                                        /* get the sensi */
        }
    }
    off2 = off - offi;                                                                        /* get the off2 */
    sens2 = sens - sensi;                                                                     /* get the sens2 */
    temp = (temp - ti);                                                                       /* get the temp */
    *temperature_c = (float)(temp) / 100.0f;                                                  /* set the temperature */
    if ((handle->type == MS5837_TYPE_02BA01) || (handle->type == MS5837_TYPE_02BA21))         /* 02ba01 and 02ba21 */
    {
        p = (int32_t)((((d1_press * sens2) / 2097152 - off2) / 32768));                       /* get the p */
        *pressure_mbar = (float)(p) / 100.0f;                                                 /* set the pressure */
    }
    else
    {
        p = (int32_t)((((d1_press * sens2) / 2097152 - off2) / 8192));                        /* get the p */
        *pressure_mbar = (float)(p) / 10.0f;                                                  /* set the pressure */
    }
}

/**
 * @brief     calculate temperature
 * @param[in] *handle points to an ms5837 handle structure
 * @param[in] d2_temp is the temperature raw data
 * @param[in] *temperature_c points to a temperature buffer
 * @note      none
 */
static void a_ms5837_calculate_temperature(ms5837_handle_t *handle, uint32_t d2_temp, float *temperature_c)
{
    int32_t dt = 0;
    int32_t ti = 0;
    int32_t temp;

    dt = d2_temp - (uint32_t)(handle->c[4]) * 256;                                           /* get the dt */
    temp = 2000 + (int64_t)(dt) * handle->c[5] / 8388608;                                    /* get the temp */
    if ((handle->type == MS5837_TYPE_02BA01) || (handle->type == MS5837_TYPE_02BA21))        /* 02ba01 and 02ba21 */
    {
        if ((temp / 100) < 20)                                                               /* if < 20 */
        {
            ti = (int32_t)((11 * (int64_t)(dt) * (int64_t)(dt)) / 34359738368U);             /* get the ti */
        }
    }
    else
    {
        if ((temp / 100) < 20)                                                               /* if < 20 */
        {
            ti = (int32_t)((3 * (int64_t)(dt) * (int64_t)(dt)) / 8589934592U);               /* get the ti */
        }
        else
        {
            ti = (int32_t)((2 * (dt * dt)) / 137438953472U);                                 /* get the ti */
        }
    }
    temp = (temp - ti);                                                                      /* get the temp */
    *temperature_c = (float)(temp) / 100.0f;                                                 /* set the temperature */
}

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
uint8_t ms5837_init(ms5837_handle_t *handle)
{
    uint8_t i;
    uint8_t crc;
    uint8_t crc_check;
    uint8_t type;
    uint16_t c[8];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("ms5837: iic_init is null.\n");          /* iic_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_init */
    {
        handle->debug_print("ms5837: iic_deinit is null.\n");        /* iic_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_read == NULL)                                    /* check iic_read */
    {
        handle->debug_print("ms5837: iic_read is null.\n");          /* iic_read is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_write == NULL)                                   /* check iic_write */
    {
        handle->debug_print("ms5837: iic_write is null.\n");         /* iic_write is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("ms5837: delay_ms is null.\n");          /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_init() != 0)                                     /* iic init */
    {
        handle->debug_print("ms5837: iic init failed.\n");           /* iic init failed */
        
        return 1;                                                    /* return error */
    }
    if (a_ms5837_iic_write(handle, MS5837_CMD_RESET, 
        NULL, 0) != 0)                                               /* reset the device */
    {
        handle->debug_print("ms5837: reset failed.\n");              /* reset failed */
        
        return 4;                                                    /* return error */
    }
    handle->delay_ms(10);                                            /* delay 10 ms */
    memset(c, 0, sizeof(uint16_t) * 8);                              /* clear the c */
    for (i = 0; i < 7; i++)                                          /* 7 times */
    {
        if (a_ms5837_iic_read(handle, MS5837_CMD_PROM_READ + i * 2, 
            handle->prom + i * 2, 2) != 0)                           /* read the prom */
        {
            handle->debug_print("ms5837: read prom failed.\n");      /* read prom failed */
            
            return 5;                                                /* return error */
        }
        c[i] = ((uint16_t)(handle->prom[i * 2]) << 8) | 
               (uint16_t)(handle->prom[i * 2 + 1]);                  /* set c[i] */
    }
    
    crc_check = (c[0] >> 12) & 0xF;                                  /* get the crc check */
    type = (c[0] >> 5) & 0x7F;                                       /* set the type */
    crc = a_ms5837_crc4(c);                                          /* calculate the crc */
    if (crc != crc_check)                                            /* check the crc */
    {
        handle->debug_print("ms5837: crc is error.\n");              /* crc is error */
        
        return 6;                                                    /* return error */
    }
    handle->c[0] = c[1];                                             /* set c0 */
    handle->c[1] = c[2];                                             /* set c1 */
    handle->c[2] = c[3];                                             /* set c2 */
    handle->c[3] = c[4];                                             /* set c3 */
    handle->c[4] = c[5];                                             /* set c4 */
    handle->c[5] = c[6];                                             /* set c5 */
    if (type == 0x00)                                                /* check the type */
    {
        handle->type = MS5837_TYPE_02BA01;                           /* ms5837 02ba01 */
    }
    else if (type == 0x15)                                           /* check the type */
    {
        handle->type = MS5837_TYPE_02BA21;                           /* ms5837 02ba21 */
    }
    else if (type == 0x1A)                                           /* check the type */
    {
        handle->type = MS5837_TYPE_30BA26;                           /* ms5837 30ba26 */
    }
    else
    {
        handle->debug_print("ms5837: type is invalid.\n");           /* type is invalid */
        
        return 7;                                                    /* return error */
    }
    handle->temp_osr = MS5837_OSR_256;                               /* set 256 temperature osr */
    handle->press_osr = MS5837_OSR_256;                              /* set 256 pressure osr */
    handle->inited = 1;                                              /* flag finish initialization */

    return 0;                                                        /* success return 0 */
}

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
uint8_t ms5837_deinit(ms5837_handle_t *handle)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
 
    if (a_ms5837_iic_write(handle, MS5837_CMD_RESET, 
        NULL, 0) != 0)                                              /* reset the device */
    {
        handle->debug_print("ms5837: reset failed.\n");             /* reset failed */
        
        return 4;                                                   /* return error */
    }
    handle->delay_ms(10);                                           /* delay 10 ms */
    if (handle->iic_deinit() != 0)                                  /* iic deinit */
    {
        handle->debug_print("ms5837: iic deinit failed.\n");        /* iic deinit failed */
        
        return 1;                                                   /* return error */
    }   
    handle->inited = 0;                                             /* flag close */
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t ms5837_get_type(ms5837_handle_t *handle, ms5837_type_t *type)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    *type = (ms5837_type_t)(handle->type);        /* get the type */
    
    return 0;                                     /* success return 0 */
}

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
uint8_t ms5837_set_type(ms5837_handle_t *handle, ms5837_type_t type)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    handle->type = (uint8_t)(type);        /* set the type */
    
    return 0;                              /* success return 0 */
}

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
uint8_t ms5837_get_temperature_osr(ms5837_handle_t *handle, ms5837_osr_t *osr)
{
    if (handle == NULL)                             /* check handle */
    {
        return 2;                                   /* return error */
    }
    if (handle->inited != 1)                        /* check handle initialization */
    {
        return 3;                                   /* return error */
    }
    
    *osr = (ms5837_osr_t)(handle->temp_osr);        /* get the osr */
    
    return 0;                                       /* success return 0 */
}

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
uint8_t ms5837_set_temperature_osr(ms5837_handle_t *handle, ms5837_osr_t osr)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    if ((handle->type == MS5837_TYPE_30BA26)
        && (osr == MS5837_OSR_8192)                                             /* check the osr */
       )
    {
        handle->debug_print("ms5837: 30ba26 can't support osr 8192.\n");        /* 30ba26 can't support osr 8192 */
        
        return 4;                                                               /* return error */
    }
    
    handle->temp_osr = (uint8_t)(osr);                                          /* set the osr */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t ms5837_get_pressure_osr(ms5837_handle_t *handle, ms5837_osr_t *osr)
{
    if (handle == NULL)                             /* check handle */
    {
        return 2;                                   /* return error */
    }
    if (handle->inited != 1)                        /* check handle initialization */
    {
        return 3;                                   /* return error */
    }
    
    *osr = (ms5837_osr_t)(handle->press_osr);       /* get the osr */
    
    return 0;                                       /* success return 0 */
}

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
uint8_t ms5837_set_pressure_osr(ms5837_handle_t *handle, ms5837_osr_t osr)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    if ((handle->type == MS5837_TYPE_30BA26)
        && (osr == MS5837_OSR_8192)                                             /* check the osr */
       )
    {
        handle->debug_print("ms5837: 30ba26 can't support osr 8192.\n");        /* 30ba26 can't support osr 8192 */
        
        return 4;                                                               /* return error */
    }
    
    handle->press_osr = (uint8_t)(osr);                                         /* set the osr */
    
    return 0;                                                                   /* success return 0 */
}

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
                                         uint32_t *pressure_raw, float *pressure_mbar)
{
    uint8_t buf[3];
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_ms5837_iic_write(handle, MS5837_CMD_D2 + handle->temp_osr, NULL, 0) != 0)            /* sent d2 */
    {
        handle->debug_print("ms5837: sent d2 failed.\n");                                      /* sent d2 failed */
        
        return 1;                                                                              /* return error */
    }
    if (handle->temp_osr == MS5837_OSR_256)                                                    /* osr 256 */
    {
        handle->delay_ms(1);                                                                   /* delay 1ms */
    }
    else if (handle->temp_osr == MS5837_OSR_512)                                               /* osr 512 */
    {
        handle->delay_ms(2);                                                                   /* delay 2ms */
    }
    else if (handle->temp_osr == MS5837_OSR_1024)                                              /* osr 1024 */
    {
        handle->delay_ms(3);                                                                   /* delay 3ms */
    }
    else if (handle->temp_osr == MS5837_OSR_2048)                                              /* osr 2048 */
    {
        handle->delay_ms(5);                                                                   /* delay 5ms */
    }
    else if (handle->temp_osr == MS5837_OSR_4096)                                              /* osr 4096 */
    {
        handle->delay_ms(9);                                                                   /* delay 9ms */
    }
    else                                                                                       /* osr 8192 */
    {
        handle->delay_ms(18);                                                                  /* delay 18ms */
    }
    if (a_ms5837_iic_read(handle, MS5837_CMD_ADC_READ, buf, 3) != 0)                           /* read adc */
    {
        handle->debug_print("ms5837: read adc failed.\n");                                     /* read adc failed */
        
        return 1;                                                                              /* return error */
    }
    *temperature_raw = (((uint32_t)buf[0]) << 16) | (((uint32_t)buf[1]) << 8) | buf[2];        /* set the temperature raw */
    
    if (a_ms5837_iic_write(handle, MS5837_CMD_D1 + handle->press_osr, NULL, 0) != 0)           /* sent d1 */
    {
        handle->debug_print("ms5837: sent d1 failed.\n");                                      /* sent d1 failed */
        
        return 1;                                                                              /* return error */
    }
    if (handle->press_osr == MS5837_OSR_256)                                                   /* osr 256 */
    {
        handle->delay_ms(1);                                                                   /* delay 1ms */
    }
    else if (handle->press_osr == MS5837_OSR_512)                                              /* osr 512 */
    {
        handle->delay_ms(2);                                                                   /* delay 2ms */
    }
    else if (handle->press_osr == MS5837_OSR_1024)                                             /* osr 1024 */
    {
        handle->delay_ms(3);                                                                   /* delay 3ms */
    }
    else if (handle->press_osr == MS5837_OSR_2048)                                             /* osr 2048 */
    {
        handle->delay_ms(5);                                                                   /* delay 5ms */
    }
    else if (handle->press_osr == MS5837_OSR_4096)                                             /* osr 4096 */
    {
        handle->delay_ms(9);                                                                   /* delay 9ms */
    }
    else                                                                                       /* osr 8192 */
    {
        handle->delay_ms(18);                                                                  /* delay 18ms */
    }
    if (a_ms5837_iic_read(handle, MS5837_CMD_ADC_READ, buf, 3) != 0)                           /* read adc */
    {
        handle->debug_print("ms5837: read adc failed.\n");                                     /* read adc failed */
        
        return 1;                                                                              /* return error */
    }
    *pressure_raw = (((uint32_t)buf[0]) << 16) | (((uint32_t)buf[1]) << 8) | buf[2];           /* set the temperature raw */
    a_ms5837_calculate_temperature_pressure(handle, *temperature_raw, temperature_c, 
                                            *pressure_raw, pressure_mbar);                     /* calculate temperature and pressure */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t ms5837_read_pressure(ms5837_handle_t *handle, uint32_t *pressure_raw, float *pressure_mbar)
{
    uint8_t buf[3];
    uint32_t temperature_raw;
    float temperature_c; 
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_ms5837_iic_write(handle, MS5837_CMD_D2 + handle->temp_osr, NULL, 0) != 0)            /* sent d2 */
    {
        handle->debug_print("ms5837: sent d2 failed.\n");                                      /* sent d2 failed */
        
        return 1;                                                                              /* return error */
    }
    if (handle->temp_osr == MS5837_OSR_256)                                                    /* osr 256 */
    {
        handle->delay_ms(1);                                                                   /* delay 1ms */
    }
    else if (handle->temp_osr == MS5837_OSR_512)                                               /* osr 512 */
    {
        handle->delay_ms(2);                                                                   /* delay 2ms */
    }
    else if (handle->temp_osr == MS5837_OSR_1024)                                              /* osr 1024 */
    {
        handle->delay_ms(3);                                                                   /* delay 3ms */
    }
    else if (handle->temp_osr == MS5837_OSR_2048)                                              /* osr 2048 */
    {
        handle->delay_ms(5);                                                                   /* delay 5ms */
    }
    else if (handle->temp_osr == MS5837_OSR_4096)                                              /* osr 4096 */
    {
        handle->delay_ms(9);                                                                   /* delay 9ms */
    }
    else                                                                                       /* osr 8192 */
    {
        handle->delay_ms(18);                                                                  /* delay 18ms */
    }
    if (a_ms5837_iic_read(handle, MS5837_CMD_ADC_READ, buf, 3) != 0)                           /* read adc */
    {
        handle->debug_print("ms5837: read adc failed.\n");                                     /* read adc failed */
        
        return 1;                                                                              /* return error */
    }
    temperature_raw = (((uint32_t)buf[0]) << 16) | (((uint32_t)buf[1]) << 8) | buf[2];         /* set the temperature raw */
    
    if (a_ms5837_iic_write(handle, MS5837_CMD_D1 + handle->press_osr, NULL, 0) != 0)           /* sent d1 */
    {
        handle->debug_print("ms5837: sent d1 failed.\n");                                      /* sent d1 failed */
        
        return 1;                                                                              /* return error */
    }
    if (handle->press_osr == MS5837_OSR_256)                                                   /* osr 256 */
    {
        handle->delay_ms(1);                                                                   /* delay 1ms */
    }
    else if (handle->press_osr == MS5837_OSR_512)                                              /* osr 512 */
    {
        handle->delay_ms(2);                                                                   /* delay 2ms */
    }
    else if (handle->press_osr == MS5837_OSR_1024)                                             /* osr 1024 */
    {
        handle->delay_ms(3);                                                                   /* delay 3ms */
    }
    else if (handle->press_osr == MS5837_OSR_2048)                                             /* osr 2048 */
    {
        handle->delay_ms(5);                                                                   /* delay 5ms */
    }
    else if (handle->press_osr == MS5837_OSR_4096)                                             /* osr 4096 */
    {
        handle->delay_ms(9);                                                                   /* delay 9ms */
    }
    else                                                                                       /* osr 8192 */
    {
        handle->delay_ms(18);                                                                  /* delay 18ms */
    }
    if (a_ms5837_iic_read(handle, MS5837_CMD_ADC_READ, buf, 3) != 0)                           /* read adc */
    {
        handle->debug_print("ms5837: read adc failed.\n");                                     /* read adc failed */
        
        return 1;                                                                              /* return error */
    }
    *pressure_raw = (((uint32_t)buf[0]) << 16) | (((uint32_t)buf[1]) << 8) | buf[2];           /* set the temperature raw */
    a_ms5837_calculate_temperature_pressure(handle, temperature_raw, &temperature_c, 
                                            *pressure_raw, pressure_mbar);                     /* calculate temperature and pressure */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t ms5837_read_temperature(ms5837_handle_t *handle, uint32_t *temperature_raw, float *temperature_c)
{
    uint8_t buf[3];
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    if (a_ms5837_iic_write(handle, MS5837_CMD_D2 + handle->temp_osr, NULL, 0) != 0)            /* sent d2 */
    {
        handle->debug_print("ms5837: sent d2 failed.\n");                                      /* sent d2 failed */
        
        return 1;                                                                              /* return error */
    }
    if (handle->temp_osr == MS5837_OSR_256)                                                    /* osr 256 */
    {
        handle->delay_ms(1);                                                                   /* delay 1ms */
    }
    else if (handle->temp_osr == MS5837_OSR_512)                                               /* osr 512 */
    {
        handle->delay_ms(2);                                                                   /* delay 2ms */
    }
    else if (handle->temp_osr == MS5837_OSR_1024)                                              /* osr 1024 */
    {
        handle->delay_ms(3);                                                                   /* delay 3ms */
    }
    else if (handle->temp_osr == MS5837_OSR_2048)                                              /* osr 2048 */
    {
        handle->delay_ms(5);                                                                   /* delay 5ms */
    }
    else if (handle->temp_osr == MS5837_OSR_4096)                                              /* osr 4096 */
    {
        handle->delay_ms(9);                                                                   /* delay 9ms */
    }
    else                                                                                       /* osr 8192 */
    {
        handle->delay_ms(18);                                                                  /* delay 18ms */
    }
    if (a_ms5837_iic_read(handle, MS5837_CMD_ADC_READ, buf, 3) != 0)                           /* read adc */
    {
        handle->debug_print("ms5837: read adc failed.\n");                                     /* read adc failed */
        
        return 1;                                                                              /* return error */
    }
    *temperature_raw = (((uint32_t)buf[0]) << 16) | (((uint32_t)buf[1]) << 8) | buf[2];        /* set the temperature raw */
    a_ms5837_calculate_temperature(handle, *temperature_raw, temperature_c);                   /* calculate temperature and pressure */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t ms5837_reset(ms5837_handle_t *handle)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    } 

    if (a_ms5837_iic_write(handle, MS5837_CMD_RESET, NULL, 0) != 0)        /* reset the device */
    {
        handle->debug_print("ms5837: reset failed.\n");                    /* reset failed */
        
        return 1;                                                          /* return error */
    }
    handle->delay_ms(10);                                                  /* delay 10 ms */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t ms5837_set_reg(ms5837_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_ms5837_iic_write(handle, reg, buf, len);                    /* write data */
    if (res != 0)                                                       /* check result */
    {
        handle->debug_print("ms5837: write register failed.\n");        /* write register failed */
        
        return 1;                                                       /* return error */
    }

    return 0;                                                           /* success return 0 */
}

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
uint8_t ms5837_get_reg(ms5837_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ms5837_iic_read(handle, reg, buf, len);                    /* read data */
    if (res != 0)                                                      /* check result */
    {
        handle->debug_print("ms5837: read register failed.\n");        /* read register failed */
        
        return 1;                                                      /* return error */
    }

    return 0;                                                          /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ms5837 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ms5837_info(ms5837_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ms5837_info_t));                         /* initialize ms5837 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
