#ifdef __cplusplus
extern "C" {
#endif

/*
 * This an unstable interface of wlroots. No guarantees are made regarding the
 * future consistency of this API.
 */
#ifndef WLR_USE_UNSTABLE
#error "Add -DWLR_USE_UNSTABLE to enable unstable wlroots features"
#endif

#ifndef WLR_TYPES_WLR_INPUT_DEVICE_H
#define WLR_TYPES_WLR_INPUT_DEVICE_H

enum wlr_button_state {
	WLR_BUTTON_RELEASED,
	WLR_BUTTON_PRESSED,
};

enum wlr_input_device_type {
	WLR_INPUT_DEVICE_KEYBOARD,
	WLR_INPUT_DEVICE_POINTER,
	WLR_INPUT_DEVICE_TOUCH,
	WLR_INPUT_DEVICE_TABLET_TOOL,
	WLR_INPUT_DEVICE_TABLET_PAD,
	WLR_INPUT_DEVICE_SWITCH,
};

/* Note: these are circular dependencies */
#include <wlr/types/wlr_keyboard.h>
#include <wlr/types/wlr_pointer.h>
#include <wlr/types/wlr_touch.h>
#include <wlr/types/wlr_tablet_tool.h>
#include <wlr/types/wlr_tablet_pad.h>
#include <wlr/types/wlr_switch.h>

struct wlr_input_device_impl;

struct wlr_input_device {
	const struct wlr_input_device_impl *impl;

	enum wlr_input_device_type type;
	unsigned int vendor, product;
	char *name;
	// Or 0 if not applicable to this device
	double width_mm, height_mm;
	char *output_name;

	/* wlr_input_device.type determines which of these is valid */
	union {
		void *_device;
		struct wlr_keyboard *keyboard;
		struct wlr_pointer *pointer;
		struct wlr_switch *lid_switch;
		struct wlr_touch *touch;
		struct wlr_tablet *tablet;
		struct wlr_tablet_pad *tablet_pad;
	};

	struct {
		struct wl_signal destroy;
	} events;

	void *data;

	struct wl_list link;
};

#endif

#ifdef __cplusplus
}
#endif
