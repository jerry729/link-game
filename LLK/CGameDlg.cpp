// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "LLKDlg.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	// 初始化起始点坐标
	m_ptGameTop.x = 5;
	m_ptGameTop.y = 5;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.top = m_ptGameTop.y;//游戏区域的初始点
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MCol;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MRow;//生成的地图是10*16的游戏区域

	//初始化图标选中状态
	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

//初始化窗口背景和大小
void CGameDlg::InitBackground()
{	

	//加载位图
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(Backbmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景图片
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//更新窗口
	UpdateWindow();
}

void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内容兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);

	//加载掩码BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内容兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//窗口标题
	this->SetWindowTextW(_T("欢乐连连看——基本模式"));

	//初始化背景
	InitBackground();

	//初始化元素
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// 绘制背景图片	
	dc.BitBlt(0, 0, 800,600, &m_dcMem, 0, 0, SRCCOPY);

					   // 不为绘图消息调用 CDialogEx::OnPaint()
}

void CGameDlg::UpdateWindow()
{

	// TODO: 在此处添加实现代码.

	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetWindowRect(rtClient);	//获得客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	//设置对话框显示，在windows窗口正中央
	CenterWindow();
}




//更新地图
void CGameDlg::UpdateMap()
{

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {//绘制地图

			int nInfo = m_gameControl.GetElement(i, j);       //当前元素图片的数值
			if (nInfo == BLANK)  continue;

			//将背景与掩码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);

			//将元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);

		}
	}

}






//绘制矩形提示框
void CGameDlg::DrawTipFrame(int nRow, int nCol) {

	//获取DC
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));//矩形框的颜色
	CRect rtTipFrame;

	//根据矩形的左上角坐标和右上角坐标进行绘制
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

//判断点击位置是否在游戏地图中
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//判断鼠标点击的区域
	if (point.y<m_rtGameRect.top || point.y>m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//行号=(点击位置y坐标-游戏地图起始y坐标)/元素的高度
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	//列号=(点击位置x坐标-游戏地图起始x坐标)/元素的长度
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	if (nRow > MRow-1 || nCol > MCol-1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	// 第一个点
	if (m_bFirstPoint) {
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
		//m_ptSelFirst.x = nCol;
		//m_ptSelFirst.y = nRow;


	}
	//第二个点
	else {
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		/*m_ptSelSec.x = nCol;
		m_ptSelSec.y = nRow;*/

		Vertex avPath[MRow*MCol];     //获得路径
		int nVexnum = 0;      //顶点个数

		//判断是否是相同图片，连接起来
		if (m_gameControl.Link(avPath, nVexnum)) {

			DrawTipLine( avPath, nVexnum);
			/*m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] = -1;
			m_anMap[m_ptSelSec.y][m_ptSelSec.x] = -1;*/
			//更新地图
			UpdateMap();
		}
		Sleep(200);    //延迟
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新

		//判断胜负
		if (m_gameControl.IsWin()) {
			MessageBox(_T("\t游戏胜利，可选择继续游戏或退出"), _T("欢乐连连看　基本模式"));
			m_bPlaying = false;
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true); 
			//游戏结束，可以继续开始游戏
		}
	}

	m_bFirstPoint = !m_bFirstPoint; //赋反值
	CDialogEx::OnLButtonUp(nFlags, point);
}

//绘制提示线
void CGameDlg::DrawTipLine(Vertex avPath[MRow*MCol], int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}


//开始游戏
void CGameDlg::OnBnClickedButtonStart()
{
	/*int anMap[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_anMap[i][j] = anMap[i][j];
		}
	}*/

	m_gameControl.StartGame();

	//判断是否输入游戏中的状态，开始游戏不能点
	m_bPlaying = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);

	//更新地图
	UpdateMap();

	//更新游戏区域
	Invalidate(FALSE);
}


void CGameDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (m_bPlaying == false) return;//游戏没有进行

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MRow*MCol];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		//画第二个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);
		//画提示线
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //延迟1秒后

		UpdateMap();	//更新地图，矩形框消失

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
}


void CGameDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gameControl.Reset();//重排

	//更新界面
	UpdateMap();
	//局部矩形更新
	InvalidateRect(m_rtGameRect, FALSE);    

}
