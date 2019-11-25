#include <string> 
#include "mbed.h"
#include "DHT11.h"
#include "GPS.h"


DigitalOut myled(LED1);
//PINES DE CONEXION DE LA TARJETA
DHT11 d(D3);
AnalogIn UVOUT(A0);
AnalogIn REF3V3(A1);
//CREACION DE VARIABLES
int uvlevel=0;
int reflevel=0;
int outvoltage;



//Serial pc(USBTX, USBRX);
Serial pc(SERIAL_TX, SERIAL_RX );

//GPS migps(PA_9 , PA_10);

GPS migps(PA_9, PA_10);

//CREACION DE FUNCIONES
void sensorTH();
void sensorUV();
void gps();
void todo();
 //float latitude2 ;
 //float longitude1;
  float latitude ;
 float longitude;
 float longitude2;
 float latitude2;
Ticker time_up;
//------------------------------------------------------------------------------------------------------
void todo()
{
        gps();
    sensorUV();
    //sensorTH();
}
//-----------------------------------------------------------------------------------------------------------
int main()
{
    time_up.attach(todo,15);
    
    
    pc.baud(9600); 
    
    
    while(1)
    { 
            //gps();
    //sensorUV();
    
    sensorTH();
    }
 
}
//-------------------------------------------------------------------------------------
void gps()
{
     if (migps.sample()==1)
            {
                
                myled=1;
                latitude = migps.latitude;
                
                 longitude = migps.longitude;
               
                float utc = migps.utc+50000;
                pc.printf("latitude: %0.2f, longitude: %0.2f, utc: %f\r\n",latitude,longitude,utc);
                wait(1); 
                
             }
            else{
               myled=0;
               
            
            }
}
//-----------------------------------------------------------------------------------------------------------------------
void sensorUV()
{
    uvlevel=(UVOUT.read());
    reflevel=(REF3V3.read());
    outvoltage= 100/(3.3/(UVOUT.read()*REF3V3.read()));
    pc.printf(" Porcentaje rayos UV: (%i)\r  !!", outvoltage);
    gps();
}
//---------------------------------------------------------------------------------------------
void sensorTH()
{
    int s;
    s = d.readData();
    if (s != DHT11::OK) {
        pc.printf("Error!\r\n");
    } else {
        pc.printf("  Temperatura en grados C :%d  !!  Porcentaje de Humedad:%d\r\n", d.readTemperature(), d.readHumidity());
    }
    wait(2);

}
