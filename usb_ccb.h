#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <notification/notification.h>

#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include "views/usb_ccb_about.h"
#include "views/usb_ccb_help.h"
#include "views/usb_ccb_start.h"
#include "views/usb_ccb_hid.h"  // Include the new header file for UsbCcbHid

typedef struct {
    Gui* gui;
    NotificationApp* notifications;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    DialogEx* dialog;
    UsbCcbAbout* usb_ccb_about;
    UsbCcbHelp* usb_ccb_help;
    UsbCcbStart* usb_ccb_start;
    UsbCcbHid* usb_ccb_hid;  // Add a new field for UsbCcbHid
    uint32_t view_id;
} UsbCcb;

typedef enum {
    UsbCcbViewSubmenu,
    UsbCcbViewAbout,
    UsbCcbViewHelp,
    UsbCcbViewStart,
    UsbCcbViewHid,  // Add new enum value for UsbCcbHid
    UsbCcbViewExitConfirm,
} UsbCcbView;

// Function prototypes
UsbCcb* usb_ccb_app_alloc();
void usb_ccb_app_free(UsbCcb* app);
int32_t usb_ccb_app(void* p);
