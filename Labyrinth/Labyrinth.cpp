#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "Menu.h"
#include "GraphicSettings.h"
#include "ProgramState.h"

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx10.lib" )

// Global Declarations
IDXGISwapChain *swapChain;							// Swap Chain Interface
ID3D11Device *dev;									// Direct3D Device Interface
ID3D11DeviceContext *devCon;						// Direct3D Device Context
ID3D11RenderTargetView *backBuffer;					// Back Buffer

// Function Prototypes
void InitD3D( HWND hWnd, GraphicSettings gSet );							// Initialize Direct3D
void RenderFrame( void );							// Render a Frame
void CleanD3D( void );								// Release Direct3D

// WindowProc Prototype
LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

// Entry Point
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow )
{
	ProgramState state = MENU;

	Menu menu;
	GraphicSettings gSet;

	// Initialize Graphical Settings
	gSet.retrieve();
	gSet.save();

	HWND hWnd;
	WNDCLASSEX wc;

	// Prepare Window Class for use
	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	// Construct Window Class
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );	
	wc.lpszClassName = "Game";
	if( !gSet.getFullScreen() )
	{
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	}

	// Register Window Class
	RegisterClassEx( &wc );

	// Get Client Area
	RECT wr = { 0, 0, gSet.getWidth(), gSet.getHeight() };
	AdjustWindowRect( &wr, WS_OVERLAPPEDWINDOW, FALSE );

	// Create Window, assign Handle
	hWnd = CreateWindowEx(	NULL,
							"Game",					// Name
							"Prototype",			// Title
							WS_OVERLAPPEDWINDOW,	// Style
							200,					// X Position
							100,					// Y Position
							wr.right - wr.left,		// Width
							wr.bottom - wr.top,		// Height
							NULL,					// Parent
							NULL,					// Menues
							hInstance,				// Handle
							NULL );

	// Display Window
	ShowWindow( hWnd, nCmdShow );
	
	// Initialize Direct3D
	InitD3D( hWnd, gSet );

	// Windows Event Messages
	MSG msg;

	// Game Loop
	while( TRUE )
	{
		// Handle Messages
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );

			// Break on Quit
			if( msg.message == WM_QUIT )
				break;
		}
		
		RenderFrame();
	}

	CleanD3D();

	return msg.wParam;
}

// Initialize and Prepare Direct3D for use
void InitD3D( HWND hWnd, GraphicSettings gSet )
{
	// Swap Chain Description
	DXGI_SWAP_CHAIN_DESC scd;

	// Prepare Swap Chain Description for use
	ZeroMemory( &scd, sizeof( DXGI_SWAP_CHAIN_DESC ) );

	// Construct Swap Chain Description
	scd.BufferCount = 1;									// Back Buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// Color Bit Depth
	scd.BufferDesc.Width = gSet.getWidth();
	scd.BufferDesc.Height = gSet.getHeight();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// Swap Chain usage
	scd.OutputWindow = hWnd;								// Window to use
	scd.SampleDesc.Count = 4;								// Multisampling
	scd.Windowed = gSet.getFullScreen() ? FALSE : TRUE;		// Screen Mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create Device, Device Context, and Swap Chain
	D3D11CreateDeviceAndSwapChain(	NULL,
									D3D_DRIVER_TYPE_HARDWARE,
									NULL,
									NULL,
									NULL,
									NULL,
									D3D11_SDK_VERSION,
									&scd,
									&swapChain,
									&dev,
									NULL,
									&devCon );

	// Get Back Buffer Address
	ID3D11Texture2D *pBackBuffer;
	swapChain -> GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );

	// Create Render Target
	dev -> CreateRenderTargetView( pBackBuffer, NULL, &backBuffer );
	pBackBuffer -> Release();

	// Set Render Target
	devCon -> OMSetRenderTargets( 1, &backBuffer, NULL );

	// Set Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( D3D11_VIEWPORT ) );

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = gSet.getHeight();
	viewport.Height = gSet.getWidth();

	devCon -> RSSetViewports( 1, &viewport );
}

// Render Frame
void RenderFrame( void )
{
	// Clear Back Buffer
	devCon -> ClearRenderTargetView( backBuffer, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );

	// Rendering
	// Determine Loop
	switch( state )
	{
	case MENU:
		// Main Menu Loop
		state = menu.loop();
		break;
	case GAME:
		// Game Loop
		break;
	case EXIT:
		// Exit Program
		break;
	default:
		MessageBox( hWnd, "An unachievable state has been achieved!", "Unexpected Error", MB_ICONERROR );
		exit( EXIT_FAILURE );
		break;
	}

	// Swap Back Buffer and Front Buffer
	swapChain -> Present( 0, 0 );
}

// Release Direct3D
void CleanD3D()
{
	// Ensure Windowed
	swapChain -> SetFullscreenState( FALSE, NULL );

	swapChain -> Release();
	backBuffer -> Release();
	dev -> Release();
	devCon -> Release();
}

// Message Handler
LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	// Sort and Run
	switch( message )
	{
		case WM_DESTROY:
		{
			// Exit Application
			PostQuitMessage( 0 );
			return 0;
		} break;
	}

	// Handle Others
	return DefWindowProc( hWnd, message, wParam, lParam );
}