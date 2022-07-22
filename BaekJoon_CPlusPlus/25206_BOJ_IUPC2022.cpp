/* 백준 25206번 너의 평점은 // IUPC #2
*
* Input: 20줄에 걸쳐 치훈이가 수강한 전공과목의 과목명, 학점, 등급이 공백으로 구분되어 주어진다.
*		 1) 1 <= 과목명 길이 <= 50
*		 2) 과목명은 아파벳 대소문자 또는 숫자로만 이루어져 있으며, 띄어쓰기 없다. 모든 과목명은 서로 다르다
*		 3) 학점은 1.0, 2.0, 3.0, 4.0 중 하나이다.
*		 4) 등급은 A+, A0, B+, B0, C+, C0, D+, D0, F, P 중 하나이다.
*		 5) 적어도 한 과목은 등급이 P가 아님이 보장된다.
*
* Output: 전공평점을 출력한다. 정답과의 절대오차 또는 상대오차가 10^(-4) 이하이면 정답으로 인정한다.
*		  전공평점은 전공과목별 (학점 x 과목평점)의 합을 학점의 총합을 나눈 값이다.
*/


#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	double ret = 0;
	string name, grade;
	float each = 0, fGrade;
	float sum = 0;

	for (int i = 0; i < 20; i++)
	{
		cin >> name >> each >> grade;
		
		if (grade == "A+") fGrade = 4.5;
		else if (grade == "A0") fGrade = 4.0;
		else if (grade == "B+") fGrade = 3.5;
		else if (grade == "B0") fGrade = 3.0;
		else if (grade == "C+") fGrade = 2.5;
		else if (grade == "C0") fGrade = 2.0;
		else if (grade == "D+") fGrade = 1.5;
		else if (grade == "D0") fGrade = 1.0;
		else if (grade == "F") fGrade = 0.0;
		else continue;

		ret = ret + (fGrade * each) * pow(10, 4);
		sum += each;
	}

	/*cout << fixed << setprecision(6);*/
	ret /= sum;
	ret /= pow(10, 4);
	cout << ret;


	return 0;
}