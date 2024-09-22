class H2O {
private:
    int data;
    condition_variable cv;
    mutex mx;
public:
    H2O() {
        data = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        {
            unique_lock<mutex> lock(mx);
            cv.wait(lock, [this] { return data < 2; });
            releaseHydrogen();
            data++;
        }
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        {
            unique_lock<mutex> lock(mx);
            cv.wait(lock, [this] { return data > -1; });
            releaseOxygen();
            data-=2;
        }
        cv.notify_all();
    }
};