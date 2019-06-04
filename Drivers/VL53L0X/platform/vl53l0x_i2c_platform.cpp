#include "vl53l0x_i2c_platform.h"
#include "stm32l0xx_ll_i2c.h"
#include "string.h"

// From CubeMX example
void Handle_I2C_Master_Write(uint8_t address, uint8_t ubNbDataToTransmit, uint8_t *pTransmitBuffer)
{
  /* (1) Initiate a Start condition to the Slave device ***********************/

  /* Master Generate Start condition for a write request :              */
  /*    - to the Slave with a 7-Bit SLAVE_OWN_ADDRESS                   */
  /*    - with a auto stop condition generation when transmit all bytes */
  LL_I2C_HandleTransfer(I2C1, address, LL_I2C_ADDRSLAVE_7BIT, ubNbDataToTransmit, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

  /* (2) Loop until end of transfer received (STOP flag raised) ***************/


  /* Loop until STOP flag is raised  */
  while(!LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* (2.1) Transmit data (TXIS flag raised) *********************************/

    /* Check TXIS flag value in ISR register */
    if(LL_I2C_IsActiveFlag_TXIS(I2C1))
    {
      /* Write data in Transmit Data register.
      TXIS flag is cleared by writing data in TXDR register */
      LL_I2C_TransmitData8(I2C1, (*pTransmitBuffer++));
    }
  }

  /* (3) Clear pending flags, Data consistency are checking into Slave process */

  /* End of I2C_SlaveReceiver_MasterTransmitter Process */
  LL_I2C_ClearFlag_STOP(I2C1);
}


int32_t VL53L0X_read_byte(uint8_t address,  uint8_t index, uint8_t  *pdata) {
  // pdata = LL_I2C_ReceiveData8(I2C1);
  return 0;
}

int32_t VL53L0X_read_word(uint8_t address,  uint8_t index, uint16_t *pdata) {
  // pdata = LL_I2C_ReceiveData8(I2C1);
  return 0;
}

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata) {
  // pdata = LL_I2C_ReceiveData8(I2C1);
  return 0;
}

int32_t VL53L0X_write_byte(uint8_t address,  uint8_t index, uint8_t data) {
  // TODO: Index ?
  uint8_t buffer[2];
  buffer[0] = index;
  buffer[1] = data;
  Handle_I2C_Master_Write(address, 2, buffer);
}

int32_t VL53L0X_write_word(uint8_t address,  uint8_t index, uint16_t  data) {
 // TODO: Improve ?
  uint8_t buffer[2];
  buffer[0] = index;
  memcpy(buffer+1, &data, 2);
  Handle_I2C_Master_Write(address, 2, buffer);
}
