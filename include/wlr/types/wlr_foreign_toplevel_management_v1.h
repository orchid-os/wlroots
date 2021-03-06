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

#ifndef WLR_TYPES_WLR_FOREIGN_TOPLEVEL_MANAGEMENT_V1_H
#define WLR_TYPES_WLR_FOREIGN_TOPLEVEL_MANAGEMENT_V1_H

#include <wayland-server.h>
#include <wlr/types/wlr_output.h>

struct wlr_foreign_toplevel_manager_v1 {
	struct wl_event_loop *event_loop;
	struct wl_global *global;
	struct wl_list resources;
	struct wl_list toplevels; // wlr_foreign_toplevel_handle_v1::link

	struct wl_listener display_destroy;

	struct {
		struct wl_signal destroy;
	} events;

	void *data;
};

enum wlr_foreign_toplevel_handle_v1_state {
	WLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_MAXIMIZED = 1,
	WLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_MINIMIZED = 2,
	WLR_FOREIGN_TOPLEVEL_HANDLE_V1_STATE_ACTIVATED = 4,
};

struct wlr_foreign_toplevel_handle_v1_output {
	struct wl_list link; // wlr_foreign_toplevel_handle_v1::outputs
	struct wl_listener output_destroy;
	struct wlr_output *output;

	struct wlr_foreign_toplevel_handle_v1 *toplevel;
};

struct wlr_foreign_toplevel_handle_v1 {
	struct wlr_foreign_toplevel_manager_v1 *manager;
	struct wl_list resources;
	struct wl_list link;
	struct wl_event_source *idle_source;

	char *title;
	char *app_id;
	struct wl_list outputs; // wlr_foreign_toplevel_v1_output
	uint32_t state; // wlr_foreign_toplevel_v1_state

	struct {
		// wlr_foreign_toplevel_handle_v1_maximized_event
		struct wl_signal request_maximize;
		//wlr_foreign_toplevel_handle_v1_minimized_event
		struct wl_signal request_minimize;
		//wlr_foreign_toplevel_handle_v1_activated_event
		struct wl_signal request_activate;
		struct wl_signal request_close;

		//wlr_foreign_toplevel_handle_v1_set_rectangle_event
		struct wl_signal set_rectangle;
		struct wl_signal destroy;
	} events;

	void *data;
};

struct wlr_foreign_toplevel_handle_v1_maximized_event {
	struct wlr_foreign_toplevel_handle_v1 *toplevel;
	bool maximized;
};

struct wlr_foreign_toplevel_handle_v1_minimized_event {
	struct wlr_foreign_toplevel_handle_v1 *toplevel;
	bool minimized;
};

struct wlr_foreign_toplevel_handle_v1_activated_event {
	struct wlr_foreign_toplevel_handle_v1 *toplevel;
	struct wlr_seat *seat;
};

struct wlr_foreign_toplevel_handle_v1_set_rectangle_event {
	struct wlr_foreign_toplevel_handle_v1 *toplevel;
	struct wlr_surface *surface;
	int32_t x, y, width, height;
};

struct wlr_foreign_toplevel_manager_v1 *wlr_foreign_toplevel_manager_v1_create(
	struct wl_display *display);
void wlr_foreign_toplevel_manager_v1_destroy(
	struct wlr_foreign_toplevel_manager_v1 *manager);

struct wlr_foreign_toplevel_handle_v1 *wlr_foreign_toplevel_handle_v1_create(
	struct wlr_foreign_toplevel_manager_v1 *manager);
void wlr_foreign_toplevel_handle_v1_destroy(
	struct wlr_foreign_toplevel_handle_v1 *toplevel);

void wlr_foreign_toplevel_handle_v1_set_title(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, const char *title);
void wlr_foreign_toplevel_handle_v1_set_app_id(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, const char *app_id);

void wlr_foreign_toplevel_handle_v1_output_enter(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, struct wlr_output *output);
void wlr_foreign_toplevel_handle_v1_output_leave(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, struct wlr_output *output);

void wlr_foreign_toplevel_handle_v1_set_maximized(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, bool maximized);
void wlr_foreign_toplevel_handle_v1_set_minimized(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, bool minimized);
void wlr_foreign_toplevel_handle_v1_set_activated(
	struct wlr_foreign_toplevel_handle_v1 *toplevel, bool activated);

#endif

#ifdef __cplusplus
}
#endif
