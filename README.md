# STM32 IO Retarget to UART
STM32 read and write system call implementations for printf(), puts(), scanf() and getchar().

# Usage

* Pass UART handler to init function (e.g. UART2)
```
RTRGT_init(&huart2);
```

* Pass your transmit function (e.g. HAL polling transmit function)
```
RTRGT_set_tx_function(HAL_UART_Transmit);
```

* Pass your receive function (e.g. HAL polling transmit function)
```
RTRGT_set_rx_function(HAL_UART_Receive);
```
