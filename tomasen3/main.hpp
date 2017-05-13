#ifndef INCLUDED_MAIN_HPP
#define INCLUDED_MAIN_HPP


#define TIMER_ID1 1					//1/60秒タイマー
#define TIME1 1000/60				//描画速度s

char checktext[256] = "test!";		//文字列チェック用
HWND hWND;							//ウィンドウハンドル

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
DWORD WINAPI GameMain(LPVOID);//スレッド用関数のプロトタイプ宣言

char szClassName[] = "main";	//ウィンドウクラス


#endif//INCLUDED_MAIN_HPP