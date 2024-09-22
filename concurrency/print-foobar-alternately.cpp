class FooBar {
private:
    int n, data;
    condition_variable cv;
    mutex mx;
public:
    FooBar(int n) {
        this->n = n;
        this->data = 0;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
        	{
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return !data; });
                printFoo();
                data = 1;
            }
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
        	{
                unique_lock<mutex> lock(mx);
                cv.wait(lock, [this] { return data; });
                printBar();
                data = 0;
            }
            cv.notify_one();
        }
    }
};