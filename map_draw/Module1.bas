Attribute VB_Name = "Module1"

Public recordok As Integer
Public coord1(0 To 50) As Double
Public startmap As Integer
Public pathpointx As Integer
Public pathpointy As Integer
Public count1 As Integer
Public index2 As Integer

Public Const WH_MOUSE = 7 '���ع���
Public Const WH_MOUSE_LL = 14 'ȫ�ֹ���
Public Declare Function SetWindowsHookEx Lib "user32" Alias "SetWindowsHookExA" (ByVal idHook As Long, ByVal lpfn As Long, ByVal hmod As Long, ByVal dwThreadId As Long) As Long
Public Declare Function CallNextHookEx Lib "user32" (ByVal hHook As Long, ByVal nCode As Long, ByVal wParam As Long, lParam As Any) As Long
Public Declare Function UnhookWindowsHookEx Lib "user32" (ByVal hHook As Long) As Long
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Public Const WM_LBUTTONDOWN = &H201 '�����а���������
Public Const WM_LBUTTONUP = &H202 '�������ɿ�������
Public Const WM_MOUSEMOVE = &H200 '�������ƶ����
Public Const WM_RBUTTONDOWN = &H204 '�����а�������Ҽ�
Public Const WM_RBUTTONUP = &H205 '�������ɿ�����Ҽ�
Public Const WM_MOUSEWHEEL = &H20A '������
Public Const WM_NCLBUTTONDOWN = &HA1 '���ڱ������а���������
Public Const WM_NCLBUTTONUP = &HA2 '���ڱ���������������
Public Const WM_NCMOUSEMOVE = &HA0  '���ڱ��������ƶ����
Public Const WM_NCRBUTTONDOWN = &HA4 '���ڱ������а�������Ҽ�
Public Const WM_NCRBUTTONUP = &HA5 '���ڱ��������ɿ�����Ҽ�

Public hHook As Long
Public Type POINTAPI
        x As Long
        y As Long
End Type

Type MSLLHOOKSTRUCT
    pt As POINTAPI '�������Ļ���Ͻǵ�����x,y
    mouseData As Long '�������
    flags As Long '���
    time As Long 'ʱ���
    dwExtraInfo As Long '������Ϣ
End Type

Type MOUSEHOOKSTRUCT
    pt As POINTAPI '�������Ļ���Ͻǵ�����x,y
    hwnd As Long '������´��ڵľ��
    wHitTestCode As Long '������ڴ����е�λ�ã�����������߿��ұ߿��±߿򡣡���
    dwExtraInfo As Long '������Ϣ��ͨ��Ϊ0
End Type
Dim oMouseHookStruct As MSLLHOOKSTRUCT

Public Function MouseHookProc(ByVal idHook As Long, ByVal wParam As Long, ByVal lParam As Long) As Long

    
    CopyMemory oMouseHookStruct, ByVal lParam, Len(oMouseHookStruct)
'    Debug.Print "��ǰ���λ��-x:" & oMouseHookStruct.pt.x & "; y:" & oMouseHookStruct.pt.y
    Form1.Text2.Text = oMouseHookStruct.pt.x - 600
    Form1.Text3.Text = oMouseHookStruct.pt.y - 26
   
    Select Case wParam
        Case WM_LBUTTONDOWN, WM_NCLBUTTONDOWN
        '����������
'        Form1.Timer3.Enabled = True
        Form1.Picture1.DrawWidth = 3
        recordok = 1

        If ((startmap = 1) And (Val(Form1.Text2) > 0) And (Val(Form1.Text2) < 300) And (Val(Form1.Text3) > 0) And (Val(Form1.Text3) < 300) And (recordok = 1)) Then
            Form1.Picture1.DrawWidth = 5
            Form1.Picture1.Line (Val(Form1.Text2), Val(Form1.Text3))-(Val(Form1.Text2), Val(Form1.Text3)), RGB(255, 255, 0)
            coord1(index2) = Val(Form1.Text2)
            index2 = index2 + 1
            coord1(index2) = Val(Form1.Text3)
            index2 = index2 + 1
            If (count1 = 0) Then
                count1 = 1
                pathpointx = Val(Form1.Text2)
                pathpointy = Val(Form1.Text3)
            End If
            Form1.Picture1.DrawWidth = 3
            Form1.Picture1.Line (pathpointx, pathpointy)-(Val(Form1.Text2), Val(Form1.Text3)), RGB(0, 0, 0)
            pathpointx = Val(Form1.Text2)
            pathpointy = Val(Form1.Text3)
        End If
'            Debug.Print "�������"
'
        Case WM_LBUTTONUP, WM_NCLBUTTONUP
        '���������𣬴����ͼ�������
        Form1.Timer3.Enabled = False
        recordok = 0
'            Debug.Print "�������"
'        Case WM_RBUTTONDOWN, WM_NCRBUTTONDOWN
'            Debug.Print "�Ҽ�����"
'            Form1.Text1.Text = "hello"
'        Case WM_RBUTTONUP, WM_NCRBUTTONUP
'            Debug.Print "�Ҽ�����"
'        Case WM_MOUSEMOVE, WM_NCMOUSEMOVE
'            Debug.Print "����ƶ�"
'        Case WM_MOUSEWHEEL
'            Debug.Print "������"
    End Select
    MouseHookProc = CallNextHookEx(hHook, idHook, wParam, ByVal lParam)
End Function



'Public Function MouseHookProc(ByVal idHook As Long, ByVal lParam As Long) As Long
'    CopyMemory oMouseHookStruct, ByVal lParam, Len(oMouseHookStruct)
'    Debug.Print "��ǰ���λ��-x:" & oMouseHookStruct.pt.x & "; y:" & oMouseHookStruct.pt.y
'    Form1.Text2.Text = oMouseHookStruct.pt.x
'    Form1.Text3.Text = oMouseHookStruct.pt.y
''    Select Case wParam
''        Case WM_LBUTTONDOWN, WM_NCLBUTTONDOWN
''            Debug.Print "�������"
''
''        Case WM_LBUTTONUP, WM_NCLBUTTONUP
''            Debug.Print "�������"
''        Case WM_RBUTTONDOWN, WM_NCRBUTTONDOWN
''            Debug.Print "�Ҽ�����"
''            Form1.Text1.Text = "hello"
''        Case WM_RBUTTONUP, WM_NCRBUTTONUP
''            Debug.Print "�Ҽ�����"
''        Case WM_MOUSEMOVE, WM_NCMOUSEMOVE
''            Debug.Print "����ƶ�"
''        Case WM_MOUSEWHEEL
''            Debug.Print "������"
''    End Select
'    MouseHookProc = CallNextHookEx(hHook, idHook, ByVal lParam)
'End Function















