/*
 * Copyright 2022 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include <hardware/adc.h>


int lm35_init(void) {
    adc_init();
    adc_gpio_init(26); // numer GPIO, do którego podpinamy linie danych sensora (zieloną)
    return 0;
}

int temperature_get_data(double *sensor_data) {
    adc_select_input(0); // "0" oznacza numer ADC (dla GPIO26 mamy ADC0)
    uint adc_val = adc_read(); // odczytaj wartość ADC (wartości 0-4095)
    //printf("Odczytana wartość: %ld\n", val); // dla debugowania
    float mili_volts = adc_val * 3300 / 4096; // 3300 ponieważ napiecie referencyjne wynosi 3.3 V (czyli 3300 mV)
                                              // 4096 poniewaz ADC ma 12 bitów (2^12 = 4096)
    float temperature = mili_volts / 10.0f; // dzielimy przez 10 zgodnie z zaleceniami producenta
    printf("------- Temperatura: %f\n", temperature); // dla debugowania

    *sensor_data = temperature;

}