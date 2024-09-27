/**
 * Константы номеров пинов 
 * **/
int const green = 13;   // светодиод зелёный
int const yellow = 12;  // светодиод жёлтый
int const red = 8;      // светодиод красный
int const button = 2;   // кнопка

/** 
 * Состояние светофора:
 *     GREEN       - горит зелёный
 *     GREEN_FLASH - мигает зелёный
 *     YELLOW      - горит зелёный
 *     RED         - горит красный
 * **/
typedef enum state {GREEN, GREEN_FLASH, YELLOW, RED} state_t;
state_t curr_state = GREEN;

// количество миганий
unsigned flash_count;

/**
 * Устанавливаем выходные пины для светодиодов
 * и входной для кнопки. 
 * **/
void setup()
{
	pinMode(green, OUTPUT);
	pinMode(yellow, OUTPUT);
	pinMode(red, OUTPUT);
  	pinMode(button, INPUT);
}

void loop()
{
    /**
     * В этом блоке проверяем нет ли сигнала на кнопке.
     * Если сигнал есть и горит зелёный, мы выжидаем 5 секунд
     * и запускаем процесс смены состояний.
     * Пока светофор в других состояниях, кнопка не будет 
     * реагировать.
     * **/
  if (HIGH == digitalRead(button) and GREEN == curr_state) {
    button_pushed = true;
    delay(5000);
    curr_state = GREEN_FLASH;
    flash_count = 0;
  }
  
  switch(curr_state) {
    case GREEN: { // просто горит зелёный
    	digitalWrite(green, HIGH);
    	break;
    }
    case GREEN_FLASH: { // мигает зелёный
      	digitalWrite(green, LOW);
    	delay(400);
    	digitalWrite(green, HIGH);
    	delay(400);
    	if (3 == ++flash_count) { // когда прошло три мигания, мы переходим к жёлтому
      		curr_state = YELLOW;
            digitalWrite(green, LOW);
        }
      	break;
    }
    
    case YELLOW:{ // зажигаем на время жёлтый и переходим к красному
    	digitalWrite(yellow, HIGH);
    	delay(1000);
    	digitalWrite(yellow, LOW);
    	curr_state = RED;
      	break;
  	}
    
    case RED: { // зажигаем на время красный, а затем снова зажигаем зелёный
    	digitalWrite(red, HIGH);
    	delay(3000);
    	digitalWrite(red, LOW);
    	curr_state = GREEN;
    	button_pushed = false;
  	}
  }
}