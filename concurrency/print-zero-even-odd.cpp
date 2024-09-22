class ZeroEvenOdd {
private:
    int n;
    int counter, turn;
    condition_variable cv;
    mutex mx;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        turn=0, counter=1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return turn == 0 || counter > n; });
                if (counter > n)
                    break;
                printNumber(0);
                turn = counter & 1 ? 1 : 2;
            }
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return turn == 2 || counter > n; });
                if (counter > n)
                    break;
                printNumber(counter++);
                turn = 0;

            }
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (counter <= n) {
            {
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return turn == 1 || counter > n; });
                if (counter > n)
                    break;
                printNumber(counter++);
                turn = 0;

            }
            cv.notify_all();
        }
    }
};