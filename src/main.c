#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define SLEEP_TIME_MS 1000

static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
    printk("=== boot ===\n");

    if (!gpio_is_ready_dt(&led)) {
        printk("LED device NOT ready\n");
        return 0;
    }

    printk("LED ready: port=%p pin=%d\n", led.port, led.pin);

    gpio_pin_configure_dt(&led, GPIO_OUTPUT);

    while (1) {
        printk("toggle\n");
        gpio_pin_toggle_dt(&led);
        k_msleep(SLEEP_TIME_MS);
    }
}
