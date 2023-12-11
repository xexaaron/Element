#define WINDOWDLL_EXPORTS
#include "include/Window.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

WINDOWDLL_API int CreateAndRunWindow() {
    Display *display;
    Window window;
    XEvent event;

    // Open a connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    // Create a simple window
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 10, 10, 400, 300, 1,
                                 BlackPixel(display, screen),
                                 WhitePixel(display, screen));

    // Select the kind of events we are interested in
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map the window to the screen
    XMapWindow(display, window);

    // Enter the event loop
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Handle expose events (window being shown)
            // You can add drawing code here if needed
        }
        if (event.type == KeyPress) {
            // Handle key press events
            break; // Exit the loop on any key press
        }
    }

    // Close the display and exit
    XCloseDisplay(display);
    return 0;
}
 
    

