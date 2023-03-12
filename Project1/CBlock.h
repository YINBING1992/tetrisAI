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

	//产生方块
	void RandCreateBlock();
	//旋转方块
	void RotateBlock();
	//设置类型
	void SetType(size_t nType);
	//设置shape
	void SetShape(size_t nShape);
	//获取类型
	size_t GetType(size_t nType);
	//获取shape
	size_t GetShape(size_t nShape);
	

	const BLOCKDATE GetCurrentBlock()const; //当前图形
	const BLOCKDATE GetNextBlock()const;	//下一个图形

private:
	unsigned char m_aryBlock[BLOCK_ROW][BLOCK_COL] = {};
	size_t m_nCurrentType = 0;
	size_t m_nCurrentShape = 0;

	unsigned char m_aryNextBlock[BLOCK_ROW][BLOCK_COL] = {};
	size_t m_nNextType = 0;
	size_t m_nNextShape = 0;

};

