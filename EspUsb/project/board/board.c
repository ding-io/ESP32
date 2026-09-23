#include "board.h"
#include "esp_log.h"
#include "driver/gpio.h"

typedef struct {
    const gpio_num_t pin;
    const uint8_t on_l;
    bool  on;
} board_led_dev_t;

static board_led_dev_t board_leds[BOARD_LED_MAX] = {
    [BOARD_LED_BLUE] = { .pin = GPIO_NUM_15, .on_l = 1, .on = false, },
    [BOARD_LED_RED]  = { .pin = GPIO_NUM_16, .on_l = 1, .on = false, },
};

static void board_led_init(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = 0,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    for (board_led_t i = 0; i < BOARD_LED_MAX; i++) {
        conf.pin_bit_mask = 1ULL << board_leds[i].pin;
        gpio_config(&conf);
        board_led_off(i);
    }

    ESP_LOGI("Board", "LEDs initialized");
}

void board_led_on(board_led_t led)
{
    board_led_dev_t *dev = &board_leds[led];
    gpio_set_level(dev->pin, dev->on_l);
    dev->on = true;
}

void board_led_off(board_led_t led)
{
    board_led_dev_t *dev = &board_leds[led];
    gpio_set_level(dev->pin, !dev->on_l);
    dev->on = false;
}

void board_led_toggle(board_led_t led)
{
    board_led_dev_t *dev = &board_leds[led];
    if (dev->on) {
        gpio_set_level(dev->pin, !dev->on_l);
        dev->on = false;
    } else {
        gpio_set_level(dev->pin, dev->on_l);
        dev->on = true;
    }
}

void board_init(void)
{
    board_led_init();
}