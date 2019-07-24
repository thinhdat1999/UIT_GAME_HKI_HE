#include "Game.h"


Game *Game::_instance = NULL;


Game::Game()
{
	gSceneManager = SceneManager::GetInstance();
	gTextureManager = TextureManager::GetInstance();
	gSpriteManager = SpriteManager::GetInstance();
}


void Game::GameInit(HINSTANCE hInstance, int cmdShow)
{
	// Tạo Window
	//WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WIN_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	//WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
	hWnd = CreateWindow(
		WIN_NAME,
		WIN_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT + 32,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);

	// Tạo thiết bị D3D
	auto d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// Lấy thông tin khung Windows để tạo Back Buffer
	RECT r;
	GetClientRect(hWnd, &r);
	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	// Tạo Device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	// Lấy BackBuffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Tạo Sprite Handler
	D3DXCreateSprite(d3ddev, &spriteHandler);

	DirectInput8Create((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di8, NULL);

	di8->CreateDevice(GUID_SysKeyboard, &didv8, NULL);
	didv8->SetDataFormat(&c_dfDIKeyboard);
	didv8->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipwd;
	dipwd.diph.dwSize = sizeof(DIPROPDWORD);
	dipwd.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipwd.diph.dwObj = 0;
	dipwd.diph.dwHow = DIPH_DEVICE;
	dipwd.dwData = 1024;

	didv8->SetProperty(DIPROP_BUFFERSIZE, &dipwd.diph);
	didv8->Acquire();

}

void Game::GameRun()
{
	MSG msg;
	auto frameStart = GetTickCount();
	auto tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (isGameRunning)
	{
		// Nếu là thông điệp thoát thì thoát
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isGameRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Vòng lặp game chính (cập nhật thời gian, thông số và Render lại Frame hình)
		auto now = GetTickCount();
		float dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
		{
			Sleep(tickPerFrame - dt);
		}
	}
}

void Game::Update(float dt)
{
	gSceneManager->GetCurScene()->Update(dt);
}

void Game::Render()
{
	auto scene = gSceneManager->GetCurScene();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackColor(), 0.0f, 0);

	if (d3ddev->BeginScene())
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		scene->Render();
		spriteHandler->End();
		d3ddev->EndScene();
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Game::GameStartUp()
{
	gTextureManager->StartUp();
	gSpriteManager->StartUp();
	gSceneManager->ReplaceScene(new PlayScene());
	CurScene = gSceneManager->GetInstance()->GetCurScene();
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		isGameRunning = false;
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_KEYDOWN:
		SceneManager::GetInstance()->GetCurScene()->OnKeyDown(wParam);
		break;

	case WM_KEYUP:

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Game::ProcessKeyboard()
{// Kiểm tra trạng thái của các phím đã sẵn sàng chưa
	auto hr = didv8->GetDeviceState(sizeof(keyStates), keyStates);

	if (FAILED(hr))
	{
		// Nếu chưa thì thử kiểm tra lại
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			auto hr = didv8->Acquire();
			if (hr != DI_OK)
				return;
		}
		else
		{
			return;
		}
	}

	// Kiểm tra các sự kiện của keyboard
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv8->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	// Scan các sự kiện, xem có phím nào được nhấn hay thả hay không
	for (DWORD i = 0; i < dwElements; ++i)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			CurScene->OnKeyDown(KeyCode);
		else CurScene->OnKeyUp(KeyCode);
	}
}

Game *Game::GetInstance()
{
	if (_instance == NULL) _instance = new Game();
	return _instance;
}