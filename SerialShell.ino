//
// Arduino Serial Shell
// By Daniel BP (www.danbp.org)
//
// This code snippet reads data from the serial port (user inputs)
// and parses the formatted data so it can be used by other functions.
// You can consider this a mini shell for the serial terminal.
//
// Command syntax:
// <commandname><separator><VariableId><separator><Value>
//
//---------------------------------------
// Main Class
//---------------------------------------
//
class serialCommandReader
{

private:
    const char SEPARATOR = ' '; //Separator character

public:
    String command; //Command Variable
    int var;        //Variable ID
    float val;      //Variable value

    //Default constructor
    serialCommandReader()
    {
        command = "";
        var = 0;
        val = 0;
    };

    //Read the serial port data
    String read()
    {
        if (Serial.available() > 0)
        {
            return Serial.readStringUntil('\n'); //Read the input String
        }
        return "";
    };

    //Process the data
    bool process(String inputReading)
    {
        command = "";
        val = var = 0;
        int break1 = inputReading.indexOf(SEPARATOR);
        if(break1 == -1) break1 = inputReading.length()-1;
        int break2 = inputReading.indexOf(SEPARATOR, break1 + 1);
        if(break2 == -1) break2 = inputReading.length()-1;
        int break3 = inputReading.length()-1;
        command = inputReading.substring(0, break1);
        if(break2 != break1) var = inputReading.substring(break1 + 1, break2).toInt();
        if(break2 != break3) val = inputReading.substring(break2 + 1, break3).toFloat();
        if (command.length() > 0)
            return true;
        return false;
    }

    //Does everything
    bool update()
    {
        return process(read());
    }

    //Clear the stored variables
    bool clear()
    {
        serialCommandReader();
    }

}; //End of the class declaration

//---------------------------------------
// Test Sketch
//---------------------------------------

serialCommandReader serialInput; //creates the class
float var1, var2 = 0;

void setup()
{
    Serial.begin(115200);                                                    // open the serial port at 115200 bp
    Serial.println("This Arduino is now a mini calculator!");                      //brief introduction
    Serial.println("Syntax <command> <variable_index> <value>");                      //brief introduction
    Serial.println("Commands: setvar, sum, substract, multiply and divide"); //brief introduction
    Serial.println("Available variables: 1 and 2");                                    //brief introduction
    Serial.println("Serial baud rate: 115200, new line: NL & CR");              //brief introduction
    Serial.println();
};

void loop()
{
    //Ouput the user command
    if (serialInput.update())
    {
        Serial.print("Command: ");
        Serial.print(serialInput.command);
        Serial.print("; Variable: ");
        Serial.print(serialInput.var);
        Serial.print("; Value: ");
        Serial.println(serialInput.val);

        //Perform actions based on the commands received
        if (serialInput.command == "setvar" && serialInput.var == 1)
        {
            var1 = serialInput.val;
        }
        else if (serialInput.command == "setvar" && serialInput.var == 2)
        {
            var2 = serialInput.val;
        }
        else if (serialInput.command == "sum")
        {
            Serial.print("Result: ");
            Serial.println(var1 + var2);
        }
        else if (serialInput.command == "subtract")
        {
            Serial.print("Result: ");
            Serial.println(var1 - var2);
        }
        else if (serialInput.command == "multiply")
        {
            Serial.print("Result: ");
            Serial.println(var1 * var2);
        }
        else if (serialInput.command == "divide")
        {
            Serial.println("Result: ");
            Serial.println(var1 / var2);
        }
        else
        {
            Serial.println("Invalid command");
        }
    }
};
