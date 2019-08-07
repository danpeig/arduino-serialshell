//
// This code snippet reads data from the serial port (user inputs) 
// and parses the formatted data so it can be used by other functions
//
// Command syntax:
// <commandname><separator><VariableId><separator><Value>
//
// Example: Set small circle (id=2) diameter equal to 12.3
// > setdia 2 12.3
//
//---------------------------------------
// Main Class
//---------------------------------------
//
class serialCommandReader {

private:
const char SEPARATOR = ' '; //Separator character

public:

String inputCommand; //Command Variable
int inputCommandVar; //Variable ID
float inputCommandVal; //Variable value

//Default constructor
serialCommandReader (){
    inputCommand = "null";
    inputCommandVar = -1;
    inputCommandVal = -1;
};

//Perform the reading
bool read(){
    String inputReading;
    int break1;
    int break2;
    int break3;
    if (Serial.available() > 0){
        inputReading = Serial.readStringUntil('\n'); //Read the input String
        break1 = inputReading.indexOf(SEPARATOR);
        break2 = inputReading.indexOf(SEPARATOR, break1+1);
        break3 = inputReading.indexOf('\n');
        inputCommand = inputReading.substring(0, break1);
        inputCommandVar = inputReading.substring(break1+1, break2).toInt();
        inputCommandVal = inputReading.substring(break2+1,break3-1).toFloat();
        return true;
    }
    return false;
};

bool clear(){
    serialCommandReader();
}

}; //End of the class declaration

//---------------------------------------
// Test Sketch
//---------------------------------------

serialCommandReader serialInput;

void setup(){
        Serial.begin(115200); // open the serial port at 115200 bp
		Serial.println("Try <command> <variable> <value>");
};

void loop(){
    if(serialInput.read()){
        Serial.print("Command:");
        Serial.println(serialInput.inputCommand);
        Serial.print("Variable:");
        Serial.println(serialInput.inputCommandVar);
        Serial.print("Value:");
        Serial.println(serialInput.inputCommandVal);
        serialInput.clear();
    }
};