#include<math.h>

// ��������Ǳͧ����
typedef struct submarines_sizes
{
	int length;   //����
	int width;    //���
	int height;   //�߶�
}submarines_sizes, * p_submarines_sizes;

// ��������ը��
typedef struct bombshell_sizes
{
	int kill_radiu;			//ɱ�˰뾶
	int sigma;				//ˮƽ�����׼��
	int submarines_target;  //Ǳͧ������ȶ�λֵ
}bombshell_sizes, * p_bombshell_sizes;

