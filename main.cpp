
extern "C" void kernel_main() {

    // VGA text mode memory address
    volatile unsigned short* video_memory =
        reinterpret_cast<volatile unsigned short*>(0xB8000);

    // Message to display
    const char* message = "Hello from C++ kernel!";

    // Write the message to the screen
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i] =
            0x0F00 | static_cast<unsigned char>(message[i]);
    }
}
