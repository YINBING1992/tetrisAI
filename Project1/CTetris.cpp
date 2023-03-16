#include "CTetris.h"

CTetris::CTetris()
{

}

CTetris::~CTetris()
{

}

void CTetris::InitGame()
{
	//��ʼ��С����
	m_cBlock.RandCreateBlock();
	m_cBlock.RandCreateBlock();

	//��ʼ������
	m_cBackGround.InitBackGround();

	m_nRow = 0;
	m_nCol = COL / 2 - 2;

	//Ai����
	m_cAI.SetBestPoint(m_cBackGround, m_cBlock, m_nRow, m_nCol);

	//��С����д����ı�����
	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

}

//��ʾ
void CTetris::ShowGame(HDC hdc)
{
	//��ʾ����
	DrawALlBack(hdc);
	//��ʾ�󱳾��µ�ͼ��
	DrawMaxLeft(hdc);
	//��ʾС�����µ�ͼ��
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

//���󱳾��µ�С����͹̶�����

void CTetris::DrawMaxLeft(HDC hdc)
{
	HGDIOBJ hPenBlaCk = GetStockObject(BLACK_PEN);
	HGDIOBJ hBrushWhite = GetStockObject(WHITE_BRUSH);

	SelectObject(hdc, hPenBlaCk);
	SelectObject(hdc, hBrushWhite);


	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();
	for (size_t y = 0; y < ROW; y++)
	{
		for (size_t x = 0; x < COL; x++)
		{
			if (BcakGround[y][x] != BLOCK_SPACE && BcakGround[y][x] != BLOCK_WAll)
			{
				//��ÿһ��С����
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


	//���ұߵ���һ������
	BLOCKDATE BlockDate = m_cBlock.GetNextBlock();

	for (size_t y = 0; y < BLOCK_ROW; y++)
	{
		for (size_t x = 0; x < BLOCK_COL; x++)
		{
			if (BlockDate[y][x] == BLOCK_MOVE)
			{
				//��ÿһ��С����
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
	//�жϿɲ�����  Rotate
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

	//�жϿɲ������ƶ�
	if (!IsCanMove())
	{
		m_nRow--;
		m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_FIXED);

		//���� 0-4
		m_cBackGround.RemoveRows();

		//��û�н���
		if (IsGameOver())
		{
			return -1;
		}
		m_cBlock.RandCreateBlock();

		m_nRow = 0;
		m_nCol = COL / 2 - 2;

		//Ai����
		m_cAI.SetBestPoint(m_cBackGround, m_cBlock, m_nRow, m_nCol);

	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

	return 0;
}

void CTetris::BlockLeft()
{
	m_cBackGround.ClearBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE);
	m_nCol--;
	//�жϿɲ������ƶ�
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
	//�жϿɲ������ƶ�
	if (!IsCanMove())
	{
		m_nCol--;

	}

	m_cBackGround.WriteBlock2BackGround(m_cBlock, m_nRow, m_nCol, BLOCK_MOVE, BLOCK_MOVE);

}

int CTetris::BlockRoateAndMove(int* pRotate, int* pMove)
{
	//��ȡ��״���±�
	if (m_cAI.GetShapeIndex())
	{
		*pRotate = 1;
		m_cAI.AIRotate();  //û����һ�μ�ȥһ��
	}
	else
	{
		*pRotate = 0;
	}

	//��ȡͼ�ε�λ��
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
	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	//���ұߵ���һ������
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
	//��ȡ��������
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

