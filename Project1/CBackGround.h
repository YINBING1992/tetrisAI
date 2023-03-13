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
	//��ʼ������
	void InitBackGround();
	//д��Block
	void WriteBlock2BackGround(const CBlock& Block,size_t nRow,size_t nCol,unsigned char chCurType, unsigned char chNextType);
	//���Block
	void ClearBlock2BackGround(const CBlock& Block, size_t nRow, size_t nCol, unsigned char chCurType);

	//��ȡ����
	const BACKGROUND GetBackGround()const;

	//�ܲ�������
	size_t RemoveRows();
	bool IsRemoveRow(int nRow);
	void RemoveRow(int nRow);

	//��ǰ�÷�
	size_t GetScore();


private:
	unsigned char m_uchBackGround[ROW][COL] = {};
	size_t m_uScore=0;
};

