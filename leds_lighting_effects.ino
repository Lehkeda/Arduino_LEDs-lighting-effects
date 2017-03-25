/* LEDs lighting effect sketch 
 * Created 2017 - March - 25 
 * By : Hesham Mohamed (LehKeda) 
 * 
 */

/* Global variables */

/* LEDs array . For proper fading effect you
 * should attach your LEDs to PWM digital output 
 * PWM output pins are (3,5,6,9,10,11) in UNO board 
 * the array should be terminated with 0 value ;
*/
int led[] = {9,10,11,0}; 

int led_array_lenth;
int functions_array_lenth;

/* LEDs lighting effect functions */
// get lenth of leds array
void get_led_array_lenth(){
  for(int i=0; led[i];i++){
      led_array_lenth++;
    }
  }

// To fade in/out each LED individually
void fade_individual(){
    for (int i=0;i <led_array_lenth ; i++){
      // Fade in from min to max in increments of 5 points:
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
       // sets the value (range from 0 to 255):
       analogWrite(led[i], fadeValue);
       // wait for 30 milliseconds to see the dimming effect
       delay(30);
    }

  // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
     // sets the value (range from 0 to 255):
     analogWrite(led[i], fadeValue);
     // wait for 30 milliseconds to see the fading in effect
     delay(30);
    }
   } 
  }

// To fade in/out all LEDs at once .
void fade_all(){
 for(int i=0; i<led_array_lenth; i++){
      for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {

     // sets the fade value for all LEDs (range from 0 to 255):
     for(int x=0; x<led_array_lenth; x++){
       analogWrite(led[x], fadeValue);
      }

     // wait for 30 milliseconds to see the dimming effect
     delay(35);
    }

  // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      
      // sets the fade value for all LEDs (range from 0 to 255):
      for(int x=0; x<led_array_lenth; x++){
       analogWrite(led[x], fadeValue);
      }       
     
      // wait for 30 milliseconds to see the fading in effect
      delay(35);
   }
  }  
}

// To randomly turn on LEDs 
void random_individual_led(){
    randomSeed(analogRead(0)); // To shuffle random function 
    for(int i=0; i<=led_array_lenth; i++){
      /* In order to make all LEDs trun on the max value 
       * for random function should be as same as LEDs array lenth
       * because random function returns MAX-1 .
       */
      int current_led=random(led_array_lenth); 

      // 255 value makes LED on all time .
      analogWrite(led[current_led],255);

      // Delay before turn off the LED / Max time the LED will be on .
      delay(200);

      // turn off LED 
      analogWrite(led[current_led],0);
    }
  }

// To randomly light group of LEDs
 void random_led_group(){
    randomSeed(analogRead(0)); // To shuffle random function 
    for (int i=0; i <=led_array_lenth; i++ ){
      // LEDs will be lit up ;
      int current_leds[led_array_lenth]; 
      
      // Pointer to current_leds array , will be used to set LEDs will be lit up ; 
      int *ptr=current_leds; 
      
      // Number of LEDs will be lit 
      int number_of_leds= random(led_array_lenth);
      
      for (int x=0; x < number_of_leds; x++){
        *ptr=led[random(led_array_lenth)]; // set LED will be lit up ;
        
        // 255 value makes LED on all time .
        analogWrite(*ptr,255);
        
        ++ptr; // go to next item on current_leds array ;
      }
        
      // Delay before turn off the LED / Max time the LED will be on .
      delay(200);

      // turn off all LEDs have been lit 
      for (int y=0; current_leds[y]; y++){ 
       analogWrite(current_leds[y],0);
      }
     }
    }

/* Array of all LEDs lighting effect 
 *  Add the name of function of effect 
 *  you want or you can remove the name 
 *  of function of effect you don't want 
 */

void (*leds_lighting_effects_functions[])()={fade_all,fade_individual, random_individual_led,random_led_group,0};
  
void get_functions_array_lenth(){
  for(int i=0; leds_lighting_effects_functions[i];i++){
      functions_array_lenth++;
    }
  }

// the setup function runs once when you press reset or power the board
void setup() {
  
  // First we need to ge the lenth of LEDs array and functions array
  get_led_array_lenth();
  get_functions_array_lenth();
}

// the loop function runs over and over again forever
void loop() {
  randomSeed(analogRead(0));
  // Here we call functions respective to which effects we want 
  for (int i=0; leds_lighting_effects_functions[i]; i++){
    leds_lighting_effects_functions[random(functions_array_lenth)]();
  }
}

