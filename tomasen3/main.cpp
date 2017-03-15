#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "main.hpp"
#include "common.hpp"
#include "tomasen.hpp"



int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;



	if (!InitApp(hCurInst))
		return FALSE;
	if (!InitInstance(hCurInst, nCmdShow)) 
		return FALSE;



	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		} else {
			TranslateMessage(&msg);//メッセージを適切に変換
			DispatchMessage(&msg);//ウィンドウプロシージャにメッセージを送信
		}
	}
	return (int)msg.wParam;//プログラムを終了
}

//ウィンドウ・クラスの登録

ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//プロシージャ名
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//インスタンス
	/*wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);*/
	wc.hIcon = LoadIcon(hInst , TEXT("ICON1"));
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;	//メニュー名
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//ウィンドウの生成

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;
	DEVMODE    devMode;
	TCHAR      szAppName[] = TEXT("Tomasen2");
	/*スレッド用*/
	DWORD dwID;

	hWnd = CreateWindowEx(
		WS_EX_LEFT,//WS_EX_TOPMOST,//拡張ウィンドウクラス　最前面表示
		szClassName,//ウィンドウクラス名
		"Tomasen2", //タイトルバーにこの名前が表示される
		WS_VISIBLE | WS_POPUP, //ウィンドウの種類
		0,	//Ｘ座標
		0,	//Ｙ座標
		tm2::SCREEN_WIDTH,	//幅
		tm2::SCREEN_HEIGHT,	//高さ
		NULL, //親ウィンドウのハンドル、親を作るときはNULL
		NULL, //メニューハンドル、クラスメニューを使うときはNULL
		hInst, //インスタンスハンドル
		NULL);

	hWND = hWnd;//グローバル変数に保持
	if (!hWnd) return FALSE;

	devMode.dmSize       = sizeof(DEVMODE);
	devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
	devMode.dmPelsWidth  = tm2::SCREEN_WIDTH;
	devMode.dmPelsHeight = tm2::SCREEN_HEIGHT;
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);//ディスプレイの解像度の変更

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/*スレッドの作成*/
	if(CreateThread(NULL, 0, GameMain, NULL, 0, &dwID) == NULL)//3  (LPVOID)&param
	{
		MessageBox(
			NULL, TEXT("スレッドの作成に失敗しました"), TEXT("エラー"),
			MB_OK | MB_ICONWARNING
		);
	}

	return TRUE;
}

//ウィンドウプロシージャ

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static RECT rc;
	static HBRUSH hBrush;
	int clw = 0, clh = 0;				//ウィンドウサイズ

	switch (msg) {//自分の気になる情報のみ受け取る
		case WM_CREATE:
			SetTimer(hWnd, TIMER_ID1, TIME1, NULL);//タイマをセット
			ShowCursor(FALSE);//マウスカーソルを非表示
			break;
		case WM_TIMER:
			if(wp == TIMER_ID1) {//タイマ1
			}
			break;
		case WM_KEYDOWN:
			switch(wp){
				case VK_BACK:
					break;
				case VK_RETURN:
					break;
				case VK_TAB:
					break;
				case VK_ESCAPE:
					//PostQuitMessage(0);
					break;
				default:
					return DefWindowProc(hWnd, msg, wp, lp);
			}
			break;
		case WM_PAINT://描画処理
			/*GetClientRect(hWnd, &rc);
			clw = rc.right;//ウィンドウ幅の取得
			clh = rc.bottom;//ウィンドウ高の取得
			
			hdc = BeginPaint(hWnd, &ps);//デバイスコンテキストの取得
			
			sprintf(checktext, "a");
			SetTextColor(hdc, RGB(255,100,100));
			TextOut(hdc, 0, 0, checktext, strlen(checktext) );

			EndPaint(hWnd, &ps);//デバイスコンテキストの開放*/
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default://その他の処理はデフォルトどおりに任せる
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return (DefWindowProc(hWnd, msg, wp, lp));
}

DWORD WINAPI GameMain(LPVOID vdParam){
	HWND hWnd;

	//hWnd = ((ThreadParam *)vdParam)->owner;
	hWnd = hWND; //グローバル変数からウィンドウハンドルを受け取る
	if(hWnd == NULL)
	{
		MessageBox(
			NULL, TEXT("スレッドへのウィンドウハンドルの受け渡しに失敗に失敗"), TEXT("エラー"),
			MB_OK | MB_ICONWARNING
		);
	}

	/*ゲーム用クラスの生成*/
	tm2::Tomasen game;

	/*ゲーム用クラスの実行*/
	game.runGame(hWND);

	/*ゲーム終了メッセージの発行*/
	SendMessage(hWND, WM_CLOSE, 0, 0);
	return TRUE;
}