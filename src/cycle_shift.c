#include <stdio.h>
#include <math.h>


int input(int *flag, int *data, const int n);
void output(int *flag, int *data, const int n);
void left(int *data, const int k, const int n);
void right(int *data, const int k, const int n);

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int data[10] = {0};
        int flag = 0;
        input(&flag, data, n);
        int k;
        if (scanf("%d", &k) == 1) {
            if (k > 0) {
                left(data, k, n);
            }
            else if (k < 0) {
                right(data, k, n);
            }
        }
        else {
            printf("n/a");
            return 3;
        }
        output(&flag, data, n);
    }
    else {
        printf("n/a");
        return 2;
    }

    return 0;
}

int input(int *flag, int *data, const int n) {
    int temp;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &temp) == 1)
            *(data + i) = temp;
        else
            *flag = 1;
    }
    return 0;
}

void output(int *flag, int *data, const int n) {
    if (*flag != 1)
        for (int i = 0; i < n; ++i)
            printf("%d ", *(data + i));
    else {
        printf("n/a");
    }
}

void left(int *data, const int k, const int n) {
    int count = k;
    while (count != 0) {
        int temp = *(data);
        for (int i = 0; i < n - 1; ++i) {
            *(data + i) = *(data + i + 1);
        }
        *(data + (n - 1)) = temp;
        --count;
    }
}

void right(int *data, const int k, const int n) {
    int count = k;
    count = abs(count);
    while (count != 0) {
        int temp = *(data + (n - 1));
        for (int i = n - 1; i > 0; --i) {
            *(data + i) = *(data + i - 1);
        }
        *(data) = temp;
        --count;
    }
}
