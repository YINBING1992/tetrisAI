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
	//初始化
	void InitGame();
	//显示
	void ShowGame(HDC hdc);

	//显示背景
	void DrawALlBack(HDC hdc);
	//显示大背景下的图形
	void DrawMaxLeft(HDC hdc); 
	//显示小背景下的图形
	void DrawMinRight(HDC hdc);

	//操作小方块
	// 旋转 rotate
	void BlockRotate();
	// 下
	int BlockDown();
	// 左
	void BlockLeft();
	// 右
	void BlockRight();


	int BlockRoateAndMove(int* pRotate, int* pMove);
private:
	//是否可以移动
	bool IsCanMove();
	//结束
	bool IsGameOver();

	CTetrisAI m_cAI;
	CBlock m_cBlock;
	CBackGround m_cBackGround;

	size_t m_nRow;	//小方块的行
	size_t m_nCol;	//小方块的列

	int m_nScore = 0;
};

