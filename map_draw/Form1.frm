VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11460
   BeginProperty Font 
      Name            =   "Times New Roman"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   6510
   ScaleWidth      =   11460
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command9 
      Caption         =   "重新开始绘制路径"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1560
      TabIndex        =   39
      Top             =   5640
      Width           =   1455
   End
   Begin VB.CommandButton Command8 
      Caption         =   "路径记录"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   38
      Top             =   5040
      Width           =   1215
   End
   Begin VB.CommandButton Command7 
      Caption         =   "退出程序"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   36
      Top             =   5640
      Width           =   1215
   End
   Begin VB.Timer Timer3 
      Interval        =   1000
      Left            =   5040
      Top             =   600
   End
   Begin VB.CommandButton Command6 
      Caption         =   "开始绘制地图"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1560
      TabIndex        =   35
      Top             =   4440
      Width           =   1335
   End
   Begin VB.Timer Timer2 
      Interval        =   200
      Left            =   4560
      Top             =   600
   End
   Begin VB.CommandButton Command5 
      Caption         =   "显示小车轨迹"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   34
      Top             =   4440
      Width           =   1215
   End
   Begin VB.TextBox Text13 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2160
      TabIndex        =   33
      Top             =   3840
      Width           =   1215
   End
   Begin VB.TextBox Text12 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   600
      TabIndex        =   31
      Top             =   3840
      Width           =   1095
   End
   Begin VB.TextBox Text11 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2160
      TabIndex        =   29
      Top             =   3360
      Width           =   1215
   End
   Begin VB.TextBox Text10 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   600
      TabIndex        =   27
      Top             =   3360
      Width           =   1095
   End
   Begin VB.TextBox Text9 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2160
      TabIndex        =   25
      Top             =   2880
      Width           =   1215
   End
   Begin VB.TextBox Text8 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   600
      TabIndex        =   23
      Top             =   2880
      Width           =   1095
   End
   Begin VB.TextBox Text7 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2160
      TabIndex        =   21
      Top             =   2400
      Width           =   1215
   End
   Begin VB.TextBox Text6 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   600
      TabIndex        =   19
      Top             =   2400
      Width           =   1095
   End
   Begin VB.CommandButton Command4 
      Caption         =   "确定保存当前点位置"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   17
      Top             =   1800
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
      Caption         =   "hook"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   16
      Top             =   1320
      Width           =   1095
   End
   Begin VB.TextBox Text5 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2760
      TabIndex        =   13
      Top             =   120
      Width           =   1335
   End
   Begin VB.TextBox Text4 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   840
      TabIndex        =   12
      Top             =   120
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   500
      Left            =   4560
      Top             =   120
   End
   Begin VB.CommandButton Command2 
      Caption         =   "请选择画笔颜色"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   4440
      TabIndex        =   11
      Top             =   3000
      Width           =   1935
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   4800
      TabIndex        =   9
      Top             =   1800
      Width           =   975
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   375
      Left            =   3840
      TabIndex        =   7
      Top             =   1320
      Width           =   3135
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   5040
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2295
      Left            =   7080
      ScaleHeight     =   2235
      ScaleWidth      =   3795
      TabIndex        =   5
      Top             =   120
      Width           =   3855
   End
   Begin VB.TextBox Text3 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2760
      TabIndex        =   2
      Top             =   720
      Width           =   1335
   End
   Begin VB.TextBox Text2 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   840
      TabIndex        =   1
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "unhook"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   1320
      Width           =   1335
   End
   Begin VB.Label Label16 
      Caption         =   "开始绘制地图以前，请先钩住鼠标"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1560
      TabIndex        =   37
      Top             =   5040
      Width           =   1575
   End
   Begin VB.Label Label15 
      Caption         =   "Y4:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   32
      Top             =   3840
      Width           =   375
   End
   Begin VB.Label Label14 
      Caption         =   "X4:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   30
      Top             =   3840
      Width           =   375
   End
   Begin VB.Label Label13 
      Caption         =   "Y3:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   28
      Top             =   3360
      Width           =   375
   End
   Begin VB.Label Label12 
      Caption         =   "X3:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   26
      Top             =   3360
      Width           =   375
   End
   Begin VB.Label Label11 
      Caption         =   "Y2:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   24
      Top             =   2880
      Width           =   375
   End
   Begin VB.Label Label10 
      Caption         =   "X2:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   22
      Top             =   2880
      Width           =   375
   End
   Begin VB.Label Label9 
      Caption         =   "Y1:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   20
      Top             =   2400
      Width           =   375
   End
   Begin VB.Label Label8 
      Caption         =   "X1:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   18
      Top             =   2400
      Width           =   375
   End
   Begin VB.Label Label7 
      Caption         =   "Y:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2160
      TabIndex        =   15
      Top             =   120
      Width           =   495
   End
   Begin VB.Label Label6 
      Caption         =   "X:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   14
      Top             =   120
      Width           =   495
   End
   Begin VB.Label Label5 
      Caption         =   "按下鼠标左键画图，按下鼠标右键擦除"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   4440
      TabIndex        =   10
      Top             =   2520
      Width           =   1815
   End
   Begin VB.Label Label4 
      Caption         =   "线条宽度："
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3600
      TabIndex        =   8
      Top             =   1920
      Width           =   975
   End
   Begin VB.Label Label3 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   6240
      TabIndex        =   6
      Top             =   1920
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "SY:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2160
      TabIndex        =   4
      Top             =   720
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "SX:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   3
      Top             =   720
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Dim x0, y0, x1, y1 As Double
Dim x11, y11, Y2 As Double
Dim scalex1, scaley1, dx, dy As Double
Dim coord(0 To 5) As Double

Dim index, index1 As Integer
Dim coordcount As Integer
Dim xmax, ymax, xmin, ymin As Double
Dim l1, l2, l3, l4, r1, r2, r3, r4 As Double
Dim temp1, temp2 As Double
Dim trace As Integer
Dim disx, disy As Double
Dim testx1, testy1, testx2, testy2 As Double

Private Sub Command1_Click()
Timer3.Enabled = False
Call DelHook
MsgBox "鼠标已释放"
End Sub


'用“通用颜色对话框”设置画笔颜色：
 
Private Sub Command2_Click()
  CommonDialog1.ShowColor
  Label3.BackColor = CommonDialog1.Color
End Sub


Private Sub Command3_Click()
    hHook = SetWindowsHookEx(WH_MOUSE_LL, AddressOf MouseHookProc, App.hInstance, 0)
    If hHook <> 0 Then
        MsgBox "已钩住鼠标事件，请按本窗体右上方的X按钮关闭窗体，不要使用VB调试工具栏的“结束”按钮，以免VB崩溃"
    End If
End Sub

Private Sub Command4_Click()

Dim scalepx As Double
Dim scalepy As Double

coordcount = coordcount + 1
If (coordcount = 1) Then
    Text6.Text = Text4.Text
    Text7.Text = Text5.Text
    MsgBox "saveok!"
'    Text6.Text = 3435825.33 '1 '
'    Text7.Text = 351794.33 '4 '
ElseIf (coordcount = 2) Then
    Text8.Text = Text4.Text
    Text9.Text = Text5.Text
    MsgBox "saveok!"
'    Text8.Text = 3435819.97 '3 '
'    Text9.Text = 351790.59 '5 '
ElseIf (coordcount = 3) Then
    Text10.Text = Text4.Text
    Text11.Text = Text5.Text
    MsgBox "saveok!"
'    Text10.Text = 3435816.81 '4 '
'    Text11.Text = 351792.56 '0 '
ElseIf (coordcount = 4) Then
    coordcount = 0
    Text12.Text = Text4.Text
    Text13.Text = Text5.Text
    MsgBox "saveok!"
'    Text12.Text = 3435819.97 '2 '
'    Text13.Text = 351799.33 '1 '
    
    Command4.Enabled = False
    
    If ((Val(Text6) > Val(Text8)) Or (Val(Text6) = Val(Text8))) Then
        xmax = Val(Text6)
    Else
        xmax = Val(Text8)
    End If
    If ((Val(Text10) > xmax) Or (Val(Text10) = xmax)) Then
        xmax = Val(Text10)
    End If
    If ((Val(Text12) > xmax) Or (Val(Text12) = xmax)) Then
        xmax = Val(Text12)
    End If
    
    If ((Val(Text6) < Val(Text8))) Then
        xmin = Val(Text6)
    Else
        xmin = Val(Text8)
    End If
    If ((Val(Text10) < xmin)) Then
        xmin = Val(Text10)
    End If
    If ((Val(Text12) < xmin)) Then
        xmin = Val(Text12)
    End If
    
    
    
    If ((Val(Text7) > Val(Text9)) Or (Val(Text7) = Val(Text9))) Then
        ymax = Val(Text7)
    Else
        ymax = Val(Text9)
    End If
    If ((Val(Text11) > ymax) Or (Val(Text11) = ymax)) Then
        ymax = Val(Text11)
    End If
    If ((Val(Text13) > ymax) Or (Val(Text13) = ymax)) Then
        ymax = Val(Text13)
    End If
    
    If ((Val(Text7) < Val(Text9))) Then
        ymin = Val(Text7)
    Else
        ymin = Val(Text9)
    End If
    If ((Val(Text11) < ymin)) Then
        ymin = Val(Text11)
    End If
    If ((Val(Text13) < ymin)) Then
        ymin = Val(Text13)
    End If
    
    
    scalex1 = (xmax - xmin) / 300 '每像素代表多少米
    scaley1 = (ymax - ymin) / 300
    
    
    l1 = (Val(Text6) - xmin) / scalex1
    l2 = (Val(Text8) - xmin) / scalex1
    l3 = (Val(Text10) - xmin) / scalex1
    l4 = (Val(Text12) - xmin) / scalex1
    
    scalepx = scalex1 * 10

    r1 = (Val(Text7) - ymin) / scaley1
    r2 = (Val(Text9) - ymin) / scaley1
    r3 = (Val(Text11) - ymin) / scaley1
    r4 = (Val(Text13) - ymin) / scaley1
    
    scalepy = scaley1 * 10


    testx1 = (3435823.72954872 - xmin) / scalex1
    testy1 = (351797.626639576 - ymin) / scaley1
    testx2 = (3435820.34795053 - xmin) / scalex1
    testy2 = (351793.568090489 - ymin) / scaley1
    
    
    Form1.Picture1.DrawWidth = 2
    Form1.Picture1.Line (220, 10)-(230, 10), RGB(0, 0, 0) 'x比例尺
    Form1.Picture1.CurrentX = 230
    Form1.Picture1.CurrentY = 5
    Form1.Picture1.Print FormatNumber(scalepx, 2, vbTrue) & "m/10pix"
    
    Form1.Picture1.Line (220, 10)-(220, 20), RGB(0, 0, 0) 'y比例尺
    Form1.Picture1.CurrentX = 220
    Form1.Picture1.CurrentY = 20
    Form1.Picture1.Print FormatNumber(scalepy, 2, vbTrue) & "m/10pix"
    
'    Form1.Picture1.Line (240, 260)-(260, 260), RGB(0, 0, 0)  'x坐标
    Form1.Picture1.CurrentX = 10
    Form1.Picture1.CurrentY = 10
    Form1.Picture1.Print "→" & "ｘ"
    
'    Form1.Picture1.Line (240, 260)-(240, 280), RGB(0, 0, 0)   'ｙ坐标
    Form1.Picture1.CurrentX = 5
    Form1.Picture1.CurrentY = 15
    Form1.Picture1.Print "↓"
    Form1.Picture1.CurrentX = 5
    Form1.Picture1.CurrentY = 25
    Form1.Picture1.Print "ｙ"

    Form1.Picture1.DrawWidth = 5
    Form1.Picture1.Line (testx1, testy1)-(testx1, testy1), RGB(0, 255, 0) '门
    Form1.Picture1.Line (testx2, testy2)-(testx2, testy2), RGB(255, 0, 0) '440窗
    Form1.Picture1.DrawWidth = 2
    Form1.Picture1.Line (testx1, testy1)-(testx2, testy2), RGB(0, 0, 0) '440窗

'    '标注各点
'    Form1.Picture1.DrawWidth = 5
'    Form1.Picture1.Line (l1, r1)-(l1, r1), RGB(0, 0, 255)
'
'    Form1.Picture1.Line (l2, r2)-(l2, r2), RGB(0, 0, 255)
'
'    Form1.Picture1.Line (l3, r3)-(l3, r3), RGB(0, 0, 255)
'
'    Form1.Picture1.Line (l4, r4)-(r4, r4), RGB(0, 0, 255)
    
    '标注范围
    
    Form1.Picture1.DrawWidth = 5
    Form1.Picture1.Line (l1, r1)-(l2, r2), RGB(255, 0, 0)

    Form1.Picture1.Line (l2, r2)-(l3, r3), RGB(255, 0, 0)

    Form1.Picture1.Line (l3, r3)-(l4, r4), RGB(255, 0, 0)

    Form1.Picture1.Line (l4, r4)-(l1, r1), RGB(255, 0, 0)
    

'    Form1.Picture1.Line (3435820.34795053, 351793.568090489)-(3435820.34795053, 351793.568090489), RGB(0, 255, 0) '窗
End If
End Sub

Private Sub Command5_Click()

    
    temp1 = Val(Text4)
    temp2 = Val(Text5)
    trace = 1
    MsgBox "ok!"
End Sub

Private Sub Command6_Click()
    Form1.Picture1.DrawWidth = 3
    Timer3.Enabled = True
    MsgBox "准备开始绘制地图，请钩住鼠标"
    Timer3.Enabled = True
    startmap = 1
End Sub

Private Sub Command7_Click()
    Unload Form1
End Sub

Private Sub Command8_Click()
    
    Open "d:\path.txt" For Append As #2   '数据以追加写的方式写入文件
    Do While coord1(index1) <> 0

        coord1(index1) = coord1(index1) * scalex1 + xmin
        index1 = index1 + 1
        coord1(index1) = coord1(index1) * scaley1 + ymin
        index1 = index1 + 1

'    Open "d:\\path.txt" For Output As #2
'    Open "d:\path.txt" For Append As #2   '数据以追加写的方式写入文件
    'If ((Text6.Text <> "") And (Text7.Text <> "")) Then
        Print #2, Str(coord1(index1 - 2)) & vbCrLf
        Print #2, Str(coord1(index1 - 1)) & vbCrLf

'        index1 = 0
'    Print #3, buf
    Loop
    Close #2
    
'    index = 0
    index1 = 0
    index2 = 0
    
    MsgBox "filewriteok!"
End Sub

Private Sub Command9_Click()
Dim k As Integer

Kill "d:\path.txt"
Open "d:\path.txt" For Output As #2
Close #2


For k = 0 To 50
    coord1(k) = 0
Next k

count1 = 0
MsgBox "resetok!"

End Sub

Private Sub Form_load()
    
    Timer3.Enabled = False
    
    Open "d:\carcoord.txt" For Output As #1
    Open "d:\path.txt" For Output As #2
    Close #1
    Close #2
    
    Form1.AutoRedraw = True
    Form1.ScaleMode = 3
    Form1.WindowState = 2
    Form1.BorderStyle = 0
'    hHook = SetWindowsHookEx(WH_MOUSE_LL, AddressOf MouseHookProc, App.hInstance, 0)
'    If hHook <> 0 Then
'        MsgBox "已钩住鼠标事件，请按本窗体右上方的X按钮关闭窗体，不要使用VB调试工具栏的“结束”按钮，以免VB崩溃"
'    End If
    
    
    
    Picture1.AutoRedraw = True
    Picture1.ScaleMode = 3
    Picture1.Height = 300
    Picture1.Width = 300
    
    
    Picture1.Left = 600
    Picture1.Top = 0
    Picture1.BorderStyle = 0
    
'    x0 = Picture1.ScaleLeft
'    y0 = Picture1.ScaleTop
'    x1 = Picture1.ScaleLeft + Picture1.ScaleWidth
'    y1 = Picture1.ScaleTop + Picture1.ScaleHeight
'
'    Print x0
'    Print y0
'    Print x1
'    Print y1

    
    Picture1.BackColor = RGB(255, 255, 255)    '将图片框的背景色设置为白色
    Picture1.BackColor = RGB(255, 255, 255)
    Label3.BackColor = RGB(0, 0, 0)
    
'    Image1.Picture = LoadPicture("d:\Red.bmp")
    
'    Form1.DrawWidth = 5
'    Picture1.Line (10, 30)-(Text2.Text, Text3.Text), RGB(255, 0, 0)

'    Picture1.ScaleMode = 0
'    Picture1.AutoSize = True:
'    Picture1.AutoRedraw = True
   
'    Picture1.Picture = LoadPicture("d:\\1-130I1214G12R.jpg")
   
   
   
'    Picture1.CurrentX = 5: Picture1.CurrentY = 5
   
'    Picture1.ScaleLeft = 15
'    Picture1.ScaleTop = 15
'    Picture1.ScaleWidth = 10
'    Picture1.ScaleHeight = 10
'    Print "当前鼠标位置-x:" & oMouseHookStruct.pt.x & "; y:" & oMouseHookStruct.pt.y
'    Print "hi"
End Sub

Private Sub HScroll1_Change()
 Text1.Text = HScroll1.Value               '将水平滚动条的属性值显示在文本框内
End Sub

Public Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If UnloadMode = 0 Then
    Call DelHook
    End
    End If
End Sub

Public Sub DelHook()
   UnhookWindowsHookEx (hHook)
End Sub




'Private Sub Form_Click()
'  Cls
'  Form1.ScaleLeft = -15
'  Form1.ScaleTop = 15
'  Form1.ScaleWidth = 30
'  Form1.ScaleHeight = -30
'  Line (-15, 0)-(15, 0)
'  Line (0, 15)-(0, -15)
'  CurrentX = 0: CurrentY = 0: Print 0
'  CurrentX = 14: CurrentY = 2: Print "X"
'  CurrentX = 0.5: CurrentY = 14: Print "Y"
'End Sub



Private Sub Picture1_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
'    Picture1.DrawWidth = HScroll1.Value + 1
    Picture1.DrawWidth = 3
    Picture1.ForeColor = CommonDialog1.Color
 
       If Button = 1 Then
         Picture1.PSet (x, y)
       End If
      
       If Button = 2 Then
         Picture1.DrawWidth = 20
         Picture1.ForeColor = RGB(255, 255, 255)
         Picture1.PSet (x, y)
       End If
'    '该句用于描绘小车的路径，验证过，没问题的
'    Form1.Picture1.Line (10, 50)-(800, 200), RGB(255, 0, 0)
'    Picture1.Line (700, 30)-(900, 30), RGB(255, 0, 0)
 
End Sub





Private Sub Timer1_Timer()



'scalex1 = 0.01
'scaley1 = 0.01

'scalex1 = (xmax - xmin) / 300 '每像素代表多少米
'scaley1 = (ymax - ymin) / 300

'这段话可以标注小车当前的位置，自己到自己就是一个点，只要把线宽调宽
'Form1.Picture1.DrawWidth = 9
'Form1.Picture1.Line (2, 2)-(2, 2), RGB(0, 0, 255)
'l1 = (Val(Text6) - xmin) * scalex1
'l2 = (Val(Text8) - xmin) * scalex1
'l3 = (Val(Text10) - xmin) * scalex1
'l4 = (Val(Text12) - xmin) * scalex1
'
'r1 = (Val(Text7) - ymin) * scaley1
'r2 = (Val(Text9) - ymin) * scaley1
'r3 = (Val(Text11) - ymin) * scaley1
'r4 = (Val(Text13) - ymin) * scaley1
'
'Form1.Picture1.DrawWidth = 9
'Form1.Picture1.Line (l1, r1)-(l1, r1), RGB(0, 0, 255)
'
'Form1.Picture1.Line (l2, r2)-(l2, r2), RGB(0, 0, 255)
'
'Form1.Picture1.Line (l3, r3)-(l3, r3), RGB(0, 0, 255)
'
'Form1.Picture1.Line (l4, r4)-(r4, r4), RGB(0, 0, 255)

Dim aas As String

Open "d:\\carcoord.txt" For Input As #1
Do While Not EOF(1) '
Line Input #1, aas

'x = Val(aas)  '每次读数据出来，经度在前，纬度在后
'y11 = Val(bs)
'Y2 = Val(cs)

coord(index) = Val(aas)
index = index + 1


'lng = Val(Text4.Text)
'lat = Val(Text3.Text)

'调用经纬度解析函数直接算出平面坐标
'Call GaussProjCal(lng, lat, x1, y1)


'Text6.Text = Str(x1)
'Text7.Text = Str(y1)
'
'coord(i) = x1
'i = i + 1
'coord(i) = Y1
'i = i + 1
'Label4.Caption = "X1=" & coord(0) & "Y1=" & coord(1)
Loop
'先把这句话注释掉，调好了再打开
Text4.Text = coord(0)
Text5.Text = coord(2)


'If (trace = 1) Then
''    If ((Text4.Text <> "") And (Text5.Text <> "")) Then
''        dx = (Val(Text4) - temp1) / scalex1
''        dy = (Val(Text5) - temp2) / scaley1
'''    dx = (coord(0) - 3430000) * scalex1
'''    dy = (coord(2) - 350000) * scaley1
''    End If
'
'
'    disx = (temp1 - xmin) / scalex1
'    disy = (temp2 - ymin) / scaley1
'
'    '标注小车路径
'    If ((temp1 <> 0) And (temp2 <> 0)) Then
'        Form1.Picture1.DrawWidth = 10
'        Form1.Picture1.Line (disx, disy)-(disx, disy), RGB(0, 0, 255)
'    End If
'    temp1 = Val(Text4)
'    temp2 = Val(Text5)
'End If
'If ((Text4.Text <> "") And (Text5.Text <> "")) Then
'    dx = (coord(0) - Text4.Text) * scalex1
'    dy = (coord(2) - Text5.Text) * scaley1
'    dx = (coord(0) - 3430000) * scalex1
'    dy = (coord(2) - 350000) * scaley1
'End If






index = 0
Close #1 ' 关闭文件
End Sub

Private Sub Timer2_Timer()

If (trace = 1) Then
'    If ((Text4.Text <> "") And (Text5.Text <> "")) Then
'        dx = (Val(Text4) - temp1) / scalex1
'        dy = (Val(Text5) - temp2) / scaley1
''    dx = (coord(0) - 3430000) * scalex1
''    dy = (coord(2) - 350000) * scaley1
'    End If
    
    
    disx = (temp1 - xmin) / scalex1
    disy = (temp2 - ymin) / scaley1
    
    '标注小车路径
    If ((temp1 <> 0) And (temp2 <> 0)) Then
        Form1.Picture1.DrawWidth = 10
        Form1.Picture1.Line (disx, disy)-(disx, disy), RGB(0, 0, 255)
    End If
    temp1 = Val(Text4)
    temp2 = Val(Text5)
End If

End Sub

'Private Sub Timer3_Timer()
''只有当横纵轴坐标都大于零时才认为是有效数据,写入文件
'If ((Val(Text2) > 0) And (Val(Text2) < 300) And (Val(Text3) > 0) And (Val(Text3) < 300) And (recordok = 1)) Then
''If ((Val(Text2) > 0) And (Val(Text3) > 0) And (recordok = 1)) Then
'    coord1(index1) = Val(Text2) * scalex1 + xmin
'    index1 = index1 + 1
'    coord1(index1) = Val(Text3) * scaley1 + ymin
''    index1 = index1 + 1
'
''    Open "d:\\path.txt" For Output As #2
'    Open "d:\path.txt" For Append As #2   '数据以追加写的方式写入文件
'    'If ((Text6.Text <> "") And (Text7.Text <> "")) Then
'        Print #2, Str(coord1(index1 - 1)) & vbCrLf
'        Print #2, Str(coord1(index1)) & vbCrLf
'
'        index1 = 0
''    Print #3, buf
''    End If
'    Close #2
'End If
'End Sub

