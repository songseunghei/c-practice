#include <iostream>
#include<cstdlib>
#include<ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define UP 0
#define DOWN 1
#define SUBMIT 4 //���� �����̽���

//�ؿ� ������ �Լ��� ����� �ۼ����ش�
int keyControl();
void level();
void levelUPsound();
void levelUP();
void titleDraw();
void gotoxy(int, int);
int menu();
void info();

//������ ������ ����ϴ� ����� �ϴ� �Լ��̴�
void titleDraw() {
	cout << "Guess What?" << endl;
}

void gotoxy(int x, int y)//�޴������� ���� ���ϴ� ��ġ�� �ҷ����� ���� �ܰ踦 ��ĥ�� �ʿ��� �Լ��̴�
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//�ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

//���� �ؿ� �޴�ȭ�� ������ ���� �Լ�
int menu()
{
	int x = 2;
	int y = 2;
	gotoxy(x - 1, y);//'>'����� �ϱ� ���� -1�� �Ѵ�
	cout << ">���ӽ���";
	gotoxy(x, y + 2);
	cout << "���ӹ��";
	gotoxy(x, y + 4);
	cout << "����" << endl;
	while (1) {//���ѷ���
		int n = keyControl();//Ű���� �޾ƿ´�
		switch (n) {
		case UP: {//�Էµ� Ű�� w�� ���
			if (y>2) {
				//y�� 2~6���� �̵�
				gotoxy(x - 1, y);
				cout << " " << endl;//������ġ�� �����
				gotoxy(x - 1, --y);//���� �ö󰡱����ؼ� (�ܼ�â������ y��ǥ�� �Ʒ��� ���������� �����Ѵ� ���� ���� ���� ���ؼ��� y���� ���ҽ��Ѿ��Ѵ�)
				cout << ">";//�ٽñ׸���
			}
			break;
		}
		case DOWN:
		{//�Էµ� Ű�� s�� ���
			if (y < 6) {//y���� �ִ밡 6�̱⿡
				gotoxy(x - 1, y);
				cout << " " << endl;
				gotoxy(x - 1, ++y);//�Ʒ��� �������� ���ؼ�
				cout << ">";
			}
			break;
		}
		case SUBMIT:
		{//�����̽��ٸ� �������� ������ ����� �Ѵ�
			return y - 2;
			//y���� ��ġ�� 2���� ������ y-2�� �ϰԵǸ� 0,2,4���� �޾ƿ� �� �ִ�
		}
		}
	}
}

//���ӹ���� �����ֱ� ���� �Լ�
void info() {
	system("cls");//ȭ�� ���� �������

	cout << "���� 3���� ���ߴ� �����Դϴ�" << endl;
	cout << "���� 3�� Ʋ���� �Ǹ� ������ ���ᰡ �˴ϴ�" << endl;
	cout << "3���� ���ڸ� ���߰� �Ǹ� �����ܰ�� �ö� 4���� ���ڸ� ���߰� �˴ϴ�" << endl;
	cout << "������ 4���� ���ڱ��� ���߰� �ȴٸ� Game Clear!!" << endl;
	cout << "����ȭ������ �̵��Ͻ÷��� �����̽��ٸ� ��������" << endl;

	while (1) {//�����̽� ������ �ݺ� ���߰� ����ȭ������ ���ư���
		if (keyControl() == SUBMIT)
		{
			break;
		}
	}
}

void level() 
{
	system("cls");//ȭ�� ���� �������
	srand(time(NULL));

	//���� ���߱� ����
	int input[3]; //�Է¹޴� ������ ������ 3�� ���� �����Ѵ�. �̸� �迭�� �����Ѵ�
	int random[3]; //���� ���ڴ� ���� ������������ ���� �� �ֵ��� �Ѵ� �̸� �迭�� �����Ѵ�	
	int wrong = 0;//Ʋ�� Ƚ���� ī��Ʈ�ϱ� ���� �ʱ�ȭ �Ѵ�.
	int answer = 0;//���� Ƚ���� ī��Ʈ�ϱ� ���� �ʱ�ȭ �Ѵ�
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; i++)
	{
	random[i] = rand() % 10;
	}

	while (1)//���ѷ����� ������ֱ� ���� while���� ����Ͽ���
	{
		cout << "************************************************" << endl;
		cout << "���� ���߱� ����___���� ������ �� ���ΰ�" << endl;
		cout << "���� ���ڸ� �Է��� �ּ���(��� 0�Է½� ���ӿ���): " << endl;
		cout << "************************************************" << endl;

		//���� ������ ������ �Է¹޴´�
		cin >> input[0] >> input[1] >> input[2];

		if (input[0] == 0 && input[1] == 0 && input[2] == 0)//��� 0�� �Է��ϸ� �ݺ��� Ż���Ѵ�
			break;
		else if (input[0]<0 || input[0]>9 || input[1] < 0 || input[1]>9 || input[2]< 0 || input[2]>9)
		{
			Beep(450, 297); //Beep(���ļ�, ���ֽð�)�Լ��� 1���� ����Ѵ�
			cout << "���� ���� ������ �����Դϴ�. �ٽ� �Է��� �ּ���" << endl;
			wrong++;//3���� ����Ƚ���� �������ؼ� ������Ų��
		}
		else if (input[0] != random[0] || input[1] != random[1] || input[2] != random[2])
		{
			Beep(450, 297); //Beep(���ļ�, ���ֽð�)�Լ��� 1���� ����Ѵ�
			cout << "����!! Ʋ�Ƚ��ϴ� �ٽ� �Է��غ�����!" << endl;
			wrong++;//3���� ����Ƚ���� �������ؼ� ������Ų��
		}

		else if (input[0] == random[0] && input[1] == random[1] && input[2] == random[2])
		{
			levelUPsound();//�������� �˸��� ���� �Ҹ� ���
			cout << "�����Դϴ�!! ������!!" << endl;
			cout << "Next Level" << endl;
			answer++;//����Ƚ�� ī��Ʈ�ϱ� ���� 1 ����
		}
		if (wrong == 3)//����Ƚ���� 3ȸ�� �Ǵ� ���� �ݺ� Ż��
		{
			cout << "����Ƚ���� �ʰ��߽��ϴ�..������ �ٽ� �����ϼ���" << endl;
			break;
		}
		if (answer == 1) {//���� ����Ƚ���� 1�� �Ǹ� �ݺ��� Ż���Ѵ�
			break;
		}
	}
	if (answer == 1)//answer������ 1�̶�� �ش� �Լ��� ȣ���Ѵ�
	{
		levelUP();
	}
	system("pause");
}

void levelUPsound()
{//����Ҹ��� ����ϱ� ���� �Լ�

	Beep(260, 200);//��
	Beep(330, 200);//��
	Beep(380, 200);//��
	Beep(330, 200);//��
	Beep(260, 200);//��
}


void levelUP()
{
	//�����߻��� ����Ƚ�� ī��Ʈ�� ���� ������ ���� �迭�� ������ �������ش�
	srand(time(NULL));
	int input2[4];
	int random2[4];	
	//����Ƚ���� ���� ī��Ʈ ���ֱ� ���� �������ְ� 0���� �ʱ�ȭ ���ش�
	int wrong2 = 0;
	srand((unsigned int)time(0));

	//�߻��� ������ ������ �迭�� �Ҵ����ش�
	for (int i = 0; i < 4; i++)
	{
	random2[i] = rand() % 10;
	}


	//�տ��� ������� ¥�ӻ��� �����ϰ� ������ش�
	while (1)
	{
		cout << "************************************************" << endl;
		cout << "����2�� 4���� ���ڸ� ���߽ø� �˴ϴ�" << endl;
		cout << "���� ���ڸ� �Է��� �ּ���(��� 0�Է½� ���ӿ���): " << endl;
		cout << "************************************************" << endl;

		cin >> input2[0] >> input2[1] >> input2[2] >> input2[3];
		
		if (input2[0] == 0 && input2[1] == 0 && input2[2] == 0 && input2[3]==0)//���� ��� 0�Է½� �ݺ� Ż���Ͽ� ��������
			break;
		else if (input2[0] < 0 || input2[0]>9 || input2[1] < 0 || input2[1]>9 || input2[2] < 0 || input2[2]>9 || input2[3] < 0 || input2[3]>9)
		{
			Beep(450, 297); //Beep(���ļ�, ���ֽð�)�Լ��� 1���� ����Ѵ�
			cout << "�������� ������ �����Դϴ�. �ٽ� �Է��� �ּ���" << endl;
			//����Ƚ�� 3���� �Ѿ�� �����ϱ� ���ؼ� 1 �������ش�
			wrong2++;
		}
		else if (input2[0] != random2[0] || input2[1] != random2[1] || input2[2] != random2[2] || input2[3] != random2[3])
		{
			Beep(450, 297); //Beep(���ļ�, ���ֽð�)�Լ��� 1���� ����Ѵ�
			cout << "����!! Ʋ�Ƚ��ϴ� �ٽ� �Է��غ�����!" << endl;
			//����Ƚ�� 3���� �Ѿ�� �����ϱ� ���ؼ� 1 �������ش�
			wrong2++;

		}
		else if (input2[0] == random2[0] && input2[1] == random2[1] && input2[2] == random2[2] && input2[3] == random2[3])
		{//�����̶�� �ݺ����� Ż���Ͽ� ������ �����Ѵ�
			levelUPsound();
			cout << "�����̿���! �����մϴ�!" << endl;
			break;
		}
		if (wrong2 == 3)//����Ƚ���� 3ȸ�� �Ǵ� ���� ����
		{
			cout << "����Ƚ���� �ʰ��߽��ϴ�..������ �ٽ� �����ϼ���" << endl;
			break;
		}
	}

}
//main���� ȣ�⸸ ���ش�
int main()
{
	while (1) {//���ѷ����� ����Ͽ� ��� �ݺ����ְ� ������ش�
		titleDraw();
		int menuCode = menu();
		//menu()���� ��ȯ�� ���� ���� ���ǹ��� �����
		if (menuCode == 0) {
			//���ӽ���
			level();
		}
		else if (menuCode == 2) {
			//��������
			info();
		}
		else if (menuCode == 4) {
			//��������
			return 0;
		}
		system("cls");//�ܼ�â�� ��� ���� ���� �ܼ� ��ǥ 0,0 ���� �ʱ�ȭ
	}
	return 0;
}

int keyControl() {//w,s,space�� ���Ʒ� �̵��� �� �� �ְ� ������ֱ� ���ؼ� ����
	char temp = _getch();//Ű���忡 ó���Է��� �ѱ��� ��� �޾Ƶ��̰� �� ���� Ű�� enterŰ�� �޾Ƶ鿩 ȭ�鿡 ������ �ʴ´�
	if (temp == ' ')
	{//�����̽� �Է¿� ���� �κ�(������ ���� Ű)
		return SUBMIT;
	}
	else if (temp == 's' || temp == 'S')
	{//���� �ö󰡱� ���� Ű�� ����
		return DOWN;
	}
	else if (temp == 'w' || temp == 'W')
	{//������ �������� ���� Ű�� ����
		return UP;
	}
}
