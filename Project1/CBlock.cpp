#include "CBlock.h"
#include <memory.h>
#include <time.h>
#include <stdlib.h>

static char g_uchBlocks[][4] = {
	/*
		����  ��������  ��   ������   ����
		����       ������    ��     ����
	 */
	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	//��������
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	//   �� 
	//  ������
	0, 1, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	//   ���� 
	//    ����
	1, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	//   ���� 
	//   ����
	0, 1, 1, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,

	0, 1, 1, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,

	//   F
	1, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,

	//   fan F
	0, 0, 1, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,
	1, 1, 1, 0,
	1, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

};

CBlock::CBlock()
{
	RandCreateBlock();
	RandCreateBlock();
}

CBlock::CBlock(const CBlock& Block)
{
	*this = Block;
}

CBlock::~CBlock()
{

}

CBlock& CBlock::operator=(const CBlock& Block)
{
	// ��ǰͼ�θ�ֵ
	m_nCurrentType = Block.m_nCurrentType;
	m_nCurrentShape = Block.m_nCurrentShape;
	memcpy(m_aryBlock, Block.m_aryBlock, sizeof(m_aryBlock));

	//��һ��ͼ�θ���
	m_nNextType = Block.m_nNextType;
	m_nNextShape = Block.m_nNextShape;
	memcpy(m_aryNextBlock, Block.m_aryNextBlock, sizeof(m_aryNextBlock));
	return *this;
}

//�����������
void CBlock::RandCreateBlock()
{
	m_nCurrentType = m_nNextType;
	m_nCurrentShape = m_nNextShape;
	memcpy(m_aryBlock, m_aryNextBlock, sizeof(m_aryBlock));

	//�������һ��
	m_nNextType = rand() % (sizeof(g_uchBlocks) / (BLOCK_COL * BLOCK_ROW * BLOCK_SHAPE_COUNT));
	m_nNextShape = rand() % BLOCK_SHAPE_COUNT;
	memcpy(m_aryNextBlock, g_uchBlocks + m_nNextType * (BLOCK_COL * BLOCK_ROW * BLOCK_SHAPE_COUNT) + m_nNextShape * (BLOCK_COL * BLOCK_ROW), sizeof(m_aryNextBlock));
}

void CBlock::RotateBlock()
{
	m_nCurrentShape = (m_nCurrentShape + 1) % 4;
	memcpy(m_aryBlock, g_uchBlocks + m_nCurrentType * (BLOCK_COL * BLOCK_ROW * BLOCK_SHAPE_COUNT) + m_nCurrentShape * (BLOCK_COL * BLOCK_ROW), sizeof(m_aryBlock));
}

void CBlock::SetType(size_t nType)
{
	m_nCurrentType = nType;
	memcpy(m_aryBlock, g_uchBlocks + m_nCurrentType * (BLOCK_COL * BLOCK_ROW * BLOCK_SHAPE_COUNT) + m_nCurrentShape * (BLOCK_COL * BLOCK_ROW), sizeof(m_aryBlock));
}

void CBlock::SetShape(size_t nShape)
{
	m_nCurrentShape = nShape;
	memcpy(m_aryBlock, g_uchBlocks + m_nCurrentType * (BLOCK_COL * BLOCK_ROW * BLOCK_SHAPE_COUNT) + m_nCurrentShape * (BLOCK_COL * BLOCK_ROW), sizeof(m_aryBlock));
}

size_t CBlock::GetType(size_t nType)
{
	return m_nCurrentType;
}

size_t CBlock::GetShape(size_t nShape)
{
	return m_nCurrentShape;
}

const BLOCKDATE CBlock::GetCurrentBlock() const
{
	return BLOCKDATE(m_aryBlock);
}

const BLOCKDATE CBlock::GetNextBlock() const
{
	return BLOCKDATE(m_aryNextBlock);
}
