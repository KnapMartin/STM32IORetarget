/*
 * retarget.h
 *
 *  Created on: Dec 5, 2024
 *      Author: Martin Knap
 */

#ifndef INC_RETARGET_H_
#define INC_RETARGET_H_


#define RTRGT_MAX_DELAY 100 // ms

struct UART_HandleTypeDef;
int _write(int file, char *data, int len);
int _read(int file, char *data, int len);

static UART_HandleTypeDef *s_huart = NULL;
static HAL_StatusTypeDef (*s_tx_func)(UART_HandleTypeDef *huart,
        const uint8_t *pData, uint16_t Size, uint32_t Timeout) = NULL;
static HAL_StatusTypeDef (*s_rx_func)(UART_HandleTypeDef *huart,
	uint8_t *pData, uint16_t Size, uint32_t Timeout) = NULL;

void RTRGT_init(UART_HandleTypeDef *huart)
{
	s_huart = huart;
}

void RTRGT_set_tx_function(
        HAL_StatusTypeDef (*tx_func_ptr)(UART_HandleTypeDef *huart,
                const uint8_t *pData, uint16_t Size, uint32_t Timeout))
{
	s_tx_func = tx_func_ptr;
}

void RTRGT_set_rx_function(
        HAL_StatusTypeDef (*rx_func_ptr)(UART_HandleTypeDef *huart,
                uint8_t *pData, uint16_t Size, uint32_t Timeout))
{
	s_rx_func = rx_func_ptr;
}

int _write(int file, char *data, int len)
{
	s_tx_func(s_huart, (uint8_t*) data, len, RTRGT_MAX_DELAY);
	return len;
}

int _read(int file, char *data, int len)
{
	s_rx_func(s_huart, (uint8_t*) data, len, RTRGT_MAX_DELAY);
	return len;
}

#endif /* INC_RETARGET_H_ */
