/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

// Include for PM
#include <esp_pm.h>

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <sys/time.h>
// #include <sys/param.h>
// #include "unity.h"
// #include "esp_pm.h"
// #include "esp_sleep.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/semphr.h"
// #include "esp_log.h"
// #include "driver/timer.h"
// #include "driver/rtc_io.h"
// #include "soc/rtc_periph.h"
// #include "esp_rom_sys.h"

#include "esp32/clk.h"
// #include "esp32/ulp.h"

// #define MHZ (1000000)


#include "app_version.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

void set_cpu_freq(int freq){
	esp_pm_config_esp32_t pm_config = {
		.max_freq_mhz = freq
	};

	esp_pm_configure(&pm_config);
    printf("Waiting for frequency to be set to %d MHz...\n", freq);
    while (esp_clk_cpu_freq() / 1000000 != freq) {
        k_sleep(K_MSEC(100));
        printf("Frequency is %d MHz\n", esp_clk_cpu_freq() / 1000000);
    }
}

void set_voltage(int voltage){
	// Implementar aqui a lógica para alterar a tensão da CPU
	// Não disponível para a ESP32

	printk("dummy");
}

void main(void)
{
	int counter = 0;
	static const int test_freqs[] = {240, 40, 160, 240, 80, 40, 240, 40, 80, 10, 80, 20, 40};

	printk("Dynamic Frequency Scaling Application %s\n", APP_VERSION_STR);

	while (1) {
		counter++;
		int freq_index = counter%13 - 1;

		printk("Counter value: %d \t| Freq Index: %d \t Freq.: %d\n", counter, freq_index, test_freqs[freq_index]);

		// set_cpu_freq(test_freqs[freq_index]);

		k_sleep(K_MSEC(1000));
	}
}

