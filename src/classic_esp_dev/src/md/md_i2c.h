#ifndef MD_I2C_H
#define MD_I2C_H

#include "../common.h"

#define I2C_READ_OK         0x00
#define I2C_READ_NG         0xFF
#define I2C_WRITE_OK        0x00
#define I2C_WRITE_NG        0xFF

#define I2C_BURST_READ_OK   0x00
#define I2C_BURST_READ_NG   0xFF
#define I2C_BURST_WRITE_OK  0x00
#define I2C_BURST_WRITE_NG  0xFF

#define I2C_RESULT_NONE     0xFF

int8_t md_i2c_burst_write(uint8_t reg_addr,
                        uint8_t *p_write_buf,
                        uint16_t len,
                        uint8_t slave_addr);

int8_t md_i2c_burst_read(uint8_t reg_addr,
                        uint8_t *p_read_buf,
                        uint16_t len,
                        uint8_t slave_addr);

#endif /* MD_I2C_H */