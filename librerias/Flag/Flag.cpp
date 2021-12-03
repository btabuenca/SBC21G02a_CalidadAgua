	#include "Flag.h"
    Flag::Flag() : flag_{false} {}

    Flag::void set()
    {
        std::lock_guard g(mutex_);
        flag_ = true;
        cond_var_.notify_all();
    }

    Flag::void clear()
    {
        std::lock_guard g(mutex_);
        flag_ = false;
    }

    Flag::void wait()
    {
        std::unique_lock lock(mutex_);
        cond_var_.wait(lock, [this]() { return flag_; });
    }
};