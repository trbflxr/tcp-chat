//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "configwindowcomponents.hpp"

ui::ConfigWindow *ui::ConfigWindow::windowPtr;

ui::ConfigWindow::ConfigWindow(Application *application, const std::wstring_view &title,
                               HINSTANCE app, unsigned width, unsigned height, int cmd) :
		Window(application, title) {

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = inputProcessor;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"ConfigWindowClass";
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hInstance = app;

	if (!RegisterClassExW(&wc)) throw std::runtime_error("Unable to register class");

	HWND parent = application->getMainWindow().getHwnd();

	RECT parentRect{};
	GetWindowRect(parent, &parentRect);

	hwnd = CreateWindowW(L"ConfigWindowClass", title.data(),
	                     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU ,
	                     parentRect.top, parentRect.left, width, height,
	                     parent, nullptr, app, nullptr);

	if (!hwnd) throw std::runtime_error("Unable to create window");

	setShowCommand(cmd);

	EnableWindow(application->getMainWindow().getHwnd(), FALSE);

	setupComponents();

	windowPtr = this;
}

ui::ConfigWindow::~ConfigWindow() { }

void ui::ConfigWindow::setupComponents() {
	components = new ConfigWindowComponents(application, hwnd);
}

LRESULT ui::ConfigWindow::inputProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:
			break;

		case WM_COMMAND:
			windowPtr->components->input(LOWORD(wParam));
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
//			BringWindowToTop(windowPtr->application->getMainWindow().getHwnd());
//			EnableWindow(windowPtr->application->getMainWindow().getHwnd(), TRUE);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
