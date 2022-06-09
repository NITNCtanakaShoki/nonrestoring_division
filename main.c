#include <stdio.h>

int input(char* requested)
{
    int number = 0;
    printf("%s: ", requested);
    scanf("%d", &number);
    return number;
}

void printResult(int divided, int divide, int quotient, int remainder)
{
    printf("%d ÷ %d = %d 余り %d", divided, divide, quotient, remainder);
}

int trimmed8bit(int number)
{
    return number & 0b11111111;
}

int isX1Sign(int x1x2)
{
    return ((x1x2 >> 7) & 0b1) == 1;
}

int leftShifted(int x1x2, int c)
{
    return trimmed8bit((x1x2 + c) << 1);
}

int x1MinusY(x1x2, y)
{
    return trimmed8bit(x1x2 - y);
}

int x1PlusY(x1x2, y)
{
    return trimmed8bit(x1x2 + y);
}



int main()
{
    int dividedNumber = input("割られる数");
    int divideNumber = input("割る数");

    int x1x2 = dividedNumber;
    int y = divideNumber << 4;

    int n = 4;
    int c = 0;

    // Y ≠ 0
    if (y == 0) {
        puts("オーバーフロー");
        return 0;
    }

    // X1 ← X1 - Y
    x1x2 = x1MinusY(x1x2, y);

    // X1 < 0
    if (!isX1Sign(x1x2)) {
        puts("オーバーフロー");
        return 0;
    }

    // X1 X2 Cを左へ1bitシフト
    x1x2 = leftShifted(x1x2, c);

    // X1 ← X1 + Y
    x1x2 = x1PlusY(x1x2, y);

    // n ← n - 1
    n--;

    do {
        // X1 >= 0
        if (isX1Sign(x1x2)) {
            // X1 < 0のとき

            // C ← 0
            c = 0;

            // X1 X2 Cを左へ1bitシフト
            x1x2 = leftShifted(x1x2, c);

            // X1 ← X1 + Y
            x1x2 = x1PlusY(x1x2, y);
        } else {
            // X1 >= 0のとき

            // C ← 1
            c = 1;

            // X1 X2 Cを左へ1bitシフト
            x1x2 = leftShifted(x1x2, c);

            // X1 ← X1 - Y
            x1x2 = x1MinusY(x1x2, y);
        }
        // n ← n - 1
        n--;
    } while (n != 0);

    // X1 >= 0
    if (isX1Sign(x1x2)) {
        // c ← 0;
        c = 0;
        // X1 ← X1 + Y 回復処理
        x1x2 = x1PlusY(x1x2, y);
    } else {
        // X1 >= 0のとき

        // c ← 1;
        c = 1;
    }
    x1x2 += c;

    int quotient = x1x2 & 0b1111;
    int remainder = (x1x2 >> 4) & 0b1111;

    printResult(dividedNumber, divideNumber, quotient, remainder);

    return 0;
}