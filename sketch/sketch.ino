#define FUNC_NUM 3

int value = -1; // the number got from serial port messages
int isReading = 0; // flag of reading number

void funcOne();
void funcTwo();
void funcThree();
void getIntFromSerial();
void callFuncsByNumber();

void (*funcs[])() =
    {
        funcOne,
        funcTwo,
        funcThree
    };

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
    testCallFuncsByNumber();
}

void callAfterRead(void *pointerOfFunction())
{
    int finished = isReading;
    getIntFromSerial();
    finished -= isReading;
    if(value >= 0 && finished == 1)
    {
        pointerOfFunction();
    }
}

void testGetIntFromSerial()
{
    // call this function in loop when you need to test getIntFromSerial()
    callAfterRead(getIntFromSerial);
}

void getIntFromSerial()
{
    if(Serial.available())
    {
        char ch = Serial.read();
        if(ch == 'H')
        {
          isReading = 1;
          value = 0;
          return;
        }
        int num_ch = ch - '0';
        if(num_ch >= 0 && num_ch <= 9 && isReading)
        {
          value = value * 10 + num_ch;
        }
        else
        {
          isReading = 0;
        }
    }
    return;
}

void testCallFuncsByNumber()
{
    // call this function when you test callFuncsByNumber()
    callAfterRead(callFuncsByNumber);
}

void callFuncsByNumber()
{
    if(value > -1 && value < FUNC_NUM)
    {
        funcs[value]();
    }
}

// sample functions
void funcOne()
{
    Serial.println("funcone");
    Serial.flush();
}

void funcTwo()
{
    Serial.println("functwo");
    Serial.flush();
}

void funcThree()
{
    Serial.println("functhree");
    Serial.flush();
}
