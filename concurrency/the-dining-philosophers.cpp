class DiningPhilosophers {
private:
    vector<int> forks;
    condition_variable cv;
    mutex mx;
    int left, right;
public:
    DiningPhilosophers() {
        forks = {0, 0, 0, 0, 0};
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		{
            unique_lock<mutex> lock(mx);
            this->right = philosopher;
            this->left = (philosopher+1)%5;
            
            cv.wait(lock, [this] { return !forks[right]; });
            pickRightFork();

            cv.wait(lock, [this] { return !forks[left]; });
            pickLeftFork();

            eat();

            putRightFork();
            forks[philosopher] = 0;

            putLeftFork();
            forks[(philosopher+1)%5] = 0;
            
        }
        cv.notify_all();
    }
};