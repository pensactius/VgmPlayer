#include "lcd.h"
#include "config.h"

LCD::LCD() : m_lcd(0x3f, 20, 4) 
{
	m_lcd.init();
	m_lcd.init();
	m_lcd.backlight();	
	m_lcd.clear();
}
void LCD::print(const char *msg, uint8_t col=0, uint8_t row=0)
{
	m_lcd.setCursor (col, row);
	m_lcd.print (msg);
}

void LCD::clear() {m_lcd.clear();}

void LCD::scroll()
{
	m_lcd.scrollDisplayLeft();
}