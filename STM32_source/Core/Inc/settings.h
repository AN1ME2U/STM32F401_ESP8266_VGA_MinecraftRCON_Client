/*
 * settings.h
 *
 *  Created on: 29 авг. 2021 г.
 *      Author: DIO
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#define NUM_OF_SYMBOLS 95												// Кол-во символов, для которых подготовлен шрифт
#define SYMBOL_HEIGHT 8													// Количество строк символа
#define PIXEL_PRESCALLER 300											// Деление чистоты APB2 для генерации пиксельной частоты таймером TIM1
#define	NUM_OF_PIXELS_IN_LINE 800										// Количество пикселей в одной строке с учетом blank space
#define NUM_OF_LINES_IN_FRAME 525										// Количесто строк с учетом blank space
#define SCREEN_TIME_PIXEL_LINES 480										// Количество пиксельных линий в видимой области
#define HALF_SCREEN_TIME_PIXEL_LINES 240								// Количество пар пиксельных линий в видимой области
#define NUM_OF_CHARS_IN_LINE 100										// Количество символов в одной полной строке, с учетом blank space. В данном случае шрифт имеет ширину 8, следовательно 800/8 = 100
#define NUM_OF_LINES_OF_CHARS 60										// Количество выводимых строк символов. В данном случае активная зона имеет ширину 480px, а высота шрифта 8px, следовательно 48-/8 = 60
#define BUFFER_SIZE 200




#endif /* INC_SETTINGS_H_ */
