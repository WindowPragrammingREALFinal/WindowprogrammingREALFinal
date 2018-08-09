#include "UI.h"

void Health(HDC memdc, int Life)
{
	CImage health[5];
	WCHAR LoadText[1000];
	WCHAR LoadText2[1000];

	wsprintf(LoadText, L"Health\\helth.png");
	wsprintf(LoadText2, L"Health\\helth2.png");

	for (int i = 0; i < 5; ++i) {
		if (i < Life)
			health[i].Load(LoadText);
		else
			health[i].Load(LoadText2);

		health[i].Draw(memdc, i * 50, 10, 50, 50, 0, 0, 50, 50);
	}
}

void Result(HDC memdc, int score) // 결과창 애니메이션도 있음
{
	
}

void screenAnimation(HDC memdc)
{

}

