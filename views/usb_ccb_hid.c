#include "usb_ccb_hid.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>
#include <gui/elements.h>

#define HID_BUTTON_COUNT 10 // Example count, adjust as needed

struct UsbCcbHid {
    View* view;
    uint16_t selected_button;
    const char* hid_buttons[HID_BUTTON_COUNT];
};

typedef struct {
    bool left_pressed;
    bool up_pressed;
    bool right_pressed;
    bool down_pressed;
    bool ok_pressed;
    bool back_pressed;
    bool connected;
} UsbCcbHidModel;

static void usb_ccb_hid_draw_callback(Canvas* canvas, void* context) {
    furi_assert(context);
    UsbCcbHid* usb_ccb_hid = (UsbCcbHid*)context;
    const char* button_text;

    canvas_set_font(canvas, FontSecondary);
    canvas_clear(canvas);

    // Draw the list of HID buttons
    for (int i = 0; i < HID_BUTTON_COUNT; i++) {
        button_text = usb_ccb_hid->hid_buttons[i];
        if (i == usb_ccb_hid->selected_button) {
            canvas_draw_str(canvas, 0, i * 10, "> ");
        }
        canvas_draw_str(canvas, 20, i * 10, button_text);
    }
}

static bool usb_ccb_hid_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    UsbCcbHid* usb_ccb_hid = (UsbCcbHid*)context;
    bool consumed = false;

    if(event->type == InputTypeLong && event->key == InputKeyBack) {
        furi_hal_hid_kb_release_all();
    } else if(event->type == InputTypePress) {
        if(event->key == InputKeyDown) {
            usb_ccb_hid->selected_button = (usb_ccb_hid->selected_button + 1) % HID_BUTTON_COUNT;
            consumed = true;
        } else if(event->key == InputKeyUp) {
            usb_ccb_hid->selected_button = (usb_ccb_hid->selected_button - 1 + HID_BUTTON_COUNT) % HID_BUTTON_COUNT;
            consumed = true;
        } else if(event->key == InputKeyOk) {
            // Execute the selected HID button
            uint16_t command = usb_ccb_hid->selected_button; // Adjust if needed
            furi_hal_hid_consumer_key_press(command);
            furi_delay_us(2000); // Hold the key pressed
            furi_hal_hid_consumer_key_release(command);
            consumed = true;
        }
    }

    return consumed;
}

UsbCcbHid* usb_ccb_hid_alloc() {
    UsbCcbHid* usb_ccb_hid = malloc(sizeof(UsbCcbHid));
    usb_ccb_hid->view = view_alloc();
    view_set_context(usb_ccb_hid->view, usb_ccb_hid);
    view_allocate_model(usb_ccb_hid->view, ViewModelTypeLocking, sizeof(UsbCcbHidModel));
    view_set_draw_callback(usb_ccb_hid->view, usb_ccb_hid_draw_callback);
    view_set_input_callback(usb_ccb_hid->view, usb_ccb_hid_input_callback);

    // Initialize HID button names
    for (int i = 0; i < HID_BUTTON_COUNT; i++) {
        usb_ccb_hid->hid_buttons[i] = "Button"; // Replace with actual button names
    }
    usb_ccb_hid->selected_button = 0;

    return usb_ccb_hid;
}

void usb_ccb_hid_free(UsbCcbHid* usb_ccb_hid) {
    furi_assert(usb_ccb_hid);
    view_free(usb_ccb_hid->view);
    free(usb_ccb_hid);
}

View* usb_ccb_hid_get_view(UsbCcbHid* usb_ccb_hid) {
    furi_assert(usb_ccb_hid);
    return usb_ccb_hid->view;
}

void usb_ccb_hid_set_connected_status(UsbCcbHid* usb_ccb_hid, bool connected) {
    furi_assert(usb_ccb_hid);
    with_view_model(usb_ccb_hid->view, UsbCcbHidModel * model, { model->connected = connected; }, true);
}
