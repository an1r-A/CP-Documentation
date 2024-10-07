// To find the GCD of two number a and b we can use the built-in function __gcd(a, b)
// To find x and y such that a*x + b*y = GCD(a, b) we can use the Extended Euclidean Algorithm
// Link: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#algorithm

int Extended_Euclidian(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = Extended_Euclidian(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Mod_inverse
// suppose we want the the inverse of a mod b
// That's like finding x such that a*x == 1 mod(b)
// In order to do that we need to find x as a solution of the equation a*x + b*y = 1
// That means that we need to find the GCD(a, b) == 1 and find x and y using extended euclidian algorithm
int a, b;
int x, y;
int g = Extended_Euclidian(a, b, x, y);
if (g != 1) {
    cout << "No solution!";
}
else {
    x = (x % b + b) % b;
    cout << x << endl;
}

// 10^9 + 7 is a prime number so if b == 10^9 + 7
// This way we can use Fermat's Theorem and find a^-1 because a^(m - 2) == a^-1 mod(b)
// We need just to calculate a^(m - 2) using binary modular exponentiation
// a . b = (a mod m) * (b mod m) (mod m)
// Complexity of the algorithm O(logn)
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// When it comes to an array of numbers we want to find modular inverse of them modulo m we can optimise things with this algorithm
std::vector<int> invs(const std::vector<int> &a, int m) {
    int n = a.size();
    if (n == 0) return {};
    std::vector<int> b(n);
    int v = 1;
    for (int i = 0; i != n; ++i) {
        b[i] = v;
        v = static_cast<long long>(v) * a[i] % m;
    }
    int x, y;
    Extended_Euclidian(v, m, x, y);
    x = (x % m + m) % m;
    for (int i = n - 1; i >= 0; --i) {
        b[i] = static_cast<long long>(x) * b[i] % m;
        x = static_cast<long long>(x) * a[i] % m;
    }
    return b;
}
// Sometimes we need to know if a number is prime, we have multiple ways.
// if we check for just one number (use the classic algo)
// if we want the algo for multiple values we just use sieve
int n;
vector<bool> is_prime(n+1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i <= n; i++) {
    if (is_prime[i] && (long long)i * i <= n) {
        for (int j = i * i; j <= n; j += i)
            is_prime[j] = false;
    }
}
// Linear Sieve is a much stronger algorithm
// It relies on classical Sieve 
// The benefit is that it will help us find also the smallest prime factor (we can this way reverse and find all the prime factors of the number)
// The output is an array: if arr[i] == 0 it's prime, if not the i is not prime and the smallest factor is arr[i] of course i >= 2
const int N = 10000000; // We can change the upper_bound
vector<int> lp(N+1);
vector<int> pr;

for (int i=2; i <= N; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
        lp[i * pr[j]] = pr[j];
        if (pr[j] == lp[i]) {
            break;
        }
    }
}
// Complexity is O(n)

// Now let's suppose we want to find the number of divisors d(n) of a number and their sum s(n)
// First d(n) and s(n) and multiplicative functions
// d(a*b) = d(a) * d(b)
long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}

long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}

//  LCM(a, b) = (a x b) / GCD(a, b)