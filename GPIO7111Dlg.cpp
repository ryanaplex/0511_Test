
// GPIO7111Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GPIO7111.h"
#include "GPIO7111Dlg.h"
#include "Winio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_GPIOS			8
#define SBC_7111_ADDRESS		0xFED0C000
#define RDTEST
// CAboutDlg dialog used for App About
static int taskmgr_count=0;

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGPIO7111Dlg dialog




CGPIO7111Dlg::CGPIO7111Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPIO7111Dlg::IDD, pParent)
	, m_address(_T(""))
	, m_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPIO7111Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LED1, m_led1);
	DDX_Control(pDX, IDC_LED2, m_led2);
	DDX_Control(pDX, IDC_LED3, m_led3);
	DDX_Control(pDX, IDC_LED4, m_led4);
	DDX_Control(pDX, IDC_LED5, m_led5);
	DDX_Control(pDX, IDC_LED6, m_led6);
	DDX_Control(pDX, IDC_LED7, m_led7);
	DDX_Control(pDX, IDC_LED8, m_led8);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT1, m_direction1);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT2, m_direction2);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT3, m_direction3);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT4, m_direction4);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT5, m_direction5);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT6, m_direction6);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT7, m_direction7);
	DDX_Control(pDX, IDC_DRIECTION_OUTPUT8, m_direction8);
	DDX_Control(pDX, IDC_PULL_HIGH1, m_pullhigh1);
	DDX_Control(pDX, IDC_PULL_HIGH2, m_pullhigh2);
	DDX_Control(pDX, IDC_PULL_HIGH3, m_pullhigh3);
	DDX_Control(pDX, IDC_PULL_HIGH4, m_pullhigh4);
	DDX_Control(pDX, IDC_PULL_HIGH5, m_pullhigh5);
	DDX_Control(pDX, IDC_PULL_HIGH6, m_pullhigh6);
	DDX_Control(pDX, IDC_PULL_HIGH7, m_pullhigh7);
	DDX_Control(pDX, IDC_PULL_HIGH8, m_pullhigh8);
	DDX_Text(pDX, IDC_ADDRESS, m_address);
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_Control(pDX, IDC_RECHECK, m_recheck);
	DDX_Control(pDX, IDC_ADVANCE, m_advance);
	DDX_Control(pDX, IDC_ADDRESS, m_addressctl);
	DDX_Control(pDX, IDC_VALUE, m_valuectl);
	DDX_Control(pDX, IDC_READ, m_readctl);
	DDX_Control(pDX, IDC_WRITE, m_writectl);
	DDX_Control(pDX, IDC_DESCRIPTION1, m_description1);
	DDX_Control(pDX, IDC_DESCRIPTION2, m_description2);
	DDX_Control(pDX, IDC_DESCRIPTION3, m_description3);
	DDX_Control(pDX, IDC_DESCRIPTION4, m_description4);
	DDX_Control(pDX, IDC_DESCRIPTION5, m_description5);
	DDX_Control(pDX, IDC_DESCRIPTION6, m_description6);
	DDX_Control(pDX, IDC_DESCRIPTION7, m_description7);
	DDX_Control(pDX, IDC_DESCRIPTION8, m_description8);
}

BEGIN_MESSAGE_MAP(CGPIO7111Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGPIO7111Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGPIO7111Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_READ, &CGPIO7111Dlg::OnBnClickedRead)
	ON_BN_CLICKED(IDC_WRITE, &CGPIO7111Dlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_ADVANCE, &CGPIO7111Dlg::OnBnClickedAdvance)
	ON_BN_CLICKED(IDC_RECHECK, &CGPIO7111Dlg::OnBnClickedRecheck)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT1, &CGPIO7111Dlg::OnBnClickedDriectionOutput1)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT2, &CGPIO7111Dlg::OnBnClickedDriectionOutput2)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT3, &CGPIO7111Dlg::OnBnClickedDriectionOutput3)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT4, &CGPIO7111Dlg::OnBnClickedDriectionOutput4)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT5, &CGPIO7111Dlg::OnBnClickedDriectionOutput5)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT6, &CGPIO7111Dlg::OnBnClickedDriectionOutput6)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT7, &CGPIO7111Dlg::OnBnClickedDriectionOutput7)
	ON_BN_CLICKED(IDC_DRIECTION_OUTPUT8, &CGPIO7111Dlg::OnBnClickedDriectionOutput8)
	ON_BN_CLICKED(IDC_PULL_HIGH1, &CGPIO7111Dlg::OnBnClickedPullHigh1)
	ON_BN_CLICKED(IDC_PULL_HIGH2, &CGPIO7111Dlg::OnBnClickedPullHigh2)
	ON_BN_CLICKED(IDC_PULL_HIGH3, &CGPIO7111Dlg::OnBnClickedPullHigh3)
	ON_BN_CLICKED(IDC_PULL_HIGH4, &CGPIO7111Dlg::OnBnClickedPullHigh4)
	ON_BN_CLICKED(IDC_PULL_HIGH5, &CGPIO7111Dlg::OnBnClickedPullHigh5)
	ON_BN_CLICKED(IDC_PULL_HIGH6, &CGPIO7111Dlg::OnBnClickedPullHigh6)
	ON_BN_CLICKED(IDC_PULL_HIGH7, &CGPIO7111Dlg::OnBnClickedPullHigh7)
	ON_BN_CLICKED(IDC_PULL_HIGH8, &CGPIO7111Dlg::OnBnClickedPullHigh8)
END_MESSAGE_MAP()


// CGPIO7111Dlg message handlers

BOOL CGPIO7111Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	int count=0;
	while(!InitializeWinIo())
	{
		if(count++>10)
		{
			MessageBox(_T("initialize WinIO fail! "));
			OnCancel();
			break;
		}
		Sleep(10);
	}

	CWnd *pWndLed = NULL;
	pWndLed = (CWnd *)GetDlgItem(IDC_LED1);
	m_led1.SetLED(pWndLed,ID_LED_GREEN,ID_SHAPE_ROUND,500);
	m_led1.SwitchOn();
	m_led1.LedOn();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED2);
	m_led2.SetLED(pWndLed,ID_LED_GREEN,ID_SHAPE_ROUND,500);
	m_led2.SwitchOn();
	m_led2.LedOn();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED3);
	m_led3.SetLED(pWndLed,ID_LED_GREEN,ID_SHAPE_ROUND,500);
	m_led3.SwitchOn();
	m_led3.LedOn();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED4);
	m_led4.SetLED(pWndLed,ID_LED_GREEN,ID_SHAPE_ROUND,500);
	m_led4.SwitchOn();
	m_led4.LedOn();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED5);
	m_led5.SetLED(pWndLed,ID_LED_RED,ID_SHAPE_ROUND,500);
	m_led5.SwitchOn();
	m_led5.LedOff();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED6);
	m_led6.SetLED(pWndLed,ID_LED_RED,ID_SHAPE_ROUND,500);
	m_led6.SwitchOn();
	m_led6.LedOff();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED7);
	m_led7.SetLED(pWndLed,ID_LED_RED,ID_SHAPE_ROUND,500);
	m_led7.SwitchOn();
	m_led7.LedOff();

	pWndLed = (CWnd *)GetDlgItem(IDC_LED8);
	m_led8.SetLED(pWndLed,ID_LED_RED,ID_SHAPE_ROUND,500);
	m_led8.SwitchOn();
	m_led8.LedOff();

	m_direction1.SetCheck(false);
	m_direction2.SetCheck(false);
	m_direction3.SetCheck(false);
	m_direction4.SetCheck(false);
	m_direction5.SetCheck(false);
	m_direction6.SetCheck(false);
	m_direction7.SetCheck(false);
	m_direction8.SetCheck(false);

	m_pullhigh1.SetCheck(true);
	m_pullhigh2.SetCheck(true);
	m_pullhigh3.SetCheck(true);
	m_pullhigh4.SetCheck(true);
	m_pullhigh5.SetCheck(true);
	m_pullhigh6.SetCheck(true);
	m_pullhigh7.SetCheck(true);
	m_pullhigh8.SetCheck(true);

	OnBnClickedDriectionOutput1();
	OnBnClickedDriectionOutput2();
	OnBnClickedDriectionOutput3();
	OnBnClickedDriectionOutput4();
	OnBnClickedDriectionOutput5();
	OnBnClickedDriectionOutput6();
	OnBnClickedDriectionOutput7();
	OnBnClickedDriectionOutput8();

	OnBnClickedPullHigh1();
	OnBnClickedPullHigh2();
	OnBnClickedPullHigh3();
	OnBnClickedPullHigh4();
	OnBnClickedPullHigh5();
	OnBnClickedPullHigh6();
	OnBnClickedPullHigh7();
	OnBnClickedPullHigh8();

	Set_GPIO_Enable();

	m_recheck.SetCheck(true);
	OnBnClickedAdvance();
#ifdef RDTEST
	m_advance.ShowWindow(SW_SHOWNORMAL);
#else
	m_advance.ShowWindow(SW_HIDE);
#endif

	for(int gpio=1;gpio <= MAX_GPIOS;gpio++)
	{
		OnChangeDescription(gpio);
	}

	SetTimer(1,400, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGPIO7111Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGPIO7111Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGPIO7111Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGPIO7111Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CGPIO7111Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CGPIO7111Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	ShutdownWinIo();
}

void CGPIO7111Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int gpio=0;

	//ShowWindow(SW_HIDE);	//LiLi
	if(m_recheck.GetCheck())
	{
		for(gpio=1;gpio<=MAX_GPIOS;gpio++)
		{
			Set_GPIO_Check(gpio);
		}
	}
	for(gpio=1;gpio<=MAX_GPIOS;gpio++)
	{
		Set_LEDS_status(gpio);
#ifdef RDTEST
		OnChangeDescription(gpio);
#endif
	}
	CDialog::OnTimer(nIDEvent);
}

void CGPIO7111Dlg::Set_GPIO_Enable(void)
{
    UINT32 PhysVal=0x0;
	UINT64 PhysAddr64=0x0;
	for(int gpio=1;gpio <= MAX_GPIOS;gpio++)
	{
		PhysAddr64=Get_GPIO_PHYSAddress(gpio);
		if(PhysAddr64)
		{
			PhysVal=0x2003CC80;
			if(gpio==3)PhysVal=0x2003CD01;
			SetPhysLong((PBYTE)PhysAddr64,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
		}
		Sleep(30);
		Set_GPIO_Check(gpio);
	}
	return;
}

void CGPIO7111Dlg::Set_GPIO_Output(int gpio,bool status)
{
	UINT32 PhysVal=0x0;
	UINT64 PhysAddr64=0x0;

	PhysAddr64=Get_GPIO_PHYSAddress(gpio);

	if(PhysAddr64)
	{
		GetPhysLong((PBYTE)PhysAddr64+8,(PDWORD)&PhysVal);
		if(PhysVal&0x4)
		{
			PhysVal=0x4;
			if(status)PhysVal|=0x01;
			SetPhysLong((PBYTE)PhysAddr64+8,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
		}
		else
		{
			SetPhysLong((PBYTE)PhysAddr64+8,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
			Sleep(10);
			PhysVal=0x4;
			if(status)PhysVal|=0x01;
			SetPhysLong((PBYTE)PhysAddr64+8,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
		}
		Sleep(10);
	}
	return;
}

void CGPIO7111Dlg::Set_GPIO_Input(int gpio,bool status)
{
	UINT32 PhysVal=0x0;
	UINT64 PhysAddr64=0x0;

	PhysAddr64=Get_GPIO_PHYSAddress(gpio);

	if(PhysAddr64)
	{
		GetPhysLong((PBYTE)PhysAddr64+8,(PDWORD)&PhysVal);

		if(status && PhysVal==0x3)
		{
			PhysVal=0x2;
			if(status)PhysVal|=0x01;
			SetPhysLong((PBYTE)PhysAddr64+8,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
		}
		else
		{
			Set_GPIO_Output(gpio,status);
			Sleep(10);
			PhysVal=0x2;
			if(status)PhysVal|=0x01;
			SetPhysLong((PBYTE)PhysAddr64+8,PhysVal);	//Func. Pin Mux = 0 //bit 0,1,2
		}
		Sleep(10);
	}
	return;
}

bool CGPIO7111Dlg::Get_GPIO_InputStatus(int gpio)
{
	UINT32 PhysVal=0x0;
	UINT64 PhysAddr64=0x0;
	PhysAddr64=Get_GPIO_PHYSAddress(gpio);

	if(PhysAddr64)
	{
		GetPhysLong((PBYTE)PhysAddr64+8,(PDWORD)&PhysVal);
	}
	return(PhysVal&0x01?true:false);
}

void CGPIO7111Dlg::Set_LEDS_status(int gpio)
{
	int gpiodirection=0;
	switch(gpio)
	{
		case 1:
			gpiodirection=m_direction1.GetCheck();
			if(gpiodirection)
				m_led1.SetColor(ID_LED_RED);
			else
				m_led1.SetColor(ID_LED_GREEN);

			if(m_pullhigh1.GetCheck())
				m_led1.LedOn();
			else
				m_led1.LedOff();
			break;
		case 2:
			gpiodirection=m_direction2.GetCheck();
			if(gpiodirection)
				m_led2.SetColor(ID_LED_RED);
			else
				m_led2.SetColor(ID_LED_GREEN);

			if(m_pullhigh2.GetCheck())
				m_led2.LedOn();
			else
				m_led2.LedOff();
			break;
		case 3:
			gpiodirection=m_direction3.GetCheck();
			if(gpiodirection)
				m_led3.SetColor(ID_LED_RED);
			else
				m_led3.SetColor(ID_LED_GREEN);

			if(m_pullhigh3.GetCheck())
				m_led3.LedOn();
			else
				m_led3.LedOff();
			break;
		case 4:
			gpiodirection=m_direction4.GetCheck();
			if(gpiodirection)
				m_led4.SetColor(ID_LED_RED);
			else
				m_led4.SetColor(ID_LED_GREEN);

			if(m_pullhigh4.GetCheck())
				m_led4.LedOn();
			else
				m_led4.LedOff();
			break;
		case 5:
			gpiodirection=m_direction5.GetCheck();
			if(gpiodirection)
				m_led5.SetColor(ID_LED_RED);
			else
				m_led5.SetColor(ID_LED_GREEN);

			if(m_pullhigh5.GetCheck())
				m_led5.LedOn();
			else
				m_led5.LedOff();
			break;
		case 6:
			gpiodirection=m_direction6.GetCheck();
			if(gpiodirection)
				m_led6.SetColor(ID_LED_RED);
			else
				m_led6.SetColor(ID_LED_GREEN);

			if(m_pullhigh6.GetCheck())
				m_led6.LedOn();
			else
				m_led6.LedOff();
			break;
		case 7:
			gpiodirection=m_direction7.GetCheck();
			if(gpiodirection)
				m_led7.SetColor(ID_LED_RED);
			else
				m_led7.SetColor(ID_LED_GREEN);

			if(m_pullhigh7.GetCheck())
				m_led7.LedOn();
			else
				m_led7.LedOff();
			break;
		case 8:
			gpiodirection=m_direction8.GetCheck();
			if(gpiodirection)
				m_led8.SetColor(ID_LED_RED);
			else
				m_led8.SetColor(ID_LED_GREEN);

			if(m_pullhigh8.GetCheck())
				m_led8.LedOn();
			else
				m_led8.LedOff();
			break;
		default:
			break;
	}
	if(gpiodirection)
		return;
	if(Get_GPIO_InputStatus(gpio))
	{
		switch(gpio)
		{
			case 1:
				taskmgr_count=0;
				m_led1.LedOn();
				break;
			case 2:
				m_led2.LedOn();
				break;
			case 3:
				m_led3.LedOn();
				break;
			case 4:
				m_led4.LedOn();
				break;
			case 5:
				m_led5.LedOn();
				break;
			case 6:
				m_led6.LedOn();
				break;
			case 7:
				m_led7.LedOn();
				break;
			case 8:
				m_led8.LedOn();
				break;
			default:
				break;
		}
	}
	else
	{
		switch(gpio)
		{
			case 1:
		
				m_led1.LedOff();
				break;
			case 2:
				m_led2.LedOff();
				break;
			case 3:
				m_led3.LedOff();
				break;
			case 4:
				m_led4.LedOff();
				break;
			case 5:
				m_led5.LedOff();
				break;
			case 6:
				m_led6.LedOff();
				break;
			case 7:
				m_led7.LedOff();
				break;
			case 8:
				m_led8.LedOff();
				break;
			default:
				break;
		}
	}
	return;
}

UINT64 CGPIO7111Dlg::Get_GPIO_PHYSAddress(int gpio)
{
	UINT64 PhysAddr64=0x0;

	switch(gpio)
	{
		case 1://gpio 9
			PhysAddr64=SBC_7111_ADDRESS+0x2250;
			break;
		case 2://gpio 10
			PhysAddr64=SBC_7111_ADDRESS+0x2120;
			break;
		case 3://gpio 17
			PhysAddr64=SBC_7111_ADDRESS+0x20A0;
			break;
		case 4://gpio 26
			PhysAddr64=SBC_7111_ADDRESS+0x2160;
			break;
		case 5://gpio 4
			PhysAddr64=SBC_7111_ADDRESS+0x2200;
			break;
		case 6://gpio 5
			PhysAddr64=SBC_7111_ADDRESS+0x2220;
			break;
		case 7://gpio 6
			PhysAddr64=SBC_7111_ADDRESS+0x2240;
			break;
		case 8://gpio 8
			PhysAddr64=SBC_7111_ADDRESS+0x2260;
			break;
		default:
			PhysAddr64=0x0;
			break;
	}
	return PhysAddr64;
}

void CGPIO7111Dlg::Set_GPIO_Check(int gpio)
{
	int outputstatus=0;
	int IOdirection=0;

	switch(gpio)
	{
		case 1:
			outputstatus=m_pullhigh1.GetCheck();
			IOdirection=m_direction1.GetCheck();
			break;
		case 2:
			outputstatus=m_pullhigh2.GetCheck();
			IOdirection=m_direction2.GetCheck();
			break;
		case 3:
			outputstatus=m_pullhigh3.GetCheck();
			IOdirection=m_direction3.GetCheck();
			break;
		case 4:
			outputstatus=m_pullhigh4.GetCheck();
			IOdirection=m_direction4.GetCheck();
			break;
		case 5:
			outputstatus=m_pullhigh5.GetCheck();
			IOdirection=m_direction5.GetCheck();
			break;
		case 6:
			outputstatus=m_pullhigh6.GetCheck();
			IOdirection=m_direction6.GetCheck();
			break;
		case 7:
			outputstatus=m_pullhigh7.GetCheck();
			IOdirection=m_direction7.GetCheck();
			break;
		case 8:
			outputstatus=m_pullhigh8.GetCheck();
			IOdirection=m_direction8.GetCheck();
			break;
		default:
			return;
			break;
	}
	if(IOdirection)
	{
		Set_GPIO_Output(gpio,outputstatus?true:false);
	}
	else
	{
		Set_GPIO_Input(gpio,outputstatus?true:false);
	}
	return;
}

void CGPIO7111Dlg::OnBnClickedRead()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int i=0;
	char charSource[20];
	size_t ilen=0;
	UINT64 PhysAddr64=0x0;

	memset(charSource, 0, sizeof(charSource));
	for(i=0;i<m_address.GetLength();i++)
	{
		charSource[i]=(char)m_address.GetAt(i);
	}
	ilen=strlen(charSource);
	for(i=0;i<ilen;i++)
	{
		if(charSource[i]>0)
		{
			PhysAddr64*=16;
			if(charSource[i]>'9')
			{
				if(charSource[i]>'F')
				{
					PhysAddr64+=(charSource[i]-'a'+10);
				}
				else
				{
					PhysAddr64+=(charSource[i]-'A'+10);
				}
			}
			else
			{
				PhysAddr64+=(charSource[i]-'0');
			}
		}
	}
//	UINT64 PhysAddr64=strtol(charSource, NULL, 16);
	m_address.Format(_T("%x"),PhysAddr64);
    UINT32 PhysVal=0x0;
	GetPhysLong((PBYTE)PhysAddr64,(PDWORD)&PhysVal);
	m_value.Format(_T("%x"),PhysVal);
	UpdateData(false);
	return;
}

void CGPIO7111Dlg::OnBnClickedWrite()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int i=0;
	char charSource[20];
	size_t ilen=0;
	UINT64 PhysAddr64=0x0;

	memset(charSource, 0, sizeof(charSource));
	for(i=0;i<m_address.GetLength();i++)
	{
		charSource[i]=(char)m_address.GetAt(i);
	}
	ilen=strlen(charSource);
	for(i=0;i<ilen;i++)
	{
		if(charSource[i]>0)
		{
			PhysAddr64*=16;
			if(charSource[i]>'9')
			{
				if(charSource[i]>'F')
				{
					PhysAddr64+=(charSource[i]-'a'+10);
				}
				else
				{
					PhysAddr64+=(charSource[i]-'A'+10);
				}
			}
			else
			{
				PhysAddr64+=(charSource[i]-'0');
			}
		}
	}
//	UINT64 PhysAddr64=strtol(charSource, NULL, 16);
	m_address.Format(_T("%x"),PhysAddr64);
    UINT32 PhysVal=0x0;
	memset(charSource, 0, sizeof(charSource));
	for(i=0;i<m_value.GetLength();i++)
	{
		charSource[i]=(char)m_value.GetAt(i);
	}
	ilen=strlen(charSource);
	for(i=0;i<ilen;i++)
	{
		if(charSource[i]>0)
		{
			PhysVal*=16;
			if(charSource[i]>'9')
			{
				if(charSource[i]>'F')
				{
					PhysVal+=(charSource[i]-'a'+10);
				}
				else
				{
					PhysVal+=(charSource[i]-'A'+10);
				}
			}
			else
			{
				PhysVal+=(charSource[i]-'0');
			}
		}
	}
	SetPhysLong((PBYTE)PhysAddr64,PhysVal);
	GetPhysLong((PBYTE)PhysAddr64,(PDWORD)&PhysVal);
	m_value.Format(_T("%x"),PhysVal);
	UpdateData(false);
	return;
}

void CGPIO7111Dlg::OnBnClickedAdvance()
{
	// TODO: Add your control notification handler code here
	if(m_advance.GetCheck())
	{
		m_addressctl.ShowWindow(SW_SHOWNORMAL);
		m_valuectl.ShowWindow(SW_SHOWNORMAL);
		m_readctl.ShowWindow(SW_SHOWNORMAL);
		m_writectl.ShowWindow(SW_SHOWNORMAL);
		m_recheck.ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		m_addressctl.ShowWindow(SW_HIDE);
		m_valuectl.ShowWindow(SW_HIDE);
		m_readctl.ShowWindow(SW_HIDE);
		m_writectl.ShowWindow(SW_HIDE);
		m_recheck.ShowWindow(SW_HIDE);
	}
}

void CGPIO7111Dlg::OnBnClickedRecheck()
{
	// TODO: Add your control notification handler code here
	if(m_recheck.GetCheck())
	{
		m_pullhigh1.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh2.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh3.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh4.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh5.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh6.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh7.ShowWindow(SW_SHOWNORMAL);
		m_pullhigh8.ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		m_pullhigh1.ShowWindow(SW_HIDE);
		m_pullhigh2.ShowWindow(SW_HIDE);
		m_pullhigh3.ShowWindow(SW_HIDE);
		m_pullhigh4.ShowWindow(SW_HIDE);
		m_pullhigh5.ShowWindow(SW_HIDE);
		m_pullhigh6.ShowWindow(SW_HIDE);
		m_pullhigh7.ShowWindow(SW_HIDE);
		m_pullhigh8.ShowWindow(SW_HIDE);
	}
}

void CGPIO7111Dlg::OnChangeDescription(int gpio)
{
	int outputstatus=0;
	int IOdirection=0;
	UINT64 PhysAddr64=0x0;
	UINT32 PhysVal=0x0;
	CString description=_T("");
	PhysAddr64=Get_GPIO_PHYSAddress(gpio);
#ifdef RDTEST
	description.Format(_T("%p"),PhysAddr64);
	GetPhysLong((PBYTE)PhysAddr64,(PDWORD)&PhysVal);
	CString secdescription=_T("");
	secdescription.Format(_T(",%p"),PhysVal);
	description+=secdescription;
	GetPhysLong((PBYTE)PhysAddr64+8,(PDWORD)&PhysVal);
	secdescription.Format(_T(",%04x"),PhysVal);
	description+=secdescription;
	switch(gpio)
	{
		case 1:
			outputstatus=m_pullhigh1.GetCheck();
			IOdirection=m_direction1.GetCheck();
			m_description1.SetWindowTextW(description);
			break;
		case 2:
			outputstatus=m_pullhigh2.GetCheck();
			IOdirection=m_direction2.GetCheck();
			m_description2.SetWindowTextW(description);
			break;
		case 3:
			outputstatus=m_pullhigh3.GetCheck();
			IOdirection=m_direction3.GetCheck();
			m_description3.SetWindowTextW(description);
			break;
		case 4:
			outputstatus=m_pullhigh4.GetCheck();
			IOdirection=m_direction4.GetCheck();
			m_description4.SetWindowTextW(description);
			break;
		case 5:
			outputstatus=m_pullhigh5.GetCheck();
			IOdirection=m_direction5.GetCheck();
			m_description5.SetWindowTextW(description);
			break;
		case 6:
			outputstatus=m_pullhigh6.GetCheck();
			IOdirection=m_direction6.GetCheck();
			m_description6.SetWindowTextW(description);
			break;
		case 7:
			outputstatus=m_pullhigh7.GetCheck();
			IOdirection=m_direction7.GetCheck();
			m_description7.SetWindowTextW(description);
			break;
		case 8:
			outputstatus=m_pullhigh8.GetCheck();
			IOdirection=m_direction8.GetCheck();
			m_description8.SetWindowTextW(description);
			break;
		default:
			return;
			break;
	}
#else
	switch(gpio)
	{
		case 1:
//			description=_T("CN2:pin03");
			outputstatus=m_pullhigh1.GetCheck();
			IOdirection=m_direction1.GetCheck();
			description.Format(_T("CN2:pin03 %08x"),PhysAddr64);
			m_description1.SetWindowTextW(description);
			break;
		case 2:
//			description=_T("CN2:pin04");
			outputstatus=m_pullhigh2.GetCheck();
			IOdirection=m_direction2.GetCheck();
			description.Format(_T("CN2:pin04 %08x"),PhysAddr64);
			m_description2.SetWindowTextW(description);
			break;
		case 3:
//			description=_T("CN2:pin05");
			outputstatus=m_pullhigh3.GetCheck();
			IOdirection=m_direction3.GetCheck();
			description.Format(_T("CN2:pin05 %08x"),PhysAddr64);
			m_description3.SetWindowTextW(description);
			break;
		case 4:
//			description=_T("CN2:pin06");
			outputstatus=m_pullhigh4.GetCheck();
			IOdirection=m_direction4.GetCheck();
			description.Format(_T("CN2:pin06 %08x"),PhysAddr64);
			m_description4.SetWindowTextW(description);
			break;
		case 5:
//			description=_T("CN2:pin07");
			outputstatus=m_pullhigh5.GetCheck();
			IOdirection=m_direction5.GetCheck();
			description.Format(_T("CN2:pin07 %08x"),PhysAddr64);
			m_description5.SetWindowTextW(description);
			break;
		case 6:
//			description=_T("CN2:pin08");
			outputstatus=m_pullhigh6.GetCheck();
			IOdirection=m_direction6.GetCheck();
			description.Format(_T("CN2:pin08 %08x"),PhysAddr64);
			m_description6.SetWindowTextW(description);
			break;
		case 7:
//			description=_T("CN2:pin09");
			outputstatus=m_pullhigh7.GetCheck();
			IOdirection=m_direction7.GetCheck();
			description.Format(_T("CN2:pin09 %08x"),PhysAddr64);
			m_description7.SetWindowTextW(description);
			break;
		case 8:
//			description=_T("CN2:pin10");
			outputstatus=m_pullhigh8.GetCheck();
			IOdirection=m_direction8.GetCheck();
			description.Format(_T("CN2:pin10 %08x"),PhysAddr64);
			m_description8.SetWindowTextW(description);
			break;
		default:
			return;
			break;
	}
#endif
	return;
}
void CGPIO7111Dlg::OnBnClickedDriectionOutput1()
{
	// TODO: Add your control notification handler code here
	if(m_direction1.GetCheck())
		m_direction1.SetWindowTextW(_T("GPIO 09 Output"));
	else
		m_direction1.SetWindowTextW(_T("GPIO 09 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput2()
{
	// TODO: Add your control notification handler code here
	if(m_direction2.GetCheck())
		m_direction2.SetWindowTextW(_T("GPIO 10 Output"));
	else
		m_direction2.SetWindowTextW(_T("GPIO 10 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput3()
{
	// TODO: Add your control notification handler code here
	if(m_direction3.GetCheck())
		m_direction3.SetWindowTextW(_T("GPIO 17 Output"));
	else
		m_direction3.SetWindowTextW(_T("GPIO 17 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput4()
{
	// TODO: Add your control notification handler code here
	if(m_direction4.GetCheck())
		m_direction4.SetWindowTextW(_T("GPIO 26 Output"));
	else
		m_direction4.SetWindowTextW(_T("GPIO 26 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput5()
{
	// TODO: Add your control notification handler code here
	if(m_direction5.GetCheck())
		m_direction5.SetWindowTextW(_T("GPIO 04 Output"));
	else
		m_direction5.SetWindowTextW(_T("GPIO 04 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput6()
{
	// TODO: Add your control notification handler code here
	if(m_direction6.GetCheck())
		m_direction6.SetWindowTextW(_T("GPIO 05 Output"));
	else
		m_direction6.SetWindowTextW(_T("GPIO 05 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput7()
{
	// TODO: Add your control notification handler code here
	if(m_direction7.GetCheck())
		m_direction7.SetWindowTextW(_T("GPIO 06 Output"));
	else
		m_direction7.SetWindowTextW(_T("GPIO 06 Input"));
}

void CGPIO7111Dlg::OnBnClickedDriectionOutput8()
{
	// TODO: Add your control notification handler code here
	if(m_direction8.GetCheck())
		m_direction8.SetWindowTextW(_T("GPIO 08 Output"));
	else
		m_direction8.SetWindowTextW(_T("GPIO 08 Input"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh1()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh1.GetCheck())
		m_pullhigh1.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh1.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh2()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh2.GetCheck())
		m_pullhigh2.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh2.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh3()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh3.GetCheck())
		m_pullhigh3.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh3.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh4()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh4.GetCheck())
		m_pullhigh4.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh4.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh5()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh5.GetCheck())
		m_pullhigh5.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh5.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh6()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh6.GetCheck())
		m_pullhigh6.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh6.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh7()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh7.GetCheck())
		m_pullhigh7.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh7.SetWindowTextW(_T("Pull low"));
}

void CGPIO7111Dlg::OnBnClickedPullHigh8()
{
	// TODO: Add your control notification handler code here
	if(m_pullhigh8.GetCheck())
		m_pullhigh8.SetWindowTextW(_T("Pull high"));
	else
		m_pullhigh8.SetWindowTextW(_T("Pull low"));
}
