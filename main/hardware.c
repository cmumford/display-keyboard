
#include "hardware.h"

#include <freertos/FreeRTOS.h>

#include <class/hid/hid.h>
#include <class/hid/hid_device.h>
#include <driver/gpio.h>
#include <driver/periph_ctrl.h>
#include <esp32s2/rom/gpio.h>
#include <esp_log.h>
#include <esp_rom_gpio.h>
#include <freertos/task.h>
#include <hal/gpio_ll.h>
#include <hal/gpio_types.h>
#include <hal/usb_hal.h>
#include <soc/periph_defs.h>
#include <soc/usb_periph.h>
#include <tusb.h>

// Copied from hw/bsp/esp32s2_saola_1/esp32s2_saola_1.c.
static void configure_pins(usb_hal_context_t* usb) {
  /* usb_periph_iopins currently configures USB_OTG as USB Device.
   * Introduce additional parameters in usb_hal_context_t when adding support
   * for USB Host.
   */
  for (const usb_iopin_dsc_t* iopin = usb_periph_iopins; iopin->pin != -1;
       ++iopin) {
    if ((usb->use_external_phy) || (iopin->ext_phy_only == 0)) {
      esp_rom_gpio_pad_select_gpio(iopin->pin);
      if (iopin->is_output) {
        esp_rom_gpio_connect_out_signal(iopin->pin, iopin->func, false, false);
      } else {
        esp_rom_gpio_connect_in_signal(iopin->pin, iopin->func, false);
        if ((iopin->pin != GPIO_FUNC_IN_LOW) &&
            (iopin->pin != GPIO_FUNC_IN_HIGH)) {
          gpio_ll_input_enable(&GPIO, iopin->pin);
        }
      }
      esp_rom_gpio_pad_unhold(iopin->pin);
    }
  }
  if (!usb->use_external_phy) {
    gpio_set_drive_capability(USBPHY_DM_NUM, GPIO_DRIVE_CAP_3);
    gpio_set_drive_capability(USBPHY_DP_NUM, GPIO_DRIVE_CAP_3);
  }
}

// Copied from hw/bsp/esp32s2_saola_1/esp32s2_saola_1.c.
void board_init() {
  // USB Controller Hal init
  periph_module_reset(PERIPH_USB_MODULE);
  periph_module_enable(PERIPH_USB_MODULE);

  usb_hal_context_t hal = {
      .use_external_phy = false  // use built-in PHY
  };
  usb_hal_init(&hal);
  configure_pins(&hal);
}