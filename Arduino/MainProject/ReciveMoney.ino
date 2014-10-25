#include <SoftwareSerial.h>
//===========Control Status==========//
#define AcceptBill       0x02
#define RejectBill       0x0F
#define HoldBill         0x18
#define RequestBillStatus 0x0C
//==========Command Respond==============//
#define PowerOn          0x80
#define Request02        0x8F
#define BillOk           0x81

//==========Recive Value Money===========//
#define TwentyBath       0x40
#define FiftyBath        0x41
#define OnehundredBath   0x42
#define FivehundredBath  0x43
#define OnethousandBath  0x44

//============Response Bill=============//
#define MotorFailure     0x20
#define CheckSumError    0x21
#define BillJam          0x22
#define BillRemove       0x23
#define StackerOpen      0x24
#define SensorProblem    0x25
#define CommunicationFailure    0x26
#define BillFish         0x27
#define StackerProblem   0x28
#define BillReject       0x29
#define InvalideCommand  0x2A
#define Revserved        0x2E
#define WhenErrorStatusisExclusion    0x2F
#define BillAcceptorEnableStatus      0x3E
#define BillAcceptorInhibitStatus     0x5E

char powerUp[] = {PowerOn,Request02};
char choice = '/0';

char bufferRx[100];
int indexRx = 0;
int indexRead = 0;

char serialbuffer[1000];
SoftwareSerial mySerial(10, 11);// RX, TX


void Init(void)
{
  Serial.begin(9600,SERIAL_8E1); 
  mySerial.begin(9600);
  Serial.println("hello");  
}

void ReciveBill(void)
{ 
 
    
   
}

void SendData(byte data)
{
  Serial.write((char)data);
}

void CalcRxData()
{
  if(indexRx == indexRead)return;
  int numData = indexRx - indexRead;
  byte data = bufferRx[indexRead];
  
  switch(data){
          case Request02 : 
              SendData(AcceptBill); break;
          case CommunicationFailure : 
              SendData(AcceptBill); break;
              
          case BillOk : // imperment
              ReciveBill(); break;
}

int8_t WaitCommand(byte expected_answer, unsigned int timeout)
{

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    
    while( Serial.available() > 0) Serial.read();  
     
    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(Serial.available() != 0){    
           
            expected_answer = Serial.read();
            x++;           
            answer = 1;
        }
         // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));   

    return answer;
}


boolean ByteArrayCompare(byte a[],byte byte b[],int array_size)
{
   for (int i = 0; i < array_size; ++i)
     if (a[i] != b[i])
       return(false);
   return(true);
}
