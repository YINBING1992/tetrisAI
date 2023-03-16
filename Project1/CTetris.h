#pragma once
#include "CBlock.h"
#include "CBackGround.h"
#include "CTetrisAI.h"

#include <wtypes.h>

class CTetris
{
public:
	CTetris();
	~CTetris();
public:
	//��ʼ��
	void InitGame();
	//��ʾ
	void ShowGame(HDC hdc);

	//��ʾ����
	void DrawALlBack(HDC hdc);
	//��ʾ�󱳾��µ�ͼ��
	void DrawMaxLeft(HDC hdc); 
	//��ʾС�����µ�ͼ��
	void DrawMinRight(HDC hdc);

	//����С����
	// ��ת rotate
	void BlockRotate();
	// ��
	int BlockDown();
	// ��
	void BlockLeft();
	// ��
	void BlockRight();


	int BlockRoateAndMove(int* pRotate, int* pMove);
private:
	//�Ƿ�����ƶ�
	bool IsCanMove();
	//����
	bool IsGameOver();

	CTetrisAI m_cAI;
	CBlock m_cBlock;
	CBackGround m_cBackGround;

	size_t m_nRow;	//С�������
	size_t m_nCol;	//С�������

	int m_nScore = 0;
};

