//Autor: MMM

//Standard-Include-Files
#include <regc515c.h>

//Diese Include-Datei macht alle Funktionen der
//AkSen-Bibliothek bekannt.
//Unbedingt einbinden!
#include <stub.h>



//Breitensuche Kode
const int MAPLENGTH = 70;


void test(int i){
	lcd_cls();
	lcd_int(i);
	sleep(200);
}


int inBereich(int c) {
	if (c > 0 && c < 70) {
		return 1;
	}
	return 0;
}

char prePos(char actPos, const char map[]) {
	int result;
	int i;

	if (map[actPos] == 0) {
		return 'e';
	}

	result = actPos;

	for (i = 0; i < 4; i++) {
		char pos = 100;
		switch (i) {
		case 0: pos = actPos + 7; break;
		case 1: pos = actPos - 7; break;
		case 2: pos = actPos - 1; break;
		case 3: pos = actPos + 1; break;
		}

		if (inBereich(pos) & (map[pos] <= (map[result] - 1))) {
			result = pos;
		}
	}

	//if (inBereich(actPos + 7) & map[actPos + 7] != 'x' & (map[actPos + 7] <= map[actPos] - 1)) {
	//	result = actPos + 7;
	//}

	return result;

}



void findTheBestWay(const char costenMap[], char zielPos, char bestWay[]) {
	char prevPos = zielPos;
	int counter = 0;

	int counter2 = counter;
	int counter3 = 0;
	do {
		bestWay[counter] = prevPos;
		counter++;
		prevPos = prePos(prevPos, costenMap);
	} while ((prevPos != 'e') && (counter != 40));


	while (costenMap[bestWay[counter2 - 1]] != 0) {
		bestWay[counter] = bestWay[counter2];
		counter++;
		counter2++;
	}


	//62      61      68      67      62      61      68      67

	for (; counter3 != counter; counter3++) {
		counter--;
		bestWay[counter3] = bestWay[counter];
	}




}


void remAllElse(char map[], char toRem, char toLetPosition) {
	int i = 0;
	for (i = 0; i < MAPLENGTH; i++) {
		if (i != toLetPosition) {
			if (map[i] == toRem) {
				map[i] = 'q';
			}
		}
	}

	toRem = toRem - 1;

	if (inBereich(toLetPosition + 1) & (map[toLetPosition + 1] == toRem))
	{
		//remAllElse(map,map[lastPosition - 1] ,lastPosition - 1);
		//cleanMap(map, lastPosition - 1, lastStufe);
		remAllElse(map, toRem, toLetPosition + 1);
	}
	else if (inBereich(toLetPosition - 1) & (map[toLetPosition - 1] == toRem))
	{
		//remAllElse(map, map[lastPosition + 1], lastPosition + 1);

		remAllElse(map, toRem, toLetPosition - 1);
	}
	else if (inBereich(toLetPosition + 7) & (map[toLetPosition + 7] == toRem))
	{
		//remAllElse(map, map[lastPosition + 7], lastPosition + 7);
		remAllElse(map, toRem, toLetPosition + 7);
	}
	else if (inBereich(toLetPosition - 7) & (map[toLetPosition - 7] == toRem))
	{
		//remAllElse(map, map[lastPosition - 7], lastPosition - 7);
		remAllElse(map, toRem, toLetPosition - 7);
	}

}

void cleanPath(char map[]) {
	int i = 0;
	for (i = 0; i < MAPLENGTH; i++) {
		if (map[i] == 'q' || map[i] == 'x' || map[i] == 'F') {
			map[i] = '.';
		}
	}
}
void findKosten(char map[], char startPosition, char zielPosition) {
	char i;
	char stuffe;
	map[startPosition] = '\0';
	map[zielPosition] = 'z';

	for (stuffe = 0; stuffe < 40; stuffe++) {

		for (i = 0; i < 70; i++) {

			if ((int)(map[i]) == stuffe) {
				//addiere eins zu jedem Nachbarknoten

				if (inBereich(i - 1) & (map[i - 1] == '.')) {
					map[i - 1] = stuffe + 1;
				}

				if (inBereich(i + 1) & (map[i + 1] == '.')) {
					map[i + 1] = stuffe + 1;
				}

				if (inBereich(i + 7) & (map[i + 7] == '.')) {
					map[i + 7] = stuffe + 1;
				}

				if (inBereich(i - 7) & (map[i - 7] == '.')) {
					map[i - 7] = (stuffe + 1);
				}

				if (inBereich(i - 1) & (map[i - 1] == 'z')) {
					map[i - 1] = stuffe + 1;
					remAllElse(map, map[i - 1], i - 1);
					return;
				}

				if (inBereich(i + 1) & (map[i + 1] == 'z')) {
					map[i + 1] = stuffe + 1;
					remAllElse(map, map[i + 1], i + 1);
					return;
				}

				if (inBereich(i + 7) & (map[i + 7] == 'z')) {
					map[i + 7] = stuffe + 1;
					remAllElse(map, map[i + 7], i + 7);
					return;
				}

				if (inBereich(i - 7) & (map[i - 7] == 'z')) {
					map[i - 7] = (stuffe + 1);
					remAllElse(map, map[i - 7], i - 7);
					return;
				}

			}
		}

	}

}
void findAllKosten(char map[], char startPosition) {
	char stuffe;
	char i;
	map[startPosition] = '\0';
	//map[zielPosition] = 'z';

	for (stuffe = 0; stuffe < 40; stuffe++) {

		for (i = 0; i < 70; i++) {

			if ((int)(map[i]) == stuffe) {
				//addiere eins zu jedem Nachbarknoten

				if (inBereich(i - 1) & (map[i - 1] == '.')) {
					map[i - 1] = stuffe + 1;
				}

				if (inBereich(i + 1) & (map[i + 1] == '.')) {
					map[i + 1] = stuffe + 1;
				}

				if (inBereich(i + 7) & (map[i + 7] == '.')) {
					map[i + 7] = stuffe + 1;
				}

				if (inBereich(i - 7) & (map[i - 7] == '.')) {
					map[i - 7] = (stuffe + 1);
				}

				//if (inBereich(i - 1) & (map[i - 1] == 'F')) {
				//	map[i - 1] = stuffe + 1;
				//	//remAllElse(map, map[i - 1], i - 1);
				//	counter++;
				//	if (counter == anzahlVonZielen)
				//	return;
				//}

				//if (inBereich(i + 1) & (map[i + 1] == 'F')) {
				//	map[i + 1] = stuffe + 1;
				//	//remAllElse(map, map[i + 1], i + 1);
				//	counter++;
				//	if (counter == anzahlVonZielen)
				//	return;
				//}

				//if (inBereich(i + 7) & (map[i + 7] == 'F')) {
				//	map[i + 7] = stuffe + 1;
				//	//remAllElse(map, map[i + 7], i + 7);
				//	counter++;
				//	if (counter == anzahlVonZielen)
				//	return;
				//}

				//if (inBereich(i - 7) & (map[i - 7] == 'F')) {
				//	map[i - 7] = (stuffe + 1);
				//	//remAllElse(map, map[i - 7], i - 7);
				//	counter++;
				//	if (counter == anzahlVonZielen)
				//	return;
				//}

			}
		}

	}

}

int getWinkel(char richtung) {
	switch (richtung) {
	case 'u':
		return 0;
		break;
	case 'd':
		return 180;
		break;
	case 'l':
		return 270;
		break;
	case 'r':
		return 90;
		break;
	}
	return 0;
}
//returning the new Direction
char changeRobotDirection(char currentRichtung, char drehung) {
	int newRichtung;

	newRichtung = (getWinkel(currentRichtung) + getWinkel(drehung)) % 360;

	switch (newRichtung) {
	case 0:
		return 'u';
		break;
	case 90:
		return 'r';
		break;

	case 180:
		return 'd';
		break;

	case 270:
		return 'l';
		break;
	}

	return 0;

}

void getNavigation(const char way[], char navigation[], char startPos) {

	int i = 0;
	char ropRichtung = 'u';
	char nextRichtung = 'n';
	char pos = way[0];
	char nextPos = way[1];
	char naviPos = 0;

	while (way[i + 1] != '~'){

		pos = way[i];
		nextPos = way[i + 1];

		if (pos + 1 == nextPos) {
			nextRichtung = 'r';
		}
		else if (pos - 1 == nextPos) {
			nextRichtung = 'l';
		}
		else if (pos + 7 == nextPos) {
			nextRichtung = 'd';
		}
		else if (pos - 7 == nextPos) {
			nextRichtung = 'u';
		}
		else if (pos == nextPos) {
			i++;
			continue;
		}

		if (ropRichtung == nextRichtung) {
			navigation[naviPos] = 'w';
			naviPos++;
		}
		else {
			if (
				(ropRichtung == 'u' && nextRichtung == 'l')
				|| (ropRichtung == 'l' && nextRichtung == 'd')
				|| (ropRichtung == 'r' && nextRichtung == 'u')
				|| (ropRichtung == 'd' && nextRichtung == 'l')
				) {
				navigation[naviPos] = 'l';
				ropRichtung = changeRobotDirection(ropRichtung, 'l');
				naviPos++;
				navigation[naviPos] = 'w';
				naviPos++;

			}
			else if (
				(ropRichtung == 'u' && nextRichtung == 'r')
				|| (ropRichtung == 'l' && nextRichtung == 'u')
				|| (ropRichtung == 'r' && nextRichtung == 'd')
				|| (ropRichtung == 'd' && nextRichtung == 'r')
				) {
				navigation[naviPos] = 'r';
				naviPos++;
				ropRichtung = changeRobotDirection(ropRichtung, 'r');
				navigation[naviPos] = 'w';
				naviPos++;
			}
			else if ((ropRichtung == 'u' && nextRichtung == 'd')
				|| (ropRichtung == 'l' && nextRichtung == 'r')
				|| (ropRichtung == 'r' && nextRichtung == 'l')
				|| (ropRichtung == 'd' && nextRichtung == 'u')) {
				navigation[naviPos] = 'r';
				naviPos++;
				ropRichtung = changeRobotDirection(ropRichtung, 'r');

				navigation[naviPos] = 'r';
				naviPos++;
				ropRichtung = changeRobotDirection(ropRichtung, 'r');

				navigation[naviPos] = 'w';
				naviPos++;

			}

		}

		i++;
	}
}

void writeOutput(void){
	lcd_cls();
	lcd_puts(" ms:");
	lcd_ubyte(analog(10));
	lcd_puts(" ls:");
	lcd_ubyte(analog(9));

	lcd_setxy(1, 0);
	lcd_puts(" rs:");
	lcd_ubyte(analog(8));

	lcd_puts(" fs:");
	lcd_ubyte(analog(14));
}

void grad(unsigned char winkel){
	servo_arc(2, winkel);
}


void fahreRechtN(void){

	int frontSensor = analog(14);
	//leftSensor
	int leftSensor = analog(9);

	//Middlesensor
	int middleSensor = analog(10);

	//Rightsensor
	int rightSensor = analog(8);
	int i = 0;

	motor_richtung(1, 1);
	motor_richtung(2, 0);


	for (i = 0; i < 900; i++){
		// (middleSensor > 100 && leftSensor < 100 && rightSensor < 100) |
		if (frontSensor > 100 && i > 100){
			break;
		}
		//fahre link
		motor_pwm(1, 4);
		motor_pwm(2, 5);
		sleep(5);


		//frontSensor
		frontSensor = analog(14);

		//leftSensor
		leftSensor = analog(9);

		//Middlesensor
		middleSensor = analog(10);

		//Rightsensor
		rightSensor = analog(8);
	}
	motor_pwm(1, 0);//left motor 0
	motor_pwm(2, 0);//right motor 10

}

void fahreLinksN(void){


	int frontSensor = analog(14);
	//leftSensor
	int leftSensor = analog(9);

	//Middlesensor
	int middleSensor = analog(10);

	//Rightsensor
	int rightSensor = analog(8);

	int i = 0;

	motor_richtung(1, 0);
	motor_richtung(2, 1);



	for (i = 0; i < 900; i++){
		// (middleSensor > 100 && leftSensor < 100 && rightSensor < 100)|
		if (frontSensor > 100 && i > 100){
			break;
		}
		//fahre link
		motor_pwm(1, 4);
		motor_pwm(2, 3);
		sleep(5);

		//frontSensor
		frontSensor = analog(14);

		//leftSensor
		leftSensor = analog(9);

		//Middlesensor
		middleSensor = analog(10);

		//Rightsensor
		rightSensor = analog(8);
	}

	motor_pwm(1, 0);//left motor 0
	motor_pwm(2, 0);//right motor 10


}

//leftSensor 9
//rightSensor 8
//middleSensor 10
//left motor 2
//right motor 1

//schalter = 0 wenn der Roboter an der Wand ist
unsigned char schalter(){
	return digital_in(15);
}

void up(void){

	grad(65);
	//char servo, winkel;
	//servo = 2;
	//for (winkel = 0; winkel < 90; winkel--){
	//servo_arc(servo, winkel);
	//lcd_cls();
	//lcd_ubyte(winkel);
	//}
	// Servo auf einen bestimmten Winkel drehen

	// 5 ms warten
	sleep(50);

}


void down(void){
	grad(5);
	//char servo, winkel;
	//servo = 2;

	//// Winkel auswaehlen
	//for (winkel = 90; winkel >= 0; winkel--)
	//{
	//	// Servo auf einen bestimmten Winkel drehen
	//	servo_arc(servo, winkel);


	//}
	//
	//// 5 ms warten
	//sleep(1000);
	//grad(45);
	sleep(50);
}


//analog(0) = left
//analog(1) = right

void fahreRuckwert(void){
	//leftSensor
	int leftSensor = analog(9);

	//Middlesensor
	int middleSensor = analog(10);

	//rightsensor
	int rightSensor = analog(8);
	
	int bLeft = analog(0);
	int bRight = analog(1);

	int timer = 0;

	motor_richtung(1, 1);
	motor_richtung(2, 1);
	motor_pwm(1, 0);
	motor_pwm(2, 0);

	while (!(leftSensor > 100 && middleSensor > 100 && rightSensor > 100) || timer < 50){
		timer++;
		


		if (bRight > 100){
			//alg1 if the left sensor on black turn the right motor 
			motor_pwm(2, 0);
			motor_pwm(1, 4);

			//alg2 if the left sensor on black turn the left motor backwards
			// motor_richtung(1,1);
			// motor_richtung(2,1);
			// motor_pwm(2,8);
			// motor_pwm(1,0);

			lcd_cls();
			lcd_puts("weiter l");

		}//wenn right sensor auf black -> turn right
		else if (bLeft > 100){
			motor_pwm(2, 4);
			motor_pwm(1, 0);

			// motor_richtung(1,1);
			// motor_richtung(2,1);
			// motor_pwm(1,2);
			// motor_pwm(2,0);


			lcd_cls();
			lcd_puts("weiter r");

		}
		else {
			motor_richtung(1, 1);
			motor_richtung(2, 1);
			motor_pwm(1, 4);
			motor_pwm(2, 4);
			lcd_cls();
			lcd_puts("weiter weiter");

		}
		writeOutput();
		sleep(5);
		//leftSensor
		leftSensor = analog(9);

		//Middlesensor
		middleSensor = analog(10);

		//Rightsensor
		rightSensor = analog(8);
		bLeft = analog(0);
		bRight = analog(1);
	}



	motor_pwm(1, 0);//left motor 0
	motor_pwm(2, 0);//right motor 10
	motor_richtung(1, 0);
	motor_richtung(2, 0);
}

void fahreNachHinten(void){
	int i = 0;
	motor_richtung(1, 1);
	motor_richtung(2, 1);
	for (i = 0; i < 100; i++){
		motor_pwm(1, 4);
		motor_pwm(2, 10);
		sleep(5);
	}

	motor_pwm(1, 0);
	motor_pwm(2, 0);
	motor_richtung(1, 0);
	motor_richtung(2, 0);
}

void fahreWeiter(void){
	//leftSensor
	int leftSensor = analog(9);

	//Middlesensor
	int middleSensor = analog(10);

	//rightsensor
	int rightSensor = analog(8);

	int timer = 0;

	motor_richtung(1, 0);
	motor_richtung(2, 0);
	motor_pwm(1, 0);
	motor_pwm(2, 0);

	while (!(leftSensor > 100 && middleSensor > 100 && rightSensor > 100) || timer < 40){
		timer++;
		//wenn left sensor auf Black -> turn left
		if (schalter() == 0){
			motor_pwm(1, 0);
			motor_pwm(2, 0);
			down();
			break;
		}

		if (leftSensor > 100){
			//alg1 if the left sensor on black turn the right motor 
			motor_pwm(2, 0);
			motor_pwm(1, 4);

			//alg2 if the left sensor on black turn the left motor backwards
			// motor_richtung(1,1);
			// motor_richtung(2,1);
			// motor_pwm(2,8);
			// motor_pwm(1,0);

			lcd_cls();
			lcd_puts("weiter l");

		}//wenn right sensor auf black -> turn right
		else if (rightSensor > 100){
			motor_pwm(2, 4);
			motor_pwm(1, 0);

			// motor_richtung(1,1);
			// motor_richtung(2,1);
			// motor_pwm(1,2);
			// motor_pwm(2,0);


			lcd_cls();
			lcd_puts("weiter r");

		}
		else {
			motor_richtung(1, 0);
			motor_richtung(2, 0);
			motor_pwm(1, 4);
			motor_pwm(2, 4);
			lcd_cls();
			lcd_puts("weiter weiter");

		}
		writeOutput();
		sleep(5);
		//leftSensor
		leftSensor = analog(9);

		//Middlesensor
		middleSensor = analog(10);

		//Rightsensor
		rightSensor = analog(8);
	}



	motor_pwm(1, 0);//left motor 0
	motor_pwm(2, 0);//right motor 10
}




void fahreEingabe(char * eingabe2){
	int i = 0;

	
	while (*eingabe2){

		switch (*eingabe2){
		case 'l':
			//printf("fahrelinks");  
			lcd_cls();
			lcd_puts("left");
			fahreLinksN();
			sleep(100);
			break;

		case 'r':
			*eingabe2++;
			
			if (*eingabe2 == 'r'){
				*eingabe2++;
				*eingabe2++;
				fahreRuckwert();
				sleep(1000);

				if (*eingabe2 == 'r'){
					//printf("fahrelinks");  
					lcd_cls();
					lcd_puts("left");
					fahreLinksN();
					sleep(100);
				}
				else if (*eingabe2 == 'l'){
					*eingabe2--;
					lcd_cls();
					lcd_puts("right");
					fahreRechtN();
					sleep(100);
				}
				else {
					//TODO hier muss der Roboter 190 grad drehen
				}
				*eingabe2++;
				

			}
			else
			{
			*eingabe2--;
			lcd_cls();
			lcd_puts("right");
			fahreRechtN();
			sleep(100);

			}
			//printf("fahreRecht");
			break;

		case 'w':
			lcd_cls();
			lcd_puts("weiter");
			fahreWeiter();
			sleep(100);
			//printf("fahreWeiter");
			break;
		}

		motor_pwm(1, 0);//left motor 0
		motor_pwm(2, 0);//right motor 10
		sleep(100);
		//	printf("%c", *eingabe);
		*eingabe2++;
	}

	motor_pwm(1, 0);//left motor 0
	motor_pwm(2, 0);//right motor 10
	lcd_cls();
}


	char map[70] = "xxFxFxxx..x..xF.x.x.Fx.x...xx.x..xxx..x..xx..x..xxx.x..xF..x..Fx..x..x";


	char bestWay1[40] = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	char bestWay[3][40] = { "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" };

	char bestReturnWay[3][40] = { "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" };
	char navigation[3][70] =
	{ "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"
	, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"
	, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0" };


//Hauptprogrammroutine
void AksenMain(void)
{

	/*char * eingabe1 = "wrwrwrwrwrwlwlwlwlwlwlwlwlwlwl";
	fahreEingabe(eingabe1);
	*/

	//ruckwert fahren testen******
	//int i = 0;
	//for (i = 0; i < 5; i++){

	//fahreRuckwert();

	//sleep(1000);

	//}

	
	
	char startPosition = 68;
	char zielPosition[3] = { 4, 20, 62 };

	int i = 0;
	test(1);
	
	for (i = 0; i < 3; i++){
	test(2 + i);
	findAllKosten(map, startPosition);
	findTheBestWay(map, zielPosition[i], bestWay[i]);
	getNavigation(bestWay[i], navigation[i], startPosition);
	}
	test(3);


	up();
	fahreEingabe(navigation[0]);
	up();

	

	/*fahreLinksN();
	fahreRuckwert();
	sleep(1000);
	fahreLinksN();
	fahreRuckwert();
	test(4);
	fahreEingabe(navigation[0]);
	up();
	fahreLinksN();
	fahreRuckwert();
	sleep(1000);
	fahreLinksN();
	fahreRuckwert();
	test(5);
	fahreEingabe(navigation[1]);
	up();

*/




	lcd_puts("ende");
	while (1){
		sleep(100);
	}

}
