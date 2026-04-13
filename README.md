# Projeto Detector de Ondas Sonoras do Ambiente

## Descrição

Este projeto apresenta o desenvolvimento de um sistema embarcado capaz de detectar e classificar eventos sonoros presentes no ambiente em tempo real. O sistema diferencia três tipos principais de som: silêncio, conversa e palmas.

A solução utiliza um microfone analógico conectado ao conversor ADC do microcontrolador para capturar sinais sonoros. Esses sinais são processados por meio de uma análise da amplitude do som, permitindo identificar padrões característicos de cada tipo de evento.

Com base nessa classificação, o sistema fornece respostas visuais e sonoras:
- LEDs RGB indicam o tipo de som detectado
- Um buzzer é acionado em eventos específicos (palmas)
- Um display OLED exibe o estado atual do ambiente

Este projeto tem como objetivo aplicar conceitos fundamentais de sistemas embarcados, processamento de sinais e integração de periféricos, proporcionando uma solução prática e funcional.

---

## Objetivos

### Objetivo Geral
Desenvolver um sistema embarcado capaz de detectar e classificar sons do ambiente utilizando um microcontrolador e sensores analógicos.

### Objetivos Específicos
- Captar sinais de áudio utilizando um microfone analógico
- Processar os sinais utilizando o ADC do Raspberry Pi Pico
- Classificar os sons em silêncio, conversa e palma
- Indicar o estado através de LEDs RGB
- Exibir informações em um display OLED
- Acionar um buzzer em eventos de palma
- Implementar uma solução eficiente e em tempo real

---

## Hardware Utilizado

- Microcontrolador Raspberry Pi Pico  
- Microfone analógico (entrada ADC - GPIO 28)  
- LED RGB (GPIO 11 - Verde, GPIO 12 - Azul, GPIO 13 - Vermelho)  
- Buzzer (GPIO 10)  
- Display OLED SSD1306 via I2C (GPIO 14 - SDA, GPIO 15 - SCL)  
- Botão (GPIO 21)  

---

## Arquitetura do Sistema

O sistema é composto por três blocos principais:

### 1. Aquisição de Dados
O microfone captura o som ambiente e envia sinais analógicos para o ADC do microcontrolador.

### 2. Processamento
Os dados são filtrados e suavizados através de um envelope, permitindo reduzir ruídos e melhorar a precisão da detecção.

### 3. Saída
Com base na análise:
- LEDs indicam o estado do som
- OLED mostra o texto correspondente
- Buzzer é acionado para eventos de palma

---

## Dependências

Para executar o projeto, são necessárias as seguintes ferramentas:

- Raspberry Pi Pico SDK  
- CMake (versão 3.13 ou superior)  
- GCC ARM Toolchain  
- Visual Studio Code  
- Extensão CMake Tools  

### Bibliotecas utilizadas
- pico/stdlib  
- hardware/adc  
- hardware/pwm  
- hardware/i2c  

---

## Instalação e Execução

### 1. Preparação do ambiente

Certifique-se de que todas as ferramentas e dependências estão corretamente instaladas no sistema.

---

### 2. Clonar o repositório

```bash
git clone https://github.com/HeberHolanda01/projeto-identificador-de-eventos-sonoros_embarcatech
cd SEU_REPOSITORIO

## Créditos

Este projeto foi desenvolvido no âmbito do programa EmbarcaTech, com foco na aplicação prática de conceitos de sistemas embarcados, integração de hardware e software e processamento de sinais.

### Desenvolvedor
- Heber Holanda  

### Instituição
- Instituto Federal de Educação, Ciência e Tecnologia do Ceará (IFCE)  

### Programa Acadêmico
- EmbarcaTech – Formação em Sistemas Embarcados  
