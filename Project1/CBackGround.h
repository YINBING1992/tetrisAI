#pragma once
#include "CBlock.h"
typedef unsigned char(*BACKGROUND)[COL];

class CBackGround
{
public:
	CBackGround();
	CBackGround(const CBackGround& BackGround);
	~CBackGround();
	CBackGround& operator= (const CBackGround& BackGround);
public:
	//初始化背景
	void InitBackGround();
	//写入Block
	void WriteBlock2BackGround(const CBlock& Block,size_t nRow,size_t nCol,unsigned char chCurType, unsigned char chNextType);
	//清除Block
	void ClearBlock2BackGround(const CBlock& Block, size_t nRow, size_t nCol, unsigned char chCurType);

	//获取数据
	const BACKGROUND GetBackGround()const;

	//能不能消除
	size_t RemoveRows();
	bool IsRemoveRow(int nRow);
	void RemoveRow(int nRow);

	//当前得分
	size_t GetScore();


private:
	unsigned char m_uchBackGround[ROW][COL] = {};
	size_t m_uScore=0;
};

