#include "mainwindow.hpp"

#include <QApplication>
#include <LayerShellQt/shell.h>
#include <LayerShellQt/window.h>

int main(int argc, char *argv[])
{
	LayerShellQt::Shell::useLayerShell();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	QWindow *qw = w.windowHandle();
	assert(qw != nullptr);
	LayerShellQt::Window *layerShell = LayerShellQt::Window::get(qw);
	layerShell->setLayer(LayerShellQt::Window::LayerOverlay);
	layerShell->setAnchors(LayerShellQt::Window::AnchorBottom);
	layerShell->setKeyboardInteractivity(
		LayerShellQt::Window::KeyboardInteractivityNone);
	layerShell->setExclusiveZone(w.targetHeight);
	layerShell->setScope("ankkanen-panel");

	w.connect(qw, &QWindow::heightChanged, &w,
		  &MainWindow::onWindowHeightChanged);
	w.prepare();

	return a.exec();
}
