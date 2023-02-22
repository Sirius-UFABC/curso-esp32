#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/adc.h"

/*Programa para fazer piscar um LED*/ /**/

#define PIN 13 /*definindo o pino*/  
#define BT_PIN 34 /*declarando pino de entrada*/

void app_main(void)
{
    /*funções para a seleção do pino*/
    /*gpio_pad_select_gpio(PIN); Linha dada no vídeo quando compilei não de erro*/
    esp_rom_gpio_pad_select_gpio(PIN);

    /*configura o sentido do pino (Numero do Pino, Como vai ser configurado)*/
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT); 

    
   
    esp_rom_gpio_pad_select_gpio(BT_PIN);
    gpio_set_direction(BT_PIN, GPIO_MODE_INPUT); 

    /*criando uma variável booleana*/
    bool status = 0;

    while(1){
        /*status = !status; quando quiser variando o status*/
        status = gpio_get_level(BT_PIN);
        gpio_set_level(PIN,status);
        vTaskDelay(10 / portTICK_PERIOD_MS); /*faz a vez do DELAY em milisegundos (ciclo do delay / ciclo de máquina)*/
    }

    /*Referente ao ADC*/
    adc1_config_width(ADC_WIDTH_BIT_13); /*definindo qual a resolução para o ADC*/
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11); /*confirgurar o adc1 canal 4 com um ganho de 11 dB*/

    adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11); 

    while(true){
        int val1 = 0;
        int val2 = 0;
        val1 = adc1_get_raw(ADC1_CHANNEL_4); /*para efetuar a discretização/leitura do valor analógico no pino, nesse caso, ADC1_CHANNEL_4)*/
        adc2_get_raw(ADC2_CHANNEL_0,ADC_WIDTH_BIT_13, &val2); /*essa função não retorna um valor, mas sim um status de erro (CANAL, Configuração de largura/precisão, Ponteiro que retorna o valor discretizado )*/

        printf("ADC1: %fV ADC2: %fV \n", val1*(3.3/4095), val2*(3.3/4095));
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}