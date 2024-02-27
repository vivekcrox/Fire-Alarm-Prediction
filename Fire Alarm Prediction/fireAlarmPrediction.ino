class ML_Model {
public:
  float predict(float* features) {
    float temp = features[0];
    // Logistic regression model parameters (you need to adjust these based on your trained model)
    float intercept =  0.9701847660091361;
    float coef_temperature = 0.05901801;

    // Calculate the linear combination
    float linear_combination = intercept + coef_temperature * temp ;

    // Apply the logistic function to get the probability
    float probability = 1.0 / (1.0 + exp(-linear_combination));

    // Return the probability
    return probability;
   }
};
ML_Model model;


#include <LiquidCrystal.h>
float temperature;
int led_red=7;
int led_green=8;
int buzzer=6;
int sensorval;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16, 2);
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  temperature=analogRead(A0);
  temperature=temperature*1.34;
  lcd.setCursor(0, 1);
  lcd.setCursor(6, 1);
   float features[] = {temperature};
  int alarmPrediction = model.predict(features);
  if(alarmPrediction==1){
    digitalWrite(led_red,HIGH);
    digitalWrite(buzzer,HIGH);
     lcd.setCursor(0,0);
    lcd.print("TEMP HIGH ALERT");
    tone(buzzer,800,200);
    delay(200);         
    tone(buzzer,600,200);
  }
 else{
  	digitalWrite(led_green,HIGH);
    digitalWrite(led_red,LOW);
    lcd.setCursor(0,0);
    lcd.print("TEMP LOW ALERT ");
  }
  Serial.print(" Fire Alarm Prediction: ");
  Serial.println(alarmPrediction);
}