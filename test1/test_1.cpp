#include <iostream>
#include<cstdlib>
#include<ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define UP 0
#define DOWN 1
#define SUBMIT 4 //선택 스페이스바

//밑에 정의할 함수의 헤더를 작성해준다
int keyControl();
void level();
void levelUPsound();
void levelUP();
void titleDraw();
void gotoxy(int, int);
int menu();
void info();

//게임의 제목을 출력하는 기능을 하는 함수이다
void titleDraw() {
	cout << "Guess What?" << endl;
}

void gotoxy(int x, int y)//메뉴정보를 내가 원하는 위치로 불러오기 위한 단계를 거칠때 필요한 함수이다
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

//제목 밑에 메뉴화면 구성을 위한 함수
int menu()
{
	int x = 2;
	int y = 2;
	gotoxy(x - 1, y);//'>'출력을 하기 위해 -1을 한다
	cout << ">게임시작";
	gotoxy(x, y + 2);
	cout << "게임방법";
	gotoxy(x, y + 4);
	cout << "종료" << endl;
	while (1) {//무한루프
		int n = keyControl();//키값을 받아온다
		switch (n) {
		case UP: {//입력된 키가 w인 경우
			if (y>2) {
				//y는 2~6까지 이동
				gotoxy(x - 1, y);
				cout << " " << endl;//원래위치를 지우고
				gotoxy(x - 1, --y);//위로 올라가기위해서 (콘솔창에서의 y좌표는 아래로 내려갈수록 증가한다 따라서 위로 가기 위해서는 y값을 감소시켜야한다)
				cout << ">";//다시그리기
			}
			break;
		}
		case DOWN:
		{//입력된 키가 s일 경우
			if (y < 6) {//y값의 최대가 6이기에
				gotoxy(x - 1, y);
				cout << " " << endl;
				gotoxy(x - 1, ++y);//아래로 내려가기 위해서
				cout << ">";
			}
			break;
		}
		case SUBMIT:
		{//스페이스바를 눌렀을때 선택의 기능을 한다
			return y - 2;
			//y시작 위치가 2였기 때문에 y-2를 하게되면 0,2,4값을 받아올 수 있다
		}
		}
	}
}

//게임방법을 보여주기 위한 함수
void info() {
	system("cls");//화면 비우고 새로출력

	cout << "숫자 3개를 맞추는 게임입니다" << endl;
	cout << "만약 3번 틀리게 되면 게임이 종료가 됩니다" << endl;
	cout << "3개의 숫자를 맞추게 되면 다음단계로 올라가 4개의 숫자를 맞추게 됩니다" << endl;
	cout << "마지막 4개의 숫자까지 맞추게 된다면 Game Clear!!" << endl;
	cout << "메인화면으로 이동하시려면 스페이스바를 누르세요" << endl;

	while (1) {//스페이스 누를시 반복 멈추고 메인화면으로 돌아간다
		if (keyControl() == SUBMIT)
		{
			break;
		}
	}
}

void level() 
{
	system("cls");//화면 비우고 새로출력
	srand(time(NULL));

	//숫자 맞추기 게임
	int input[3]; //입력받는 숫자의 개수를 3개 부터 시작한다. 이를 배열로 정의한다
	int random[3]; //정답 숫자는 각각 난수생성으로 얻을 수 있도록 한다 이를 배열로 정의한다	
	int wrong = 0;//틀린 횟수를 카운트하기 위해 초기화 한다.
	int answer = 0;//정답 횟수를 카운트하기 위해 초기화 한다
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; i++)
	{
	random[i] = rand() % 10;
	}

	while (1)//무한루프를 만들어주기 위해 while문을 사용하였다
	{
		cout << "************************************************" << endl;
		cout << "숫자 맞추기 게임___과연 어디까지 갈 것인가" << endl;
		cout << "정답 숫자를 입력해 주세요(모두 0입력시 게임오버): " << endl;
		cout << "************************************************" << endl;

		//내가 생각한 정답을 입력받는다
		cin >> input[0] >> input[1] >> input[2];

		if (input[0] == 0 && input[1] == 0 && input[2] == 0)//모두 0을 입력하면 반복을 탈출한다
			break;
		else if (input[0]<0 || input[0]>9 || input[1] < 0 || input[1]>9 || input[2]< 0 || input[2]>9)
		{
			Beep(450, 297); //Beep(주파수, 연주시간)함수로 1번만 출력한다
			cout << "옳지 않은 범위의 숫자입니다. 다시 입력해 주세요" << endl;
			wrong++;//3번의 오류횟수를 세기위해서 증가시킨다
		}
		else if (input[0] != random[0] || input[1] != random[1] || input[2] != random[2])
		{
			Beep(450, 297); //Beep(주파수, 연주시간)함수로 1번만 출력한다
			cout << "삐입!! 틀렸습니다 다시 입력해보세요!" << endl;
			wrong++;//3번의 오류횟수를 세기위해서 증가시킨다
		}

		else if (input[0] == random[0] && input[1] == random[1] && input[2] == random[2])
		{
			levelUPsound();//정답임을 알리기 위한 소리 출력
			cout << "정답입니다!! 레벨업!!" << endl;
			cout << "Next Level" << endl;
			answer++;//정답횟수 카운트하기 위해 1 증가
		}
		if (wrong == 3)//오류횟수가 3회가 되는 순간 반복 탈출
		{
			cout << "오류횟수를 초과했습니다..다음에 다시 도전하세요" << endl;
			break;
		}
		if (answer == 1) {//만약 정답횟수가 1이 되면 반복을 탈출한다
			break;
		}
	}
	if (answer == 1)//answer변수가 1이라면 해당 함수를 호출한다
	{
		levelUP();
	}
	system("pause");
}

void levelUPsound()
{//정답소리를 출력하기 위한 함수

	Beep(260, 200);//도
	Beep(330, 200);//미
	Beep(380, 200);//솔
	Beep(330, 200);//미
	Beep(260, 200);//도
}


void levelUP()
{
	//난수발생과 오류횟수 카운트를 위해 다음과 같은 배열과 변수를 정의해준다
	srand(time(NULL));
	int input2[4];
	int random2[4];	
	//오류횟수를 새로 카운트 해주기 위해 정의해주고 0으로 초기화 해준다
	int wrong2 = 0;
	srand((unsigned int)time(0));

	//발생한 난수를 정의한 배열에 할당해준다
	for (int i = 0; i < 4; i++)
	{
	random2[i] = rand() % 10;
	}


	//앞에서 만들었던 짜임새와 동일하게 만들어준다
	while (1)
	{
		cout << "************************************************" << endl;
		cout << "레벨2는 4개의 숫자를 맞추시면 됩니다" << endl;
		cout << "정답 숫자를 입력해 주세요(모두 0입력시 게임오버): " << endl;
		cout << "************************************************" << endl;

		cin >> input2[0] >> input2[1] >> input2[2] >> input2[3];
		
		if (input2[0] == 0 && input2[1] == 0 && input2[2] == 0 && input2[3]==0)//만약 모두 0입력시 반복 탈출하여 게임종료
			break;
		else if (input2[0] < 0 || input2[0]>9 || input2[1] < 0 || input2[1]>9 || input2[2] < 0 || input2[2]>9 || input2[3] < 0 || input2[3]>9)
		{
			Beep(450, 297); //Beep(주파수, 연주시간)함수로 1번만 출력한다
			cout << "옳지않은 범위의 숫자입니다. 다시 입력해 주세요" << endl;
			//오류횟수 3번을 넘어갈시 종료하기 위해서 1 증가해준다
			wrong2++;
		}
		else if (input2[0] != random2[0] || input2[1] != random2[1] || input2[2] != random2[2] || input2[3] != random2[3])
		{
			Beep(450, 297); //Beep(주파수, 연주시간)함수로 1번만 출력한다
			cout << "삐입!! 틀렸습니다 다시 입력해보세요!" << endl;
			//오류횟수 3번을 넘어갈시 종료하기 위해서 1 증가해준다
			wrong2++;

		}
		else if (input2[0] == random2[0] && input2[1] == random2[1] && input2[2] == random2[2] && input2[3] == random2[3])
		{//정답이라면 반복문을 탈출하여 게임을 종료한다
			levelUPsound();
			cout << "정답이에요! 축하합니다!" << endl;
			break;
		}
		if (wrong2 == 3)//오류횟수가 3회가 되는 순간 종료
		{
			cout << "오류횟수를 초과했습니다..다음에 다시 도전하세요" << endl;
			break;
		}
	}

}
//main에서 호출만 해준다
int main()
{
	while (1) {//무한루프를 사용하여 계속 반복해주게 만들어준다
		titleDraw();
		int menuCode = menu();
		//menu()에서 반환된 값에 따라서 조건문을 만든다
		if (menuCode == 0) {
			//게임시작
			level();
		}
		else if (menuCode == 2) {
			//게임정보
			info();
		}
		else if (menuCode == 4) {
			//게임종료
			return 0;
		}
		system("cls");//콘솔창의 모든 글자 비우고 콘솔 좌표 0,0 으로 초기화
	}
	return 0;
}

int keyControl() {//w,s,space로 위아래 이동을 할 수 있게 만들어주기 위해서 정의
	char temp = _getch();//키보드에 처음입력한 한글자 즉시 받아들이고 그 다음 키는 enter키로 받아들여 화면에 보이지 않는다
	if (temp == ' ')
	{//스페이스 입력에 대한 부분(선택을 위한 키)
		return SUBMIT;
	}
	else if (temp == 's' || temp == 'S')
	{//위로 올라가기 위한 키를 정의
		return DOWN;
	}
	else if (temp == 'w' || temp == 'W')
	{//밑으로 내려가기 위한 키를 정의
		return UP;
	}
}
