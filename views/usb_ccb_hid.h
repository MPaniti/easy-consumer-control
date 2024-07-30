#pragma once

#include <gui/view.h>

typedef struct UsbCcbHid UsbCcbHid;

UsbCcbHid* usb_ccb_hid_alloc();
void usb_ccb_hid_free(UsbCcbHid* usb_ccb_hid);
View* usb_ccb_hid_get_view(UsbCcbHid* usb_ccb_hid);
void usb_ccb_hid_set_connected_status(UsbCcbHid* usb_ccb_hid, bool connected);
