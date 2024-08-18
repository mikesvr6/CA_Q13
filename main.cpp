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
Serial pc(USBRX, USBTX); // This script appears to be for a previous version of mbed, to fix we wil have to change the coding for the mbed 6 version aswell as any other errors 
Serial dev(p9, p10); // Pin nomenclature is incorrect as use of "Serial" in mbed 6

void dev_recv(){
    while(dev.readable()){
        pc.putc(dev.getc())    // putc and getc are not used in mbed 6, will need to add a colon here as well
    }    
}

void pc_recv(){
    while(pc.readable()){
        dev.putc(pc.getc());    // as above
    }    
}

int main() {
    pc.baud(9600);
    device1.baud(115200); //device1 is not correct here nd will need to be changed to dev as well as the baud rate from 115200 to 9600
    pc.attach(&pc_recv);
    dev.atach(&dev); //there is no dev interrupt , needs to be changed to &dev_recv
    pc.printf("Hello!! \r\n"); // printf here wiill be an issue
    
    while(1) {
        myled = 1;
        wait(1); // wait here is incorrect and not in use. will need to be changed
        myled = 0;
        wait(1); // as above
    }
}