#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "board.h"

void app_main(void)
{
    board_init();

    while (1) {
        board_led_toggle(BOARD_LED_BLUE);
        vTaskDelay(pdMS_TO_TICKS(500));
        board_led_toggle(BOARD_LED_RED);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}