class Foo {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int data;
public:
    Foo() : data(0) {
    }

    void first(function<void()> printFirst) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            printFirst();
            data = 1;
        }
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return data >= 1; });
            printSecond();
            data = 2;
        }
        cv.notify_all();

    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return data >= 2; });
            printThird();
        }
        cv.notify_all();

    }
};