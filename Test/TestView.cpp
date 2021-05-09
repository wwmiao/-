// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "TestDoc.h"
#include "TestView.h"
#include "time.h"
#include "setlength.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415926
using namespace std;

class Cbranch{
public:
    CPoint s_point;
	CPoint e_point;
	double L_auxin;
	double R_auxin;
	int R;
	int last_R;
	int lun;
	//int last_a;
	double ang;
};
vector<Cbranch> branch;
int l=0;
/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_START_SIMULATION, OnStartSimulation)
	ON_COMMAND(ID_SET_LENGTH, OnSetLength)
	ON_COMMAND(ID_STOP_SIMULATION, OnStopSimulation)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	count=0;
    length=50;
	sun.x=900;
	sun.y=100;
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int d=count*2;
	int d1=length*2;
	CDC* pdc=pDC;
    CBrush b;
    CPen p;
	/*if(branch[0].e_point.y<=sun.y){//植物不可能比太阳高
		KillTimer(0);
	}*/
	//计算每个的生长素
	int i=0;
	//double a=0.6;
	for(i=0;i<branch.size();i++){
        //branch[i].R_auxin=a;
		//branch[i].L_auxin=0;
		double t;
		double j,j1,j2,jr,jl;
		if((sun.x-branch[i].s_point.x)*(-(branch[i].e_point.y-branch[i].s_point.y))//三点一线
			-(sun.y-branch[i].s_point.y)*(-(branch[i].e_point.x-branch[i].s_point.x))==0){
			jr=PI/2;
			jl=PI/2;
			branch[i].R_auxin=(1/2)*(1-cos(jr));
			branch[i].L_auxin=(1/2)*(1-cos(jl));
			//branch[i].R_auxin=0;
			//branch[i].L_auxin=0;
		}
		j1=atan2(branch[i].s_point.y-branch[i].e_point.y,branch[i].s_point.x-branch[i].e_point.x);
		j2=atan2(branch[i].e_point.y-sun.y,branch[i].e_point.x-sun.x);
		t=j2-j1;
		//t=atan2(branch[i].s_point.x-branch[i].e_point.x,-(branch[i].s_point.y-branch[i].e_point.y))
			//-atan2(sun.x-branch[i].e_point.x,-(sun.y-branch[i].e_point.y));
		/*if(t>PI){
			t=t-2*PI;
		}
		if(t<-PI){
			t=t+2*PI;
		}*/
        //t=abs(t);
		if((sun.x-branch[i].s_point.x)*(-(branch[i].e_point.y-branch[i].s_point.y))
			-(sun.y-branch[i].s_point.y)*(-(branch[i].e_point.x-branch[i].s_point.x))<0){//太阳在树枝左边
			//t=abs(t);
			/*if(t>=PI/2){
				branch[i].R_auxin=0;
				branch[i].L_auxin=1;
			}
			else{
				branch[i].R_auxin=0;
				branch[i].L_auxin=sin(t);
			}*/
			if(j1==0){
				t=t-PI;
			}
			if(t>PI){
				t=t-2*PI;
			}
			jr=PI/2+t;
			jl=PI/2-t;
			if(jr<=0){
				branch[i].R_auxin=0;
				branch[i].L_auxin=1;
			}
			else{
				branch[i].R_auxin=(1-cos(jr))/2;
				branch[i].L_auxin=(1-cos(jl))/2;
			}
		}
		if((sun.x-branch[i].s_point.x)*(-(branch[i].e_point.y-branch[i].s_point.y))
			-(sun.y-branch[i].s_point.y)*(-(branch[i].e_point.x-branch[i].s_point.x))>0){//太阳在树枝右边
			/*if(t>=PI/2){
				branch[i].R_auxin=1;
				branch[i].L_auxin=0;
			}
			else{
				branch[i].R_auxin=sin(t);
				branch[i].L_auxin=0;
			}*/
			jr=PI/2+t;
			jl=PI/2-t;
			if(jl<=0){
				branch[i].R_auxin=1;
				branch[i].L_auxin=0;
			}
			else{
				//branch[i].L_auxin=(sin(jl))/2;
				branch[i].R_auxin=(1-cos(jr))/2;
				branch[i].L_auxin=(1-cos(jl))/2;
				//branch[i].R_auxin=1-branch[i].L_auxin;
			}
		}

	}
    //如果到达长度
	if(count!=0&&count%length==0){
		l=l+1;
		//计算新的绘图点起点角度存入branch
		int t1=branch.size();
        for(i=0;i<t1;i++){
			Cbranch newb;
			newb.s_point=branch[i].e_point;
			double p;
            //branch.push_back(newb);
			if(branch[i].R==0){//上一树枝垂直长
                if(branch[i].R_auxin>branch[i].L_auxin){
					p=asin(branch[i].R_auxin);
					newb.ang=PI/2-p;
					newb.R=1;
					//newb.last_a=1;
				}
                if(branch[i].R_auxin<branch[i].L_auxin){
					p=asin(branch[i].L_auxin);
					newb.ang=PI/2-p;
					newb.R=2;
					//newb.last_a=2;
				}
				if(branch[i].R_auxin==branch[i].L_auxin){
					//p=asin(branch[i].L_auxin);
					newb.ang=PI/2;
					newb.R=0;
					//newb.last_a=0;
				}
				newb.last_R=0;
			}
			if(branch[i].R==1){//上一树枝向右长
				if(branch[i].R_auxin>branch[i].L_auxin){
					p=asin(branch[i].R_auxin);
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)))-p;
					//newb.last_a=1;
				}
				if(branch[i].R_auxin<branch[i].L_auxin){
					p=asin(branch[i].L_auxin);
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)))+p;
					//newb.last_a=2;
				}
				if(branch[i].R_auxin==branch[i].L_auxin){
					//p=0;
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)));
					//newb.last_a=0;
				}
				newb.last_R=1;
				if(newb.ang<PI/2){
					newb.R=1;
				}
				else if(newb.ang==PI/2){
					newb.R=0;
				}
				else{
					newb.R=2;
				}
			}
			if(branch[i].R==2){//上一树枝向左长
				if(branch[i].R_auxin<branch[i].L_auxin){
					p=asin(branch[i].L_auxin);
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)))-p;
					//newb.last_a=2;
				}
				if(branch[i].R_auxin>branch[i].L_auxin){
					p=asin(branch[i].L_auxin);
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)))+p;
					//newb.last_a=1;
				}
				if(branch[i].R_auxin==branch[i].L_auxin){
					//p=0;
					newb.ang=atan(abs((branch[i].e_point.y-branch[i].s_point.y)/(branch[i].e_point.x-branch[i].s_point.x)));
					//newb.last_a=0;
				}
				newb.last_R=2;
				if(newb.ang<PI/2){
					newb.R=2;
				}
				else if(newb.ang==PI/2){
					newb.R=0;
				}
				else{
					newb.R=1;
				}
			}
			//newb.lun=branch[i].lun;
			newb.lun=l;
			branch.push_back(newb);
		}
		//CString output;
	    //output.Format("branch.size = %d",branch.size()-1);
	    //this->MessageBox(output);
	}
	//计算终点画出图像
	for(i=0;i<branch.size();i++){
		if(branch[i].last_R==0){
            if(branch[i].R==1){
				branch[i].e_point.x=branch[i].s_point.x+(d-branch[i].lun*d1)*cos(branch[i].ang);
				branch[i].e_point.y=branch[i].s_point.y-(d-branch[i].lun*d1)*sin(branch[i].ang);
			}
			if(branch[i].R==2){
				branch[i].e_point.x=branch[i].s_point.x-(d-branch[i].lun*d1)*cos(branch[i].ang);
				branch[i].e_point.y=branch[i].s_point.y-(d-branch[i].lun*d1)*sin(branch[i].ang);
			}
			if(branch[i].R==0){
				branch[i].e_point.x=branch[i].s_point.x-(d-branch[i].lun*d1)*cos(branch[i].ang);
				branch[i].e_point.y=branch[i].s_point.y-(d-branch[i].lun*d1)*sin(branch[i].ang);
			}
		}
		if(branch[i].last_R==1){
			branch[i].e_point.x=branch[i].s_point.x+(d-branch[i].lun*d1)*cos(branch[i].ang);
			branch[i].e_point.y=branch[i].s_point.y-(d-branch[i].lun*d1)*sin(branch[i].ang);
		}
		if(branch[i].last_R==2){
			branch[i].e_point.x=branch[i].s_point.x-(d-branch[i].lun*d1)*cos(branch[i].ang);
			branch[i].e_point.y=branch[i].s_point.y-(d-branch[i].lun*d1)*sin(branch[i].ang);
		}

        //(d-(branch[i].lun-1)*d1)
		p.CreatePen(PS_SOLID,10,RGB(0,255,0));
	    pdc->SelectObject(p);
        pdc->MoveTo(branch[i].s_point);
	    pdc->LineTo(branch[i].e_point);
        p.DeleteObject();
		/*p.CreatePen(PS_SOLID,1,RGB(255,255,255));
        pdc->SelectObject(p);
	    b.CreateSolidBrush(RGB(255,0,0));
        pdc->SelectObject(b);
	    pdc->Ellipse(sun.x-20,sun.y-20,sun.x+20,sun.y+20);
        p.DeleteObject();*/
	}
	p.CreatePen(PS_SOLID,1,RGB(255,255,255));
    pdc->SelectObject(p);
	b.CreateSolidBrush(RGB(255,0,0));
    pdc->SelectObject(b);
	pdc->Ellipse(sun.x-20,sun.y-20,sun.x+20,sun.y+20);
    p.DeleteObject();
	
	
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//x=point.x;
	//y=point.y;
	sun.x=point.x;
	sun.y=point.y;
	//SetTimer(0,1000,NULL);
	//Invalidate();
	//CString output;
	//output.Format("zuobiaowei x = %d,y = %d",x,y);
	//this->MessageBox(output);
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    this->count++;
	Invalidate();
	CView::OnTimer(nIDEvent);
}

void CTestView::OnStartSimulation() 
{
	// TODO: Add your command handler code here
	//CDC* pdc=GetDC();

    SetTimer(0,500,NULL);
    Cbranch temp;
	temp.s_point.x=500;
	temp.s_point.y=500;
	temp.R=0;
	temp.ang=PI/2;
    temp.last_R=0;
	temp.lun=0;
	branch.push_back(temp);
	//Invalidate();
	
}

void CTestView::OnSetLength() 
{
	// TODO: Add your command handler code here
    setlength dlg;
	//dlg.DoModal();
    if(IDOK==dlg.DoModal()){
        length=dlg.m_length;
	}
    //CString output;
	//output.Format("length = %d",length);
	//this->MessageBox(output);
	
}

void CTestView::OnStopSimulation() 
{
	// TODO: Add your command handler code here
	KillTimer(0);
}
