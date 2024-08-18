/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


DigitalOut myled(LED1);
UnbufferedSerial pc(USBTX, USBRX); /* This script appears to be for a previous version of mbed, 
to fix we wil have to change the coding for the mbed 6 version aswell as any other errors 
unbufferredSerial added above, USBRX and TX need to swapped for proper order*/

UnbufferedSerial dev(PA_0, PA_1); /* Pin nomenclature is incorrect as use of "Serial" in mbed 6. 
UnbufferedSerial added here. Pins changed to proper format, issue may not be solved!!   */

/* + MbedOS Error Info ++
Error Status: 0x80010130 Code: 304 Module: 1
Error Message: pinmap not found for peripheral
Location: 0x8007CB1
Error Value: 0x17

found when running - indicating the dev pins are in use, will change these to PA_0, PA_1 which are available from the pinmap */

const char* buffer; // buffer variable added for data storage


void dev_recv(){
    while(dev.readable()){
        dev.read(&buffer, 8);   
        pc.write(&buffer, 8); 
    // putc and getc are not used in mbed 6, will need to add a colon here as well. get and put replaced with read and write
    }    
}

void pc_recv(){
    while(pc.readable()){
        pc.read(&buffer, 8);
        dev.write(&buffer, 8);       // as above
    }    
}

int main() {
    pc.baud(9600);
    dev.baud(9600); //device1 is not correct here nd will need to be changed to dev as well as the baud rate from 115200 to 9600
    pc.attach(&pc_recv);
    dev.attach(&dev_recv); //there is no dev interrupt , needs to be changed to &dev_recv
    pc.write("Hello!! \r\n", 8); // printf here will be an issue, replaced with write
    
    while(1) {
        myled = 1;
        ThisThread::sleep_for(1s); // wait here is incorrect and not in use. will need to be changed, replaced with sleep_for
        myled = 0;
        ThisThread::sleep_for(1s); // as above
    }
}