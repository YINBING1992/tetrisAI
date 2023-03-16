#pragma once
#define BLOCK_COL	4
#define BLOCK_ROW	4

#define ROW     25   
#define COL     12

#define WIDTH	20
#define HEIGHT	20

#define BLOCK_SHAPE_COUNT	4

#define BLOCK_SPACE		0
#define BLOCK_MOVE		1
#define BLOCK_WAll		2
#define BLOCK_FIXED		3


typedef unsigned char(*BLOCKDATE)[BLOCK_COL];

class CBlock
{
public:
	CBlock();
	CBlock(const CBlock& Block);
	~CBlock();
	CBlock& operator=(const CBlock& Block);

	//��������
	void RandCreateBlock();
	//��ת����
	void RotateBlock();
	//��������
	void SetType(size_t nType);
	//����shape
	void SetShape(size_t nShape);
	//��ȡ����
	size_t GetType();
	//��ȡshape
	size_t GetShape();
	

	const BLOCKDATE GetCurrentBlock()const; //��ǰͼ��
	const BLOCKDATE GetNextBlock()const;	//��һ��ͼ��

private:
	unsigned char m_aryBlock[BLOCK_ROW][BLOCK_COL] = {};
	size_t m_nCurrentType = 0;
	size_t m_nCurrentShape = 0;

	unsigned char m_aryNextBlock[BLOCK_ROW][BLOCK_COL] = {};
	size_t m_nNextType = 0;
	size_t m_nNextShape = 0;

};

