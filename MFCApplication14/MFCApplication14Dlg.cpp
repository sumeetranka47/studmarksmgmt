// MFCApplication14Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFCApplication14.h"
#include "MFCApplication14Dlg.h"
#include "afxdialogex.h"
#include "BasicExcel1.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "login_ats.h"
#include "ObjectDefinitions.h"

#define IDC_EDIT1
using namespace YExcel;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication14Dlg dialog



CMFCApplication14Dlg::CMFCApplication14Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication14Dlg::IDD, pParent)
	, test(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication14Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CMFCApplication14Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication14Dlg::OnBnClickedButton1)

	
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication14Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication14Dlg message handlers

BOOL CMFCApplication14Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication14Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication14Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication14Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication14Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TCHAR filtri[] = _T("CSV files (*.csv)|*.csv||");
	CString path;

	CFileDialog dlg(TRUE, _T("csv"), _T("*.csv"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filtri);
	dlg.m_ofn.lpstrTitle = _T("Open...");

	if (dlg.DoModal() == IDOK) //OK
	{
		path = dlg.GetPathName();
		//
		CStdioFile readFile;
		CFileException fileException;
		CString strLine;

		if (readFile.Open(path, CFile::modeRead, &fileException))
		{
			while (readFile.ReadString(strLine))
			{
				MessageBox(path);
			}
		}
		else
		{
			CString strErrorMsg;
			strErrorMsg.Format(_T("Can't open file %s , error : %u"), path, fileException.m_cause);
			AfxMessageBox(strErrorMsg);
		}
		readFile.Close();
	}
	ifstream in(path);

	string line, field;

	vector<long long int > rollno;  // the 2D array
	vector<int> marks;                // array of values for one line only
	int i; int error = 0;
	while (getline(in, line))    // get next line in file
	{
		i = 0;
		stringstream ss(line);

		while (getline(ss, field, ','))  // break line into comma delimitted fields
		{
			if (field != "")
			{
				if (i == 0)
				{
					int temp1;
					stringstream(field) >> temp1;
					rollno.push_back(temp1);  // add each field to the 1D array
					i = i + 1;
					IDC_EDIT1
					/*cout << temp1 << "\n";*/
				}
				else if (i == 1)
				{
					int temp2;
					stringstream(field) >> temp2;
					marks.push_back(temp2);  // add each field to the 1D array
					i = i + 1;
					
					/*cout << temp2 << endl;*/
				}
				else
				{
					error = 1;
					AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
				}
				//error

			}
			else
			{
				error = 1;
				AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
			}
			//error
		}


	}
	if (error == 0)
	{
		BasicExcel test;
		test.New(2);
		test.RenameWorksheet("Sheet1", "Test1");
		BasicExcelWorksheet* sheet = test.GetWorksheet("Test1");
		if (sheet)
		{
			sheet->Cell(0, 0)->Set("abc");
			test.SaveAs("Time1.xls");
		}
		test.Load("Time1.xls");
		BasicExcelWorksheet* w = test.GetWorksheet("Test1");
		if (w)
		{
			w->Cell(1, 1)->Set("def");
			test.SaveAs("Time1.xls");
		}
		BasicExcel excelFile;
		excelFile.AddWorksheet("courseName",-1);
		excelFile.SaveAs("courses.xls");

		excelFile.Load("courses.xls");
		BasicExcelWorksheet* curCourse = excelFile.GetWorksheet("courseName");
		if (curCourse)
		{
			TRACE("curCourse name is %s", curCourse->GetAnsiSheetName());
			curCourse->Cell(1, 1)->Set("coursename");
			/*curCourse->Cell(2, 1)->Set("RollNo\\Quiz");
			for (int i = 1; i <= numQuiz; i++)
			{
			curCourse->Cell(1, i)->SetInteger(i);
			}*/
			excelFile.SaveAs("courses.xls");
		}
		for (i = 0; i < 3;i++)
		excelFile.AddWorksheet("CS203", -1);
		excelFile.SaveAs("courses.xls");

	}



}


void CMFCApplication14Dlg::OnBnClickedButton2()
{
	/*DatabaseWrapper* db;
	db = new DatabaseWrapper();
	int quizWts[5] = { 20, 20, 20, 20, 20 };
	db->createCourse(5, "Chemistry", "ch101", 2015);
	db->createCourse(6, "Physics", "ph102", 2015);
	db->addPerson("chatto", 101010, Person::PROF);
	db->addPerson("jainam", 130101055, Person::STUDENT);
	db->addPerson("admin", 1, Person::ADMIN);
	db->addLoginDetails(1, "admin", Person::ADMIN);
	db->addPerson("ranka", 130101033, Person::STUDENT);
	db->linkPersonCourse(130101055, Person::STUDENT, "ch101");
	db->linkPersonCourse(130101033, Person::STUDENT, "ph102");
	db->linkPersonCourse(130101033, Person::STUDENT, "ch101");
	db->linkPersonCourse(101010, Person::PROF, "ch101");
	db->linkPersonCourse(101010, Person::PROF, "ph102");
	db->addLoginDetails(101010, "prof", Person::PROF);
	db->setQuizWeights("ch101", quizWts);
	int a = db->getQuizWeight(3, "ch101");
	db->setQuizMarks("ch101", 130101033, 3, 15);
	db->setQuizMarks("ch101", 130101055, 3, 17);
	Quiz *q = db->getQuizMarks("ch101", 3);
	Student* st = NULL;
	st = db->getCourseStudents("ch101", &a);
	db->addLoginDetails(130101033, "yomanas", Person::STUDENT);*/
	/*CString a("yomanas");
	db->checkLogin(130101033, "yomanas", Person::STUDENT);
	db->checkLogin(130101033, "yomanas", Person::STUDENT);
	
	Course *co = db->getStudentCourses(130101033, &a);
	string *cs = db->getCourseList(&a);	*/
	login_ats dlg;
	dlg.DoModal();
	// TODO: Add your control notification handler code here
}
