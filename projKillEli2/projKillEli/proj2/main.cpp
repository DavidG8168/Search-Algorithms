#include "Main.cpp"
#include <iostream>

// The sub-main.
int main(int argc, char** argv) {
    // Create the other main that runs the server.
    boot::Main* m = new boot::Main();
    // Send the command arguments to the function.
    m->main(argc,argv);
    return 0;
}