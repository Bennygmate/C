// Starting date: 15 April 2016

/*
 *  bmpServer.c
 *
 *
 */

// This program now serves an image of a specified request of the
// mandelbrot set

#ifndef _MANDELBROTH_
#define _MANDELBROTH_

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "pixelColor.h"
#include "mandelbrot.h"

static int waitForConnection (int serverSocket);
static int makeServerSocket (int portno);
static void serveHTML (int socket);
static void servePage (int socket, char * request);
static void serveBMP (int socket, char *tileCoord);

int escapeSteps (double x, double y);
long int zoomLevel (long int zoom);


#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7991
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt

#define SIZE 512                 //The length and width of the bmp in pixels
#define MIDWAY 256               //Half of the pixel length and width of the bmp

#define LIMIT 4                  
#define MAX_STEPS 256            //The maximum number of iterations to escape

typedef struct _color {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} color;

int main (int argc, char *argv[]) {
      
   printf ("************************************\n");
   printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
   printf ("Serving bmps since 2012\n");   
   
   int serverSocket = makeServerSocket (DEFAULT_PORT);   
   printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
   printf ("************************************\n");
   
   char request[REQUEST_BUFFER_SIZE];
   
   int numberServed = 0;
   while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
      
      printf ("*** So far served %d pages ***\n", numberServed);
      
      int connectionSocket = waitForConnection (serverSocket);
      // wait for a request to be sent from a web browser, open a new
      // connection for this conversation
      
      // read the first line of the request sent by the browser  
      int bytesRead;
      bytesRead = read (connectionSocket, request, (sizeof request)-1);
      assert (bytesRead >= 0); 
      // were we able to read any data from the connection?
            
      // print entire request to the console 
      printf (" *** Received http request ***\n %s\n", request);
      
      //send the browser a simple html page using http
      printf (" *** Sending http response ***\n");
      servePage(connectionSocket, request);
      
      // close the connection after sending the page- keep aust beautiful
      close(connectionSocket);
      
      numberServed++;
   } 
   
   // close the server connection after we are done- keep aust beautiful
   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}

static void servePage (int socket, char * request) {
   char tileCoord[REQUEST_BUFFER_SIZE];

   int i = 0;
   int x = 0;
   while (request[i] != '\0') {
      if (request[i] == '1') {
         i++;
         if (request[i] == '9') {
            i++;
            if (request[i] == '9') {
               i++;
               if (request[i] == '7') {
                  i++;
                  if (request[i + 1]== ' ') {
                     serveHTML(socket);
                  } else {
                     while (request[i + 5] != ' ') {
                        tileCoord[x] = request[i + 5];
                        i++;
                        x++;
                     }
                  }
                  // null-terminate where the '.' of '.bmp' is
                  tileCoord[x + 1] = 0;
                  serveBMP(socket, tileCoord);
               }
            }

         }
      }
      i++;
   }
   return;
}

static void serveHTML (int socket) {
   char* message;
 
   // first send the http response header
   message =
      "HTTP/1.0 200 Found\n"
      "Content-Type: text/html\n"
      "\n";
   printf ("about to send=> %s\n", message);
   write (socket, message, strlen (message));
 
   message =
      "<!DOCTYPE html>\n"
      "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
      "\n";      
   write (socket, message, strlen (message));
}

// Send the BMP
static void serveBMP (int socket, char *tileCoord) {
// BMP header from original code
   unsigned char header[] = {
     0x42,0x4d,0x5a,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
     0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,
     0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
     0x00,0x00,0x24,0x00,0x00,0x00,0x13,0x0b,
     0x00,0x00,0x13,0x0b,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00};

   write (socket, header, sizeof(header));

   // Finding the input coordinates and the zoom level
   double a;
   double b;
   long int zoom;
   sscanf (tileCoord, "tile_x%lf_y%lf_z%ld.bmp", &a, &b, &zoom);

   long int squareSize = zoomLevel (zoom); // number of pixels in one unit square

   color pixel;

   // The rest of the BMP
   int col = 0;                           //column number
   int row = 0;                           //row noumber

   // Loops until the variables = SIZE
   while (col < SIZE) {
      row = 0;                            // first square of a row of pixels

      while (row < SIZE) {

         //bottom left point of the image relative to the input point
         double x, y;
            x = a + (row - MIDWAY) / squareSize;
            y = b + (col - MIDWAY) / squareSize;

         // Calculates the number of steps to escape 
         int steps = escapeSteps (x, y);

         // Prints the mandelbrot tile using this number

         pixel.red = stepsToRed(steps);
            write(socket, &pixel.red, 1);
         
         pixel.green = stepsToGreen(steps);
            write(socket, &pixel.green, 1);
         
         pixel.blue = stepsToBlue(steps);
            write(socket, &pixel.blue, 1); 
        

         row++;
      }

      col ++;
   }

   // echo the http response to the console for debugging purpose
   printf ("VVVV about to send bmp file via http VVVV\n");
   printf ("^^^^ end of message ^^^^\n");

}

long int zoomLevel (long int zoom) {
   int x = 0;
   long int zoomlvl = 1;
   while (x < zoom) {
      zoomlvl *= 2;
      x++;
   }
   return zoomlvl;
}

int escapeSteps (double x, double y) {   // The mandelbrot formula : c = x + yi
   
   int iteration = 0;
   double a = 0;
   double b = 0;
   
   while (iteration < MAX_STEPS && a*a + b*b < LIMIT) {  
      // this is a & b after expanding z^2 + c
      // keeps calculating while increase iteration
      
      double aTemporary;
      double bTemporary;
      aTemporary = a*a - b*b + x;  // Temporary a
      bTemporary = 2*a*b + y;      // Temporary b
      b = bTemporary;              // Modified b coordinate
      a = aTemporary;              // Modified a coordinate
      
      iteration++;
   }
   
   return iteration;
}

// start the server listening on the specified port number
static int makeServerSocket (int portNumber) { 
   
   // create socket
   int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
   assert (serverSocket >= 0);   
   // error opening socket
   
   // bind socket to listening port
   struct sockaddr_in serverAddress;
   memset ((char *)&serverAddress, 0, sizeof(serverAddress));
   
   serverAddress.sin_family      = AF_INET;
   serverAddress.sin_addr.s_addr = INADDR_ANY;
   serverAddress.sin_port        = htons(portNumber);
   
   // let the server start immediately after a previous shutdown
   int optionValue = 1;
   setsockopt (
      serverSocket,
      SOL_SOCKET,
      SO_REUSEADDR,
      &optionValue, 
      sizeof(int)
   );

   int bindSuccess = 
      bind (
         serverSocket, 
         (struct sockaddr *) &serverAddress,
         sizeof (serverAddress)
      );
   
   assert (bindSuccess >= 0);
   // if this assert fails wait a short while to let the operating 
   // system clear the port before trying again
   
   return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
static int waitForConnection (int serverSocket) {
   // listen for a connection
   const int serverMaxBacklog = 10;
   listen (serverSocket, serverMaxBacklog);
   
   // accept the connection
   struct sockaddr_in clientAddress;
   socklen_t clientLen = sizeof(clientAddress);
   int connectionSocket = 
      accept (
         serverSocket, 
         (struct sockaddr *) &clientAddress, 
         &clientLen
      );
   
   assert(connectionSocket >= 0);
   // error on accept
   
   return (connectionSocket);
}

#endif

