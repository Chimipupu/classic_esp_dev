#include "md_i2c.h"

int8_t md_i2c_burst_read(uint8_t reg_addr,
                                uint8_t *p_read_buf,
                                uint16_t len,
                                uint8_t slave_addr)
{
    int8_t result;
    uint16_t cnt;

    result      = I2C_BURST_READ_OK;

#ifdef __DEBUG_I2C_DRV__
    DEBUG_PRITNF("******************************************\n");
    DEBUG_PRITNF("[DEBUG MSG] : I2C Read Func\n");
    DEBUG_PRITNF("******************************************\n");

    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Slave = 0x%X\n", slave_addr);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Write Length = %dByte\n", len);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Write Reg(%XH)\n", reg_addr);
#endif

    // Arduino IDE Env I2C
    Wire.beginTransmission(slave_addr);
    Wire.write(reg_addr);
    Wire.endTransmission();

#ifdef __DEBUG_I2C_DRV__
    DEBUG_PRITNF("[DEBUG MSG] : I2C Read ... Slave = 0x%X\n", slave_addr);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Read ... Read Length = %dByte\n", len);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Read ... Read Reg(%XH)\n", reg_addr);
#endif

    Wire.requestFrom(slave_addr, len);

    // データが受信された
    while(Wire.available())
    {
        for(cnt = 0; cnt < len; cnt++)
        {
            *p_read_buf = Wire.read();
    #ifdef __DEBUG_I2C_DRV__
                DEBUG_PRITNF("[DEBUG MSG] : I2C Read ... Read Data = 0x%X\n", *p_read_buf);
    #endif
            p_read_buf++;
        }
        break;
    }

#ifdef __DEBUG_I2C_DRV__
    DEBUG_PRITNF("******************************************\n\n");
#endif
    return result;
}

int8_t md_i2c_burst_write(uint8_t reg_addr,
                                uint8_t *p_write_buf,
                                uint16_t len,
                                uint8_t slave_addr)
{
    int8_t result;
    uint16_t cnt;

    result = I2C_BURST_WRITE_OK;

#ifdef __DEBUG_I2C_DRV__
    DEBUG_PRITNF("******************************************\n");
    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Func\n");
    DEBUG_PRITNF("******************************************\n");

    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Slave = 0x%X\n", slave_addr);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Write Length = %dByte\n", len);
    DEBUG_PRITNF("[DEBUG MSG] : I2C Write Reg Select ... Write Reg(%XH)\n", reg_addr);
#endif

    // Arduino IDE Env I2C Write
    Wire.beginTransmission(slave_addr);
    Wire.write(reg_addr);

    for(cnt = 0; cnt <= len; cnt++)
    {
#ifdef __DEBUG_I2C_DRV__
        DEBUG_PRITNF("[DEBUG MSG] : I2C Write ... Write Data = 0x%X\n", *p_write_buf);
#endif
        Wire.write(*p_write_buf);
        p_write_buf++;
    }
    Wire.endTransmission();

#ifdef __DEBUG_I2C_DRV__
    DEBUG_PRITNF("******************************************\n\n");
#endif

    return result;
}