// 我们调用:
logger->info("output {}", (void*)ptr);

// 它做的：
std::tm tm;
localtime_r(&time_tt, &tm);
CharBuffer time = asctime(&tm);
CharBuffer s = time + ("output ");
CharBuffer arg_buffer;
std::ostream os(arg_buffer);
os << (void*)ptr;
s.append(arg_buffer);
{
    std::lock_guard lk(stdout_mutex);
    std::cout << s.str();
}
// 最终输出:
// 2017-02-01 21:00:00 output 0xdeadbeef
