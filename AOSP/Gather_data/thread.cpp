#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>


class Thread final
{
public:
    /** Start a new thread
     *
     * Thread will be pinned to a given core id if value is non-negative
     *
     * @param[in] core_pin Core id to pin the thread on. If negative no thread pinning will take place
     */
    //explicit Thread();

    //Thread(const Thread &) = delete;
    //Thread &operator=(const Thread &) = delete;
    //Thread(Thread &&)                 = delete;
    //Thread &operator=(Thread &&) = delete;

    /** Destructor. Make the thread join. */
    ~Thread();


    void Create();

    /** Request the worker thread to start executing workloads.
     *
     * The thread will start by executing workloads[info.thread_id] and will then call the feeder to
     * get the index of the following workload to run.
     *
     * @note This function will return as soon as the workloads have been sent to the worker thread.
     * wait() needs to be called to ensure the execution is complete.
     */
    //void start(std::vector<IScheduler::Workload> *workloads, ThreadFeeder &feeder, const ThreadInfo &info);
    void start();

    /** Wait for the current kernel execution to complete. */
    void wait();

    /** Function ran by the worker thread. */
    void worker_thread();

    bool				done{false};
private:
    std::thread                        _thread{};
    //ThreadInfo                         _info{};
    //std::vector<IScheduler::Workload> *_workloads{ nullptr };
    //ThreadFeeder                      *_feeder{ nullptr };
    std::mutex                         _m{};
    std::condition_variable            _cv{};
    bool                               _wait_for_work{ false };
    bool                               _job_complete{ true };
    std::exception_ptr                 _current_exception{ nullptr };
    //int                                _core_pin{ -1 };
    
};


/*Thread::Thread()
//    : _core_pin(core_pin)
{
    _thread = std::thread(&Thread::worker_thread, this);
    //_thread = std::thread(&Thread::worker_thread);
}*/
void Thread::Create()
//    : _core_pin(core_pin)
{
    _thread = std::thread(&Thread::worker_thread, this);
    //_thread = std::thread(&Thread::worker_thread);
}



Thread::~Thread()
{
    std::cerr<<"tamam\n";
    // Make sure worker thread has ended
    if(_thread.joinable())
    {
        //ThreadFeeder feeder;
        //start(nullptr, feeder, ThreadInfo());
        start();
        _thread.join();
    }
}



//void Thread::start(std::vector<IScheduler::Workload> *workloads, ThreadFeeder &feeder, const ThreadInfo &info)
void Thread::start()
{
    //_workloads = workloads;
    //_feeder    = &feeder;
    //_info      = info;
    {
        std::lock_guard<std::mutex> lock(_m);
        _wait_for_work = true;
        _job_complete  = false;
    }
    _cv.notify_one();
}


void Thread::wait()
{
    {
        std::unique_lock<std::mutex> lock(_m);
        _cv.wait(lock, [&] { return _job_complete; });
    }

    if(_current_exception)
    {
        std::rethrow_exception(_current_exception);
    }
}

float s[1000];
void process_workloads(int i)
{
	std::cerr<<"process\n";
	for (int j=0;j<i;j++){
		s[j]=i*1.2;
	}
}

void Thread::worker_thread()
{
    //set_thread_affinity(_core_pin);

    while(true)
    {
        std::unique_lock<std::mutex> lock(_m);
        _cv.wait(lock, [&] { return _wait_for_work; });
        std::cerr<<"notified\n";
        _wait_for_work = false;

        _current_exception = nullptr;

        // Time to exit
        //if(_workloads == nullptr)
        if(done)
        {
            return;
        }

#ifndef EXCEPTIONS_DISABLED
        try
        {
#endif
            process_workloads(1000);

#ifndef EXCEPTIONS_DISABLED
        }
        catch(...)
        {
            _current_exception = std::current_exception();
        }
#endif
        _job_complete = true;
        lock.unlock();
        _cv.notify_one();
    }
}

timespec t_switch;
Thread t;
float *a=NULL;
int main(){
	clock_gettime(CLOCK_MONOTONIC, &t_switch);
	std::cerr<<"starting main\n";
	t.Create();
	std::cerr<<"salam\n";
	//t.wait();
	std::cerr<<"salam2\n";
	t.start();
	std::cerr<<"salam3\n";
	//t.wait();
	t.start();
	//t.wait();
	std::cerr<<"salam4\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//t.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	t.done=true;
	a=new float[10];
	a[4]=3;
	//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	//t.start();
	//t.join();
	return 0;
}
