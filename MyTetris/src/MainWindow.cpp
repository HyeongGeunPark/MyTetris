#include "MainWindow.h" 


// post-construct init
bool MainWindow::Init(WNDPROC WndProc) {
	// define main window
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = appName;
	wc.hInstance = hInstance;
	// TODO: Is CS_OWNDC neccesary for efficienty?
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// NOTE: Maybe Background is not neccesary...
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// no menu, no extra memory 

	// register window
	if (!RegisterClass(&wc)) {
		// fail
		OutputDebugString(L"MainWindow: wndclass register fail");
		return false;
	}

	// window create 
	hwnd = CreateWindow(
		appName,
		windowName,
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,	// window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// initial position
		//CW_USEDEFAULT, CW_USEDEFAULT,	// use default size now. updated later
		500,500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd) {
		OutputDebugString(L"MainWindow: CreateWindow failed");
		return false;
	}

	return true;
}

// pre-destruct deinit
bool MainWindow::DeInit() {
	UnregisterClass(appName, hInstance);
	return true;
}


