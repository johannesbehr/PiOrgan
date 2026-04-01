#include "virtualKeyboard.h"

#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

VirtualKeyboard::VirtualKeyboard()
{
    fd = -1;
}

VirtualKeyboard::~VirtualKeyboard()
{
    destroy();
}

bool VirtualKeyboard::init()
{
    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0)
        return false;

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_SYN);

    ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);

    struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor  = 0x1234;
    usetup.id.product = 0x5678;

    strcpy(usetup.name, "PiOrgan Virtual Keyboard");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    sleep(1); // Kernel braucht kurz Zeit zum Anlegen
    
    return true;
}

void VirtualKeyboard::sendShiftTap()
{
    if (fd < 0)
        return;

    sendKey(KEY_LEFTSHIFT, 1);
    sendKey(KEY_LEFTSHIFT, 0);
}

void VirtualKeyboard::destroy()
{
    if (fd >= 0)
    {
        ioctl(fd, UI_DEV_DESTROY);
        close(fd);
        fd = -1;
    }
}

void VirtualKeyboard::sendKey(int key, int value)
{
    struct input_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.type = EV_KEY;
    ev.code = key;
    ev.value = value;

    write(fd, &ev, sizeof(ev));

    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;

    write(fd, &ev, sizeof(ev));
}