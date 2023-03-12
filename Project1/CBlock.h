#pragma once
#define BLOCK_COL	4
#define BLOCK_ROW	4

#define BLOCK_SHAPE_COUNT	4

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
	size_t GetType(size_t nType);
	//��ȡshape
	size_t GetShape(size_t nShape);
	

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

