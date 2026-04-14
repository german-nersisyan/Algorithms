#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

class MMap {
private:
    void* data_ = nullptr;
    size_t size_ = 0;
    int fd_ = -1;
    bool owner_ = false;

public:
    // Disable copy
    MMap(const MMap&) = delete;
    MMap& operator=(const MMap&) = delete;

    // Move semantics
    MMap(MMap&& other) noexcept {
        *this = std::move(other);
    }

    MMap& operator=(MMap&& other) noexcept {
        if (this != &other) {
            cleanup();

            data_ = other.data_;
            size_ = other.size_;
            fd_ = other.fd_;
            owner_ = other.owner_;

            other.data_ = nullptr;
            other.fd_ = -1;
        }
        return *this;
    }

    MMap() = default;

    // File-backed mmap
    static MMap mapFile(const std::string& path, bool write = false) {
        MMap m;

        int flags = write ? O_RDWR : O_RDONLY;
        m.fd_ = open(path.c_str(), flags);
        if (m.fd_ < 0) {
            throw std::runtime_error("open failed");
        }

        struct stat st;
        if (fstat(m.fd_, &st) < 0) {
            close(m.fd_);
            throw std::runtime_error("fstat failed");
        }

        m.size_ = st.st_size;

        int prot = write ? (PROT_READ | PROT_WRITE) : PROT_READ;

        m.data_ = mmap(nullptr, m.size_, prot, MAP_SHARED, m.fd_, 0);
        if (m.data_ == MAP_FAILED) {
            close(m.fd_);
            throw std::runtime_error("mmap failed");
        }

        m.owner_ = true;
        return m;
    }

    // Anonymous mmap
    static MMap mapAnonymous(size_t size) {
        MMap m;

        m.size_ = size;
        m.fd_ = -1;

        m.data_ = mmap(nullptr, size,
                       PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS,
                       -1, 0);

        if (m.data_ == MAP_FAILED) {
            throw std::runtime_error("anonymous mmap failed");
        }

        m.owner_ = true;
        return m;
    }

    void* data() { return data_; }
    const void* data() const { return data_; }

    size_t size() const { return size_; }

    template<typename T>
    T* as() {
        return reinterpret_cast<T*>(data_);
    }

    void sync() {
        if (data_) {
            msync(data_, size_, MS_SYNC);
        }
    }

    ~MMap() {
        cleanup();
    }

private:
    void cleanup() {
        if (data_ && data_ != MAP_FAILED) {
            munmap(data_, size_);
        }
        if (fd_ >= 0) {
            close(fd_);
        }
        data_ = nullptr;
        fd_ = -1;
    }
};

int main() {
    auto mmap = MMap::mapAnonymous(1024);

    int* arr = mmap.as<int>();

    arr[0] = 42;
    arr[1] = 99;

    std::cout << arr[0] << " " << arr[1] << "\n";
}