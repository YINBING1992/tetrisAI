#include "CTetris.h"

CTetris::CTetris()
{

}

CTetris::~CTetris()
{

}

void CTetris::InitGame()
{
	//初始化小方块
	m_cBlock.RandCreateBlock();
	m_cBlock.RandCreateBlock();

	//初始化背景
	m_cBackGround.InitBackGround();

	m_nRow = 0;
	m_nCol = COL / 2 - 2;

	//Ai计算
	m_cAI.SetBestPoint(m_cBackGround, m_cBlock, m_nRow, m_nCol);

	//把小方块写进大的背景中
	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

}

//显示
void CTetris::ShowGame(HDC hdc)
{
	//显示背景
	DrawALlBack(hdc);
	//显示大背景下的图形
	DrawMaxLeft(hdc);
	//显示小背景下的图形
	DrawMinRight(hdc);
}

void CTetris::DrawALlBack(HDC hdc)
{
	//COL* WIDTH, ROW* HEIGHT
	HGDIOBJ hPenNull = GetStockObject(NULL_PEN);
	HGDIOBJ hBrushGray = GetStockObject(GRAY_BRUSH);

	SelectObject(hdc, hPenNull);
	SelectObject(hdc, hBrushGray);

	//Rectangle(hdc, 0, 0, COL * WIDTH, ROW * HEIGHT);

	Rectangle(hdc, WIDTH, WIDTH * 4, (COL - 1) * WIDTH, ROW * HEIGHT);
	//Rectangle(hdc, 0, 0, COL * WIDTH, ROW * HEIGHT);

	Rectangle(hdc, (COL + 1) * WIDTH, WIDTH * 4, (COL + 9) * WIDTH, ROW * HEIGHT);

	DeleteObject(hBrushGray);
	DeleteObject(hPenNull);

}

//画大背景下的小方块和固定方块

void CTetris::DrawMaxLeft(HDC hdc)
{
	HGDIOBJ hPenBlaCk = GetStockObject(BLACK_PEN);
	HGDIOBJ hBrushWhite = GetStockObject(WHITE_BRUSH);

	SelectObject(hdc, hPenBlaCk);
	SelectObject(hdc, hBrushWhite);


	//获取背景数据
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();
	for (size_t y = 0; y < ROW; y++)
	{
		for (size_t x = 0; x < COL; x++)
		{
			if (BcakGround[y][x] != BLOCK_SPACE && BcakGround[y][x] != BLOCK_WAll)
			{
				//画每一个小方块
				Rectangle(hdc, x * WIDTH, y * HEIGHT, x * WIDTH + WIDTH, y * HEIGHT + HEIGHT);
			}
		}
	}


	DeleteObject(hBrushWhite);
	DeleteObject(hPenBlaCk);
}

void CTetris::DrawMinRight(HDC hdc)
{
	HGDIOBJ hPenBlaCk = GetStockObject(BLACK_PEN);
	HGDIOBJ hBrushWhite = GetStockObject(WHITE_BRUSH);

	SelectObject(hdc, hPenBlaCk);
	SelectObject(hdc, hBrushWhite);


	//画右边的下一个方块
	BLOCKDATE BlockDate = m_cBlock.GetNextBlock();

	for (size_t y = 0; y < BLOCK_ROW; y++)
	{
		for (size_t x = 0; x < BLOCK_COL; x++)
		{
			if (BlockDate[y][x] == BLOCK_MOVE)
			{
				//画每一个小方块
				Rectangle(hdc, (COL + 3 + x) * WIDTH, (y + 6) * HEIGHT, (COL + 3 + x) * WIDTH + WIDTH, (y + 6) * HEIGHT + HEIGHT);
			}
		}
	}


	DeleteObject(hBrushWhite);
	DeleteObject(hPenBlaCk);
}

void CTetris::BlockRotate()
{
	m_cBackGround.ClearBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE);

	//record
	size_t nIndex = m_cBlock.GetShape();

	m_cBlock.RotateBlock();
	//判断可不可以  Rotate
	if (!IsCanMove())
	{
		m_cBlock.SetShape(nIndex);
	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

}

int CTetris::BlockDown()
{
	m_cBackGround.ClearBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE);
	m_nRow++;

	//判断可不可以移动
	if (!IsCanMove())
	{
		m_nRow--;
		m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_FIXED);

		//消行 0-4
		m_cBackGround.RemoveRows();

		//有没有结束
		if (IsGameOver())
		{
			return -1;
		}
		m_cBlock.RandCreateBlock();

		m_nRow = 0;
		m_nCol = COL / 2 - 2;

		//Ai计算
		m_cAI.SetBestPoint(m_cBackGround, m_cBlock, m_nRow, m_nCol);

	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

	return 0;
}

void CTetris::BlockLeft()
{
	m_cBackGround.ClearBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE);
	m_nCol--;
	//判断可不可以移动
	if (!IsCanMove())
	{
		m_nCol++;

	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);
}

void CTetris::BlockRight()
{
	m_cBackGround.ClearBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE);
	m_nCol++;
	//判断可不可以移动
	if (!IsCanMove())
	{
		m_nCol--;

	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

}

int CTetris::BlockRoateAndMove(int* pRotate, int* pMove)
{
	//获取形状的下标
	if (m_cAI.GetShapeIndex())
	{
		*pRotate = 1;
		m_cAI.AIRotate();  //没调用一次减去一个
	}
	else
	{
		*pRotate = 0;
	}

	//获取图形的位置
	if (m_cAI.GetPointX() < m_nCol)
	{
		*pMove = -1;
	}
	else if (m_cAI.GetPointX() > m_nCol)
	{
		*pMove = 1;
	}
	else
	{
		*pMove = 0;
	}

	return 0;
}


bool CTetris::IsCanMove()
{
	//获取背景数据
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	//画右边的下一个方块
	BLOCKDATE BlockDate = m_cBlock.GetCurrentBlock();

	for (size_t y = 0; y < BLOCK_ROW; y++)
	{
		for (size_t x = 0; x < BLOCK_COL; x++)
		{
			if (BlockDate[y][x] == BLOCK_MOVE && (BcakGround[y + m_nRow][x + m_nCol] == BLOCK_WAll || BcakGround[y + m_nRow][x + m_nCol] == BLOCK_FIXED))
			{
				return false;
			}
		}
	}
	return true;
}

bool CTetris::IsGameOver()
{
	//获取背景数据
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	for (size_t x = 1; x < COL - 1; x++)
	{
		if (BcakGround[3][x] == BLOCK_FIXED)
		{
			return true;
		}
	}

	return false;
}

