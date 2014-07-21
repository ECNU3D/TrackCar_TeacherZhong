#include "stm32f10x.h"

#ifndef _VAR_H_
#define	_VAR_H_
//����һ���࣬�����ž�γ������

extern u8 heartok;//�Ƿ����������������

extern u16 beat;
extern double seitatest;
extern u8 pathen;

extern double seita;

extern double head2,pitch2,roll2;

extern u8 coord[50];
extern u8 package[70];//����������������

extern u8 pathrecord[1024];//������е�Ԥ��·��������
extern double pathrecord1[1024];//������е�Ԥ��·��������

extern u16 count;

// extern double speed;
extern u8 speeden;

extern double gaussx;
extern double gaussy;

extern u8 rotateok;

extern u8 rotateok1;
extern u8 pathok;
extern u16 pathlen;

extern u8 comd1[5];//ͬʱ��ȡ�����Ƕ�
extern u8 comd2[5];//У׼����
extern u8 comd3[6];//���ò��������� ,9600
extern u8 comd4[6];//����ģ���ַ����,0x10
extern u8 comd5[6];//�Զ�Ӧ��ģʽ

extern u8 *command1;//ͬʱ��ȡ�����Ƕ�
extern u8 *command2;//У׼����
extern u8 *command3;//���ò��������� ,9600
extern u8 *command4;//����ģ���ַ����,0x10
extern u8 *command5;//�Զ�Ӧ��ģʽ

extern u8 *ps;

typedef struct 
{
		u8 LAT[16];
		u8 LNG[16];
		double *latitude;
		double *longitude;
		
}tTuoqiu;//��γ�Ƚṹ��

extern double latitude3;
extern double longitude3;

extern tTuoqiu tuoqiu1;
extern tTuoqiu *ptuoqiu;

typedef struct 
{
		double *gaosix;//δ��ƽ���ĸ�˹����
		double *gaosiy;
		double *gaosix1;//����ƽ���Ժ�ĸ�˹����
		double *gaosiy1;
		
}gaosiplain;//ƽ������ṹ��

extern double gaosix3;
extern double gaosiy3;
extern double gaosix4;
extern double gaosiy4;

extern gaosiplain gaosiplain1;
extern gaosiplain *gaosi;

#endif

// extern u8 LAT,LNG;//��������ָ��ָ���ž�γ�ȵ��ڴ��ַ
// extern double f1[100];
// extern double X;
// extern double Y;

// extern double longitude2;
// extern double latitude2;

// extern double *X2;
// extern double *Y2;

// extern double px;
// extern double py;
// extern u8 anglewide;
// extern u8 seitaok;
// extern u8 testcoord0[10];
// extern u8 testcoord1[10];
// extern u8 testcoord2[10];
// extern u8 testcoord3[10];
// extern double testcoord4[10];
// extern u8 receivepackage[70];//��Ž��յ��Ĵ���õ�����
// extern double heading;
// extern double roll;
// extern double pitch;
// extern u8 orderen;
// extern u16 jp;
// extern u8 *order7;//��������
// extern u8 *order8;//��������
// extern u8 *order6;//��������
// extern u8 *order1;//��������
// extern u8 *order2;//��������

// extern u8 *order3;//��������
// extern u8 *order4;//��������

// extern u8 *order5;//��������


// extern u8 *stop;//ֹͣ����

// extern u8 *right;//��ת����
// extern u8 *left;//��ת����

// extern u8 *orgright;//ԭ����ת
// extern u8 *orgleft;//ԭ����ת



// extern u8 *back;//��������

// extern u8 *emergency;

// extern u8 *remote;

// extern u8 *path;