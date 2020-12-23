#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include <iostream>
#include <fstream>

FILE * openGNUPlot() {
    FILE * gnuplot = popen( "gnuplot", "w" ); /* otwarcie potoku do zapisu */
    return gnuplot;
}

void histogram(std::string data_filename, FILE * gnuplot){
    


}

int main() {
    FILE * gnuplot= openGNUPlot();


    pclose(gnuplot);
    return 0;