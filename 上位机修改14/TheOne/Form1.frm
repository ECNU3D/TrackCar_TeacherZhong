VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "ieframe.dll"
Begin VB.Form Form1 
   Caption         =   "GoogleMap"
   ClientHeight    =   11010
   ClientLeft      =   60
   ClientTop       =   465
   ClientWidth     =   15240
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   11010
   ScaleWidth      =   15240
   Begin VB.TextBox Text12 
      Height          =   375
      Left            =   12600
      TabIndex        =   46
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Timer Timer5 
      Interval        =   200
      Left            =   12240
      Top             =   3120
   End
   Begin VB.PictureBox Picture2 
      Height          =   3015
      Left            =   8400
      ScaleHeight     =   2955
      ScaleWidth      =   3795
      TabIndex        =   44
      Top             =   6360
      Width           =   3855
   End
   Begin VB.TextBox Text11 
      Height          =   735
      Left            =   6600
      TabIndex        =   42
      Top             =   6960
      Width           =   1575
   End
   Begin VB.TextBox Text10 
      Height          =   735
      Left            =   4920
      TabIndex        =   39
      Top             =   6960
      Width           =   1575
   End
   Begin VB.CommandButton Command19 
      Caption         =   "开始绘制地图"
      Height          =   495
      Left            =   8280
      TabIndex        =   38
      Top             =   5040
      Width           =   1095
   End
   Begin VB.CommandButton Command18 
      Caption         =   "手动制动"
      Height          =   495
      Left            =   9600
      TabIndex        =   37
      Top             =   4440
      Width           =   1335
   End
   Begin VB.Timer Timer4 
      Interval        =   6000
      Left            =   14280
      Top             =   3120
   End
   Begin VB.TextBox Text9 
      Height          =   270
      Left            =   13440
      TabIndex        =   31
      Top             =   2160
      Width           =   255
   End
   Begin VB.Timer Timer3 
      Interval        =   500
      Left            =   15000
      Top             =   5280
   End
   Begin VB.TextBox Text8 
      Height          =   375
      Left            =   13680
      TabIndex        =   30
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton Command17 
      Caption         =   "串口打开"
      Height          =   495
      Left            =   8280
      TabIndex        =   28
      Top             =   3840
      Width           =   975
   End
   Begin VB.TextBox Text7 
      Height          =   375
      Left            =   14280
      TabIndex        =   27
      Top             =   1200
      Width           =   1455
   End
   Begin VB.TextBox Text6 
      Height          =   375
      Left            =   14280
      TabIndex        =   26
      Top             =   840
      Width           =   1455
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   5775
      Left            =   360
      TabIndex        =   23
      Top             =   600
      Width           =   7695
      ExtentX         =   13573
      ExtentY         =   10186
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin VB.Timer Timer2 
      Interval        =   500
      Left            =   11520
      Top             =   960
   End
   Begin VB.CommandButton Command16 
      Caption         =   "十六进制发送"
      Height          =   615
      Left            =   10800
      TabIndex        =   22
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "hex显示"
      Height          =   255
      Left            =   11040
      TabIndex        =   21
      Top             =   1920
      Width           =   975
   End
   Begin VB.CommandButton Command15 
      Caption         =   "退出程序"
      Height          =   735
      Left            =   15360
      TabIndex        =   20
      Top             =   6720
      Width           =   1335
   End
   Begin VB.CommandButton Command8 
      Caption         =   "关闭串口"
      Height          =   495
      Left            =   9600
      TabIndex        =   18
      Top             =   3840
      Width           =   1335
   End
   Begin VB.CommandButton Command7 
      Caption         =   "发送字符"
      Height          =   495
      Left            =   10800
      TabIndex        =   17
      Top             =   3120
      Width           =   975
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   10920
      Top             =   960
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   0   'False
      RTSEnable       =   -1  'True
   End
   Begin VB.Timer Timer1 
      Interval        =   200
      Left            =   10920
      Top             =   480
   End
   Begin VB.TextBox Text2 
      Height          =   1095
      Left            =   8400
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   16
      Top             =   2640
      Width           =   2415
   End
   Begin VB.TextBox Text1 
      Height          =   1215
      Left            =   8280
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   15
      Top             =   600
      Width           =   2535
   End
   Begin VB.CommandButton Command14 
      Caption         =   "back"
      Height          =   495
      Left            =   13440
      TabIndex        =   13
      Top             =   4200
      Width           =   495
   End
   Begin VB.CommandButton Command13 
      Caption         =   "stop"
      Height          =   495
      Left            =   13440
      TabIndex        =   12
      Top             =   3720
      Width           =   495
   End
   Begin VB.CommandButton Command12 
      Caption         =   "left"
      Height          =   495
      Left            =   12840
      TabIndex        =   11
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command11 
      Caption         =   "right"
      Height          =   495
      Left            =   13920
      TabIndex        =   10
      Top             =   3720
      Width           =   615
   End
   Begin VB.CommandButton Command10 
      Caption         =   "go"
      Height          =   495
      Left            =   13440
      TabIndex        =   9
      Top             =   3240
      Width           =   495
   End
   Begin VB.TextBox Text5 
      Height          =   735
      Left            =   240
      TabIndex        =   8
      Top             =   6480
      Width           =   1335
   End
   Begin VB.PictureBox Picture1 
      Height          =   975
      Left            =   2040
      ScaleHeight     =   915
      ScaleWidth      =   1395
      TabIndex        =   7
      Top             =   7080
      Width           =   1455
   End
   Begin VB.CommandButton Command9 
      Caption         =   "路径坐标转换"
      Height          =   495
      Left            =   8280
      TabIndex        =   6
      Top             =   4440
      Width           =   1095
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   12600
      TabIndex        =   3
      Text            =   "000.0000"
      Top             =   1200
      Width           =   1095
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   12600
      TabIndex        =   2
      Text            =   "00.0000"
      Top             =   840
      Width           =   1095
   End
   Begin VB.CommandButton Command3 
      Caption         =   "清除标注"
      Height          =   495
      Left            =   13320
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "查找坐标"
      Height          =   495
      Left            =   12120
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label Label9 
      Caption         =   "m"
      Height          =   375
      Left            =   15840
      TabIndex        =   49
      Top             =   1320
      Width           =   855
   End
   Begin VB.Label Label6 
      Caption         =   "m"
      Height          =   375
      Left            =   15840
      TabIndex        =   48
      Top             =   840
      Width           =   735
   End
   Begin VB.Label Label20 
      Caption         =   "cm/s"
      Height          =   375
      Left            =   13800
      TabIndex        =   47
      Top             =   1560
      Width           =   615
   End
   Begin VB.Label Label19 
      Caption         =   "速度"
      Height          =   375
      Left            =   12120
      TabIndex        =   45
      Top             =   1680
      Width           =   495
   End
   Begin VB.Label Label18 
      Caption         =   "Pitch"
      Height          =   375
      Left            =   6600
      TabIndex        =   43
      Top             =   7800
      Width           =   735
   End
   Begin VB.Label Label17 
      Caption         =   "Roll"
      Height          =   375
      Left            =   4920
      TabIndex        =   41
      Top             =   7800
      Width           =   855
   End
   Begin VB.Label Label16 
      Caption         =   "Header"
      Height          =   375
      Left            =   240
      TabIndex        =   40
      Top             =   8160
      Width           =   855
   End
   Begin VB.Label Label15 
      Caption         =   "E"
      Height          =   375
      Left            =   4080
      TabIndex        =   36
      Top             =   7800
      Width           =   375
   End
   Begin VB.Label Label14 
      Caption         =   "W"
      Height          =   375
      Left            =   1680
      TabIndex        =   35
      Top             =   7800
      Width           =   375
   End
   Begin VB.Label Label13 
      Caption         =   "S"
      Height          =   255
      Left            =   2880
      TabIndex        =   34
      Top             =   9000
      Width           =   375
   End
   Begin VB.Label Label11 
      Caption         =   "N"
      Height          =   375
      Left            =   2880
      TabIndex        =   33
      Top             =   6720
      Width           =   375
   End
   Begin VB.Label Label4 
      Caption         =   "数据接收正常"
      Height          =   255
      Left            =   12120
      TabIndex        =   32
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Label Label12 
      Caption         =   "剩余电量："
      Height          =   375
      Left            =   12600
      TabIndex        =   29
      Top             =   5280
      Width           =   1095
   End
   Begin VB.Label Label5 
      Caption         =   "Y:"
      Height          =   255
      Left            =   13800
      TabIndex        =   25
      Top             =   1200
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "X:"
      Height          =   255
      Left            =   13800
      TabIndex        =   24
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label3 
      Caption         =   "接收字符区"
      Height          =   255
      Left            =   8280
      TabIndex        =   19
      Top             =   120
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "输入发送字符区"
      Height          =   255
      Left            =   8280
      TabIndex        =   14
      Top             =   2160
      Width           =   2295
   End
   Begin VB.Label Label8 
      Caption         =   "经度"
      Height          =   255
      Left            =   12120
      TabIndex        =   5
      Top             =   1320
      Width           =   495
   End
   Begin VB.Label Label7 
      Caption         =   "纬度"
      Height          =   255
      Left            =   12120
      TabIndex        =   4
      Top             =   960
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'*********************************************串口组件应用函数*************************************************************
'根据串口数据的特点 先截取GMRMC和*之间的数据，再从中得到时间，A后的数据，N后的数据，和E后的数据 再分别进行显示
'标准协议数据格式例子:我们只从第一行中取得相关数据
'$GPRMC,130134.50,A,3504.38785,N,12024.31176,E,0.041,,041212,,,A*70
'$GPVTG,,T,,M,0.041,N,0.076,K,A*27
'$GPGGA,140134.50,3604.38785,N,12024.31176,E,1,06,1.35,40.8,M,5.4,M,,*51
'$GPGSA,A,3,25,22,31,18,32,12,,,,,,,2.66,1.35,2.29*00
'$GPGSV,3,1,09,12,43,059,31,18,34,168,42,22,63,213,46,25,63,120,50*7C
'$GPGSV,3,2,09,31,34,256,49,32,08,320,36,40,11,254,42,42,41,142,44*70
'$GPGSV,3,3,09,50,41,142,42*41
'$GPGLL,3604.38785,N,12024.31176,E,140134.50,A,A*68
'*******************************************************************************

Private WithEvents ctDoc As HTMLDocument, ctRefresh As Boolean
Attribute ctDoc.VB_VarHelpID = -1
Dim ctP180 As Double, ctNumJ As Double, ctNumW As Double, ctZ As Double
Dim ctX As Long, ctY As Long, ctS As Long, ctXs As Long, ctYs As Long, ctF As String


Private Type BitMap
   bmType As Long         '图像类型：0 表示是位图
   bmWidth As Long        '图像宽度（像素）
   bmHeight As Long       '图像高度（像素）
   bmWidthBytes As Long   '每一行图像的字节数
   bmPlanes As Integer    '图像的图层数
   bmBitsPixel As Integer '图像的位数
   bmBits As Long         '位图的内存指针
End Type
Private Declare Function GetObject Lib "gdi32" Alias "GetObjectA" (ByVal hObject As Long, ByVal nCount As Long, lpObject As Any) As Long
Private Declare Function GetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long
Private Declare Function SetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long



'*****************************布尔型位标志变量定义******************************
Dim Bit_Flag        As Boolean
Dim FindMeEnF       As Boolean  '引导码判定有效标志位

Dim timer2enf As Boolean        '是否启用定时器2
Dim comdclick As Boolean        '是否按下查询坐标按键

Dim COMM_EnF        As Boolean  'IP定位有效标志位
Dim IP_EnF          As Boolean  'IP定位有效标志位
'*****************************串口通信 变量定义*********************************
Dim Rx_DataBag  As String                    '定义接收数据字符串
Dim Data         As String                    '定义数据
Dim DataLen     As Integer                   '定义数据长度
Dim Data_Cnt1   As Integer                   '定义数据个数计数
'---------------------------------------------------------------
'*****************************字符串 变量定义************************************

Dim gprmc()     As String        '收到的定位数据字符串
Dim status      As Boolean      '状态标志位 布尔值
Dim latitude    As Double       '纬度
Dim longitude   As Double       '经度
Dim speed       As Double       '速度

Dim ZoomNO      As Integer      '地图显示的放大系数 取值 0--20  暂时不用
'********************** 显示时间变量定义：时　分　秒 当前时间********************
Dim hour        As Integer
Dim minute      As Integer
Dim second      As Integer
Dim NowTime     As Date
'*******************     GPS 解析中间变量     ************************************
Dim oData       As String
Dim aData       As String
Dim NetData     As String

Dim m           As Long
Dim n           As Long
Dim MsgCount    As Long             '声明一个长整型量,接收数据包个数

Dim S1          As String
Dim S2          As String

Dim timer3count As Integer
Dim receiveok As Integer

Dim heartcount As Integer
Dim beat As Integer
Dim coord(0 To 200) As Double
Dim coordtosend(0 To 50) As String
Dim coordindex As Integer
Dim coordindex1 As Integer
Dim sendcoord$
Dim send$
Dim sendcoordok As Integer
Dim pathsendok As Integer
Dim pathokcount As Integer

Dim orderok As Integer
Dim order$

Dim httemp As Double
Dim httempcount As Integer
Dim rotemp As Double
Dim rotempcount As Integer
Dim pitemp As Double
Dim pitempcount As Integer
Dim gausscount As Integer
Dim gaussx As Double
Dim gaussy As Double




Function KillSpace(Expression)
Dim tmpS
For i = 1 To Len(Expression)
tmpT = Mid(Expression, i, 1)
If tmpT <> " " Then tmpS = tmpS & tmpT
Next i
KillSpace = tmpS
End Function



'Private Sub Command1_Click()

'End Sub

'Private Sub Command1_Click()

'End Sub

'Private Sub Command1_Click()                     '单击 我的位置刷新按钮 显示我的坐标

    'FindMeEnF = True
    
    'Call Findme                                 '调用查找地图程序

'End Sub

Private Sub Command10_Click()
'If (orderok = 0) Then
'    Text2.Text = "5fast"
'    If Text2.Text = "" Then
'        pp = MsgBox("发送的数据不能为空！", 16)
'    Exit Sub
'    End If
'    MSComm1.Output = Trim(Text2.Text)
    order = "4fast"
    Command10.Enabled = False
    Command11.Enabled = False
    Command12.Enabled = False
    Command13.Enabled = False
    Command14.Enabled = False
'ElseIf (orderok = 1) Then
'    orderok = 0
'End If
' For i = 1 To 20000000
'Next i
End Sub

Private Sub Command11_Click()

'Text2.Text = "right"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'' For i = 1 To 20000000
''Next i
order = "right"
    Command10.Enabled = False
    Command11.Enabled = False
    Command12.Enabled = False
    Command13.Enabled = False
    Command14.Enabled = False
End Sub

Private Sub Command12_Click()

'Text2.Text = "left"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'' For i = 1 To 20000000
''Next i
order = "left"
    Command10.Enabled = False
    Command11.Enabled = False
    Command12.Enabled = False
    Command13.Enabled = False
    Command14.Enabled = False
End Sub

Private Sub Command13_Click()

'Text2.Text = "stop"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'' For i = 1 To 20000000
''Next i
order = "stop"
    Command10.Enabled = False
    Command11.Enabled = False
    Command12.Enabled = False
    Command13.Enabled = False
    Command14.Enabled = False
End Sub

Private Sub Command14_Click()
'Text2.Text = "back"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'' For i = 1 To 20000000
''Next i
order = "back"
    Command10.Enabled = False
    Command11.Enabled = False
    Command12.Enabled = False
    Command13.Enabled = False
    Command14.Enabled = False
End Sub

Private Sub Command15_Click()

MSComm1.PortOpen = False


Kill "d:\testfile.txt"   '我最喜欢的一个函数，功能是删除一个文件，函数名是无与伦比的霸气
Kill "d:\gpscoord.txt"
Kill "d:\path.txt"
Kill "d:\carcoord.txt"

Unload Me '卸除窗体
End Sub


Private Sub Command16_Click()

    Call hexsend
    j = 0

End Sub

Private Sub Command17_Click()

MSComm1.PortOpen = True

End Sub

Private Sub Command18_Click()

order = "instanthalt"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i

End Sub

Private Sub Command19_Click()
Dim FilePath As String
FilePath = "D:\地图坐标.exe"
'FilePath = "D:\VB程序\画图板.exe"
If Dir(FilePath, vbNormal) <> "" Then
    Shell FilePath, vbNormalFocus
Else
    MsgBox "文件不存在", vbCritical, "提示"
End If
End Sub

Private Sub Command2_Click()                    '单击 查找坐标 显示输出框所在的地图位置  显示我的坐标


    FindMeEnF = True
    
    comdclick = True
    
    Call Findme                                     '调用查找地图程序



End Sub



Private Sub Findme()                            '单击 查找坐标 显示输出框所在的地图位置  显示我的坐标

    If FindMeEnF = True Then
        
        If ((Text3.Text <> "") And (Text4.Text <> "")) Then
            
            'If (comdclick = True) Then
            'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng(10,118),{icon:myIcon1}))", "javascript"
            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & ")),{icon:myIcon1})", "javascript" '添加标注
            'WebBrowser1.Document.parentWindow.execScript "google.maps.LatLng(" & Text3 & "," & Text4 & ");", "javascript"            '显示指定坐标点，缩放等级10
            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & ")),{icon: myIcon})", "javascript" '添加标注
            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng(" & Text3 & "," & Text4 & ")),{icon: myIcon1}))", "javascript" '添加标注
                'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & "),{icon:myIcon1}))", "javascript" '添加标注,这句话是可以的，在不用定时器调用的时候
        
            'End If
        
        
            'If ((latd > 0.01) And (latd < 1) And (lngd > 0.01) And (lngd < 1)) Then
                
                'comdclick = False
                'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & "),{icon:myIcon1}))", "javascript" '添加标注,这句话是可以的，在不用定时器调用的时候
            
            'End If
        End If
        
    End If

End Sub

Private Sub Command3_Click()
    WebBrowser1.document.parentWindow.execScript "map.clearOverlays()", "javascript"                                                     '清除所有标注
    Text3.Text = 0                     '清空显示纬度
    Text4.Text = 0                     '清空显示经度
    'Text_speed.Text = 0                '清空显示速度
    'TimeText.Text = 0                  '清空显示时间
End Sub



'Private Sub Command4_Click()                '单击分别进行串口显示内容、使能有效和无效的切换'

        'If Command4.Caption = "串口定位" Then
        '    Command4.Caption = "串口开启"
        '    COMM_EnF = True
        'Else
        'If Command4.Caption = "串口开启" Then
        '    Command4.Caption = "串口关闭"
        '    COMM_EnF = False
        '
        ' Else
        ' If Command4.Caption = "串口关闭" Then
        '    Command4.Caption = "串口开启"
        '    COMM_EnF = True
        '  End If
        ' End If
        'End If
       '
       ' IP_EnF = False
       ' Frame1.Visible = True                                    '串口设置框架 可见
       ' Frame2.Visible = False                                   '网络设置框架 不可见
    
'End Sub

'Private Sub Command5_Click()                '单击网络定位控制按钮

    'If Command5.Caption = "网络定位" Then
    '   Command5.Caption = "网络开启"
    '   IP_EnF = True
    '   COMM_EnF = False     '这里可以加入　网络开启使能
    'Else''

    'If Command5.Caption = "网络开启" Then
    '   Command5.Caption = "网络关闭"
    '          IP_EnF = False
    '          COMM_EnF = True
    '
    'Else
'
'     If Command5.Caption = "网络关闭" Then
'        IP_EnF = True
'        COMM_EnF = False
'        Command5.Caption = "网络开启"
'    End If
'    End If
'    End If
'
'    Frame1.Visible = False                  '网络定位时　串口定位不可见
'    Frame2.Visible = True                  '显示网络定位设置
'
'
'
'End Sub


'Private Sub Command6_Click()                     '点击连接网络按钮
' On Error GoTo ButtonErrToEnd
''************************  载入TCP服务器设置  *****************************
'    tcpserver.LocalPort = RandomPort.Text   '用户自己设定的端口号
'
'    tcpserver.Listen            '服务器开启监听标志
'    IP_EnF = True               '网络定位标志位有效
'ButtonErrToEnd:
'End Sub                         '操作结束






Private Sub Command9_Click()


'Dim x1 As Double
'Dim y1 As Double
''Call GaussProjCal(121.2632423, 31.34234, x1, y1)
'
''Label4.Caption = "a=" & x1 & "b=" & y1
'
'MsgBox "pathok!"
Call gettextlatlng

End Sub


Private Sub Form_Load()         '当窗体运行时,首先执行它下面的语句

Dim i As Integer
Dim x00, y00, x10, y10 As Integer
i = 1
ctP180 = 4 * Atn(1) '圆周率
ctS = 256           '每张图片的大小尺寸


    timer2findme = 0


    Open "d:\testfile.txt" For Output As #1 '在D盘创建一个新文件
    Open "d:\gpscoord.txt" For Output As #2
    Open "d:\carcoord.txt" For Output As #3
    'Open "d:\path.txt" For Output As #4
    Close #1 '如果该文件已经存在，新数据覆盖，不用担心读到的是前面几次的数据
    Close #2
    Close #3
    'Close #4

   Picture1.Picture = LoadPicture("d:\\s0271.jpg")
   Picture2.Picture = LoadPicture("d:\\%IS~XM9%PA3M1TNFGB@B_TJ.jpg")

   Form1.ScaleMode = 3:
   Picture1.ScaleMode = 3
   Picture2.AutoRedraw = True
   Picture1.AutoSize = True:
   Picture1.AutoRedraw = True
   Picture1.ToolTipText = "双击恢复原图形"
   
   
    Picture2.Left = 570
    Picture2.Top = 400
    Picture2.BorderStyle = 0
    Picture2.DrawWidth = 3

    x00 = Picture2.ScaleLeft
    y00 = Picture2.ScaleTop
    x10 = Picture2.ScaleLeft + Picture2.ScaleWidth
    y10 = Picture2.ScaleTop + Picture2.ScaleHeight

    Form1.Picture2.Line (1930, 570)-(1930, 500), RGB(0, 255, 0) 'header
    Form1.Picture2.Line (1930, 860)-(1930, 800), RGB(255, 0, 0) 'roll
    Form1.Picture2.Line (1800, 1507)-(1600, 1507), RGB(0, 0, 255) 'pitch
   
   ctP180 = 4 * Atn(1) '圆周率
   
    
   
   '设置控件位置，实际可以在设计窗体时完成
   Dim W11 As Long
   W11 = Me.TextWidth("A")


   Text5.Move W11 * 1, W11 * 80, W11 * 12
   'Picture1.Move W11 * 20, W11 * 70, W11 * 20, W11 * 20

 On Error GoTo ErrToEnd
 
'    WebBrowser1.navigate App.Path & "\GoogleMap.html"  '载入谷歌地图网页
    
'    Command1.Enabled = False
    Command2.Enabled = False
    Command3.Enabled = False
    '****************************界面载入时 串口数据初始化*********************
    'MSComm1.CommPort = 1                                '串口1
    'MSComm1.Settings = "9600,n,8,1"             '波特率
    'MSComm1.InBufferCount = 0
    'MSComm1.InputLen = 0
    'MSComm1.InBufferSize = 1024                 '输入缓冲区大小
    'MSComm1.OutBufferSize = 512
    'MSComm1.OutBufferCount = 0
    'MSComm1.RThreshold = 512               '每次接收512个数据再产生 MSCOMM 事件 。这个值 很关键 ， 它决定 接收中断再次产生的时间
    'MSComm1.SThreshold = 0
    'MSComm1.PortOpen = False                '打开软件时 就打开了串口 接收到数据解析时 根据网络/串口有效标志位进行决定解析来自哪种类型的接口
             
             
    MSComm1.InBufferCount = 0
'    MSComm1.InputLen = 0 '自动清缓冲区
    MSComm1.InBufferSize = 1024                 '输入缓冲区大小
    MSComm1.OutBufferSize = 1024
    MSComm1.CommPort = 9                  ' 设置通信端口号为COM1
    MSComm1.Settings = "57600,n,8,1"       ' 设置串口1参数\
    MSComm1.InputMode = 0                ' 接收文本型数据
    MSComm1.PortOpen = True                 ' 打开通信端口1
    MSComm1.RThreshold = 80




        
ErrToEnd:
End Sub                                    '结束 Private Sub Form_Load()



Private Sub MSComm1_OnComm()
    'Dim buf$
    Dim buf2$
    
    Dim buf4$
    Dim buf5$
    
    
    
    Dim i As Integer
    
    Timer4.Enabled = False '一旦串口有数据接收，定时器4不可以启用
    
    buf = MSComm1.Input    ' 将缓冲区内的数据读入buf变量中
    
    
    If Len(buf) <> 0 Then         ' 判断缓冲区内是否存在数据

        'Text1.Text = Text1.Text + Chr(13) + Chr(10) + buf      '回车换行
       
         'Text1.Text = buf   '没必要的时候不显示
         Text9.BackColor = vbGreen '数据接收指示灯亮
         Call resolvegps
        
'        If (InStr(buf, buf2) <> 0) Then '如果找得到方位角的标志
'
'            buf3 = Mid(buf, InStr(buf, buf2) + 2, 10)
'
'            delta = Abs(Val(buf3) - Val(buf6))
'
'            buf6 = buf3
'
'
'        ElseIf ((InStr(buf, buf4) <> 0)) Then
'            Text3.Text = Mid(buf, InStr(buf, buf4) + 2, 10)
'        ElseIf ((InStr(buf, buf5) <> 0)) Then
'            Text4.Text = Mid(buf, InStr(buf, buf5) + 2, 10)
'
'
        End If

End Sub

'Private Sub MSComm1_OnComm()               '串口通信数据解析

    'On Error GoTo ErrHdl
    
    'Call GPS_Data_Load                      '调用数据解析程序。  将它写成一个通用模块 ， 根据网络和串口有效标志分别解析
                                            
                                           
    
'ErrHdl:                                     '如果遇到错误 直接跳转到这儿
'End Sub






Private Sub Option1_Click()
    'MSComm1.Settings = "9600,n,8,1"  '设定串口参数
    Option2.Value = False
End Sub

Private Sub Option2_Click()
    'MSComm1.Settings = "4800,n,8,1"  '设定串口规定
    Option1.Value = False
    
End Sub





Private Sub Timer2_Timer()

Dim gausscx As Double
Dim gausscy As Double

Open "d:\\gpscoord.txt" For Output As #2
'虽然平面坐标一直在转换，但是只有符合规定的数据才能写入文件
If ((Val(Text3) > 25) And (Val(Text3) < 35) And (Val(Text4) > 110) And (Val(Text4) < 130)) Then
    Print #2, Text3.Text & vbCrLf
    Print #2, Text4.Text & vbCrLf
'    Print #2, buf
    End If
Close #2

gausscx = Val(Text6)
gausscy = Val(Text7)

Open "d:\\carcoord.txt" For Output As #3

If ((Abs(gausscx - gaussx) < 0.5) And (Abs(gausscy - gaussy) < 0.5) And (guasscount > 0)) Then
    
    Print #3, Str(gausscx) & vbCrLf
    Print #3, Str(gausscy) & vbCrLf
    
    gaussx = gausscx '将前一次的高斯平面坐标保存，和下一次的坐标相比
    gaussy = gausscy

ElseIf ((gausscx > 3000000) And (gausscy > 300000) And (guasscount = 0)) Then
    Print #3, Str(gausscx) & vbCrLf
    Print #3, Str(gausscy) & vbCrLf
    
    gaussx = gausscx '将前一次的高斯平面坐标保存，和下一次的坐标相比
    gaussy = gausscy
    
    gausscount = 1
    
End If
Close #3

'If ((Val(Text6) > 3000000) And (Val(Text7) > 300000)) Then
'    gaussx = Val(Text6) '将前一次的高斯平面坐标保存，和下一次的坐标相比
'    gaussy = Val(Text7)

'    gausscount = gausscount + 1
'    If (gausscount > 0) Then
'        gausscount = 1
'    End If
'End If

End Sub

Private Sub Timer3_Timer()

heartcount = heartcount + 1

'If (heartcount = 1) Then
'If (beat <> 0) Then
    If (MSComm1.PortOpen = True) Then
        Text2.Text = "ARQ"
        'If Text2.Text = "" Then
            'pp = MsgBox("发送的数据不能为空！", 16)
            'Exit Sub
        'End If
        If ((pathokcount > 1) And (pathsendok = 1)) Then
            sendcoord = ""
            pathsendok = 0
'        ElseIf ((sendcoordok = 1)) Then
'            sendcoordok = 0
'        Else
'            sendcoord = ""
        End If
        
        
        If (orderok = 0) Then
            Command10.Enabled = True
            Command11.Enabled = True
            Command12.Enabled = True
            Command13.Enabled = True
            Command14.Enabled = True
        End If
        
        
        If (orderok = 1) Then '如果已经收到了指令的话，那么就不用再发了
            orderok = 0 '清零，不要再发了
            order = "0"

        End If

        MSComm1.Output = KillSpace(Text2.Text & sendcoord & order)
'        For i = 1 To 20000000
'        Next i
    End If
'End If
'End If


If (heartcount = 3) Then '2S时间到，检测是否和小车正常通信，是否接收到小车的心跳
    heartcount = 0
    
'    If (MSComm1.PortOpen = True) Then
'        Text2.Text = "ARQ"
'        'If Text2.Text = "" Then
'            'pp = MsgBox("发送的数据不能为空！", 16)
'            'Exit Sub
'        'End If
'        MSComm1.Output = Trim(Text2.Text)
''        For i = 1 To 20000000
''        Next i
'    End If

    '如果没有接收到，则小车立即制动
    If ((beat = 0) And (MSComm1.PortOpen = True)) Then
        Text2.Text = "stop"

        MSComm1.Output = Trim(Text2.Text)
'        For i = 1 To 20000000
'        Next i
    '如果收到了，则说明通信正常
    ElseIf (beat <> 0) Then
        Text2.Text = ""
        beat = 0
    End If
    
End If

If (Val(Text8.Text) < 11) Then
    If (timer3count = 0) Then
        Text8.BackColor = vbRed
        timer3count = 1
        receiveok = 1
    ElseIf (timer3count = 1) Then
        Text8.BackColor = vbWhite
        timer3count = 0
    End If
ElseIf (Val(Text8.Text) >= 7.6) Then
    Text8.BackColor = vbWhite
End If

End Sub

Private Sub Timer4_Timer()
'Dim buftest$
'Dim i As Integer
'buftest = MSComm1.Input
'    If ((comflag = 0) Or (MSComm1.PortOpen = False)) Then
        '如果串口关闭或者是没有数据传过来的话，则数据接收指示灯变为闪烁红色
'        If (buf = "") Then
            If (receiveok = 0) Then
                Text9.BackColor = vbRed
                receiveok = 1
            ElseIf (receiveok = 1) Then
                Text9.BackColor = vbWhite
                receiveok = 0
            End If
'        Else
'            Text9.BackColor = vbGreen
'        End If
'    ElseIf ((comfalg = 1)) Then '如果能够触发oncomm事件，说明数据完整接收，绿灯亮
'
'        Text9.BackColor = vbGreen
'
'    End If
End Sub


'Private Sub Timer5_Timer()
'
'If (leftok = 1) Then
'
'Text2.Text = "left"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'End If
'If (rightok = 1) Then
'
'Text2.Text = "right"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
'End If
'End Sub

Private Sub WebBrowser1_DocumentComplete(ByVal pDisp As Object, URL As Variant) '地图加载完成前 按钮无效
    
'    Do While WebBrowser1.Busy '等待加载完成.
'
'    Timer5.Enabled = False
'    Timer4.Enabled = False
'    MSComm1.PortOpen = False
'    Timer2.Enabled = False
'    Timer3.Enabled = False
'    Timer1.Enabled = False
''    Command1.Enabled = False
'    Command2.Enabled = False
'    Command3.Enabled = False
'
'    Loop
'
'    '如果加载完成
'    MSComm1.PortOpen = True
    Timer2.Enabled = True
    
    Timer1.Enabled = True
    Timer3.Enabled = True
'    Command1.Enabled = True
    Command2.Enabled = True
    Command3.Enabled = True
    Timer4.Enabled = True
    Timer5.Enabled = True
    
    Timer4.Interval = 200
    
End Sub

Private Sub Winsock1_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)

End Sub



Private Sub Webbrowser1_DownloadComplete()
   Set ctDoc = WebBrowser1.document
End Sub






Private Function GaussProjCal(longitude As Double, latitude As Double, X As Double, Y As Double)

Dim A1, e2, e1, a, Bc, c, d, n1, x1, dl, n, t, n2, pi, xval, yval As Double
Dim m, L0 As Integer
Dim n11, M1, n12, t1, BB, B0, B1, B2, B4, B6, r As Double

pi = 4 * Atn(1) '圆周率
m = CInt(longitude / 6) + 1


'If ((m > 19) And (m < 23)) Then


L0 = 6 * m - 3
dl = longitude - L0
dl = dl * pi / 180
latitude = latitude * pi / 180
A1 = 6378245
e1 = 0.006738525415
e2 = 0.006693421623
a = 1.0050517739
Bc = 0.00506237764
c = 0.00001062451
d = 0.00000002081
n1 = A1 / Sqr(1 - e2 * Sin(latitude) * Sin(latitude))
t = Tan(latitude)
n = 0.006738525415 * Cos(latitude) * Cos(latitude)
x1 = A1 * (1 - e2) * (a * latitude - Bc / 2 * Sin(2 * latitude) + c / 4 * Sin(4 * latitude) - d / 6 * Sin(6 * latitude))
xval = x1 + dl * dl / 2 * n1 * Sin(latitude) * Cos(latitude) * (1 + dl * dl * Cos(latitude) * Cos(latitude) / 12 * (5 - t * t + 9 * n + 4 * n * n) + dl * dl * dl * dl * Cos(latitude) * Cos(latitude) * Cos(latitude) * Cos(latitude) / 360 * (61 - 58 * t * t + t * t * t * t))
yval = dl * n1 * Cos(latitude) * (1 + dl * dl * Cos(latitude) * Cos(latitude) / 6 * (1 - t * t + n) + dl * dl * dl * dl * Cos(latitude) * Cos(latitude) * Cos(latitude) * Cos(latitude) / 120 * (5 - 18 * t * t + t * t * t * t + 14 * n - 58 * n * t * t))
yval = yval + 500000
X = xval
Y = yval

'End If

End Function

'该函数负责将得到的经纬度转换成平面坐标
Private Function getlatlng()

Dim aas, bs As String
Dim lng As Double
Dim lat As Double
Dim x1 As Double
Dim y1 As Double
Dim coord(0 To 99) As Double

Dim i As Integer

i = 0
'现在不需要去读取文件了，现在直接把text里面的东西拿出来就行了
'Open "d:\\testfile.txt" For Input As #1
'Do While Not EOF(1) '
'Input #1, aas
'Input #1, bs
'
'lng = Val(aas)  '每次读数据出来，经度在前，纬度在后
'lat = Val(bs)


lng = Val(Text4.Text)
lat = Val(Text3.Text)

'调用经纬度解析函数直接算出平面坐标
Call GaussProjCal(lng, lat, x1, y1)


Text6.Text = Str(x1)
Text7.Text = Str(y1)

'
'coord(i) = x1
'i = i + 1
'coord(i) = y1
'Label4.Caption = "X1=" & coord(0) & "Y1=" & coord(1)
'Loop

'Close #1 ' 关闭文件


'提取数据给变量


'Label4.Caption = "a=" & a & "b=" & B & "c=" & c & "d=" & d

End Function


'该函数负责将平面坐标取出发送给小车
Private Function gettextlatlng()

Dim aas, bs As String
Dim lng As Double
Dim lat As Double
Dim x1 As Double
Dim y1 As Double
Dim coord(0 To 99) As Double

Dim i As Integer

'Open "d:\\path.txt" For Input As #1
'Do While Not EOF(1) '
'Input #1, aas
'Input #1, bs
'
'lng = Val(aas)  '每次读数据出来，经度在前，纬度在后
'lat = Val(bs)
'
'
''lng = Val(Text4.Text)
''lat = Val(Text3.Text)
'
''调用经纬度解析函数直接算出平面坐标
'Call GaussProjCal(lng, lat, x1, y1)
'
'
''Text6.Text = Str(x1)
''Text7.Text = Str(y1)
''
'coord(i) = x1
'i = i + 1
'coord(i) = y1
'i = i + 1
''Label4.Caption = "X1=" & coord(0) & "Y1=" & coord(1)
'Loop

'Close #1 ' 关闭文件

pathokcount = 0 '再次点击的时候重新开始判断计算
pathsendok = 0 '再次点击的时候重新开始判断计算
sendcoordok = 0 '再次点击的时候重新开始判断计算

For i = 0 To 99 Step 1
    coord(i) = 0
Next i

For i = 0 To 50 Step 1
    coordtosend(i) = 0
Next i


coordtosend(0) = "B"
coordindex1 = 1 '从第二个数组元素开始赋值，第一个作为路径数据的标记

Open "d:\\path.txt" For Input As #4
Do While Not EOF(4)
Line Input #4, aas

'x = Val(aas)  '每次读数据出来，经度在前，纬度在后
'y11 = Val(bs)
'Y2 = Val(cs)

'先把这里的根据文件读入数据的话注掉，先调试两个点的
coord(coordindex) = Val(aas)

If ((coordindex Mod 2) = 0) Then
    coordtosend(coordindex1) = Str(coord(coordindex))
    coordindex1 = coordindex1 + 1
End If

coordindex = coordindex + 1
'到这里结束



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
Close #4

'提取数据给变量
coordtosend(coordindex1) = "P" '数组最后一位赋值为P，代表这是路径的数组
sendcoord = Join(coordtosend, ",")
'sendcoord = "B,3435820.3479,351793.5681,3435823.7295,351797.6266,P" '测试用数据
'Text2.Text = "3fast"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'If (MSComm1.PortOpen = True) Then '把路径数组发出去
'    MSComm1.Output = Trim(sendcoord)
'End If
' For i = 1 To 20000000
'Next i
sendcoordok = 1
coordindex = 0
coordindex1 = 0


''在发送字串中添加逗号，分隔开每个字符
'For i = 1 To Len(coordtosend)  '循环插入.
'    coordtosend = coordtosend & Mid(coordtosend, i, 1)
'    If i <> Len(coordtosend) Then
'        coordtosend =  & "," '不要在最后加入空格.
'    End If
'Next i



'Label4.Caption = "a=" & a & "b=" & B & "c=" & c & "d=" & d

End Function


Private Sub GetBmpDat(Kj As Control, W As Long, H As Long, B() As Byte, bs As Long, BytesW As Long, Ps As Long)
   '获取控件 Kj 的图像数据
   Dim MapInf As BitMap
   GetObject Kj.Image, Len(MapInf), MapInf '用 MapInf 得到 Kj 的图像信息
   W = MapInf.bmWidth: H = MapInf.bmHeight '图像宽度、高度（像素）
   BytesW = MapInf.bmWidthBytes            '每行占用字节数
   Ps = BytesW \ W                         '每个像素字节数(一般为4)
   bs = W * H * Ps                         '总字节数=宽度*高度*每个像素字节
   ReDim B(0 To bs - 1)
   GetBitmapBits Kj.Image, bs, B(0)        '将 Kj 图像所有像素点的颜色值读入二进数组 B()
End Sub

Private Function XYtoIndex(X As Long, Y As Long, BytesW As Long, Ps As Long) As Long
   '返回图像坐标 x,y 在颜色数组中的序号位置。
   'BytesW：每行图像占用字节数，Ps：每个像素点占用字节数(一般为4)
   XYtoIndex = Y * BytesW + X * Ps
End Function

Private Sub Zhuan(ToJ As Single, x0 As Long, y0 As Long, ByVal X As Long, ByVal Y As Long, x1 As Long, y1 As Long)
   '将点 x,y 围绕 x0,y0 顺时针旋转 ToJ 弧度，用 x1,y1 返回旋转后的位置
   '注意：要预先设置圆周率 ctP180 = 4 * Atn(1)
    Dim S As Single, j As Single
   
    X = X - x0: Y = Y - y0
    S = Sqr(X ^ 2 + Y ^ 2)               'X,Y 与 x0,y0 的距离
    If S = 0 Then j = 0 Else j = Y / S   '与水平线的夹角的正弦值

    If Abs(j) >= 1 Then
       If j > 0 Then j = ctP180 * 0.5 Else j = -ctP180 * 0.5 '90 度时的特殊情况
    Else
       j = Atn(j / Sqr(-j * j + 1)) '与水平线的夹角
    End If
   
    If X < 0 Then j = -ctP180 - j
    x1 = x0 + S * Cos(j + ToJ): y1 = y0 + S * Sin(j + ToJ) '返回旋转后的位置
End Sub




Private Function rotation()
   '旋转图片
   Dim W1 As Long, H1 As Long, B1() As Byte, Bs1 As Long, BytesW1 As Long, Ps1 As Long
   Dim W2 As Long, H2 As Long, B2() As Byte, Bs2 As Long, BytesW2 As Long, Ps2 As Long
   Dim S1 As Long, S2 As Long, X As Long, Y As Long, x1 As Long, y1 As Long
   Dim CenX1 As Long, CenY1 As Long, CenX2 As Long, CenY2 As Long
   Dim KjFocus As Control, ToJ As Single

   Text5.Enabled = True
   
   ToJ = Val(Text5.Text) / 180 * ctP180 '旋转角度转弧度
   
   Set KjFocus = Me.ActiveControl '记忆具有焦点的控件


   Text5.Enabled = False
   
   '下面一条语句看似可有可无，实际有两个作用：恢复旋转前控件的原图像和大小
   Picture1.Picture = Picture1.Picture
   
   '旋转前图像数据：宽度，高度，颜色数组，总字节数，每行字节数，每像素字节数
   GetBmpDat Picture1, W1, H1, B1, Bs1, BytesW1, Ps1
   CenX1 = Int(W1 * 0.5): CenY1 = Int(H1 * 0.5)       '旋转前的图像中心点
   
   '计算旋转后控件的高度和宽度，要预先设置窗体和图片的 ScaleMode 为 3（像素）
   W2 = Abs(W1 * Cos(ToJ)) + Abs(H1 * Sin(ToJ))  '旋转后：图像宽度
   H2 = Abs(H1 * Cos(ToJ)) + Abs(W1 * Sin(ToJ))  '旋转后：图像高度
   X = Picture1.Width - Picture1.ScaleWidth      '图片框边框：宽度
   Y = Picture1.Height - Picture1.ScaleHeight    '图片框边框：高度
   'Picture1.Move Picture1.Left, Picture1.Top, X + W2, Y + H2
   
   '下面的 Picture1.Cls 语句此处的作用主要不是清除图像，而是更新控件
   '的 Image 属性，使调用 GetBmpDat 时能正确取得图像数据
   'Picture1.Cls
   Picture1.Line (0, 0)-(W2, H2), &H0&, BF

   '旋转后图像数据：宽度，高度，颜色数组，总字节数，每行字节数，每像素字节数
   GetBmpDat Picture1, W2, H2, B2, Bs2, BytesW2, Ps2
   CenX2 = Int(W2 * 0.5): CenY2 = Int(H2 * 0.5)       '旋转后：图像中心点

   '显示信息
   Picture1.CurrentX = 5: Picture1.CurrentY = 5
   Picture1.Print "处理中，请稍候..."
   Me.Refresh
   
   W1 = W1 - 1: H1 = H1 - 1
   For X = 0 To W2 - 1
   For Y = 0 To H2 - 1
      Zhuan -ToJ, CenX2, CenY2, X, Y, x1, y1           '用 x1,y1 获得旋转坐标
      x1 = x1 - CenX2 + CenX1: y1 = y1 - CenY2 + CenY1 '转变为旋转前的坐标
      
      S2 = XYtoIndex(X, Y, BytesW2, Ps2)    '旋转后：像素点在数组 B2 中的索引
      If x1 < 0 Or x1 > W1 Or y1 < 0 Or y1 > H1 Then
         B2(S2 + 2) = 0: B2(S2 + 1) = 0: B2(S2) = 0 '超出原图像区域，设为白色
      Else
         S1 = XYtoIndex(x1, y1, BytesW1, Ps1)  '旋转前：像素点在数组 B1 中的索引
         B2(S2 + 2) = B1(S1 + 2): B2(S2 + 1) = B1(S1 + 1): B2(S2) = B1(S1) '红绿蓝
      End If
   Next
   Next
   
   SetBitmapBits Picture1.Image, Bs2, B2(0) '将 Picture1 的图像设置为旋转后的二进数组 B2()


   Text5.Enabled = True
   On Error Resume Next
   KjFocus.SetFocus  '还原具有焦点的控件



End Function

Private Sub Picture1_DblClick()
   '下面语句看似可有可无，实际有两个作用：恢复旋转前控件的原图像和大小
   Picture1.Picture = Picture1.Picture
End Sub



' 把字符通过串口发送出去
 Private Sub Command7_Click()
If Text2.Text = "" Then
pp = MsgBox("发送的数据不能为空！", 16)
 Exit Sub
End If
MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
End Sub

 ' 通过时钟控制来自动接收字符
Private Sub Timer1_Timer()

    If (Timer1.Enabled = True) Then

        'If ((delta > 0.1) And (delta < 5)) Then

            Call rotation
        


        'End If
    End If
    
End Sub

' 关闭通信端口,停止程序运行
Private Sub Command8_Click()
MSComm1.PortOpen = False
'Unload Me
End Sub


Private Function hexsend()
    Dim sj() As String
    Dim sjByt() As Byte
    Dim i As Long
    
    
    Dim sjByt1() As Byte
    Dim highbit, lowbit As String

    
    sj = Split(Text2, " ")
    ReDim sjByt(UBound(sj))
    ReDim sjByt1(1000)
    
    
    If Check1.Value = 0 Then '如果不勾选十六进制显示，则数据直接转成十六进制发出去
        For i = 0 To UBound(sj)
            sjByt(i) = Val("&H" & Str(Val(Left(sj(i), 2)))) '字符数组转成十六进制发送出去
        Next i
        MSComm1.Output = sjByt
    
    ElseIf Check1.Value = 1 Then '如果勾选了十六进制显示，则数据转成十六进制后分别转成ascii码发出去
        For i = 0 To UBound(sj)
            sjByt(i) = Val("&H" & Str(Val(Left(sj(i), 2)))) '字符数组转成十六进制发送出去
            
            highbit = sjByt(i) And &HF0
            highbit = highbit / 16
            
            lowbit = sjByt(i) And &HF
            
            
            If (highbit >= 0 And highbit <= 9) Then
                highbit = highbit + &H30
            ElseIf (highbit >= a And highbit <= f) Then
                highbit = highbit + &H37
            End If
            If (lowbit >= 0 And lowbit <= 9) Then
                lowbit = lowbit + &H30
            ElseIf (lowbit >= a And lowbit <= f) Then
                lowbit = lowbit + &H37
            End If
            
            sjByt1(j) = CStr(highbit) '分别把每一位数字都取出来放到一个新的数组里
            sjByt1(j + 1) = lowbit
            sjByt1(j + 2) = Str(&H20) '由于字符根据空格隔开，所以取出来以后要把空格加回去
            j = j + 3
            
             
        Next i
        MSComm1.Output = sjByt1
    End If
End Function




Public Function resolvegps()

Dim startbit$
Dim endbit$
Dim numbit$
Dim dislat$
Dim dislnt$
Dim dishead$
Dim disroll$
Dim dispitch$
Dim speed$
Dim pow$



Dim numindex As Integer
Dim i, k As Integer
Dim dataindex As Integer
Dim latdata(10) As String
Dim lntdata(10) As String
Dim header(10) As String
Dim roller(10) As String
Dim pitcher(10) As String
Dim speeder(10) As String
Dim power(4) As String
Dim receiver As String
Dim receiver1() As String
Dim status As Integer
Dim stxindex, etxindex As Integer
Dim dotindex1, dotindex2, dotindex3, dotindex4, dotindex5, dotindex6, dotindex7 As Integer
Dim minus1, minus2 As Integer
Dim numberok As Integer
Dim pi1 As Double


pi1 = 4 * Atn(1)

receiveok = 1 '数据接收完，开始解析

status = 0
startbit = "s"
endbit = "e"
numbit = "1E"

If (InStr(buf, "H") <> 0) Then
    beat = beat + 1
    
End If


If (InStr(buf, "M") <> 0) Then
    If ((pathokcount > 1) Or (pathokcount = 1)) Then
        pathokcount = 2
    End If
    pathokcount = pathokcount + 1
    pathsendok = 1
Else
    pathsendok = 0
End If

If (InStr(buf, "Y") <> 0) Then
    orderok = 1
Else
    orderok = 0
End If


'在接收字串中添加逗号，分隔开每个字符
For i = 1 To Len(buf)  '循环插入.
    receiver = receiver & Mid(buf, i, 1)
    If i <> Len(buf) Then
        receiver = receiver & "," '不要在最后加入空格.
    End If
Next i


buf = ""


'以逗号为标记，将字串拆开，拆成一个一个的字符
receiver1 = Split(receiver, ",")
'receiver = Split(buf, "")

k = 0

If (status = 0) Then
    For i = 0 To UBound(receiver1) Step 1 '遍历数组，确认是否接收完整的一包数据

        If (receiver1(i) = "s") Then
            stxindex = i '记录下此时的坐标
        ElseIf (receiver1(i) = "e") Then
            etxindex = i
        End If
        If ((etxindex - stxindex) = 79) Then
            status = 1
            Exit For '如果找到完整的一包数据，跳出整个for循环
        End If
    Next i
End If

If (status = 1) Then
    For i = stxindex To etxindex Step 1
    
        If (receiver1(i) = ".") Then '如果找到小数点的话
            k = k + 1 '计数有多少个小数点
            If (k = 1) Then '纬度
                dotindex1 = i '取出该小数点的下标
            ElseIf (k = 2) Then '经度
                dotindex2 = i
            ElseIf (k = 3) Then '方位角
                dotindex3 = i
            ElseIf (k = 4) Then 'roll角
                dotindex4 = i
            ElseIf (k = 5) Then 'pitch角
                dotindex5 = i
            ElseIf (k = 6) Then '速度
                dotindex6 = i
            ElseIf (k = 7) Then '电量
                dotindex7 = i
                status = 2
                k = 0 '清零计数器
                Exit For '跳出for循环
            End If
        End If
    Next i
End If

If (status = 2) Then
    For i = stxindex To etxindex Step 1 '遍历一部分数组，取出纬度
        If (receiver1(i) = "-") Then
            If ((k >= 30) And (k < 40)) Then
                minus1 = 1
            ElseIf ((k >= 40) And (k <= 50)) Then
                minus2 = 1
            End If
        End If
        If ((receiver1(i) >= "0") And (receiver1(i) <= "9") And (i > 6) Or (receiver1(i) = ".")) Then '如果是数字的话，取出来
            If (k < 10) Then
                latdata(k) = receiver1(i) '赋值给纬度数组
                If ((i - dotindex1) = 7) Then '如果已经有了6位小数的话
                    k = 10
                Else
                    k = k + 1
                End If
            ElseIf ((k >= 10) And (k < 20)) Then '如果数据取完，开始读取经度
                lntdata(k - 10) = receiver1(i) '赋值给经度数组
                If ((i - dotindex2) = 7) Then '如果已经有了6位小数的话
                    k = 20
                Else
                    k = k + 1
                End If
            ElseIf ((k >= 20) And (k < 30)) Then '开始读取方位角度
                header(k - 20) = receiver1(i)
                If ((i - dotindex3) = 7) Then '如果已经有了6位小数的话
                    k = 30
                Else
                    k = k + 1
                End If
            ElseIf ((k >= 30) And (k < 40)) Then '开始读取左右倾角roll
                roller(k - 30) = receiver1(i)
                If ((i - dotindex4) = 7) Then '如果已经有了6位小数的话
                    k = 40
                Else
                    k = k + 1
                End If
            ElseIf ((k >= 40) And (k < 50)) Then '开始读取前后倾角pitch
                pitcher(k - 40) = receiver1(i)
                If ((i - dotindex5) = 6) Then '如果已经有了6位小数的话
                    k = 50
                Else
                    k = k + 1
                End If
            ElseIf ((k >= 50) And (k < 54)) Then '开始读取速度
                speeder(k - 50) = receiver1(i)
                If ((i - dotindex6) = 1) Then '如果已经有了3位小数的话
                    k = 54
                Else
                    k = k + 1
                End If
            ElseIf (k >= 54) Then            '开始读取剩余电量
                power(k - 54) = receiver1(i)
                k = k + 1
                If ((i - dotindex7) = 2) Then
                    status = 3
                    Exit For
                End If
            End If
        End If
    Next i
End If


If (status = 3) Then '如果解析完成，数据进行格式转换

    
    For i = 0 To 9 Step 1
        dislat = dislat & latdata(i)
        dislnt = dislnt & lntdata(i)
        dishead = dishead & header(i)
        disroll = disroll & roller(i)
        dispitch = dispitch & pitcher(i)
    Next i
    
    For i = 0 To 3 Step 1
        speed = speed & speeder(i)
    Next i
    
    For i = 0 To 3 Step 1
        pow = pow & power(i)
    Next i
    
    If ((dislat > 25) And (dislat < 35) And (dislnt > 115) And (dislnt < 130)) Then
        Text3.Text = dislat
        Text4.Text = dislnt
        Text5.Text = dishead
        If (minus1 = 0) Then
            Text10.Text = disroll
        ElseIf (minus1 = 1) Then
            Text10.Text = "-" & disroll
            minus1 = 0
        End If
        
        If (minus2 = 0) Then
            Text11.Text = dispitch
        ElseIf (minus2 = 1) Then
            Text11.Text = "-" & dispitch
            minus2 = 0
        End If
        buf6 = dishead
        Text12.Text = speed
        Text8.Text = pow
    Else
        Text3.Text = "0"
        Text4.Text = "0"
        Text5.Text = dishead
        
        
        If (minus1 = 0) Then
            Text10.Text = disroll
        ElseIf (minus1 = 1) Then
            Text10.Text = "-" & disroll
            minus1 = 0
        End If
        
        If (minus2 = 0) Then
            Text11.Text = dispitch
        ElseIf (minus2 = 1) Then
            Text11.Text = "-" & dispitch
            minus2 = 0
        End If
        
        
'        If ((Val(Text5) >= 0) And (Val(Text5) <= 90)) Then

        If (httempcount > 0) Then
            httempcount = 1
            Form1.Picture2.Line (1930 + 950 * Sin(httemp * pi1 / 180), 1507 - 950 * Cos(httemp * pi1 / 180))-(1930 + 1080 * Sin(httemp * pi1 / 180), 1507 - 1080 * Cos(httemp * pi1 / 180)), RGB(255, 255, 255) 'header
            Form1.Picture2.Line (1930 + 950 * Sin(Val(Text5) * pi1 / 180), 1507 - 950 * Cos(Val(Text5) * pi1 / 180))-(1930 + 1080 * Sin(Val(Text5) * pi1 / 180), 1507 - 1080 * Cos(Val(Text5) * pi1 / 180)), RGB(0, 255, 0) 'header
            httemp = Val(Text5)
        ElseIf (httempcount = 0) Then
            Form1.Picture2.Line (1930, 500)-(1930, 570), RGB(255, 255, 255)  'header
            httempcount = httempcount + 1
            Form1.Picture2.Line (1930 + 950 * Sin(Val(Text5) * pi1 / 180), 1507 - 950 * Cos(Val(Text5) * pi1 / 180))-(1930 + 1080 * Sin(Val(Text5) * pi1 / 180), 1507 - 1080 * Cos(Val(Text5) * pi1 / 180)), RGB(0, 255, 0) 'header
            httemp = Val(Text5)
        End If
        
        
        If (rotempcount > 0) Then
            rotempcount = 1
            Form1.Picture2.Line (1930 - 600 * Sin(rotemp * pi1 / 180), 1507 - 600 * Cos(rotemp * pi1 / 180))-(1930 - 670 * Sin(rotemp * pi1 / 180), 1507 - 670 * Cos(rotemp * pi1 / 180)), RGB(255, 255, 255) 'roll
            Form1.Picture2.Line (1930 - 600 * Sin(Val(Text10) * pi1 / 180), 1507 - 600 * Cos(Val(Text10) * pi1 / 180))-(1930 - 670 * Sin(Val(Text10) * pi1 / 180), 1507 - 670 * Cos(Val(Text10) * pi1 / 180)), RGB(255, 0, 0) 'roll
            rotemp = Val(Text10)
        ElseIf (rotempcount = 0) Then
            Form1.Picture2.Line (1930, 800)-(1930, 900), RGB(255, 255, 255)  'roll
            rotempcount = rotempcount + 1
            Form1.Picture2.Line (1930 - 600 * Sin(Val(Text10) * pi1 / 180), 1507 - 600 * Cos(Val(Text10) * pi1 / 180))-(1930 - 670 * Sin(Val(Text10) * pi1 / 180), 1507 - 670 * Cos(Val(Text10) * pi1 / 180)), RGB(255, 0, 0) 'roll
            rotemp = Val(Text10)
        End If
        
        If (pitempcount > 0) Then
            pitempcount = 1
            Form1.Picture2.Line (1800, (1507 - pitemp * 340 / 90))-(1600, (1507 - pitemp * 340 / 90)), RGB(255, 255, 255)  'pitch
            Form1.Picture2.Line (1800, (1507 - Val(Text11) * 340 / 90))-(1600, (1507 - Val(Text11) * 340 / 90)), RGB(0, 0, 255)  'pitch
            pitemp = Val(Text11)
        ElseIf (pitempcount = 0) Then
            Form1.Picture2.Line (1800, (1507 - Val(Text11) * 340 / 90))-(1600, (1507 - Val(Text11) * 340 / 90)), RGB(255, 255, 255)  'pitch
            pitempcount = pitempcount + 1
            Form1.Picture2.Line (1800, (1507 - Val(Text11) * 340 / 90))-(1600, (1507 - Val(Text11) * 340 / 90)), RGB(0, 0, 255)  'pitch
            rotemp = Val(Text10)
        End If
'        End If
'        Text10.Text = disroll
'        Text11.Text = dispitch
        buf6 = dishead
        Text12.Text = speed
        Text8.Text = pow
        
    End If
    '不论数据是什么，都显示一下平面坐标
    Call getlatlng '显示出平面坐标
    Timer4.Enabled = True '解析完成以后再把定时器4给打开
    

    
    
End If
End Function

'********************************************* 串口 网络组件 定位数据解析子程序*************************************************************

''Private Sub GPS_Data_Load()                       'IP 定位数据解析
'' On Error GoTo DataErrToEnd
'
' '           If IP_EnF = True Then              '如果不是网络定位模式  退出此子程序
'                oData = NetData                                                          '网络定位模式有有效时 解析来自于网络的数据
'            Else
'            If COMM_EnF = True Then
'                'oData = MSComm1.Input                                    '串口通信模式有效时 解析来自于串口的数据
'            End If
'            End If
'
'
'
'    S1 = "$GPRMC"
'    S2 = "*"
'    m = InStr(oData, S1)         '获取第一个字符出现的位置
'    n = InStr(oData, S2)         '获取第二个字符出现的位置
'
'    aData = Mid(oData, m, n)     '截取m n地址间间的内容，若数据长度不够，认为是无效，退出数据解析子程序。
'
'        If Len(aData) < 55 Then
'            Exit Sub
'         End If
'                                 GpsText.Text = aData & vbCrLf                     '测试用语句 在文本中显示运行这儿的数据  检测算法得到的数据串对不对 正式程序中屏掉
'                                 'GpsText.Text = GpsText.Text & vbCrLf & NetData    '将数据追加显示在文本框中　　注意　是换行＋追加
'
'                                        gprmc = Split(aData, ",")                   '用逗号分割字符串 分别装入相应的字符串数组gprmc元素中
'
'                                         '--------------------接收时间解析----------------------------------------
'                                                hour = Mid(gprmc(1), 1, 2)
'                                                       '==========================================================
'                                                        If hour > 15 Then
'                                                            hour = hour - 16        '格林威治时间转换东8区北京时间
'                                                        Else
'                                                            hour = hour + 8
'                                                        End If
'                                                        '=========================================================
'                                                minute = Mid(gprmc(1), 3, 2)        '从字符串数组gprmc(1)中 取得第3个起的两位数据作为分钟
'                                                second = Mid(gprmc(1), 5, 2)        '取秒字符串
'
'                                                TimeText.Text = TimeValue(hour & ":" & minute & ":" & second)    '在文本显示 收到并转换后的时间
'                                        '-------------------------------------------------------------------------
'                                                         ' Latitude = CDbl(gprmc(3)) / 100             'CDbl字符串转换为双精度值
'                                                         ' Longitude = CDbl(gprmc(5)) / 100
'
'                                                        Dim TEMP_La1 As String
'                                                        Dim TEMP_La2 As String
'                                                        Dim TEMP_Lo1 As String
'                                                        Dim TEMP_Lo2 As String
'
'                                                    '************将GPS小数部分除以60换算成 dd度ddd分的形式******
'                                                    TEMP_La1 = Mid(gprmc(3), 1, 2)
'                                                    TEMP_La2 = Mid(gprmc(3), 3, Len(gprmc(3))) / 60
'                                                    TEMP_La2 = Format(TEMP_La2, ".000000")        '将数据转换成这种格式显示，不然会自动显示成科学计数法
'
'
'                                                    TEMP_Lo1 = Mid(gprmc(5), 1, 3)
'                                                    TEMP_Lo2 = (Mid(gprmc(5), 4, Len(gprmc(5)))) / 60
'
'                                                    TEMP_Lo2 = Format(TEMP_Lo2, ".000000")
'                                                     ' Latitude =TEMP_La2
'                                                     ' Longitude =TEMP_Lo2
'                                                     '************************************************************
'
'
'                                                Text3.Text = TEMP_La1 + TEMP_La2   '文本框中显示纬度
'                                                Text4.Text = TEMP_Lo1 + TEMP_Lo2   '文本框中显示经度
'
'                                                '.................................................
'                                                Speed = CDbl(gprmc(7)) * 1.609     '速度转换
'                                                Text_speed.Text = Speed            '文本框显示速度
'                                                '..................................................
'DataErrToEnd:                                     '如果遇到错误 直接跳转到这儿
'End Sub
'*****************************************************************************************************************************************************
'Private Sub tcpserver_Close()           '关闭服务器端
'    tcpserver.Close
'    tcpserver.Listen
'End Sub
'****************************  TCP 联接处理 ***********************
'Private Sub tcpserver_ConnectionRequest(ByVal requestID As Long)    '有接入请求  就转入这里运行。注意SOCKET 属性要修改成 tcpserver

'    If tcpserver.State <> sckClosed Then
'        tcpserver.Close
'    End If
'
'    tcpserver.accept requestID                                '自动接受请求ID
'    PORT.Text = tcpserver.RemotePort
'    CONECT_IP.Text = CStr(tcpserver.RemoteHostIP)             '显示终端接入的IP
'
    
'End Sub
'***************************** 接收数据处理 ***********************
'Private Sub tcpserver_DataArrival(ByVal bytesTotal As Long)        '当有数据输入时 转入这里运行
'
'    tcpserver.GetData NetData                                       ''得到对方发送过来的数据
'
'    GpsText.Text = NetData
'
'    Call GPS_Data_Load                                               '调用数据解析程序。  将它写成一个通用模块 ， 根据网络和串口有效标志分别解析
'
'End Sub
'*********************************************************************

'
''*********************************************串口组件应用函数*************************************************************
''根据串口数据的特点 先截取GMRMC和*之间的数据，再从中得到时间，A后的数据，N后的数据，和E后的数据 再分别进行显示
''标准协议数据格式例子:我们只从第一行中取得相关数据
''$GPRMC,130134.50,A,3504.38785,N,12024.31176,E,0.041,,041212,,,A*70
''$GPVTG,,T,,M,0.041,N,0.076,K,A*27
''$GPGGA,140134.50,3604.38785,N,12024.31176,E,1,06,1.35,40.8,M,5.4,M,,*51
''$GPGSA,A,3,25,22,31,18,32,12,,,,,,,2.66,1.35,2.29*00
''$GPGSV,3,1,09,12,43,059,31,18,34,168,42,22,63,213,46,25,63,120,50*7C
''$GPGSV,3,2,09,31,34,256,49,32,08,320,36,40,11,254,42,42,41,142,44*70
''$GPGSV,3,3,09,50,41,142,42*41
''$GPGLL,3604.38785,N,12024.31176,E,140134.50,A,A*68
''*******************************************************************************
'
'Private WithEvents ctDoc As HTMLDocument, ctRefresh As Boolean
'Dim ctP180 As Double, ctNumJ As Double, ctNumW As Double, ctZ As Double
'Dim ctX As Long, ctY As Long, ctS As Long, ctXs As Long, ctYs As Long, ctF As String
'
'
'Private Type BitMap
'   bmType As Long         '图像类型：0 表示是位图
'   bmWidth As Long        '图像宽度（像素）
'   bmHeight As Long       '图像高度（像素）
'   bmWidthBytes As Long   '每一行图像的字节数
'   bmPlanes As Integer    '图像的图层数
'   bmBitsPixel As Integer '图像的位数
'   bmBits As Long         '位图的内存指针
'End Type
'Private Declare Function GetObject Lib "gdi32" Alias "GetObjectA" (ByVal hObject As Long, ByVal nCount As Long, lpObject As Any) As Long
'Private Declare Function GetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long
'Private Declare Function SetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long
'
'
'
''*****************************布尔型位标志变量定义******************************
'Dim Bit_Flag        As Boolean
'Dim FindMeEnF       As Boolean  '引导码判定有效标志位
'
'Dim timer2enf As Boolean        '是否启用定时器2
'Dim comdclick As Boolean        '是否按下查询坐标按键
'
'Dim COMM_EnF        As Boolean  'IP定位有效标志位
'Dim IP_EnF          As Boolean  'IP定位有效标志位
''*****************************串口通信 变量定义*********************************
'Dim Rx_DataBag  As String                    '定义接收数据字符串
'Dim Data         As String                    '定义数据
'Dim DataLen     As Integer                   '定义数据长度
'Dim Data_Cnt1   As Integer                   '定义数据个数计数
''---------------------------------------------------------------
''*****************************字符串 变量定义************************************
'
'Dim gprmc()     As String        '收到的定位数据字符串
'Dim status      As Boolean      '状态标志位 布尔值
'Dim latitude    As Double       '纬度
'Dim longitude   As Double       '经度
'Dim Speed       As Double       '速度
'
'Dim ZoomNO      As Integer      '地图显示的放大系数 取值 0--20  暂时不用
''********************** 显示时间变量定义：时　分　秒 当前时间********************
'Dim hour        As Integer
'Dim minute      As Integer
'Dim second      As Integer
'Dim NowTime     As Date
''*******************     GPS 解析中间变量     ************************************
'Dim oData       As String
'Dim aData       As String
'Dim NetData     As String
'
'Dim m           As Long
'Dim n           As Long
'Dim MsgCount    As Long             '声明一个长整型量,接收数据包个数
'
'Dim S1          As String
'Dim S2          As String
'
'
''Private Sub Command1_Click()
'
''End Sub
'
''Private Sub Command1_Click()
'
''End Sub
'
''Private Sub Command1_Click()                     '单击 我的位置刷新按钮 显示我的坐标
'
'    'FindMeEnF = True
'
'    'Call Findme                                 '调用查找地图程序
'
''End Sub
'
'Private Sub Command10_Click()
'Text2.Text = "4fast"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
'Private Sub Command11_Click()
'Text2.Text = "right"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
'Private Sub Command12_Click()
'Text2.Text = "left"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
'Private Sub Command13_Click()
'Text2.Text = "stop"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
'Private Sub Command14_Click()
'Text2.Text = "back"
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
'Private Sub Command15_Click()
'
'Kill "d:\testfile.txt"   '我最喜欢的一个函数，功能是删除一个文件，函数名是无与伦比的霸气
'Kill "d:\gpscoord.txt"
'
'
'Unload Me '卸除窗体
'End Sub
'
'
'Private Sub Command16_Click()
'
'    Call hexsend
'    j = 0
'
'End Sub
'
'Private Sub Command2_Click()                    '单击 查找坐标 显示输出框所在的地图位置  显示我的坐标
'
'
'    FindMeEnF = True
'
'    comdclick = True
'
'    Call Findme                                     '调用查找地图程序
'
'
'
'End Sub
'
'
'
'Private Sub Findme()                            '单击 查找坐标 显示输出框所在的地图位置  显示我的坐标
'
'    If FindMeEnF = True Then
'
'        If ((Text3.Text <> "") And (Text4.Text <> "")) Then
'
'            'If (comdclick = True) Then
'            'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng(10,118),{icon:myIcon1}))", "javascript"
'            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & ")),{icon:myIcon1})", "javascript" '添加标注
'            'WebBrowser1.Document.parentWindow.execScript "google.maps.LatLng(" & Text3 & "," & Text4 & ");", "javascript"            '显示指定坐标点，缩放等级10
'            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & ")),{icon: myIcon})", "javascript" '添加标注
'            'WebBrowser1.Document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng(" & Text3 & "," & Text4 & ")),{icon: myIcon1}))", "javascript" '添加标注
'                'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & "),{icon:myIcon1}))", "javascript" '添加标注,这句话是可以的，在不用定时器调用的时候
'
'            'End If
'
'
'            'If ((latd > 0.01) And (latd < 1) And (lngd > 0.01) And (lngd < 1)) Then
'
'                'comdclick = False
'                'WebBrowser1.document.parentWindow.execScript "map.addOverlay(new GMarker(new GLatLng( " & Text3 & "," & Text4 & "),{icon:myIcon1}))", "javascript" '添加标注,这句话是可以的，在不用定时器调用的时候
'
'            'End If
'        End If
'
'    End If
'
'End Sub
'
'Private Sub Command3_Click()
'    WebBrowser1.document.parentWindow.execScript "map.clearOverlays()", "javascript"                                                     '清除所有标注
'    Text3.Text = 0                     '清空显示纬度
'    Text4.Text = 0                     '清空显示经度
'    Text_speed.Text = 0                '清空显示速度
'    TimeText.Text = 0                  '清空显示时间
'End Sub
'
''Private Sub Command6_Click()
'
''End Sub
'
''Private Sub Command5_Click()
'
''End Sub
'
''Private Sub Command6_Click()
'
''End Sub
'
''Private Sub Command4_Click()
'
''End Sub
'
''Private Sub Command4_Click()                '单击分别进行串口显示内容、使能有效和无效的切换'
'
'        'If Command4.Caption = "串口定位" Then
'        '    Command4.Caption = "串口开启"
'        '    COMM_EnF = True
'        'Else
'        'If Command4.Caption = "串口开启" Then
'        '    Command4.Caption = "串口关闭"
'        '    COMM_EnF = False
'        '
'        ' Else
'        ' If Command4.Caption = "串口关闭" Then
'        '    Command4.Caption = "串口开启"
'        '    COMM_EnF = True
'        '  End If
'        ' End If
'        'End If
'       '
'       ' IP_EnF = False
'       ' Frame1.Visible = True                                    '串口设置框架 可见
'       ' Frame2.Visible = False                                   '网络设置框架 不可见
'
''End Sub
'
''Private Sub Command5_Click()                '单击网络定位控制按钮
'
'    'If Command5.Caption = "网络定位" Then
'    '   Command5.Caption = "网络开启"
'    '   IP_EnF = True
'    '   COMM_EnF = False     '这里可以加入　网络开启使能
'    'Else''
'
'    'If Command5.Caption = "网络开启" Then
'    '   Command5.Caption = "网络关闭"
'    '          IP_EnF = False
'    '          COMM_EnF = True
'    '
'    'Else
''
''     If Command5.Caption = "网络关闭" Then
''        IP_EnF = True
''        COMM_EnF = False
''        Command5.Caption = "网络开启"
''    End If
''    End If
''    End If
''
''    Frame1.Visible = False                  '网络定位时　串口定位不可见
''    Frame2.Visible = True                  '显示网络定位设置
''
''
''
''End Sub
'
'
''Private Sub Command6_Click()                     '点击连接网络按钮
'' On Error GoTo ButtonErrToEnd
'''************************  载入TCP服务器设置  *****************************
''    tcpserver.LocalPort = RandomPort.Text   '用户自己设定的端口号
''
''    tcpserver.Listen            '服务器开启监听标志
''    IP_EnF = True               '网络定位标志位有效
''ButtonErrToEnd:
''End Sub                         '操作结束
'
'
'
'
'
'
'Private Sub Command9_Click()
'
'
'Dim x1 As Double
'Dim y1 As Double
''Call GaussProjCal(121.2632423, 31.34234, x1, y1)
'
''Label4.Caption = "a=" & x1 & "b=" & y1
'
'Call getlatlng
'
'End Sub
'
'
'Private Sub Form_Load()         '当窗体运行时,首先执行它下面的语句
'
'Dim i As Integer
'i = 1
'ctP180 = 4 * Atn(1) '圆周率
'ctS = 256           '每张图片的大小尺寸
'
'
'    timer2findme = 0
'
'    Open "d:\testfile.Txt" For Output As #1 '在D盘创建一个新文件
'    Open "d:\gpscoord.txt" For Output As #2
'    Close #1 '如果该文件已经存在，新数据覆盖，不用担心读到的是前面几次的数据
'    Close #2
'
'   Picture1.Picture = LoadPicture("d:\\s0271.jpg")
'
'   Me.ScaleMode = 3:
'   Picture1.ScaleMode = 3
'   Picture1.AutoSize = True: Picture1.AutoRedraw = True
'   Picture1.ToolTipText = "双击恢复原图形"
'
'   ctP180 = 4 * Atn(1) '圆周率
'
'
'
'   '设置控件位置，实际可以在设计窗体时完成
'   Dim W11 As Long
'   W11 = Me.TextWidth("A")
'
'
'   Text5.Move W11 * 1, W11 * 80, W11 * 12
'   Picture1.Move W11 * 20, W11 * 70, W11 * 20, W11 * 20
'
' On Error GoTo ErrToEnd
'
'    WebBrowser1.navigate App.Path & "\GoogleMap.html"  '载入谷歌地图网页
'
'    Command1.Enabled = False
'    Command2.Enabled = False
'    Command3.Enabled = False
'    '****************************界面载入时 串口数据初始化*********************
'    'MSComm1.CommPort = 1                                '串口1
'    'MSComm1.Settings = "9600,n,8,1"             '波特率
'    'MSComm1.InBufferCount = 0
'    'MSComm1.InputLen = 0
'    'MSComm1.InBufferSize = 1024                 '输入缓冲区大小
'    'MSComm1.OutBufferSize = 512
'    'MSComm1.OutBufferCount = 0
'    'MSComm1.RThreshold = 512               '每次接收512个数据再产生 MSCOMM 事件 。这个值 很关键 ， 它决定 接收中断再次产生的时间
'    'MSComm1.SThreshold = 0
'    'MSComm1.PortOpen = False                '打开软件时 就打开了串口 接收到数据解析时 根据网络/串口有效标志位进行决定解析来自哪种类型的接口
'
'
'    MSComm1.InBufferCount = 0          '自动清缓冲区
'    MSComm1.InBufferSize = 1024                 '输入缓冲区大小
'    MSComm1.OutBufferSize = 512
'    MSComm1.CommPort = 9                  ' 设置通信端口号为COM1
'    MSComm1.Settings = "9600,n,8,1"       ' 设置串口1参数\
'    MSComm1.InputMode = 0                  ' 接收文本型数据
'    'MSComm1.PortOpen = True                 ' 打开通信端口1
'    'MSComm1.RThreshold = 55
'
'
'
'
'
'ErrToEnd:
'End Sub                                    '结束 Private Sub Form_Load()
'
'Private Sub GpsText_Change()               '串口接收显示文本框
'
'End Sub
'
'
'
'
'Private Sub MSComm1_OnComm()
'
'    Dim buf2$
'
'    Dim buf4$
'    Dim buf5$
'
'
'
'    Dim i As Integer
'
'
'    'buf = MSComm1.Input    ' 将缓冲区内的数据读入buf变量中
'
'    'Call resolve
'
''    buf2 = "hd"
''
''    buf4 = "lt"
''    buf5 = "lg"
''
''
''    If Len(buf) <> 0 Then         ' 判断缓冲区内是否存在数据
''
''        'Text1.Text = Text1.Text + Chr(13) + Chr(10) + buf      '回车换行
''
''         'Text1.Text = buf   '没必要的时候不显示
''
''        If (InStr(buf, buf2) <> 0) Then '如果找得到方位角的标志
''
''            buf3 = Mid(buf, InStr(buf, buf2) + 2, 10)
''
''            delta = Abs(Val(buf3) - Val(buf6))
''
''            buf6 = buf3
''
''
''        ElseIf ((InStr(buf, buf4) <> 0)) Then
''            Text3.Text = Mid(buf, InStr(buf, buf4) + 2, 10)
''        ElseIf ((InStr(buf, buf5) <> 0)) Then
''            Text4.Text = Mid(buf, InStr(buf, buf5) + 2, 10)
''
''
''        End If
''    End If
'End Sub
'
''Private Sub MSComm1_OnComm()               '串口通信数据解析
'
'    'On Error GoTo ErrHdl
'
'    'Call GPS_Data_Load                      '调用数据解析程序。  将它写成一个通用模块 ， 根据网络和串口有效标志分别解析
'
'
'
''ErrHdl:                                     '如果遇到错误 直接跳转到这儿
''End Sub
'
'
'
'
'
'
'Private Sub Option1_Click()
'    'MSComm1.Settings = "9600,n,8,1"  '设定串口参数
'    Option2.Value = False
'End Sub
'
'Private Sub Option2_Click()
'    'MSComm1.Settings = "4800,n,8,1"  '设定串口规定
'    Option1.Value = False
'
'End Sub
'
'
'
'Private Sub Text3_Change()          '纬度输出文本
'End Sub
'
'Private Sub Text4_Change()          '经度输出文本
'End Sub
'
'Private Sub TXTPORT_Change()
'
'End Sub
'
'
'
'
'
'
'
'
'
'
'Private Sub Timer2_Timer()
'
'
'Open "d:\\gpscoord.txt" For Output As #2
'If ((Text3.Text <> "") And (Text4.Text <> "")) Then
'    Print #2, Text3.Text & vbCrLf
'    Print #2, Text4.Text & vbCrLf
'    End If
'Close #2
'
'
'
'End Sub
'
'Private Sub WebBrowser1_DocumentComplete(ByVal pDisp As Object, URL As Variant) '地图加载完成前 按钮无效
'
'    Do While WebBrowser1.Busy '等待加载完成.
'
'    MSComm1.PortOpen = False
'    Timer2.Enabled = False
'    Timer1.Enabled = False
'    Command1.Enabled = False
'    Command2.Enabled = False
'    Command3.Enabled = False
'
'    Loop
'
'    '如果加载完成
'    Timer2.Enabled = True
'    Timer1.Enabled = True
'    Command1.Enabled = True
'    Command2.Enabled = True
'    Command3.Enabled = True
'    MSComm1.PortOpen = True
'
'End Sub
'
'Private Sub Winsock1_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
'
'End Sub
'
''********************************************* 串口 网络组件 定位数据解析子程序*************************************************************
'
'''Private Sub GPS_Data_Load()                       'IP 定位数据解析
''' On Error GoTo DataErrToEnd
''
'' '           If IP_EnF = True Then              '如果不是网络定位模式  退出此子程序
''                oData = NetData                                                          '网络定位模式有有效时 解析来自于网络的数据
''            Else
''            If COMM_EnF = True Then
''                'oData = MSComm1.Input                                    '串口通信模式有效时 解析来自于串口的数据
''            End If
''            End If
''
''
''
''    S1 = "$GPRMC"
''    S2 = "*"
''    m = InStr(oData, S1)         '获取第一个字符出现的位置
''    n = InStr(oData, S2)         '获取第二个字符出现的位置
''
''    aData = Mid(oData, m, n)     '截取m n地址间间的内容，若数据长度不够，认为是无效，退出数据解析子程序。
''
''        If Len(aData) < 55 Then
''            Exit Sub
''         End If
''                                 GpsText.Text = aData & vbCrLf                     '测试用语句 在文本中显示运行这儿的数据  检测算法得到的数据串对不对 正式程序中屏掉
''                                 'GpsText.Text = GpsText.Text & vbCrLf & NetData    '将数据追加显示在文本框中　　注意　是换行＋追加
''
''                                        gprmc = Split(aData, ",")                   '用逗号分割字符串 分别装入相应的字符串数组gprmc元素中
''
''                                         '--------------------接收时间解析----------------------------------------
''                                                hour = Mid(gprmc(1), 1, 2)
''                                                       '==========================================================
''                                                        If hour > 15 Then
''                                                            hour = hour - 16        '格林威治时间转换东8区北京时间
''                                                        Else
''                                                            hour = hour + 8
''                                                        End If
''                                                        '=========================================================
''                                                minute = Mid(gprmc(1), 3, 2)        '从字符串数组gprmc(1)中 取得第3个起的两位数据作为分钟
''                                                second = Mid(gprmc(1), 5, 2)        '取秒字符串
''
''                                                TimeText.Text = TimeValue(hour & ":" & minute & ":" & second)    '在文本显示 收到并转换后的时间
''                                        '-------------------------------------------------------------------------
''                                                         ' Latitude = CDbl(gprmc(3)) / 100             'CDbl字符串转换为双精度值
''                                                         ' Longitude = CDbl(gprmc(5)) / 100
''
''                                                        Dim TEMP_La1 As String
''                                                        Dim TEMP_La2 As String
''                                                        Dim TEMP_Lo1 As String
''                                                        Dim TEMP_Lo2 As String
''
''                                                    '************将GPS小数部分除以60换算成 dd度ddd分的形式******
''                                                    TEMP_La1 = Mid(gprmc(3), 1, 2)
''                                                    TEMP_La2 = Mid(gprmc(3), 3, Len(gprmc(3))) / 60
''                                                    TEMP_La2 = Format(TEMP_La2, ".000000")        '将数据转换成这种格式显示，不然会自动显示成科学计数法
''
''
''                                                    TEMP_Lo1 = Mid(gprmc(5), 1, 3)
''                                                    TEMP_Lo2 = (Mid(gprmc(5), 4, Len(gprmc(5)))) / 60
''
''                                                    TEMP_Lo2 = Format(TEMP_Lo2, ".000000")
''                                                     ' Latitude =TEMP_La2
''                                                     ' Longitude =TEMP_Lo2
''                                                     '************************************************************
''
''
''                                                Text3.Text = TEMP_La1 + TEMP_La2   '文本框中显示纬度
''                                                Text4.Text = TEMP_Lo1 + TEMP_Lo2   '文本框中显示经度
''
''                                                '.................................................
''                                                Speed = CDbl(gprmc(7)) * 1.609     '速度转换
''                                                Text_speed.Text = Speed            '文本框显示速度
''                                                '..................................................
''DataErrToEnd:                                     '如果遇到错误 直接跳转到这儿
''End Sub
''*****************************************************************************************************************************************************
''Private Sub tcpserver_Close()           '关闭服务器端
''    tcpserver.Close
''    tcpserver.Listen
''End Sub
''****************************  TCP 联接处理 ***********************
''Private Sub tcpserver_ConnectionRequest(ByVal requestID As Long)    '有接入请求  就转入这里运行。注意SOCKET 属性要修改成 tcpserver
'
''    If tcpserver.State <> sckClosed Then
''        tcpserver.Close
''    End If
''
''    tcpserver.accept requestID                                '自动接受请求ID
''    PORT.Text = tcpserver.RemotePort
''    CONECT_IP.Text = CStr(tcpserver.RemoteHostIP)             '显示终端接入的IP
''
'
''End Sub
''***************************** 接收数据处理 ***********************
''Private Sub tcpserver_DataArrival(ByVal bytesTotal As Long)        '当有数据输入时 转入这里运行
''
''    tcpserver.GetData NetData                                       ''得到对方发送过来的数据
''
''    GpsText.Text = NetData
''
''    Call GPS_Data_Load                                               '调用数据解析程序。  将它写成一个通用模块 ， 根据网络和串口有效标志分别解析
''
''End Sub
''*********************************************************************
'
'
'
'Private Sub Webbrowser1_DownloadComplete()
'   Set ctDoc = WebBrowser1.document
'End Sub
'
'
'
'
'
'
'Private Function GaussProjCal(longitude As Double, latitude As Double, X As Double, Y As Double)
'
'Dim A1, e2, e1, a, Bc, c, d, n1, x1, dl, n, t, n2, pi, xval, yval As Double
'Dim m, L0 As Integer
'Dim n11, M1, n12, t1, BB, B0, B1, B2, B4, B6, r As Double
'
'pi = 4 * Atn(1) '圆周率
'm = CInt(longitude / 6) + 1
'L0 = 6 * m - 3
'dl = longitude - L0
'dl = dl * pi / 180
'latitude = latitude * pi / 180
'A1 = 6378245
'e1 = 0.006738525415
'e2 = 0.006693421623
'a = 1.0050517739
'Bc = 0.00506237764
'c = 0.00001062451
'd = 0.00000002081
'n1 = A1 / Sqr(1 - e2 * Sin(latitude) * Sin(latitude))
't = Tan(latitude)
'n = 0.006738525415 * Cos(latitude) * Cos(latitude)
'x1 = A1 * (1 - e2) * (a * latitude - Bc / 2 * Sin(2 * latitude) + c / 4 * Sin(4 * latitude) - d / 6 * Sin(6 * latitude))
'xval = x1 + dl * dl / 2 * n1 * Sin(latitude) * Cos(latitude) * (1 + dl * dl * Cos(latitude) * Cos(latitude) / 12 * (5 - t * t + 9 * n + 4 * n * n) + dl * dl * dl * dl * Cos(latitude) * Cos(latitude) * Cos(latitude) * Cos(latitude) / 360 * (61 - 58 * t * t + t * t * t * t))
'yval = dl * n1 * Cos(latitude) * (1 + dl * dl * Cos(latitude) * Cos(latitude) / 6 * (1 - t * t + n) + dl * dl * dl * dl * Cos(latitude) * Cos(latitude) * Cos(latitude) * Cos(latitude) / 120 * (5 - 18 * t * t + t * t * t * t + 14 * n - 58 * n * t * t))
'yval = yval + 500000 + m * 1000000
'X = xval
'Y = yval
'
'End Function
'
'
'Private Function getlatlng()
'
'Dim aas, bs As String
'Dim lng As Double
'Dim lat As Double
'Dim x1 As Double
'Dim y1 As Double
'Dim coord(0 To 99) As Double
'
'Dim i As Integer
'
'i = 0
'Open "d:\\testfile.txt" For Input As #1
'Do While Not EOF(1) '
'Input #1, aas
'Input #1, bs
'
'lng = Val(aas)  '每次读数据出来，经度在前，纬度在后
'lat = Val(bs)
'
'
''调用经纬度解析函数直接算出平面坐标
'Call GaussProjCal(lng, lat, x1, y1)
'
'
'coord(i) = x1
'i = i + 1
'coord(i) = y1
'Label4.Caption = "X1=" & coord(0) & "Y1=" & coord(1)
'Loop
'
'Close #1 ' 关闭文件
'
'
''提取数据给变量
'
'
''Label4.Caption = "a=" & a & "b=" & B & "c=" & c & "d=" & d
'
'End Function
'
'
'
'Private Sub GetBmpDat(Kj As Control, W As Long, H As Long, B() As Byte, bs As Long, BytesW As Long, Ps As Long)
'   '获取控件 Kj 的图像数据
'   Dim MapInf As BitMap
'   GetObject Kj.Image, Len(MapInf), MapInf '用 MapInf 得到 Kj 的图像信息
'   W = MapInf.bmWidth: H = MapInf.bmHeight '图像宽度、高度（像素）
'   BytesW = MapInf.bmWidthBytes            '每行占用字节数
'   Ps = BytesW \ W                         '每个像素字节数(一般为4)
'   bs = W * H * Ps                         '总字节数=宽度*高度*每个像素字节
'   ReDim B(0 To bs - 1)
'   GetBitmapBits Kj.Image, bs, B(0)        '将 Kj 图像所有像素点的颜色值读入二进数组 B()
'End Sub
'
'Private Function XYtoIndex(X As Long, Y As Long, BytesW As Long, Ps As Long) As Long
'   '返回图像坐标 x,y 在颜色数组中的序号位置。
'   'BytesW：每行图像占用字节数，Ps：每个像素点占用字节数(一般为4)
'   XYtoIndex = Y * BytesW + X * Ps
'End Function
'
'Private Sub Zhuan(ToJ As Single, x0 As Long, y0 As Long, ByVal X As Long, ByVal Y As Long, x1 As Long, y1 As Long)
'   '将点 x,y 围绕 x0,y0 顺时针旋转 ToJ 弧度，用 x1,y1 返回旋转后的位置
'   '注意：要预先设置圆周率 ctP180 = 4 * Atn(1)
'    Dim S As Single, j As Single
'
'    X = X - x0: Y = Y - y0
'    S = Sqr(X ^ 2 + Y ^ 2)               'X,Y 与 x0,y0 的距离
'    If S = 0 Then j = 0 Else j = Y / S   '与水平线的夹角的正弦值
'
'    If Abs(j) >= 1 Then
'       If j > 0 Then j = ctP180 * 0.5 Else j = -ctP180 * 0.5 '90 度时的特殊情况
'    Else
'       j = Atn(j / Sqr(-j * j + 1)) '与水平线的夹角
'    End If
'
'    If X < 0 Then j = -ctP180 - j
'    x1 = x0 + S * Cos(j + ToJ): y1 = y0 + S * Sin(j + ToJ) '返回旋转后的位置
'End Sub
'
'
'
'
'Private Function rotation()
'   '旋转图片
'   Dim W1 As Long, H1 As Long, B1() As Byte, Bs1 As Long, BytesW1 As Long, Ps1 As Long
'   Dim W2 As Long, H2 As Long, B2() As Byte, Bs2 As Long, BytesW2 As Long, Ps2 As Long
'   Dim S1 As Long, S2 As Long, X As Long, Y As Long, x1 As Long, y1 As Long
'   Dim CenX1 As Long, CenY1 As Long, CenX2 As Long, CenY2 As Long
'   Dim KjFocus As Control, ToJ As Single
'
'   'Text5.Enabled = True
'
'   ToJ = Val(buf6) / 180 * ctP180 '旋转角度转弧度
'
'   Set KjFocus = Me.ActiveControl '记忆具有焦点的控件
'
'
'   'Text5.Enabled = False
'
'   '下面一条语句看似可有可无，实际有两个作用：恢复旋转前控件的原图像和大小
'   Picture1.Picture = Picture1.Picture
'
'   '旋转前图像数据：宽度，高度，颜色数组，总字节数，每行字节数，每像素字节数
'   GetBmpDat Picture1, W1, H1, B1, Bs1, BytesW1, Ps1
'   CenX1 = Int(W1 * 0.5): CenY1 = Int(H1 * 0.5)       '旋转前的图像中心点
'
'   '计算旋转后控件的高度和宽度，要预先设置窗体和图片的 ScaleMode 为 3（像素）
'   W2 = Abs(W1 * Cos(ToJ)) + Abs(H1 * Sin(ToJ))  '旋转后：图像宽度
'   H2 = Abs(H1 * Cos(ToJ)) + Abs(W1 * Sin(ToJ))  '旋转后：图像高度
'   X = Picture1.Width - Picture1.ScaleWidth      '图片框边框：宽度
'   Y = Picture1.Height - Picture1.ScaleHeight    '图片框边框：高度
'   'Picture1.Move Picture1.Left, Picture1.Top, X + W2, Y + H2
'
'   '下面的 Picture1.Cls 语句此处的作用主要不是清除图像，而是更新控件
'   '的 Image 属性，使调用 GetBmpDat 时能正确取得图像数据
'   'Picture1.Cls
'   Picture1.Line (0, 0)-(W2, H2), &H0&, BF
'
'   '旋转后图像数据：宽度，高度，颜色数组，总字节数，每行字节数，每像素字节数
'   GetBmpDat Picture1, W2, H2, B2, Bs2, BytesW2, Ps2
'   CenX2 = Int(W2 * 0.5): CenY2 = Int(H2 * 0.5)       '旋转后：图像中心点
'
'   '显示信息
'   Picture1.CurrentX = 5: Picture1.CurrentY = 5
'   Picture1.Print "处理中，请稍候..."
'   Me.Refresh
'
'   W1 = W1 - 1: H1 = H1 - 1
'   For X = 0 To W2 - 1
'   For Y = 0 To H2 - 1
'      Zhuan -ToJ, CenX2, CenY2, X, Y, x1, y1           '用 x1,y1 获得旋转坐标
'      x1 = x1 - CenX2 + CenX1: y1 = y1 - CenY2 + CenY1 '转变为旋转前的坐标
'
'      S2 = XYtoIndex(X, Y, BytesW2, Ps2)    '旋转后：像素点在数组 B2 中的索引
'      If x1 < 0 Or x1 > W1 Or y1 < 0 Or y1 > H1 Then
'         B2(S2 + 2) = 0: B2(S2 + 1) = 0: B2(S2) = 0 '超出原图像区域，设为白色
'      Else
'         S1 = XYtoIndex(x1, y1, BytesW1, Ps1)  '旋转前：像素点在数组 B1 中的索引
'         B2(S2 + 2) = B1(S1 + 2): B2(S2 + 1) = B1(S1 + 1): B2(S2) = B1(S1) '红绿蓝
'      End If
'   Next
'   Next
'
'   SetBitmapBits Picture1.Image, Bs2, B2(0) '将 Picture1 的图像设置为旋转后的二进数组 B2()
'
'
'   'Text5.Enabled = True
'   On Error Resume Next
'   KjFocus.SetFocus  '还原具有焦点的控件
'
'
'
'End Function
'
'Private Sub Picture1_DblClick()
'   '下面语句看似可有可无，实际有两个作用：恢复旋转前控件的原图像和大小
'   Picture1.Picture = Picture1.Picture
'End Sub
'
'
'
'' 把字符通过串口发送出去
' Private Sub Command7_Click()
'If Text2.Text = "" Then
'pp = MsgBox("发送的数据不能为空！", 16)
' Exit Sub
'End If
'MSComm1.Output = Trim(Text2.Text)
' For i = 1 To 20000000
'Next i
'End Sub
'
' ' 通过时钟控制来自动接收字符
'Private Sub Timer1_Timer()
'
'    If (Timer1.Enabled = True) Then
'
'
'        buf = MSComm1.Input
'        'If ((delta > 0.1) And (delta < 5)) Then
'        If (buf6 <> "") Then
'            Call rotation
'
'        End If
'    End If
'
'End Sub
'
'' 关闭通信端口,停止程序运行
'Private Sub Command8_Click()
'MSComm1.PortOpen = False
''Unload Me
'End Sub
'
'
'Private Function hexsend()
'    Dim sj() As String
'    Dim sjByt() As Byte
'    Dim i As Long
'
'
'    Dim sjByt1() As Byte
'    Dim highbit, lowbit As String
'
'
'    sj = Split(Text2, " ")
'    ReDim sjByt(UBound(sj))
'    ReDim sjByt1(1000)
'
'
'    If Check1.Value = 0 Then '如果不勾选十六进制显示，则数据直接转成十六进制发出去
'        For i = 0 To UBound(sj)
'            sjByt(i) = Val("&H" & Str(Val(Left(sj(i), 2)))) '字符数组转成十六进制发送出去
'        Next i
'        MSComm1.Output = sjByt
'
'    ElseIf Check1.Value = 1 Then '如果勾选了十六进制显示，则数据转成十六进制后分别转成ascii码发出去
'        For i = 0 To UBound(sj)
'            sjByt(i) = Val("&H" & Str(Val(Left(sj(i), 2)))) '字符数组转成十六进制发送出去
'
'            highbit = sjByt(i) And &HF0
'            highbit = highbit / 16
'
'            lowbit = sjByt(i) And &HF
'
'
'            If (highbit >= 0 And highbit <= 9) Then
'                highbit = highbit + &H30
'            ElseIf (highbit >= a And highbit <= f) Then
'                highbit = highbit + &H37
'            End If
'            If (lowbit >= 0 And lowbit <= 9) Then
'                lowbit = lowbit + &H30
'            ElseIf (lowbit >= a And lowbit <= f) Then
'                lowbit = lowbit + &H37
'            End If
'
'            sjByt1(j) = CStr(highbit) '分别把每一位数字都取出来放到一个新的数组里
'            sjByt1(j + 1) = lowbit
'            sjByt1(j + 2) = Str(&H20) '由于字符根据空格隔开，所以取出来以后要把空格加回去
'            j = j + 3
'
'
'        Next i
'        MSComm1.Output = sjByt1
'    End If
'End Function
'
'

'
'
'
'
'
