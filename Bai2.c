#include <stdio.h>
#include <stdlib.h>

// Hàm sàng Eratosthenes để tìm tất cả các số nguyên tố nhỏ hơn N
void thuattoanEratosthenes(int n, int primes[]) {
    for (int i = 2; i <= n; i++) {
        primes[i] = 1; // Giả sử tất cả các số đều là số nguyên tố
    }
    for (int p = 2; p * p <= n; p++) {
        if (primes[p]) {
            for (int i = p * p; i <= n; i += p) {
                primes[i] = 0; // Đánh dấu các bội của p là hợp số
            }
        }
    }
}

// Hàm kiểm tra số Blum
int isBlum(int p, int q, int primes[]) {
    return primes[p] && primes[q] && p % 4 == 3 && q % 4 == 3;
}

// Hàm sinh các số Blum và kiểm tra tổng của các cặp số Blum
void taovakiemtraBlum(int N) {
    int *primes = (int*)malloc(N * sizeof(int));
    thuattoanEratosthenes(N, primes);

    // Mảng để lưu trữ các số Blum
    int *blums = (int*)malloc(N/2 * sizeof(int)); // Ước lượng số lượng số Blum
    int blumCount = 0;

    for (int p = 3; p < N; p += 2) {
        if (primes[p] && p % 4 == 3) {
            for (int q = p; q < N; q += 2) {
                if (primes[q] && q % 4 == 3) {
                    int blum = p * q;
                    blums[blumCount++] = blum;
                }
            }
        }
    }

    printf("Cac so Blum nho hon %d la:\n", N);
    for (int i = 0; i < blumCount; i++) {
        printf("%d ", blums[i]);
    }
    printf("\n");

    printf("Cac cap so Blum co tong cung la so Blum:\n");
    for (int i = 0; i < blumCount; i++) {
        for (int j = i + 1; j < blumCount; j++) {
            int sum = blums[i] + blums[j];
            if (sum < N && primes[sum] && sum % 4 == 3) {
                printf("(%d, %d) có tong la %d\n", blums[i], blums[j], sum);
            }
        }
    }
    free(primes);
    free(blums);
}

int main() {
    int N;
    printf("Nhap gia tri N: ");
    scanf("%d", &N);

    taovakiemtraBlum(N);

    return 0;
}