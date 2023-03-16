#pragma once
#include "CBlock.h"
#include "CBackGround.h"

#define LANDINGHEIGHT		-45
#define ROWSELIMINATED		34
#define ROWTRANSITIONS		-32
#define COLUMNTRANSITIONS	-93 
#define NUMBEROFHOLES		-79
#define WELLSUMS			-34

typedef struct
{
	size_t m_nShapeIndex;//旋转次数
	size_t m_nY;	//小方块的行
	size_t m_nX;	//小方块的列

	int m_nLandingHeight;
	int m_nErodedPieceCellsMetric;
	int m_nRowTransitions;
	int m_nBoardColTransitions;
	int m_nBoardBuriedHoles;
	int m_nBoardWells;

	int m_nPierreDellacherie;	//分数
	int m_nPriority;
}BLOCKRECORD;



class CTetrisAI
{

public:
	CTetrisAI();
	~CTetrisAI();

public:
	void SetBlock(const CBlock cBlock);
	void SetBackGround(const CBackGround cBackGround);
	void SetBestPoint( const CBackGround cBackGround, const CBlock cBlock, size_t nRow, size_t nCol);

	bool IsBlockCanWrite(size_t nRow, size_t nCol);
	void Cmp2SetBest();

	size_t AIRotate();//旋转
	size_t GetShapeIndex();
	size_t GetPointX();
private:

	int LandingHeight(size_t nRow);
	int ErodedPieceCellsMetric(size_t nRow, size_t nCol);
	int RowTransitions();
	int BoardColTransitions();
	int BoardBuriedHoles();
	int BoardWells();

	int Priority(int nIndex, int nCol);



	CBlock m_cBlock;
	CBackGround m_cBackGround;

	size_t m_nRow;	//小方块的行
	size_t m_nCol;	//小方块的列

	BLOCKRECORD m_BlockPoint = {};
	BLOCKRECORD m_aryBlockRecord[4][10] = {};
};

