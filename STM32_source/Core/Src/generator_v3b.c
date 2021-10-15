/*
 * generator.cpp
 *
 *  Created on: Jul 29, 2021
 *      Author: DIO
 */

#include <main.h>
#include "dma.h"
#include "font.h"
#include "settings.h"

void draw(void);
void prepare(void);
void color_stream(void);
uint8_t search(char bukva, uint8_t slice);

uint8_t buffer[BUFFER_SIZE];
uint8_t part = 0;																						// Текущая часть символа
uint8_t row = 0;																						// Текущий ряд символов

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern uint8_t color_map[480][100];
extern char screen[60][100];

void prepare(void){																						// Функция подготовки первых двух строк. Необходима, поскольку draw запускает передачу сразу.

	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);															// Необходима для проверки срабатывания функции, можно отключить
	part = 0;																							// Увеличение смещения по части символа
	for(uint8_t i = 0; i < 100; i++){																	// Подготовка строки 1
		buffer[i] = search(screen[row][i], part);
	}
	part++;
	for(uint8_t i = 0; i < 100; i++){																	// Подготовка строки 2
		buffer[i+100] = search(screen[row][i], part);
	}
	part++;																								// Увеличение смещения по части символа

}

void color_stream(void){
	DMA1_Stream4->CR |= DMA_SxCR_EN;
	HAL_SPI_Transmit_DMA(&hspi2, color_map, sizeof(color_map));
}


void draw(void){																						// Функция подготовки и вывода кадра
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);															// Необходима для проверки срабатывания функции, можно отключить
	DMA2_Stream3->CR |= DMA_SxCR_EN;																	// Включение DMA перед отправкой
	HAL_SPI_Transmit_DMA(&hspi1, buffer, sizeof(buffer));												// Включение DMA перед отправкой

	for(uint8_t l = 1; l < HALF_SCREEN_TIME_PIXEL_LINES; l++){											// Собственно цикл, в которой подготавливаются две строки кадра
		while(!(DMA2->LISR & DMA_LISR_HTIF3));															// Ожидание окончания передачи строки 1
		DMA2->LIFCR |= DMA_LIFCR_CHTIF3;																// Сброс флага
		for(uint8_t i = 0; i < 100; i++){																// Подготовка строки 1
			buffer[i] = search(screen[row][i], part);
		}

		part++;																							// Увеличение смещения по части символа
		while(!(DMA2->LISR & DMA_LISR_TCIF3));															// Ожидание окончания передачи строки 2
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3;																// Сброс флага
		for(uint8_t i = 0; i < 100; i++){																// Подготовка строки 2
			buffer[i+100] = search(screen[row][i], part);
		}
		part++;																							// Увеличение смещения по части символа
		if(part == 8){																					// Проверка на переполнение смещения части символа
			part = 0;																					// Сброс смещения
			row++;																						// Перемещение на следующий ряд символов
		}

	}
	row = 0;																							// Сброс смещения ряда символов
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	while(!(DMA2->LISR & DMA_LISR_TCIF3));																// Ожидания окончания передачи
	DMA2->LIFCR |= DMA_LIFCR_CTCIF3;																	// Сброс флага
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;																	// Отключение DMA
	DMA1_Stream4->CR &= ~DMA_SxCR_EN;
	DMA2->LIFCR = (1 << 27) | (1 << 26) | (1 << 25) | (1 << 24) | 										// Сброс флагов DMA
				  (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) |
				  (1 << 18) | (1 << 16) | (1 << 11) | (1 << 10) |
				  (1 << 9) | (1 << 8) | (1 << 6) | (1 << 5) |
				  (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1);
	DMA1->LIFCR = (1 << 27) | (1 << 26) | (1 << 25) | (1 << 24) | 										// Сброс флагов DMA
				  (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) |
				  (1 << 18) | (1 << 16) | (1 << 11) | (1 << 10) |
				  (1 << 9) | (1 << 8) | (1 << 6) | (1 << 5) |
				  (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1);


}


uint8_t search(char bukva, uint8_t slice){																// Функция поиска нужной части символа
	for(uint8_t i = 0; i < 94; i++ ){																	// Перебор массива reference и сравнение принятого символа и символом массива
		if(reference[i] == bukva){
			return font[i-1][slice];																	// Возвращает код части символа
			break;
		}
	}
	return 0;																							// Если вимвол отсутствует, возвращает 0
}

