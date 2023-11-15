#include <coroutine>
#include <iostream>

struct promise;
 
struct ReceiverCoroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};
 
struct promise{
    ReceiverCoroutine get_return_object() { return {ReceiverCoroutine::from_promise(*this)}; }
    std::suspend_never initial_suspend() noexcept { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
};


ReceiverCoroutine Receiver() {
    std::cout << "Coroutine started\n";
    co_await std::suspend_always{}; // Suspend the coroutine
    std::cout << "Coroutine resumed\n";
}

int main(int argc, char* argv[]) {
    auto coroutine =  Receiver();
    coroutine.resume();
    return 0;
}