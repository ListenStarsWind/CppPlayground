#define _CRT_SECURE_NO_WARNINGS
#include"configuration.h"
int main()
{
	int import;//�Ƿ����������
	foreword();//ǰ�Ժ��������ڶ���Ϸ����˵����
	do
	{
import = PlayMenu();//����˵�������������ֵ����import��
		if (import == 1)
		{
			DifficultyMenu();//�ѶȲ˵������������Ѷ�ѡ��
			game();

		}

	} while (import);
	return 0;
}