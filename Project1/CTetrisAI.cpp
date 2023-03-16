#include "CTetrisAI.h"
#include  <stdlib.h>


CTetrisAI::CTetrisAI()
{
}

CTetrisAI::~CTetrisAI()
{
}

void CTetrisAI::SetBlock(const CBlock cBlock)
{
	m_cBlock = cBlock;
}

void CTetrisAI::SetBackGround(const CBackGround cBackGround)
{
	m_cBackGround = cBackGround;
}

void CTetrisAI::SetBestPoint(const CBackGround cBackGround, const CBlock cBlock, size_t nRow, size_t nCol)
{
	SetBackGround(cBackGround);
	SetBlock(cBlock);

	m_nRow = nRow;
	m_nCol = nCol;

	//����Ѱ�����λ��
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t x = 0; x < COL - 2; x++)
		{
			for (size_t y = 4; y <= ROW - 1; y++)
			{
				if (IsBlockCanWrite(y, x) == false)
				{
					y--;
					if (IsBlockCanWrite(y, x) == false)
					{
						//����
						m_aryBlockRecord[i][x].m_nShapeIndex = i;
						m_aryBlockRecord[i][x].m_nY = y;
						m_aryBlockRecord[i][x].m_nX = x;
						m_aryBlockRecord[i][x].m_nPierreDellacherie = INT_MIN;
						m_aryBlockRecord[i][x].m_nPriority = Priority(i, x);

					}
					else
					{
						//���ݼ�¼
						m_cBackGround.WriteBlock2BackGround(m_cBlock, y, x, BLOCK_MOVE, BLOCK_MOVE);

						//����
						m_aryBlockRecord[i][x].m_nShapeIndex = i;
						m_aryBlockRecord[i][x].m_nY = y;
						m_aryBlockRecord[i][x].m_nX = x;
						m_aryBlockRecord[i][x].m_nLandingHeight = LandingHeight(y);
						m_aryBlockRecord[i][x].m_nErodedPieceCellsMetric = ErodedPieceCellsMetric(y, x);
						m_aryBlockRecord[i][x].m_nRowTransitions = RowTransitions();
						m_aryBlockRecord[i][x].m_nBoardColTransitions = BoardColTransitions();
						m_aryBlockRecord[i][x].m_nBoardBuriedHoles = BoardBuriedHoles();
						m_aryBlockRecord[i][x].m_nBoardWells = BoardWells();

						m_aryBlockRecord[i][x].m_nPierreDellacherie = m_aryBlockRecord[i][x].m_nLandingHeight + m_aryBlockRecord[i][x].m_nErodedPieceCellsMetric + m_aryBlockRecord[i][x].m_nRowTransitions + m_aryBlockRecord[i][x].m_nBoardColTransitions + m_aryBlockRecord[i][x].m_nBoardBuriedHoles + m_aryBlockRecord[i][x].m_nBoardWells;
						m_aryBlockRecord[i][x].m_nPriority = Priority(i, x);

						//���
						m_cBackGround.ClearBlock2BackGround(m_cBlock, y, x, BLOCK_MOVE);
					}

					break;
				}
			}
		}
		m_cBlock.RotateBlock();
	}

	//�Ա�ѡ����ѵ�
	Cmp2SetBest();
}

bool CTetrisAI::IsBlockCanWrite(size_t nRow, size_t nCol)
{
	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	//���ұߵ���һ������
	BLOCKDATE BlockDate = m_cBlock.GetCurrentBlock();

	for (size_t i = 0; i < BLOCK_ROW; i++)
	{
		for (size_t j = 0; j < BLOCK_COL; j++)
		{
			if (BlockDate[i][j] == BLOCK_MOVE && (BcakGround[i + nRow][j + nCol] == BLOCK_WAll || BcakGround[i + nRow][j + nCol] == BLOCK_FIXED))
			{
				return false;
			}
		}
	}
	return true;
}

//ѡ������Ž�
void CTetrisAI::Cmp2SetBest()
{
	//ͨ���Ա�ѡ�����ֵ��
	m_BlockPoint.m_nShapeIndex = m_aryBlockRecord[0][0].m_nShapeIndex;
	m_BlockPoint.m_nY = m_aryBlockRecord[0][0].m_nY;
	m_BlockPoint.m_nX = m_aryBlockRecord[0][0].m_nX;
	m_BlockPoint.m_nPierreDellacherie = m_aryBlockRecord[0][0].m_nPierreDellacherie;
	m_BlockPoint.m_nPriority = m_aryBlockRecord[0][0].m_nPriority;

	//��ֵ
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t x = 0; x < COL - 2; x++)
		{
			if (m_aryBlockRecord[i][x].m_nPierreDellacherie > m_BlockPoint.m_nPierreDellacherie
				|| (
					(m_aryBlockRecord[i][x].m_nPierreDellacherie == m_BlockPoint.m_nPierreDellacherie)
					&& (m_BlockPoint.m_nPriority > m_aryBlockRecord[i][x].m_nPriority)
					)
				)
			{
				m_BlockPoint.m_nShapeIndex = m_aryBlockRecord[i][x].m_nShapeIndex;
				m_BlockPoint.m_nY = m_aryBlockRecord[i][x].m_nY;
				m_BlockPoint.m_nX = m_aryBlockRecord[i][x].m_nX;
				m_BlockPoint.m_nPierreDellacherie = m_aryBlockRecord[i][x].m_nPierreDellacherie;
				m_BlockPoint.m_nPriority = m_aryBlockRecord[i][x].m_nPriority;
			}
		}
	}

}



size_t CTetrisAI::AIRotate()
{
	m_BlockPoint.m_nShapeIndex--;
	return 0;
}

size_t CTetrisAI::GetShapeIndex()
{
	return m_BlockPoint.m_nShapeIndex;
}

size_t CTetrisAI::GetPointX()
{
	return m_BlockPoint.m_nX;
}



int CTetrisAI::LandingHeight(size_t nRow)
{
	int nResult = LANDINGHEIGHT * (ROW - nRow - 1);
	return nResult;
}

//����   ����*����
int CTetrisAI::ErodedPieceCellsMetric(size_t nRow, size_t nCol)
{
	int nCellsMetric = 0;
	int nCellLine = 0;
	int nLineSum = 0;

	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	for (size_t y = nRow; y < nRow + 4 && y < ROW - 1; y++)
	{
		nLineSum = 0;
		for (size_t x = 1; x < COL - 1; x++)
		{
			if (BcakGround[y][x] == BLOCK_SPACE)
			{
				break;
			}
			else
			{
				nLineSum = nLineSum + 1;
			}
		}

		if (nLineSum == (COL - 2))
		{
			nCellLine++;
			for (size_t x = 0; x < COL - 1; x++)
			{
				if (BcakGround[y][x] == BLOCK_MOVE)
				{
					nCellsMetric++;
				}
			}
		}
	}

	int nResult = ROWSELIMINATED * nCellsMetric * nCellLine;

	return nResult;
}

//�б任
int CTetrisAI::RowTransitions()
{
	size_t nTmpY = 0;
	int nPreFalage = 1;
	int nCurFalage = 0;
	int nSum = 0;


	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	for (size_t y = 4; y < ROW - 1; y++)
	{
		for (size_t x = 1; x < COL - 1; x++)
		{
			if (BcakGround[y][x])
			{
				nTmpY = y;
				break;
			}
		}

		if (nTmpY)
		{
			break;
		}
	}

	//���㿪ʼ
	for (size_t y = nTmpY; y < ROW - 1; y++)
	{
		nPreFalage = 1;

		for (size_t x = 1; x <= COL - 1; x++)
		{
			/*if (BcakGround[y][x])
			{
				nCurFalage = 1;
			}
			else
			{
				nCurFalage = 0;
			}*/


			nCurFalage = (BcakGround[y][x] != BLOCK_SPACE) ? 1 : 0;

			if (nPreFalage != nCurFalage)
			{
				nSum++;
				nPreFalage = nCurFalage;
			}


		}

	}

	int nResult = ROWTRANSITIONS * nSum;
	return nResult;
}

//�б仯
int CTetrisAI::BoardColTransitions()
{
	int nPreFalage = 1;
	int nCurFalage = 0;
	int nSum = 0;

	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();

	for (size_t x = 1; x <= COL - 2; x++)
	{
		nPreFalage = 1;
		for (size_t y = 4; y <= ROW - 1; y++)
		{
			nCurFalage = (BcakGround[y][x] != BLOCK_SPACE) ? 1 : 0;

			if (nPreFalage != nCurFalage)
			{
				nSum++;
				nPreFalage = nCurFalage;
			}

		}
	}

	int nResult = COLUMNTRANSITIONS * nSum;
	return nResult;
}


//�ն�
int CTetrisAI::BoardBuriedHoles()
{
	int nSum = 0;

	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();
	for (size_t x = 1; x <= COL - 2; x++)
	{
		for (size_t y = 4; y <= ROW - 2; y++)
		{
			int nNextY = y + 1;
			if (BcakGround[y][x] != BLOCK_SPACE && BcakGround[nNextY][x] != BLOCK_SPACE)
			{
				nSum++;
				y = nNextY;
			}
		}
	}

	int nResult = NUMBEROFHOLES * nSum;
	return nResult;
}

int CTetrisAI::BoardWells()
{
	int nSum = 0;
	int nBlockSum = 0;
	//��ȡ��������
	BACKGROUND BcakGround = m_cBackGround.GetBackGround();
	for (size_t x = 1; x <= COL - 2; x++)
	{
		for (size_t y = 4; y < ROW - 1; y++)
		{
			int nPreX = x - 1;
			int nNextX = x + 1;
			if ((BcakGround[y][x] == BLOCK_SPACE) && (BcakGround[y][nPreX] != BLOCK_SPACE) && (BcakGround[y][nNextX] != BLOCK_SPACE))
			{
				nBlockSum++;
				nSum = nSum + nBlockSum;
			}
			else
			{
				nBlockSum = 0;
			}
		}
	}


	int nResult = WELLSUMS * nSum;
	return nResult;
}

int CTetrisAI::Priority(int nIndex, int nCol)
{
	int nTest = m_nCol;
	int nResult = 100 * abs(nTest - nCol) + nIndex;
	return nResult;
}
