#ifndef __ESP_USB_BOARD_H__
#define __ESP_USB_BOARD_H__

typedef enum {
    BOARD_LED_BLUE = 0,
    BOARD_LED_RED,
    BOARD_LED_MAX,
} board_led_t;

void board_init(void);

void board_led_on(board_led_t led);
void board_led_off(board_led_t led);
void board_led_toggle(board_led_t led);

#endif  /* __ESP_USB_BOARD_H__ */