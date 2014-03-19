TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -pthread -I/usr/include/gtkmm-3.0 -I/usr/lib64/gtkmm-3.0/include \
	-I/usr/include/atkmm-1.6 -I/usr/include/gtk-3.0/unix-print \
	-I/usr/include/gdkmm-3.0 -I/usr/lib64/gdkmm-3.0/include \
	-I/usr/include/giomm-2.4 -I/usr/lib64/giomm-2.4/include \
	-I/usr/include/pangomm-1.4 -I/usr/lib64/pangomm-1.4/include \
	-I/usr/include/glibmm-2.4 -I/usr/lib64/glibmm-2.4/include \
	-I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gtk-3.0 \
	-I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz \
	-I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/cairomm-1.0 \
	-I/usr/lib64/cairomm-1.0/include -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 \
	-I/usr/include/libdrm -I/usr/include/libpng16 -I/usr/include/sigc++-2.0 -I/usr/lib64/sigc++-2.0/include \
	-I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include \
	`pkg-config --cflags ImageMagick++`
QMAKE_LIBS += -lGLEW -lglfw -lGL -lPocoXML -lPocoFoundation `pkg-config --libs ImageMagick++ gtkmm-3.0`

SOURCES += \
	hge-application.cpp \
	hge-base-actor.cpp \
	hge-camera-matrix.cpp \
	hge-collada-importer.cpp \
	hge-geometry-unit.cpp \
	hge-main.cpp \
	hge-math.cpp \
	hge-mesh-unit.cpp \
	hge-model-matrix.cpp \
	hge-perspective-matrix.cpp \
	hge-scene-unit.cpp \
	hge-shader-engine.cpp \
	hge-shader-unit.cpp \
	hge-sun-shader.cpp \
	hge-terrain-sun-shader.cpp \
	hge-terrain-unit.cpp \
	hge-texture-unit.cpp \
	hge-texture-util.cpp \
	hge-total-shader.cpp \
	hge-vertex-data.cpp \
	hge-white-shader.cpp \
	hge-main-window.cpp \
	hge-opengl-render-widget.cpp \
	hge-mesh-tab.cpp \
	hge-menubar.cpp \
	hge-toolbar.cpp \
	hge-statusbar.cpp \
	hge-side-window.cpp \
	hge-terrain-window.cpp

OTHER_FILES += \
	game-loop.txt \
	object-importing-notes.txt \
	project-decisions.txt \
	hge-terrain-shader-string.vert \
	hge-terrain-shader-string.frag \
    terrain-constraints.txt \
    hge-terrain-shader-string.geometryShader \
    hge-terrain-shader-string.fragmentShader \
    hge-terrain-shader-string.vertexShader \
    TODO.txt

HEADERS += \
	hge-application.hpp \
	hge-base-actor.hpp \
	hge-camera-matrix.hpp \
	hge-collada-importer.hpp \
	hge-geometry-unit.hpp \
	hge-main.hpp \
	hge-math.hpp \
	hge-mesh-unit.hpp \
	hge-model-matrix.hpp \
	hge-perspective-matrix.hpp \
	hge-scene-unit.hpp \
	hge-shader-engine.hpp \
	hge-shader-unit.hpp \
	hge-sun-shader.hpp \
	hge-terrain-sun-shader.hpp \
	hge-terrain-unit.hpp \
	hge-texture-unit.hpp \
	hge-texture-util.hpp \
	hge-total-shader.hpp \
	hge-vertex-data.hpp \
	hge-white-shader.hpp \
	hge-main-window.hpp \
	hge-opengl-render-widget.hpp \
	hge-mesh-tab.hpp \
	hge-menubar.hpp \
	hge-toolbar.hpp \
	hge-statusbar.hpp \
	hge-side-window.hpp \
	hge-terrain-window.hpp

