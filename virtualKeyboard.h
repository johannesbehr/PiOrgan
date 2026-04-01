#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

class VirtualKeyboard
{
public:
    VirtualKeyboard();
    ~VirtualKeyboard();

    bool init();
    void sendShiftTap();
    void destroy();

private:
    int fd;

    void sendKey(int key, int value);
};

#endif // VIRTUALKEYBOARD_H