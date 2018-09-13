; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGMineDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gMine.h"

ClassCount=3
Class1=CGMineApp
Class2=CGMineDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_GMINE_DIALOG

[CLS:CGMineApp]
Type=0
HeaderFile=gMine.h
ImplementationFile=gMine.cpp
Filter=N

[CLS:CGMineDlg]
Type=0
HeaderFile=gMineDlg.h
ImplementationFile=gMineDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDT_DATA

[CLS:CAboutDlg]
Type=0
HeaderFile=gMineDlg.h
ImplementationFile=gMineDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GMINE_DIALOG]
Type=1
Class=CGMineDlg
ControlCount=6
Control1=IDC_EDT_DATA,edit,1353777156
Control2=IDC_BTN_READ,button,1342242816
Control3=IDC_BTN_RCLICKFIRST,button,1342242816
Control4=IDC_BTN_RCLICKALLMINE,button,1342242816
Control5=IDC_BTN_LCLICKALLNOMINE,button,1342242816
Control6=IDC_STATIC,static,1342308352

