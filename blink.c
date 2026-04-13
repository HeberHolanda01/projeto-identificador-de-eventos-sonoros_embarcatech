#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"

// ================= MIC =================
#define MIC_PIN 28
#define MIC_CHANNEL 2

// ================= LED =================
#define LED_B 12
#define LED_R 13
#define LED_G 11

// ================= BUZZER =================
#define BUZZER 10

// ================= OLED =================
#define I2C_PORT i2c1
#define SDA_PIN 14
#define SCL_PIN 15
#define OLED_ADDR 0x3C

// ================= BOTAO A =================
#define BTN_A 21

// ================= BUZZER PWM =================
void buzzer_init(){
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_wrap(slice, 10000);
    pwm_set_enabled(slice, true);
}

void buzzer_beep(){
    uint slice = pwm_gpio_to_slice_num(BUZZER);

    pwm_set_gpio_level(BUZZER, 5000);
    sleep_ms(80);
    pwm_set_gpio_level(BUZZER, 0);
}

// ================= FONT =================
uint8_t font(char c, int i){
    switch(c){
        case 'P': return (uint8_t[]){0x7F,0x09,0x09,0x09,0x06}[i];
        case 'A': return (uint8_t[]){0x7E,0x09,0x09,0x09,0x7E}[i];
        case 'L': return (uint8_t[]){0x7F,0x40,0x40,0x40,0x40}[i];
        case 'M': return (uint8_t[]){0x7F,0x02,0x04,0x02,0x7F}[i];
        case 'C': return (uint8_t[]){0x3E,0x41,0x41,0x41,0x22}[i];
        case 'O': return (uint8_t[]){0x3E,0x41,0x41,0x41,0x3E}[i];
        case 'N': return (uint8_t[]){0x7F,0x02,0x04,0x08,0x7F}[i];
        case 'V': return (uint8_t[]){0x3F,0x40,0x40,0x40,0x3F}[i];
        case 'R': return (uint8_t[]){0x7F,0x09,0x19,0x29,0x46}[i];
        case 'U': return (uint8_t[]){0x3F,0x40,0x40,0x40,0x3F}[i];
        case 'I': return (uint8_t[]){0x41,0x7F,0x41,0x00,0x00}[i];
        case 'S': return (uint8_t[]){0x26,0x49,0x49,0x49,0x32}[i];
        case 'E': return (uint8_t[]){0x7F,0x49,0x49,0x49,0x41}[i];
        case ' ': return 0x00;
        default: return 0x00;
    }
}

// ================= OLED =================
void oled_cmd(uint8_t c){
    uint8_t b[2]={0x00,c};
    i2c_write_blocking(I2C_PORT,OLED_ADDR,b,2,false);
}

void oled_data(uint8_t d){
    uint8_t b[2]={0x40,d};
    i2c_write_blocking(I2C_PORT,OLED_ADDR,b,2,false);
}

void oled_init(){
    sleep_ms(100);

    oled_cmd(0xAE);
    oled_cmd(0x20); oled_cmd(0x00);
    oled_cmd(0xB0);
    oled_cmd(0xC8);
    oled_cmd(0x00);
    oled_cmd(0x10);
    oled_cmd(0x40);
    oled_cmd(0x81); oled_cmd(0xFF);
    oled_cmd(0xA1);
    oled_cmd(0xA6);
    oled_cmd(0xA8); oled_cmd(0x3F);
    oled_cmd(0xD3); oled_cmd(0x00);
    oled_cmd(0xD5); oled_cmd(0xF0);
    oled_cmd(0xD9); oled_cmd(0x22);
    oled_cmd(0xDA); oled_cmd(0x12);
    oled_cmd(0xDB); oled_cmd(0x20);
    oled_cmd(0x8D); oled_cmd(0x14);
    oled_cmd(0xAF);
}

void oled_clear(){
    for(int i=0;i<1024;i++) oled_data(0x00);
}

void oled_set_cursor(int page,int col){
    oled_cmd(0xB0+page);
    oled_cmd(0x00+(col&0x0F));
    oled_cmd(0x10+(col>>4));
}

void oled_char(char c){
    for(int i=0;i<5;i++){
        oled_data(font(c,i));
    }
    oled_data(0x00);
}

void oled_print(char *s){
    while(*s) oled_char(*s++);
}

// ================= LED =================
void pwm_init_pin(int pin){
    gpio_set_function(pin,GPIO_FUNC_PWM);
    uint slice=pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice,65535);
    pwm_set_enabled(slice,true);
}

void set_color(int r,int g,int b){
    pwm_set_gpio_level(LED_R,r);
    pwm_set_gpio_level(LED_G,g);
    pwm_set_gpio_level(LED_B,b);
}

// ================= MIC =================
int mic_read(){
    int max=0;

    for(int i=0;i<8;i++){
        adc_select_input(MIC_CHANNEL);
        int v=adc_read();
        if(v>max) max=v;
        sleep_us(120);
    }

    return max;
}

// ================= MAIN =================
int main(){
    stdio_init_all();

    adc_init();
    adc_gpio_init(MIC_PIN);

    pwm_init_pin(LED_R);
    pwm_init_pin(LED_G);
    pwm_init_pin(LED_B);

    buzzer_init();

    i2c_init(I2C_PORT,400*1000);
    gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    oled_init();
    oled_clear();

    

    // ================= CALIBRAÇÃO =================
    long sum=0;
    for(int i=0;i<120;i++){
        sum += mic_read();
        sleep_ms(2);
    }

    float base=sum/120.0;
    float envelope=base;

    while(1){

        int value=mic_read();

        envelope=(envelope*0.85)+(value*0.15);

        int diff=envelope-base;
        if(diff<0) diff=0;

        int amp=diff*12;

        char *estado;

     if(amp > 2500){
    estado = "CONVERSA";
    set_color(0,65535,0);
    buzzer_beep();
}
else if(amp > 400){
    estado = "PALMA";
    set_color(65535,0,0);
}
        else{
            estado="SILENCIO";
            set_color(0,0,65535);
        }

    // ================= OLED =================
oled_set_cursor(0,0);
oled_print("SOM:        ");

oled_set_cursor(2,0);
oled_print("            ");

oled_set_cursor(2,0);
oled_print(estado);

sleep_ms(80);;
    }
}