#include "stdafx.h"
#include "cMainGame.h"

#include "cLoadScene.h"
#include "cCustomGame.h"
#include "cTitle.h"
#include "cPuzzle.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	m_hDC = GetDC(m_hWnd);

	SetTimer(m_hWnd, 0, 1000, NULL);

	IMAGE->Init();

	//Init ���� Scene�� �߰������ش� ������� �̸�, Scene Ŭ����
	SCENE->AddScene("Load", new cLoadScene);
	SCENE->AddScene("Custom_BG", new cCustomGame);
	SCENE->AddScene("Title_BG", new cTitle);
	SCENE->AddScene("Puzzle_BG", new cPuzzle);
	
	//ó������ ������ ������ �ٲ۴�
	SCENE->ChangeScene("Load");
}

void cMainGame::Update()
{
	SCENE->Update();
	INPUT->Update();
	Count++;
}

void cMainGame::Render()
{
	HDC hdc = GetDC(m_hWnd);
	HDC m_MemDC;
	HBITMAP hBitmap;
	HBITMAP OldBitMap;

	RECT WindowRect;
	GetClientRect(m_hWnd, &WindowRect);

	m_MemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, WindowRect.right, WindowRect.bottom);
	OldBitMap = (HBITMAP)SelectObject(m_MemDC, hBitmap);


	IMAGE->InputHDC(m_MemDC);
	SCENE->Render();

	BitBlt(hdc, 0, 0, WindowRect.right, WindowRect.bottom, m_MemDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(m_MemDC, OldBitMap));
	DeleteDC(m_MemDC);

}

void cMainGame::Release()
{
	KillTimer(m_hWnd, 0);

	cImageManager::ResetInstance();
	cInputManager::ResetInstance();
	cSceneManager::ResetInstance();
}

void cMainGame::InputHDC(HDC hdc)
{
	m_hDC = hdc;
}

void cMainGame::InputHINSTANCE(HINSTANCE hinstance)
{
	m_hIns = hinstance;
}
