class FizzBuzz {
private:
    int n;
    condition_variable cv;
    mutex mx;
    int counter;
public:
    FizzBuzz(int n) {
        this->n = n;
        counter = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return (counter % 3 == 0 && counter % 5 != 0) || counter > n; });
                if (counter > n)
                    break;
                printFizz();
                counter++;
            }
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return (counter % 5 == 0 && counter % 3 != 0) || counter > n; });
                if (counter > n)
                    break;
                printBuzz();
                counter++;
            }
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return (counter % 5 == 0 && counter % 3 == 0) || counter > n; });
                if (counter > n)
                    break;
                printFizzBuzz();
                counter++;
            }
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return (counter % 5 != 0 && counter % 3 != 0) || counter > n; });
                if (counter > n) 
                    break;
                printNumber(counter++);
            }
            cv.notify_all();
        }
    }
};