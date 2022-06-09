#include <stdio.h>

int 入力(char* requested)
{
    int number = 0;
    printf("%s: ", requested);
    scanf("%d", &number);
    return number;
}

void 答え出力(int 割られる数, int 割る数, int 商, int 余り)
{
    printf("%d ÷ %d = %d 余り %d", 割られる数, 割る数, 商, 余り);
}

int ビット数を8bitに調整(int number)
{
    return number & 0b11111111;
}

int x1は負の数か(int x1x2)
{
    return ((x1x2 >> 7) & 0b1) == 1;
}

int X1とX2とCを左へ1bitシフト(int x1x2, int c)
{
    return ビット数を8bitに調整((x1x2 + c) << 1);
}

int X1引くY(x1x2, y)
{
    return ビット数を8bitに調整(x1x2 - y);
}

int X1足すY(x1x2, y)
{
    return ビット数を8bitに調整(x1x2 + y);
}

int main()
{
    int 割る数 = 入力("割られる数");
    int 割られる数 = 入力("割る数");

    int x1x2 = 割る数;
    int y = 割られる数 << 4;

    int n = 4;
    int c = 0;

    // Y ≠ 0
    if (y == 0) {
        puts("オーバーフロー");
        return 0;
    }

    // X1 ← X1 - Y
    x1x2 = X1引くY(x1x2, y);

    // X1 < 0
    if (!x1は負の数か(x1x2)) {
        puts("オーバーフロー");
        return 0;
    }

    // X1 X2 Cを左へ1bitシフト
    x1x2 = X1とX2とCを左へ1bitシフト(x1x2, c);

    // X1 ← X1 + Y
    x1x2 = X1足すY(x1x2, y);

    // n ← n - 1
    n--;

    do {
        // X1 >= 0
        if (x1は負の数か(x1x2)) {
            // X1 < 0のとき

            // C ← 0
            c = 0;

            // X1 X2 Cを左へ1bitシフト
            x1x2 = X1とX2とCを左へ1bitシフト(x1x2, c);

            // X1 ← X1 + Y
            x1x2 = X1足すY(x1x2, y);
        } else {
            // X1 >= 0のとき

            // C ← 1
            c = 1;

            // X1 X2 Cを左へ1bitシフト
            x1x2 = X1とX2とCを左へ1bitシフト(x1x2, c);

            // X1 ← X1 - Y
            x1x2 = X1引くY(x1x2, y);
        }
        // n ← n - 1
        n--;
    } while (n != 0);

    // X1 >= 0
    if (x1は負の数か(x1x2)) {
        // c ← 0;
        c = 0;
        // X1 ← X1 + Y 回復処理
        x1x2 = X1足すY(x1x2, y);
    } else {
        // X1 >= 0のとき

        // c ← 1;
        c = 1;
    }
    x1x2 += c;

    int 商 = x1x2 & 0b1111;
    int 余り = (x1x2 >> 4) & 0b1111;

    答え出力(割る数, 割られる数, 商, 余り);

    return 0;
}