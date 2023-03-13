#include "CBackGround.h"
#include <memory.h>
CBackGround::CBackGround()
{
    
}

CBackGround::CBackGround(const CBackGround& BackGround)
{
    *this = BackGround;
}

CBackGround::~CBackGround()
{

}

CBackGround& CBackGround::operator=(const CBackGround& BackGround)
{
    // TODO: 在此处插入 return 语句
    memcpy(m_uchBackGround, BackGround.m_uchBackGround, sizeof(m_uchBackGround));
    m_uScore = BackGround.m_uScore;
    
    return *this;
}

void CBackGround::InitBackGround()
{
    for (size_t y = 0; y < ROW; y++)
    {
        for (size_t x = 0; x < COL; x++)
        {
            if (y == ROW - 1 || x == 0 || x == COL - 1)
            {
                m_uchBackGround[y][x] = BLOCK_WAll;
            }
            else
            {
                m_uchBackGround[y][x] = BLOCK_SPACE;
            }
        }
    }
}

void CBackGround::WriteBlock2BackGround(const CBlock& Block, size_t nRow, size_t nCol, unsigned char chCurType, unsigned char chNextType)
{
    BLOCKDATE BlockDate = Block.GetCurrentBlock();

    for (size_t y = 0; y < BLOCK_ROW; y++)
    {
        for (size_t x = 0; x < BLOCK_COL; x++)
        {
            if (BlockDate[y][x] == chCurType) //BLCOK_MOVE   ==>    1
            {
                m_uchBackGround[y + nRow][x + nCol] = chNextType; //BLCOK_MOVE   ==>    1    BLOCK_FIXED   4
            }

        }
    }

}

void CBackGround::ClearBlock2BackGround(const CBlock& Block, size_t nRow, size_t nCol, unsigned char chCurType)
{
    BLOCKDATE BlockDate = Block.GetCurrentBlock();

    for (size_t y = 0; y < BLOCK_ROW; y++)
    {
        for (size_t x = 0; x < BLOCK_COL; x++)
        {
            if (BlockDate[y][x] == chCurType) //BLCOK_MOVE   ==>    1
            {
                m_uchBackGround[y + nRow][x + nCol] = BLOCK_SPACE; //BLCOK_MOVE   ==>    1    BLOCK_FIXED   4
            }

        }
    }
}

const BACKGROUND CBackGround::GetBackGround() const
{
    return BACKGROUND(m_uchBackGround);
}

size_t CBackGround::RemoveRows()
{
    size_t nCount = 0;

    for (size_t y = ROW - 2; y > 3; y--)
    {
        if (IsRemoveRow(y))
        {
            RemoveRow(y);
            nCount++;
            y++;
        }
    }
    m_uScore = m_uScore + nCount;
    return nCount;
}

//判断能否消除这一行
bool CBackGround::IsRemoveRow(int nRow)
{
    for (size_t x = 1; x < COL -1; x++)
    {
        if (m_uchBackGround[nRow][x] == BLOCK_SPACE)
        {
            return false;
        }
    }
    return true;
}

void CBackGround::RemoveRow(int nRow)
{
    for (size_t y = nRow; y > 3; y--)
    {
        memcpy(&m_uchBackGround[y][0], &m_uchBackGround[y - 1][0], COL);
    }
}

size_t CBackGround::GetScore()
{
    return m_uScore;
}
