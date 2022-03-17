; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRoboticGridView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RoboticGrid.h"
LastPage=0

ClassCount=6
Class1=CRoboticGridApp
Class2=CRoboticGridDoc
Class3=CRoboticGridView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CSetSizeDlg
Resource3=IDD_SIZE_DLG

[CLS:CRoboticGridApp]
Type=0
HeaderFile=RoboticGrid.h
ImplementationFile=RoboticGrid.cpp
Filter=N

[CLS:CRoboticGridDoc]
Type=0
HeaderFile=RoboticGridDoc.h
ImplementationFile=RoboticGridDoc.cpp
Filter=N

[CLS:CRoboticGridView]
Type=0
HeaderFile=RoboticGridView.h
ImplementationFile=RoboticGridView.cpp
Filter=W
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_GRID_SAVENET


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_GRID_CREATE




[CLS:CAboutDlg]
Type=0
HeaderFile=RoboticGrid.cpp
ImplementationFile=RoboticGrid.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_GRID_INIT
Command18=ID_GRID_CREATE
Command19=ID_GRID_SAVENET
Command20=ID_GRID_CALC
Command21=ID_GRID_SHOW
Command22=ID_GRID_QUERY
Command23=ID_HEX_INIT
Command24=ID_HEX_CREATE
Command25=ID_HEX_CREATENET
Command26=ID_HEX_CALC
Command27=ID_HEX_SHOW
Command28=ID_HEX_QUERY
Command29=ID_MAP_SHOWOR
Command30=ID_MAP_ZOOMIN
Command31=ID_MAP_ZOOMOUT
Command32=ID_MAP_PAN
Command33=ID_MAP_FULL
Command34=ID_MAP_CALC
Command35=ID_ANALYSE_ADD
Command36=ID_ANALYSE_EXEC
Command37=ID_ANALYSE_CLEAR
CommandCount=37

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_SIZE_DLG]
Type=1
Class=CSetSizeDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_EDIT_SIZE,edit,1350631552

[CLS:CSetSizeDlg]
Type=0
HeaderFile=SetSizeDlg.h
ImplementationFile=SetSizeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_SIZE
VirtualFilter=dWC

