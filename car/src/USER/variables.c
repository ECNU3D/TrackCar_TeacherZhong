#include "variables.h"
#include "stm32f10x.h"
#include "stdint.h"

u8 heartok=0;//�Ƿ����������������

u16 beat=0;
double seitatest=0;

u8 pathen=0;

double seita;

double head2,pitch2,roll2;

u8 coord[50];
u8 package[70]={0};//�����������������Լ���Դʣ�����

u8 pathrecord[1024];//������е�Ԥ��·��������
double pathrecord1[1024];//������е�Ԥ��·��������

u16 count;

// double speed=0;
u8 speeden=0;

u8 rotateok=0;

u8 rotateok1=0;
u8 pathok=0;

u16 pathlen=0;

u8 comd1[5]={0x68,0x04,0x00,0x04,0x08};//ͬʱ��ȡ�����Ƕ�
u8 comd2[5]={0x68,0x04,0x00,0x08,0x0c};//У׼����
u8 comd3[6]={0x68,0x05,0x00,0x0b,0x02,0x12};//���ò��������� ,9600
u8 comd4[6]={0x68,0x05,0x00,0x0f,0x10,0x15};//����ģ���ַ����,0x10
u8 comd5[6]={0x68,0x05,0x00,0x0c,0x01,0x12};//�Զ�Ӧ��ģʽ

u8 *command1=comd1;//ͬʱ��ȡ�����Ƕ�
u8 *command2=comd2;//У׼����
u8 *command3=comd3;//���ò��������� ,9600
u8 *command4=comd4;//����ģ���ַ����,0x10
u8 *command5=comd5;//�Զ�Ӧ��ģʽ

u8 *ps;

double latitude3=0;
double longitude3=0;

tTuoqiu tuoqiu1;
tTuoqiu *ptuoqiu=&tuoqiu1;

double gaosix3=0;
double gaosiy3=0;
double gaosix4=0;
double gaosiy4=0;

gaosiplain gaosiplain1;
gaosiplain *gaosi=&gaosiplain1;



// tTuoqiu ptuoqiu=&tuoqiu1;
// tTuoqiu tuoqiu1=
// {
// 	.LAT={0,1},
// 	.LNG={0,1},
// 	.latitude=&latitude3,
// 	.longitude=&longitude3
// };
// u8 LAT,LNG;//��������ָ��ָ���ž�γ�ȵ��ڴ��ַ
// double f1[100];
// double X;
// double Y;

// double longitude2;
// double latitude2;

// double gaussx;
// double gaussy;


// double *X2;
// double *Y2;

// double px=0;
// double py=0;
// u8 anglewide=10;
// u8 seitaok=0;
// u8 testcoord0[10];
// u8 testcoord1[10];
// u8 testcoord2[10];
// u8 testcoord3[10];
// double testcoord4[10];
// u8 receivepackage[70];//��Ž��յ��Ĵ���õ�����
// double heading;
// double roll;
// double pitch;
// u8 orderen=0;
// u16 jp=0;
// u8 *order7="4fast";//��������
// u8 *order8="4slow";//��������
// u8 *order6="6fast";//��������


// u8 *order1="1fast";//��������
// u8 *order2="2fast";//��������

// u8 *order3="3fast";//��������
// u8 *order4="4fast";//��������

// u8 *order5="5fast";//��������

// u8 *stop="stop";//ֹͣ����

// u8 *right="right";//��ת����
// u8 *left="left";//��ת����

// u8 *orgright="orgright";//ԭ����ת
// u8 *orgleft="orgleft";//ԭ����ת

// u8 *back="back";//��������

// u8 *emergency="instanthalt";

// u8 *remote="ARQ";

// u8 *path="P";