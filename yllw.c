#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xrandr.h>

#include <cairo.h>
#include <cairo-xlib.h>

#include "config.h"

#define PARSE_DOUBLE_OPT(flag, value) \
	if (strcmp(argv[i], (flag)) == 0) { \
		(value) = strtod(argv[i + 1], NULL); \
		i++; \
		continue; \
	}

int main(int argc, char *argv[]) {
	for (unsigned i = 1; i < argc; i++) {
		PARSE_DOUBLE_OPT("-r", red)
		PARSE_DOUBLE_OPT("-g", green)
		PARSE_DOUBLE_OPT("-b", blue)
		PARSE_DOUBLE_OPT("-a", opacity)

		if (strcmp("-h", argv[i]) == 0) {
			printf("usage: %s [-r n] [-g n] [-b n] [-a n]\n", argv[0]);

			return 0;
		}
	}

	Display *disp = XOpenDisplay(NULL);
	int screen = DefaultScreen(disp);
	Window root = RootWindow(disp, screen);

	XSetWindowAttributes attrs;
	attrs.override_redirect = 1;

	XVisualInfo vinfo;
	if (!XMatchVisualInfo(disp, screen, 32, TrueColor, &vinfo)) {
		fprintf(stderr, "32 bit color not supported, exiting\n");

		return 1;
	}

	attrs.colormap = XCreateColormap(disp, root, vinfo.visual, AllocNone);
	attrs.background_pixel = 0;
	attrs.border_pixel = 0;

	int width = DisplayWidth(disp, screen);
	int height = DisplayHeight(disp, screen);

	Window overlay = XCreateWindow(
		disp,
		root,
		0, 0, width, height,
		0,
		vinfo.depth,
		InputOutput,
		vinfo.visual,
		CWOverrideRedirect | CWColormap | CWBackPixel | CWBorderPixel,
		&attrs
	);

	XMapWindow(disp, overlay);

	XRectangle rect;
	XserverRegion region = XFixesCreateRegion(disp, &rect, 1);
	XFixesSetWindowShapeRegion(disp, overlay, ShapeInput, 0, 0, region);
	XFixesDestroyRegion(disp, region);

	cairo_surface_t *surf = cairo_xlib_surface_create(
		disp, overlay, vinfo.visual, width, height
	);
	cairo_t *cr = cairo_create(surf);

	cairo_set_source_rgba(cr, red, green, blue, opacity);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);

	XFlush(disp);

	for (;;) {}

	cairo_destroy(cr);
	cairo_surface_destroy(surf);

	XUnmapWindow(disp, overlay);
	XCloseDisplay(disp);

	return 0;
}
